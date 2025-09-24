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
