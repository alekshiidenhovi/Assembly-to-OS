#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "Symbol.hpp"

TEST(SymbolTest, ValidSymbols) {
  const std::vector<std::string> valid_symbol_names = {
      "onlyletters",          "includesd1t1ts",    "underscores_allowed",
      "so_are_dollar_signs$", "ANDCAPITALLETTERS", "as:well:as:colons",
  };

  for (const auto name : valid_symbol_names) {
    EXPECT_NO_THROW((Symbol(name)))
        << "The Symbol constructor threw an error with a valid symbol string: '"
        << name << "'.";
  }
}

TEST(SymbolTest, InvalidSymbols) {
  const std::vector<std::string> invalid_symbol_names = {
      "0cannotstartwithdigit", "no spaces allowed", "noexclamations!",
      "noquestionamarks?"};

  for (const auto& name : invalid_symbol_names) {
    EXPECT_THROW((Symbol(name)), std::invalid_argument)
        << "The Symbol constructor did not throw an error for invalid name: \'"
        << name << "'.";
  }
}

TEST(SymbolTest, Equality) {
  const Symbol symbol1("R0");
  const Symbol symbol2("R0");
  EXPECT_EQ(symbol1, symbol2)
      << "Symbols constructed with equal strings should be equal. Symbol1 '"
      << symbol1.str() << "' != Symbol2 '" << symbol2.str() << "'.";
}

TEST(SymbolTest, Inequality) {
  const Symbol symbol1("R0");
  const Symbol symbol2("R1");
  EXPECT_NE(symbol1, symbol2)
      << "Symbols constructed with different strings should not be equal. "
         "Symbol1 '"
      << symbol1.str() << "' != Symbol2 '" << symbol2.str() << "'.";
}
