#ifndef RFT_CMPLX_H
#define RFT_CMPLX_H

typedef struct
{
  double a;
  double b;
} cmplx;

cmplx cmplx_real_imag(const double real, const double imag);

cmplx cmplx_mag_arg(const double mag, const double arg);

cmplx cmplx_imag_unit();

double cmplx_abs (const cmplx z);

double cmplx_arg (const cmplx z);

cmplx cmplx_add (const cmplx z1, const cmplx z2);

cmplx cmplx_sub (const cmplx z1, const cmplx z2);

cmplx cmplx_mul (const cmplx z1, const cmplx z2);

cmplx cmplx_div (const cmplx z1, const cmplx z2);

cmplx cmplx_sqrt (const cmplx z);

cmplx cmplx_exp (const cmplx z);

#endif /* RFT_CMPLX_H */
