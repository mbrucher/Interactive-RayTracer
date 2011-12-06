/**
 * \file vector_traits.h
 * This files contains the definitions of zero, one for each datatype
 */

#ifndef VECTOR_TRAITS
#define VECTOR_TRAITS

#include <cmath>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include "type_traits.h"

namespace IRT
{
  namespace Tools
  {
    template<class DataType, unsigned long Height>
    struct Vector;
  }
}

/// This structure contains the value for zero, one and some other operation for an IRT::Tools::Vector type
template <class DataType, unsigned long Height>
struct DataTypeTraits<IRT::Tools::Vector<DataType, Height> >
{
  /// The difference between 1 and the least value greater than 1 that is representable
  static const IRT::Tools::Vector<DataType, Height> epsilon(const IRT::Tools::Vector<DataType, Height>& data)
  {
    return IRT::Tools::Vector<DataType, Height>(IRT::Tools::Vector<DataType, Height>::DataTraits::epsilon(data(0, 0)));
  }

  static IRT::Tools::Vector<DataType, Height> zero(const IRT::Tools::Vector<DataType, Height>& data)
  {
    return IRT::Tools::Vector<DataType, Height>(IRT::Tools::Vector<DataType, Height>::DataTraits::zero(data(0, 0)));
  }

  /**
   * This function calculates the absolute value of a IRT::Tools::Vector
   * @param data is the piece of data
   * @return the absolute value of the piece of data
   */
  static const IRT::Tools::Vector<DataType, Height> absolute(const IRT::Tools::Vector<DataType, Height>& data)
  {
    unsigned long height = data.height();
    IRT::Tools::Vector<DataType, Height> abso;

    for(unsigned long i = 0; i < height; ++i)
    {
      abso(i) = IRT::Tools::Vector<DataType, Height>::DataTraits::absolute(data(i));
    }
    return abso;
  }
};

#endif
