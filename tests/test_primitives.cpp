/**
 * \file test_primitives.cpp
 * Primitives file for the test suit
 */

#include <boost/test/unit_test.hpp>

#include "../IRT/primitives.h"

using namespace IRT;

BOOST_AUTO_TEST_SUITE( irt_primitives_suite )

BOOST_AUTO_TEST_CASE( test_IRT_primitive_bb )
{
  Primitive* primitive = new IRT::Sphere(Vector3df(0.), 5);

  BoundingBox bb = primitive->getBoundingBox();
  
  BOOST_CHECK( all(bb.corner1 == Vector3df(-5.)));
  BOOST_CHECK( all(bb.corner2 == Vector3df(5.)));

  delete primitive;
}

BOOST_AUTO_TEST_SUITE_END()
