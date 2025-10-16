#pragma once
#include <string_view>

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
inline constexpr std::string_view kAssemblyFileExtension = ".asm";

/**
 * File extension for output Hack binary files
 */
inline constexpr std::string_view kHackFileExtension = ".hack";

/**
 * Hack instruction type
 */
enum class InstructionType {
  A_INSTRUCTION,  ///< Address instruction, @xxx
  C_INSTRUCTION,  ///< Compute instruction, dest=comp;jump
  L_INSTRUCTION,  ///< Label instruction, (xxx)
};

}  // namespace hack_assembler
