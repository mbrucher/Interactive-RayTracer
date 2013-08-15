/**
 * \file test_light.cpp
 * Light file for the test suit
 */

#include <boost/test/unit_test.hpp>

#include "../IRT/light.h"

using namespace IRT;

BOOST_AUTO_TEST_SUITE( irt_light_suite )

BOOST_AUTO_TEST_CASE( test_IRT_Light_color )
{
  Light* light = new IRT::Light(Vector3df::Zero(), Vector3df::Constant(1.));

  BOOST_CHECK( (light->computeColor(Ray(Vector3df::Zero(), Vector3df::Constant(1.)), 1.) == Vector3df::Constant(1.)) );
  BOOST_CHECK( (light->computeColor(Ray(Vector3df::Zero(), Vector3df::Constant(1.)), 2.) == Vector3df::Constant(.25)) );

  delete light;
}

BOOST_AUTO_TEST_CASE( test_IRT_Light_center )
{
  Light* light = new IRT::Light(Vector3df::Zero(), Vector3df::Constant(1.));

  BOOST_CHECK( (light->getCenter() == Vector3df::Zero()) );
  BOOST_CHECK( (light->getCenter() == Vector3df::Zero()) );

  delete light;
}

BOOST_AUTO_TEST_SUITE_END()
