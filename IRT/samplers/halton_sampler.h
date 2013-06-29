/**
 * \file halton_sampler.h
 * Describes a sampler based on Halton sequences
 */

#ifndef HALTONSAMPLER
#define HALTONSAMPLER

#include <ctime>
#include <iostream>
#include <vector>

#include "../common.h"

namespace IRT
{
  template<class Sampler>
  class Raytracer;

  template<class DataType, long prime1, long prime2>
  struct HaltonSampler
  {
    HaltonSampler(int oversampling = 2)
    {
      setOversampling(oversampling);
    }

    int getOversampling() const
    {
     return oversampling;
    }

    static DataType haltonTerm(long index, long base)
    {
      DataType h = 0;
      DataType fac = DataType(1) / base;
      DataType inv = DataType(1) / base;
      
      while(index != 0)
      {
        long digit = index % base;
        h = h + digit * fac;
        index = (index - digit) * inv;
        fac = fac * inv;
      }
      return h;

    }
    
    void setOversampling(int oversampling)
    {
      this->oversampling = oversampling;
      inverse_oversampling = 1. / oversampling;

      samples.clear();
      int index = 1;
      while(samples.size() < oversampling * oversampling)
      {
        samples.push_back(std::make_pair(haltonTerm(index, prime1), haltonTerm(index, prime2)));
        ++index;
      }
    }

    Color computeColor(const Raytracer<HaltonSampler>* raytracer, const BoundingBox& bb, Ray& ray, int i, int j) const
    {
      Color final_color = Color::Zero();
      for(typename std::vector<std::pair<DataType, DataType> >::const_iterator sample = samples.begin(); sample != samples.end(); ++sample)
      {
        raytracer->generateRay(i + sample->first, j + sample->second, ray);
        Color color = Color::Zero();
        if(raytracer->mustShoot(ray, bb))
        {
          raytracer->computeColor(ray, color);
        }

        final_color += color;
      }
      final_color *= inverse_oversampling * inverse_oversampling;

      return final_color;
    }

  protected:
    unsigned int oversampling;
    DataType inverse_oversampling;

    std::vector<std::pair<DataType, DataType> > samples;
  };
}

#endif
