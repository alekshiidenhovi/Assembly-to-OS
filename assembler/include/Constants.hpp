#pragma once
#include <string>

namespace hack_assembler {

/**
 * Number of reserved registers in the Hack CPU architecture
 */
inline constexpr int kCpuNumRegisters = 16;

/**
 * Number of bits in a Hack RAM address
 */
inline constexpr int kRamAddressLength = 15;

/**
 * Maximum value for a Hack RAM address
 */
inline constexpr int kMaxRamAddress = (1 << kRamAddressLength) - 1;

/**
 * Maximum value for a Hack constant
 */
inline constexpr int kMaxConstant = 32767;

/**
 * Minimum value for a Hack constant
 */
inline constexpr int kMinConstant = 0;

/**
 * File extension for input Hack assembly files
 */
inline constexpr std::string kAssemblyFileExtension = ".asm";

/**
 * File extension for output Hack binary files
 */
inline constexpr std::string kHackFileExtension = ".hack";

/**
 * String characters that indicate a comment in Hack assembly
 */
inline constexpr std::string kCommentIndicators = "//";

/**
 * String characters indicating a null mnemonic in Hack assembly
 */
inline constexpr std::string kNullMnemonic = "";

/**
 * String character separating the dest mnenomic from the comp mnenomic in Hack
 * assembly
 */
inline constexpr std::string kDestSeparator = "=";

/**
 * String character separating the jump mnenomic from the comp mnenomic in Hack
 * assembly
 */
inline constexpr std::string kJumpSeparator = ";";

/**
 * Hack instruction type
 */
enum class InstructionType {
  A_INSTRUCTION,  ///< Address instruction, @xxx
  C_INSTRUCTION,  ///< Compute instruction, dest=comp;jump
  L_INSTRUCTION,  ///< Label instruction, (xxx)
};

}  // namespace hack_assembler
