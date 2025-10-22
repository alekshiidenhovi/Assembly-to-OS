#pragma once

#include "Parser.hpp"
#include "SymbolTable.hpp"

namespace hack_assembler {

/**
 * @class Assembler
 * @brief Hack assembler class that assembles binary files from Hack assembly
 * files.
 *
 * The Assembler class is responsible for orchestrating the assembly process
 * from Hack assembly files to Hack binary files. It performs the following
 * tasks:
 *
 * - Reads Hack assembly files and parses them into a list of instructions.
 * - Validates the instructions and their operands.
 * - Translates the instructions into Hack binary code.
 * - Writes the binary code to a file.
 */
class Assembler {
 public:
  /**
   * @brief Constructs an Assembler object.
   * @param src_file The input file stream.
   * @param out_file The output file stream.
   */
  Assembler(std::istream& src_stream, std::ostream& out_stream)
      : parser_(src_stream), out_stream_(out_stream), symbol_table_() {
    initialize_();
  }

  /**
   * @brief Executes the first pass of the assembly process.
   *
   * This function is called after the initialization. It tracks symbols and
   * records them into the SymbolTable.
   */
  void first_pass();

  /**
   * @brief Executes the second pass of the assembly process.
   *
   * This function is called after the first pass. It performs the following
   * tasks:
   *
   * - Validates the instructions and their operands.
   * - Translates the instructions into Hack binary code.
   * - Writes the binary code to a file.
   */
  void second_pass();

 private:
  Parser parser_;
  std::ostream& out_stream_;
  SymbolTable symbol_table_;
  int next_symbol_table_index_;

  /**
   * @brief Initialization function that prepares the Assembler for first pass.
   *
   * This function is called before the first pass of the assembly process. It
   * performs the following tasks:
   *
   * - Initializes the symbol_table_
   * - Initializes the next_symbol_table_index_
   */
  void initialize_();
};

}  // namespace hack_assembler
