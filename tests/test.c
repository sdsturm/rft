#include "../config.h"
#include "../touchstone.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char const* argv[])
{
  const char* filename = argv[1];

  int n_ports;
  int n_freq;
  double r_ref;
  double* freq;
  rft_complex* data;

  parse_touchstone(filename, &n_ports, &n_freq, &r_ref, &freq, &data);

  return EXIT_SUCCESS;
}
