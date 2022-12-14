#include "sparams.h"

#include <stdlib.h>

void sparams_init_empty(sparams *s, const int n_ports, const int n_freq)
{
    int i;
    s->z_ref = malloc(n_ports * sizeof(s->z_ref[0]));
    for (i = 0; i < n_ports; ++i) {
        s->z_ref[i] = 50.0;
    }
    nwparams_init_empty(&s->p, n_ports, n_freq);
}

void sparams_init_from_touchstone(sparams *s, const char* filename)
{
    /* TODO */
    nwparams_init_from_tochstone(&s->p, filename);
}
