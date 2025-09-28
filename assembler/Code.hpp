#include <string>

using namespace std;

/**
 * Provides services for translating symbolic Hack mnemonics into respective
 * binary codes.
 */
class Code {
private:
public:
  /**
   * Returns the binary code of dest mnemonic
   */
  string dest(string symbol);

  /**
   * Returns the binary code of comp mnemonic
   */
  string comp(string symbol);

  /**
   * Returns the binary code of jump mnemonic
   */
  string jump(string symbol);
};
