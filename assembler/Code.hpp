#pragma once
#include <string>

#include "Symbol.hpp"

namespace hack_assembler {

/**
 * Provides services for translating symbolic Hack mnemonics into respective
 * binary codes.
 */
class Code {
 public:
  /**
   * Returns the binary code of dest mnemonic
   */
  std::string& dest(Symbol& symbol) const;

  /**
   * Returns the binary code of comp mnemonic
   */
  std::string& comp(Symbol& symbol) const;

  /**
   * Returns the binary code of jump mnemonic
   */
  std::string& jump(Symbol& symbol) const;

 private:
};

}  // namespace hack_assembler
