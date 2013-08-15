/**
 * \file test_primitives.cpp
 * Primitives file for the test suit
 */

#include <boost/test/unit_test.hpp>
#include <memory>

#include "../IRT/primitives.h"

using namespace IRT;

BOOST_AUTO_TEST_SUITE( irt_primitives_suite )

BOOST_AUTO_TEST_CASE( test_IRT_primitive_bb )
{
  Vector3df v0 = Vector3df::Zero();
  v0 << 5, -5, 5;
  Vector3df v1 = Vector3df::Zero();
  v1 << 5, 5, 5;
  Vector3df v2 = Vector3df::Zero();
  v2 << -5, -5, -5;
  std::unique_ptr<Triangle> triangle(new Triangle(v0, v1, v2));

  BoundingBox bb = triangle->getBoundingBox();

  BOOST_CHECK( (bb.corner1 == Vector3df::Constant(-5.)));
  BOOST_CHECK( (bb.corner2 == Vector3df::Constant(5.)));
}

BOOST_AUTO_TEST_SUITE_END()
