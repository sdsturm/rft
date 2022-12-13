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
  int n_read;
  unsigned int i;
  char unit[3];
  char format_str[2];

  /* Defaults */
  *freq_factor = 1.0e9; /* GHz */
  *r_ref = 50.0;        /* Ohm */
  *format = MA;         /* Magnitude and phase in degrees */

  /* Convert line to lowercase */
  for (i = 0; i < strlen(line); ++i) {
    line[i] = tolower(line[i]);
  }

  /* Parse line */
  n_read = sscanf(line, "# %s %s %s r %lf\n", unit, type, format_str, r_ref);
  if (4 != n_read) {
    fprintf(stderr, "Error reading options line.\n");
    exit(EXIT_FAILURE);
  }

  /* Frequency unit */
  if (0 == strcmp(unit + 1, "hz")) {
    *freq_factor = 1.0;
  } else if (0 == strcmp(unit, "khz")) {
    *freq_factor = 1.0e3;
  } else if (0 == strcmp(unit, "mhz")) {
    *freq_factor = 1.0e6;
  } else if (0 == strcmp(unit, "ghz")) {
    *freq_factor = 1.0e9;
  } else {
    fprintf(stderr, "Invalid frequency unit %s read from options line. ", unit);
    fprintf(stderr, "Using default.\n");
  }

  /* Parameter type */
  if ('s' == *type || 'y' == *type || 'z' == *type || 'h' == *type ||
      'g' == *type) {
    fprintf(stderr, "Invalid network parameter type detected.\n");
    exit(EXIT_FAILURE);
  } else {
    *type = toupper(*type);
  }

  /* Complex number format */
  if (0 == strcmp(format_str, "db")) {
    *format = DB;
  } else if (0 == strcmp(format_str, "ma")) {
    *format = MA;
  } else if (0 == strcmp(format_str, "ri")) {
    *format = RI;
  } else {
    fprintf(stderr, "Invalid complex number format %s detected.\n", format_str);
    exit(EXIT_FAILURE);
  }
}

rft_complex
unformat_complex(const double a,
                 const double b,
                 const enum complex_format format)
{
  rft_complex ret;
  switch (format) {
    case DB:
      ret = rft_complex_mag_arg(pow(10.0, a / 20.0), deg2rad(b));
      break;
    case MA:
      ret = rft_complex_mag_arg(a, deg2rad(b));
      break;
    case RI:
      ret = rft_complex_real_imag(a, b);
      break;
  }
  return ret;
}

void
parse_data_block_s1p(const char* line,
                     const int n_params,
                     const enum complex_format format,
                     int* n_freq,
                     double** freq,
                     rft_complex** data)
{
  rft_complex s11;
  double f, a, b;
  int index;

  /* Parse line */
  if (3 != sscanf(line, "%lf %lf %lf\n", &f, &a, &b)) {
    return;
  }

  /* Process data */
  ++(*n_freq);
  *freq = realloc(*freq, *n_freq * sizeof(*freq[0]));
  index = *n_freq - 1;
  (*freq)[index] = f;
  *data = realloc(*data, n_params * sizeof(*data[0]));
  s11 = unformat_complex(a, b, format);
  (*data)[index] = s11;
}

void
parse_data_block_s2p(const char* line,
                     const int n_params,
                     const enum complex_format format,
                     int* n_freq,
                     double** freq,
                     rft_complex** data)
{
  int i, index;
  double f;
  double a[4];
  double b[4];

  /* Parse line */
  if (9 != sscanf(line,
                  "%lf %lf %lf %lf %lf %lf %lf %lf %lf\n",
                  &f,
                  &a[0],
                  &b[0],
                  &a[1],
                  &b[1],
                  &a[2],
                  &b[2],
                  &a[3],
                  &b[3])) {
    return;
  }

  /* Process data */
  ++(*n_freq);
  *freq = realloc(*freq, *n_freq * sizeof(*freq[0]));
  index = *n_freq - 1;
  (*freq)[index] = f;
  *data = realloc(*data, n_params * sizeof(*data[0]));
  index *= n_params;
  for (i = 0; i < 4; ++i) {
    (*data)[index + i] = unformat_complex(a[i], b[i], format);
  }
}

void
parse_data_block_s3p(const char* line,
                     const int n_params,
                     const enum complex_format format,
                     int* n_freq,
                     double** freq,
                     rft_complex** data)
{
  /* TODO */
}

void
parse_data_block_s4p(const char* line,
                     const int n_params,
                     const enum complex_format format,
                     int* n_freq,
                     double** freq,
                     rft_complex** data)
{
  /* TODO */
}

void
parse_data_block_snp(const char* line,
                     const int n_params,
                     const enum complex_format format,
                     int* n_freq,
                     double** freq,
                     rft_complex** data)
{
  /* TODO */
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
                 rft_complex** data)
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

  /* Counter for frequency sampling points */
  *n_freq = 0;

  /* Get number of ports */
  *n_ports = get_n_ports(filename);
  n_params = (*n_ports) * (*n_ports);

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
    n_read = sscanf(line_buff,
                    "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf "
                    "%lf %lf %lf %lf %lf %lf %lf\n",
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
    if (5 != n_read) { /* Only noise parameters contain five entries per line */
      (*n_freq)++;
    } else {
      break;
      ;
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
    n_read = sscanf(line_buff,
                    "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf "
                    "%lf %lf %lf %lf %lf %lf %lf\n",
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
