#pragma once
#include "Symbol.hpp"
#include <unordered_map>

using namespace std;

/**
 * Creates a symbol table, inittalized with predefined values such as register
 * names.
 */
class SymbolTable {
public:
  SymbolTable(int num_registers);

  /**
   * Add symbol-address entry to the table
   */
  void addEntry(const Symbol &symbol, int address);

  /**
   * Checks whether the symbol table includes the argument symbol.
   */
  bool contains(const Symbol &symbol) const;

  /**
   * Returns the address associated with the symbol.
   */
  int getAddress(const Symbol &symbol) const;

private:
  /**
   * Creates a symbol table for default registers
   */
  unordered_map<Symbol, int> create_register_symbol_table(int num_registers);

  /**
   * Creates a symbol table for predefined values
   */
  unordered_map<Symbol, int> create_predefined_symbol_table();

  /**
   * Initializes the symbol table
   */
  unordered_map<Symbol, int> initialize_symbol_table(int num_registers);

  unordered_map<Symbol, int> symbol_table_;
};
