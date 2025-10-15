#include "DestMnemonic.hpp"

#include <string>
#include <unordered_map>

#include "Binary.hpp"

namespace hack_assembler {

const std::unordered_map<std::string, DestBinary>&
DestMnemonic::staticCodeTable() {
  static const std::unordered_map<std::string, DestBinary> code_table = {
      // dest -> d1 d2 d3 (3 bits)
      {"null", DestBinary("000")},  // the value is not stored
      {"M", DestBinary("001")},     // RAM[A]
      {"D", DestBinary("010")},     // D register (reg)
      {"DM", DestBinary("011")},    // D reg and RAM[A]
      {"A", DestBinary("100")},     // A reg
      {"AM", DestBinary("101")},    // A reg and RAM[A]
      {"AD", DestBinary("110")},    // A reg and D reg
      {"ADM", DestBinary("111")}    // A reg, D reg, and RAM[A]
  };
  return code_table;
}
}  // namespace hack_assembler
