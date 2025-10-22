#pragma once

#include <string>
#include <unordered_set>
#include <utility>

#include "Validated.hpp"

namespace hack_assembler {

/**
 * A comp mnemonic, corresponding to ALU operation instructions,
 * supported by the Hack platform.
 */
class CompMnemonic : public Validated<CompMnemonic, std::string> {
 public:
  /**
   * Constructs a comp mnemonic from a string
   */
  explicit CompMnemonic(std::string value) : value_(std::move(value)) {
    if (!isValid(value_)) {
      throw std::invalid_argument("Invalid Hack comp mnemonic: " + value_);
    }
  }

  /**
   * Return the value of the comp mnemonic
   */
  const std::string& getValue() const noexcept { return value_; }

  /**
   * Comp mnemonic validation method. Returns true if the comp mnemonic adheres
   * to Hack assembler rules.
   *
   * A comp mnemonic:
   *   - can be of 28 specified combinations of characters, any other string is
   * invalid.
   */
  static bool isValid(const std::string& s) {
    static const std::unordered_set<std::string> valid_comps = {
        "0",   "1",   "-1",  "D",   "A",   "!D",  "!A",  "-D",  "-A",
        "D+1", "A+1", "D-1", "A-1", "D+A", "D-A", "A-D", "D&A", "D|A",
        "M",   "!M",  "M+1", "M-1", "D+M", "D-M", "M-D", "D&M", "D|M"};
    return valid_comps.contains(s);
  }

 private:
  const std::string value_;
};

}  // namespace hack_assembler

namespace std {
template <>
struct hash<hack_assembler::CompMnemonic> {
  size_t operator()(const hack_assembler::CompMnemonic& s) const noexcept {
    return hash<string>()(s.getValue());
  }
};
}  // namespace std
