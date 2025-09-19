#include "code.hpp"

int main() {
  constexpr int num_registers = 16;
  auto sym_table = initialize_symbol_table(num_registers);
  return 0;
}
