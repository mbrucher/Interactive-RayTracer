/**
 * \file ray.h
 * Describes one ray
 */

#ifndef RAY
#define RAY

#include "common.h"

namespace IRT
{
  /// The default class for the ray
  class Ray
  {
  private:
    /// The origin
    Point3df origin_;
    /// The direction
    Vector3df direction_;

  public:
    /// Simple constructor
    _export_tools Ray(const Point3df& origin, const Vector3df& direction);
    /// Simple constructor
    _export_tools Ray();

    /// Destructor
    _export_tools ~Ray();

    /// Returns the origin of the ray
    const Point3df& origin() const
    {
      return origin_;
    }
    /// Returns the origin of the ray
    Point3df& origin()
    {
      return origin_;
    }
    /// Returns the direction of the ray
    const Vector3df& direction() const
    {
      return direction_;
    }
    /// Returns the direction of the ray
    Vector3df& direction()
    {
      return direction_;
    }
  };
}

#endif
