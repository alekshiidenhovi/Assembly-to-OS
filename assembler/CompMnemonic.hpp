#pragma once

#include <string>
#include <unordered_map>

#include "Binary.hpp"
#include "Mnemonic.hpp"

namespace hack_assembler {

/**
 * A computation mnemonic, corresponding to ALU operation instructions,
 * supported by the Hack platform.
 */
class CompMnemonic : public Mnemonic<CompBinary> {
 public:
  /**
   * Factory creation method. Returns a CompMnemonic object
   */
  static CompMnemonic create(const std::string& value) {
    if (!isValid(value, staticCodeTable())) {
      throw std::invalid_argument("Invalid Hack comp mnemonic: " + value);
    }
    return CompMnemonic(value);
  }

 private:
  /**
   * Private, single argument constructor
   */
  explicit CompMnemonic(const std::string& value) : Mnemonic(value) {}

  /**
   * Static mnemonic code table, lazily initialized
   */
  static const std::unordered_map<std::string, CompBinary>& staticCodeTable();

 protected:
  /**
   * Comp mnemonic code table
   */
  const std::unordered_map<std::string, CompBinary>& codeTable()
      const override {
    return staticCodeTable();
  }
};

}  // namespace hack_assembler
