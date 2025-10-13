#include <fstream>
#include <optional>

#include "Constants.hpp"
#include "Symbol.hpp"

namespace hack_assembler {

/**
 * Opens the input file / stream and gets ready to parse it
 */
class Parser {
 public:
  /*
   * Constructor class
   */
  explicit Parser(std::ifstream& src_file);

  /**
   * Checks whether there are more lines in the input.
   */
  bool hasMoreLines() const;

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
  Symbol& symbol() const;

  /**
   * Returns the symbolic dest part of the current C_INSTRUCTION (8
   * possibilities)
   *
   * Should be called only with C_INSTRUCTIONs.
   */
  Symbol& dest() const;

  /**
   * Returns the symbolic comp part of the current C_INSTRUCTION (28
   * possibilities)
   *
   * Should be called only with C_INSTRUCTIONs.
   */
  Symbol& comp() const;
  /**
   * Returns the symbolic jump part of the current C_INSTRUCTION (8
   * possibilities)
   *
   * Should be called only with C_INSTRUCTIONs.
   */
  Symbol& jump() const;

 private:
  std::optional<hack_assembler::InstructionType> current_instruction_type_;
  std::ifstream& src_file;
};
}  // namespace hack_assembler
