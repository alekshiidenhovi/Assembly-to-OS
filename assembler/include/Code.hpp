#pragma once

#include "Binary.hpp"
#include "CompMnemonic.hpp"
#include "DestMnemonic.hpp"
#include "JumpMnemonic.hpp"

namespace hack_assembler {

/**
 * @brief Provides translation services between Hack assembly mnemonics
 *        and their corresponding binary codes.
 *
 * The Code class exposes three lookup functions—one for each mnemonic type
 * (comp, dest, jump). Each function retrieves a validated Binary object
 * associated with the given Mnemonic. Translation tables are defined in
 * the corresponding Code.cpp implementation file.
 */
namespace code {

/**
 * @brief Returns the binary code corresponding to a given jump mnemonic.
 * @param jump A validated JumpMnemonic object.
 * @return A JumpBinary object containing the encoded binary value.
 * @throws std::out_of_range if the mnemonic is not found in the table.
 */
JumpBinary getJumpBinary(const JumpMnemonic& jump);

/**
 * @brief Returns the binary code corresponding to a given destination
 * mnemonic.
 * @param dest A validated DestMnemonic object.
 * @return A DestBinary object containing the encoded binary value.
 * @throws std::out_of_range if the mnemonic is not found in the table.
 */
DestBinary getDestBinary(const DestMnemonic& dest);

/**
 * @brief Returns the binary code corresponding to a given computation
 * mnemonic.
 * @param comp A validated CompMnemonic object.
 * @return A CompBinary object containing the encoded binary value.
 * @throws std::out_of_range if the mnemonic is not found in the table.
 */
CompBinary getCompBinary(const CompMnemonic& comp);

};  // namespace code

}  // namespace hack_assembler
