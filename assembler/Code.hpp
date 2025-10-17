#pragma once
#include <unordered_map>

#include "Binary.hpp"
#include "CompMnemonic.hpp"
#include "DestMnemonic.hpp"
#include "JumpMnemonic.hpp"

namespace hack_assembler {

/**
 * @class Code
 * @brief Provides translation services between Hack assembly mnemonics
 *        and their corresponding binary codes.
 *
 * The Code class exposes three lookup functions—one for each mnemonic type
 * (comp, dest, jump). Each function retrieves a validated Binary object
 * associated with the given Mnemonic. Translation tables are defined in
 * the corresponding Code.cpp implementation file.
 */
class Code {
 public:
  /**
   * @brief Returns the binary code corresponding to a given jump mnemonic.
   * @param jump A validated JumpMnemonic object.
   * @return A JumpBinary object containing the encoded binary value.
   * @throws std::out_of_range if the mnemonic is not found in the table.
   */
  JumpBinary getJumpBinary(const JumpMnemonic& jump) const;

  /**
   * @brief Returns the binary code corresponding to a given destination
   * mnemonic.
   * @param dest A validated DestMnemonic object.
   * @return A DestBinary object containing the encoded binary value.
   * @throws std::out_of_range if the mnemonic is not found in the table.
   */
  DestBinary getDestBinary(const DestMnemonic& dest) const;

  /**
   * @brief Returns the binary code corresponding to a given computation
   * mnemonic.
   * @param comp A validated CompMnemonic object.
   * @return A CompBinary object containing the encoded binary value.
   * @throws std::out_of_range if the mnemonic is not found in the table.
   */
  CompBinary getCompBinary(const CompMnemonic& comp) const;

 private:
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
  static const std::unordered_map<JumpMnemonic, JumpBinary>& jumpTable();

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
  static const std::unordered_map<DestMnemonic, DestBinary>& destTable();

  /**
   * @brief Computation mnemonic translation table.
   *
   * Maps each computation mnemonic to its 7-bit ALU control code (a c1–c6).
   * Bit `a` selects between A (0) and M (1) as the right input.
   */
  static const std::unordered_map<CompMnemonic, CompBinary>& compTable();
};

}  // namespace hack_assembler
