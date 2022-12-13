#ifndef RFT_SPARAMETERS_H
#define RFT_SPARAMETERS_H

#include "cmplx.h"

#ifdef __cplusplus
extern "C" {
#endif 

struct sparameters
{
  int n_ports;
  int n_freq;
  double* z_ref;
  double* freq;
  cmplx* data;
};

#ifdef __cplusplus
}
#endif

#endif /* RFT_SPARAMETERS_H */
