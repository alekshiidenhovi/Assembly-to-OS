#include <bitset>
#include <string>
namespace hack_assembler {

/**
 * @brief Provides simple utility functions for the assembler.
 */
namespace utils {

inline std::string decimalTo16Bits(int value) {
  return std::bitset<16>(value).to_string();
}

}  // namespace utils

}  // namespace hack_assembler
