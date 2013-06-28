/**
 * \file simple_scene.h
 * Describes a simple scene, that is with no search accelerations
 */

#ifndef SIMPLESCENE
#define SIMPLESCENE

#include <vector>

#include "common.h"
#include "ray.h"
#include "bounding_box.h"
#include "kdtree.h"

namespace IRT
{
  class Primitive;
  class Light;
  struct MaterialPoint;

  /// Description of a simple scene
  class SimpleScene
  {
  private:
    /// Array for the primitives
    std::vector<Primitive*> primitives;
    /// KD-tree
    KDTree<Primitive> tree;
    /// Array for the lights
    std::vector<Light*> lights;
    
    BoundingBox bb;

  public:
    /// Constructor
    _export_tools SimpleScene();

    /// Destructor
    _export_tools ~SimpleScene();

    /**
     * Returns a primitive
     * @param index is the index of the primitive to get
     * @return the asked primitive
     */
    _export_tools Primitive* getPrimitive(unsigned long index);

    /**
     * Returns the bounding box
     * @return the bounding box
     */
    _export_tools const BoundingBox& getBoundingBox() const;

        /**
     * Recomputes the bounding box
     */
    _export_tools void computeBoundingBox();

    /**
     * Removes a primitive and returns it
     * @param index is the index of the primitive to get
     * @return the asked primitive
     */
    _export_tools Primitive* removePrimitive(unsigned long index);

    /**
     * Returns a light
     * @param index is the index of the light to get
     * @return the asked light
     */
    _export_tools Light* getLight(unsigned long index);

    /**
     * Removes a light and returns it
     * @param index is the index of the light to get
     * @return the asked light
     */
    _export_tools Light* removeLight(unsigned long index);

    /**
     * Returns the index of the first primitive that is hit by the ray
     * @param ray is the ray to test
     * @param dist is the distance to the primitive
     * @return the index of the hit primitive, else -1
     */
    _export_tools Primitive* getFirstCollision(const Ray& ray, float& dist, float tfar, float tnear);
    
    /**
     * Returns the hit level in the tree
     * @param ray is the ray to test
     * @return the hit level
     */
    _export_tools long getHitLevel(const Ray& ray, float tfar, float tnear);

    /**
     * Computes the color
     * @param center is the point where the light will hit the primitive
     * @param caracteristics is the caracteristics to the primitive
     * @return the actual color of the point
     */
    _export_tools const Color computeColor(const Point3df& center, const MaterialPoint& caracteristics, const Primitive* primitive);

    /**
     * Tests if a ray collides with objects in the scene
     * @param ray is the ray to test
     * @param dist is the maximum distance to test
     * @return true if the ray hits a primitive before dist
     */
    _export_tools bool testCollision(const Ray& ray, float dist);

    /**
     * Adds a new primitive to the scene
     * @param primitive is the primitive to add
     * @return the index of the primitive
     * @throw std::out_of_range if the primitive was already added
     */
    _export_tools unsigned long addPrimitive(Primitive* primitive);

    /**
     * Returns the index of the given primitive
     * @param primitive is the primitive to look for
     * @return the index of the primitive
     */
    _export_tools unsigned long getPrimitiveIndex(Primitive* primitive);

    /**
     * Adds a new light to the scene
     * @param light is the light to add
     * @return True if the light was added, False if not
     * @throw std::out_of_range if the light was already added
     */
    _export_tools unsigned long addLight(Light* light);

    /**
     * Returns the index of the given light
     * @param light is the light to look for
     * @return the index of the light
     * @throw std::out_of_range if the light was not found
     */
    _export_tools unsigned long getLightIndex(Light* light);
    
    /**
     * Returns the whole primitives vector
     * @return the primitives
     */
    _export_tools const std::vector<Primitive*>& getPrimitives() const;
    
    /**
     * Returns the kd-tree
     * @return the kd-tree for modification
     */
    _export_tools KDTree<Primitive>& getKDTree();
  };
}

#endif

