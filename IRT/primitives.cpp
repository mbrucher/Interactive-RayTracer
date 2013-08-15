/**
 * \file primitives.cpp
 * Implementation of primitives
 */

#include "primitives.h"
#include "simple_scene.h"
#include "common.h"

namespace IRT
{
  MaterialPoint::MaterialPoint()
  :normal(Normal3df::Zero())
  {
  }

  Primitive::Primitive()
  {
  }

  void Primitive::setColor(const Color& color)
  {
    for(auto it = triangles.begin(); it != triangles.end(); ++it)
    {
      (*it)->setColor(color);
    }
  }

  void Primitive::setReflection(float reflection)
  {
    for(auto it = triangles.begin(); it != triangles.end(); ++it)
    {
      (*it)->setReflection(reflection);
    }
  }

  void Primitive::setDiffuse(float diffuse)
  {
    for(auto it = triangles.begin(); it != triangles.end(); ++it)
    {
      (*it)->setDiffuse(diffuse);
    }
  }

  void Primitive::addToScene(SimpleScene* scene)
  {
    scene->addTriangles(triangles);
  }

  Sphere::Sphere(const Point3df& center, DataType radius) :
    center(center), radius(radius)
  {
  }

  Sphere::~Sphere()
  {
  }
  
  Box::Box(const Point3df& corner1, const Point3df& corner2) :
  corner1(corner1), corner2(corner2)
  {
  }
  
  Box::~Box()
  {
  }
  
  Triangle::Triangle(const Point3df& corner1, const Point3df& corner2, const Point3df& corner3) :
  corner1(corner1), corner2(corner2), corner3(corner3), v0(corner3 - corner1), v1(corner2 - corner1), normal(v1.cross(v0)), color(Color::Constant(1.f)), reflection(0), diffuse(0)

  {
    normalize(normal);
  }
  
  Triangle::~Triangle()
  {
  }
  
  bool Triangle::intersect(const Ray& ray, float& dist) const
  {
    float coeff = ray.direction().dot(normal);
    if(std::abs(coeff) < std::numeric_limits<float>::epsilon())
      return false;
  
    float d = corner1.dot(normal);
    dist = - (ray.origin().dot(normal) - d) / coeff;
    
    Vector3df intersect = ray.origin() + ray.direction() * dist;

    Vector3df v2 = intersect - corner1;
    
    // Compute dot products
    float dot00 = v0.dot(v0);
    float dot01 = v0.dot(v1);
    float dot02 = v0.dot(v2);
    float dot11 = v1.dot(v1);
    float dot12 = v1.dot(v2);
    
    // Compute barycentric coordinates
    float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
    
    // Check if point is in triangle
    return (u >= 0) && (v >= 0) && (u + v < 1);
  }
  
  void Triangle::computeColorNormal(const Ray& ray, float dist, MaterialPoint& caracteristics) const
  {
    caracteristics.normal = normal;
  }
  
  BoundingBox Triangle::getBoundingBox() const
  {
    BoundingBox bb;
    
    bb.corner1 = corner1.array().min(corner2.array()).min(corner3.array());
    bb.corner2 = corner1.array().max(corner2.array()).max(corner3.array());
    
    return bb;
  }

  void Triangle::setColor(const Color& color)
  {
    this->color = color;
  }

  const Color& Triangle::getColor() const
  {
    return color;
  }

  void Triangle::setReflection(float reflection)
  {
    this->reflection = reflection;
  }

  float Triangle::getReflection() const
  {
    return reflection;
  }

  void Triangle::setDiffuse(float diffuse)
  {
    this->diffuse = diffuse;
  }

  float Triangle::getDiffuse() const
  {
    return diffuse;
  }
}
