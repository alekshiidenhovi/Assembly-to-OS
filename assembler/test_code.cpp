#include "SymbolTable.hpp"
#include <cassert>
#include <iostream>

using namespace std;

int main() {
  constexpr int NUM_REGISTERS = 16;
  auto reg_table = create_register_symbol_table(NUM_REGISTERS);
  assert(reg_table["R0"] == 0);
  assert(reg_table["R15"] == 15);
  assert(reg_table.size() == NUM_REGISTERS);
  cout << "Register table tests passed!\n";

  // Test combined symbol table
  auto predefined_table = create_predefined_symbol_table();
  auto sym_table = initialize_symbol_table(NUM_REGISTERS);
  assert(sym_table.size() == predefined_table.size() + NUM_REGISTERS);
  cout << "Combined table tests passed!\n";

  cout << "✅ All tests passed successfully!\n";
  return 0;
}
