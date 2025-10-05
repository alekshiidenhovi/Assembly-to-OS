#pragma once
#include "Symbol.hpp"
#include <string>

using namespace std;

/**
 * Provides services for translating symbolic Hack mnemonics into respective
 * binary codes.
 */
class Code {
public:
  /**
   * Returns the binary code of dest mnemonic
   */
  string &dest(Symbol &symbol) const;

  /**
   * Returns the binary code of comp mnemonic
   */
  string &comp(Symbol &symbol) const;

  /**
   * Returns the binary code of jump mnemonic
   */
  string &jump(Symbol &symbol) const;

private:
};
