#include "SymbolTable.hpp"
#include <cassert>
#include <iostream>

using namespace std;

int main() {
  constexpr int NUM_REGISTERS = 16;
  auto symbol_table = SymbolTable(NUM_REGISTERS);

  assert(symbol_table.contains(Symbol("R0")));
  assert(symbol_table.contains(Symbol("R15")));
  assert(symbol_table.contains(Symbol("SP")));
  assert(!symbol_table.contains(Symbol("R16")));

  assert(symbol_table.getAddress(Symbol("R0")) == 0);
  assert(symbol_table.getAddress(Symbol("R15")) == 15);
  assert(symbol_table.getAddress(Symbol("SP")) == 0);
  cout << "Table initialization tests passed!\n";

  string symbol_name = "NEWSYMBOL";
  Symbol symbol(symbol_name);
  assert(!symbol_table.contains(symbol));
  symbol_table.addEntry(symbol, 100);
  assert(symbol_table.contains(symbol));
  cout << "Symbol table insertion tests passed!\n";

  cout << "✅ All SymbolTable tests passed successfully!\n";
  return 0;
}
