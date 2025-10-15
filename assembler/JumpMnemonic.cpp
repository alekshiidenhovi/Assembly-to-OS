#include "JumpMnemonic.hpp"

#include <string>
#include <unordered_map>

#include "Binary.hpp"

namespace hack_assembler {

const std::unordered_map<std::string, JumpBinary>&
JumpMnemonic::staticCodeTable() {
  static const std::unordered_map<std::string, JumpBinary> code_table = {
      // jump -> j1 j2 j3 (3 bits)
      {"null", JumpBinary("000")},  // no jump
      {"JGT", JumpBinary("001")},   // if comp > 0 jump
      {"JEQ", JumpBinary("010")},   // if comp = 0 jump
      {"JGE", JumpBinary("011")},   // if comp >= 0 jump
      {"JLT", JumpBinary("100")},   // if comp < 0 jump
      {"JNE", JumpBinary("101")},   // if comp != 0 jump
      {"JLE", JumpBinary("110")},   // if comp <= 0 jump
      {"JMP", JumpBinary("111")}    // unconditional jump
  };
  return code_table;
}
}  // namespace hack_assembler
