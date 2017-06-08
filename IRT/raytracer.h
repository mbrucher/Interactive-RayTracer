/**
 * \file raytracer.h
 * The raytracer
 */

#ifndef RAYTRACER
#define RAYTRACER

#ifdef USE_TBB
#include <tbb/tbb.h>
#endif

#include "common.h"
#include "ray.h"
#include "bounding_box.h"

namespace IRT
{
  class SimpleScene;

  /// The default class for the raytracer
  template<class Sampler>
  class Raytracer
  {
  public:
    /**
     * Generate a new ray to the screen
     * @param x is the abscisse of the point
     * @param y is the ordinate of the point
     * @param ray is a new ray passing through the point
     */
    void generateRay(DataType x, DataType y, Ray& ray) const
    {
      ray.direction() = direction + orientation_u * (x - precompWidth) + orientation_v * (precompHeight - y);

      normalize(ray.direction());
    }

    /**
     * Computes the color for a specific ray
     * @param ray is the ray to use
     * @param color is the color to specify
     * @param level is the level of the ray (primary ray = 0)
     */
    void computeColor(const Ray& ray, Color& color, unsigned int level=0) const
    {
      DataType tnear;
      DataType tfar;

      if(!scene->getBoundingBox().getEntryExitDistances(ray, tnear, tfar))
      {
        return;
      }

      DataType dist;
      Primitive* primitive = scene->getFirstCollision(ray, dist, tnear, tfar);
      if(primitive == nullptr)
        return;

      MaterialPoint characteristics;
      primitive->computeColorNormal(ray, dist, characteristics);
      color = scene->computeColor(ray.origin() + dist * ray.direction(), characteristics, primitive);

      if(level < levels)
      {
        Ray ray_sec(ray.origin() + dist * ray.direction(), ray.direction() - (ray.direction().dot(characteristics.normal)) * 2 * characteristics.normal);
        normalize(ray_sec.direction());
        Color color_sec = Color::Zero();
        computeColor(ray_sec, color_sec, level+1);

        color += color_sec * primitive->getReflection();
      }
    }

  private:
    /// Updates the parameters of the raytracer
    void updateParameters()
    {
      precompWidth = static_cast<DataType>(pixelWidth) / 2;
      precompHeight = static_cast<DataType>(pixelHeight) / 2;

      normalize(orientation_v);
      orientation_u = orientation_v.cross(direction);
      normalize(orientation_u);
      orientation_u *= width / pixelWidth;
      orientation_v *= height / pixelHeight;
    }
    
    void hitLevel(const Ray& ray, int& level)
    {
      DataType tnear;
      DataType tfar;
      
      if(!scene->getBoundingBox().getEntryExitDistances(ray, tnear, tfar))
      {
        return;
      }
      
      level = scene->getHitLevel(ray, tnear, tfar);
    }
    
    void hitDistance(const Ray& ray, int& dist)
    {
      DataType tnear;
      DataType tfar;
      
      if(!scene->getBoundingBox().getEntryExitDistances(ray, tnear, tfar))
      {
        dist = 0;
        return;
      }
      
      dist = scene->getHitDistance(ray, tnear, tfar);
    }

    /// Maximum recursion level
    unsigned int levels;

    Sampler sampler;
#ifdef USE_TBB
    tbb::task_scheduler_init init;
#endif

  public:
    /**
   * Constructs a raytracer
   * @param pixelWidth is the number of pixels in a row
   * @param pixelHeight is the number of pixel in a column
   */
    Raytracer(unsigned long pixelWidth, unsigned long pixelHeight)
    :levels(3), origin(Point3df::Zero()), direction(Vector3df::Zero()), orientation_u(Vector3df::Zero()), orientation_v(Vector3df::Zero()), pixelWidth(pixelWidth), pixelHeight(pixelHeight), width(0), height(0)
    {
      orientation_u(0) = 1.;
      orientation_v(1) = 1.;
    }

    /// Destructor
    ~Raytracer()
    {
    }

    /**
     * Draws the scene on the screen
     * @param screen is an allocated array of dimension pixelWidth * pixelHeight
     */
#ifdef USE_TBB
  private:
    class RaytracerOperator
    {
      const Raytracer* raytracer;
      const Sampler& sampler;
      DataType* screen;
      unsigned int pixelWidth;
      const BoundingBox& bb;
      Point3df origin;
      Vector3df direction;

    public:
      RaytracerOperator(const Raytracer* raytracer, const Sampler& sampler, DataType* screen, unsigned int pixelWidth, const BoundingBox& bb, const Point3df& origin, const Vector3df& direction)
      :raytracer(raytracer), sampler(sampler), screen(screen), pixelWidth(pixelWidth), bb(bb), origin(origin), direction(direction)
      {
      }

      void operator()(const tbb::blocked_range2d<unsigned int>& range) const
      {
        Ray ray(origin, direction);
        for( unsigned int j=range.cols().begin(); j!=range.cols().end(); ++j )
        {
          for( unsigned int i=range.rows().begin(); i!=range.rows().end(); ++i )
          {
            Color final_color = sampler.computeColor(raytracer, bb, ray, i, j);

            for(unsigned int k = 0; k < nbColors; ++k)
              screen[nbColors * (j * pixelWidth + i) + k] = final_color(k);
          }
        }
      }
    };
  public:
    void draw(DataType* screen) const
    {
      tbb::parallel_for( tbb::blocked_range2d<unsigned int>(0, pixelWidth, 32, 0, pixelHeight, 32), RaytracerOperator(this, sampler, screen, pixelWidth, scene->getBoundingBox(), origin, direction) );
    }
#else
    void draw(DataType* screen) const
    {
      Ray ray(origin, direction);
      const BoundingBox& bb = scene->getBoundingBox();
      for(unsigned int j = 0; j < pixelHeight; ++j)
      {
        for(unsigned int i = 0; i < pixelWidth; ++i)
        {
          Color final_color = sampler.computeColor(this, bb, ray, i, j);

          for(unsigned int k = 0; k < nbColors; ++k)
              screen[nbColors * (j * pixelWidth + i) + k] = final_color(k);
        }
      }
    }
#endif

    /**
     * Sets the size of the screen
     * @param width is the width of the screen
     * @param height is the height of the screen
     */
    void setSize(float width, float height)
    {
      this->width = width;
      this->height = height;

      updateParameters();
    }

    std::pair<float, float> getSize() const
    {
      return std::make_pair(width, height);
    }

    /**
     * Sets the position of the viewer and its line of sight
     * @param origin is the origin of the point
     * @param direction is the line of sight (not normalized, the norm is the distance to the screen)
     */
    void setViewer(const Point3df& origin, const Vector3df& direction)
    {
      this->origin = origin;
      this->direction = direction;

      updateParameters();
    }

    std::pair<Point3df, Vector3df> getViewer() const
    {
      return std::make_pair(origin, direction);
    }

    /**
     * Sets the orientation of the screen
     * @param orientation is the vertical orientation of the screen
     */
    void setOrientation(const Vector3df& orientation)
    {
      this->orientation_v = orientation;

      updateParameters();
    }

    Vector3df getOrientation() const
    {
      return orientation_v;
    }

    /**
     * Sets the resolution of the screen
     * @param pixelWidth the number of pixels in a row
     * @param pixelHeight is the number of pixels in a column
     */
    void setResolution(unsigned long pixelWidth, unsigned long pixelHeight)
    {
      this->pixelWidth = pixelWidth;
      this->pixelHeight = pixelHeight;

      updateParameters();
    }

    std::pair<unsigned long, unsigned long> getResolution() const
    {
      return std::make_pair(pixelWidth, pixelHeight);
    }
    /**
     * Sets the used scene
     * @param scene is the scene to use
     */
    void setScene(SimpleScene* scene)
    {
      this->scene = scene;
    }

    SimpleScene* getScene() const
    {
      return scene;
    }

    /**
     * Modifies the recursion level
     * @param levels is the new recursion level
     */
    void setLevels(unsigned int levels)
    {
      this->levels = levels;
    }

    /**
     * Returns the recursion level
     * @return the recursion level
     */
    unsigned int getLevels() const
    {
      return levels;
    }

    int getOversampling() const
    {
     return sampler.getOversampling();
    }

    void setOversampling(int oversampling)
    {
      sampler.setOversampling(oversampling);
    }

    /**
      * Indicates if the ray must be shot or not
      * @param ray is the ray to test against the bounding box
      * @param bb is the bounding box to test
      * @return true is the ray must be shot
      */
    bool mustShoot(const Ray& ray, const BoundingBox& bb) const
    {
      for ( int i = 0; i < 3; ++i )
      {
        if (ray.direction()(i) < 0)
        {
          if (ray.origin()(i) < bb.corner1(i))
          {
            return false;
          }
        }
        else if (ray.origin()(i) > bb.corner2(i))
        {
          return false;
        }
      }
      return true;
    }
   private:
    /// Origin of the field of view
    Point3df origin;
    /// Direction, line of sight, W
    Vector3df direction;
    /// Orientation U
    Vector3df orientation_u;
    /// Orientation V
    Vector3df orientation_v;
    /// Width of the array
    unsigned long pixelWidth;
    /// Height of the array
    unsigned long pixelHeight;
    /// Physical width of the screen
    float width;
    /// Physical height of the screen
    float height;

    /// Precomputed coefficient for the width
    float precompWidth;
    /// Precomputed coefficient for the height
    float precompHeight;

    /// Viewed scene, the pointer is not acquired
    SimpleScene* scene;
  };
}

#endif
