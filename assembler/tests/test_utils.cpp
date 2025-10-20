#include <gtest/gtest.h>

#include "Utils.hpp"

TEST(UtilsTest, DecimalTo16Bits) {
  EXPECT_EQ(hack_assembler::utils::decimalTo16Bits(0), "0000000000000000");
  EXPECT_EQ(hack_assembler::utils::decimalTo16Bits(1), "0000000000000001");
  EXPECT_EQ(hack_assembler::utils::decimalTo16Bits(10), "0000000000001010");
  EXPECT_EQ(hack_assembler::utils::decimalTo16Bits(100), "0000000001100100");
}
