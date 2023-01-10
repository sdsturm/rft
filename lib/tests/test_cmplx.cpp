#include <boost/test/unit_test.hpp>

#include "../cmplx.h"

#include <math.h>

BOOST_AUTO_TEST_SUITE(test_cmplx)

BOOST_AUTO_TEST_CASE(set_re_im)
{
  cmplx z;
  const double re = 1.234;
  const double im = 2.345;
  z = cmplx_set_re_im(re, im);
  BOOST_CHECK_CLOSE(z.a, re, 1e-30);
  BOOST_CHECK_CLOSE(z.b, im, 1e-30);
}

BOOST_AUTO_TEST_CASE(abs_ang)
{
  cmplx z;
  z = cmplx_set_abs_ang(1.0, M_PI / 4.0);
  BOOST_CHECK_CLOSE(z.a, sqrt(2.0) / 2.0, 1e-8);
  BOOST_CHECK_CLOSE(z.b, sqrt(2.0) / 2.0, 1e-8);
}

BOOST_AUTO_TEST_CASE(abs)
{
  cmplx z;
  double ans;
  z = cmplx_set_re_im(1.0, 1.0);
  ans = cmplx_abs(z);
  BOOST_CHECK_CLOSE(ans, sqrt(2.0), 1e-15);
}

BOOST_AUTO_TEST_CASE(arg)
{
  cmplx z;
  double ans;
  z = cmplx_set_re_im(-1.0, 1.0);
  ans = cmplx_arg(z);
  BOOST_CHECK_CLOSE(ans, 3.0 / 4.0 * M_PI, 1e-20);
}

BOOST_AUTO_TEST_CASE(add)
{
  cmplx z_1, z_2, z_3;
  z_1 = cmplx_set_re_im(1.0, 2.0);
  z_2 = cmplx_set_re_im(3.0, 4.0);
  z_3 = cmplx_add(z_1, z_2);
  BOOST_CHECK_CLOSE(z_3.a, 4.0, 1e-20);
  BOOST_CHECK_CLOSE(z_3.b, 6.0, 1e-20);
}

BOOST_AUTO_TEST_CASE(sub)
{
  cmplx z_1, z_2, z_3;
  z_1 = cmplx_set_re_im(1.0, 2.0);
  z_2 = cmplx_set_re_im(3.0, 4.0);
  z_3 = cmplx_sub(z_1, z_2);
  BOOST_CHECK_CLOSE(z_3.a, -2.0, 1e-20);
  BOOST_CHECK_CLOSE(z_3.b, -2.0, 1e-20);
}

BOOST_AUTO_TEST_CASE(mul)
{
  cmplx z_1, z_2, z_3;
  double mag_1, mag_2, mag_ans, arg_1, arg_2, arg_ans;
  mag_1 = 1.234;
  mag_2 = 2.345;
  arg_1 = 0.567;
  arg_2 = 1.234;
  z_1 = cmplx_set_abs_ang(mag_1, arg_1);
  z_2 = cmplx_set_abs_ang(mag_2, arg_2);
  z_3 = cmplx_mul(z_1, z_2);
  BOOST_CHECK_CLOSE(cmplx_abs(z_3), mag_1 * mag_2, 1e-12);
  BOOST_CHECK_CLOSE(cmplx_arg(z_3), arg_1 + arg_2, 1e-12);
}

BOOST_AUTO_TEST_CASE(div)
{
  cmplx z_1, z_2, z_3;
  double mag_1, mag_2, mag_ans, arg_1, arg_2, arg_ans;
  mag_1 = 1.234;
  mag_2 = 2.345;
  arg_1 = 0.567;
  arg_2 = 1.234;
  z_1 = cmplx_set_abs_ang(mag_1, arg_1);
  z_2 = cmplx_set_abs_ang(mag_2, arg_2);
  z_3 = cmplx_div(z_1, z_2);
  BOOST_CHECK_CLOSE(cmplx_abs(z_3), mag_1 / mag_2, 1e-12);
  BOOST_CHECK_CLOSE(cmplx_arg(z_3), arg_1 - arg_2, 1e-12);
}

BOOST_AUTO_TEST_CASE(sqrt)
{
  cmplx arg, ans;
  arg = cmplx_set_re_im(-1.0, 0.0);
  ans = cmplx_sqrt(arg);

  BOOST_CHECK_LE(cmplx_real(ans), 1e-50);
  BOOST_CHECK_CLOSE(cmplx_imag(ans), 1.0, 1e-20);
}

BOOST_AUTO_TEST_CASE(exp)
{
  cmplx arg, ans;

  arg = cmplx_set_re_im(0.0, M_PI);
  ans = cmplx_exp(arg);
  BOOST_CHECK_CLOSE(cmplx_real(ans), -1.0, 1e-20);
  BOOST_CHECK_LT(cmplx_imag(ans), 1e-15);

  arg = cmplx_set_re_im(0.0, M_PI / 2.0);
  ans = cmplx_exp(arg);
  BOOST_CHECK_LT(cmplx_real(ans), 1e-15);
  BOOST_CHECK_CLOSE(cmplx_imag(ans), 1.0, 1e-20);
}

BOOST_AUTO_TEST_CASE(log)
{
  cmplx arg, ans;
  arg.a = 0.0;
  arg.b = 1.0;
  ans = cmplx_log(arg);
  BOOST_CHECK_LT(cmplx_real(ans), 1e-15);
  BOOST_CHECK_CLOSE(cmplx_imag(ans), M_PI / 2.0, 1e-20);
}

BOOST_AUTO_TEST_SUITE_END()
