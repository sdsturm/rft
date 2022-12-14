#ifndef RFT_SPARAMETERS_H
#define RFT_SPARAMETERS_H

#include "cmplx.h"

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct
{
  int n_ports;
  int n_freq;
  double* z_ref;
  double* freq;
  cmplx* data;
} sparams;

sparams sparams_init_from_tochstone(const char* filename);

void sparams_set_n_ports(sparams *s, const int n_ports);

void sparams_set_freq(sparams *s, const double* freq, const int n_freq);

void sparams_set_s_mn(sparams *s, const cmplx* s_mn, const int m, const int n);

void sparams_free(sparams *s);

#ifdef __cplusplus
}
#endif

#endif /* RFT_SPARAMETERS_H */
