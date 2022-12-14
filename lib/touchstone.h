#ifndef RFT_TOUCHSTONE_H
#define RFT_TOUCHSTONE_H

#include "cmplx.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif 

void
parse_touchstone(const char* filename,
                 int* n_ports,
                 int* n_freq,
                 double* r_ref,
                 double** freq,
                 cmplx** data);

#ifdef __cplusplus
}
#endif

#endif /* RFT_TOUCHSTONE_H */
