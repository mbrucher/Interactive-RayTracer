/**
 * \file light.h
 * Describes the lights in a scene
 */

#ifndef LIGHT
#define LIGHT

#include "common.h"
#include "ray.h"

namespace IRT
{
  /// Class for lights
  class _export_tools Light
  {
  private:
    /// Center of the light
    Vector3df center;
    /// Color of the light
    Color color;
  public:
    /**
     * Construct a light with a specific color
     * @param center is the center of the light
     * @param color is the color of the light
     */
    Light(const Vector3df& center, const Color& color);

    /// destructor
    ~Light()
    {}

    /**
     * Returns the color of the light
     * @return a color
     */
    Color computeColor(const Ray& ray, float dist) const;

    /**
     * Returns the center of the light
     */
    const Vector3df& getCenter() const;
  };
}

#endif
