#ifndef RFT_SPARAMETERS_H
#define RFT_SPARAMETERS_H

#include "cmplx.h"

struct sparameters
{
  int n_ports;
  int n_freq;
  double* z_ref;
  double* freq;
  cmplx* data;
};

#endif /* RFT_SPARAMETERS_H */
