#pragma once
#include <initializer_list>
#include <ostream>
#include <unordered_map>
#include <utility>

#include "Symbol.hpp"

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
  void addEntry(const Symbol& symbol, int address);

  /**
   * Checks whether the symbol table includes the argument symbol.
   */
  bool contains(const Symbol& symbol) const;

  /**
   * Returns the address associated with the symbol.
   */
  int getAddress(const Symbol& symbol) const;

  /**
   * Prints the symbol table to the output stream.
   */
  friend std::ostream& operator<<(std::ostream& os,
                                  const SymbolTable& symbol_table);

 private:
  std::unordered_map<Symbol, int> symbol_table_;
};
