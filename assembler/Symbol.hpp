#pragma once
#include <functional>
#include <ostream>
#include <string>

class Symbol {
public:
  /**
   * Single argument constructor
   */
  explicit Symbol(const std::string &name);

  /**
   * String conversion operator
   */
  operator const std::string &() const noexcept;

  /**
   * String conversion method
   */
  const std::string &str() const noexcept;

  /**
   * Symbol equality operator
   */
  bool operator==(const Symbol &other) const noexcept;

  /**
   * Symbol inequality operator
   */
  bool operator!=(const Symbol &other) const noexcept;

  /**
   * Symbol validation method. Returns true if the symbol adheres to Hack
   * assembler rules.
   *
   * A symbol:
   *   - can be any sequence of letters, digits, underscores, dots, dollar
   * signs, and colon.
   *   - cannot start with a digit.
   */
  static bool isValid(const std::string &s);

  friend std::ostream &operator<<(std::ostream &os, const Symbol &symbol);

private:
  const std::string name_;
};

namespace std {
template <> struct hash<Symbol> {
  size_t operator()(const Symbol &s) const noexcept {
    return hash<string>()(s.str());
  }
};
} // namespace std
