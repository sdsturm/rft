#ifndef RFT_CMPLX_H
#define RFT_CMPLX_H

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct
{
  double a;
  double b;
} cmplx;

cmplx cmplx_set_re_im(const double real, const double imag);

cmplx cmplx_set_abs_ang(const double mag, const double arg);

cmplx cmplx_imag_unit();

double cmplx_real(const cmplx z);

double cmplx_imag(const cmplx z);

double cmplx_abs (const cmplx z);

double cmplx_arg (const cmplx z);

cmplx cmplx_add (const cmplx z1, const cmplx z2);

cmplx cmplx_sub (const cmplx z1, const cmplx z2);

cmplx cmplx_mul (const cmplx z1, const cmplx z2);

cmplx cmplx_div (const cmplx z1, const cmplx z2);

cmplx cmplx_sqrt (const cmplx z);

cmplx cmplx_exp (const cmplx z);

#ifdef __cplusplus
}
#endif

#endif /* RFT_CMPLX_H */
