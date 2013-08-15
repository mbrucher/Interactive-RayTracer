/**
 * \file kdtree.h
 * The kd-tree implementation for fast triangle lookup
 */

#ifndef KDTREE
#define KDTREE

#include <iostream>
#include <list>
#include <vector>

#include "common.h"

namespace IRT
{
  /// The default class for the kd-tree
  template<class Triangle>
  class KDTree
  {
  public:
    /// Inside kd-tree node
    class KDTreeNode
    {
    private:
      /// Axis
      short axis;
      /// Indicates if the node is a leaf
      bool is_leaf;
      /// The triangles that are in this leaf
      const std::vector<Triangle*>* triangles;
      /// split position on an axis
      DataType split_position;
      /// Pointer to the left node
      KDTreeNode* left;
    public:
      KDTreeNode()
      : is_leaf(true), triangles(NULL), left(NULL)
      {
      }

      /**
       * Returns the axis
       * @return the axis
       */
      short getAxis() const
      {
        return axis;
      }

      /**
       * Sets the new axis
       * @param axis is the new axis
       */
      void setAxis(short axis)
      {
        this->axis = axis;
      }

      /// Returns true is the node is a leaf
      bool isLeaf() const
      {
        return is_leaf;
      }

      /**
       * Sets the fact that the node is a leaf or not
       * @param is_leaf indicates if the node will be a leaf, or not
       */
      void setLeaf(bool is_leaf)
      {
        this->is_leaf = is_leaf;
      }

      /**
       * Sets the container of triangles
       * @param triangles is the new triangles container
       */
      void setTriangles(const std::vector<Triangle*>* triangles)
      {
        this->triangles = triangles;
      }

      /**
       * Returns the inner triangles
       */
      const std::vector<Triangle*>* getTriangles() const
      {
        return triangles;
      }

      Triangle* getFirstCollision(const Ray& ray, float& dist) const
      {
        float min_dist = std::numeric_limits<float>::max();
        Triangle* min_triangle = NULL;

        for(typename std::vector<Triangle*>::const_iterator it = getTriangles()->begin(); it != getTriangles()->end(); ++it)
        {
          float cur_dist;
          bool test = (*it)->intersect(ray, cur_dist);

          if(test && (0.0001f < cur_dist) && (cur_dist < min_dist))
          {
            min_triangle = *it;
            dist = cur_dist;
          }
        }

        return min_triangle;
      }

      /// Returns the split position
      DataType getSplitPosition() const
      {
        return split_position;
      }

      /// Sets the split position for this node
      void setSplitPosition(DataType split_position)
      {
        this->split_position = split_position;
      }

      /// Return the left node
      KDTreeNode* leftNode() const
      {
        return left;
      }

      /// Returns the right node
      KDTreeNode* rightNode() const
      {
        return left + 1;
      }

      /**
       * Ses the left and by consequence right nodes
       * @param left is the new left node
       */
      void setLeftNode(KDTreeNode* left)
      {
        this->left = left;
      }
    };

    /// Stack for the ray traversal
    struct KDStack
    {
      const KDTreeNode* node;
      DataType t;
      Vector3df pb;
      int previous;
    };
    
    /// Stack for stats
    struct KDStackStats
    {
      const KDTreeNode* node;
      DataType t;
      Vector3df pb;
      int previous;
      long level;
    };

  private:
    /// The triangles that the kd-tree will browse
    std::vector<Triangle*> triangles;
    /// All the actual nodes of the binary tree
    std::vector<KDTreeNode> nodes;
    std::list<std::vector<Triangle*> > nodes_triangles;

    KDTree(const KDTree& tree);

    int mod[5];
  public:
    /**
   * Constructs a kdtree for some triangles
   * @param triangles is the triangles container
   */
    KDTree()
    {
      mod[0] = 0, mod[1] = 1, mod[2] = 2, mod[3] = 0, mod[4] = 1;
    }

    /// Destructor
    ~KDTree()
    {
    }

    void setTriangles(const std::vector<Triangle*>& triangles)
    {
      this->triangles = triangles;
      KDTreeNode node;
      node.setLeaf(true);
      node.setTriangles(&triangles);

      nodes.clear();
      nodes.reserve(3 * triangles.size());
      nodes.push_back(node);
      nodes_triangles.clear();
    }

    std::vector<KDTreeNode>& getNodes()
    {
      return nodes;
    }

    KDTreeNode* getPairEmptyNodes()
    {
      int size = nodes.size();

      nodes.resize(size + 2);

      return &nodes[size];
    }

    std::vector<Triangle*>* getNewTrianglesStore()
    {
      nodes_triangles.push_back(std::vector<Triangle*>());
      return &nodes_triangles.back();
    }

    void removeNewTrianglesStore(const std::vector<Triangle*>* store)
    {
      for(typename std::list<std::vector<Triangle*> >::iterator it = nodes_triangles.begin(); it != nodes_triangles.end(); ++it)
      {
        if(store == &(*it))
        {
          nodes_triangles.erase(it);
          return;
        }
      }
    }
    
    struct DefaultTraversal
    {
      typedef Triangle* Return;
      typedef KDStack Stack;
      Return returnFrom(Triangle* triangle)
      {
        return triangle;
      }
      Return defaultReturn()
      {
        return NULL;
      }

      void update()
      {
      }
      
      void updateFrom(const Stack& stack)
      {
      }

      void updateTo(Stack& stack) const
      {
      }
    };
    
    struct HitLevelTraversal
    {
      typedef int Return;
      typedef KDStackStats Stack;
      HitLevelTraversal()
      :level(0)
      {
        
      }
      
      Return returnFrom(Triangle* triangle)
      {
        return level;
      }
      int level;
      Return defaultReturn()
      {
        return 1;
      }
      
      void update()
      {
        ++level;
      }
      
      void updateFrom(const Stack& stack)
      {
        level = stack.level;
      }

      void updateTo(Stack& stack) const
      {
        stack.level = level;
      }
    };
    
    /**
     * Returns the first collision from a vector of Triangles
     * @param ray is the ray to test
     * @param dist is the distance to the triangle
     * @return the index of the hit triangle, else -1
     */
    template<class TraversalStructure>
    typename TraversalStructure::Return getFirstCollision(const Ray& ray, float& dist, float tnear, float tfar) const
    {
      TraversalStructure traversal;
      typename TraversalStructure::Stack stack[50];

      const KDTreeNode* current_node = &nodes[0];
      int entrypoint = 0;
      int exitpoint = 1;

      stack[entrypoint].t = tnear;
      if (tnear > 0.0f)
      {
        stack[entrypoint].pb = ray.origin() + ray.direction() * tnear;
      }
      else
      {
        stack[entrypoint].pb = ray.origin();
      }
      stack[exitpoint].t = tfar;
      stack[exitpoint].pb = ray.origin() + ray.direction() * tfar;
      stack[exitpoint].node = NULL;
      traversal.updateTo(stack[entrypoint]);

      while(current_node != NULL)
      {
        while(!current_node->isLeaf())
        {
          current_node = splitNode<TraversalStructure>(ray, current_node, entrypoint, exitpoint, stack, traversal);
        }

        Triangle* triangle = current_node->getFirstCollision(ray, dist);
        if(triangle != NULL && dist <= stack[exitpoint].t)
        {
          return traversal.returnFrom(triangle);
        }
        entrypoint = exitpoint;
        current_node = stack[exitpoint].node;
        traversal.updateFrom(stack[exitpoint]);
        exitpoint = stack[exitpoint].previous;
      }

      return traversal.defaultReturn();
    }
    
    template<class TraversalStructure>
    const KDTreeNode* splitNode(const Ray& ray, const KDTreeNode* current_node, int& entrypoint, int& exitpoint, typename TraversalStructure::Stack* stack, TraversalStructure& traversal) const
    {
      const KDTreeNode* far_node;
      
      int axis = current_node->getAxis();
      DataType splitpos = current_node->getSplitPosition();
      if (stack[entrypoint].pb(axis) <= splitpos)
      {
        if (stack[exitpoint].pb(axis) <= splitpos)
        {
          traversal.update();
          return current_node->leftNode();
        }
        traversal.update();
        far_node = current_node->rightNode();
        current_node = current_node->leftNode();
      }
      else
      {
        if (stack[exitpoint].pb(axis) >= splitpos)
        {
          traversal.update();
          return current_node->rightNode();
        }
        traversal.update();
        far_node = current_node->leftNode();
        current_node = current_node->rightNode();
      }
      DataType t = (splitpos - ray.origin()(axis)) / ray.direction()(axis);
      int tmp = exitpoint++;
      if (exitpoint == entrypoint)
      {
        ++exitpoint;
      }
      stack[exitpoint].previous = tmp;
      stack[exitpoint].t = t;
      stack[exitpoint].node = far_node;
      stack[exitpoint].pb(axis) = splitpos;
      traversal.updateTo(stack[exitpoint]);
      int nextaxis = mod[axis + 1];
      int prevaxis = mod[axis + 2];
      stack[exitpoint].pb(nextaxis) = ray.origin()(nextaxis) + t * ray.direction()(nextaxis);
      stack[exitpoint].pb(prevaxis) = ray.origin()(prevaxis) + t * ray.direction()(prevaxis);
      
      return current_node;
    }
  };
}

#endif
