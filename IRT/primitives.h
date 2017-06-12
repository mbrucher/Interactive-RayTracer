/**
 * \file primitives.h
 * Describes the virtual class for primitives
 */

#ifndef PRIMITIVES
#define PRIMITIVES

#include <memory>

#include "common.h"
#include "ray.h"
#include "bounding_box.h"

namespace IRT
{
  /// Characteristic of a primitive at a specific point
  struct _export_tools MaterialPoint
  {
    MaterialPoint();
    /// Normal of the primitive at a point
    Normal3df normal;
  };

  /// Virtual class for primitives (triangles, spheres, ...)
  class _export_tools Primitive
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
    * Sets the color of the sphere (emission part)
    * @param color is the color of the sphere
    */
    void setEmissionColor(const Color& color);

    const Color& getEmissionColor() const;

    /**
     * Sets the color of the sphere (diffusion)
     * @param color is the color of the sphere
     */
    void setDiffuseColor(const Color& color);

    const Color& getDiffuseColor() const;

    /**
    * Sets the color of the sphere (specular)
    * @param color is the color of the sphere
    */
    void setSpecularColor(const Color& color);

    const Color& getSpecularColor() const;

    /**
    * Sets the shininess parameters of the sphere
    * @param shininess is the shininess factor of the sphere
    */
    void setShininess(DataType shininess);

    DataType getShininess() const;

    /**
      * Sets the reflection parameters of the sphere
      * @param reflection is the reflection factor of the sphere
      */
    void setReflection(DataType reflection);

    DataType getReflection() const;

    virtual std::unique_ptr<Primitive> clone() const = 0;

  protected:
    /// Color of the sphere
    Color emission_color;
    /// Color of the sphere
    Color diffuse_color;
    /// Color of the sphere
    Color specular_color;
    /// Shininess factor of the sphere
    DataType shininess;
    /// Reflection factor of the sphere
    DataType reflection;
  };

  /// A simple sphere
  class _export_tools Sphere: public Primitive
  {
  public:
    /**
     * Construct a new sphere
     * @param center is the center of the sphere
     * @param radius is the radius of the sphere
     */
    Sphere(const Point3df& center, DataType radius);

    /// Destructor
    ~Sphere();

    /**
     * Tests if a ray intersects the sphere
     * @param ray is the ray to test
     * @param dist is an output argument that will contain the distance between the ray origin and the primitive
     * @return True or False depending on the result of the test
     */
    bool intersect(const Ray& ray, DataType& dist) const override;

    /**
     * Computes the normal and the color of the point based on the intersection point with the primitive
     * @param ray is the direction ray
     * @param dist is the distance to the primitive
     * @param caracteristics is a the caracteristics of the primitive at this point
     */
    void computeColorNormal(const Ray& ray, DataType dist, MaterialPoint& caracteristics) const override;

    /**
     * Returns the bounding box of the primitive
     * @return the bounding box
     */
    virtual BoundingBox getBoundingBox() const override;

    virtual std::unique_ptr<Primitive> clone() const override;

  private:
    /// Center of the sphere
    Point3df center;
    /// Radius of the sphere
    DataType radius;
  };
  
  /// A simple Box
  class _export_tools Box: public Primitive
  {
  public:
    /**
     * Construct a new Box
     * @param corner1 is the left bottom back corner
     * @param corner2 is the right up front corner
     */
    Box(const Point3df& corner1, const Point3df& corner2);
    
    /// Destructor
    ~Box();
    
    /**
     * Tests if a ray intersects the sphere
     * @param ray is the ray to test
     * @param dist is an output argument that will contain the distance between the ray origin and the primitive
     * @return True or False depending on the result of the test
     */
    bool intersect(const Ray& ray, DataType& dist) const override;
    
    /**
     * Computes the normal and the color of the point based on the intersection point with the primitive
     * @param ray is the direction ray
     * @param dist is the distance to the primitive
     * @param caracteristics is a the caracteristics of the primitive at this point
     */
    void computeColorNormal(const Ray& ray, DataType dist, MaterialPoint& caracteristics) const override;
    
    /**
     * Returns the bounding box of the primitive
     * @return the bounding box
     */
    virtual BoundingBox getBoundingBox() const override;

    virtual std::unique_ptr<Primitive> clone() const override;
  private:
    /// First corner
    Point3df corner1;
    /// Second corner
    Point3df corner2;
  };
  
  /// A simple triangle
  class _export_tools Triangle: public Primitive
  {
  public:
    /**
     * Construct a new Triangle
     * @param corner1
     * @param corner2
     * @param corner3
     */
    Triangle(const Point3df& corner1, const Point3df& corner2, const Point3df& corner3);
    
    /// Destructor
    ~Triangle();
    
    /**
     * Tests if a ray intersects the triangle
     * @param ray is the ray to test
     * @param dist is an output argument that will contain the distance between the ray origin and the primitive
     * @return True or False depending on the result of the test
     */
    bool intersect(const Ray& ray, DataType& dist) const override;
    
    /**
     * Computes the normal and the color of the point based on the intersection point with the primitive
     * @param ray is the direction ray
     * @param dist is the distance to the primitive
     * @param caracteristics is a the caracteristics of the primitive at this point
     */
    void computeColorNormal(const Ray& ray, DataType dist, MaterialPoint& caracteristics) const override;
    
    /**
     * Returns the bounding box of the primitive
     * @return the bounding box
     */
    virtual BoundingBox getBoundingBox() const override;

    virtual std::unique_ptr<Primitive> clone() const override;
  private:
    /// First corner
    Point3df corner1;
    /// Second corner
    Point3df corner2;
    /// Third corner
    Point3df corner3;
    /// First direction
    Point3df v0;
    /// Second direction
    Point3df v1;
    /// Normal
    Point3df normal;
  };
}

#endif
