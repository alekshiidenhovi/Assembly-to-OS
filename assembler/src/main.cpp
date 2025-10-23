#include <fstream>
#include <ios>
#include <iostream>

#include "Assembler.hpp"
#include "FileUtils.hpp"

int main(int argc, char* argv[]) {
  auto [src_filepath, out_filepath] =
      hack_assembler::file_utils::parseAssemblyFilePaths(argc, argv);

  std::ifstream src_stream(src_filepath);
  std::ofstream out_stream(out_filepath, std::ios::out | std::ios::trunc);

  auto assembler = hack_assembler::Assembler(src_stream, out_stream);
  std::cout << "Performing the first pass of the assembly process..."
            << std::endl;
  assembler.first_pass();
  std::cout << "Performing the second pass of the assembly process..."
            << std::endl;
  assembler.second_pass();
  std::cout << "Assembly process completed." << std::endl;
  return 0;
}
