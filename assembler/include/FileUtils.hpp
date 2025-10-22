#pragma once
#include <fstream>

namespace hack_assembler {

/**
 * @brief A class used for preprocessing the input and output file streams.
 *
 *
 */
namespace file_utils {

/**
 * @brief Sets up the input and output file for the assembler.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @return A pair of input and output file streams.
 * @throws std::runtime_error if the input file cannot be opened.
 */
std::pair<std::ifstream, std::ofstream> setupAssemblyFiles(int argc,
                                                           char* argv[]);

}  // namespace file_utils

}  // namespace hack_assembler
