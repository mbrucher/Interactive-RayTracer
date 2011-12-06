/* -*- C -*-  (not really, but good for syntax highlighting) */

// Matthieu Brucher
// Last Change : 2009-05-34 15:12

#ifdef SWIGPYTHON

%{
#include "IRT/build_kdtree.h"
%}

namespace IRT
{
  struct BuildKDTree
  {
    static void custom_build(IRT::SimpleScene* scene, int remaining_depth, int remaining_failures, float enhancement_ratio_failure);
    static void automatic_build(IRT::SimpleScene* scene);
  };
}
#endif /* SWIGPYTHON */
