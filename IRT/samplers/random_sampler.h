/**
 * \file random_sampler.h
 * Describes a random sampler
 */

#ifndef RANDOMSAMPLER
#define RANDOMSAMPLER

#include <ctime>
#include <vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_real.hpp>

#include "../common.h"

namespace IRT
{
  template<class Sampler>
  class Raytracer;

  template<class DataType>
  struct RandomSampler
  {
    RandomSampler(int oversampling = 2)
    {
      setOversampling(oversampling);
    }

    int getOversampling() const
    {
     return oversampling;
    }

    void setOversampling(int oversampling)
    {
      this->oversampling = oversampling;
      inverse_oversampling = 1. / oversampling;

      boost::mt19937 engine(static_cast<long unsigned int>(clock()));
      boost::uniform_real<DataType> generator(-.5, .5);
      boost::variate_generator<boost::mt19937, boost::uniform_real<DataType> > binded(engine, generator);

      samples.clear();
      for(int i = 0; i < oversampling * oversampling; ++i)
      {
        samples.push_back(std::make_pair(binded(), binded()));
      }
    }

    Color computeColor(const Raytracer<RandomSampler>* raytracer, const BoundingBox& bb, Ray& ray, int i, int j) const
    {
      Color final_color(0.);
      for(typename std::vector<std::pair<DataType, DataType> >::const_iterator sample = samples.begin(); sample != samples.end(); ++sample)
      {
        raytracer->generateRay(i + sample->first, j + sample->second, ray);
        Color color(0.);
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
