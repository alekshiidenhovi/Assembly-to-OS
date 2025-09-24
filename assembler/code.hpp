#pragma once
#include <string>
#include <unordered_map>

using namespace std;

/**
 * Creates a symbol table for default registers
 */
unordered_map<string, int> create_register_symbol_table(int num_registers);

/**
 * Creates a symbol table for predefined values
 */
unordered_map<string, int> create_predefined_symbol_table();

/**
 * Initializes the symbol table
 */
unordered_map<string, int> initialize_symbol_table(int num_registers);
