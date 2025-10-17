#include <gtest/gtest.h>

#include "CompMnemonic.hpp"
#include "DestMnemonic.hpp"
#include "JumpMnemonic.hpp"

TEST(MnemonicTest, ValidMnemonic) {
  EXPECT_NO_THROW(hack_assembler::CompMnemonic("M"));
  EXPECT_NO_THROW(hack_assembler::DestMnemonic("ADM"));
  EXPECT_NO_THROW(hack_assembler::JumpMnemonic("JMP"));
}

TEST(MnemonicTest, InvalidMnemonic) {
  EXPECT_THROW(hack_assembler::CompMnemonic("m"),
               std::invalid_argument);  // Lowercase letters not allowed
  EXPECT_THROW(hack_assembler::CompMnemonic("M1"),
               std::invalid_argument);  // Missing plus
  EXPECT_THROW(hack_assembler::CompMnemonic("M+"),
               std::invalid_argument);  // Missing plus 1
  EXPECT_THROW(hack_assembler::CompMnemonic("1+M"),
               std::invalid_argument);  // Wrong order of letters
  EXPECT_THROW(hack_assembler::CompMnemonic("M + 1"),
               std::invalid_argument);  // Spaces not allowed

  EXPECT_THROW(hack_assembler::DestMnemonic("adm"),
               std::invalid_argument);  // Lowercase letters not allowed
  EXPECT_THROW(hack_assembler::DestMnemonic("ADD"),
               std::invalid_argument);  // Non-existing mnemonic
  EXPECT_THROW(hack_assembler::DestMnemonic("MDA"),
               std::invalid_argument);  // Wrong order of letters
  EXPECT_THROW(hack_assembler::DestMnemonic("A D M"),
               std::invalid_argument);  // Spaces not allowed
                                        //
  EXPECT_THROW(hack_assembler::JumpMnemonic("jmb"),
               std::invalid_argument);  // Lowercase letters not allowed
  EXPECT_THROW(hack_assembler::JumpMnemonic("JMB"),
               std::invalid_argument);  // Non-existing mnemonic
  EXPECT_THROW(hack_assembler::JumpMnemonic("PMJ"),
               std::invalid_argument);  // Wrong order of letters
  EXPECT_THROW(hack_assembler::JumpMnemonic("J M P"),
               std::invalid_argument);  // Spaces not allowed
}

TEST(MnemonicTest, EqualityOperators) {
  auto a = hack_assembler::CompMnemonic("M");
  auto b = hack_assembler::CompMnemonic("M");
  auto c = hack_assembler::CompMnemonic("M+1");

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);
  EXPECT_TRUE(a != c);
  EXPECT_FALSE(a == c);

  auto d = hack_assembler::DestMnemonic("ADM");
  auto e = hack_assembler::DestMnemonic("ADM");
  auto f = hack_assembler::DestMnemonic("AD");

  EXPECT_TRUE(d == e);
  EXPECT_FALSE(d != e);
  EXPECT_TRUE(d != f);
  EXPECT_FALSE(d == f);

  auto g = hack_assembler::JumpMnemonic("JMP");
  auto h = hack_assembler::JumpMnemonic("JMP");
  auto i = hack_assembler::JumpMnemonic("JNE");

  EXPECT_TRUE(g == h);
  EXPECT_FALSE(g != h);
  EXPECT_TRUE(g != i);
  EXPECT_FALSE(g == i);
}
