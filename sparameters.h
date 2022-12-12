#ifndef RFT_SPARAMETERS_H
#define RFT_SPARAMETERS_H

#include "rft_complex.h"

struct sparameters
{
  int n_ports;
  int n_freq;
  double* z_ref;
  double* freq;
  rft_complex* data;
};

#endif /* RFT_SPARAMETERS_H */
