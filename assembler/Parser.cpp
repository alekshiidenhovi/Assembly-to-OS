#include "Parser.hpp"

#include <fstream>

Parser::Parser(std::ifstream& src_file)
    : src_file(src_file), current_instruction_type_() {}

bool Parser::hasMoreLines() const { return src_file.peek() != EOF; };

void Parser::advance() {}
