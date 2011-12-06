/**
 * \file test_functions.h
 * Some test functions and variables.
 * This files includes the prototypes of some conversion functions, the declaration of assertions functions and macros
 */

#ifndef CLASS_TEST_H
#define CLASS_TEST_H

#include <boost/lexical_cast.hpp>
#include <iostream>

namespace Tester
{
  /// Class trown when an assert is false
  struct Thrown
  {
    Thrown(const std::string& title, const std::string& explanation, const std::string& line, const std::string& function, const std::string& file)
      :title(title), explanation(explanation), line(line), function(function), file(file)
    {
      std::cerr << title << "\n" << explanation << "\n" << "file : " << file << "(l" << line << ") : " << function << std::endl;
    }
    /// Title of the exception
    std::string title;
    /// Explanation of the exception
    std::string explanation;
    /// Line in the file where the exception was raised
    std::string line;
    /// Function in the file where the exception was raised
    std::string function;
    /// File where the exception was raised
    std::string file;
  };

  /// Assertion for equality
  template<class T1, class T2>
  void assertEqual(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(rhs == lhs)
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert Equal (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Equal (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Not Equal to ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for no equality
  template<class T1, class T2>
  void assertNotEqual(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(!(rhs == lhs))
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert NotEqual (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Equal (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" different from ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for difference
  template<class T1, class T2>
  void assertDifferent(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(rhs != lhs)
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert Different (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Different (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Not different from ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for no difference
  template<class T1, class T2>
  void assertNotDifferent(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(!(rhs != lhs))
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert NotDifferent (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Different (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Equal from ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for inferiority
  template<class T1, class T2>
  void assertLess(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(rhs < lhs)
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert Less (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Less (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Not less than ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for no inferiority
  template<class T1, class T2>
  void assertNotLess(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(!(rhs < lhs))
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert NotLess (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Less (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Greater than ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for superiority
  template<class T1, class T2>
  void assertGreater(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(rhs > lhs)
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert Great (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Great (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Not greater than ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for no superiority
  template<class T1, class T2>
  void assertNotGreater(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(!(rhs > lhs))
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert NotGreat (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Great (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Less than ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for true
  template<class T1>
  void assertTrue(const T1& rhs, unsigned int line, const char* function, const char* file)
  {
    if(rhs)
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert True (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert True (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" not True"), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for false
  template<class T1>
  void assertFalse(const T1& rhs, unsigned int line, const char* function, const char* file)
  {
    if(!rhs)
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert False (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert False (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" not False"), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for equality
  template<class T1, class T2>
  void assertEqualArray(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(rhs == lhs)
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert EqualArray (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Equal (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Not Equal to ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for no equality
  template<class T1, class T2>
  void assertNotEqualArray(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(!(rhs == lhs))
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert NotEqualArray (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Equal (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" different from ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for difference
  template<class T1, class T2>
  void assertDifferentArray(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(rhs != lhs)
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert DifferentArray (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Different (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Not different from ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for no difference
  template<class T1, class T2>
  void assertNotDifferentArray(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(!(rhs != lhs))
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert NotDifferentArray (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Different (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Equal from ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for inferiority
  template<class T1, class T2>
  void assertLessArray(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(rhs < lhs)
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert LessArray (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Less (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Not less than ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for no inferiority
  template<class T1, class T2>
  void assertNotLessArray(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(rhs < lhs)
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert NotLessArray (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Less (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Greater than ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for superiority
  template<class T1, class T2>
  void assertGreaterArray(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(rhs > lhs)
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert GreatArray (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Great (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Not greater than ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assertion for no superiority
  template<class T1, class T2>
  void assertNotGreaterArray(const T1& rhs, const T2& lhs, unsigned int line, const char* function, const char* file)
  {
    if(!(rhs > lhs))
    {
    }
    else
    {
      throw(Thrown(std::string("Failure in assert NotGreatArray (l") + boost::lexical_cast<std::string>(line) + (")"), std::string("Failure in assert Great (l") + boost::lexical_cast<std::string>(line) + ("): ") + boost::lexical_cast<std::string>(rhs) + std::string(" Less than ") + boost::lexical_cast<std::string>(lhs), boost::lexical_cast<std::string>(line), function, file));
    }
  }

  /// Assert that only one kind of exception is thrown
  template<class Exception>
  void assertNoThrow(void (FunctionPtr)(), unsigned int line, const char* function, const char* file)
  {
    try
    {
      FunctionPtr();
    }
    catch(const Exception& exception)
    {
    }
  }
}

#define assertEqual(a, b) Tester::assertEqual(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertNotEqual(a, b) Tester::assertNotEqual(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertDifferent(a, b) Tester::assertDifferent(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertNotDifferent(a, b) Tester::assertNotDifferent(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertLess(a, b) Tester::assertLess(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertNotLess(a, b) Tester::assertNotLess(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertGreater(a, b) Tester::assertGreater(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertNotGreater(a, b) Tester::assertNotGreater(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertTrue(a) Tester::assertTrue(a, __LINE__, __FUNCTION__, __FILE__)
#define assertFalse(a) Tester::assertFalse(a, __LINE__, __FUNCTION__, __FILE__)
#define assertEqualArray(a, b) Tester::assertEqualArray(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertNotEqualArray(a, b) Tester::assertNotEqualArray(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertDifferentArray(a, b) Tester::assertDifferentArray(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertNotDifferentArray(a, b) Tester::assertNotDifferentArray(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertLessArray(a, b) Tester::assertLessArray(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertNotLessArray(a, b) Tester::assertNotLessArray(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertGreaterArray(a, b) Tester::assertGreaterArray(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertNotGreaterArray(a, b) Tester::assertNotGreaterArray(a, b, __LINE__, __FUNCTION__, __FILE__)
#define assertNoThrow(a, b) Tester::assertNoThrow<a >(b, __LINE__, __FUNCTION__, __FILE__)
#define thrown(a, b) Tester::Thrown(a, b, boost::lexical_cast<std::string>(__LINE__), __FUNCTION__, __FILE__)

#endif
