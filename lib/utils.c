#include "utils.h"

#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double
rad2deg(const double arg_rad)
{
  return arg_rad / M_PI * 180.0;
}

double
deg2rad(const double arg_deg)
{
  return arg_deg / 180.0 * M_PI;
}
