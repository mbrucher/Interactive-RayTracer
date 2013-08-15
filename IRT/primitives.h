/**
 * \file primitives.h
 * Describes the virtual class for primitives
 */

#ifndef PRIMITIVES
#define PRIMITIVES

#include "common.h"
#include "ray.h"
#include "bounding_box.h"

#include <list>
#include <vector>

namespace IRT
{
  class SimpleScene;

  /// Carateristic of a primitive at a specific point
  struct MaterialPoint
  {
    _export_tools MaterialPoint();
    /// Normal of the primitive at a point
    Normal3df normal;
  };

    /// A simple triangle
  class Triangle
  {
  public:
    /**
     * Construct a new Triangle
     * @param corner1
     * @param corner2
     * @param corner3
     */
    _export_tools Triangle(const Point3df& corner1, const Point3df& corner2, const Point3df& corner3);
    
    /// Destructor
    _export_tools ~Triangle();
    
    /**
     * Tests if a ray intersects the triangle
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
    /// Third corner
    Point3df corner3;
    /// First direction
    Vector3df v0;
    /// Second direction
    Vector3df v1;
    /// Normal
    Vector3df normal;
 
 public:
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

  /// Virtual class for primitives (triangles, spheres, ...)
  class Primitive
  {
  public:
    Primitive();

    /// Virtual destructor
    virtual ~Primitive()
    {}

    /**
     * Adds the primitive to the scene
     */
    _export_tools void addToScene(SimpleScene* scene);

    /**
     * Sets the color of the sphere
     * @param color is the color of the sphere
     */
    _export_tools void setColor(const Color& color);

    /**
      * Sets the reflection parameters of the sphere
      * @param reflection is the reflection "color" of the sphere
      */
    _export_tools void setReflection(float reflection);
    /**
      * Sets the diffuse parameters of the sphere
      * @param diffuse is the reflection "color" of the sphere
      */
    _export_tools void setDiffuse(float diffuse);
  protected:
    /// Vector of triangles for the primitive
    std::vector<Triangle*> triangles;
    
    struct TriPoints
    {
      TriPoints(const Point3df& p0, const Point3df& p1, const Point3df& p2)
      :p0(p0), p1(p1), p2(p2)
      {
      }
      
      Point3df p0;
      Point3df p1;
      Point3df p2;
    };
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
    _export_tools Sphere(const Point3df& center, DataType radius, int refinement = 2);

    /// Destructor
    _export_tools ~Sphere();
  private:
    /// Compute the middle point of a segment on the sphere
    Point3df middlePoint(const Point3df& p1, const Point3df& p2);
    /// Create initial mesh
    std::list<TriPoints> createMesh();
    /// Refine the sphere mesh
    void refine(std::list<TriPoints>& list);
    /// Generate the triangles
    void generateTriangles(std::list<TriPoints>& list);
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
  private:
    /// First corner
    Point3df corner1;
    /// Second corner
    Point3df corner2;
  };
}
  
#endif
