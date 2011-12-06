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

#include "../tools/matrix.h"

namespace IRT
{
  typedef float DataType;
  /// Type for a vector
  typedef Tools::Vector<DataType, 3> Vector3df;
  /// Type for a point
  typedef Tools::Vector<DataType, 3> Point3df;
  /// Type for a normal
  typedef Tools::Vector<DataType, 3> Normal3df;

  /// Number of colors
  const unsigned int nbColors = 3;
  /// Typedef for a simple color
  typedef Tools::Vector<DataType, nbColors> Color;
}

#endif
