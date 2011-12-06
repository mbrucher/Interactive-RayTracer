/**
 * \file vector_functions.h
 * Contains functions that can be used on every vector
 */

#ifndef VECTOR_FUNCTIONS
#define VECTOR_FUNCTIONS

#include <iosfwd>
#include <functional>

#include <boost/type_traits.hpp>

#include "vector_traits.h"

namespace IRT
{
  namespace Tools
  {
    /** @name Addition */
    /// @{
    /**
     * + operator : adding something
     * @param lhs is the left member
     * @param rhs is the right member
     * @return the new matrix
     */
    template<class MatrixType>
    const MatrixType operator+(const MatrixType& lhs, const MatrixType& rhs)
    {
      MatrixType tempMat(lhs);
      tempMat += rhs;
      return (tempMat);
    }

    /**
     * + operator : adding a constant
     * @param lhs is the left member
     * @param rhs is the right member
     * @return the new matrix
     */
    template<class MatrixType>
    const MatrixType operator+(const typename MatrixType::DataType lhs, const MatrixType& rhs)
    {
      MatrixType tempMat(rhs);
      tempMat += lhs;
      return (tempMat);
    }

    /**
     * + operator : adding a constant
     * @param lhs is the left member
     * @param rhs is the right member
     * @return the new matrix
     */
    template<class MatrixType>
    const MatrixType operator+(const MatrixType& lhs, const typename MatrixType::DataType rhs)
    {
      return (rhs + lhs);
    }

    /**
     * += operator : adding a constant
     * @param lhs is the matrix
     * @param rhs is the value to add
     * @return the modified matrix
     */
    template<class MatrixType>
    MatrixType& operator+=(MatrixType& lhs, const typename MatrixType::DataType rhs)
    {
      for(unsigned long i = 0; i < lhs.height(); ++i)
      {
        lhs(i) += rhs;
      }
      return lhs;
    }

    /**
     * += operator : adding another matrix
     * @param lhs is the matrix
     * @param rhs is the matrix to add
     * @return the modified matrix
     */
    template<class MatrixType>
    MatrixType& operator+=(MatrixType& lhs, const MatrixType& rhs)
    {
      for(unsigned long i = 0; i < lhs.height(); ++i)
      {
        lhs(i) += rhs(i);
      }
      return lhs;
    }
    ///@}

    /** @name Unary operations */
    /// @{
    /**
     * - operator : opposes matrix
     * @return the opposed matrix
     */
    template<class MatrixType>
    const MatrixType operator-(const MatrixType& matrix)
    {
      MatrixType temp_mat;
      for(unsigned long i = 0; i < temp_mat.height(); ++i)
      {
        temp_mat(i) = -matrix(i);
      }
      return (temp_mat);
    }
    ///@}

    /** @name Substraction */
    /// @{
    /**
     * - operator : substracting something
     * @param lhs is the left member
     * @param rhs is the right member
     * @return the new matrix
     */
    template<class MatrixType>
    const MatrixType operator-(const MatrixType& lhs, const MatrixType& rhs)
    {
      MatrixType tempMat(lhs);
      tempMat -= rhs;
      return (tempMat);
    }

    /**
     * - operator : substracting to a constant
     * @param lhs is the left member
     * @param rhs is the right member
     * @return the new matrix
     */
    template<class MatrixType>
    const MatrixType operator-(const typename MatrixType::DataType lhs, const MatrixType& rhs)
    {
      MatrixType tempMat(rhs);
      tempMat -= lhs;
      return -(tempMat);
    }

    /**
     * - operator : substracting a constant
     * @param lhs is the left member
     * @param rhs is the right member
     * @return the new matrix
     */
    template<class MatrixType>
    const MatrixType operator-(const MatrixType& lhs, const typename MatrixType::DataType rhs)
    {
      MatrixType tempMat(lhs);
      tempMat -= rhs;
      return (tempMat);
    }

    /**
     * -= operator : substracting a constant
     * @param lhs is the matrix
     * @param rhs is the value to add
     * @return the modified matrix
     */
    template<class MatrixType>
    MatrixType& operator-=(MatrixType& lhs, const typename MatrixType::DataType rhs)
    {
      for(unsigned long i = 0; i < lhs.height(); ++i)
      {
        lhs(i) -= rhs;
      }
      return lhs;
    }

    /**
     * -= operator : substracting another matrix
     * @param lhs is the matrix
     * @param rhs is the matrix to add
     * @return the modified matrix
     */
    template<class MatrixType>
    MatrixType& operator-=(MatrixType& lhs, const MatrixType& rhs)
    {
      for(unsigned long i = 0; i < lhs.height(); ++i)
      {
        lhs(i) -= rhs(i);
      }
      return lhs;
    }
    ///@}

    /** @name Multiplication */
    /// @{
    /**
     * * operator : multiply by something
     * @param lhs is the left member
     * @param rhs is the right member
     * @return the new matrix
     */
    template<class MatrixType>
    const MatrixType operator*(const MatrixType& lhs, const typename MatrixType::DataType rhs)
    {
      MatrixType tempMat(lhs);
      tempMat *= rhs;
      return (tempMat);
    }

    /**
     * *= operator : multiply by something
     * @param lhs is the matrix
     * @param rhs is the value to multiply
     * @return the modified matrix
     */
    template<class MatrixType>
    MatrixType& operator*=(MatrixType& lhs, const typename MatrixType::DataType rhs)
    {
      for(unsigned long i = 0; i < lhs.height(); ++i)
      {
        lhs(i) *= rhs;
      }
      return lhs;
    }

    /**
     * * operator : multiply the matrix by another one
     * @param lhs is the left member
     * @param rhs is the right member
     * @return the scalar product between the two matrices
     */
    template<class MatrixType>
    typename MatrixType::DataType operator*(const MatrixType& lhs, const MatrixType& rhs)
    {
      typename MatrixType::DataType result = MatrixType::DataTraits::zero(lhs(0) * rhs(0));

      for(unsigned long i = 0; i < lhs.height(); ++i)
      {
        result += lhs(i) * rhs(i);
      }
      return result;
    }

    /**
     * mult : multiply the matrix by another one
     * @param lhs is the left member
     * @param rhs is the right member
     * @return the product between the two matrices
     */
    template<class MatrixType>
    MatrixType mult(const MatrixType& lhs, const MatrixType& rhs)
    {
      MatrixType result(0.);

      for(unsigned long i = 0; i < lhs.height(); ++i)
      {
        result(i) = lhs(i) * rhs(i);
      }
      return result;
    }

    /**
     * operator ^ : vectorial product between two Vector3d
     * @param lhs is the left member
     * @param rhs is the right member
     * @return the product between the two matrices
     */
    template<class MatrixType>
    MatrixType operator^(const MatrixType& lhs, const MatrixType& rhs)
    {
      MatrixType result(0.);

      for(unsigned long i = 0; i < 3; ++i)
      {
        result(i) = lhs((i+1)%3) * rhs((i+2)%3) - lhs((i+2)%3) * rhs((i+1)%3);
      }
      return result;
    }

    /**
     * min: updates the minimum vector
     * @param minimum will be updated
     * @param other
     * @return the minimum
     */
    template<class MatrixType>
    const MatrixType& min(MatrixType& minimum, const MatrixType& other)
    {
      for(unsigned long i = 0; i < 3; ++i)
      {
        minimum(i) = std::min(minimum(i), other(i));
      }
      return minimum;
    }

        /**
     * max: updates the maximum vector
     * @parammaximum will be updated
     * @param other
     * @return the minimum
     */
    template<class MatrixType>
    const MatrixType& max(MatrixType& maximum, const MatrixType& other)
    {
      for(unsigned long i = 0; i < 3; ++i)
      {
        maximum(i) = std::max(maximum(i), other(i));
      }
      return maximum;
    }

    /**
     * * operator : useful for non-commutative DataType
     * @param lhs is a DataType data
     * @param rhs is the matrix being left-multiplied
     * @return lhs * rhs
     */
    template<class MatrixType>
    const MatrixType operator*(const typename MatrixType::DataType lhs, const MatrixType& rhs)
    {
      MatrixType tempMat(rhs);
      for(unsigned long i = 0; i < tempMat.height(); ++i)
      {
        tempMat(i) = lhs * rhs(i);
      }
      return (tempMat);
    }

    /**
     * Calculates the sum of the elements of a matrix
     * @return the sum of all elements in the matrix
     */
    template<class MatrixType>
    typename MatrixType::DataType sum(const MatrixType& me)
    {
      typename MatrixType::DataType sumTemp(MatrixType::DataTraits::zero(me(0)));
      for(unsigned long i = 0; i < me.height(); ++i)
      {
        sumTemp += me(i);
      }
      return sumTemp;
    }

    /**
     * Calculates the euclidian norm of the matrix
     * @return square the norm2 of the matrix
     */
    template<class MatrixType>
    typename MatrixType::DataType norm2(const MatrixType& me)
    {
      typename MatrixType::DataType norm_temp = MatrixType::DataTraits::zero(me(0));
      for(unsigned long i = 0; i < me.height(); ++i)
      {
        norm_temp += MatrixType::DataTraits::conjuge(me(i)) * me(i);
      }
      return norm_temp;
    }

    /**
     * Calculates the absolute norm of the matrix
     * @return the norm1 of the matrix
     */
    template<class MatrixType>
    typename MatrixType::DataType norm1(const MatrixType& me)
    {
      typename MatrixType::DataType norm_temp = MatrixType::DataTraits::zero(me(0));
      for(unsigned long i = 0; i < me.height(); ++i)
      {
        norm_temp += MatrixType::DataTraits::absolute(me(i));
      }
      return norm_temp;
    }

    /**
     * Equality test
     * @param lhs is the left member
     * @param rhs is the right member
     * @return true if the matrices are equal
     */
    template<class MatrixType>
    const typename boost::enable_if<typename boost::is_floating_point<typename MatrixType::DataType>, typename MatrixType::ComparisonResult>::type operator==(const MatrixType& lhs, const MatrixType& rhs)
    {
      typename MatrixType::ComparisonResult result;

      unsigned long height = lhs.height();
      for(unsigned long i = 0; i < height; ++i)
      {
        result(i) = (DataTypeTraits<typename MatrixType::DataType>::absolute(lhs(i) - rhs(i)) <= DataTypeTraits<typename MatrixType::DataType>::epsilon(lhs(i) - rhs(i)));
      }
      return result;
    }

    /**
     * Equality test
     * @param lhs is the left member
     * @param rhs is the right member
     * @return true if the matrices are equal
     */
    template<class MatrixType>
    const typename boost::enable_if<typename boost::is_integral<typename MatrixType::DataType>, typename MatrixType::ComparisonResult>::type operator==(const MatrixType& lhs, const MatrixType& rhs)
    {
      typename MatrixType::ComparisonResult result;

      unsigned long height = lhs.height();
      for(unsigned long i = 0; i < height; ++i)
      {
        result(i) = lhs(i) == rhs(i);
      }
      return result;
    }

    /**
     * Equality test
     * @param lhs is the left member
     * @param rhs is the right member
     * @return true if the matrices are equal
     */
    template<class MatrixType>
    const typename boost::enable_if<typename boost::is_floating_point<typename MatrixType::DataType>, typename MatrixType::ComparisonResult>::type operator==(const MatrixType& lhs, const typename MatrixType::DataType rhs)
    {
      typename MatrixType::ComparisonResult result;

      unsigned long height = lhs.height();
      for(unsigned long i = 0; i < height; ++i)
      {
        result(i) = (DataTypeTraits<typename MatrixType::DataType>::absolute(lhs(i) - rhs) <= DataTypeTraits<typename MatrixType::DataType>::epsilon(lhs(i) - rhs));
      }
      return result;
    }

    /**
     * Equality test
     * @param lhs is the left member
     * @param rhs is the right member
     * @return true if the matrices are equal
     */
    template<class MatrixType>
    const typename boost::enable_if<typename boost::is_integral<typename MatrixType::DataType>, typename MatrixType::ComparisonResult>::type operator==(const MatrixType& lhs, const typename MatrixType::DataType rhs)
    {
      typename MatrixType::ComparisonResult result;

      unsigned long height = lhs.height();
      for(unsigned long i = 0; i < height; ++i)
      {
        result(i) = (lhs(i) == rhs);
      }
      return result;
    }

    template<class MatrixType>
    const typename MatrixType::ComparisonResult operator==(const typename MatrixType::DataType lhs, const MatrixType& rhs)
    {
      return rhs == lhs;
    }

    /**
     * Different test
     * @param lhs is the left member
     * @param rhs is the right member
     * @return true if the matrices are different
     */
    template<class MatrixType>
    const typename boost::enable_if<typename boost::is_floating_point<typename MatrixType::DataType>, typename MatrixType::ComparisonResult>::type operator!=(const MatrixType& lhs, const MatrixType& rhs)
    {
      typename MatrixType::ComparisonResult result;
      unsigned long height = lhs.height();
      for(unsigned long i = 0; i < height; ++i)
      {
        result(i) = (DataTypeTraits<typename MatrixType::DataType>::absolute(lhs(i) - rhs(i)) >= DataTypeTraits<typename MatrixType::DataType>::epsilon(lhs(i) - rhs(i)));
      }
      return result;
    }

    /**
     * Different test
     * @param lhs is the left member
     * @param rhs is the right member
     * @return true if the matrices are different
     */
    template<class MatrixType>
    const typename boost::enable_if<typename boost::is_integral<typename MatrixType::DataType>, typename MatrixType::ComparisonResult>::type operator!=(const MatrixType& lhs, const MatrixType& rhs)
    {
      typename MatrixType::ComparisonResult result;
      unsigned long height = lhs.height();
      for(unsigned long i = 0; i < height; ++i)
      {
        result(i) = (lhs(i) != rhs(i));
      }
      return result;
    }

    /**
     * Different test
     * @param lhs is the left member
     * @param rhs is the right member
     * @return true if the matrices are different
     */
    template<class MatrixType>
    const typename boost::enable_if<typename boost::is_floating_point<typename MatrixType::DataType>, typename MatrixType::ComparisonResult>::type operator!=(const MatrixType& lhs, const typename MatrixType::DataType rhs)
    {
      typename MatrixType::ComparisonResult result;

      unsigned long height = lhs.height();
      for(unsigned long i = 0; i < height; ++i)
      {
        result(i) = (DataTypeTraits<typename MatrixType::DataType>::absolute(lhs(i) - rhs) >= DataTypeTraits<typename MatrixType::DataType>::epsilon(lhs(i) - rhs));
      }
      return result;
    }

    /**
     * Different test
     * @param lhs is the left member
     * @param rhs is the right member
     * @return true if the matrices are different
     */
    template<class MatrixType>
    const typename boost::enable_if<typename boost::is_integral<typename MatrixType::DataType>, typename MatrixType::ComparisonResult>::type operator!=(const MatrixType& lhs, const typename MatrixType::DataType rhs)
    {
      typename MatrixType::ComparisonResult result;

      unsigned long height = lhs.height();
      for(unsigned long i = 0; i < height; ++i)
      {
        result(i) = (lhs(i) != rhs);
      }
      return result;
    }

    template<class MatrixType>
    const typename MatrixType::ComparisonResult operator!=(const typename MatrixType::DataType lhs, const MatrixType& rhs)
    {
      return rhs != lhs;
    }

    /**
     * Superiority test
     * @param lhs is the left member
     * @param rhs is the right member
     * @return true if the matrices are different
     */
    template<class MatrixType>
    const typename MatrixType::ComparisonResult operator>(const MatrixType& lhs, const typename MatrixType::DataType rhs)
    {
      typename MatrixType::ComparisonResult result;

      unsigned long height = lhs.height();
      for(unsigned long i = 0; i < height; ++i)
      {
        result(i) = lhs(i)> rhs;
      }
      return result;
    }

    template<class MatrixType>
    const typename MatrixType::ComparisonResult operator>(const typename MatrixType::DataType lhs, const MatrixType& rhs)
    {
      return rhs < lhs;
    }

    /**
     * Inferiority test
     * @param lhs is the left member
     * @param rhs is the right member
     * @return true if the matrices are different
     */
    template<class MatrixType>
    const typename MatrixType::ComparisonResult operator<(const MatrixType& lhs, const typename MatrixType::DataType rhs)
    {
      typename MatrixType::ComparisonResult result;

      unsigned long height = lhs.height();
      for(unsigned long i = 0; i < height; ++i)
      {
        result(i) = lhs(i) < rhs;
      }
      return result;
    }

    template<class MatrixType>
    const typename MatrixType::ComparisonResult operator<(const typename MatrixType::DataType lhs, const MatrixType& rhs)
    {
      return rhs> lhs;
    }

    /**
     * Tests that all elements in the matrix are true
     * @param matrix is the matrix to test
     * @return true if every element in the matrix is true
     */
    template<class MatrixType>
    bool all(const MatrixType& matrix)
    {
      bool isTrue = true;

      for(unsigned int i = 0; i < matrix.height(); ++i)
      {
        isTrue &= matrix(i);
      }
/*      for(typename MatrixType::const_iterator it = matrix.begin(); it != matrix.end(); ++it)
      {
        isTrue &= *it;
      }*/

      return isTrue;
    }

    /**
     * Tests if any element in the matrix is true
     * @param matrix is the matrix to test
     * @return true if one element in the matrix is true
     */
    template<class MatrixType>
    bool any(const MatrixType& matrix)
    {
      bool isTrue = false;

      for(unsigned int i = 0; i < matrix.height(); ++i)
      {
        isTrue |= matrix(i);
      }

/*      for(typename MatrixType::const_iterator it = matrix.begin(); it != matrix.end(); ++it)
      {
        isTrue |= *it;
      }*/

      return isTrue;
    }
  }
}
#endif
