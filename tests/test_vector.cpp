/**
 * \file test_vector.cpp
 * Vector file for the test suit
 */

#include <boost/test/unit_test.hpp>

#include "../tools/vector.h"

using namespace IRT::Tools;

BOOST_AUTO_TEST_SUITE( irt_vector_suite )

typedef Vector<float, 3> Vector3df;

BOOST_AUTO_TEST_CASE( test_IRT_Tools_Vector_Vector )
{
  Vector3df vector(0.);

  for(unsigned long i = 0; i < 3; ++i)
    BOOST_CHECK(vector(i) == 0.f);
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_Vector_assignation_element )
{
  Vector3df vector(0.);

  vector(1) = 1.;
  vector(2) = 2.;

  for(unsigned long i = 0; i < 3; ++i)
    BOOST_CHECK(vector(i) == static_cast<float>(i));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_Vector_copy_Vector )
{
  Vector3df vector(0.);

  vector(1) = 1.;
  vector(2) = 2.;

  Vector3df vector_copy(vector);

  for(unsigned long i = 0; i < 3; ++i)
    BOOST_CHECK(vector_copy(i) == static_cast<float>(i));
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_Vector_pointer_Vector )
{
  float elements[] = {2.f, 5.f, 1.f};
  Vector3df vector(elements);

  for(unsigned long i = 0; i < 3; ++i)
    BOOST_CHECK(vector(i) == elements[i]);
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_Vector_assignation_one_float )
{
  Vector3df vector(0.);

  vector = 1.f;

  for(unsigned long i = 0; i < 3; ++i)
    BOOST_CHECK(vector(i) == 1.f);
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_Vector_assignation_Vector )
{
  float elements[] = {2.f, 5.f, 1.f};
  Vector3df vector(elements);
  Vector3df vector_copy(0.f);

  vector_copy = vector;

  for(unsigned long i = 0; i < 3; ++i)
    BOOST_CHECK(vector_copy(i) == elements[i]);
}

BOOST_AUTO_TEST_CASE( test_IRT_Tools_Vector_normalize )
{
  float elements[] = {3.f, 0.f, 4.f};
  Vector3df vector(elements);
  float elements_norm[] = {3.f/5.f, 0.f, 4.f/5.f};
  Vector3df vector_norm(elements_norm);

  vector.normalize();

  for(unsigned long i = 0; i < 3; ++i)
    BOOST_CHECK(vector(i) == vector_norm(i));
}

BOOST_AUTO_TEST_SUITE_END()
