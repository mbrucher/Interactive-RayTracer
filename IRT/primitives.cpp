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

  Sphere::Sphere(const Point3df& center, DataType radius, int refinement) :
    center(center), radius(radius)
  {
    std::list<TriPoints> list = createMesh();
    for(int i = 0; i < refinement; ++i)
      refine(list);
    generateTriangles(list);
  }

  Sphere::~Sphere()
  {
  }
  
  std::list<Primitive::TriPoints> Sphere::createMesh()
  {
    std::list<TriPoints> list;
    DataType t = t = (1.0 + std::sqrt(5.0)) / 2.0;
    
    std::vector<Point3df> initialPoints;
    
    Point3df pt;
    pt << -1, t, 0;
    normalize(pt);
    initialPoints.push_back(pt);
    pt << 1, t, 0;
    normalize(pt);
    initialPoints.push_back(pt);
    pt << -1, -t, 0;
    normalize(pt);
    initialPoints.push_back(pt);
    pt << 1, -t, 0;
    normalize(pt);
    initialPoints.push_back(pt);
    pt << 0, -1, t;
    normalize(pt);
    initialPoints.push_back(pt);
    pt << 0, 1, t;
    normalize(pt);
    initialPoints.push_back(pt);
    pt << 0, -1, -t;
    normalize(pt);
    initialPoints.push_back(pt);
    pt << 0, 1, -t;
    normalize(pt);
    initialPoints.push_back(pt);
    pt << t, 0, -1;
    normalize(pt);
    initialPoints.push_back(pt);
    pt << t, 0, 1;
    normalize(pt);
    initialPoints.push_back(pt);
    pt << -t, 0, -1;
    normalize(pt);
    initialPoints.push_back(pt);
    pt << -t, 0, 1;
    normalize(pt);
    initialPoints.push_back(pt);
    
    list.push_back(TriPoints(initialPoints[0], initialPoints[11], initialPoints[15]));
    list.push_back(TriPoints(initialPoints[0], initialPoints[5], initialPoints[1]));
    list.push_back(TriPoints(initialPoints[0], initialPoints[1], initialPoints[7]));
    list.push_back(TriPoints(initialPoints[0], initialPoints[7], initialPoints[10]));
    list.push_back(TriPoints(initialPoints[0], initialPoints[10], initialPoints[11]));

    list.push_back(TriPoints(initialPoints[1], initialPoints[5], initialPoints[9]));
    list.push_back(TriPoints(initialPoints[5], initialPoints[11], initialPoints[4]));
    list.push_back(TriPoints(initialPoints[11], initialPoints[10], initialPoints[2]));
    list.push_back(TriPoints(initialPoints[10], initialPoints[7], initialPoints[6]));
    list.push_back(TriPoints(initialPoints[7], initialPoints[1], initialPoints[8]));

    list.push_back(TriPoints(initialPoints[3], initialPoints[9], initialPoints[4]));
    list.push_back(TriPoints(initialPoints[3], initialPoints[4], initialPoints[2]));
    list.push_back(TriPoints(initialPoints[3], initialPoints[2], initialPoints[6]));
    list.push_back(TriPoints(initialPoints[3], initialPoints[6], initialPoints[8]));
    list.push_back(TriPoints(initialPoints[3], initialPoints[8], initialPoints[9]));

    list.push_back(TriPoints(initialPoints[4], initialPoints[9], initialPoints[5]));
    list.push_back(TriPoints(initialPoints[2], initialPoints[4], initialPoints[11]));
    list.push_back(TriPoints(initialPoints[6], initialPoints[2], initialPoints[10]));
    list.push_back(TriPoints(initialPoints[8], initialPoints[6], initialPoints[7]));
    list.push_back(TriPoints(initialPoints[9], initialPoints[8], initialPoints[1]));

    return list;
  }
  
  void Sphere::refine(std::list<Primitive::TriPoints>& list)
  {
    std::list<Primitive::TriPoints> newlist;
    
    for(auto it = list.begin(); it != list.end(); ++it)
    {
      auto middle0 = middlePoint(it->p0, it->p1);
      auto middle1 = middlePoint(it->p1, it->p2);
      auto middle2 = middlePoint(it->p2, it->p0);
      newlist.push_back(TriPoints(it->p0, middle0, middle2));
      newlist.push_back(TriPoints(it->p1, middle1, middle0));
      newlist.push_back(TriPoints(it->p2, middle2, middle1));
      newlist.push_back(TriPoints(middle0, middle1, middle2));
    }
    
    list.swap(newlist);
  }
  
  void Sphere::generateTriangles(std::list<Primitive::TriPoints>& list)
  {
    for(auto it = list.begin(); it != list.end(); ++it)
    {
      triangles.push_back(new Triangle(it->p0 * radius + center, it->p1 * radius + center, it->p2 * radius + center));
    }
  }

  Point3df Sphere::middlePoint(const Point3df& p1, const Point3df& p2)
  {
    Point3df middle = (p1 + p2) / 2;
    normalize(middle);
    return middle;
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
