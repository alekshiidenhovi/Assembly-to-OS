#include "Parser.hpp"

#include <fstream>

namespace hack_assembler {

Parser::Parser(std::ifstream& src_file)
    : src_file(src_file), current_instruction_type_() {}

bool Parser::hasMoreLines() const { return src_file.peek() != EOF; };

void Parser::advance() {}

}  // namespace hack_assembler
