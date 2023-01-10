#include <boost/test/unit_test.hpp>

#include "../cmplx.h"

BOOST_AUTO_TEST_SUITE(test_cmplx)

BOOST_AUTO_TEST_CASE(real_imag)
{
  /* TODO*/
  BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(abs_ang)
{
  /* TODO*/
  BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(abs)
{
  /* TODO*/
  BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(arg)
{
  /* TODO*/
  BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(add)
{
  cmplx z_1, z_2, z_3;
  z_1 = cmplx_real_imag(1.0, 2.0);
  z_2 = cmplx_real_imag(3.0, 4.0);
  z_3 = cmplx_add(z_1, z_2);
  BOOST_CHECK_CLOSE(z_3.a, 4.0, 1e-20);
  BOOST_CHECK_CLOSE(z_3.b, 6.0, 1e-20);
}

BOOST_AUTO_TEST_CASE(sub)
{
  cmplx z_1, z_2, z_3;
  z_1 = cmplx_real_imag(1.0, 2.0);
  z_2 = cmplx_real_imag(3.0, 4.0);
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
  z_1 = cmplx_abs_ang(mag_1, arg_1);
  z_2 = cmplx_abs_ang(mag_2, arg_2);
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
  z_1 = cmplx_abs_ang(mag_1, arg_1);
  z_2 = cmplx_abs_ang(mag_2, arg_2);
  z_3 = cmplx_div(z_1, z_2);
  BOOST_CHECK_CLOSE(cmplx_abs(z_3), mag_1 / mag_2, 1e-12);
  BOOST_CHECK_CLOSE(cmplx_arg(z_3), arg_1 - arg_2, 1e-12);
}

BOOST_AUTO_TEST_CASE(exp)
{
  /* TODO*/
  BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(sqrt)
{
  cmplx arg, ans;
  arg = cmplx_real_imag(0.0, 1.0);
  ans = cmplx_sqrt(arg);

  /* TODO*/
  BOOST_CHECK(false);
}

BOOST_AUTO_TEST_SUITE_END()
