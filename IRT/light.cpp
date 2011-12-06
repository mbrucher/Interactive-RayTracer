/**
 * \file light.cpp
 * Implementation of lights
 */

// Matthieu Brucher
// Last Change : 2009-04-05 22:43

#include "light.h"

namespace IRT
{
  Light::Light(const Vector3df& center, const Color& color)
  :center(center), color(color)
  {
  }

  Color Light::computeColor(const Ray& ray, float dist) const
  {
    return color;// * (1 / (dist * dist));
  }

  const Vector3df& Light::getCenter() const
  {
    return center;
  }
}
