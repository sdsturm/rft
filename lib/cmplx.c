#include "cmplx.h"

#include <math.h>

cmplx
cmplx_real_imag(const double real, const double imag)
{
  cmplx ans;
  ans.a = real;
  ans.b = imag;
  return ans;
}

cmplx
cmplx_abs_ang(const double mag, const double arg)
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

double cmplx_abs (const cmplx z)
{
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

double cmplx_arg (const cmplx z)
{
  return atan2(z.b, z.a);
}

cmplx cmplx_add (const cmplx z1, const cmplx z2)
{
  cmplx ans;
  ans.a = z1.a + z2.a;
  ans.b = z1.b + z2.b;
  return ans;
}

cmplx cmplx_sub (const cmplx z1, const cmplx z2)
{
  cmplx ans;
  ans.a = z1.a - z2.a;
  ans.b = z1.b - z2.b;
  return ans;
}

cmplx cmplx_mul (const cmplx z1, const cmplx z2)
{
  cmplx ans;
  double ac = z1.a * z2.a;
  double bd = z1.b * z2.b;
  ans.a = ac -bd;
  ans.b = (z1.a + z1.b) * (z2.a + z2.b) - ac - bd;
  return ans;
}

cmplx cmplx_div (const cmplx z1, const cmplx z2)
{
  cmplx ans;
  double den, common;
  if (fabs(z2.a) >= fabs(z2.b)) {
    common = z2.b / z2.a;
    den = z2.a + z2.b * common;
    ans.a = z1.a + z1.b * common;
    ans.b = z1.b - z1.a * common;
  } else {
    common = z2.a / z2.b;
    den = z1.a * (z1.a / z2.b) + z2.b;
    ans.a = z1.a * common + z1.b;
    ans.b = z1.b * common - z1.a;
  }
  ans.a /= den;
  ans.b /= den;
  return ans;
}

cmplx cmplx_sqrt (const cmplx z)
{
  double w;
  double tmp;
  cmplx ans;

  if ((0.0 == z.a) && (z.a == z.b)) {
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
    ans.b = fabs(z.b) / (2.0 * w);
  } else if ((z.a < 0.0) && (z.b >= 0.0)) {
    ans.a = fabs(z.b) / (2.0 * w);
    ans.b = w;
  } else {
    ans.a = fabs(z.b) / (2.0 * w);
    ans.b = -w;
  }

  return ans;
}

cmplx cmplx_exp (const cmplx z)
{
  cmplx ans;
  double factor = exp(z.a);
  ans.a = factor * cos(z.b);
  ans.b = factor * sin(z.b);
  return ans;
}
