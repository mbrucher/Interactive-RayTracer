/**
 * \file bounding_box.h
 * Describes the bounding box
 */

// Matthieu Brucher
// Last Change: 2009-05-15 22:47

#ifndef BOUNDINGBOX
#define BOUNDINGBOX

#include "common.h"

namespace IRT
{
  /// Carateristic of a primitive at a specific point
  struct BoundingBox
  {
    /// right corner
    Point3df corner1;
    /// left corner
    Point3df corner2;

    /**
     * Computes the entry and exit distances of the ray for this bounding box
     */
    bool getEntryExitDistances(const Ray& ray, DataType& tnear, DataType& tfar) const
    {
      tfar = std::numeric_limits<float>::max();
      tnear = std::numeric_limits<float>::epsilon();
      for(int i = 0; i < 3; ++i)
      {
        float pos = ray.origin()(i) + tfar * ray.direction()(i);
        float pos_near = ray.origin()(i) + tnear * ray.direction()(i);
        if(ray.direction()(i) < 0)
        {
          if(pos < corner1(i))
          {
            tfar = (corner1(i) - ray.origin()(i)) / ray.direction()(i);
          }
          else if(pos > corner2(i))
          {
            tfar = std::numeric_limits<float>::epsilon();
          }
          if(pos_near > corner2(i))
          {
            tnear = (corner2(i) - ray.origin()(i)) / ray.direction()(i);
          }
          else if(pos_near < corner1(i))
          {
            tnear = std::numeric_limits<float>::max();
          }
        }
        else if (ray.direction()(i) > 0)
        {
          if(pos > corner2(i))
          {
            tfar = (corner2(i) - ray.origin()(i)) / ray.direction()(i);
          }
          else if(pos < corner1(i))
          {
            tfar = std::numeric_limits<float>::epsilon();
          }
          if(pos_near < corner1(i))
          {
            tnear = (corner1(i) - ray.origin()(i)) / ray.direction()(i);
          }
          else if(pos_near > corner2(i))
          {
            tnear = std::numeric_limits<float>::max();
          }
        }
        
        if (tnear > tfar)
        {
          return false;
        }
      }

      return true;
    }

    DataType SAH() const
    {
      Vector3df size = corner2 - corner1;
      
      return 2 * (size(0) * size(1) + size(0) * size(2) + size(1) * size(2));
    }
  };
}

#endif
