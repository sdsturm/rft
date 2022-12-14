#ifndef RFT_SPARAMETERS_H
#define RFT_SPARAMETERS_H

#include "nwparams.h"

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct
{
  double* z_ref;
  nwparams p;
} sparams;

void sparams_init_empty(sparams *s, const int n_ports, const int n_freq);

void sparams_init_from_touchstone(sparams *s, const char* filename);

#ifdef __cplusplus
}
#endif

#endif /* RFT_SPARAMETERS_H */
