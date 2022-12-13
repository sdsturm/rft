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
