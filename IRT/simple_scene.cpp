/**
 * \file simple_scene.cpp
 * Implementation of the simple scene
 */

#include <iostream>
#include <stdexcept>

#include "simple_scene.h"
#include "primitives.h"
#include "light.h"

#include "build_kdtree.h"

namespace IRT
{
  SimpleScene::SimpleScene()
    :primitives(), lights()
  {
    bb.corner1 = Point3df::Constant(std::numeric_limits<float>::max());
    bb.corner2 = Point3df::Constant(std::numeric_limits<float>::min());
  }

  SimpleScene::~SimpleScene()
  {
    for(std::vector<Primitive*>::const_iterator it = primitives.begin(); it != primitives.end(); ++it)
      delete *it;
    for(std::vector<Light*>::const_iterator it = lights.begin(); it != lights.end(); ++it)
      delete *it;
  }

  Primitive* SimpleScene::getPrimitive(unsigned long index)
  {
    return primitives[index];
  }

  Primitive* SimpleScene::removePrimitive(unsigned long index)
  {
    std::vector<Primitive*>::iterator it = primitives.begin();
    std::advance(it, index);
    Primitive* primitive = *it;
    primitives.erase(it);
    return primitive;
  }

  const BoundingBox& SimpleScene::getBoundingBox() const
  {
    return bb;
  }

  void SimpleScene::computeBoundingBox()
  {
    std::vector<Primitive*>::iterator it = primitives.begin();
    bb = (*it)->getBoundingBox();

    for(++it; it != primitives.end(); ++it)
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
  
  Primitive* SimpleScene::getFirstCollision(const Ray& ray, float& dist, float tnear, float tfar)
  {
    return tree.getFirstCollision(ray, dist, tnear, tfar);
  }
  
  long SimpleScene::getHitLevel(const Ray& ray, float tnear, float tfar)
  {
    return tree.getHitLevel(ray, tnear, tfar);
  }

  const Color SimpleScene::computeColor(const Point3df& center, const MaterialPoint& caracteristics, const Primitive* primitive)
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

      float cosphi = path.dot(caracteristics.normal) * primitive->getDiffuse();
      if(cosphi < 0.)
        continue;
      t_color += (primitive->getColor() * cosphi).cwiseProduct((*it)->computeColor(ray, pathSize));
    }

    return t_color;
  }

  bool SimpleScene::testCollision(const Ray& ray, float dist)
  {
    return (tree.getFirstCollision(ray, dist, 0, dist) != NULL);
  }

  unsigned long SimpleScene::addPrimitive(Primitive* primitive)
  {
    if(std::find(primitives.begin(), primitives.end(), primitive) != primitives.end())
      throw std::out_of_range("Primitive already added");

    BoundingBox primitive_bb = primitive->getBoundingBox();
    bb.corner1 = bb.corner1.array().min(primitive_bb.corner1.array());
    bb.corner2 = bb.corner2.array().max(primitive_bb.corner2.array());

    primitives.push_back(primitive);
    return primitives.size() - 1;
  }

  unsigned long SimpleScene::getPrimitiveIndex(Primitive* primitive)
  {
    std::vector<Primitive*>::const_iterator it;
    if((it = std::find(primitives.begin(), primitives.end(), primitive)) != primitives.end())
      return it - primitives.begin();

    throw std::out_of_range("Primitive not found!");
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

  const std::vector<Primitive*>& SimpleScene::getPrimitives() const
  {
    return primitives;
  }

  KDTree<Primitive>& SimpleScene::getKDTree()
  {
    return tree;
  }
}
