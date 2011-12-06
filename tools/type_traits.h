/**
 * \file type_traits.h
 * This files contains the definitions of zero, one for each datatype for basic types
 * \todo - other types - std::complex, ... -
 */

#ifndef TYPE_TRAITS
#define TYPE_TRAITS

#include <cmath>
#include <cstdlib>
#include <limits>
#include <algorithm>

#ifdef USE_PYTHON
# include <Python.h>
# include <numpy/arrayobject.h>
#endif

#ifdef __GNUC__
#define unused_argument __attribute((unused))
#else
#define unused_argument
#endif

const double PI = 3.14159265;

/// This structure contains nothing for the undefined datatypes
template <class DataType>
struct DataTypeTraits
{
};

/// This structure contains the value for zero, one and some other operation for an int type
template <>
struct DataTypeTraits<unsigned char>
{
  /// The difference between 1 and the least value greater than 1 that is representable
  static const unsigned char epsilon(const unsigned char data unused_argument)
  {
    return std::numeric_limits<unsigned char>::epsilon();
  }

  static const unsigned char zero(const unsigned char data unused_argument)
  {
    return 0;
  }

  static const unsigned char one(const unsigned char data unused_argument)
  {
    return 1;
  }

  /**
   * This function calculates the absolute value of a matrix
   * @param data is the piece of data
   * @return the absolute value of the piece of data
   */
  static const unsigned char absolute(const unsigned char data)
  {
    return static_cast<unsigned char>(std::abs(data));
  }

  /**
   * This function conjugates a piece of data
   * @param data is the piece of data to be conjugated
   * @return the conjugated piece of data
   */
  static const unsigned char conjuge(const unsigned char data)
  {
    return (data);
  }

  /**
   * This function calulates the square root of a piece of data
   * @param data is the piece of data to be square-rooted
   * @return the square-rooted piece of data
   */
  static const unsigned char sqrt(const unsigned char data)
  {
    return static_cast<unsigned char>(std::sqrt(static_cast<float>(data)));
  }

  /**
   * This function returns the square of the norm2 of a piece of data
   * @param data is the piece of data to be normed
   * @return the norm2 of the piece of data
   */
  static const unsigned char norm2(const unsigned char data)
  {
    return (data * data);
  }

#ifdef USE_PYTHON
  /// Numpy char symbol
//  static const char type_kind = 'f';
  /// Numpy constant
  static const int type_num = NPY_UBYTE;
#endif
};

/// This structure contains the value for zero, one and some other operation for an int type
template <>
struct DataTypeTraits<int>
{
  /// The difference between 1 and the least value greater than 1 that is representable
  static const int epsilon(const int data)
  {
    return std::numeric_limits<int>::epsilon();
  }

  static const int zero(const int data)
  {
    return 0;
  }

  static const int one(const int data)
  {
    return 1;
  }

  /**
   * This function calculates the absolute value of a matrix
   * @param data is the piece of data
   * @return the absolute value of the piece of data
   */
  static const int absolute(const int data)
  {
    return std::abs(data);
  }

  /**
   * This function conjugates a piece of data
   * @param data is the piece of data to be conjugated
   * @return the conjugated piece of data
   */
  static const int conjuge(const int data)
  {
    return (data);
  }

  /**
   * This function calulates the square root of a piece of data
   * @param data is the piece of data to be square-rooted
   * @return the square-rooted piece of data
   */
  static const int sqrt(const int data)
  {
    return static_cast<int>(std::sqrt(static_cast<float>(data)));
  }

  /**
   * This function returns the square of the norm2 of a piece of data
   * @param data is the piece of data to be normed
   * @return the norm2 of the piece of data
   */
  static const int norm2(const int data)
  {
    return (data * data);
  }

#ifdef USE_PYTHON
  /// Numpy char symbol
//  static const char type_kind = 'f';
  /// Numpy constant
  static const int type_num = NPY_INT;
#endif
};

/// This structure contains the value for zero, one and some other operation for an unsigned int type
template <>
struct DataTypeTraits<unsigned int>
{
  /// The difference between 1 and the least value greater than 1 that is representable
  static const unsigned int epsilon(const unsigned int data)
  {
    return std::numeric_limits<unsigned int>::epsilon();
  }

  static const unsigned int zero(const unsigned int data)
  {
    return 0;
  }

  static const unsigned int one(const unsigned int data)
  {
    return 1;
  }

  /**
   * This function calculates the absolute value of a matrix
   * @param data is the piece of data
   * @return the absolute value of the piece of data
   */
  static const unsigned int absolute(const unsigned int data)
  {
    return data;
  }

  /**
   * This function conjugates a piece of data
   * @param data is the piece of data to be conjugated
   * @return the conjugated piece of data
   */
  static const unsigned int conjuge(const unsigned int data)
  {
    return (data);
  }

  /**
   * This function returns the square of the norm2 of a piece of data
   * @param data is the piece of data to be normed
   * @return the norm2 of the piece of data
   */
  static const unsigned int norm2(const unsigned int data)
  {
    return (data * data);
  }

#ifdef USE_PYTHON
  /// Numpy char symbol
//  static const char type_kind = 'f';
  /// Numpy constant
  static const int type_num = NPY_UINT;
#endif
};

/// This structure contains the value for zero, one and some other operation for an bool type
template <>
struct DataTypeTraits<bool>
{
  /// The difference between 1 and the least value greater than 1 that is representable
  static const bool epsilon(const bool data)
  {
    return std::numeric_limits<bool>::epsilon();
  }
  static const bool zero(const bool data)
  {
    return false;
  }

  static const bool one(const bool data)
  {
    return true;
  }

  /**
   * This function calculates the absolute value of a matrix
   * @param data is the piece of data
   * @return the absolute value of the piece of data
   */
  static const bool absolute(const bool data)
  {
    return data;
  }

  static void clone(bool value, bool& resultat)
  {
    resultat = value;
  }

  static const bool conjuge(const bool data)
  {
    return (data);
  }

#ifdef USE_PYTHON
  /// Numpy char symbol
  static const char type_kind = 'b';
  /// Numpy constant
  static const int type_num = NPY_BOOL;
#endif
};

/// This structure contains the value for zero, one and some other operation for an short type
template <>
struct DataTypeTraits<short>
{
  /// The difference between 1 and the least value greater than 1 that is representable
  static const short epsilon(const short data)
  {
    return std::numeric_limits<short>::epsilon();
  }

  static const short zero(const short data)
  {
    return 0;
  }

  static const short one(const short data)
  {
    return 1;
  }

  /**
   * Binding over operator +=
   * @param assigned is the value to be assigned
   * @param value is the value to add
   * @return the assigned value
   */
  static short& addAssign(short& assigned,  short value)
  {
    return assigned += value;
  }

  /**
   * Binding over operator -=
   * @param assigned is the value to be assigned
   * @param value is the value to substract
   * @return the assigned value
   */
  static short& subAssign(short& assigned, short value)
  {
    return assigned -= value;
  }

  /**
   * This function calculates the absolute value of a matrix
   * @param data is the piece of data
   * @return the absolute value of the piece of data
   */
  static const short absolute(const short data)
  {
    return std::abs(data);
  }

  /**
   * This function conjugates a piece of data
   * @param data is the piece of data to be conjugated
   * @return the conjugated piece of data
   */
  static const short conjuge(const short data)
  {
    return (data);
  }

  /**
   * This function returns the square of the norm2 of a piece of data
   * @param data is the piece of data to be normed
   * @return the norm2 of the piece of data
   */
  static const short norm2(const short data)
  {
    return (data * data);
  }

#ifdef USE_PYTHON
  /// Numpy char symbol
//  static const char type_kind = 'f';
  /// Numpy constant
  static const int type_num = NPY_SHORT;
#endif
};

/// This structure contains the value for zero, one and some other operation for an long type
template <>
struct DataTypeTraits<long>
{
  /// The difference between 1 and the least value greater than 1 that is representable
  static const long epsilon(const long data)
  {
    return std::numeric_limits<long>::epsilon();
  }

  static const long zero(const long data)
  {
    return 0;
  }

  static const long one(const long data)
  {
    return 1;
  }

  /**
   * Binding over operator +=
   * @param assigned is the value to be assigned
   * @param value is the value to add
   * @return the assigned value
   */
  static long& addAssign(long& assigned, long value)
  {
    return assigned += value;
  }

  /**
   * Binding over operator -=
   * @param assigned is the value to be assigned
   * @param value is the value to substract
   * @return the assigned value
   */
  static long& subAssign(long& assigned, long value)
  {
    return assigned -= value;
  }

  /**
   * This function calculates the absolute value of a matrix
   * @param data is the piece of data
   * @return the absolute value of the piece of data
   */
  static const long absolute(const long data)
  {
    return std::abs(data);
  }

  /**
   * This function conjugates a piece of data
   * @param data is the piece of data to be conjugated
   * @return the conjugated piece of data
   */
  static const long conjuge(const long data)
  {
    return (data);
  }

  /**
   * This function returns the square of the norm2 of a piece of data
   * @param data is the piece of data to be normed
   * @return the norm2 of the piece of data
   */
  static const long norm2(const long data)
  {
    return (data * data);
  }

#ifdef USE_PYTHON
  /// Numpy char symbol
//  static const char type_kind = 'f';
  /// Numpy constant
  static const int type_num = NPY_LONG;
#endif
};

/// This structure contains the value for zero, one and some other operation for an int type
template <>
struct DataTypeTraits<unsigned long>
{
  /// The difference between 1 and the least value greater than 1 that is representable
  static const unsigned long epsilon(const unsigned long data)
  {
    return std::numeric_limits<unsigned long>::epsilon();
  }

  static const long zero(const unsigned long data)
  {
    return 0;
  }

  static const long one(const unsigned long data)
  {
    return 1;
  }

  /**
   * This function calculates the absolute value of a matrix
   * @param data is the piece of data
   * @return the absolute value of the piece of data
   */
  static const unsigned long absolute(const unsigned long data)
  {
    return data;
  }

  /**
   * This function conjugates a piece of data
   * @param data is the piece of data to be conjugated
   * @return the conjugated piece of data
   */
  static const unsigned long conjuge(const unsigned long data)
  {
    return (data);
  }

  /**
   * This function returns the square of the norm2 of a piece of data
   * @param data is the piece of data to be normed
   * @return the norm2 of the piece of data
   */
  static const unsigned long norm2(const unsigned long data)
  {
    return (data * data);
  }

#ifdef USE_PYTHON
  /// Numpy char symbol
//  static const char type_kind = 'f';
  /// Numpy constant
  static const int type_num = NPY_ULONG;
#endif
};

/// This structure contains the value for zero, one and some other operation for an float type
template <>
struct DataTypeTraits<float>
{
  /// The difference between 1 and the least value greater than 1 that is representable
  static const float epsilon(const float data)
  {
    return std::numeric_limits<float>::epsilon();
  }

  static const float zero(const float data)
  {
    return 0.0f;
  }

  static const float one(const float data)
  {
    return 1.0f;
  }

  /**
   * This function inverses a piece of data
   * @param data is the piece of data to be inverted
   * @return the inverted piece of data
   */
  static const float inverse(const float data)
  {
    return (1.f / data);
  }

  /**
   * This function calculates the absolute value of a matrix
   * @param data is the piece of data
   * @return the absolute value of the piece of data
   */
  static const float absolute(const float data)
  {
    return std::abs(data);
  }

  /**
   * This function returns a value indicating if it is invertible
   * @param data is the piece of data being tested
   * @return the "invertibility"
   */
  static const float is_invertible(const float data)
  {
    return absolute(data);
  }

  /**
   * This function conjugates a piece of data
   * @param data is the piece of data to be conjugated
   * @return the conjugated piece of data
   */
  static const float conjuge(const float data)
  {
    return (data);
  }

  /**
   * This function returns the square of the norm2 of a piece of data
   * @param data is the piece of data to be normed
   * @return the norm2 of the piece of data
   */
  static const float norm2(const float data)
  {
    return (data * data);
  }

  /**
   * This function calulates the square root of a piece of data
   * @param data is the piece of data to be square-rooted
   * @return the square-rooted piece of data
   */
  static const float sqrt(const float data)
  {
    return std::sqrt(data);
  }

  /**
   * This function returns the data needed to transpose the original data
   * @param data is the piece of data to be transposed
   * @return the anti-diagonal system
   */
  static const float create_transpose(const float data)
  {
    return (1.f);
  }

#ifdef USE_PYTHON
  /// Numpy char symbol
  static const char type_kind = 'f';
  /// Numpy constant
  static const int type_num = NPY_FLOAT;
#endif
};

/// This structure contains the value for zero, one and some other operation for an double type
template <>
struct DataTypeTraits<double>
{
  /// The difference between 1 and the least value greater than 1 that is representable
  static const double epsilon(const double data)
  {
    return std::numeric_limits<double>::epsilon();
  }

  static const double zero(const double data)
  {
    return 0.0;
  }

  static const double one(const double data)
  {
    return 1.0;
  }

  /**
   * This function inverses a piece of data
   * @param data is the piece of data to be inverted
   * @return the inverted piece of data
   */
  static const double inverse(const double data)
  {
    return (1. / data);
  }

  /**
   * This function calculates the absolute value of a matrix
   * @param data is the piece of data
   * @return the absolute value of the piece of data
   */
  static const double absolute(const double data)
  {
    return std::abs(data);
  }

  /**
   * This function conjugates a piece of data
   * @param data is the piece of data to be conjugated
   * @return the conjugated piece of data
   */
  static const double conjuge(const double data)
  {
    return (data);
  }

  /**
   * This function returns the square of the norm2 of a piece of data
   * @param data is the piece of data to be normed
   * @return the norm2 of the piece of data
   */
  static const double norm2(const double data)
  {
    return (data * data);
  }

  /**
   * This function calulates the square root of a piece of data
   * @param data is the piece of data to be square-rooted
   * @return the square-rooted piece of data
   */
  static const double sqrt(const double data)
  {
    return std::sqrt(data);
  }

#ifdef USE_PYTHON
  /// Numpy char symbol
  static const char type_kind = 'f';
  /// Numpy constant
  static const int type_num = NPY_DOUBLE;
#endif
};

/// This structure contains the value for zero, one and some other operation for an double type
template <>
struct DataTypeTraits<long double>
{
  /// The difference between 1 and the least value greater than 1 that is representable
  static const long double epsilon(const long double data)
  {
    return std::numeric_limits<long double>::epsilon();
  }

  static const double zero(const long double data)
  {
    return 0.0;
  }

  static const double one(const long double data)
  {
    return 1.0;
  }

  /**
   * This function inverses a piece of data
   * @param data is the piece of data to be inverted
   * @return the inverted piece of data
   */
  static const long double inverse(const long double data)
  {
    return (1. / data);
  }

  /**
   * This function calculates the absolute value of a matrix
   * @param data is the piece of data
   * @return the absolute value of the piece of data
   */
  static const long double absolute(const long double data)
  {
    return std::abs(data);
  }

  /**
   * This function conjugates a piece of data
   * @param data is the piece of data to be conjugated
   * @return the conjugated piece of data
   */
  static const long double conjuge(const long double data)
  {
    return (data);
  }

  /**
   * This function returns the square of the norm2 of a piece of data
   * @param data is the piece of data to be normed
   * @return the norm2 of the piece of data
   */
  static const long double norm2(const long double data)
  {
    return (data * data);
  }

  /**
   * This function calulates the square root of a piece of data
   * @param data is the piece of data to be square-rooted
   * @return the square-rooted piece of data
   */
  static const long double sqrt(const long double data)
  {
    return std::sqrt(data);
  }

#ifdef USE_PYTHON
  /// Numpy char symbol
//  static const char type_kind = 'f';
  /// Numpy constant
  static const int type_num = NPY_LONGDOUBLE;
#endif
};
#endif
