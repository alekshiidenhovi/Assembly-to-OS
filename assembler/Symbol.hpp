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
  explicit Symbol(std::string name) : name_(std::move(name)) {
    if (!isValid(name_)) {
      throw std::invalid_argument("Invalid Hack symbol: " + name_);
    }
  }

  /**
   * String conversion operator
   */
  operator const std::string&() const noexcept { return name_; }

  /**
   * String conversion method
   */
  const std::string& str() const noexcept { return name_; }

  /**
   * Symbol equality operator
   */
  bool operator==(const Symbol& other) const noexcept {
    return name_ == other.name_;
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
    return os << symbol.str();
  }

 private:
  const std::string name_;
};
}  // namespace hack_assembler

namespace std {
template <>
struct hash<hack_assembler::Symbol> {
  size_t operator()(const hack_assembler::Symbol& s) const noexcept {
    return hash<string>()(s.str());
  }
};
}  // namespace std
