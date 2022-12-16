#include "nwparams.h"

#include "touchstone.h"

#include <stdlib.h>

int nwparams_get_index(const nwparams *p, const int f, const int m, const int n)
{
    /* Matrix in column major format; consecutive frequency sampling posize_ts */
    int index = f * p->n_freq + n * p->n_ports + m;
    return index;
}

void nwparams_init_empty(nwparams *p, const int n_ports, const int n_freq)
{
  p->n_ports = n_ports;
  p->n_freq = n_freq;
  p->freq = realloc(p->freq, n_freq * sizeof(p->freq[0]));
  p->data = realloc(p->data, n_ports * n_freq * sizeof(p->data[0]));
}

void nwparams_init_from_tochstone(nwparams *p, const char* filename)
{
    double *r_ref = NULL;
    parse_touchstone(filename, &p->n_ports, &p->n_freq, r_ref, &p->freq, &p->data);
    /* TODO */
}

cmplx nwparams_get_p_fmn(const nwparams *p, const int f, const int m, const int n)
{
    return p->data[nwparams_get_index(p, f, m, n)];
}

void nwparams_get_p_mn(const nwparams *p, cmplx* p_mn, const int m, const int n)
{
    int f;
    p_mn = realloc(p_mn, p->n_freq * sizeof(p_mn[0]));
    for (f = 0; f < p->n_freq; ++f) {
        p_mn[f] = nwparams_get_p_fmn(p, f, m, n);
    }
}

void nwparams_free(nwparams *p)
{
    free(p->freq);
    free(p->data);
}
