#include <gtest/gtest.h>

#include "Constant.hpp"

TEST(ConstantTest, ValidConstant) {
  EXPECT_TRUE(hack_assembler::Constant::isValid("0"));
  EXPECT_TRUE(hack_assembler::Constant::isValid("11"));
  EXPECT_TRUE(hack_assembler::Constant::isValid("123"));
  EXPECT_TRUE(hack_assembler::Constant::isValid("9876"));
  EXPECT_TRUE(hack_assembler::Constant::isValid("32767"));

  EXPECT_NO_THROW(hack_assembler::Constant("0"));
  EXPECT_NO_THROW(hack_assembler::Constant("11"));
  EXPECT_NO_THROW(hack_assembler::Constant("123"));
  EXPECT_NO_THROW(hack_assembler::Constant("9876"));
  EXPECT_NO_THROW(hack_assembler::Constant("32767"));
}

TEST(ConstantTest, InvalidConstant) {
  EXPECT_FALSE(hack_assembler::Constant::isValid("0x0"));    // Hexadecimal
  EXPECT_FALSE(hack_assembler::Constant::isValid("32768"));  // Too big
  EXPECT_FALSE(hack_assembler::Constant::isValid("0.0"));    // Decimal
  EXPECT_FALSE(hack_assembler::Constant::isValid("-1"));     // Negative
  EXPECT_FALSE(hack_assembler::Constant::isValid(""));       // Empty
  EXPECT_FALSE(hack_assembler::Constant::isValid("a"));      // Non-digit

  EXPECT_THROW(hack_assembler::Constant("0x0"), std::invalid_argument);
  EXPECT_THROW(hack_assembler::Constant("32768"), std::invalid_argument);
  EXPECT_THROW(hack_assembler::Constant("0.0"), std::invalid_argument);
  EXPECT_THROW(hack_assembler::Constant("-1"), std::invalid_argument);
  EXPECT_THROW(hack_assembler::Constant(""), std::invalid_argument);
  EXPECT_THROW(hack_assembler::Constant("a"), std::invalid_argument);
}

TEST(ConstantTest, EqualityOperator) {
  auto a = hack_assembler::Constant("0");
  auto b = hack_assembler::Constant("0");
  auto c = hack_assembler::Constant("1");

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
  EXPECT_TRUE(a != c);
  EXPECT_FALSE(a == c);
}
