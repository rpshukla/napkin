#ifndef NAPKIN_NOBJECT_H_
#define NAPKIN_NOBJECT_H_

#include <string>
#include <vector>


/**
 * C++ representations of objects in the napkin language.
 */

namespace napkin {

// Forward declare Interpreter class
class Interpreter;

/**
 * All possible types of objects in the napkin language.
 */
enum NType {
  N_REAL_NUMBER,
  N_COMPLEX_NUMBER,
  N_BOOLEAN,
  N_STRING,
  N_CALLABLE,
};

/**
 * Base class for all napkin objects.
 */
class NObject {
public:
  virtual NType getType() {
    return type;
  }
  // Like python's __repr__()
  virtual std::string repr() = 0;
protected:
  NType type; // Store runtime type information
};

/**
 * Real numbers.
 */
class NRealNumber : public NObject {
public:
  NRealNumber(double t_value) : value(t_value) {
    type = N_REAL_NUMBER;
  };
  double value;

  virtual std::string repr() {
    return std::to_string(value);
  }
};

/**
 * Complex numbers.
 */
class NComplexNumber : public NObject {
public:
  NComplexNumber(double t_re, double t_im) : re(t_re), im(t_im) {
    type = N_COMPLEX_NUMBER;
  }
  double re;
  double im;

  virtual std::string repr() {
    std::string re_str = std::to_string(re);
    std::string im_str = std::to_string(im);
    return re_str + " + j" + im_str;
  }
};

/**
 * Booleans.
 */
class NBoolean : public NObject {
public:
  NBoolean(bool t_value) : value(t_value) {
    type = N_BOOLEAN;
  }
  bool value;

  virtual std::string repr() {
    return (value ? "true" : "false");
  }
};

/**
 * Strings.
 */
class NString : public NObject {
public:
  NString(std::string t_value) : value(t_value) {
    type = N_STRING;
  }
  std::string value;

  virtual std::string repr() {
    return value;
  }
};

/**
 * Base class for callable objects.
 */
class NCallable : public NObject {
public:
  NCallable() {
    type = N_CALLABLE;
  }
  virtual NObject *call(Interpreter *interpreter,
                        std::vector<NObject *> arguments) = 0;
  virtual int arity() = 0;
};

/**
 * Null type.
 */
class NNullType : public NObject {
public:
  NNullType() {};

  virtual std::string repr() {
    return "null";
  }
};

} // namespace napkin

#endif
