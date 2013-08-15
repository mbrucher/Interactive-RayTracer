/**
 * \file test_simple_scene.cpp
 * Simple scene file for the test suit
 */

#include <limits>
#include <boost/test/unit_test.hpp>

#include "../IRT/simple_scene.h"
#include "../IRT/primitives.h"
#include "../IRT/light.h"

#include "../IRT/build_kdtree.h"

using namespace IRT;

BOOST_AUTO_TEST_SUITE( irt_simplescene_suite )

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_addTriangle )
{
  Vector3df v0 = Vector3df::Zero();
  v0 << 5, -5, 5;
  Vector3df v1 = Vector3df::Zero();
  v1 << 5, 5, 5;
  Vector3df v2 = Vector3df::Zero();
  v2 << -5, -5, -5;
  Triangle* triangle = new Triangle(v0, v1, v2);
  SimpleScene* scene = new SimpleScene;

  BOOST_CHECK_NO_THROW(scene->addTriangle(triangle));
  BOOST_CHECK_THROW(scene->addTriangle(triangle), std::out_of_range);

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_addPrimitive )
{
  Primitive* primitive = new Sphere(Vector3df::Zero(), 3.f);
  SimpleScene* scene = new SimpleScene;

  BOOST_CHECK_NO_THROW(primitive->addToScene(scene));
  BOOST_CHECK_THROW(primitive->addToScene(scene), std::out_of_range);

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getTriangle )
{
  Vector3df v0 = Vector3df::Zero();
  v0 << 5, -5, 5;
  Vector3df v1 = Vector3df::Zero();
  v1 << 5, 5, 5;
  Vector3df v2 = Vector3df::Zero();
  v2 << -5, -5, -5;
  Triangle* triangle = new Triangle(v0, v1, v2);
  SimpleScene* scene = new SimpleScene;

  unsigned long index = 0;;
  BOOST_CHECK_NO_THROW(index = scene->addTriangle(triangle));

  Triangle* result = scene->getTriangle(index);

  BOOST_REQUIRE_EQUAL(triangle, result);

  result = scene->getTriangle(index);

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getTriangleIndex )
{
  Vector3df v0 = Vector3df::Zero();
  v0 << 5, -5, 5;
  Vector3df v1 = Vector3df::Zero();
  v1 << 5, 5, 5;
  Vector3df v2 = Vector3df::Zero();
  v2 << -5, -5, -5;
  Triangle* triangle = new Triangle(v0, v1, v2);
  SimpleScene* scene = new SimpleScene;

  unsigned long index = 0;
  BOOST_REQUIRE_NO_THROW(index = scene->addTriangle(triangle));
  BOOST_REQUIRE_EQUAL(index, scene->getTriangleIndex(triangle));

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getBoundingBox )
{
  Primitive* primitive = new Sphere(Vector3df::Zero(), 3.f);
  SimpleScene* scene = new SimpleScene;

  BOOST_CHECK_NO_THROW(primitive->addToScene(scene));

  BoundingBox bb;
  bb.corner1 = Point3df::Constant(-3);
  bb.corner2 = Point3df::Constant(3);
  BoundingBox scene_bb = scene->getBoundingBox();

  BOOST_CHECK((bb.corner1 == scene_bb.corner1));
  BOOST_CHECK((bb.corner2 == scene_bb.corner2));

  float elements1[] = {3.f, 0.f, 4.f};
  Vector3df vector1(elements1);

  primitive = new Sphere(vector1, 2.f);
  BOOST_CHECK_NO_THROW(primitive->addToScene(scene));

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

  BOOST_CHECK_NO_THROW(primitive->addToScene(scene));

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
  BOOST_CHECK_NO_THROW(primitive->addToScene(scene));

  scene->computeBoundingBox();
  scene_bb = scene->getBoundingBox();

  bb.corner2(0) = 5;
  bb.corner2(2) = 6;

  BOOST_CHECK((bb.corner1 == scene_bb.corner1));
  BOOST_CHECK((bb.corner2 == scene_bb.corner2));
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_removeTriangle )
{
  Vector3df v0 = Vector3df::Zero();
  v0 << 5, -5, 5;
  Vector3df v1 = Vector3df::Zero();
  v1 << 5, 5, 5;
  Vector3df v2 = Vector3df::Zero();
  v2 << -5, -5, -5;
  Triangle* triangle = new Triangle(v0, v1, v2);
  SimpleScene* scene = new SimpleScene;

  unsigned long index = 0;
  BOOST_REQUIRE_NO_THROW(index = scene->addTriangle(triangle));

  Triangle* result = scene->removeTriangle(index);

  BOOST_CHECK(triangle == result);
  Triangle* triangle2 = new Triangle(v0, v1, v2);
  scene->addTriangle(triangle2);
  BOOST_REQUIRE_NE(scene->getTriangle(index), triangle);

  delete triangle;
  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_addLight )
{
  Light* light = new Light(Vector3df::Zero(), Vector3df(1.));
  SimpleScene* scene = new SimpleScene;

  BOOST_CHECK_NO_THROW(scene->addLight(light));
  BOOST_CHECK_THROW(scene->addLight(light), std::out_of_range);

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getLight )
{
  Light* light = new Light(Vector3df::Zero(), Vector3df(1.));
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
  Light* light = new Light(Vector3df::Zero(), Vector3df(1.));
  SimpleScene* scene = new SimpleScene;

  unsigned long index = 0;
  BOOST_REQUIRE_NO_THROW(index = scene->addLight(light));
  BOOST_REQUIRE_EQUAL(index, scene->getLightIndex(light));

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_removeLight )
{
  Light* light = new Light(Vector3df::Zero(), Vector3df(1.));
  SimpleScene* scene = new SimpleScene;

  unsigned long index = 0;
  BOOST_REQUIRE_NO_THROW(index = scene->addLight(light));

  Light* result = scene->removeLight(index);

  BOOST_REQUIRE_EQUAL(light, result);
  Light* light2 = new Light(Vector3df::Zero(), Vector3df(1.));
  scene->addLight(light2);
  BOOST_REQUIRE_NE(scene->getLight(index), light);

  delete result;
  delete scene;
}

/*BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_getFirstCollision )
{
  Primitive* primitive = new Sphere(Vector3df::Zero(), 3.f);
  SimpleScene* scene = new SimpleScene;

  BOOST_CHECK_NO_THROW(primitive->addToScene(scene));
  BuildKDTree::automatic_build(scene);

  float dist = 0;
  float tnear = 0; float tfar = std::numeric_limits<float>::max();
  BOOST_CHECK_EQUAL(primitive, scene->getFirstCollision(Ray(Vector3df::Constant(-5.), Vector3df::Constant(1.)), dist, tnear, tfar));
  BOOST_CHECK_GT(dist, 0);
  BOOST_CHECK_EQUAL(scene->getFirstCollision(Ray(Vector3df::Constant(-5.), Vector3df::Constant(-1.)), dist, tnear, tfar), static_cast<Primitive*>(NULL));

  delete scene;
}*/

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_testCollision )
{
  Primitive* primitive = new Sphere(Vector3df(0.), 3.f);
  SimpleScene* scene = new SimpleScene;
  IRT::BuildKDTree::automatic_build(scene);

  BOOST_CHECK_NO_THROW(primitive->addToScene(scene));

  BOOST_CHECK(scene->testCollision(Ray(Vector3df::Constant(-5.), Vector3df::Constant(1.)), std::numeric_limits<float>::max()));
  BOOST_CHECK(!scene->testCollision(Ray(Vector3df::Constant(-5.), Vector3df::Constant(-1.)), std::numeric_limits<float>::max()));

  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_SimpleScene_computeColor )
{
  Vector3df v0 = Vector3df::Zero();
  v0 << 5, -5, 5;
  Vector3df v1 = Vector3df::Zero();
  v1 << 5, 5, 5;
  Vector3df v2 = Vector3df::Zero();
  v2 << -5, -5, -5;
  std::unique_ptr<Triangle> triangle(new Triangle(v0, v1, v2));
  triangle->setDiffuse(1);
  Light* light = new Light(Vector3df::Constant(5.), Vector3df::Constant(1.));
  SimpleScene* scene = new SimpleScene;
  IRT::BuildKDTree::automatic_build(scene);

  unsigned long index = 0;
  BOOST_CHECK_NO_THROW(index = scene->addLight(light));
  BOOST_CHECK_NO_THROW(scene->addTriangle(triangle.get()));

  MaterialPoint material;
  material.normal = Normal3df::Constant(1.);
  material.normal.normalize();

  BOOST_CHECK((scene->computeColor(Vector3df::Constant(4.), material, triangle.get()) != Normal3df::Constant(0.f)));
  BOOST_CHECK((scene->computeColor(Vector3df::Constant(-4.), material, triangle.get()) == Normal3df::Constant(0.f)));

  triangle.release();

  delete scene;
}

BOOST_AUTO_TEST_SUITE_END()
