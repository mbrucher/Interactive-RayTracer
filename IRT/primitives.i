/* -*- C -*-  (not really, but good for syntax highlighting) */

#ifdef SWIGPYTHON

%{
#include "IRT/primitives.h"
%}

%typemap(in)
    (IRT::Vector3df&)
    (PyArrayObject* array=NULL)
{
  array = obj_to_array_no_conversion($input, DataTypeKind);
  if (!array || !require_dimensions(array, 1) || (array->dimensions[0] != 3)) SWIG_fail;

  $1 = new IRT::Vector3df(reinterpret_cast<IRT::DataType*>(array->data));
}
%typemap(freearg)
    (IRT::Vector3df&)
{
  delete $1;
}

%typemap(in)
    (IRT::Point3df&)
    (PyArrayObject* array=NULL)
{
  array = obj_to_array_no_conversion($input, DataTypeKind);
  if (!array || !require_dimensions(array, 1) || (array->dimensions[0] != 3)) SWIG_fail;

  $1 = new IRT::Point3df(reinterpret_cast<IRT::DataType*>(array->data));
}
%typemap(freearg)
    (IRT::Point3df&)
{
  delete $1;
}

%typemap(in)
    (IRT::Color&)
    (PyArrayObject* array=NULL)
{
  array = obj_to_array_no_conversion($input, DataTypeKind);
  if (!array || !require_dimensions(array, 1) || (array->dimensions[0] != static_cast<long>(IRT::nbColors))) SWIG_fail;

  $1 = new IRT::Color(reinterpret_cast<IRT::DataType*>(array->data));
}
%typemap(freearg)
    (IRT::Color&)
{
  delete $1;
}

%typemap(in) IRT::Triangle*
{
  if ((SWIG_ConvertPtr($input,(void **)(&$1),$1_descriptor, SWIG_POINTER_EXCEPTION | SWIG_POINTER_DISOWN)) == -1) SWIG_fail;
}

%typemap(out) IRT::Triangle*
{
  $result = SWIG_NewPointerObj($1, $1_descriptor, SWIG_POINTER_OWN);
}

%typemap(in) IRT::Light*
{
  if ((SWIG_ConvertPtr($input,(void **)(&$1),$1_descriptor, SWIG_POINTER_EXCEPTION | SWIG_POINTER_DISOWN)) == -1) SWIG_fail;
}

%typemap(out) IRT::Light*
{
  $result = SWIG_NewPointerObj($1, $1_descriptor, SWIG_POINTER_OWN);
}

namespace IRT
{
  class SimpleScene;

  class Primitive
  {
  public:
    ~Primitive();
    void setColor(IRT::Color& color);
    void setReflection(float reflection);
    void setDiffuse(float diffuse);
    void addToScene(SimpleScene* scene);
  };

  class Sphere: public Primitive
  {
  public:
    Sphere(IRT::Vector3df& center, float dist);
    ~Sphere();
  };
  
  class Box: public Primitive
  {
  public:
    Box(IRT::Vector3df& corner1, IRT::Vector3df& corner2);
    ~Box();
  };
  
  class Triangle
  {
  public:
    Triangle(IRT::Vector3df& corner1, IRT::Vector3df& corner2, IRT::Vector3df& corner3);
    ~Triangle();
    void setColor(IRT::Color& color);
    void setReflection(float reflection);
    void setDiffuse(float diffuse);
  };
}

#endif /* SWIGPYTHON */
