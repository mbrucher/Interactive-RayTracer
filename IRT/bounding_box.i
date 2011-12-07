/* -*- C -*-  (not really, but good for syntax highlighting) */

#ifdef SWIGPYTHON

%{
#include "IRT/bounding_box.h"
%}

namespace IRT
{
  class BoundingBox
  {
  public:
    IRT::Point3df corner1;
    IRT::Point3df corner2;
  };
}

#endif /* SWIGPYTHON */
