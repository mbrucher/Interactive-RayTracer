/**
 * \file build_kdtree.h
 * The kd-tree implementation for fast triangle lookup
 */

#ifndef BUILDKDTREE
#define BUILDKDTREE

#include <set>

#include "simple_scene.h"
#include "kdtree.h"

#ifdef max
#undef max
#endif

namespace IRT
{
  struct BuildKDTree
  {
    static void custom_build(IRT::SimpleScene* scene, int remaining_depth, int remaining_failures, DataType enhancement_ratio_failure)
    {
      KDTree<Triangle>& tree = scene->getKDTree();
      tree.setTriangles(scene->getTriangles());
      subdivide(tree, &tree.getNodes()[0], scene->getBoundingBox(), remaining_depth, remaining_failures, enhancement_ratio_failure);
    }

    static void automatic_build(IRT::SimpleScene* scene)
    {
      // Using Havran's values
      DataType k1 = 1.2;
      DataType k2 = 2.0;
      DataType K1 = 1.;
      DataType K2 = .2;

      int remaining_depth = static_cast<int>(std::ceil(k1 * std::log(static_cast<DataType>(scene->getTriangles().size())) + k2));
      int remaining_failures = static_cast<int>(std::ceil(K1 + remaining_depth * K2));
      DataType enhancement_ratio_failure = .75;

      custom_build(scene, remaining_depth, remaining_failures, enhancement_ratio_failure);
    }

    static void subdivide(KDTree<Triangle>& tree, KDTree<Triangle>::KDTreeNode* node, const BoundingBox& bb, int remaining_depth, int remaining_failures, DataType enhancement_ratio_failure)
    {
      const std::set<std::pair<int, DataType> >& split_positions = getSplitPositions(node, bb);

      DataType lowest_cost = std::numeric_limits<DataType>::max();
      std::pair<int, DataType> lowest_split = std::make_pair(-1, 0.);
      std::vector<Triangle*> right_triangles, left_triangles;

      for(std::set<std::pair<int, DataType> >::const_iterator it = split_positions.begin(); it != split_positions.end(); ++it)
      {
        std::vector<Triangle*> right_triangles_test, left_triangles_test;

        DataType new_cost = computeCost(it->first, it->second, bb, node->getTriangles(), right_triangles_test, left_triangles_test);
        new_cost = (new_cost + 0.3) / (bb.SAH() * node->getTriangles()->size());

        if(new_cost < lowest_cost)
        {
          right_triangles_test.swap(right_triangles);
          left_triangles_test.swap(left_triangles);
          lowest_split = *it;
          lowest_cost = new_cost;
        }
      }

      if(lowest_split.first != -1 && (lowest_cost < enhancement_ratio_failure || --remaining_failures >= 0))
      {
        KDTree<Triangle>::KDTreeNode* left_node = tree.getPairEmptyNodes();
        KDTree<Triangle>::KDTreeNode* right_node = left_node + 1;

        std::vector<Triangle*>* left_store = tree.getNewTrianglesStore();
        left_store->swap(left_triangles);
        left_node->setTriangles(left_store);

        std::vector<Triangle*>* right_store = tree.getNewTrianglesStore();
        right_store->swap(right_triangles);
        right_node->setTriangles(right_store);

        node->setAxis(lowest_split.first);
        node->setSplitPosition(lowest_split.second);
        node->setLeftNode(left_node);
        node->setLeaf(false);
        tree.removeNewTrianglesStore(node->getTriangles());

        if(remaining_depth > 0 && left_store->size() > 1)
        {
          BoundingBox bb_left;
          bb_left = bb;
          bb_left.corner2(lowest_split.first) = lowest_split.second;
          subdivide(tree, left_node, bb_left, remaining_depth - 1, remaining_failures, enhancement_ratio_failure);
        }
        if(remaining_depth > 0 && right_store->size() > 1)
        {
          BoundingBox bb_right;
          bb_right = bb;
          bb_right.corner1(lowest_split.first) = lowest_split.second;
          subdivide(tree, right_node, bb_right, remaining_depth - 1, remaining_failures, enhancement_ratio_failure);
        }
      }
    }

    static std::set<std::pair<int, DataType> > getSplitPositions(const KDTree<Triangle>::KDTreeNode* node, const BoundingBox& bb)
    {
      std::set<std::pair<int, DataType> > split_positions;

      for(std::vector<Triangle*>::const_iterator triangle = node->getTriangles()->begin(); triangle != node->getTriangles()->end(); ++triangle)
      {
        const BoundingBox& bb_triangle = (*triangle)->getBoundingBox();
        for(int i = 0; i < 3; ++i)
        {
          if (bb_triangle.corner1(i) >= bb.corner1(i) && bb_triangle.corner1(i) <= bb.corner2(i))
          {
            split_positions.insert(std::make_pair(i, bb_triangle.corner1(i)));
          }
          if (bb_triangle.corner2(i) >= bb.corner1(i) && bb_triangle.corner2(i) <= bb.corner2(i))
          {
            split_positions.insert(std::make_pair(i, bb_triangle.corner2(i)));
          }
        }
      }

      return split_positions;
    }

    static DataType computeCost(int axis, DataType split_position, const BoundingBox& bb, const std::vector<Triangle*>* triangles, std::vector<Triangle*>& right_triangles, std::vector<Triangle*>& left_triangles)
    {
      BoundingBox bb_right, bb_left;
      bb_right = bb_left = bb;
      bb_right.corner1(axis) = split_position;
      bb_left.corner2(axis) = split_position;

      for(std::vector<Triangle*>::const_iterator triangle = triangles->begin(); triangle != triangles->end(); ++triangle)
      {
        const BoundingBox& bb = (*triangle)->getBoundingBox();
        
        if(bb.corner1(axis) <= split_position)
        {
         left_triangles.push_back(*triangle);
        }
        if(bb.corner2(axis) >= split_position)
        {
         right_triangles.push_back(*triangle);
        }
      }

      return bb_right.SAH() * right_triangles.size() + bb_left.SAH() * left_triangles.size();
    }
  };
}

#endif
