#pragma once

#include <istream>
#include <optional>
#include <string>
#include <variant>

#include "CompMnemonic.hpp"
#include "Constant.hpp"
#include "Constants.hpp"
#include "DestMnemonic.hpp"
#include "JumpMnemonic.hpp"
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
  explicit Parser(std::istream& src_stream) : src_stream_(src_stream) {}

  /**
   * Checks whether there are more lines in the input.
   */
  bool hasMoreLines() const { return src_stream_.peek() != EOF; }

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
   * Resets the parser to the beginning of the file. Also resets the stream
   * internal status bit to goodbit (no errors).
   */
  void reset();

  /**
   * Returns the type of the A-instruction address.
   *
   * Should be called only with A_INSTRUCTIONs.
   */
  std::variant<Constant, Symbol> getAddressSymbol() const;

  /**
   * Return the instruction type of the current instruction.
   */
  std::optional<InstructionType> getInstructionType() const {
    return current_instruction_type_;
  }

  /**
   * If the current instruction is (xxx), returns the symbol xxx.
   *
   * Should be called only with L_INSTRUCTIONs.
   */
  Symbol getLabelSymbol() const {
    size_t seq_length = current_line_.length() - 2;
    return Symbol(current_line_.substr(1, seq_length));
  }

  /**
   * Returns the symbolic dest part of the current C_INSTRUCTION (8
   * possibilities)
   *
   * Should be called only with C_INSTRUCTIONs.
   */
  DestMnemonic getDestMnemonic() const;

  /**
   * Returns the symbolic comp part of the current C_INSTRUCTION (28
   * possibilities)
   *
   * Should be called only with C_INSTRUCTIONs.
   */
  CompMnemonic getCompMnemonic() const;

  /**
   * Returns the symbolic jump part of the current C_INSTRUCTION (8
   * possibilities)
   *
   * Should be called only with C_INSTRUCTIONs.
   */
  JumpMnemonic getJumpMnemonic() const;

  /**
   * Returns the current line number, 0 indicates that the parsing has not yet
   * started.
   */
  int getCurrentLineNumber() const { return current_line_number_; }

 private:
  /**
   * The input file stream
   */
  std::istream& src_stream_;

  /**
   * The current instruction, initially an empty string
   */
  std::string current_line_ = "";

  std::optional<InstructionType> current_instruction_type_ = std::nullopt;

  /**
   * The current line number, initially 0, set to 1 after the first line is
   * parsed
   */
  int current_line_number_ = 0;

  /**
   * Checks whether the given line is a comment line
   */
  bool isCommentLine_(const std::string& line) const {
    return line.find(kCommentIndicators) != std::string::npos;
  }

  /**
   * Checks whether the gives line is an empty line
   */
  bool isEmptyLine_(const std::string& line) const { return line.empty(); }

  /**
   * Trims the whitespace from the beginning and end of the given line
   */
  void trimWhitespace_(std::string& line) {
    line.erase(0, line.find_first_not_of(" \t\r\n"));
    line.erase(line.find_last_not_of(" \t\r\n") + 1);
  }

  /**
   * Increments the current line number by 1
   */
  void incrementCurrentLineNumber_() { current_line_number_++; }
};

}  // namespace hack_assembler
