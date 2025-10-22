#include "Code.hpp"

#include <unordered_map>

#include "CompMnemonic.hpp"
#include "Constants.hpp"
#include "DestMnemonic.hpp"
#include "JumpMnemonic.hpp"

namespace {

/**
 * @brief Jump mnemonic translation table.
 *
 * Maps each symbolic Hack jump mnemonic to its corresponding 3-bit binary
 * code. The three bits (j1 j2 j3) determine whether to jump based on the ALU
 * output:
 *
 * | Bits | Mnemonic  | Meaning                    |
 * |------|-----------|----------------------------|
 * | 000  | null      | No jump                    |
 * | 001  | JGT       | Jump if comp > 0           |
 * | 010  | JEQ       | Jump if comp == 0          |
 * | 011  | JGE       | Jump if comp >= 0          |
 * | 100  | JLT       | Jump if comp < 0           |
 * | 101  | JNE       | Jump if comp != 0          |
 * | 110  | JLE       | Jump if comp <= 0          |
 * | 111  | JMP       | Unconditional jump         |
 */
const std::unordered_map<hack_assembler::JumpMnemonic,
                         hack_assembler::JumpBinary>&
jumpTable() {
  static const std::unordered_map<hack_assembler::JumpMnemonic,
                                  hack_assembler::JumpBinary>
      table = {
          {hack_assembler::JumpMnemonic(hack_assembler::kNullMnemonic),
           hack_assembler::JumpBinary("000")},  // no jump
          {hack_assembler::JumpMnemonic("JGT"),
           hack_assembler::JumpBinary("001")},  // if comp > 0 jump
          {hack_assembler::JumpMnemonic("JEQ"),
           hack_assembler::JumpBinary("010")},  // if comp = 0 jump
          {hack_assembler::JumpMnemonic("JGE"),
           hack_assembler::JumpBinary("011")},  // if comp >= 0 jump
          {hack_assembler::JumpMnemonic("JLT"),
           hack_assembler::JumpBinary("100")},  // if comp < 0 jump
          {hack_assembler::JumpMnemonic("JNE"),
           hack_assembler::JumpBinary("101")},  // if comp != 0 jump
          {hack_assembler::JumpMnemonic("JLE"),
           hack_assembler::JumpBinary("110")},  // if comp <= 0 jump
          {hack_assembler::JumpMnemonic("JMP"),
           hack_assembler::JumpBinary("111")}  // unconditional jump
      };
  return table;
}

/**
 * @brief Destination mnemonic translation table.
 *
 * Maps symbolic Hack destination mnemonics to their corresponding 3-bit
 * binary codes. Each bit (d1 d2 d3) indicates where to store the ALU
 * computation result:
 *
 * | Bits | Mnemonic  | Meaning                    |
 * |------|-----------|----------------------------|
 * | 000  | null      | No destination             |
 * | 001  | M         | RAM[A]                     |
 * | 010  | D         | D register                 |
 * | 011  | DM        | D register and RAM[A]      |
 * | 100  | A         | A register                 |
 * | 101  | AM        | A register and RAM[A]      |
 * | 110  | AD        | A register and D register  |
 * | 111  | ADM       | A, D, and RAM[A]           |
 */
const std::unordered_map<hack_assembler::DestMnemonic,
                         hack_assembler::DestBinary>&
destTable() {
  static const std::unordered_map<hack_assembler::DestMnemonic,
                                  hack_assembler::DestBinary>
      table = {
          {hack_assembler::DestMnemonic(hack_assembler::kNullMnemonic),
           hack_assembler::DestBinary("000")},  // value is not stored
          {hack_assembler::DestMnemonic("M"),
           hack_assembler::DestBinary("001")},  // RAM[A]
          {hack_assembler::DestMnemonic("D"),
           hack_assembler::DestBinary("010")},  // D register
          {hack_assembler::DestMnemonic("DM"),
           hack_assembler::DestBinary("011")},  // D register and RAM[A]
          {hack_assembler::DestMnemonic("A"),
           hack_assembler::DestBinary("100")},  // A register
          {hack_assembler::DestMnemonic("AM"),
           hack_assembler::DestBinary("101")},  // A register and RAM[A]
          {hack_assembler::DestMnemonic("AD"),
           hack_assembler::DestBinary("110")},  // A register and D register
          {hack_assembler::DestMnemonic("ADM"),
           hack_assembler::DestBinary("111")}  // A, D, and RAM[A]
      };
  return table;
}

/**
 * @brief Computation mnemonic translation table.
 *
 * Maps each computation mnemonic to its 7-bit ALU control code (a c1–c6).
 * Bit `a` selects between A (0) and M (1) as the right input.
 */
const std::unordered_map<hack_assembler::CompMnemonic,
                         hack_assembler::CompBinary>&
compTable() {
  static const std::unordered_map<hack_assembler::CompMnemonic,
                                  hack_assembler::CompBinary>
      table = {
          {hack_assembler::CompMnemonic("0"),
           hack_assembler::CompBinary("0101010")},
          {hack_assembler::CompMnemonic("1"),
           hack_assembler::CompBinary("0111111")},
          {hack_assembler::CompMnemonic("-1"),
           hack_assembler::CompBinary("0111010")},
          {hack_assembler::CompMnemonic("D"),
           hack_assembler::CompBinary("0001100")},
          {hack_assembler::CompMnemonic("A"),
           hack_assembler::CompBinary("0110000")},
          {hack_assembler::CompMnemonic("M"),
           hack_assembler::CompBinary("1110000")},
          {hack_assembler::CompMnemonic("!D"),
           hack_assembler::CompBinary("0001101")},
          {hack_assembler::CompMnemonic("!A"),
           hack_assembler::CompBinary("0110001")},
          {hack_assembler::CompMnemonic("!M"),
           hack_assembler::CompBinary("1110001")},
          {hack_assembler::CompMnemonic("-D"),
           hack_assembler::CompBinary("0001111")},
          {hack_assembler::CompMnemonic("-A"),
           hack_assembler::CompBinary("0110011")},
          {hack_assembler::CompMnemonic("D+1"),
           hack_assembler::CompBinary("0011111")},
          {hack_assembler::CompMnemonic("A+1"),
           hack_assembler::CompBinary("0110111")},
          {hack_assembler::CompMnemonic("M+1"),
           hack_assembler::CompBinary("1110111")},
          {hack_assembler::CompMnemonic("D-1"),
           hack_assembler::CompBinary("0001110")},
          {hack_assembler::CompMnemonic("A-1"),
           hack_assembler::CompBinary("0110010")},
          {hack_assembler::CompMnemonic("M-1"),
           hack_assembler::CompBinary("1110010")},
          {hack_assembler::CompMnemonic("D+A"),
           hack_assembler::CompBinary("0000010")},
          {hack_assembler::CompMnemonic("D+M"),
           hack_assembler::CompBinary("1000010")},
          {hack_assembler::CompMnemonic("D-A"),
           hack_assembler::CompBinary("0010011")},
          {hack_assembler::CompMnemonic("D-M"),
           hack_assembler::CompBinary("1010011")},
          {hack_assembler::CompMnemonic("A-D"),
           hack_assembler::CompBinary("0000111")},
          {hack_assembler::CompMnemonic("M-D"),
           hack_assembler::CompBinary("1000111")},
          {hack_assembler::CompMnemonic("D&A"),
           hack_assembler::CompBinary("0000000")},
          {hack_assembler::CompMnemonic("D&M"),
           hack_assembler::CompBinary("1000000")},
          {hack_assembler::CompMnemonic("D|A"),
           hack_assembler::CompBinary("0010101")},
          {hack_assembler::CompMnemonic("D|M"),
           hack_assembler::CompBinary("1010101")},
      };
  return table;
}

}  // namespace

namespace hack_assembler {

namespace code {

JumpBinary getJumpBinary(const JumpMnemonic& jump) {
  return jumpTable().at(jump);
}

DestBinary getDestBinary(const DestMnemonic& dest) {
  return destTable().at(dest);
}

CompBinary getCompBinary(const CompMnemonic& comp) {
  return compTable().at(comp);
}

}  // namespace code

}  // namespace hack_assembler
