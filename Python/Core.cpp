/**
 * \file Core.cpp
 */

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/eigen.h>

#include <IRT/primitives.h>
#include <IRT/light.h>
#include <IRT/simple_scene.h>
#include <IRT/build_kdtree.h>
#include <IRT/raytracer.h>

#include <IRT/samplers/halton_sampler.h>
#include <IRT/samplers/jittered_sampler.h>
#include <IRT/samplers/multi_jittered_sampler.h>
#include <IRT/samplers/nrooks_sampler.h>
#include <IRT/samplers/random_sampler.h>
#include <IRT/samplers/uniform_sampler.h>

namespace py = pybind11;

using namespace IRT;

namespace
{
  template<typename Sampler>
  void populate_raytracer(py::module& m, const char* type)
  {
    py::class_<Raytracer<Sampler>>(m, type)
      .def(py::init<unsigned long, unsigned long>())
      .def_property("size", &Raytracer<Sampler>::getSize,
      [](Raytracer<Sampler>& instance, const py::array_t<DataType>& array)
      {
        instance.setSize(array.at(0), array.at(1));
      })
      .def_property("viewer",
      [](const Raytracer<Sampler>& instance)
      {
        auto view = instance.getViewer();
        return std::make_pair(py::array_t<DataType>(3, view.first.data()), py::array_t<DataType>(3, view.second.data()));
      },
      [](Raytracer<Sampler>& instance, const std::pair<Point3df, Vector3df>& l)
      {
        instance.setViewer(l.first, l.second);
      })
      .def_property("orientation", &Raytracer<Sampler>::getOrientation, &Raytracer<Sampler>::setOrientation)
      .def_property("oversampling", &Raytracer<Sampler>::getOversampling, &Raytracer<Sampler>::setOversampling)
      .def_property("levels", &Raytracer<Sampler>::getLevels, &Raytracer<Sampler>::setLevels)
      .def_property("scene", &Raytracer<Sampler>::getScene, &Raytracer<Sampler>::setScene)
      .def("draw", [](const Raytracer<Sampler>& instance, py::array_t<DataType>& array)
      {
        instance.draw(array.mutable_data());
      })
        .def("checkDraw", [](const Raytracer<Sampler>& instance, py::array_t<int>& array, int type)
      {
        instance.checkDraw(array.mutable_data(), type);
      });

  }
}

PYBIND11_PLUGIN(PythonIRT) {
  py::module m("PythonIRT", "Interactive RayTracer module");

  py::class_<Primitive>(m, "Primitive")
    .def_property("emission_color", &Primitive::getEmissionColor, &Primitive::setEmissionColor)
    .def_property("diffuse_color", &Primitive::getDiffuseColor, &Primitive::setDiffuseColor)
    .def_property("specular_color", &Primitive::getSpecularColor, &Primitive::setSpecularColor)
    .def_property("shininess", &Primitive::getShininess, &Primitive::setShininess)
    .def_property("reflection", &Primitive::getReflection, &Primitive::setReflection);

  py::class_<Sphere, Primitive>(m, "Sphere")
    .def(py::init<Point3df, DataType>());

  py::class_<Box, Primitive>(m, "Box")
    .def(py::init<Point3df, Point3df>());

  py::class_<Triangle, Primitive>(m, "Triangle")
    .def(py::init<Point3df, Point3df, Point3df>());

  py::class_<Light>(m, "Light")
    .def(py::init<Point3df, Color>());

  py::class_<SimpleScene>(m, "SimpleScene")
    .def(py::init<>())
    .def_property("ambient_color", &SimpleScene::getAmbientColor, &SimpleScene::setAmbientColor)
    .def("addPrimitive", [](SimpleScene& scene, const Primitive* primitive)
    {
      scene.addPrimitive(primitive->clone());
    })
    .def("addLight", [](SimpleScene& scene, const Light* light)
    {
      scene.addLight(std::unique_ptr<Light>(new Light(*light)));
    });

  py::class_<BuildKDTree>(m, "BuildKDTree")
    .def_static("custom_build", &BuildKDTree::custom_build)
    .def_static("automatic_build", &BuildKDTree::automatic_build);

  populate_raytracer<HaltonSampler<DataType, 2, 3>>(m, "Raytracer_Halton_2_3");
  populate_raytracer<JitteredSampler<DataType>>(m, "Raytracer_Jittered");
  populate_raytracer<MultiJitteredSampler<DataType>>(m, "Raytracer_MultiJittered");
  populate_raytracer<NRooksSampler<DataType>>(m, "Raytracer_NRooks");
  populate_raytracer<RandomSampler<DataType>>(m, "Raytracer_Random");
  populate_raytracer<UniformSampler<DataType>>(m, "Raytracer_Uniform");

  return m.ptr();
}
