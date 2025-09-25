#include <string>

using namespace std;

/**
 * Number of reserved registers in the Hack CPU architecture
 */
constexpr int NUM_REGISTERS = 16;

/**
 * Number of bits in a Hack RAM address
 */
constexpr int ADDRESS_LENGTH = 15;

/**
 * Maximum value for a Hack RAM address
 */
constexpr int MAX_ADDRESS = (1 << ADDRESS_LENGTH) - 1;

/**
 * File extension for input Hack assembly files
 */
string ASSEMBLY_FILE_EXTENSION = ".asm";

/**
 * File extension for output Hack binary files
 */
string HACK_FILE_EXTENSION = ".hack";

/**
 * Hack instruction type
 */
enum class InstructionType {
  A_INSTRUCTION, ///< Address instruction, @xxx
  C_INSTRUCTION, ///< Compute instruction, dest=comp;jump
  L_INSTRUCTION, ///< Label instruction, (xxx)
};
