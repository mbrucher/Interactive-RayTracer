/**
 * \file light.cpp
 * Implementation of lights
 */

#include "light.h"

namespace IRT
{
  Light::Light(const Vector3df& center, const Color& color)
  :center(center), color(color)
  {
  }

  Color Light::computeColor(const Ray& ray, float dist) const
  {
    return color * (1 / (dist * dist));
  }

  const Vector3df& Light::getCenter() const
  {
    return center;
  }
}
