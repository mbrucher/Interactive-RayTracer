/**
 * \file simple_scene.cpp
 * Implementation of the simple scene
 */

#include <stdexcept>

#include "simple_scene.h"
#include "primitives.h"
#include "light.h"

#include "build_kdtree.h"

namespace IRT
{
  SimpleScene::SimpleScene()
    :triangles(), lights()
  {
    bb.corner1 = Point3df::Constant(std::numeric_limits<float>::max());
    bb.corner2 = Point3df::Constant(std::numeric_limits<float>::min());
  }

  SimpleScene::~SimpleScene()
  {
    for(std::vector<Triangle*>::const_iterator it = triangles.begin(); it != triangles.end(); ++it)
      delete *it;
    for(std::vector<Light*>::const_iterator it = lights.begin(); it != lights.end(); ++it)
      delete *it;
  }

  Triangle* SimpleScene::getTriangle(unsigned long index)
  {
    return triangles[index];
  }

  Triangle* SimpleScene::removeTriangle(unsigned long index)
  {
    std::vector<Triangle*>::iterator it = triangles.begin();
    std::advance(it, index);
    Triangle* triangle = *it;
    triangles.erase(it);
    return triangle;
  }

  const BoundingBox& SimpleScene::getBoundingBox() const
  {
    return bb;
  }

  void SimpleScene::computeBoundingBox()
  {
    std::vector<Triangle*>::iterator it = triangles.begin();
    bb = (*it)->getBoundingBox();

    for(++it; it != triangles.end(); ++it)
    {
      BoundingBox bb_bis = (*it)->getBoundingBox();
      bb.corner1 = bb.corner1.array().min(bb_bis.corner1.array());
      bb.corner2 = bb.corner2.array().max(bb_bis.corner2.array());
    }
  }

  Light* SimpleScene::getLight(unsigned long index)
  {
    return lights[index];
  }

  Light* SimpleScene::removeLight(unsigned long index)
  {
    std::vector<Light*>::iterator it = lights.begin();
    std::advance(it, index);
    Light* light = *it;
    lights.erase(it);
    return light;
  }
  
  Triangle* SimpleScene::getFirstCollision(const Ray& ray, float& dist, float tnear, float tfar)
  {
    return tree.getFirstCollision<KDTree<Triangle>::DefaultTraversal>(ray, dist, tnear, tfar);
  }
  
  long SimpleScene::getHitLevel(const Ray& ray, float tnear, float tfar)
  {
    float dist;
    return tree.getFirstCollision<KDTree<Triangle>::HitLevelTraversal>(ray, dist, tnear, tfar);
  }
  
  long SimpleScene::getHitDistance(const Ray& ray, float tnear, float tfar)
  {
    float dist;
    tree.getFirstCollision<KDTree<Triangle>::HitLevelTraversal>(ray, dist, tnear, tfar);
    return dist;
  }

  const Color SimpleScene::computeColor(const Point3df& center, const MaterialPoint& caracteristics, const Triangle* triangle)
  {
    Color t_color(Color::Zero());
    for(std::vector<Light*>::const_iterator it = lights.begin(); it != lights.end(); ++it)
    {
      Vector3df path = (*it)->getCenter() - center;
      float pathSize = std::sqrt(norm2(path));
      path = path.cwiseProduct(Vector3df::Constant(1/pathSize));
      Ray ray(center, path);
      if(testCollision(ray, pathSize))
        continue;

      float cosphi = path.dot(caracteristics.normal) * triangle->getDiffuse();
      if(cosphi < 0.)
        continue;
      t_color += (triangle->getColor() * cosphi).cwiseProduct((*it)->computeColor(ray, pathSize));
    }

    return t_color;
  }

  bool SimpleScene::testCollision(const Ray& ray, float dist)
  {
    return (tree.getFirstCollision<KDTree<Triangle>::DefaultTraversal>(ray, dist, 0, dist) != NULL);
  }

  unsigned long SimpleScene::addTriangle(Triangle* triangle)
  {
    if(std::find(triangles.begin(), triangles.end(), triangle) != triangles.end())
      throw std::out_of_range("Triangle already added");

    BoundingBox triangle_bb = triangle->getBoundingBox();
    bb.corner1 = bb.corner1.array().min(triangle_bb.corner1.array());
    bb.corner2 = bb.corner2.array().max(triangle_bb.corner2.array());

    triangles.push_back(triangle);
    return triangles.size() - 1;
  }

  std::vector<unsigned long> SimpleScene::addTriangles(const std::vector<IRT::Triangle*>& triangles)
  {
    std::vector<unsigned long> indices;
    
    for(auto it = triangles.begin(); it != triangles.end(); ++it)
    {
      indices.push_back(addTriangle(*it));
    }

    return indices;
  }

  unsigned long SimpleScene::getTriangleIndex(Triangle* triangle)
  {
    std::vector<Triangle*>::const_iterator it;
    if((it = std::find(triangles.begin(), triangles.end(), triangle)) != triangles.end())
      return it - triangles.begin();

    throw std::out_of_range("Triangle not found!");
  }

  unsigned long SimpleScene::addLight(Light* light)
  {
    if(std::find(lights.begin(), lights.end(), light) != lights.end())
      throw std::out_of_range("Light already added");

    lights.push_back(light);
    return lights.size() - 1;
  }

  unsigned long SimpleScene::getLightIndex(Light* light)
  {
    std::vector<Light*>::const_iterator it;
    if((it = std::find(lights.begin(), lights.end(), light)) != lights.end())
      return it - lights.begin();

    throw std::out_of_range("Light not found!");
  }

  const std::vector<Triangle*>& SimpleScene::getTriangles() const
  {
    return triangles;
  }

  KDTree<Triangle>& SimpleScene::getKDTree()
  {
    return tree;
  }
}
