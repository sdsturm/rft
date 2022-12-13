#ifndef RFT_TOUCHSTONE_H
#define RFT_TOUCHSTONE_H

#include "cmplx.h"

void
parse_touchstone(const char* filename,
                 int* n_ports,
                 int* n_freq,
                 double* r_ref,
                 double** freq,
                 cmplx** data);

#endif /* RFT_TOUCHSTONE_H */
