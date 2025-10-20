#include <gtest/gtest.h>

#include <sstream>

#include "CompMnemonic.hpp"
#include "Constant.hpp"
#include "Constants.hpp"
#include "DestMnemonic.hpp"
#include "JumpMnemonic.hpp"
#include "Parser.hpp"
#include "Symbol.hpp"

TEST(ParserTest, Empty) {
  std::stringstream input_stream("");
  hack_assembler::Parser parser(input_stream);

  EXPECT_FALSE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), -1);
  EXPECT_EQ(parser.getInstructionType(), std::nullopt);
}

TEST(ParserTest, ValidCommentFile) {
  std::stringstream input_stream("// This is a comment");
  hack_assembler::Parser parser(input_stream);

  EXPECT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getInstructionType(), std::nullopt);

  parser.advance();

  EXPECT_FALSE(parser.hasMoreLines());
  EXPECT_EQ(parser.getInstructionType(), std::nullopt);
}

TEST(ParserTest, ValidCInstruction1) {
  std::stringstream input_stream("D");
  hack_assembler::Parser parser(input_stream);

  ASSERT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getInstructionType(), std::nullopt);

  parser.advance();

  EXPECT_FALSE(parser.hasMoreLines());

  ASSERT_TRUE(parser.getInstructionType().has_value());
  EXPECT_EQ(parser.getInstructionType().value(),
            hack_assembler::InstructionType::C_INSTRUCTION);

  EXPECT_EQ(parser.getDestMnemonic(),
            hack_assembler::DestMnemonic(hack_assembler::kNullMnemonic));
  EXPECT_EQ(parser.getCompMnemonic(), hack_assembler::CompMnemonic("D"));
  EXPECT_EQ(parser.getJumpMnemonic(),
            hack_assembler::JumpMnemonic(hack_assembler::kNullMnemonic));
}

TEST(ParserTest, ValidCInstruction2) {
  std::stringstream input_stream("M=1");
  hack_assembler::Parser parser(input_stream);

  ASSERT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), -1);
  EXPECT_EQ(parser.getInstructionType(), std::nullopt);

  parser.advance();

  EXPECT_FALSE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), 0);

  ASSERT_TRUE(parser.getInstructionType().has_value());
  EXPECT_EQ(parser.getInstructionType().value(),
            hack_assembler::InstructionType::C_INSTRUCTION);

  EXPECT_EQ(parser.getDestMnemonic(), hack_assembler::DestMnemonic("M"));
  EXPECT_EQ(parser.getCompMnemonic(), hack_assembler::CompMnemonic("1"));
  EXPECT_EQ(parser.getJumpMnemonic(),
            hack_assembler::JumpMnemonic(hack_assembler::kNullMnemonic));
}

TEST(ParserTest, ValidCInstruction3) {
  std::stringstream input_stream("0;JMP");
  hack_assembler::Parser parser(input_stream);

  ASSERT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), -1);
  EXPECT_EQ(parser.getInstructionType(), std::nullopt);

  parser.advance();

  EXPECT_FALSE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), 0);

  ASSERT_TRUE(parser.getInstructionType().has_value());
  EXPECT_EQ(parser.getInstructionType().value(),
            hack_assembler::InstructionType::C_INSTRUCTION);

  EXPECT_EQ(parser.getDestMnemonic(),
            hack_assembler::DestMnemonic(hack_assembler::kNullMnemonic));
  EXPECT_EQ(parser.getCompMnemonic(), hack_assembler::CompMnemonic("0"));
  EXPECT_EQ(parser.getJumpMnemonic(), hack_assembler::JumpMnemonic("JMP"));
}

TEST(ParserTest, ValidAInstructionConstant) {
  std::stringstream input_stream("@0");
  hack_assembler::Parser parser(input_stream);

  ASSERT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), -1);
  EXPECT_EQ(parser.getInstructionType(), std::nullopt);

  parser.advance();

  EXPECT_FALSE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), 0);

  ASSERT_TRUE(parser.getInstructionType().has_value());
  EXPECT_EQ(parser.getInstructionType().value(),
            hack_assembler::InstructionType::A_INSTRUCTION);

  ASSERT_TRUE(std::holds_alternative<hack_assembler::Constant>(
      parser.getAddressSymbol()));
  EXPECT_EQ(std::get<hack_assembler::Constant>(parser.getAddressSymbol()),
            hack_assembler::Constant("0"));
}

TEST(ParserTest, ValidAInstructionSymbol) {
  std::stringstream input_stream("@sum");
  hack_assembler::Parser parser(input_stream);

  ASSERT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), -1);
  EXPECT_EQ(parser.getInstructionType(), std::nullopt);

  parser.advance();

  EXPECT_FALSE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), 0);

  ASSERT_TRUE(parser.getInstructionType().has_value());
  EXPECT_EQ(parser.getInstructionType().value(),
            hack_assembler::InstructionType::A_INSTRUCTION);

  ASSERT_TRUE(std::holds_alternative<hack_assembler::Symbol>(
      parser.getAddressSymbol()));
  EXPECT_EQ(std::get<hack_assembler::Symbol>(parser.getAddressSymbol()),
            hack_assembler::Symbol("sum"));
}

TEST(ParserTest, ValidLInstruction) {
  std::stringstream input_stream("(LOOP)");
  hack_assembler::Parser parser(input_stream);

  ASSERT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), -1);
  EXPECT_EQ(parser.getInstructionType(), std::nullopt);

  parser.advance();

  EXPECT_FALSE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), -1);

  ASSERT_TRUE(parser.getInstructionType().has_value());
  EXPECT_EQ(parser.getInstructionType().value(),
            hack_assembler::InstructionType::L_INSTRUCTION);

  EXPECT_EQ(parser.getLabelSymbol(), hack_assembler::Symbol("LOOP"));
}

TEST(ParserTest, ValidASMProgram) {
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

  hack_assembler::Parser parser(input_stream);

  EXPECT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), -1);
  EXPECT_EQ(parser.getInstructionType(), std::nullopt);

  parser.advance();

  EXPECT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), 0);
  ASSERT_TRUE(parser.getInstructionType().has_value());
  EXPECT_EQ(parser.getInstructionType().value(),
            hack_assembler::InstructionType::A_INSTRUCTION);
  ASSERT_TRUE(std::holds_alternative<hack_assembler::Constant>(
      parser.getAddressSymbol()));
  EXPECT_EQ(std::get<hack_assembler::Constant>(parser.getAddressSymbol()),
            hack_assembler::Constant("10"));

  parser.advance();

  EXPECT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), 1);
  ASSERT_TRUE(parser.getInstructionType().has_value());
  EXPECT_EQ(parser.getInstructionType().value(),
            hack_assembler::InstructionType::C_INSTRUCTION);
  EXPECT_EQ(parser.getDestMnemonic(), hack_assembler::DestMnemonic("D"));
  EXPECT_EQ(parser.getCompMnemonic(), hack_assembler::CompMnemonic("A"));
  EXPECT_EQ(parser.getJumpMnemonic(),
            hack_assembler::JumpMnemonic(hack_assembler::kNullMnemonic));

  parser.advance();

  EXPECT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), 2);
  ASSERT_TRUE(parser.getInstructionType().has_value());
  EXPECT_EQ(parser.getInstructionType().value(),
            hack_assembler::InstructionType::A_INSTRUCTION);
  ASSERT_TRUE(std::holds_alternative<hack_assembler::Symbol>(
      parser.getAddressSymbol()));
  EXPECT_EQ(std::get<hack_assembler::Symbol>(parser.getAddressSymbol()),
            hack_assembler::Symbol("R0"));

  parser.advance();

  EXPECT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), 3);
  ASSERT_TRUE(parser.getInstructionType().has_value());
  EXPECT_EQ(parser.getInstructionType().value(),
            hack_assembler::InstructionType::C_INSTRUCTION);
  EXPECT_EQ(parser.getDestMnemonic(), hack_assembler::DestMnemonic("M"));
  EXPECT_EQ(parser.getCompMnemonic(), hack_assembler::CompMnemonic("D"));
  EXPECT_EQ(parser.getJumpMnemonic(),
            hack_assembler::JumpMnemonic(hack_assembler::kNullMnemonic));

  parser.advance();

  EXPECT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), 3);
  ASSERT_TRUE(parser.getInstructionType().has_value());
  EXPECT_EQ(parser.getInstructionType().value(),
            hack_assembler::InstructionType::L_INSTRUCTION);
  EXPECT_EQ(parser.getLabelSymbol(), hack_assembler::Symbol("END"));

  parser.advance();

  EXPECT_TRUE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), 4);
  ASSERT_TRUE(parser.getInstructionType().has_value());
  EXPECT_EQ(parser.getInstructionType().value(),
            hack_assembler::InstructionType::A_INSTRUCTION);
  EXPECT_EQ(std::get<hack_assembler::Symbol>(parser.getAddressSymbol()),
            hack_assembler::Symbol("END"));

  parser.advance();

  EXPECT_FALSE(parser.hasMoreLines());
  EXPECT_EQ(parser.getCurrentLineNumber(), 5);
  ASSERT_TRUE(parser.getInstructionType().has_value());
  EXPECT_EQ(parser.getInstructionType().value(),
            hack_assembler::InstructionType::C_INSTRUCTION);
  EXPECT_EQ(parser.getDestMnemonic(),
            hack_assembler::DestMnemonic(hack_assembler::kNullMnemonic));
  EXPECT_EQ((parser.getCompMnemonic()), hack_assembler::CompMnemonic("0"));
  EXPECT_EQ((parser.getJumpMnemonic()), hack_assembler::JumpMnemonic("JMP"));
}
