#include "rft_complex.h"

#include <math.h>

rft_complex
rft_complex_real_imag(const double real, const double imag)
{
  rft_complex ans;
  ans.a = real;
  ans.b = imag;
  return ans;
}

rft_complex
rft_complex_mag_arg(const double mag, const double arg)
{
  rft_complex ans;
  ans.a = mag * cos(arg);
  ans.b = mag * sin(arg);
  return ans;
}

rft_complex
rft_complex_imag_unit()
{
  rft_complex ans;
  ans.a = 0.0;
  ans.b = 1.0;
  return ans;
}

double rft_complex_abs (const rft_complex z)
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

double rft_complex_arg (const rft_complex z)
{
  return atan2(z.b, z.a);
}

rft_complex rft_complex_add (const rft_complex z1, const rft_complex z2)
{
  rft_complex ans;
  ans.a = z1.a + z2.a;
  ans.b = z1.b + z2.b;
  return ans;
}

rft_complex rft_complex_sub (const rft_complex z1, const rft_complex z2)
{
  rft_complex ans;
  ans.a = z1.a - z2.a;
  ans.b = z1.b - z2.b;
  return ans;
}

rft_complex rft_complex_mul (const rft_complex z1, const rft_complex z2)
{
  rft_complex ans;
  double ac = z1.a * z2.a;
  double bd = z1.b * z2.b;
  ans.a = ac -bd;
  ans.b = (z1.a + z1.b) * (z2.a + z2.b) - ac - bd;
  return ans;
}

rft_complex rft_complex_div (const rft_complex z1, const rft_complex z2)
{
  rft_complex ans;
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

rft_complex rft_complex_sqrt (const rft_complex z)
{
  double w;
  double tmp;
  rft_complex ans;

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

rft_complex rft_complex_exp (const rft_complex z)
{
  rft_complex ans;
  double factor = exp(z.a);
  ans.a = factor * cos(z.b);
  ans.b = factor * sin(z.b);
  return ans;
}
