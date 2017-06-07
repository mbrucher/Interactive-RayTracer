/**
 * \file test_primitives.cpp
 * Primitives file for the test suit
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include "../IRT/primitives.h"

using namespace IRT;

BOOST_AUTO_TEST_SUITE( irt_primitives_suite )

BOOST_AUTO_TEST_CASE( test_IRT_primitive_bb )
{
  Primitive* primitive = new IRT::Sphere(Vector3df::Zero(), 5);

  BoundingBox bb = primitive->getBoundingBox();

  BOOST_CHECK( (bb.corner1 == Vector3df::Constant(-5.)));
  BOOST_CHECK( (bb.corner2 == Vector3df::Constant(5.)));

  delete primitive;
}

BOOST_AUTO_TEST_SUITE_END()
