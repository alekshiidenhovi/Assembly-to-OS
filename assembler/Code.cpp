#include "Code.hpp"

#include <unordered_map>

#include "CompMnemonic.hpp"
#include "DestMnemonic.hpp"
#include "JumpMnemonic.hpp"

namespace hack_assembler {

// ---- Public Methods ----

JumpBinary Code::getJumpBinary(const JumpMnemonic& jump) const {
  return jumpTable().at(jump);
}

DestBinary Code::getDestBinary(const DestMnemonic& dest) const {
  return destTable().at(dest);
}

CompBinary Code::getCompBinary(const CompMnemonic& comp) const {
  return compTable().at(comp);
}

const std::unordered_map<JumpMnemonic, JumpBinary>& Code::jumpTable() {
  static const std::unordered_map<JumpMnemonic, JumpBinary> table = {
      {JumpMnemonic("null"), JumpBinary("000")},  // no jump
      {JumpMnemonic("JGT"), JumpBinary("001")},   // if comp > 0 jump
      {JumpMnemonic("JEQ"), JumpBinary("010")},   // if comp = 0 jump
      {JumpMnemonic("JGE"), JumpBinary("011")},   // if comp >= 0 jump
      {JumpMnemonic("JLT"), JumpBinary("100")},   // if comp < 0 jump
      {JumpMnemonic("JNE"), JumpBinary("101")},   // if comp != 0 jump
      {JumpMnemonic("JLE"), JumpBinary("110")},   // if comp <= 0 jump
      {JumpMnemonic("JMP"), JumpBinary("111")}    // unconditional jump
  };
  return table;
}

const std::unordered_map<DestMnemonic, DestBinary>& Code::destTable() {
  static const std::unordered_map<DestMnemonic, DestBinary> table = {
      {DestMnemonic("null"), DestBinary("000")},  // value is not stored
      {DestMnemonic("M"), DestBinary("001")},     // RAM[A]
      {DestMnemonic("D"), DestBinary("010")},     // D register
      {DestMnemonic("DM"), DestBinary("011")},    // D register and RAM[A]
      {DestMnemonic("A"), DestBinary("100")},     // A register
      {DestMnemonic("AM"), DestBinary("101")},    // A register and RAM[A]
      {DestMnemonic("AD"), DestBinary("110")},    // A register and D register
      {DestMnemonic("ADM"), DestBinary("111")}    // A, D, and RAM[A]
  };
  return table;
}

const std::unordered_map<CompMnemonic, CompBinary>& Code::compTable() {
  static const std::unordered_map<CompMnemonic, CompBinary> table = {
      {CompMnemonic("0"), CompBinary("0101010")},
      {CompMnemonic("1"), CompBinary("0111111")},
      {CompMnemonic("-1"), CompBinary("0111010")},
      {CompMnemonic("D"), CompBinary("0001100")},
      {CompMnemonic("A"), CompBinary("0110000")},
      {CompMnemonic("M"), CompBinary("1110000")},
      {CompMnemonic("!D"), CompBinary("0001101")},
      {CompMnemonic("!A"), CompBinary("0110001")},
      {CompMnemonic("!M"), CompBinary("1110001")},
      {CompMnemonic("-D"), CompBinary("0001111")},
      {CompMnemonic("-A"), CompBinary("0110011")},
      {CompMnemonic("D+1"), CompBinary("0011111")},
      {CompMnemonic("A+1"), CompBinary("0110111")},
      {CompMnemonic("M+1"), CompBinary("1110111")},
      {CompMnemonic("D-1"), CompBinary("0001110")},
      {CompMnemonic("A-1"), CompBinary("0110010")},
      {CompMnemonic("M-1"), CompBinary("1110010")},
      {CompMnemonic("D+A"), CompBinary("0000010")},
      {CompMnemonic("D+M"), CompBinary("1000010")},
      {CompMnemonic("D-A"), CompBinary("0010011")},
      {CompMnemonic("D-M"), CompBinary("1010011")},
      {CompMnemonic("A-D"), CompBinary("0000111")},
      {CompMnemonic("M-D"), CompBinary("1000111")},
      {CompMnemonic("D&A"), CompBinary("0000000")},
      {CompMnemonic("D&M"), CompBinary("1000000")},
      {CompMnemonic("D|A"), CompBinary("0010101")},
      {CompMnemonic("D|M"), CompBinary("1010101")},
  };
  return table;
}

}  // namespace hack_assembler
