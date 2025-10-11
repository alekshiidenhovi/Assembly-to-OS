#include "SymbolTable.hpp"
#include "Symbol.hpp"
#include <initializer_list>
#include <unordered_map>
#include <utility>

using namespace std;

SymbolTable::SymbolTable() : symbol_table_() {}

SymbolTable::SymbolTable(
    std::initializer_list<std::pair<Symbol, int>> symbol_pairs) {
  for (const auto &[symbol, address] : symbol_pairs) {
    symbol_table_.emplace(symbol, address);
  }
}

void SymbolTable::addEntry(const Symbol &symbol, int address) {
  symbol_table_.emplace(symbol, address);
}

bool SymbolTable::contains(const Symbol &symbol) const {
  return symbol_table_.contains(symbol);
}

int SymbolTable::getAddress(const Symbol &symbol) const {
  return symbol_table_.at(symbol);
}
