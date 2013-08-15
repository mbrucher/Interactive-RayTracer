/**
 * \file build_kdtree.h
 * The kd-tree implementation for fast primitive lookup
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
      KDTree<Primitive>& tree = scene->getKDTree();
      tree.setPrimitives(scene->getPrimitives());
      subdivide(tree, &tree.getNodes()[0], scene->getBoundingBox(), remaining_depth, remaining_failures, enhancement_ratio_failure);
    }

    static void automatic_build(IRT::SimpleScene* scene)
    {
      // Using Havran's values
      DataType k1 = 1.2f;
      DataType k2 = 2.0f;
      DataType K1 = 1.f;
      DataType K2 = .2f;

      int remaining_depth = static_cast<int>(std::ceil(k1 * std::log(static_cast<DataType>(scene->getPrimitives().size())) + k2));
      int remaining_failures = static_cast<int>(std::ceil(K1 + remaining_depth * K2));
      DataType enhancement_ratio_failure = .75f;

      custom_build(scene, remaining_depth, remaining_failures, enhancement_ratio_failure);
    }

    static void subdivide(KDTree<Primitive>& tree, KDTree<Primitive>::KDTreeNode* node, const BoundingBox& bb, int remaining_depth, int remaining_failures, DataType enhancement_ratio_failure)
    {
      const std::set<std::pair<int, DataType> >& split_positions = getSplitPositions(node, bb);

      DataType lowest_cost = std::numeric_limits<DataType>::max();
      std::pair<int, DataType> lowest_split = std::make_pair(-1, 0.f);
      std::vector<Primitive*> right_primitives, left_primitives;

      for(std::set<std::pair<int, DataType> >::const_iterator it = split_positions.begin(); it != split_positions.end(); ++it)
      {
        std::vector<Primitive*> right_primitives_test, left_primitives_test;

        DataType new_cost = computeCost(it->first, it->second, bb, node->getPrimitives(), right_primitives_test, left_primitives_test);
        new_cost = (new_cost + 0.3) / (bb.SAH() * node->getPrimitives()->size());

        if(new_cost < lowest_cost)
        {
          right_primitives_test.swap(right_primitives);
          left_primitives_test.swap(left_primitives);
          lowest_split = *it;
          lowest_cost = new_cost;
        }
      }

      if(lowest_split.first != -1 && (lowest_cost < enhancement_ratio_failure || --remaining_failures >= 0))
      {
        KDTree<Primitive>::KDTreeNode* left_node = tree.getPairEmptyNodes();
        KDTree<Primitive>::KDTreeNode* right_node = left_node + 1;

        std::vector<Primitive*>* left_store = tree.getNewPrimitivesStore();
        left_store->swap(left_primitives);
        left_node->setPrimitives(left_store);

        std::vector<Primitive*>* right_store = tree.getNewPrimitivesStore();
        right_store->swap(right_primitives);
        right_node->setPrimitives(right_store);

        node->setAxis(lowest_split.first);
        node->setSplitPosition(lowest_split.second);
        node->setLeftNode(left_node);
        node->setLeaf(false);
        tree.removeNewPrimitivesStore(node->getPrimitives());

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

    static std::set<std::pair<int, DataType> > getSplitPositions(const KDTree<Primitive>::KDTreeNode* node, const BoundingBox& bb)
    {
      std::set<std::pair<int, DataType> > split_positions;

      for(std::vector<Primitive*>::const_iterator primitive = node->getPrimitives()->begin(); primitive != node->getPrimitives()->end(); ++primitive)
      {
        const BoundingBox& bb_primitive = (*primitive)->getBoundingBox();
        for(int i = 0; i < 3; ++i)
        {
          if (bb_primitive.corner1(i) >= bb.corner1(i) && bb_primitive.corner1(i) <= bb.corner2(i))
          {
            split_positions.insert(std::make_pair(i, bb_primitive.corner1(i)));
          }
          if (bb_primitive.corner2(i) >= bb.corner1(i) && bb_primitive.corner2(i) <= bb.corner2(i))
          {
            split_positions.insert(std::make_pair(i, bb_primitive.corner2(i)));
          }
        }
      }

      return split_positions;
    }

    static DataType computeCost(int axis, DataType split_position, const BoundingBox& bb, const std::vector<Primitive*>* primitives, std::vector<Primitive*>& right_primitives, std::vector<Primitive*>& left_primitives)
    {
      BoundingBox bb_right, bb_left;
      bb_right = bb_left = bb;
      bb_right.corner1(axis) = split_position;
      bb_left.corner2(axis) = split_position;

      for(std::vector<Primitive*>::const_iterator primitive = primitives->begin(); primitive != primitives->end(); ++primitive)
      {
        const BoundingBox& bb = (*primitive)->getBoundingBox();
        
        if(bb.corner1(axis) <= split_position)
        {
         left_primitives.push_back(*primitive);
        }
        if(bb.corner2(axis) >= split_position)
        {
         right_primitives.push_back(*primitive);
        }
      }

      return bb_right.SAH() * right_primitives.size() + bb_left.SAH() * left_primitives.size();
    }
  };
}

#endif
