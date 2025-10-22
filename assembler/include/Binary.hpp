#pragma once

#include <string>
#include <utility>

namespace hack_assembler {

template <size_t N>
class Binary {
 public:
  explicit Binary(const std::string value) : value_(std::move(value)) {
    if (!isValid(value_)) {
      throw std::invalid_argument("Invalid Hack binary string: " + value_);
    }
  }

  /**
   * Value getter method
   */
  const std::string& getValue() const noexcept { return value_; }

  /**
   * Binary equality operator
   */
  bool operator==(const Binary& other) const noexcept {
    return value_ == other.value_;
  }

  /**
   * Binary inequality operator
   */
  bool operator!=(const Binary& other) const noexcept {
    return !(*this == other);
  }

  /**
   * Binary validation method. Returns true if all the characters in the string
   * equal to 0 or 1, and the string length is N.
   */
  static bool isValid(const std::string& value) noexcept {
    if (value.length() != N) {
      return false;
    }
    return value.find_first_not_of("01") == std::string::npos;
  }

  friend std::ostream& operator<<(std::ostream& os, const Binary& bin) {
    return os << bin.getValue();
  }

 private:
  const std::string value_;
};

using CompBinary = Binary<7>;
using DestBinary = Binary<3>;
using JumpBinary = Binary<3>;
using InstructionBinary = Binary<16>;

}  // namespace hack_assembler
