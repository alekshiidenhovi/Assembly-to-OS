#pragma once

#include <string>
#include <unordered_map>

#include "Binary.hpp"
#include "Mnemonic.hpp"

namespace hack_assembler {

/**
 * A jump mnemonic, corresponding to ALU operation instructions,
 * supported by the Hack platform.
 */
class JumpMnemonic : public Mnemonic<JumpBinary> {
 public:
  /**
   * Factory creation method. Returns a JumpMnemonic object
   */
  static JumpMnemonic create(const std::string& value) {
    if (!isValid(value, staticCodeTable())) {
      throw std::invalid_argument("Invalid Hack jump mnemonic: " + value);
    }
    return JumpMnemonic(value);
  }

 private:
  /**
   * Private, single argument constructor
   */
  explicit JumpMnemonic(const std::string& value) : Mnemonic(value) {}

  /**
   * Static mnemonic code table, lazily initialized
   */
  static const std::unordered_map<std::string, JumpBinary>& staticCodeTable();

 protected:
  /**
   * Comp mnemonic code table
   */
  const std::unordered_map<std::string, JumpBinary>& codeTable()
      const override {
    return staticCodeTable();
  }
};

}  // namespace hack_assembler
