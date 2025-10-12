#include "Parser.hpp"
#include "SymbolTable.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Incorrect CLI arguments! Usage: " << argv[0] << " <filename>"
              << std::endl;
    return 1;
  }

  const std::filesystem::path src_filepath(argv[1]);
  const std::string src_filename = src_filepath.stem().string();
  const std::string src_extension = src_filepath.extension().string();
  if (src_extension.ends_with(".asm")) {
    std::cerr << "The source file needs to be an assembly file, you passed: "
              << src_extension << std::endl;
  }
  const std::filesystem::path out_filepath(src_filename + ".hack");
  std::ifstream src_file(src_filepath);

  if (!src_file.is_open()) {
    std::cerr << "Failed to open file: " << src_filepath << std::endl;
  }

  // Initialize the symbol table
  auto symbolTable = SymbolTable{};
  const std::vector<std::pair<Symbol, int>> predefinedSymbols = {
      {Symbol("SP"), 0},          {Symbol("LCL"), 1},
      {Symbol("ARG"), 2},         {Symbol("THIS"), 3},
      {Symbol("THAT"), 4},        {Symbol("SCREEN"), 16384},
      {Symbol("KEYBOARD"), 24576}};
  for (auto &[symbol, address] : predefinedSymbols) {
    symbolTable.addEntry(symbol, address);
  }
  for (int registerNumber = 0;
       registerNumber < hack_assembler::kCpuNumRegisters; registerNumber++) {
    symbolTable.addEntry(Symbol("R" + std::to_string(registerNumber)),
                         registerNumber);
  }

  int variable_idx = hack_assembler::kCpuNumRegisters;

  // First pass: Complete the symbol table
  int line_number = 0;
  Parser parser{src_file};
  while (parser.hasMoreLines()) {
    parser.advance();
  }

  return 0;
}
