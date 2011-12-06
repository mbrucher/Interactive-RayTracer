/**
 * \file ray.cpp
 * Implements the ray
 */

#include "ray.h"

namespace IRT
{
  Ray::Ray(const Point3df& origin, const Vector3df& direction)
    :origin_(origin), direction_(direction)
  {
  }

  Ray::Ray()
  {
  }

  Ray::~Ray()
  {
  }
}
