#pragma once
#include <ostream>
#include <string>

namespace hack_assembler {

template <typename Derived, typename T>
class Validated {
 public:
  const T& getValue() const noexcept {
    return static_cast<const Derived&>(*this).getValue();
  }

  bool operator==(const Validated& other) const noexcept {
    return static_cast<const Derived&>(*this).getValue() ==
           static_cast<const Derived&>(other).getValue();
  }

  bool operator!=(const Validated& other) const noexcept {
    return !(*this == other);
  }

  friend std::ostream& operator<<(std::ostream& os, const Validated& s) {
    return os << static_cast<const Derived&>(s).getValue();
  }

  static bool isValid(const std::string s) { return Derived::isValid(s); }

 private:
  // The following lines prevent misusing the class by calling from nonrecursive
  // class
  //
  // Example:
  // - class Symbol1 : public Validated>Symbol1, std::string> - OK!
  // - class Symbol2 : public Validated>Symbol1, std::string> - Error!
  Validated() = default;
  friend Derived;
};

}  // namespace hack_assembler
