/**
 * \file test_light.cpp
 * Light file for the test suit
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>

#include "../IRT/simple_scene.h"
#include "../IRT/primitives.h"
#include "../IRT/raytracer.h"

#include "../IRT/samplers/uniform_sampler.h"

using namespace IRT;

BOOST_AUTO_TEST_SUITE( irt_raytracer_suite )

BOOST_AUTO_TEST_CASE( test_IRT_Raytracer_Raytracer )
{
  Raytracer<UniformSampler<float> >* raytracer = new Raytracer<UniformSampler<float> >(640, 480);

  delete raytracer;
}

BOOST_AUTO_TEST_CASE( test_IRT_Raytracer_setScene )
{
  Raytracer<UniformSampler<float> >* raytracer = new Raytracer<UniformSampler<float> >(640, 480);
  SimpleScene* scene = new SimpleScene;

  raytracer->setScene(scene);

  delete raytracer;
  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_Raytracer_setResolution )
{
  Raytracer<UniformSampler<float> >* raytracer = new Raytracer<UniformSampler<float> >(640, 480);
  SimpleScene* scene = new SimpleScene;

  raytracer->setScene(scene);
  raytracer->setResolution(800, 600);

  delete raytracer;
  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_Raytracer_setSize )
{
  Raytracer<UniformSampler<float> >* raytracer = new Raytracer<UniformSampler<float> >(640, 480);
  SimpleScene* scene = new SimpleScene;

  raytracer->setScene(scene);
  raytracer->setSize(6.4, 4.8);

  delete raytracer;
  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_Raytracer_setViewer )
{
  Raytracer<UniformSampler<float> >* raytracer = new Raytracer<UniformSampler<float> >(640, 480);
  SimpleScene* scene = new SimpleScene;

  raytracer->setScene(scene);
  raytracer->setViewer(Point3df::Constant(0), Vector3df::Constant(1));

  delete raytracer;
  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_Raytracer_setOrientation )
{
  Raytracer<UniformSampler<float> >* raytracer = new Raytracer<UniformSampler<float> >(640, 480);
  SimpleScene* scene = new SimpleScene;

  raytracer->setScene(scene);
  Vector3df vector = Vector3df::Constant(0.);
  vector(1) = 1.;
  raytracer->setOrientation(vector);

  delete raytracer;
  delete scene;
}

BOOST_AUTO_TEST_CASE( test_IRT_Raytracer_draw )
{
  Raytracer<UniformSampler<float> >* raytracer = new Raytracer<UniformSampler<float> >(640, 480);
  SimpleScene* scene = new SimpleScene;

  raytracer->setScene(scene);
  raytracer->setSize(6.4, 4.8);
  raytracer->setViewer(Point3df::Constant(0.), Vector3df::Constant(1.));
  Vector3df vector = Vector3df::Constant(0.);
  vector(1) = 1.;
  raytracer->setOrientation(vector);

  float* screen = new float[640*480*3];

  raytracer->draw(screen);

  for(unsigned i = 0; i < 640*480*3; ++i)
    BOOST_CHECK(screen[i] == 0.f);

  delete[] screen;
  delete raytracer;
  delete scene;
}

// BOOST_AUTO_TEST_CASE( test_IRT_Raytracer_computeColor )
// {
//   Raytracer* raytracer = new Raytracer(640, 480);
//   SimpleScene* scene = new SimpleScene;
//
//   raytracer->setScene(scene);
//   raytracer->setSize(6.4, 4.8);
//   raytracer->setViewer(Point3df(0.), Vector3df(1.));
//   Vector3df vector(0.);
//   vector(1) = 1.;
//   raytracer->setOrientation(vector);
//
//   Vector3df direction(0.);
//   direction(2) = 1.;
//   Ray ray(Point3df(0.f), direction);
//   Color color(0.);
//
//   raytracer->computeColor(ray, color, -1);
//   BOOST_CHECK(all(color == 0.f));
//
//   raytracer->computeColor(ray, color, 0);
//   BOOST_CHECK(all(color > 0.f));
//
//
//   delete raytracer;
//   delete scene;
// }

BOOST_AUTO_TEST_SUITE_END()
