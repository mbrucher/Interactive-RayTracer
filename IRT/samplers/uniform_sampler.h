/**
 * \file uniform_sampler.h
 * Describes a uniform sampler
 */

#ifndef UNIFORMSAMPLER
#define UNIFORMSAMPLER

#include "../common.h"

namespace IRT
{
  template<class Sampler>
  class Raytracer;

  template<class DataType>
  struct UniformSampler
  {
    UniformSampler()
    {
      setOversampling(2);
    }

    int getOversampling() const
    {
     return oversampling;
    }

    void setOversampling(int oversampling)
    {
      this->oversampling = oversampling;
      inverse_oversampling = 1. / oversampling;
    }

    Color computeColor(const Raytracer<UniformSampler>* raytracer, const BoundingBox& bb, Ray& ray, int i, int j) const
    {
      Color final_color = Color::Zero();
      for(float l = -1/2. + inverse_oversampling / 2; l < 1/2.; l += inverse_oversampling)
      {
        for(float k = -1/2. + inverse_oversampling / 2; k < 1/2.; k += inverse_oversampling)
        {
          raytracer->generateRay(i + k, j + l, ray);
          Color color = Color::Zero();
          if(raytracer->mustShoot(ray, bb))
          {
            raytracer->computeColor(ray, color);
          }

          final_color += color;
        }
      }
      final_color *= inverse_oversampling * inverse_oversampling;

      return final_color;
    }

  protected:
    unsigned int oversampling;
    DataType inverse_oversampling;
  };
}

#endif
