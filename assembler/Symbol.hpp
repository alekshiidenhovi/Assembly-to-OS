#pragma once
#include <functional>
#include <ostream>
#include <regex>
#include <string>
#include <utility>

namespace hack_assembler {
class Symbol {
 public:
  /**
   * Single argument constructor
   */
  explicit Symbol(std::string value) : value_(std::move(value)) {
    if (!isValid(value_)) {
      throw std::invalid_argument("Invalid Hack symbol: " + value_);
    }
  }

  /**
   * String conversion method
   */
  const std::string& getValue() const noexcept { return value_; }

  /**
   * Symbol equality operator
   */
  bool operator==(const Symbol& other) const noexcept {
    return value_ == other.value_;
  }

  /**
   * Symbol inequality operator
   */
  bool operator!=(const Symbol& other) const noexcept {
    return !(*this == other);
  }

  /**
   * Symbol validation method. Returns true if the symbol adheres to Hack
   * assembler rules.
   *
   * A symbol:
   *   - can be any sequence of letters, digits, underscores, dots, dollar
   * signs, and colon.
   *   - cannot start with a digit.
   */
  static bool isValid(const std::string& s) {
    static const std::regex pattern(R"(^[A-Za-z_\.\$\:][A-Za-z0-9_\.\$\:]*$)");
    return regex_match(s, pattern);
  }
  friend std::ostream& operator<<(std::ostream& os, const Symbol& symbol) {
    return os << symbol.getValue();
  }

 private:
  const std::string value_;
};
}  // namespace hack_assembler

namespace std {
template <>
struct hash<hack_assembler::Symbol> {
  size_t operator()(const hack_assembler::Symbol& s) const noexcept {
    return hash<string>()(s.getValue());
  }
};
}  // namespace std
