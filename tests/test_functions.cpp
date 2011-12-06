/**
 * \file test_functions.cpp
 * Functions file for the test suit
 */

#include <iostream>
#include <boost/test/unit_test.hpp>

#include "../tools/matrix.h"

using namespace IRT::Tools;
typedef Vector<float, 3> Vector3df;

BOOST_AUTO_TEST_SUITE( irt_tools_suite )

BOOST_AUTO_TEST_CASE( test_IRT_Tools_all )
{
  bool elements1[] = {true, true, true};
  Vector3df::ComparisonResult vector1(elements1);
  bool elements2[] = {true, false, true};
  Vector3df::ComparisonResult vector2(elements2);

  BOOST_CHECK(all(vector1));
  BOOST_CHECK(!all(vector2));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_any )
{
  bool elements1[] = {true, false, true};
  Vector3df::ComparisonResult vector1(elements1);
  bool elements2[] = {false, false, false};
  Vector3df::ComparisonResult vector2(elements2);

  BOOST_CHECK(any(vector1));
  BOOST_CHECK(!any(vector2));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_equal_b_VV )
{
  bool elements1[] = {true, true, true};
  Vector3df::ComparisonResult vector1(elements1);
  bool elements2[] = {true, false, true};
  Vector3df::ComparisonResult vector2(elements2);

  BOOST_CHECK(all(vector1 == vector1));
  BOOST_CHECK(!all(vector1 == vector2));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_equal_f_VV )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements2[] = {1.f, 2.f, 3.f};
  Vector3df vector2(elements2);

  BOOST_CHECK(all(vector1 == vector1));
  BOOST_CHECK(!all(vector1 == vector2));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_different_b_VV )
{
  bool elements1[] = {true, true, true};
  Vector3df::ComparisonResult vector1(elements1);
  bool elements2[] = {true, false, true};
  Vector3df::ComparisonResult vector2(elements2);

  BOOST_CHECK(any(vector1 != vector2));
  BOOST_CHECK(!all(vector1 != vector1));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_different_f_VV )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements2[] = {1.f, 2.f, 3.f};
  Vector3df vector2(elements2);

  BOOST_CHECK(any(vector1 != vector2));
  BOOST_CHECK(!all(vector1 != vector1));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_addition_VV )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements2[] = {1.f, 2.f, 3.f};
  Vector3df vector2(elements2);
  float elements3[] = {4.f, 2.f, 7.f};
  Vector3df vector3(elements3);

  BOOST_CHECK(all(vector1 + vector2 == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_addition_fV )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements3[] = {4.f, 1.f, 5.f};
  Vector3df vector3(elements3);

  BOOST_CHECK(all(1.f + vector1 == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_addition_Vf )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements3[] = {5.f, 2.f, 6.f};
  Vector3df vector3(elements3);

  BOOST_CHECK(all(vector1 + 2.f == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_addition_assign_VV )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements2[] = {1.f, 2.f, 3.f};
  Vector3df vector2(elements2);
  float elements3[] = {4.f, 2.f, 7.f};
  Vector3df vector3(elements3);

  vector1 += vector2;
  BOOST_CHECK(all(vector1 == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_addition_assign_Vf )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements3[] = {5.f, 2.f, 6.f};
  Vector3df vector3(elements3);

  vector1 += 2.f;
  BOOST_CHECK(all(vector1 == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_oppose_V )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements2[] = {-3.f, 0.f, -4.f};
  Vector3df vector2(elements2);

  BOOST_CHECK(all(vector1 == - vector2));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_subtraction_VV )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements2[] = {1.f, 2.f, 3.f};
  Vector3df vector2(elements2);
  float elements3[] = {2.f, -2.f, 1.f};
  Vector3df vector3(elements3);

  BOOST_CHECK(all(vector1 - vector2 == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_subtraction_fV )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements3[] = {-2.f, 1.f, -3.f};
  Vector3df vector3(elements3);

  BOOST_CHECK(all(1.f - vector1 == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_subtraction_Vf )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements3[] = {1.f, -2.f, 2.f};
  Vector3df vector3(elements3);

  BOOST_CHECK(all(vector1 - 2.f == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_subtraction_assign_VV )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements2[] = {1.f, 2.f, 3.f};
  Vector3df vector2(elements2);
  float elements3[] = {2.f, -2.f, 1.f};
  Vector3df vector3(elements3);

  vector1 -= vector2;
  BOOST_CHECK(all(vector1 == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_subtraction_assign_Vf )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements3[] = {1.f, -2.f, 2.f};
  Vector3df vector3(elements3);

  vector1 -= 2.f;
  BOOST_CHECK(all(vector1 == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_multiplication_fV )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements3[] = {3.f, 0.f, 4.f};
  Vector3df vector3(elements3);

  BOOST_CHECK(all(1.f * vector1 == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_multiplication_Vf )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements3[] = {6.f, 0.f, 8.f};
  Vector3df vector3(elements3);

  BOOST_CHECK(all(vector1 * 2.f == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_multiplication_VV )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements2[] = {6.f, 0.f, 8.f};
  Vector3df vector2(elements2);

  BOOST_CHECK(vector1 * vector2 == 50.f);
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_multiplication_assign_Vf )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements3[] = {6.f, 0.f, 8.f};
  Vector3df vector3(elements3);

  vector1 *= 2.f;
  BOOST_CHECK(all(vector1 == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_mult_VV )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements2[] = {6.f, 1.f, 8.f};
  Vector3df vector2(elements2);
  float elements3[] = {18.f, 0.f, 32.f};
  Vector3df vector3(elements3);

  BOOST_CHECK(all(mult(vector1, vector2) == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_cross_VV )
{
  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements2[] = {6.f, 1.f, 8.f};
  Vector3df vector2(elements2);
  float elements3[] = {-4.f, 0.f, 3.f};
  Vector3df vector3(elements3);

  BOOST_CHECK(all((vector1 ^ vector2) == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_min )
{
  float elements1[] = {7.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements2[] = {6.f, 1.f, 8.f};
  Vector3df vector2(elements2);
  float elements3[] = {6.f, 0.f, 4.f};
  Vector3df vector3(elements3);

  BOOST_CHECK(all(min(vector1,vector2) == vector3));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_max )
{
  float elements1[] = {7.f, 0.f, 4.f};
  Vector3df vector1(elements1);
  float elements2[] = {6.f, 1.f, 8.f};
  Vector3df vector2(elements2);
  float elements3[] = {7.f, 1.f, 8.f};
  Vector3df vector3(elements3);

  BOOST_CHECK(all(max(vector1,vector2) == vector3));
}

BOOST_AUTO_TEST_SUITE_END()
