/* -*- C -*-  (not really, but good for syntax highlighting) */

#ifdef SWIGPYTHON

%{
#define SWIG_FILE_WITH_INIT
#define PY_ARRAY_UNIQUE_SYMBOL PyArray_API
%}
%include "numpy.i"
%fragment("NumPy_Fragments");
%{
const int DataTypeKind = NPY_FLOAT;
%}
%init %{
import_array();
%}

%include "constraints.i"

%module(package="IRT", docstring="Python interface to the Interactive RayTracer") IRT

%nodefaultdtor;
%nodefaultctor;

%include "primitives.i"
%include "bounding_box.i"
%include "light.i"
%include "simple_scene.i"
%include "raytracer.i"

%include "kdtree.i"

#endif /* SWIGPYTHON */
