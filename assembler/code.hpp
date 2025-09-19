#pragma once
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, int> create_register_symbol_table(int num_registers);
unordered_map<string, int> create_predefined_symbol_table();
unordered_map<string, int> initialize_symbol_table(int num_registers);
