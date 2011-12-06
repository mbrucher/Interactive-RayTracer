/**
 * \file vector.h
 * Contains the general static vector with dimensions fixed at compile-time
 */

#ifndef VECTOR
#define VECTOR

#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <cassert>
#include "type_traits.h"
#include "vector_functions.h"
//#include <tools/container_iterator.h>

namespace IRT
{
  namespace Tools
  {
    /// The general matrix container
    template<class Data_Type, unsigned long Height>
    struct Vector
    {
    public:
      /// Typedef of self
      typedef Vector<Data_Type, Height> Self;
      /// Typedef of internal data
      typedef Data_Type DataType;
      enum
      {
        staticHeight = Height
      };
      /// Typedef of internal data
      typedef DataType* VectorType;
      /// Typedef for data traits
      typedef DataTypeTraits<DataType> DataTraits;
      typedef Vector<bool, Height> ComparisonResult;

      /// Typedef of pointer to an element
      typedef DataType* pointer;

      /** @name Constructors and destructors */
      /// @{
      /**
       * The constructor of the matrix
       * @param init_val is the initial value that has to be put in the matrix
       */
      Vector(DataType init_val = 0)
      {
        for (unsigned int i = 0; i < height(); ++i)
        {
          (*this)(i) = init_val;
        }
      }

      /**
       * Copy constructor
       * @param other is the copied matrix
       */
      Vector(const Self& other)
      {
        for (unsigned int i = 0; i < height(); ++i)
        {
          (*this)(i) = other(i);
        }
      }

      /**
       * Constructor from a table of elements
       * @param elements is a pointer to the table of DataType elements
       */
      Vector(const DataType* elements)
      {
        for (unsigned int i = 0; i < height(); ++i)
        {
          (*this)(i) = elements[i];
        }
      }
      ///@}

      /**
       * Returns the height of the matrix
       * @return the height of the matrix
       */
      unsigned long height() const
      {
        return Height;
      }

      /**
       * Subscript operator
       * @param i is the line selected
       * @return the element in the matrix at the emplacement [i]
       */
      DataType& operator()(unsigned long i)
      {
        assert(i < height());
        return mVector[i];
      }

      /**
       * Const subscript operator
       * @param i is the line selected
       * @return the element in the matrix at the emplacement [i]
       */
      DataType operator()(unsigned long i) const
      {
        assert(i < height());
        return mVector[i];
      }

      /**
       * Assignmenent operator : assigning a new value
       * @param rhs is the new value in the matrix
       * @return the modified matrix
       */
      Self& operator=(const DataType rhs)
      {
        for (unsigned int i = 0; i < height(); ++i)
        {
          (*this)(i) = rhs;
        }
        return (*this);
      }

      /**
       * Assignement operator : assigning a matrix
       * @param rhs is the copied matrix
       * @return the new matrix
       */
      Self& operator=(const Self& rhs)
      {
        for (unsigned int i = 0; i < height(); ++i)
        {
          (*this)(i) = rhs(i);
        }
        return (*this);
      }
      ///@}

      /**
       * Returns the dataholder
       * @return the smart pointer containing the data
       */
      const DataType* get() const
      {
        return &mVector[0];
      }

      /**
       * Returns the dataholder
       * @return the smart pointer containing the data
       */
      DataType* get()
      {
        return &mVector[0];
      }

      /**
       * Normalizes the vector
       */
      Self& normalize()
      {
        DataType norm = std::sqrt(norm2(*this));
        for (int i = 0; i < height(); ++i)
        {
          (*this)(i) /= norm;
        }

        return *this;
      }
    protected:
      /// Data storage
      DataType mVector[Height];
    };
  }
}

#endif
