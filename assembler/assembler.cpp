#include "code.hpp"
#include "constants.cpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Incorrect CLI arguments! Usage: " << argv[0] << " <filename>"
         << endl;
    return 1;
  }

  string filename = argv[1];
  ifstream file(filename);

  if (!file.is_open()) {
    cerr << "Failed to open file: " << filename << endl;
  }

  auto sym_table = initialize_symbol_table(NUM_REGISTERS);

  int variable_idx = NUM_REGISTERS;

  return 0;
}
