/* -*- C -*-  (not really, but good for syntax highlighting) */

#ifdef SWIGPYTHON

%{
#include "IRT/simple_scene.h"
%}

%apply Pointer NONNULL{IRT::Triangle*};

namespace IRT
{
  class SimpleScene
  {
  public:
    SimpleScene();
    ~SimpleScene();
    IRT::Triangle* removeTriangle(unsigned long index);
    unsigned long addTriangle(IRT::Triangle* Triangle);
    std::vector<unsigned long> addTriangles(const std::vector<IRT::Triangle*>& triangles);
    IRT::Light* removeLight(unsigned long index);
    unsigned long addLight(IRT::Light* light);
    const BoundingBox& getBoundingBox();
  };
}

#endif /* SWIGPYTHON */
