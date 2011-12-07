/**
 * \file nrooks_sampler.h
 * Describes a n-rooks sampler
 */

#ifndef NROOKSSAMPLER
#define NROOKSSAMPLER

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
  struct NRooksSampler
  {
    NRooksSampler(int oversampling = 2)
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

      std::vector<DataType> shuffled_positions(oversampling*oversampling);
      for(int i = 0; i < oversampling*oversampling; ++i)
      {
        shuffled_positions[i] = i - oversampling*oversampling/2.;
      }
      std::random_shuffle(shuffled_positions.begin(), shuffled_positions.end());

      int i = 0;
      for(DataType j = -oversampling*oversampling/2.; j < oversampling*oversampling/2.; ++j)
      {
          samples.push_back(std::make_pair((shuffled_positions[i] + binded()) * inverse_oversampling * inverse_oversampling, (j + binded()) * inverse_oversampling * inverse_oversampling));
          ++i;
      }
    }

    Color computeColor(const Raytracer<NRooksSampler>* raytracer, const BoundingBox& bb, Ray& ray, int i, int j) const
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
