#include "Symbol.hpp"

#include <ostream>
#include <regex>
#include <stdexcept>
#include <string>

namespace hack_assembler {

Symbol::Symbol(const std::string& name) : name_(name) {
  if (!isValid(name_)) {
    throw std::invalid_argument("Invalid Hack symbol: " + name_);
  }
}

Symbol::operator const std::string&() const noexcept { return name_; }

const std::string& Symbol::str() const noexcept { return name_; }

bool Symbol::operator==(const Symbol& other) const noexcept {
  return name_ == other.name_;
}

bool Symbol::operator!=(const Symbol& other) const noexcept {
  return !(*this == other);
}

bool Symbol::isValid(const std::string& s) {
  static const std::regex pattern(R"(^[A-Za-z_\.\$\:][A-Za-z0-9_\.\$\:]*$)");
  return regex_match(s, pattern);
}

std::ostream& operator<<(std::ostream& os, const Symbol& symbol) {
  return os << symbol.str();
}

}  // namespace hack_assembler
