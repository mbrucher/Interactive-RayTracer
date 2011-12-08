/**
 * \file primitives.cpp
 * Implementation of primitives
 */

#include "primitives.h"
#include "common.h"

namespace IRT
{
  MaterialPoint::MaterialPoint()
  :normal(Normal3df::Zero())
  {
  }

  Primitive::Primitive()
  :color(Color::Constant(1.f)), reflection(0), diffuse(0)
  {
  }

  void Primitive::setColor(const Color& color)
  {
    this->color = color;
  }

  const Color& Primitive::getColor() const
  {
    return color;
  }

  void Primitive::setReflection(float reflection)
  {
    this->reflection = reflection;
  }

  float Primitive::getReflection() const
  {
    return reflection;
  }

  void Primitive::setDiffuse(float diffuse)
  {
    this->diffuse = diffuse;
  }

  float Primitive::getDiffuse() const
  {
    return diffuse;
  }

  Sphere::Sphere(const Point3df& center, DataType radius) :
    center(center), radius(radius)
  {
  }

  Sphere::~Sphere()
  {
  }

  bool Sphere::intersect(const Ray& ray, DataType& dist) const
  {
    const Vector3df& vector = ray.origin() - center;
    DataType B = -(ray.direction().dot(vector));
    DataType C = norm2(vector) - radius * radius;

    DataType delta = (B * B - C);

    if (delta < 0.f)
      return false;
    DataType disc = std::sqrt(delta);
    if ((dist = (B - disc)) < 0.)
      dist = (B + disc);
    return true;
  }

  void Sphere::computeColorNormal(const Ray& ray, DataType dist, MaterialPoint& caracteristics) const
  {
    caracteristics.normal = ray.origin() + dist * ray.direction() - center;
    normalize(caracteristics.normal);
  }

  BoundingBox Sphere::getBoundingBox() const
  {
    BoundingBox bb;

    bb.corner1 = center.array() - radius;
    bb.corner2 = center.array() + radius;

    return bb;
  }

  Box::Box(const Point3df& corner1, const Point3df& corner2) :
    corner1(corner1), corner2(corner2)
  {
  }

  Box::~Box()
  {
  }

  bool Box::intersect(const Ray& ray, float& dist) const
  {
    DataType tnear, tfar;
    BoundingBox bb;
    bb.corner1 = corner1;
    bb.corner2 = corner2;

    bool result = bb.getEntryExitDistances(ray, tnear, tfar);

    if(result)
    {
      dist = tnear;
    }

    return result;
  }

  void Box::computeColorNormal(const Ray& ray, float dist, MaterialPoint& caracteristics) const
  {
    Vector3df collide(ray.origin() + dist * ray.direction());

    caracteristics.normal = Normal3df::Zero();
    for(int i = 0; i < 3; ++i)
    {
      if(std::abs(collide(i) - corner1(i)) <= std::numeric_limits<DataType>::epsilon())
      {
        caracteristics.normal(i) = -1;
      }
      if(std::abs(collide(i) - corner2(i)) <= std::numeric_limits<DataType>::epsilon())
      {
        caracteristics.normal(i) = 1;
      }
    }
  }

  BoundingBox Box::getBoundingBox() const
  {
    BoundingBox bb;

    bb.corner1 = corner1;
    bb.corner2 = corner2;

    return bb;
  }
}
