#pragma once
#include "Symbol.hpp"
#include <initializer_list>
#include <unordered_map>
#include <utility>

using namespace std;

/**
 * Creates a symbol table, inittalized with predefined values such as register
 * names.
 */
class SymbolTable {
public:
  /**
   * Default constructor
   */
  SymbolTable();

  /**
   * Initializer-list constructor
   */
  SymbolTable(std::initializer_list<std::pair<Symbol, int>>);

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
  unordered_map<Symbol, int> symbol_table_;
};
