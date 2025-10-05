#pragma once
#include <string>

using namespace std;

class Symbol {
public:
  /**
   * Single argument constructor
   */
  explicit Symbol(const string &name);

  /**
   * String conversion operator
   */
  operator const string &() const noexcept;

  /**
   * String conversion method
   */
  const string &str() const noexcept;

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
  static bool isValid(const string &s);

private:
  string name_;
};
