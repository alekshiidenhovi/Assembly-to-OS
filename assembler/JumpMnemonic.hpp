#pragma once

#include <string>
#include <unordered_set>
#include <utility>

#include "Validated.hpp"

namespace hack_assembler {

/**
 * A jump mnemonic, specifying whether to jump to a different instruction based
 * on the Hack ALU output.
 */
class JumpMnemonic : public Validated<JumpMnemonic, std::string> {
 public:
  /**
   * Constructs a jump mnemonic from a string
   */
  explicit JumpMnemonic(std::string value) : value_(std::move(value)) {
    if (!isValid(value_)) {
      throw std::invalid_argument("Invalid Hack jump mnemonic: " + value_);
    }
  }

  /**
   * Return the value of the jump mnemonic
   */
  const std::string& getValue() const noexcept { return value_; }

  /**
   * Jump mnemonic validation method. Returns true if the jump mnemonic adheres
   * to Hack assembler rules.
   *
   * A jump mnemonic:
   *   - can be of 8 specified combinations of characters, any other string is
   * invalid.
   */
  static bool isValid(const std::string& s) {
    static const std::unordered_set<std::string> valid_jumps = {
        "null", "JGT", "JEQ", "JGE", "JLT", "JNE", "JLE", "JMP"};
    return valid_jumps.contains(s);
  }

 private:
  const std::string value_;
};

}  // namespace hack_assembler

namespace std {
template <>
struct hash<hack_assembler::JumpMnemonic> {
  size_t operator()(const hack_assembler::JumpMnemonic& s) const noexcept {
    return hash<string>()(s.getValue());
  }
};
}  // namespace std
