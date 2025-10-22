#include "Parser.hpp"

#include <istream>
#include <optional>
#include <stdexcept>
#include <string>

#include "CompMnemonic.hpp"

namespace hack_assembler {

void Parser::advance() {
  current_line_ = "";
  current_instruction_type_ = std::nullopt;

  std::string line;
  while (std::getline(src_stream_, line)) {
    trimWhitespace_(line);

    if (isCommentLine_(line) || isEmptyLine_(line)) {
      continue;
    }

    if (line.empty()) {
      continue;
    }

    current_line_ = line;

    if (line[0] == '(') {
      current_instruction_type_ = InstructionType::L_INSTRUCTION;
    } else if (line[0] == '@') {
      current_line_number_++;
      current_instruction_type_ = InstructionType::A_INSTRUCTION;
    } else if (line.find("=") != std::string::npos ||
               line.find(";") != std::string::npos ||
               CompMnemonic::isValid(current_line_)) {
      current_line_number_++;
      current_instruction_type_ = InstructionType::C_INSTRUCTION;
    } else {
      throw std::runtime_error(
          "Current line did not match any instruction type: " + current_line_);
    }
    break;
  }
};

void Parser::reset() {
  src_stream_.clear();
  src_stream_.seekg(0, std::ios::beg);
  current_line_number_ = -1;
  current_line_ = "";
  current_instruction_type_ = std::nullopt;
}

std::variant<Constant, Symbol> Parser::getAddressSymbol() const {
  std::string address = current_line_.substr(1);
  if (Symbol::isValid(address)) {
    return Symbol(address);
  } else if (Constant::isValid(address)) {
    return Constant(address);
  } else {
    throw std::runtime_error("Invalid A-instruction address symbol: " +
                             current_line_);
  }
}

DestMnemonic Parser::getDestMnemonic() const {
  size_t dest_separator_pos = current_line_.find(kDestSeparator);
  if (dest_separator_pos == std::string::npos) {
    return DestMnemonic(kNullMnemonic);
  }
  return DestMnemonic(current_line_.substr(0, dest_separator_pos));
}

CompMnemonic Parser::getCompMnemonic() const {
  size_t dest_separator_pos = current_line_.find(kDestSeparator);
  size_t jump_separator_pos = current_line_.find(kJumpSeparator);
  if (dest_separator_pos != std::string::npos &&
      jump_separator_pos != std::string::npos) {  // dest = comp; jump
    return CompMnemonic(current_line_.substr(
        dest_separator_pos + 1, jump_separator_pos - dest_separator_pos));
  } else if (dest_separator_pos != std::string::npos) {  // dest = comp
    return CompMnemonic(current_line_.substr(dest_separator_pos + 1));
  } else if (jump_separator_pos != std::string::npos) {  // comp; jump
    return CompMnemonic(current_line_.substr(0, jump_separator_pos));
  } else {  // comp
    return CompMnemonic(current_line_);
  }
}

JumpMnemonic Parser::getJumpMnemonic() const {
  size_t jump_separator_pos = current_line_.find(kJumpSeparator);
  if (jump_separator_pos == std::string::npos) {
    return JumpMnemonic(kNullMnemonic);
  }
  return JumpMnemonic(current_line_.substr(jump_separator_pos + 1));
}

}  // namespace hack_assembler
