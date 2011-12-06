/**
 * \file expression_template.h
 * Defines a set of templates that will be used for standard operations
 */

#ifndef EXPRESSIONTEMPLATE
#define EXPRESSIONTEMPLATE

#include <expression_template_iterators.h>

namespace IRT
{
  namespace Tools
  {
    /// Basic unary template
    template<class VectorType, unsigned char op>
    struct UnaryExpression
    {
    };

    enum
    {Minus='-', };

    /// The unary oppose expression
    template<class VectorType>
    struct UnaryExpression<VectorType, '-'>
    {
      /// The type of data inside the vector
      typedef typename VectorType::DataType DataType;
      /// The type of self
      typedef UnaryExpression<VectorType, '-'> Self;
      /// Typedef of comparison result
      typedef Vector<bool, staticHeight> ComparisonResult;
      /// Typedef of internal data
      typedef DataType* VectorType;

      /// Typedef for data traits
      typedef DataTypeTraits<DataType> DataTraits;

      /// Const iterator
      typedef OpposeExpressionIterator<const VectorType> const_iterator;

      /**
       * Default constructor
       * @param vector is the vector that will be transposed
       * \warning verify the reference thing
       */
      UnaryExpression<VectorType, '-'>(const VectorType& vector)
        :vector(vector)
      {
      }

      /** @name Other operations*/
      /// @{
      /**
       * Calculates the height of the vector
       * @return the height of the vector
       */
      unsigned long height() const
      {
        return vector.height();
      }

      /**
       * Calculates the width of the vector
       * @return the width of the vector
       */
      unsigned long width() const
      {
        return vector.width();
      }

      /**
       * Const subscript operator
       * @param i is the line selected
       * @param j is the column selected
       * @return the element in the vector at the emplacement [i,j]
       */
      const Data_Type operator()(unsigned long i, unsigned long j) const
      {
        assert(i < height());
        assert(j < width());
        return - vector(i, j);
      }
      ///@}

      /**
       * Iterator to the beginning of the vector
       * @return a const iterator on the beginning of the vector/expression
       */
      const_iterator begin() const
      {
        return const_iterator(vector.begin());
      }

      /**
       * Iterator to the end of the vector
       * @return a const iterator on the end of the vector/expression
       */
      const_iterator end() const
      {
        return const_iterator(vector.end());
      }
    private:
      /// A const ref to the vector that will be opposed
      const VectorType& vector;
    };

    /**
     * Encapsulates the creation of a opposed expression
     * @param vector is the expressiont emplate to transform
     * @return the opposed expression
     */
    template<class VectorType>
    const UnaryExpression<VectorType, '-'> makeOppose(const VectorType& vector)
    {
      return UnaryExpression<VectorType, '-'>(vector);
    }

    /// Basic binary template
    template<class VectorType1, class VectorType2, unsigned char op>
    struct BinaryExpression
    {
    };

    enum
    {Add = '+', Sub = '-', Mult = '*'};

    /// The binary addition expression
    template<class VectorType1, class VectorType2>
    struct BinaryExpression<VectorType1, VectorType2, '+'>
    {
      /// The type of data inside the vector
      typedef typename VectorType1::Data_Type Data_Type;
      /// The type of self
      typedef BinaryExpression<VectorType1, VectorType2, '+'> Self;
      /// Typedef of operation result
      typedef typename returnTypeStaticSize<VectorType1, VectorType2>::Type Result;
      /// Static dimensions
      enum{staticHeight = Result::staticHeight} ;
      /// Typedef of comparison result
      typedef Vector<bool, staticHeight, staticWidth> ComparisonResult;
      /// Typedef of column selection
      typedef typename ColumnVector<Data_Type, staticHeight>::Type Column;
      /// Typedef of line selection
      typedef typename LineVector<Data_Type, staticWidth>::Type Line;
      /// Typedef for <<
      typedef typename std::ostream ostream;
      /// Typedef for >>
      typedef typename std::istream istream;

      /// Typedef for data traits
      typedef DataTypeTraits<Data_Type> DataTraits;

      /// Const iterator
      typedef AdditionExpressionIterator<const VectorType1, const VectorType2> const_iterator;

      /**
       * Default constructor
       * @param vector1 is the first vector that will be added
       * @param vector2 is the second vector that will be added
       * \warning verify the reference thing
       */
      BinaryExpression<VectorType1, VectorType2, '+'>(const VectorType1& vector1, const VectorType2& vector2)
        :vector1(vector1), vector2(vector2)
      {
      }

      /** @name Other operations*/
      /// @{
      /**
       * Calculates the height of the vector
       * @return the height of the vector
       */
      unsigned long height() const
      {
        return vector1.height();
      }

      /**
       * Calculates the width of the vector
       * @return the width of the vector
       */
      unsigned long width() const
      {
        return vector1.width();
      }

      /**
       * Const subscript operator
       * @param i is the line selected
       * @param j is the column selected
       * @return the element in the vector at the emplacement [i,j]
       */
      const Data_Type operator()(unsigned long i, unsigned long j) const
      {
        assert(i < height());
        assert(j < width());
        return vector1(i, j) + vector2(i, j);
      }
      ///@}

      /**
       * Iterator to the beginning of the vector
       * @return a const iterator on the beginning of the vector/expression
       */
      const_iterator begin() const
      {
        return const_iterator(vector1.begin(), vector2.begin());
      }

      /**
       * Iterator to the end of the vector
       * @return a const iterator on the end of the vector/expression
       */
      const_iterator end() const
      {
        return const_iterator(vector1.end(), vector2.end());
      }
    private:
      /// A const ref to the first vector that will be added
      const VectorType1& vector1;
      /// A const ref to the second vector that will be added
      const VectorType2& vector2;
    };

    /// The binary addition expression
    template<class VectorType>
    struct BinaryExpression<VectorType, typename VectorType::Data_Type, '+'>
    {
      /// The type of data inside the vector
      typedef typename VectorType::Data_Type Data_Type;
      /// The type of self
      typedef BinaryExpression<VectorType, typename VectorType::Data_Type, '+'> Self;
      /// Typedef of operation result
      typedef typename VectorType::Result Result;
      /// Static dimensions
      enum{staticHeight = Result::staticHeight, staticWidth = Result::staticWidth} ;
      /// Typedef of comparison result
      typedef Vector<bool, staticHeight, staticWidth> ComparisonResult;
      /// Typedef of column selection
      typedef typename ColumnVector<Data_Type, staticHeight>::Type Column;
      /// Typedef of line selection
      typedef typename LineVector<Data_Type, staticWidth>::Type Line;
      /// Typedef for <<
      typedef typename std::ostream ostream;
      /// Typedef for >>
      typedef typename std::istream istream;

      /// Typedef for data traits
      typedef DataTypeTraits<Data_Type> DataTraits;

      /// Const iterator
      typedef AdditionConstantExpressionIterator<const VectorType> const_iterator;
      /**
       * Default constructor
       * @param vector is the vector that will be added
       * @param element is the element that will be added
       * \warning verify the reference thing
       */
      BinaryExpression<VectorType, typename VectorType::Data_Type, '+'>(const VectorType& vector, const Data_Type& element)
        :vector(vector), element(element)
      {
      }

      /** @name Other operations*/
      /// @{
      /**
       * Calculates the height of the vector
       * @return the height of the vector
       */
      unsigned long height() const
      {
        return vector.height();
      }

      /**
       * Calculates the width of the vector
       * @return the width of the vector
       */
      unsigned long width() const
      {
        return vector.width();
      }

      /**
       * Const subscript operator
       * @param i is the line selected
       * @param j is the column selected
       * @return the element in the vector at the emplacement [i,j]
       */
      const Data_Type operator()(unsigned long i, unsigned long j) const
      {
        assert(i < height());
        assert(j < width());
        return vector(i, j) + element;
      }
      ///@}

      /**
       * Iterator to the beginning of the vector
       * @return a const iterator on the beginning of the vector/expression
       */
      const_iterator begin() const
      {
        return const_iterator(vector.begin(), element);
      }

      /**
       * Iterator to the end of the vector
       * @return a const iterator on the end of the vector/expression
       */
      const_iterator end() const
      {
        return const_iterator(vector.end(), element);
      }
    private:
      /// A const ref to the first vector that will be added
      const VectorType& vector;
      /// A const ref to the second vector that will be added
      const Data_Type& element;
    };

    /// The binary addition expression
    template<class VectorType>
    struct BinaryExpression<typename VectorType::Data_Type, VectorType, '+'>
    {
      /// The type of data inside the vector
      typedef typename VectorType::Data_Type Data_Type;
      /// The type of self
      typedef BinaryExpression<VectorType, typename VectorType::Data_Type, '+'> Self;
      /// Typedef of operation result
      typedef typename VectorType::Result Result;
      /// Static dimensions
      enum{staticHeight = Result::staticHeight, staticWidth = Result::staticWidth} ;
      /// Typedef of comparison result
      typedef Vector<bool, staticHeight, staticWidth> ComparisonResult;
      /// Typedef of column selection
      typedef typename ColumnVector<Data_Type, staticHeight>::Type Column;
      /// Typedef of line selection
      typedef typename LineVector<Data_Type, staticWidth>::Type Line;
      /// Typedef for <<
      typedef typename std::ostream ostream;
      /// Typedef for >>
      typedef typename std::istream istream;

      /// Typedef for data traits
      typedef DataTypeTraits<Data_Type> DataTraits;

      /// Const iterator
      typedef ConstantAdditionExpressionIterator<const VectorType> const_iterator;

      /**
       * Default constructor
       * @param vector is the vector that will be added
       * @param element is the element that will be added
       * \warning verify the reference thing
       */
      BinaryExpression<typename VectorType::Data_Type, VectorType, '+'>(const Data_Type& element, const VectorType& vector)
        :vector(vector), element(element)
      {
      }

      /** @name Other operations*/
      /// @{
      /**
       * Calculates the height of the vector
       * @return the height of the vector
       */
      unsigned long height() const
      {
        return vector.height();
      }

      /**
       * Calculates the width of the vector
       * @return the width of the vector
       */
      unsigned long width() const
      {
        return vector.width();
      }

      /**
       * Const subscript operator
       * @param i is the line selected
       * @param j is the column selected
       * @return the element in the vector at the emplacement [i,j]
       */
      const Data_Type operator()(unsigned long i, unsigned long j) const
      {
        assert(i < height());
        assert(j < width());
        return element + vector(i, j);
      }
      ///@}

      /**
       * Iterator to the beginning of the vector
       * @return a const iterator on the beginning of the vector/expression
       */
      const_iterator begin() const
      {
        return const_iterator(vector.begin(), element);
      }

      /**
       * Iterator to the end of the vector
       * @return a const iterator on the end of the vector/expression
       */
      const_iterator end() const
      {
        return const_iterator(vector.end(), element);
      }
    private:
      /// A const ref to the first vector that will be added
      const VectorType& vector;
      /// A const ref to the second vector that will be added
      const Data_Type& element;
    };

    /**
     * Encapsulates the creation of a addition expression
     * @param vector is the expression template to transform
     * @return the addition expression
     */
    template<class VectorType1, class VectorType2>
    const BinaryExpression<VectorType1, VectorType2, '+'> makeAdd(const VectorType1& vector1, const VectorType2& vector2)
    {
      return BinaryExpression<VectorType1, VectorType2, '+'>(vector1, vector2);
    }

    /// The binary addition expression
    template<class VectorType1, class VectorType2>
    struct BinaryExpression<VectorType1, VectorType2, '-'>
    {
      /// The type of data inside the vector
      typedef typename VectorType1::Data_Type Data_Type;
      /// The type of self
      typedef BinaryExpression<VectorType1, VectorType2, '-'> Self;
      /// Typedef of operation result
      typedef typename returnTypeStaticSize<VectorType1, VectorType2>::Type Result;
      /// Static dimensions
      enum{staticHeight = Result::staticHeight, staticWidth = Result::staticWidth} ;
      /// Typedef of comparison result
      typedef Vector<bool, staticHeight, staticWidth> ComparisonResult;
      /// Typedef of column selection
      typedef typename ColumnVector<Data_Type, staticHeight>::Type Column;
      /// Typedef of line selection
      typedef typename LineVector<Data_Type, staticWidth>::Type Line;
      /// Typedef for <<
      typedef typename std::ostream ostream;
      /// Typedef for >>
      typedef typename std::istream istream;

      /// Typedef for data traits
      typedef DataTypeTraits<Data_Type> DataTraits;

      /// Const iterator
      typedef SubstractionExpressionIterator<const VectorType1, const VectorType2> const_iterator;

      /**
       * Default constructor
       * @param vector is the vector that will be transposed
       * \warning verify the reference thing
       */
      BinaryExpression<VectorType1, VectorType2, '-'>(const VectorType1& vector1, const VectorType2& vector2)
        :vector1(vector1), vector2(vector2)
      {
      }

      /** @name Other operations*/
      /// @{
      /**
       * Calculates the height of the vector
       * @return the height of the vector
       */
      unsigned long height() const
      {
        return vector1.height();
      }

      /**
       * Calculates the width of the vector
       * @return the width of the vector
       */
      unsigned long width() const
      {
        return vector1.width();
      }

      /**
       * Const subscript operator
       * @param i is the line selected
       * @param j is the column selected
       * @return the element in the vector at the emplacement [i,j]
       */
      const Data_Type operator()(unsigned long i, unsigned long j) const
      {
        assert(i < height());
        assert(j < width());
        return vector1(i, j) - vector2(i, j);
      }

      /**
       * Iterator to the beginning of the vector
       * @return a const iterator on the beginning of the vector/expression
       */
      const_iterator begin() const
      {
        return const_iterator(vector1.begin(), vector2.begin());
      }

      /**
       * Iterator to the end of the vector
       * @return a const iterator on the end of the vector/expression
       */
      const_iterator end() const
      {
        return const_iterator(vector1.end(), vector2.end());
      }
      ///@}

    private:
      /// A const ref to the first vector that will be substracted
      const VectorType1& vector1;
      /// A const ref to the second vector that will be substracted
      const VectorType2& vector2;
    };

    /// The binary substraction expression
    template<class VectorType>
    struct BinaryExpression<VectorType, typename VectorType::Data_Type, '-'>
    {
      /// The type of data inside the vector
      typedef typename VectorType::Data_Type Data_Type;
      /// The type of self
      typedef BinaryExpression<VectorType, typename VectorType::Data_Type, '-'> Self;
      /// Typedef of operation result
      typedef typename VectorType::Result Result;
      /// Static dimensions
      enum{staticHeight = Result::staticHeight, staticWidth = Result::staticWidth} ;
      /// Typedef of comparison result
      typedef Vector<bool, staticHeight, staticWidth> ComparisonResult;
      /// Typedef of column selection
      typedef typename ColumnVector<Data_Type, staticHeight>::Type Column;
      /// Typedef of line selection
      typedef typename LineVector<Data_Type, staticWidth>::Type Line;
      /// Typedef for <<
      typedef typename std::ostream ostream;
      /// Typedef for >>
      typedef typename std::istream istream;

      /// Typedef for data traits
      typedef DataTypeTraits<Data_Type> DataTraits;

      /// Const iterator
      typedef SubstractionConstantExpressionIterator<const VectorType> const_iterator;

      /**
       * Default constructor
       * @param vector is the vector that will be substracted
       * @param element is the element that will be substracted
       * \warning verify the reference thing
       */
      BinaryExpression<VectorType, typename VectorType::Data_Type, '-'>(const VectorType& vector, const Data_Type& element)
        :vector(vector), element(element)
      {
      }

      /** @name Other operations*/
      /// @{
      /**
       * Calculates the height of the vector
       * @return the height of the vector
       */
      unsigned long height() const
      {
        return vector.height();
      }

      /**
       * Calculates the width of the vector
       * @return the width of the vector
       */
      unsigned long width() const
      {
        return vector.width();
      }

      /**
       * Const subscript operator
       * @param i is the line selected
       * @param j is the column selected
       * @return the element in the vector at the emplacement [i,j]
       */
      const Data_Type operator()(unsigned long i, unsigned long j) const
      {
        assert(i < height());
        assert(j < width());
        return vector(i, j) - element;
      }

      /**
       * Iterator to the beginning of the vector
       * @return a const iterator on the beginning of the vector/expression
       */
      const_iterator begin() const
      {
        return const_iterator(vector.begin(), element);
      }

      /**
       * Iterator to the end of the vector
       * @return a const iterator on the end of the vector/expression
       */
      const_iterator end() const
      {
        return const_iterator(vector.end(), element);
      }
      ///@}

    private:
      /// A const ref to the first vector that will be substracted
      const VectorType& vector;
      /// A const ref to the second vector that will be substracted
      const Data_Type& element;
    };

    /// The binary substraction expression
    template<class VectorType>
    struct BinaryExpression<typename VectorType::Data_Type, VectorType, '-'>
    {
      /// The type of data inside the vector
      typedef typename VectorType::Data_Type Data_Type;
      /// The type of self
      typedef BinaryExpression<VectorType, typename VectorType::Data_Type, '-'> Self;
      /// Typedef of operation result
      typedef typename VectorType::Result Result;
      /// Static dimensions
      enum{staticHeight = Result::staticHeight, staticWidth = Result::staticWidth} ;
      /// Typedef of comparison result
      typedef Vector<bool, staticHeight, staticWidth> ComparisonResult;
      /// Typedef of column selection
      typedef typename ColumnVector<Data_Type, staticHeight>::Type Column;
      /// Typedef of line selection
      typedef typename LineVector<Data_Type, staticWidth>::Type Line;
      /// Typedef for <<
      typedef typename std::ostream ostream;
      /// Typedef for >>
      typedef typename std::istream istream;

      /// Typedef for data traits
      typedef DataTypeTraits<Data_Type> DataTraits;

      /// Const iterator
      typedef ConstantSubstractionExpressionIterator<const VectorType> const_iterator;

      /**
       * Default constructor
       * @param vector is the vector that will be substracted
       * @param element is the element that will be substracted
       * \warning verify the reference thing
       */
      BinaryExpression<typename VectorType::Data_Type, VectorType, '-'>(const Data_Type& element, const VectorType& vector)
        :vector(vector), element(element)
      {
      }

      /** @name Other operations*/
      /// @{
      /**
       * Calculates the height of the vector
       * @return the height of the vector
       */
      unsigned long height() const
      {
        return vector.height();
      }

      /**
       * Calculates the width of the vector
       * @return the width of the vector
       */
      unsigned long width() const
      {
        return vector.width();
      }

      /**
       * Const subscript operator
       * @param i is the line selected
       * @param j is the column selected
       * @return the element in the vector at the emplacement [i,j]
       */
      const Data_Type operator()(unsigned long i, unsigned long j) const
      {
        assert(i < height());
        assert(j < width());
        return element - vector(i, j);
      }

      /**
       * Iterator to the beginning of the vector
       * @return a const iterator on the beginning of the vector/expression
       */
      const_iterator begin() const
      {
        return const_iterator(vector.begin(), element);
      }

      /**
       * Iterator to the end of the vector
       * @return a const iterator on the end of the vector/expression
       */
      const_iterator end() const
      {
        return const_iterator(vector.end(), element);
      }
      ///@}

    private:
      /// A const ref to the first vector that will be substracted
      const VectorType& vector;
      /// A const ref to the second vector that will be substracted
      const Data_Type& element;
    };

    /**
     * Encapsulates the creation of a substraction expression
     * @param vector is the expression template to transform
     * @return the substraction expression
     */
    template<class VectorType1, class VectorType2>
    const BinaryExpression<VectorType1, VectorType2, '-'> makeSub(const VectorType1& vector1, const VectorType2& vector2)
    {
      return BinaryExpression<VectorType1, VectorType2, '-'>(vector1, vector2);
    }

    /// The binary multiplication expression
    template<class VectorType1, class VectorType2>
    struct BinaryExpression<VectorType1, VectorType2, '*'>
    {
      /// The type of data inside the vector
      typedef typename VectorType1::Data_Type Data_Type;
      /// The type of self
      typedef BinaryExpression<VectorType1, VectorType2, '*'> Self;
      /// Typedef of operation result
      typedef typename returnTypeMultiplicationSize<VectorType1, VectorType2>::Type Result;
      /// Static dimensions
      enum{staticHeight = Result::staticHeight, staticWidth = Result::staticWidth} ;
      /// Typedef of comparison result
      typedef Vector<bool, staticHeight, staticWidth> ComparisonResult;
      /// Typedef of column selection
      typedef typename ColumnVector<Data_Type, staticHeight>::Type Column;
      /// Typedef of line selection
      typedef typename LineVector<Data_Type, staticWidth>::Type Line;
      /// Typedef for <<
      typedef typename std::ostream ostream;
      /// Typedef for >>
      typedef typename std::istream istream;

      /// Typedef for data traits
      typedef DataTypeTraits<Data_Type> DataTraits;

      /// Const iterator
      typedef MultiplicationExpressionIterator<const VectorType1, const VectorType2> const_iterator;
      /**
       * Default constructor
       * @param vector is the vector that will be transposed
       * \warning verify the reference thing
       */
      BinaryExpression<VectorType1, VectorType2, '*'>(const VectorType1& vector1, const VectorType2& vector2)
        :vector1(vector1), vector2(vector2)
      {
      }

      /** @name Other operations*/
      /// @{
      /**
       * Calculates the height of the vector
       * @return the height of the vector
       */
      unsigned long height() const
      {
        return vector1.height();
      }

      /**
       * Calculates the width of the vector
       * @return the width of the vector
       */
      unsigned long width() const
      {
        return vector2.width();
      }

      /**
       * Const subscript operator
       * @param i is the line selected
       * @param j is the column selected
       * @return the element in the vector at the emplacement [i,j]
       */
      const Data_Type operator()(unsigned long i, unsigned long j) const
      {
        assert(i < height());
        assert(j < width());
        Data_Type result = DataTypeTraits<Data_Type>::zero(vector1(i, 0) * vector2(0, j));
        for(unsigned long k = 0; k < vector1.width(); ++k)
        {
          result += vector1(i,k) * vector2(k,j);
        }
        return result;
      }

      /**
       * Iterator to the beginning of the vector
       * @return a const iterator on the beginning of the vector/expression
       */
      const_iterator begin() const
      {
        return const_iterator(vector1.begin(), vector2.begin());
      }

      /**
       * Iterator to the end of the vector
       * @return a const iterator on the end of the vector/expression
       */
      const_iterator end() const
      {
        return const_iterator(vector1.end(), vector2.end());
      }
      ///@}

    private:
      /// A const ref to the first vector that will be multiplied
      const VectorType1& vector1;
      /// A const ref to the second vector that will be multiplied
      const VectorType2& vector2;
    };

    /// The binary multiplication expression
    template<class VectorType1, class VectorType2>
    struct BinaryExpression<DiagonalVector<VectorType1>, VectorType2, '*'>
    {
      /// The type of data inside the vector
      typedef typename VectorType1::Data_Type Data_Type;
      /// The type of self
      typedef BinaryExpression<DiagonalVector<VectorType1>, VectorType2, '*'> Self;
      /// Typedef of operation result
      typedef typename returnTypeMultiplicationSize<DiagonalVector<VectorType1>, VectorType2>::Type Result;
      /// Static dimensions
      enum{staticHeight = Result::staticHeight, staticWidth = Result::staticWidth} ;
      /// Typedef of comparison result
      typedef Vector<bool, staticHeight, staticWidth> ComparisonResult;
      /// Typedef of column selection
      typedef typename ColumnVector<Data_Type, staticHeight>::Type Column;
      /// Typedef of line selection
      typedef typename LineVector<Data_Type, staticWidth>::Type Line;
      /// Typedef for <<
      typedef typename std::ostream ostream;
      /// Typedef for >>
      typedef typename std::istream istream;

      /// Typedef for data traits
      typedef DataTypeTraits<Data_Type> DataTraits;

      /**
       * Default constructor
       * @param vector is the vector that will be transposed
       * \warning verify the reference thing
       */
      BinaryExpression<DiagonalVector<VectorType1>, VectorType2, '*'>(const DiagonalVector<VectorType1>& vector1, const VectorType2& vector2)
        :vector1(vector1), vector2(vector2)
      {
      }

      /** @name Other operations*/
      /// @{
      /**
       * Calculates the height of the vector
       * @return the height of the vector
       */
      unsigned long height() const
      {
        return vector1.height();
      }

      /**
       * Calculates the width of the vector
       * @return the width of the vector
       */
      unsigned long width() const
      {
        return vector2.width();
      }

      /**
       * Const subscript operator
       * @param i is the line selected
       * @param j is the column selected
       * @return the element in the vector at the emplacement [i,j]
       */
      const Data_Type operator()(unsigned long i, unsigned long j) const
      {
        assert(i < height());
        assert(j < width());
        return vector1(i,i) * vector2(i,j);
      }
      ///@}

    private:
      /// A const ref to the first vector that will be multiplied
      const DiagonalVector<VectorType1>& vector1;
      /// A const ref to the second vector that will be multiplied
      const VectorType2& vector2;
    };

    /// The binary multiplication expression
    template<class VectorType1, class VectorType2>
    struct BinaryExpression<VectorType1, DiagonalVector<VectorType2>, '*'>
    {
      /// The type of data inside the vector
      typedef typename VectorType1::Data_Type Data_Type;
      /// The type of self
      typedef BinaryExpression<VectorType1, DiagonalVector<VectorType2>, '*'> Self;
      /// Typedef of operation result
      typedef typename returnTypeMultiplicationSize<VectorType1, DiagonalVector<VectorType2> >::Type Result;
      /// Static dimensions
      enum{staticHeight = Result::staticHeight, staticWidth = Result::staticWidth} ;
      /// Typedef of comparison result
      typedef Vector<bool, staticHeight, staticWidth> ComparisonResult;
      /// Typedef of column selection
      typedef typename ColumnVector<Data_Type, staticHeight>::Type Column;
      /// Typedef of line selection
      typedef typename LineVector<Data_Type, staticWidth>::Type Line;
      /// Typedef for <<
      typedef typename std::ostream ostream;
      /// Typedef for >>
      typedef typename std::istream istream;

      /// Typedef for data traits
      typedef DataTypeTraits<Data_Type> DataTraits;

      /**
       * Default constructor
       * @param vector is the vector that will be transposed
       * \warning verify the reference thing
       */
      BinaryExpression<VectorType1, DiagonalVector<VectorType2>, '*'>(const VectorType1& vector1, const DiagonalVector<VectorType2>& vector2)
        :vector1(vector1), vector2(vector2)
      {
      }

      /** @name Other operations*/
      /// @{
      /**
       * Calculates the height of the vector
       * @return the height of the vector
       */
      unsigned long height() const
      {
        return vector1.height();
      }

      /**
       * Calculates the width of the vector
       * @return the width of the vector
       */
      unsigned long width() const
      {
        return vector2.width();
      }

      /**
       * Const subscript operator
       * @param i is the line selected
       * @param j is the column selected
       * @return the element in the vector at the emplacement [i,j]
       */
      const Data_Type operator()(unsigned long i, unsigned long j) const
      {
        assert(i < height());
        assert(j < width());
        return vector1(i,j) * vector2(j,j);
      }
      ///@}

    private:
      /// A const ref to the first vector that will be multiplied
      const VectorType1& vector1;
      /// A const ref to the second vector that will be multiplied
      const DiagonalVector<VectorType2>& vector2;
    };

    /// The binary multiplication expression
    template<class VectorType>
    struct BinaryExpression<VectorType, typename VectorType::Data_Type, '*'>
    {
      /// The type of data inside the vector
      typedef typename VectorType::Data_Type Data_Type;
      /// The type of self
      typedef BinaryExpression<VectorType, typename VectorType::Data_Type, '*'> Self;
      /// Typedef of operation result
      typedef VectorType Result;
      /// Static dimensions
      enum{staticHeight = Result::staticHeight, staticWidth = Result::staticWidth} ;
      /// Typedef of comparison result
      typedef Vector<bool, staticHeight, staticWidth> ComparisonResult;
      /// Typedef of column selection
      typedef typename ColumnVector<Data_Type, staticHeight>::Type Column;
      /// Typedef of line selection
      typedef typename LineVector<Data_Type, staticWidth>::Type Line;
      /// Typedef for <<
      typedef typename std::ostream ostream;
      /// Typedef for >>
      typedef typename std::istream istream;

      /// Typedef for data traits
      typedef DataTypeTraits<Data_Type> DataTraits;

      /// Const iterator
      typedef ConstantMultiplicationExpressionIterator<const VectorType> const_iterator;

      /**
       * Default constructor
       * @param vector is the vector that will be substracted
       * @param element is the element that will be substracted
       * \warning verify the reference thing
       */
      BinaryExpression<VectorType, typename VectorType::Data_Type, '*'>(const VectorType& vector, const Data_Type& element)
        :vector(vector), element(element)
      {
      }

      /** @name Other operations*/
      /// @{
      /**
       * Calculates the height of the vector
       * @return the height of the vector
       */
      unsigned long height() const
      {
        return vector.height();
      }

      /**
       * Calculates the width of the vector
       * @return the width of the vector
       */
      unsigned long width() const
      {
        return vector.width();
      }

      /**
       * Const subscript operator
       * @param i is the line selected
       * @param j is the column selected
       * @return the element in the vector at the emplacement [i,j]
       */
      const Data_Type operator()(unsigned long i, unsigned long j) const
      {
        assert(i < height());
        assert(j < width());
        return vector(i, j) * element;
      }

      /**
       * Iterator to the beginning of the vector
       * @return a const iterator on the beginning of the vector/expression
       */
      const_iterator begin() const
      {
        return const_iterator(vector.begin(), element);
      }

      /**
       * Iterator to the end of the vector
       * @return a const iterator on the end of the vector/expression
       */
      const_iterator end() const
      {
        return const_iterator(vector.end(), element);
      }
      ///@}

    private:
      /// A const ref to the first vector that will be multiplied
      const VectorType& vector;
      /// A const ref to the second vector that will be multiplied
      const Data_Type& element;
    };

    /// The binary multiplication expression
    template<class VectorType>
    struct BinaryExpression<typename VectorType::Data_Type, VectorType, '*'>
    {
      /// The type of data inside the vector
      typedef typename VectorType::Data_Type Data_Type;
      /// The type of self
      typedef BinaryExpression<VectorType, typename VectorType::Data_Type, '*'> Self;
      /// Typedef of operation result
      typedef VectorType Result;
      /// Static dimensions
      enum{staticHeight = Result::staticHeight, staticWidth = Result::staticWidth} ;
      /// Typedef of comparison result
      typedef Vector<bool, staticHeight, staticWidth> ComparisonResult;
      /// Typedef of column selection
      typedef typename ColumnVector<Data_Type, staticHeight>::Type Column;
      /// Typedef of line selection
      typedef typename LineVector<Data_Type, staticWidth>::Type Line;
      /// Typedef for <<
      typedef typename std::ostream ostream;
      /// Typedef for >>
      typedef typename std::istream istream;

      /// Typedef for data traits
      typedef DataTypeTraits<Data_Type> DataTraits;

      /// Const iterator
      typedef MultiplicationConstantExpressionIterator<const VectorType> const_iterator;

      /**
       * Default constructor
       * @param vector is the vector that will be multiplied
       * @param element is the element that will be multiplied
       * \warning verify the reference thing
       */
      BinaryExpression<typename VectorType::Data_Type, VectorType, '*'>(const Data_Type& element, const VectorType& vector)
        :vector(vector), element(element)
      {
      }

      /** @name Other operations*/
      /// @{
      /**
       * Calculates the height of the vector
       * @return the height of the vector
       */
      unsigned long height() const
      {
        return vector.height();
      }

      /**
       * Calculates the width of the vector
       * @return the width of the vector
       */
      unsigned long width() const
      {
        return vector.width();
      }

      /**
       * Const subscript operator
       * @param i is the line selected
       * @param j is the column selected
       * @return the element in the vector at the emplacement [i,j]
       */
      const Data_Type operator()(unsigned long i, unsigned long j) const
      {
        assert(i < height());
        assert(j < width());
        return element * vector(i, j);
      }

      /**
       * Iterator to the beginning of the vector
       * @return a const iterator on the beginning of the vector/expression
       */
      const_iterator begin() const
      {
        return const_iterator(vector.begin(), element);
      }

      /**
       * Iterator to the end of the vector
       * @return a const iterator on the end of the vector/expression
       */
      const_iterator end() const
      {
        return const_iterator(vector.end(), element);
      }
      ///@}

    private:
      /// A const ref to the first vector that will be multiplied
      const VectorType& vector;
      /// A const ref to the second vector that will be multiplied
      const Data_Type& element;
    };

    /**
     * Encapsulates the creation of a multiplication expression
     * @param vector is the expression template to transform
     * @return the multiplication expression
     */
    template<class VectorType1, class VectorType2>
    const BinaryExpression<VectorType1, VectorType2, '*'> makeMult(const VectorType1& vector1, const VectorType2& vector2)
    {
      return BinaryExpression<VectorType1, VectorType2, '*'>(vector1, vector2);
    }
  }
}
#endif
