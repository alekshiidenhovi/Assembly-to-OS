#include "Parser.hpp"
#include "SymbolTable.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Incorrect CLI arguments! Usage: " << argv[0] << " <filename>"
         << endl;
    return 1;
  }

  filesystem::path src_filepath(argv[1]);
  string src_filename = src_filepath.stem().string();
  string src_extension = src_filepath.extension().string();
  if (src_extension.ends_with(".asm")) {
    cerr << "The source file needs to be an assembly file, you passed: "
         << src_extension << endl;
  }
  filesystem::path out_filepath(src_filename + ".hack");

  ifstream src_file(src_filepath);

  if (!src_file.is_open()) {
    cerr << "Failed to open file: " << src_filepath << endl;
  }

  auto sym_table = initialize_symbol_table(NUM_REGISTERS);

  int variable_idx = NUM_REGISTERS;

  // First pass: Complete the symbol table
  int line_number = 0;
  string instruction;
  /**
  Parser parser {};
  while (parser.hasMoreLines()) {
    parser.advance();

  }
  */

  return 0;
}
