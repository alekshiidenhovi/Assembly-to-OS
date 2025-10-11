#include "Symbol.hpp"
#include <regex>
#include <stdexcept>
#include <string>

using namespace std;

Symbol::Symbol(const string &name) : name_(name) {
  if (!isValid(name_)) {
    throw invalid_argument("Invalid Hack symbol: " + name_);
  }
}

Symbol::operator const string &() const noexcept { return name_; }

const string &Symbol::str() const noexcept { return name_; }

bool Symbol::operator==(const Symbol &other) const noexcept {
  return name_ == other.name_;
}

bool Symbol::operator!=(const Symbol &other) const noexcept {
  return name_ != other.name_;
}

bool Symbol::isValid(const string &s) {
  static const regex pattern(R"(^[A-Za-z_\.\$\:][A-Za-z0-9_\.\$\:]*$)");
  return regex_match(s, pattern);
}
