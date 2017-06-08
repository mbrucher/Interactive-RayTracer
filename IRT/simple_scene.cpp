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
    :primitives(), lights()
  {
    bb.corner1 = Point3df::Constant(std::numeric_limits<float>::max());
    bb.corner2 = Point3df::Constant(std::numeric_limits<float>::min());
  }

  SimpleScene::~SimpleScene()
  {
  }

  Primitive* SimpleScene::getPrimitive(unsigned long index)
  {
    return primitives[index].get();
  }

  std::unique_ptr<Primitive> SimpleScene::removePrimitive(unsigned long index)
  {
    auto it = primitives.begin();
    std::advance(it, index);
    auto primitive = std::move(*it);
    primitives.erase(it);
    return primitive;
  }

  const BoundingBox& SimpleScene::getBoundingBox() const
  {
    return bb;
  }

  void SimpleScene::computeBoundingBox()
  {
    auto it = primitives.begin();
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
    return lights[index].get();
  }

  std::unique_ptr<Light> SimpleScene::removeLight(unsigned long index)
  {
    auto it = lights.begin();
    std::advance(it, index);
    auto light = std::move(*it);
    lights.erase(it);
    return light;
  }
  
  Primitive* SimpleScene::getFirstCollision(const Ray& ray, float& dist, float tnear, float tfar)
  {
    return tree.getFirstCollision<KDTree<Primitive>::DefaultTraversal>(ray, dist, tnear, tfar);
  }
  
  long SimpleScene::getHitLevel(const Ray& ray, float tnear, float tfar)
  {
    float dist;
    return tree.getFirstCollision<KDTree<Primitive>::HitLevelTraversal>(ray, dist, tnear, tfar);
  }
  
  long SimpleScene::getHitDistance(const Ray& ray, float tnear, float tfar)
  {
    float dist;
    tree.getFirstCollision<KDTree<Primitive>::HitLevelTraversal>(ray, dist, tnear, tfar);
    return dist;
  }

  const Color SimpleScene::computeColor(const Point3df& center, const MaterialPoint& characteristics, const Primitive* primitive)
  {
    Color t_color(Color::Zero());
    for(auto& light: lights)
    {
      Vector3df path = light->getCenter() - center;
      float pathSize = std::sqrt(norm2(path));
      path = path.cwiseProduct(Vector3df::Constant(1/pathSize));
      Ray ray(center, path);
      if(testCollision(ray, pathSize))
        continue;

      float cosphi = path.dot(characteristics.normal) * primitive->getDiffuse();
      if(cosphi < 0.)
        continue;
      t_color += (primitive->getColor() * cosphi).cwiseProduct(light->computeColor(ray, pathSize));
    }

    return t_color;
  }

  bool SimpleScene::testCollision(const Ray& ray, float dist)
  {
    return (tree.getFirstCollision<KDTree<Primitive>::DefaultTraversal>(ray, dist, 0, dist) != nullptr);
  }

  unsigned long SimpleScene::addPrimitive(std::unique_ptr<Primitive> primitive)
  {
    BoundingBox primitive_bb = primitive->getBoundingBox();
    bb.corner1 = bb.corner1.array().min(primitive_bb.corner1.array());
    bb.corner2 = bb.corner2.array().max(primitive_bb.corner2.array());

    primitives.push_back(std::move(primitive));
    return primitives.size() - 1;
  }

  unsigned long SimpleScene::getPrimitiveIndex(Primitive* primitive)
  {
    auto it = std::find_if(primitives.begin(), primitives.end(), [primitive](const auto& _primitive){return _primitive.get() == primitive; });
    if(it != primitives.end())
      return it - primitives.begin();

    throw std::out_of_range("Primitive not found!");
  }

  unsigned long SimpleScene::addLight(std::unique_ptr<Light> light)
  {
    lights.push_back(std::move(light));
    return lights.size() - 1;
  }

  unsigned long SimpleScene::getLightIndex(Light* light)
  {
    auto it = std::find_if(lights.begin(), lights.end(), [light](const auto& _light) {return _light.get() == light; });
    if (it != lights.end())
      return it - lights.begin();

    throw std::out_of_range("Light not found!");
  }

  std::vector<Primitive*> SimpleScene::getPrimitives() const
  {
    std::vector<Primitive*> result;
    for(auto& primitive: primitives)
      result.push_back(primitive.get());
    return result;
  }

  KDTree<Primitive>& SimpleScene::getKDTree()
  {
    return tree;
  }
}
