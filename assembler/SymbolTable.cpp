#include "SymbolTable.hpp"
#include "Symbol.hpp"
#include <string>
#include <unordered_map>

using namespace std;

SymbolTable::SymbolTable(int num_registers)
    : symbol_table_(initialize_symbol_table(num_registers)) {}

void SymbolTable::addEntry(const Symbol &symbol, int address) {
  symbol_table_.emplace(symbol, address);
}

bool SymbolTable::contains(const Symbol &symbol) const {
  return symbol_table_.contains(symbol);
}

int SymbolTable::getAddress(const Symbol &symbol) const {
  return symbol_table_.at(symbol);
}

unordered_map<Symbol, int>
SymbolTable::create_register_symbol_table(int num_registers) {
  unordered_map<Symbol, int> register_sym_table;
  for (int register_number = 0; register_number < num_registers;
       register_number++) {
    Symbol register_name = Symbol("R" + to_string(register_number));
    register_sym_table[register_name] = register_number;
  }
  return register_sym_table;
}

unordered_map<Symbol, int> SymbolTable::create_predefined_symbol_table() {
  return {{Symbol("SP"), 0},          {Symbol("LCL"), 1},
          {Symbol("ARG"), 2},         {Symbol("THIS"), 3},
          {Symbol("THAT"), 4},        {Symbol("SCREEN"), 16384},
          {Symbol("KEYBOARD"), 24576}};
}

unordered_map<Symbol, int>
SymbolTable::initialize_symbol_table(int num_registers) {
  unordered_map<Symbol, int> sym_table =
      create_register_symbol_table(num_registers);
  unordered_map<Symbol, int> predefined_sym_table =
      create_predefined_symbol_table();
  sym_table.insert(predefined_sym_table.begin(), predefined_sym_table.end());
  return sym_table;
}
