/**
 * \file test_simple_scene.cpp
 * Simple scene file for the test suit
 */

#include <limits>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include "../IRT/simple_scene.h"
#include "../IRT/primitives.h"
#include "../IRT/light.h"

#include "../IRT/build_kdtree.h"

using namespace IRT;

BOOST_AUTO_TEST_SUITE( irt_simplescene_suite )

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_addPrimitive )
{
  Primitive* primitive = new Sphere(Vector3df::Zero(), 3.f);
  SimpleScene* scene = new SimpleScene;

  BOOST_CHECK_NO_THROW(scene->addPrimitive(primitive));
  BOOST_CHECK_THROW(scene->addPrimitive(primitive), std::out_of_range);

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getPrimitive )
{
  Primitive* primitive = new Sphere(Vector3df::Zero(), 3.f);
  SimpleScene* scene = new SimpleScene;

  unsigned long index = 0;;
  BOOST_CHECK_NO_THROW(index = scene->addPrimitive(primitive));

  Primitive* result = scene->getPrimitive(index);

  BOOST_REQUIRE_EQUAL(primitive, result);

  result = scene->getPrimitive(index);

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getPrimitiveIndex )
{
  Primitive* primitive = new Sphere(Vector3df::Zero(), 3.f);
  SimpleScene* scene = new SimpleScene;

  unsigned long index = 0;
  BOOST_REQUIRE_NO_THROW(index = scene->addPrimitive(primitive));
  BOOST_REQUIRE_EQUAL(index, scene->getPrimitiveIndex(primitive));

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getBoundingBox )
{
  Primitive* primitive = new Sphere(Vector3df::Zero(), 3.f);
  SimpleScene* scene = new SimpleScene;

  BOOST_CHECK_NO_THROW(scene->addPrimitive(primitive));

  BoundingBox bb;
  bb.corner1 = Point3df::Constant(-3);
  bb.corner2 = Point3df::Constant(3);
  BoundingBox scene_bb = scene->getBoundingBox();

  BOOST_CHECK((bb.corner1 == scene_bb.corner1));
  BOOST_CHECK((bb.corner2 == scene_bb.corner2));

  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);

  primitive = new Sphere(vector1, 2.f);
  BOOST_CHECK_NO_THROW(scene->addPrimitive(primitive));

  scene_bb = scene->getBoundingBox();

  bb.corner2(0) = 5;
  bb.corner2(2) = 6;

  BOOST_CHECK((bb.corner1 == scene_bb.corner1));
  BOOST_CHECK((bb.corner2 == scene_bb.corner2));
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_computeBoundingBox )
{
  Primitive* primitive = new Sphere(Vector3df::Zero(), 3.f);
  SimpleScene* scene = new SimpleScene;

  BOOST_CHECK_NO_THROW(scene->addPrimitive(primitive));

  BoundingBox bb;
  bb.corner1 = Point3df::Constant(-3);
  bb.corner2 = Point3df::Constant(3);
  scene->computeBoundingBox();
  BoundingBox scene_bb = scene->getBoundingBox();

  BOOST_CHECK((bb.corner1 == scene_bb.corner1));
  BOOST_CHECK((bb.corner2 == scene_bb.corner2));

  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);

  primitive = new Sphere(vector1, 2.f);
  BOOST_CHECK_NO_THROW(scene->addPrimitive(primitive));

  scene->computeBoundingBox();
  scene_bb = scene->getBoundingBox();

  bb.corner2(0) = 5;
  bb.corner2(2) = 6;

  BOOST_CHECK((bb.corner1 == scene_bb.corner1));
  BOOST_CHECK((bb.corner2 == scene_bb.corner2));
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_removePrimitive )
{
  Primitive* primitive = new Sphere(Vector3df::Zero(), 3.f);
  SimpleScene* scene = new SimpleScene;

  unsigned long index = 0;
  BOOST_REQUIRE_NO_THROW(index = scene->addPrimitive(primitive));

  Primitive* result = scene->removePrimitive(index);

  BOOST_CHECK(primitive == result);
  Primitive* primitive2 = new Sphere(Vector3df::Zero(), 3.f);
  scene->addPrimitive(primitive2);
  BOOST_REQUIRE_NE(scene->getPrimitive(index), primitive);

  delete primitive;
  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_addLight )
{
  Light* light = new Light(Vector3df::Zero(), Vector3df::Constant(1.f));
  SimpleScene* scene = new SimpleScene;

  BOOST_CHECK_NO_THROW(scene->addLight(light));
  BOOST_CHECK_THROW(scene->addLight(light), std::out_of_range);

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getLight )
{
  Light* light = new Light(Vector3df::Zero(), Vector3df::Constant(1.f));
  SimpleScene* scene = new SimpleScene;

  unsigned long index = 0;
  BOOST_REQUIRE_NO_THROW(index = scene->addLight(light));

  Light* result = scene->getLight(index);

  BOOST_REQUIRE_EQUAL(light, result);

  result = scene->getLight(index);

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getLightIndex )
{
  Light* light = new Light(Vector3df::Zero(), Vector3df::Constant(1.f));
  SimpleScene* scene = new SimpleScene;

  unsigned long index = 0;
  BOOST_REQUIRE_NO_THROW(index = scene->addLight(light));
  BOOST_REQUIRE_EQUAL(index, scene->getLightIndex(light));

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_removeLight )
{
  Light* light = new Light(Vector3df::Zero(), Vector3df::Constant(1.f));
  SimpleScene* scene = new SimpleScene;

  unsigned long index = 0;
  BOOST_REQUIRE_NO_THROW(index = scene->addLight(light));

  Light* result = scene->removeLight(index);

  BOOST_REQUIRE_EQUAL(light, result);
  Light* light2 = new Light(Vector3df::Zero(), Vector3df::Constant(1.f));
  scene->addLight(light2);
  BOOST_REQUIRE_NE(scene->getLight(index), light);

  delete result;
  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getFirstCollision )
{
  Primitive* primitive = new Sphere(Vector3df::Zero(), 3.f);
  SimpleScene* scene = new SimpleScene;

  unsigned long index = 0;
  BOOST_CHECK_NO_THROW(index = scene->addPrimitive(primitive));
  BuildKDTree::automatic_build(scene);

  float dist = 0;
  float tnear = 0; float tfar = std::numeric_limits<float>::max();
  BOOST_CHECK_EQUAL(primitive, scene->getFirstCollision(Ray(Vector3df::Constant(-5.), Vector3df::Constant(1.)), dist, tnear, tfar));
  BOOST_CHECK_GT(dist, 0);
  BOOST_CHECK_EQUAL(scene->getFirstCollision(Ray(Vector3df::Constant(-5.), Vector3df::Constant(-1.)), dist, tnear, tfar), static_cast<Primitive*>(nullptr));

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_testCollision )
{
  Primitive* primitive = new Sphere(Vector3df::Zero(), 3.f);
  SimpleScene* scene = new SimpleScene;
  IRT::BuildKDTree::automatic_build(scene);

  unsigned long index = 0;
  BOOST_CHECK_NO_THROW(index = scene->addPrimitive(primitive));

  BOOST_CHECK(scene->testCollision(Ray(Vector3df::Constant(-5.), Vector3df::Constant(1.)), std::numeric_limits<float>::max()));
  BOOST_CHECK(!scene->testCollision(Ray(Vector3df::Constant(-5.), Vector3df::Constant(-1.)), std::numeric_limits<float>::max()));

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_computeColor )
{
  Primitive* primitive = new Sphere(Vector3df::Zero(), 3.f);
  primitive->setDiffuse(1);
  Light* light = new Light(Vector3df::Constant(5.), Vector3df::Constant(1.));
  SimpleScene* scene = new SimpleScene;
  IRT::BuildKDTree::automatic_build(scene);

  unsigned long index = 0;
  BOOST_CHECK_NO_THROW(index = scene->addLight(light));
  BOOST_CHECK_NO_THROW(index = scene->addPrimitive(primitive));

  MaterialPoint material;
  material.normal = Normal3df::Constant(1.);
  material.normal.normalize();

  BOOST_CHECK((scene->computeColor(Vector3df::Constant(4.), material, primitive) != Normal3df::Constant(0.f)));
  BOOST_CHECK((scene->computeColor(Vector3df::Constant(-4.), material, primitive) == Normal3df::Constant(0.f)));

  delete scene;
}

BOOST_AUTO_TEST_SUITE_END()
