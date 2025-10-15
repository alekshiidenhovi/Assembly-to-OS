#pragma once

#include <string>
#include <unordered_map>

#include "Binary.hpp"
#include "Mnemonic.hpp"

namespace hack_assembler {

/**
 * A destination mnemonic, corresponding to ALU operation instructions,
 * supported by the Hack platform.
 */
class DestMnemonic : public Mnemonic<DestBinary> {
 public:
  /**
   * Factory creation method. Returns a DestMnemonic object
   */
  static DestMnemonic create(const std::string& value) {
    if (!isValid(value, staticCodeTable())) {
      throw std::invalid_argument("Invalid Hack dest mnemonic: " + value);
    }
    return DestMnemonic(value);
  }

 private:
  /**
   * Private, single argument constructor
   */
  explicit DestMnemonic(const std::string& value) : Mnemonic(value) {}

  /**
   * Static mnemonic code table, lazily initialized
   */
  static const std::unordered_map<std::string, DestBinary>& staticCodeTable();

 protected:
  /**
   * Comp mnemonic code table
   */
  const std::unordered_map<std::string, DestBinary>& codeTable()
      const override {
    return staticCodeTable();
  }
};

}  // namespace hack_assembler
