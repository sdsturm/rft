#include "touchstone.h"

#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char const* argv[])
{
  if (2 != argc) {
    fprintf(stderr, "Program expects one argument\n");
    exit(EXIT_FAILURE);
  }

  const char* filename = argv[1];

  int n_ports;
  int n_freq;
  double r_ref;
  double* freq;
  rft_complex* data;

  parse_touchstone(filename, &n_ports, &n_freq, &r_ref, &freq, &data);

  return EXIT_SUCCESS;
}
