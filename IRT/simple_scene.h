/**
 * \file simple_scene.h
 * Describes a simple scene, that is with no search accelerations
 */

#ifndef SIMPLESCENE
#define SIMPLESCENE

#include <memory>
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
  class _export_tools SimpleScene
  {
  private:
    /// Array for the primitives
    std::vector<std::unique_ptr<Primitive>> primitives;
    /// KD-tree
    KDTree<Primitive> tree;
    /// Array for the lights
    std::vector<std::unique_ptr<Light>> lights;
    
    BoundingBox bb;
    /// Ambient color
    Color ambient_color;

  public:
    /// Constructor
    SimpleScene();

    /// Destructor
    ~SimpleScene();

    SimpleScene(const SimpleScene&) = delete;
    SimpleScene& operator=(const SimpleScene&) = delete;

    /**
     * Returns a primitive
     * @param index is the index of the primitive to get
     * @return the asked primitive
     */
    Primitive* getPrimitive(unsigned long index);

    /**
     * Returns the bounding box
     * @return the bounding box
     */
    const BoundingBox& getBoundingBox() const;

        /**
     * Recomputes the bounding box
     */
    void computeBoundingBox();

    /**
     * Removes a primitive and returns it
     * @param index is the index of the primitive to get
     * @return the asked primitive
     */
    std::unique_ptr<Primitive> removePrimitive(unsigned long index);

    /**
     * Returns a light
     * @param index is the index of the light to get
     * @return the asked light
     */
    Light* getLight(unsigned long index);

    /**
     * Removes a light and returns it
     * @param index is the index of the light to get
     * @return the asked light
     */
    std::unique_ptr<Light> removeLight(unsigned long index);

    /**
    * Sets the ambient color
    * @param color is the color of the sphere
    */
    void setAmbientColor(const Color& color);

    const Color& getAmbientColor() const;

    /**
     * Returns the index of the first primitive that is hit by the ray
     * @param ray is the ray to test
     * @param dist is the distance to the primitive
     * @return the index of the hit primitive, else -1
     */
    Primitive* getFirstCollision(const Ray& ray, float& dist, float tfar, float tnear);
    
    /**
     * Returns the hit level in the tree
     * @param ray is the ray to test
     * @return the hit level
     */
    long getHitLevel(const Ray& ray, float tfar, float tnear);
    
    /**
     * Returns the hit distance in the tree
     * @param ray is the ray to test
     * @return the hit distance
     */
    long getHitDistance(const Ray& ray, float tfar, float tnear);

    /**
     * Computes the color
     * @param center is the point where the light will hit the primitive
     * @param characteristics is the characteristics to the primitive
     * @return the actual color of the point
     */
    const Color computeColor(const Point3df& center, const Vector3df& direction, const MaterialPoint& characteristics, const Primitive* primitive);

    /**
     * Tests if a ray collides with objects in the scene
     * @param ray is the ray to test
     * @param dist is the maximum distance to test
     * @return true if the ray hits a primitive before dist
     */
    bool testCollision(const Ray& ray, float dist);

    /**
     * Adds a new primitive to the scene
     * @param primitive is the primitive to add
     * @return the index of the primitive
     * @throw std::out_of_range if the primitive was already added
     */
    unsigned long addPrimitive(std::unique_ptr<Primitive> primitive);

    /**
     * Returns the index of the given primitive
     * @param primitive is the primitive to look for
     * @return the index of the primitive
     */
    unsigned long getPrimitiveIndex(Primitive* primitive);

    /**
     * Adds a new light to the scene
     * @param light is the light to add
     * @return True if the light was added, False if not
     * @throw std::out_of_range if the light was already added
     */
    unsigned long addLight(std::unique_ptr<Light> light);

    /**
     * Returns the index of the given light
     * @param light is the light to look for
     * @return the index of the light
     * @throw std::out_of_range if the light was not found
     */
    unsigned long getLightIndex(Light* light);
    
    /**
     * Returns the whole primitives vector
     * @return the primitives
     */
    std::vector<Primitive*> getPrimitives() const;
    
    /**
     * Returns the kd-tree
     * @return the kd-tree for modification
     */
    KDTree<Primitive>& getKDTree();
  };
}

#endif

