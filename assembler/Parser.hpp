#include "Constants.hpp"
#include <string>

using namespace std;

/**
 * Opens the input file / stream and gets ready to parse it
 */
class Parser {
public:
  /**
   * Checks whether there are more lines in the input.
   */
  bool hasMoreLines();

  /**
   * Reads the next instruction from the input, and makes it the current
   * instruction.
   *
   * Skips over white space and comments, if necessary.
   *
   * This routine should be called only if hasMoreLines is true.
   *
   * Initially, there is no current instruction.
   */
  void advance();

  /**
   * If the current instruction is (xxx), returns the symbol xxx. If the current
   * instruction is @xxx, returns the symbol or decimal xxx (as a string).
   *
   * Should be called only with A_INSTRUCTIONs or L_INSTRUCTIONs.
   */
  string symbol();

  /**
   * Returns the symbolic dest part of the current C_INSTRUCTION (8
   * possibilities)
   *
   * Should be called only with C_INSTRUCTIONs.
   */
  string dest();

  /**
   * Returns the symbolic comp part of the current C_INSTRUCTION (28
   * possibilities)
   *
   * Should be called only with C_INSTRUCTIONs.
   */
  string comp();
  /**
   * Returns the symbolic jump part of the current C_INSTRUCTION (8
   * possibilities)
   *
   * Should be called only with C_INSTRUCTIONs.
   */
  string jump();

private:
  InstructionType *currentInstruction;
};
