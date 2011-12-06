/**
 * \file multi_jittered_sampler.h
 * Describes a multi-jittered sampler
 */

#ifndef MULTIJITTEREDSAMPLER
#define MULTIJITTEREDSAMPLER

#include <ctime>
#include <vector>
#include <algorithm>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_real.hpp>

#include "../common.h"

namespace IRT
{
  template<class Sampler>
  class Raytracer;

  template<class DataType>
  struct MultiJitteredSampler
  {
    MultiJitteredSampler(int oversampling = 2)
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
      boost::uniform_real<DataType> generator(0, 1);
      boost::variate_generator<boost::mt19937, boost::uniform_real<DataType> > binded(engine, generator);

      samples.clear();

      std::vector<DataType> shuffled_positions_x(oversampling);
      std::vector<DataType> shuffled_positions_y(oversampling);
      for(int i = 0; i < oversampling; ++i)
      {
        shuffled_positions_x[i] = oversampling * (i - oversampling/2.);
        shuffled_positions_y[i] = oversampling * (i - oversampling/2.);
      }
      std::random_shuffle(shuffled_positions_x.begin(), shuffled_positions_x.end());
      std::random_shuffle(shuffled_positions_y.begin(), shuffled_positions_y.end());

      for(int i = 0; i < oversampling; ++i)
      {
        for(int j = 0; j < oversampling; ++j)
        {
          samples.push_back(std::make_pair((shuffled_positions_x[i] + (oversampling - j - 1) + binded()) * inverse_oversampling * inverse_oversampling,
                                           (shuffled_positions_y[j] + (oversampling - i - 1) + binded()) * inverse_oversampling * inverse_oversampling));
        }
      }
    }

    Color computeColor(const Raytracer<MultiJitteredSampler>* raytracer, const BoundingBox& bb, Ray& ray, int i, int j) const
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
