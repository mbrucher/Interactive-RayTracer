/* -*- C -*-  (not really, but good for syntax highlighting) */

#ifdef SWIGPYTHON

%{
#include "IRT/light.h"
%}

namespace IRT
{
  class Light
  {
  public:
    Light(IRT::Vector3df& center, IRT::Color& color);
    ~Light();
    IRT::Color computeColor(IRT::Ray& ray, float dist);
  };
}

#endif /* SWIGPYTHON */
