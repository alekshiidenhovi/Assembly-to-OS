#include "Constant.hpp"

#include "Constants.hpp"
namespace hack_assembler {

bool Constant::isValid(const std::string& s) {
  if (s.empty()) {
    return false;
  }

  if (s.length() > 5) {
    return false;
  }

  for (auto& c : s) {
    if (!std::isdigit(c)) {
      return false;
    }
  }

  const int digit = std::stoi(s);
  return digit >= hack_assembler::kMinConstant &&
         digit <= hack_assembler::kMaxConstant;
}
}  // namespace hack_assembler
