#include <gtest/gtest.h>

#include <sstream>

#include "Assembler.hpp"

void runAssembler(std::istream& input_stream, std::ostream& output_stream) {
  hack_assembler::Assembler assembler(input_stream, output_stream);
  assembler.first_pass();
  assembler.second_pass();
}

TEST(AssemblerTest, Empty) {
  std::stringstream input_stream("");
  std::stringstream output_stream("");
  runAssembler(input_stream, output_stream);

  EXPECT_EQ(output_stream.str(), "");
}

TEST(AssemblerTest, ValidCommentFile) {
  std::stringstream input_stream("// This is a comment");
  std::stringstream output_stream("");
  runAssembler(input_stream, output_stream);

  EXPECT_EQ(output_stream.str(), "");
}

TEST(AssemblerTest, ValidCInstruction1) {
  std::stringstream input_stream("D");
  std::stringstream output_stream("");
  runAssembler(input_stream, output_stream);

  EXPECT_EQ(output_stream.str(), "1110001100000000\n");
}

TEST(AssemblerTest, ValidCInstruction2) {
  std::stringstream input_stream("M=1");
  std::stringstream output_stream("");
  runAssembler(input_stream, output_stream);

  EXPECT_EQ(output_stream.str(), "1110111111001000\n");
}

TEST(AssemblerTest, ValidCInstruction3) {
  std::stringstream input_stream("0;JMP");
  std::stringstream output_stream("");
  runAssembler(input_stream, output_stream);

  EXPECT_EQ(output_stream.str(), "1110101010000111\n");
}

TEST(AssemblerTest, ValidAInstructionConstant) {
  std::stringstream input_stream("@0");
  std::stringstream output_stream("");
  runAssembler(input_stream, output_stream);

  EXPECT_EQ(output_stream.str(), "0000000000000000\n");
}

TEST(AssemblerTest, ValidAInstructionSymbol) {
  std::stringstream input_stream("@sum");
  std::stringstream output_stream("");
  runAssembler(input_stream, output_stream);

  EXPECT_EQ(output_stream.str(), "0000000000010000\n");
}

TEST(AssemblerTest, ValidLInstruction) {
  std::stringstream input_stream("(LOOP)");
  std::stringstream output_stream("");
  runAssembler(input_stream, output_stream);

  EXPECT_EQ(output_stream.str(), "");
}

TEST(AssemblerTest, ValidASMProgram) {
  std::stringstream input_stream(
      "// This is a valid ASM program\n"
      "\n"
      "// Here we load a constant 10 into register R0\n"
      "@10\n"
      "D=A\n"
      "@R0\n"
      "M=D\n"
      "\n"
      "(END)\n"
      "@END\n"
      "0;JMP\n");
  std::stringstream output_stream("");
  runAssembler(input_stream, output_stream);

  std::stringstream expected_output_stream(
      "0000000000001010\n"
      "1110110000010000\n"
      "0000000000000000\n"
      "1110001100001000\n"
      "0000000000000100\n"
      "1110101010000111\n");

  EXPECT_EQ(output_stream.str(), expected_output_stream.str());
}
