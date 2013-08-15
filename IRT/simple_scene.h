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
  class Triangle;
  class Light;
  struct MaterialPoint;

  /// Description of a simple scene
  class SimpleScene
  {
  private:
    /// Array for the triangles
    std::vector<Triangle*> triangles;
    /// KD-tree
    KDTree<Triangle> tree;
    /// Array for the lights
    std::vector<Light*> lights;
    
    BoundingBox bb;

  public:
    /// Constructor
    _export_tools SimpleScene();

    /// Destructor
    _export_tools ~SimpleScene();

    /**
     * Returns a triangle
     * @param index is the index of the triangle to get
     * @return the asked triangle
     */
    _export_tools Triangle* getTriangle(unsigned long index);

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
     * Removes a triangle and returns it
     * @param index is the index of the triangle to get
     * @return the asked triangle
     */
    _export_tools Triangle* removeTriangle(unsigned long index);

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
     * Returns the index of the first triangle that is hit by the ray
     * @param ray is the ray to test
     * @param dist is the distance to the triangle
     * @return the index of the hit triangle, else -1
     */
    _export_tools Triangle* getFirstCollision(const Ray& ray, float& dist, float tfar, float tnear);
    
    /**
     * Returns the hit level in the tree
     * @param ray is the ray to test
     * @return the hit level
     */
    _export_tools long getHitLevel(const Ray& ray, float tfar, float tnear);
    
    /**
     * Returns the hit distance in the tree
     * @param ray is the ray to test
     * @return the hit distance
     */
    _export_tools long getHitDistance(const Ray& ray, float tfar, float tnear);

    /**
     * Computes the color
     * @param center is the point where the light will hit the triangle
     * @param caracteristics is the caracteristics to the triangle
     * @return the actual color of the point
     */
    _export_tools const Color computeColor(const Point3df& center, const MaterialPoint& caracteristics, const Triangle* triangle);

    /**
     * Tests if a ray collides with objects in the scene
     * @param ray is the ray to test
     * @param dist is the maximum distance to test
     * @return true if the ray hits a triangle before dist
     */
    _export_tools bool testCollision(const Ray& ray, float dist);

    /**
     * Adds a new triangle to the scene
     * @param triangle is the triangle to add
     * @return the index of the triangle
     * @throw std::out_of_range if the triangle was already added
     */
    _export_tools unsigned long addTriangle(Triangle* triangle);
    /**
     * Adds several new triangles to the scene
     * @param triangles is the triangles to add
     * @return the indices of the triangles
     * @throw std::out_of_range if a triangle was already added
     */
    _export_tools std::vector<unsigned long> addTriangles(const std::vector<IRT::Triangle*>& triangles);

    /**
     * Returns the index of the given triangle
     * @param triangle is the triangle to look for
     * @return the index of the triangle
     */
    _export_tools unsigned long getTriangleIndex(Triangle* triangle);

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
     * Returns the whole triangles vector
     * @return the triangles
     */
    _export_tools const std::vector<Triangle*>& getTriangles() const;
    
    /**
     * Returns the kd-tree
     * @return the kd-tree for modification
     */
    _export_tools KDTree<Triangle>& getKDTree();
  };
}

#endif

