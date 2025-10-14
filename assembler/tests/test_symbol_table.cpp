#include <gtest/gtest.h>

#include "SymbolTable.hpp"

class SymbolTableTest : public testing::Test {
 protected:
  SymbolTableTest()
      : existing_symbol(hack_assembler::Symbol("FirstSymbol1")),
        non_existing_symbol(hack_assembler::Symbol("NonExistingSymbol")),
        symbol_table_({{existing_symbol, 10}}) {}

  const hack_assembler::Symbol existing_symbol;
  const hack_assembler::Symbol non_existing_symbol;
  hack_assembler::SymbolTable symbol_table_;
};

TEST_F(SymbolTableTest, Contains) {
  EXPECT_TRUE(symbol_table_.contains(existing_symbol))
      << "Symbol table does not contain its initialized value '"
      << existing_symbol.getValue() << "'." << symbol_table_;
  EXPECT_FALSE(symbol_table_.contains(non_existing_symbol))
      << "Symbol table contains values that it was not initialized with!";
}

TEST_F(SymbolTableTest, GettingAddress) {
  EXPECT_EQ(symbol_table_.getAddress(existing_symbol), 10)
      << "Symbol table returns wrong address for its initialized value '"
      << existing_symbol.getValue() << "'.";
  EXPECT_THROW(symbol_table_.getAddress(non_existing_symbol), std::out_of_range)
      << "Symbol table returns address for non-existing symbol!";
}

TEST_F(SymbolTableTest, Insertion) {
  const std::string symbol_name = "NEWSYMBOL";
  const int address = 100;
  const hack_assembler::Symbol new_symbol(symbol_name);
  EXPECT_FALSE(symbol_table_.contains(new_symbol))
      << "Symbol table contains values that it was not initialized with "
         "(inserted value '"
      << new_symbol.getValue() << "').";

  symbol_table_.addEntry(new_symbol, address);
  ASSERT_TRUE(symbol_table_.contains(new_symbol))
      << "Symbol table does not contain its inserted value '"
      << new_symbol.getValue() << "'.";
  EXPECT_EQ(symbol_table_.getAddress(new_symbol), address)
      << "Symbol table returns wrong address for its inserted value '"
      << new_symbol.getValue() << "'.";
}
