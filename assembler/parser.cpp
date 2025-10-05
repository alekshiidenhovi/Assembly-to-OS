#include "Parser.hpp"
#include <cstdio>
#include <fstream>

Parser::Parser(ifstream &src_file) : src_file(src_file), currentInstruction() {}

bool Parser::hasMoreLines() const { return src_file.peek() != EOF; };

void Parser::advance() {}
