/* -*- C -*-  (not really, but good for syntax highlighting) */

#ifdef SWIGPYTHON

%{
#include "IRT/raytracer.h"

#include "IRT/samplers/halton_sampler.h"
#include "IRT/samplers/jittered_sampler.h"
#include "IRT/samplers/multi_jittered_sampler.h"
#include "IRT/samplers/nrooks_sampler.h"
#include "IRT/samplers/random_sampler.h"
#include "IRT/samplers/uniform_sampler.h"
%}

%typemap(typecheck)
  (IRT::DataType* INPLACE_ARRAY)
{
  $1 = is_array($input) && PyArray_EquivTypenums(array_type($input), DataTypeKind);
}
%typemap(in)
  (IRT::DataType* INPLACE_ARRAY)
  (PyArrayObject* array=NULL)
{
if(is_array($input) && PyArray_EquivTypenums(array_type($input), DataTypeKind))
{
  array = obj_to_array_no_conversion($input, DataTypeKind);
  $1 = ($1_ltype) array->data;
}
else
{
  PyErr_SetString(PyExc_ValueError, "Not the proper value type");
  return NULL;
}
}

%typemap(typecheck)
(int* INPLACE_ARRAY)
{
  $1 = is_array($input) && PyArray_EquivTypenums(array_type($input), CheckTypeKind);
}
%typemap(in)
(int* INPLACE_ARRAY)
(PyArrayObject* array=NULL)
{
if(is_array($input) && PyArray_EquivTypenums(array_type($input), CheckTypeKind))
{
  array = obj_to_array_no_conversion($input, CheckTypeKind);
  $1 = ($1_ltype) array->data;
}
else
{
  PyErr_SetString(PyExc_ValueError, "Not the proper value type");
  return NULL;
}
}

namespace IRT
{
  template<class Sampler>
  class Raytracer
  {
  public:
    Raytracer(unsigned long pixelWidth, unsigned long pixelHeight);
    ~Raytracer();

    void draw(IRT::DataType* INPLACE_ARRAY);
    void checkDraw(int* INPLACE_ARRAY, long type);
    void setResolution(unsigned long pixelWidth, unsigned long pixelHeight);
    std::pair<unsigned long, unsigned long> getResolution();
    void setScene(IRT::SimpleScene* scene);
    void setSize(float width, float height);
    void setViewer(IRT::Vector3df& origin, IRT::Vector3df& direction);
    void setOrientation(IRT::Vector3df& orientation);
    void setOversampling(int oversampling);
    void setLevels(int levels);
  };
}

%template(Raytracer_Halton_2_3) IRT::Raytracer<IRT::HaltonSampler<float, 2, 3> >;
%template(Raytracer_Jittered) IRT::Raytracer<IRT::JitteredSampler<float> >;
%template(Raytracer_MultiJittered) IRT::Raytracer<IRT::MultiJitteredSampler<float> >;
%template(Raytracer_NRooks) IRT::Raytracer<IRT::NRooksSampler<float> >;
%template(Raytracer_Random) IRT::Raytracer<IRT::RandomSampler<float> >;
%template(Raytracer_Uniform) IRT::Raytracer<IRT::UniformSampler<float> >;

#endif /* SWIGPYTHON */
