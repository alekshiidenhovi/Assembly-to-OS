#pragma once
#include <string>

#include "Validated.hpp"

namespace hack_assembler {

/**
 * A Hack constant class. Encapsulates a 16-bit integer constant,
 */
class Constant : public Validated<Constant, short> {
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
   * Return the value of the constant value
   */
  const short& getValue() const noexcept { return value_; }

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
