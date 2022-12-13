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
  n_ports = atoi(n_ports_str);

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
  for (i = 0; i < strlen(line); ++i) {
    line[i] = (char)tolower(line[i]);
  }

  /* Parse line */
  token = strtok(line, " "); /* First token is '#' */
  while (token != NULL) {
    token = strtok(NULL, " ");

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
  int n_params;
  FILE* fp;
  char line_buff[LINE_BUFF_LENGTH];
  char type;
  char* comment_char;
  int options_line_found = 0;
  double freq_factor = 1.0;
  enum complex_format format;
  int n_read;
  double f;    /* Frequency for sscanf */
  double a[8]; /* 1st number of complex format for sscanf */
  double b[8]; /* 2nd number of complex format for sscanf */
  int n_nums_freq_line;

  /* Counter for frequency sampling points */
  *n_freq = 0;

  /* Get number of ports */
  *n_ports = get_n_ports(filename);
  n_params = (*n_ports) * (*n_ports);

  /* Number of floating point numbers in lines of data block */
  switch (*n_ports) {
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
  while (fgets(line_buff, LINE_BUFF_LENGTH, fp)) {
    /* Ignore line and tailing comments */
    if (NULL != (comment_char = strchr(line_buff, '!'))) {
      line_buff[comment_char - line_buff] = '\0';
    }

    /* Ignore empty lines */
    if (0 == strlen(line_buff)) {
      continue;
    }

    /* Options line */
    if ('#' == line_buff[0] && !options_line_found) {
      parse_options_line(line_buff, r_ref, &freq_factor, &type, &format);
      options_line_found = 1;
      continue;
    }

    /* Count data lines */
    n_read = sscanf(
      line_buff,
      "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
      &f,
      &a[0],
      &b[0],
      &a[1],
      &b[1],
      &a[2],
      &b[2],
      &a[3],
      &b[3],
      &a[4],
      &b[4],
      &a[5],
      &b[5],
      &a[6],
      &b[6],
      &a[7],
      &b[7]);
    if (n_read == n_nums_freq_line) {
      (*n_freq)++;
    } else if (5 == n_read) {
      /* Only noise parameters contain five entries per line */
      break;
    }
  }
  fclose(fp);

  /* Allocate memory */
  *freq = realloc(*freq, (*n_freq) * sizeof((*freq)[0]));
  *data = realloc(*data, (*n_freq) * n_params * sizeof((*data)[0]));

  /* Parse acutal data */
  fp = fopen(filename, "r");
  while (fgets(line_buff, LINE_BUFF_LENGTH, fp)) {
    /* Ignore line and tailing comments */
    if (NULL != (comment_char = strchr(line_buff, '!'))) {
      line_buff[comment_char - line_buff] = '\0';
    }

    /* Ignore empty lines */
    if (0 == strlen(line_buff)) {
      continue;
    }

    /* Parse data line */
    n_read = sscanf(
      line_buff,
      "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
      &f,
      &a[0],
      &b[0],
      &a[1],
      &b[1],
      &a[2],
      &b[2],
      &a[3],
      &b[3],
      &a[4],
      &b[4],
      &a[5],
      &b[5],
      &a[6],
      &b[6],
      &a[7],
      &b[7]);
    if (5 == n_read) { /* Only noise parameters contain five entries per line */
      break;
    }
    /* TODO: assemble data into arrays */
  }

  fclose(fp);
}
