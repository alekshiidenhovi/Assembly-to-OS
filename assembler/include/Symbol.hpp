#pragma once
#include <functional>
#include <regex>
#include <string>
#include <utility>

#include "Validated.hpp"

namespace hack_assembler {
/**
 * A Hack symbol class. Encapsulates a symbol string that adheres to Hack symbol
 * rules.
 */
class Symbol : public Validated<Symbol, std::string> {
 public:
  /**
   * Constructs a symbol from a string
   */
  explicit Symbol(std::string value) : value_(std::move(value)) {
    if (!isValid(value_)) {
      throw std::invalid_argument("Invalid Hack symbol: " + value_);
    }
  }

  /**
   * Return the value of the symbol
   */
  const std::string& getValue() const noexcept { return value_; }

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
