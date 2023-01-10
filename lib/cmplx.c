#include "cmplx.h"

#include <math.h>

cmplx
cmplx_set_re_im(const double real, const double imag)
{
  cmplx ans;
  ans.a = real;
  ans.b = imag;
  return ans;
}

cmplx
cmplx_set_abs_ang(const double mag, const double arg)
{
  cmplx ans;
  ans.a = mag * cos(arg);
  ans.b = mag * sin(arg);
  return ans;
}

cmplx
cmplx_imag_unit()
{
  cmplx ans;
  ans.a = 0.0;
  ans.b = 1.0;
  return ans;
}

double
cmplx_real(const cmplx z)
{
  return z.a;
}

double
cmplx_imag(const cmplx z)
{
  return z.b;
}

double
cmplx_abs(const cmplx z)
{
  /* See (5.5.4) in "Numerical Recipes", 3rd edition, 2007 */
  double tmp;
  double ans;
  if (fabs(z.a) >= fabs(z.b)) {
    tmp = z.b / z.a;
    ans = fabs(z.a);
  } else {
    tmp = z.a / z.b;
    ans = fabs(z.b);
  }
  ans *= sqrt(1.0 + tmp * tmp);
  return ans;
}

double
cmplx_arg(const cmplx z)
{
  return atan2(z.b, z.a);
}

cmplx
cmplx_add(const cmplx z1, const cmplx z2)
{
  cmplx ans;
  ans.a = z1.a + z2.a;
  ans.b = z1.b + z2.b;
  return ans;
}

cmplx
cmplx_sub(const cmplx z1, const cmplx z2)
{
  cmplx ans;
  ans.a = z1.a - z2.a;
  ans.b = z1.b - z2.b;
  return ans;
}

cmplx
cmplx_mul(const cmplx z1, const cmplx z2)
{
  /* See (5.5.2) in "Numerical Recipes", 3rd edition, 2007 */
  cmplx ans;
  double ac = z1.a * z2.a;
  double bd = z1.b * z2.b;
  ans.a = ac - bd;
  ans.b = (z1.a + z1.b) * (z2.a + z2.b) - ac - bd;
  return ans;
}

cmplx
cmplx_div(const cmplx z1, const cmplx z2)
{
  /* See (5.5.5) in "Numerical Recipes", 3rd edition, 2007 */
  cmplx ans;
  double den, common;
  if (fabs(z2.a) >= fabs(z2.b)) {
    common = z2.b / z2.a;
    den = z2.a + z2.b * common;
    ans.a = z1.a + z1.b * common;
    ans.b = z1.b - z1.a * common;
  } else {
    common = z2.a / z2.b;
    den = z2.a * common + z2.b;
    ans.a = z1.a * common + z1.b;
    ans.b = z1.b * common - z1.a;
  }
  ans.a /= den;
  ans.b /= den;
  return ans;
}

cmplx
cmplx_sqrt(const cmplx z)
{
  /* See (5.5.6) and (5.5.7) in "Numerical Recipes", 3rd edition, 2007 */
  double w;
  double tmp;
  cmplx ans;

  if ((0.0 == z.a) && (0.0 == z.b)) {
    w = 0.0;
  } else if (fabs(z.a) >= fabs(z.b)) {
    tmp = z.b / z.a;
    w = sqrt(fabs(z.a)) * sqrt((1.0 + sqrt(1.0 + tmp * tmp)) / 2.0);
  } else {
    tmp = z.a / z.b;
    w = sqrt(fabs(z.b)) * sqrt((fabs(tmp) + sqrt(1.0 + tmp * tmp)) / 2.0);
  }

  if (0.0 == w) {
    ans.a = 0.0;
    ans.b = 0.0;
  } else if (z.a >= 0.0) {
    ans.a = w;
    ans.b = z.b / (2.0 * w);
  } else if ((z.a < 0.0) && (z.b >= 0.0)) {
    ans.a = fabs(z.b) / (2.0 * w);
    ans.b = w;
  } else {
    ans.a = fabs(z.b) / (2.0 * w);
    ans.b = -w;
  }

  return ans;
}

cmplx
cmplx_exp(const cmplx z)
{
  /* See (4.45.16) in "NIST Handbook of Mathematical Functions", 2010*/
  cmplx ans;
  double factor = exp(z.a);
  ans.a = factor * cos(z.b);
  ans.b = factor * sin(z.b);
  return ans;
}

cmplx cmplx_log (const cmplx z)
{
  /* See (4.45.15) in "NIST Handbook of Mathematical Functions", 2010*/
  cmplx ans;
  ans.a = log(cmplx_abs(z));
  ans.b = cmplx_arg(z);
  return ans;
}
