#include "SymbolTable.hpp"
#include <cassert>
#include <iostream>

using namespace std;

int main() {
  auto symbol_table = SymbolTable();

  const string symbol_name = "NEWSYMBOL";
  const int address = 100;

  Symbol symbol(symbol_name);
  assert(!symbol_table.contains(symbol));
  symbol_table.addEntry(symbol, address);
  assert(symbol_table.contains(symbol));
  assert(symbol_table.getAddress(symbol) == address);
  cout << "Symbol table insertion tests passed!\n";

  cout << "✅ All SymbolTable tests passed successfully!\n";
  return 0;
}
