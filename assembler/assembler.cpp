#include "Parser.hpp"
#include "SymbolTable.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Incorrect CLI arguments! Usage: " << argv[0] << " <filename>"
         << endl;
    return 1;
  }

  const filesystem::path src_filepath(argv[1]);
  const string src_filename = src_filepath.stem().string();
  const string src_extension = src_filepath.extension().string();
  if (src_extension.ends_with(".asm")) {
    cerr << "The source file needs to be an assembly file, you passed: "
         << src_extension << endl;
  }
  const filesystem::path out_filepath(src_filename + ".hack");
  ifstream src_file(src_filepath);

  if (!src_file.is_open()) {
    cerr << "Failed to open file: " << src_filepath << endl;
  }

  // Initialize the symbol table
  auto symbolTable = SymbolTable{};
  const vector<pair<Symbol, int>> predefinedSymbols = {
      {Symbol("SP"), 0},          {Symbol("LCL"), 1},
      {Symbol("ARG"), 2},         {Symbol("THIS"), 3},
      {Symbol("THAT"), 4},        {Symbol("SCREEN"), 16384},
      {Symbol("KEYBOARD"), 24576}};
  for (auto &[symbol, address] : predefinedSymbols) {
    symbolTable.addEntry(symbol, address);
  }
  for (int registerNumber = 0; registerNumber < NUM_REGISTERS;
       registerNumber++) {
    symbolTable.addEntry(Symbol("R" + to_string(registerNumber)),
                         registerNumber);
  }

  int variable_idx = NUM_REGISTERS;

  // First pass: Complete the symbol table
  int line_number = 0;
  Parser parser{src_file};
  while (parser.hasMoreLines()) {
    parser.advance();
  }

  return 0;
}
