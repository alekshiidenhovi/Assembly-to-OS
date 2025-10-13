#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Constants.hpp"
#include "Parser.hpp"
#include "SymbolTable.hpp"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Incorrect CLI arguments! Usage: " << argv[0] << " <filename>"
              << std::endl;
    return 1;
  }

  const std::filesystem::path src_filepath(argv[1]);
  const std::string src_filename = src_filepath.stem().string();
  const std::string src_extension = src_filepath.extension().string();
  if (!src_extension.ends_with(hack_assembler::kAssemblyFileExtension)) {
    std::cerr << "The source file needs to be an assembly file, you passed: "
              << src_extension << std::endl;
    return 1;
  }
  const std::filesystem::path out_filepath(
      src_filename + std::string(hack_assembler::kHackFileExtension));
  std::ifstream src_file(src_filepath);

  if (!src_file.is_open()) {
    std::cerr << "Failed to open Hack assembly file: " << src_filepath
              << std::endl;
    return 1;
  }

  // Initialize the symbol table
  auto symbolTable =
      hack_assembler::SymbolTable{{hack_assembler::Symbol("SP"), 0},
                                  {hack_assembler::Symbol("LCL"), 1},
                                  {hack_assembler::Symbol("ARG"), 2},
                                  {hack_assembler::Symbol("THIS"), 3},
                                  {hack_assembler::Symbol("THAT"), 4},
                                  {hack_assembler::Symbol("SCREEN"), 16384},
                                  {hack_assembler::Symbol("KEYBOARD"), 24576}};
  for (int registerNumber = 0;
       registerNumber < hack_assembler::kCpuNumRegisters; registerNumber++) {
    symbolTable.addEntry(
        hack_assembler::Symbol("R" + std::to_string(registerNumber)),
        registerNumber);
  }

  int variable_idx = hack_assembler::kCpuNumRegisters;

  // First pass: Complete the symbol table
  int line_number = 0;
  hack_assembler::Parser parser{src_file};
  while (parser.hasMoreLines()) {
    parser.advance();
  }

  return 0;
}
