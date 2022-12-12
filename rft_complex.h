#ifndef RFT_RFT_COMPLEX_H
#define RFT_RFT_COMPLEX_H

typedef struct
{
  double a;
  double b;
} rft_complex;

rft_complex rft_complex_real_imag(const double real, const double imag);

rft_complex rft_complex_mag_arg(const double mag, const double arg);

rft_complex rft_complex_imag_unit();

double rft_complex_abs (const rft_complex z);

double rft_complex_arg (const rft_complex z);

rft_complex rft_complex_add (const rft_complex z1, const rft_complex z2);

rft_complex rft_complex_sub (const rft_complex z1, const rft_complex z2);

rft_complex rft_complex_mul (const rft_complex z1, const rft_complex z2);

rft_complex rft_complex_div (const rft_complex z1, const rft_complex z2);

#endif /* RFT_RFT_COMPLEX_H */
