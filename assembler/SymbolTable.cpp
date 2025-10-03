#include "SymbolTable.hpp"
#include "Code.hpp"
#include <string>
#include <unordered_map>

using namespace std;

SymbolTable::SymbolTable(int num_registers)
    : symbol_table(initialize_symbol_table(num_registers)) {}

void SymbolTable::addEntry(const string &symbol, int address) {
  symbol_table.emplace(symbol, address);
}

bool SymbolTable::contains(const string &symbol) const {
  return symbol_table.contains(symbol);
}

int SymbolTable::getAddress(const string &symbol) const {
  return symbol_table.at(symbol);
}

unordered_map<string, int>
SymbolTable::create_register_symbol_table(int num_registers) {
  unordered_map<string, int> register_sym_table;
  for (int register_number = 0; register_number < num_registers;
       register_number++) {
    string register_name = "R" + to_string(register_number);
    register_sym_table[register_name] = register_number;
  }
  return register_sym_table;
}

unordered_map<string, int> SymbolTable::create_predefined_symbol_table() {
  return {{"SP", 0},   {"LCL", 1},        {"ARG", 2},         {"THIS", 3},
          {"THAT", 4}, {"SCREEN", 16384}, {"KEYBOARD", 24576}};
}

unordered_map<string, int>
SymbolTable::initialize_symbol_table(int num_registers) {
  unordered_map<string, int> sym_table =
      create_register_symbol_table(num_registers);
  unordered_map<string, int> predefined_sym_table =
      create_predefined_symbol_table();
  sym_table.insert(predefined_sym_table.begin(), predefined_sym_table.end());
  return sym_table;
}
