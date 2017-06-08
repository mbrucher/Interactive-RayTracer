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
  auto primitive = std::unique_ptr<Primitive>(new Sphere(Vector3df::Zero(), 3.f));
  SimpleScene* scene = new SimpleScene;

  BOOST_CHECK_NO_THROW(scene->addPrimitive(std::move(primitive)));

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getPrimitive )
{
  auto primitive = std::unique_ptr<Primitive>(new Sphere(Vector3df::Zero(), 3.f));
  SimpleScene* scene = new SimpleScene;
  auto primitive_ = primitive.get();

  unsigned long index = 0;;
  BOOST_CHECK_NO_THROW(index = scene->addPrimitive(std::move(primitive)));

  Primitive* result = scene->getPrimitive(index);

  BOOST_REQUIRE_EQUAL(primitive_, result);

  result = scene->getPrimitive(index);

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getPrimitiveIndex )
{
  auto primitive = std::unique_ptr<Primitive>(new Sphere(Vector3df::Zero(), 3.f));
  SimpleScene* scene = new SimpleScene;
  auto primitive_ = primitive.get();

  unsigned long index = 0;
  BOOST_CHECK_NO_THROW(index = scene->addPrimitive(std::move(primitive)));
  BOOST_REQUIRE_EQUAL(index, scene->getPrimitiveIndex(primitive_));

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getBoundingBox )
{
  auto primitive = std::unique_ptr<Primitive>(new Sphere(Vector3df::Zero(), 3.f));
  SimpleScene* scene = new SimpleScene;

  BOOST_CHECK_NO_THROW(scene->addPrimitive(std::move(primitive)));

  BoundingBox bb;
  bb.corner1 = Point3df::Constant(-3);
  bb.corner2 = Point3df::Constant(3);
  BoundingBox scene_bb = scene->getBoundingBox();

  BOOST_CHECK((bb.corner1 == scene_bb.corner1));
  BOOST_CHECK((bb.corner2 == scene_bb.corner2));

  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);

  primitive = std::unique_ptr<Primitive>(new Sphere(vector1, 2.f));
  BOOST_CHECK_NO_THROW(scene->addPrimitive(std::move(primitive)));

  scene_bb = scene->getBoundingBox();

  bb.corner2(0) = 5;
  bb.corner2(2) = 6;

  BOOST_CHECK((bb.corner1 == scene_bb.corner1));
  BOOST_CHECK((bb.corner2 == scene_bb.corner2));
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_computeBoundingBox )
{
  auto primitive = std::unique_ptr<Primitive>(new Sphere(Vector3df::Zero(), 3.f));
  SimpleScene* scene = new SimpleScene;

  BOOST_CHECK_NO_THROW(scene->addPrimitive(std::move(primitive)));

  BoundingBox bb;
  bb.corner1 = Point3df::Constant(-3);
  bb.corner2 = Point3df::Constant(3);
  scene->computeBoundingBox();
  BoundingBox scene_bb = scene->getBoundingBox();

  BOOST_CHECK((bb.corner1 == scene_bb.corner1));
  BOOST_CHECK((bb.corner2 == scene_bb.corner2));

  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);

  primitive = std::unique_ptr<Primitive>(new Sphere(vector1, 2.f));
  BOOST_CHECK_NO_THROW(scene->addPrimitive(std::move(primitive)));

  scene->computeBoundingBox();
  scene_bb = scene->getBoundingBox();

  bb.corner2(0) = 5;
  bb.corner2(2) = 6;

  BOOST_CHECK((bb.corner1 == scene_bb.corner1));
  BOOST_CHECK((bb.corner2 == scene_bb.corner2));
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_removePrimitive )
{
  auto primitive = std::unique_ptr<Primitive>(new Sphere(Vector3df::Zero(), 3.f));
  SimpleScene* scene = new SimpleScene;
  auto primitive_ = primitive.get();

  unsigned long index = 0;
  BOOST_CHECK_NO_THROW(scene->addPrimitive(std::move(primitive)));

  auto result = scene->removePrimitive(index);

  BOOST_CHECK(primitive_ == result.get());
  auto primitive2 = std::unique_ptr<Primitive>(new Sphere(Vector3df::Zero(), 3.f));
  scene->addPrimitive(std::move(primitive2));
  BOOST_REQUIRE_NE(scene->getPrimitive(index), primitive_);

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_addLight )
{
  auto light = std::unique_ptr<Light>(new Light(Vector3df::Zero(), Vector3df::Constant(1.f)));
  SimpleScene* scene = new SimpleScene;

  BOOST_CHECK_NO_THROW(scene->addLight(std::move(light)));

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getLight )
{
  auto light = std::unique_ptr<Light>(new Light(Vector3df::Zero(), Vector3df::Constant(1.f)));
  SimpleScene* scene = new SimpleScene;
  auto light_ = light.get();

  unsigned long index = 0;
  BOOST_CHECK_NO_THROW(scene->addLight(std::move(light)));

  Light* result = scene->getLight(index);

  BOOST_REQUIRE_EQUAL(light_, result);

  result = scene->getLight(index);

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getLightIndex )
{
  auto light = std::unique_ptr<Light>(new Light(Vector3df::Zero(), Vector3df::Constant(1.f)));
  SimpleScene* scene = new SimpleScene;
  auto light_ = light.get();

  unsigned long index = 0;
  BOOST_CHECK_NO_THROW(scene->addLight(std::move(light)));
  BOOST_REQUIRE_EQUAL(index, scene->getLightIndex(light_));

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_removeLight )
{
  auto light = std::unique_ptr<Light>(new Light(Vector3df::Zero(), Vector3df::Constant(1.f)));
  SimpleScene* scene = new SimpleScene;
  auto light_ = light.get();

  unsigned long index = 0;
  BOOST_CHECK_NO_THROW(scene->addLight(std::move(light)));

  auto result = scene->removeLight(index);

  BOOST_REQUIRE_EQUAL(light_, result.get());
  auto light2 = std::unique_ptr<Light>(new Light(Vector3df::Zero(), Vector3df::Constant(1.f)));
  scene->addLight(std::move(light2));
  BOOST_REQUIRE_NE(scene->getLight(index), light_);

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getFirstCollision )
{
  auto primitive = std::unique_ptr<Primitive>(new Sphere(Vector3df::Zero(), 3.f));
  SimpleScene* scene = new SimpleScene;
  auto primitive_ = primitive.get();

  unsigned long index = 0;
  BOOST_CHECK_NO_THROW(scene->addPrimitive(std::move(primitive)));
  BuildKDTree::automatic_build(scene);

  float dist = 0;
  float tnear = 0; float tfar = std::numeric_limits<float>::max();
  BOOST_CHECK_EQUAL(primitive_, scene->getFirstCollision(Ray(Vector3df::Constant(-5.), Vector3df::Constant(1.)), dist, tnear, tfar));
  BOOST_CHECK_GT(dist, 0);
  BOOST_CHECK_EQUAL(scene->getFirstCollision(Ray(Vector3df::Constant(-5.), Vector3df::Constant(-1.)), dist, tnear, tfar), static_cast<Primitive*>(nullptr));

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_testCollision )
{
  auto primitive = std::unique_ptr<Primitive>(new Sphere(Vector3df::Zero(), 3.f));
  SimpleScene* scene = new SimpleScene;
  IRT::BuildKDTree::automatic_build(scene);

  BOOST_CHECK_NO_THROW(scene->addPrimitive(std::move(primitive)));

  BOOST_CHECK(scene->testCollision(Ray(Vector3df::Constant(-5.), Vector3df::Constant(1.)), std::numeric_limits<float>::max()));
  BOOST_CHECK(!scene->testCollision(Ray(Vector3df::Constant(-5.), Vector3df::Constant(-1.)), std::numeric_limits<float>::max()));

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_computeColor )
{
  auto primitive = std::unique_ptr<Primitive>(new Sphere(Vector3df::Zero(), 3.f));
  primitive->setDiffuse(1);
  auto primitive_ = primitive.get();

  auto light = std::unique_ptr<Light>(new Light(Vector3df::Zero(), Vector3df::Constant(1.f)));
  SimpleScene* scene = new SimpleScene;
  IRT::BuildKDTree::automatic_build(scene);

  BOOST_CHECK_NO_THROW(scene->addLight(std::move(light)));
  BOOST_CHECK_NO_THROW(scene->addPrimitive(std::move(primitive)));

  MaterialPoint material;
  material.normal = Normal3df::Constant(1.);
  material.normal.normalize();

  BOOST_CHECK((scene->computeColor(Vector3df::Constant(4.), material, primitive_) != Normal3df::Constant(0.f)));
  BOOST_CHECK((scene->computeColor(Vector3df::Constant(-4.), material, primitive_) == Normal3df::Constant(0.f)));

  delete scene;
}

BOOST_AUTO_TEST_SUITE_END()
