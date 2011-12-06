/* -*- C -*-  (not really, but good for syntax highlighting) */

// Matthieu Brucher
// Last Change : 2008-12-14 18:28

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
