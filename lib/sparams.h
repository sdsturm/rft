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

typedef struct
{
  sparams s_dd;
  sparams s_cc;
  sparams s_cd;
  sparams s_dc;
} sparams_mm;

void sparams_init_empty(sparams *s, const int n_ports, const int n_freq);

void sparams_init_from_touchstone(sparams *s, const char* filename);

void sparams_print_touchstone(FILE* stream, const sparams *p, const char* format);

void sparams_se2mm(const sparams *s_se, sparams_mm *s_mm);

void sparams_mm2se(const sparams_mm *s_mm, sparams *s_se);

#ifdef __cplusplus
}
#endif

#endif /* RFT_SPARAMETERS_H */
