/**
 * \file primitives.h
 * Describes the virtual class for primitives
 */

#ifndef PRIMITIVES
#define PRIMITIVES

#include "common.h"
#include "ray.h"
#include "bounding_box.h"

namespace IRT
{
  /// Carateristic of a primitive at a specific point
  struct MaterialPoint
  {
    _export_tools MaterialPoint();
    /// Normal of the primitive at a point
    Normal3df normal;
  };

  /// Virtual class for primitives (triangles, spheres, ...)
  class Primitive
  {
  public:
    Primitive();

    /// Virtual destructor
    virtual ~Primitive()
    {}

    /**
     * Tests if a ray intersects the primitive and at which distance it does
     * @param ray is the ray to test
     * @param dist is an output argument that will contain the distance between the ray origin and the primitive
     * @return True or False depending on the result of the test
     */
    virtual bool intersect(const Ray& ray, DataType& dist) const = 0;

    /**
     * Computes the normal and the color of the point based on the intersection point with the primitive
     * @param ray is the direction ray
     * @param dist is the distance to the primitive
     * @param caracteristics is a the caracteristics of the primitive at this point
     */
    virtual void computeColorNormal(const Ray& ray, DataType dist, MaterialPoint& caracteristics) const = 0;
    
    /**
     * Returns the bounding box of the primitive
     * @return the bounding box
     */
    virtual BoundingBox getBoundingBox() const = 0;

    /**
     * Sets the color of the sphere
     * @param color is the color of the sphere
     */
    _export_tools void setColor(const Color& color);

    _export_tools const Color& getColor() const;
    
    /**
      * Sets the reflection parameters of the sphere
      * @param reflection is the reflection "color" of the sphere
      */
    _export_tools void setReflection(float reflection);

    _export_tools float getReflection() const;    
    /**
      * Sets the diffuse parameters of the sphere
      * @param diffuse is the reflection "color" of the sphere
      */
    _export_tools void setDiffuse(float diffuse);

    _export_tools float getDiffuse() const;
  protected:
    /// Color of the sphere
    Color color;
    /// Reflection factor of the sphere
    float reflection;
    /// Diffuse factor of the sphere
    float diffuse;
  };

  /// A simple sphere
  class Sphere: public Primitive
  {
  public:
    /**
     * Construct a new sphere
     * @param center is the center of the sphere
     * @param radius is the raius of the sphere
     */
    _export_tools Sphere(const Point3df& center, DataType radius);

    /// Destructor
    _export_tools ~Sphere();

    /**
     * Tests if a ray intersects the sphere
     * @param ray is the ray to test
     * @param dist is an output argument that will contain the distance between the ray origin and the primitive
     * @return True or False depending on the result of the test
     */
    _export_tools bool intersect(const Ray& ray, DataType& dist) const;

    /**
     * Computes the normal and the color of the point based on the intersection point with the primitive
     * @param ray is the direction ray
     * @param dist is the distance to the primitive
     * @param caracteristics is a the caracteristics of the primitive at this point
     */
    _export_tools void computeColorNormal(const Ray& ray, DataType dist, MaterialPoint& caracteristics) const;

    /**
     * Returns the bounding box of the primitive
     * @return the bounding box
     */
    _export_tools virtual BoundingBox getBoundingBox() const;
  private:
    /// Center of the sphere
    Point3df center;
    /// Radius of the sphere
    DataType radius;
  };

  /// A simple Box
  class Box: public Primitive
  {
  public:
    /**
     * Construct a new Box
     * @param corner1 is the left bottom back corner
     * @param corner2 is the right up front corner
     */
    _export_tools Box(const Point3df& corner1, const Point3df& corner2);

    /// Destructor
    _export_tools ~Box();

    /**
     * Tests if a ray intersects the sphere
     * @param ray is the ray to test
     * @param dist is an output argument that will contain the distance between the ray origin and the primitive
     * @return True or False depending on the result of the test
     */
    _export_tools bool intersect(const Ray& ray, DataType& dist) const;

    /**
     * Computes the normal and the color of the point based on the intersection point with the primitive
     * @param ray is the direction ray
     * @param dist is the distance to the primitive
     * @param caracteristics is a the caracteristics of the primitive at this point
     */
    _export_tools void computeColorNormal(const Ray& ray, DataType dist, MaterialPoint& caracteristics) const;

    /**
     * Returns the bounding box of the primitive
     * @return the bounding box
     */
    _export_tools virtual BoundingBox getBoundingBox() const;
  private:
    /// First corner
    Point3df corner1;
    /// Second corner
    Point3df corner2;
  };
}

#endif
