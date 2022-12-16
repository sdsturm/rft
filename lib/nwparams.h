#ifndef RFT_NWPARAMS_H
#define RFT_NWPARAMS_H

#include "cmplx.h"

#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct
{
  int n_ports;
  int n_freq;
  double* freq;
  cmplx* data;
} nwparams;

int nwparams_get_index(const nwparams *p, const int f, const int m, const int n);

void nwparams_init_empty(nwparams *p, const int n_ports, const int n_freq);

void nwparams_init_from_tochstone(nwparams *p, const char* filename);

cmplx nwparams_get_p_fmn(const nwparams *p, const int f, const int m, const int n);

void nwparams_get_p_mn(const nwparams *p, cmplx* p_mn, const int m, const int n);

void nwparams_print_touchstone(FILE* stream, const nwparams *p, const char* format);

void nwparams_free(nwparams *p);

#ifdef __cplusplus
}
#endif

#endif /* RFT_NWPARAMS_H */
