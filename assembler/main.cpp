#include <iostream>

#include "Assembler.hpp"
#include "FileUtils.hpp"

int main(int argc, char* argv[]) {
  auto [src_stream, out_stream] =
      hack_assembler::file_utils::setupAssemblyFiles(argc, argv);

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
