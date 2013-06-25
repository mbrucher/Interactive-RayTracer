/**
 * \file common.h
 * All common definitions
 */

#ifndef COMMON
#define COMMON

#ifdef _MSC_VER
# ifdef IRT_EXPORTS
#  define _export_tools _declspec(dllexport)
# else
#  define _export_tools _declspec(dllimport)
# endif

#pragma warning (disable: 4100)
#pragma warning (disable: 4710)

#else
# define _export_tools
#endif

#include <Eigen/Dense>

namespace IRT
{
  typedef float DataType;
  /// Type for a vector
  typedef Eigen::Matrix<DataType, 3, 1> Vector3df;
  /// Type for a point
  typedef Eigen::Matrix<DataType, 3, 1> Point3df;
  /// Type for a normal
  typedef Eigen::Matrix<DataType, 3, 1> Normal3df;

  /// Number of colors
  const unsigned int nbColors = 3;
  /// Typedef for a simple color
  typedef Eigen::Matrix<DataType, nbColors, 1> Color;

  template<class Array>
  DataType norm2(const Array& array)
  {
    return (array.cwiseProduct(array)).sum();
  }

  template<class Array>
  void normalize(Array& array)
  {
    array /= std::sqrt(norm2(array));
  }
}

#endif
