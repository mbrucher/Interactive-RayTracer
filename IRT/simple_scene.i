/* -*- C -*-  (not really, but good for syntax highlighting) */

#ifdef SWIGPYTHON

%{
#include "IRT/simple_scene.h"
%}

%apply Pointer NONNULL{IRT::Primitive*};

namespace IRT
{
  class SimpleScene
  {
  public:
    SimpleScene();
    ~SimpleScene();
    IRT::Primitive* removePrimitive(unsigned long index);
    unsigned long addPrimitive(IRT::Primitive* primitive);
    std::vector<unsigned long> addPrimitives(const std::vector<IRT::Primitive*>& primitives);
    IRT::Light* removeLight(unsigned long index);
    unsigned long addLight(IRT::Light* light);
    const BoundingBox& getBoundingBox();
  };
}

#endif /* SWIGPYTHON */
