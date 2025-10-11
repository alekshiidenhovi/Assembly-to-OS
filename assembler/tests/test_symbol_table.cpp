#include "SymbolTable.hpp"
#include <gtest/gtest.h>

using namespace std;

class SymbolTableTest : public testing::Test {
protected:
  SymbolTable symbol_table_;
};

TEST_F(SymbolTableTest, Insertion) {
  const string symbol_name = "NEWSYMBOL";
  const int address = 100;
  Symbol symbol(symbol_name);
  EXPECT_FALSE(symbol_table_.contains(symbol));

  symbol_table_.addEntry(symbol, address);
  EXPECT_TRUE(symbol_table_.contains(symbol));
  EXPECT_EQ(symbol_table_.getAddress(symbol), address);
}
