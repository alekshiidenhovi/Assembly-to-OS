
#include <gtest/gtest.h>

#include <stdexcept>

#include "Binary.hpp"

namespace {

// Helper to check valid construction
template <size_t N>
void expectValidBinary(const std::string& value) {
  EXPECT_NO_THROW({
    hack_assembler::Binary<N> b(value);
    EXPECT_EQ(b.getValue(), value);
  });
}

// Helper to check invalid construction
template <size_t N>
void expectInvalidBinary(const std::string& value) {
  EXPECT_THROW(hack_assembler::Binary<N> b(value), std::invalid_argument);
}

}  // namespace

TEST(BinaryTest, ValidLengthAndCharacters) {
  expectValidBinary<1>("0");
  expectValidBinary<1>("1");

  expectValidBinary<3>("101");
  expectValidBinary<7>("1110001");
  expectValidBinary<16>("1010101010101010");
}

TEST(BinaryTest, InvalidLength) {
  // Too short
  expectInvalidBinary<3>("10");
  expectInvalidBinary<7>("101010");
  expectInvalidBinary<16>("101010101010101");

  // Too long
  expectInvalidBinary<3>("1010");
  expectInvalidBinary<7>("11100010");
  expectInvalidBinary<16>("10101010101010100");
}

TEST(BinaryTest, InvalidCharacters) {
  expectInvalidBinary<3>("10A");
  expectInvalidBinary<7>("11100x1");
  expectInvalidBinary<16>("10101010101010a0");
  expectInvalidBinary<1>("2");
}

TEST(BinaryTest, AliasesCorrectLength) {
  // Valid
  EXPECT_NO_THROW(hack_assembler::CompBinary("1110001"));  // 7 bits
  EXPECT_NO_THROW(hack_assembler::DestBinary("101"));      // 3 bits
  EXPECT_NO_THROW(hack_assembler::JumpBinary("010"));      // 3 bits
  EXPECT_NO_THROW(
      hack_assembler::InstructionBinary("0001000000111001"));  // 16 bits
}
TEST(BinaryTest, AliasesIncorrectLength) {
  // Invalid
  EXPECT_THROW(hack_assembler::CompBinary("111000"), std::invalid_argument);
  EXPECT_THROW(hack_assembler::DestBinary("10"), std::invalid_argument);
  EXPECT_THROW(hack_assembler::JumpBinary("0101"), std::invalid_argument);
  EXPECT_THROW(hack_assembler::InstructionBinary("000100000011100"),
               std::invalid_argument);
}

TEST(BinaryTest, EqualityOperators) {
  hack_assembler::Binary<3> a("101");
  hack_assembler::Binary<3> b("101");
  hack_assembler::Binary<3> c("111");

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
  EXPECT_TRUE(a != c);
  EXPECT_FALSE(a == c);
}
