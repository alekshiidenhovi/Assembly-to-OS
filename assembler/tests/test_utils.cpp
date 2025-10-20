#include <gtest/gtest.h>

#include "Utils.hpp"

TEST(UtilsTest, DecimalTo16Bits) {
  EXPECT_EQ(hack_assembler::utils::decimalTo16Bits(0), "0000'0000'0000'0000");
  EXPECT_EQ(hack_assembler::utils::decimalTo16Bits(1), "0000'0000'0000'0001");
  EXPECT_EQ(hack_assembler::utils::decimalTo16Bits(10), "0000'0000'0000'1010");
  EXPECT_EQ(hack_assembler::utils::decimalTo16Bits(100), "0000'0000'0110'0100");
}
