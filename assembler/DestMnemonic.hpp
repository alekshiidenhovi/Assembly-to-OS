#pragma once

#include <string>
#include <unordered_set>
#include <utility>

#include "Validated.hpp"

namespace hack_assembler {

/**
 * A dest mnemonic, defining where to store the ALU computation result.
 */
class DestMnemonic : public Validated<DestMnemonic, std::string> {
 public:
  /**
   * Constructs a dest mnemonic from a string
   */
  explicit DestMnemonic(std::string value) : value_(std::move(value)) {
    if (!isValid(value_)) {
      throw std::invalid_argument("Invalid Hack dest mnemonic: " + value);
    }
  }

  /**
   * Return the value of the dest mnemonic
   */
  const std::string& getValue() const noexcept { return value_; }

  /**
   * Dest mnemonic validation method. Returns true if the dest mnemonic adheres
   * to Hack assembler rules.
   *
   * A dest mnemonic:
   *   - can be of 28 specified combinations of characters, any other string is
   * invalid.
   */
  static bool isValid(const std::string& s) {
    static const std::unordered_set<std::string> valid_dests = {
        "null", "M", "D", "DM", "A", "AM", "AD", "ADM"};
    return valid_dests.contains(s);
  }

 private:
  const std::string value_;
};

}  // namespace hack_assembler

namespace std {
template <>
struct hash<hack_assembler::DestMnemonic> {
  size_t operator()(const hack_assembler::DestMnemonic& s) const noexcept {
    return hash<string>()(s.getValue());
  }
};
}  // namespace std
