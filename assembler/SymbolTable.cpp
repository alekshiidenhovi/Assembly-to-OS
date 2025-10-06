#include "SymbolTable.hpp"
#include "Symbol.hpp"
#include <unordered_map>

using namespace std;

SymbolTable::SymbolTable() : symbol_table_() {}

void SymbolTable::addEntry(const Symbol &symbol, int address) {
  symbol_table_.emplace(symbol, address);
}

bool SymbolTable::contains(const Symbol &symbol) const {
  return symbol_table_.contains(symbol);
}

int SymbolTable::getAddress(const Symbol &symbol) const {
  return symbol_table_.at(symbol);
}
