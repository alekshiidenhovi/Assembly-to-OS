#pragma once
#include <string>

namespace hack_assembler {

/**
 * A Hack constant class. Encapsulates a 16-bit integer constant,
 */
class Constant {
 public:
  /**
   * Single argument constructor
   */
  explicit Constant(std::string value) : value_(std::stoi(value)) {
    if (!isValid(value)) {
      throw std::invalid_argument("Invalid Hack constant: " + value);
    }
  }

  /**
   * Value getter method
   */
  short getValue() const { return value_; }

  /**
   * Constant equality operator
   */
  bool operator==(const Constant& other) const noexcept {
    return value_ == other.value_;
  }

  /**
   * Constant inequality operator
   */
  bool operator!=(const Constant& other) const noexcept {
    return !(*this == other);
  }

  /**
   * Constant validation method. Returns true if the constant adheres to Hack
   * assembler rules.
   *
   * A constant is a value in the range of 0-32767 and is written in decimal
   * notation.
   */
  static bool isValid(const std::string& s);

 private:
  const short value_;
};

}  // namespace hack_assembler
