#include "Assembler.hpp"

#include <iostream>

#include "Code.hpp"
#include "Constant.hpp"
#include "Symbol.hpp"
#include "Utils.hpp"

namespace hack_assembler {

void Assembler::initialize_() {
  symbol_table_ = SymbolTable{{Symbol("SP"), 0},     {Symbol("LCL"), 1},
                              {Symbol("ARG"), 2},    {Symbol("THIS"), 3},
                              {Symbol("THAT"), 4},   {Symbol("SCREEN"), 16384},
                              {Symbol("KBD"), 24576}};
  for (int registerNumber = 0;
       registerNumber < hack_assembler::kCpuNumRegisters; registerNumber++) {
    symbol_table_.addEntry(Symbol("R" + std::to_string(registerNumber)),
                           registerNumber);
  }
  next_symbol_table_index_ = kCpuNumRegisters;
}

void Assembler::first_pass() {
  while (parser_.hasMoreLines()) {
    parser_.advance();
    auto instruction_type = parser_.getInstructionType();
    if (!instruction_type.has_value()) {
      continue;
    }
    if (*instruction_type == InstructionType::L_INSTRUCTION) {
      symbol_table_.addEntry(parser_.getLabelSymbol(),
                             parser_.getCurrentLineNumber() + 1);
    }
  }
}

void Assembler::second_pass() {
  parser_.reset();
  while (parser_.hasMoreLines()) {
    parser_.advance();
    auto instruction_type = parser_.getInstructionType();
    if (!instruction_type.has_value()) {
      std::cout << "Warning: No instruction type found on line "
                << parser_.getCurrentLineNumber() << std::endl;
      continue;
    }

    if (*instruction_type == InstructionType::L_INSTRUCTION) {
      continue;

    } else if (*instruction_type == InstructionType::C_INSTRUCTION) {
      auto dest = parser_.getDestMnemonic();
      auto comp = parser_.getCompMnemonic();
      auto jump = parser_.getJumpMnemonic();

      auto dest_binary = code::getDestBinary(dest);
      auto comp_binary = code::getCompBinary(comp);
      auto jump_binary = code::getJumpBinary(jump);

      auto c_instruction_binary_string = "111" + comp_binary.getValue() +
                                         dest_binary.getValue() +
                                         jump_binary.getValue();
      out_stream_ << c_instruction_binary_string << std::endl;

    } else if (*instruction_type == InstructionType::A_INSTRUCTION) {
      auto address_symbol = parser_.getAddressSymbol();

      if (std::holds_alternative<Constant>(address_symbol)) {
        auto constant = std::get<Constant>(address_symbol);
        auto a_instruction_binary_string =
            utils::decimalTo16Bits(constant.getValue());
        out_stream_ << a_instruction_binary_string << std::endl;

      } else if (std::holds_alternative<Symbol>(address_symbol)) {
        auto symbol = std::get<Symbol>(address_symbol);

        if (symbol_table_.contains(symbol)) {
          auto symbol_address = symbol_table_.getAddress(symbol);
          auto a_instruction_binary_string =
              utils::decimalTo16Bits(symbol_address);
          out_stream_ << a_instruction_binary_string << std::endl;

        } else {
          auto symbol_address = next_symbol_table_index_;
          auto a_instruction_binary_string =
              utils::decimalTo16Bits(symbol_address);

          symbol_table_.addEntry(symbol, symbol_address);
          next_symbol_table_index_++;
          out_stream_ << a_instruction_binary_string << std::endl;
        }

      } else {
        throw std::runtime_error("Invalid A-instruction address");
      }

    } else {
      throw std::runtime_error("Invalid instruction type");
    }
  }
}

}  // namespace hack_assembler
