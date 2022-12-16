#include "touchstone.h"

#include "utils.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ========================================================================== */
/*                      Local to this translation unit                        */
/* ========================================================================== */

#define LINE_BUFF_LENGTH 255

int
get_n_ports(const char* filename)
{
  int n_ports;
  char* ext;
  char n_ports_str[3];

  ext = strstr(filename, ".s");
  strncpy(n_ports_str, ext + 2, strlen(ext) - 3);
  n_ports = (int) atol(n_ports_str);

  return n_ports;
}

enum complex_format
{
  DB, /* 20 * log10(magnitude) and angle in degrees */
  MA, /* Magnitude and angle in degrees */
  RI  /* Real and imaginary part */
};

void
parse_options_line(char* line,
                   double* r_ref,
                   double* freq_factor,
                   char* type,
                   enum complex_format* format)
{
  int i;
  char* token;

  /* Defaults */
  *freq_factor = 1.0e9; /* GHz */
  *type = 'S';          /* S-parameters */
  *format = MA;         /* Magnitude and phase in degrees */
  *r_ref = 50.0;        /* Ohm */

  /* Convert line to lowercase */
  for (i = 0; i < (int) strlen(line); ++i) {
    line[i] = (char)tolower(line[i]);
  }

  /* Parse line */
  token = strtok(line, " "); /* First token is '#' */
  while (NULL != (token = strtok(NULL, " "))) {
    /* Frequency unit */
    if (0 == strcmp(token, "hz")) {
      *freq_factor = 1.0;
    } else if (0 == strcmp(token, "khz")) {
      *freq_factor = 1.0e3;
    } else if (0 == strcmp(token, "mhz")) {
      *freq_factor = 1.0e6;
    } else if (0 == strcmp(token, "ghz")) {
      *freq_factor = 1.0e9;
    }

    /* Parameter type */
    if (0 == strcmp(token, "s") || 0 == strcmp(token, "y") ||
        0 == strcmp(token, "z") || 0 == strcmp(token, "h") ||
        0 == strcmp(token, "g")) {
      *type = (char)toupper(token[0]);
    }

    /* Complex number format */
    if (0 == strcmp(token, "db")) {
      *format = DB;
    } else if (0 == strcmp(token, "ma")) {
      *format = MA;
    } else if (0 == strcmp(token, "ri")) {
      *format = RI;
    }

    /* Reference impedance */
    if (0 == strcmp(token, "r")) {
      token = strtok(NULL, " ");
      *r_ref = atof(token);
    }
  }
}

cmplx
unformat_complex(const double a,
                 const double b,
                 const enum complex_format format)
{
  cmplx ret;
  switch (format) {
    case DB:
      ret = cmplx_abs_ang(pow(10.0, a / 20.0), deg2rad(b));
      break;
    case MA:
      ret = cmplx_abs_ang(a, deg2rad(b));
      break;
    case RI:
      ret = cmplx_real_imag(a, b);
      break;
  }
  return ret;
}

void clear_comment(char *line)
{
  /* Ignore line and tailing comments */
  char* comment;
  if (NULL != (comment = strchr(line, '!'))) {
    line[comment - line] = '\0';
  }
}

void parse_metadata(const char* filename,
                    const int n_ports,
                    int* n_freq,
                    double* r_ref,
                    double* freq_factor,
                    char* type,
                    enum complex_format* format)
{
  FILE* fp;
  char line[LINE_BUFF_LENGTH];
  char* token;
  int n_tokens;
  int n_nums_freq_line;

  /* Number of floating point numbers in lines of data block */
  switch (n_ports) {
    case 1:
      n_nums_freq_line = 3; /* 1 + 1 * 2 */
      break;
    case 2:
      n_nums_freq_line = 9; /* 1 + 4 * 2 */
      break;
    case 3:
      n_nums_freq_line = 7; /* 1 + 3 * 2 */
      break;
    case 4:
      n_nums_freq_line = 9; /* 1 + 4 * 2 */
      break;
    default:
      n_nums_freq_line = 9; /* 1 + 4 * 2 */
      break;
  }

  /* Open file for reading */
  if (!(fp = fopen(filename, "r"))) {
    fprintf(stderr, "Could not open file %s for reading.\n", filename);
  }

  /* Parse metainformation and count number of frequency sampling points */
  *n_freq = 0;
  while (fgets(line, LINE_BUFF_LENGTH, fp)) {
    /* Clear comments and ignore empty lines */
    clear_comment(line);
    if (0 == strlen(line)) {
      continue;
    }

    /* Options line */
    if ('#' == line[0]) {
      parse_options_line(line, r_ref, freq_factor, type, format);
      continue;
    }

    /* Data line */
    n_tokens = 0;
    if (NULL != (token = strtok(line, " "))) {
      n_tokens++;
    }
    while (NULL != (token = strtok(NULL, " "))) {
      n_tokens++;
    }
    if (5 == n_tokens) {
      /* Noise parameters */
      break;
    }
    if (n_tokens == n_nums_freq_line) {
      (*n_freq)++;
    }
  }
  fclose(fp);
}

void rowmaj2colmaj(cmplx *matrix_data, const int rows, const int cols)
{
  int m, n;
  int i_cm, i_rm;
  for (m = 0; m < rows; ++m) {
    for (n = 0; n < cols; ++n) {
      i_cm = m + n * rows;
      i_rm = n + m * cols;
      if (i_cm != i_rm) {
        matrix_data[i_cm] = matrix_data[i_rm];
      }
    }
  }
}

/* ========================================================================== */
/*                          Declared in header file                           */
/* ========================================================================== */

void
parse_touchstone(const char* filename,
                 int* n_ports,
                 int* n_freq,
                 double* r_ref,
                 double** freq,
                 cmplx** data)
{
  FILE* fp;
  char line[LINE_BUFF_LENGTH];
  char type;
  double freq_factor;
  enum complex_format format;
  int n_params;
  char *token;
  double *raw;
  int i, ii, iii, iiii;

  /* Counter for frequency sampling posize_ts */
  *n_freq = 0;

  /* Get number of ports */
  *n_ports = get_n_ports(filename);
  n_params = (*n_ports) * (*n_ports);

  /* First reading of file for metadata and number of sampling points */
  parse_metadata(filename, *n_ports, n_freq, r_ref, &freq_factor, &type, &format);

  /* Parse acutal data */
  fp = fopen(filename, "r");
  raw = malloc((*n_freq) * (1 + 2 * n_params) * sizeof(raw[0]));
  while (fgets(line, LINE_BUFF_LENGTH, fp)) {
    /* Skip everything except data lines */
    clear_comment(line);
    if ('#' == line[0]) {
      continue;
    }
    if (0 == strlen(line)) {
      continue;
    }

    /* Tokenize and store data stream */
    token = strtok(line, " ");
    raw[i++] = atof(token);
    while (NULL != (token = strtok(NULL, " "))) {
      raw[i++] = atof(token);
    }
  }
  fclose(fp);

  /* Assembe read raw data into target arrays */
  *freq = malloc((*n_freq) * sizeof((*freq)[0]));
  *data = malloc((*n_freq) * n_params * sizeof((*data)[0]));
  for (i = 0; i < *n_freq; ++i) {
    ii = i * (1 + n_params);
    (*freq)[i] = raw[ii];
    for (iii = 0; iii < n_params; ++iii) {
      iiii = ii + 1 + 2 * iii;
      (*data)[i * n_params] = unformat_complex(raw[iiii], raw[iiii + 1], format);
    }
  }
  free(raw);

  /* Only s2p is column major from Touchstone parsing */
  /* For three and more ports we have row major from Touchstone parsing */
  if (3 <= *n_ports) {
    for (i = 0; i < *n_freq; ++i) {
      rowmaj2colmaj(&(*data)[i * n_params], *n_ports, *n_ports);
    }
  }
}
