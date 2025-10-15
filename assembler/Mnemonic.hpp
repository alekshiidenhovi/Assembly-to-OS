#pragma once

#include <string>
#include <unordered_map>
#include <utility>

namespace hack_assembler {

/**
 * An abstract base class for Hack assembly language's symbolic mnemonic,
 * corresponding to a subset of a single assembly instruction.
 */
template <typename TBinary>
class Mnemonic {
 public:
  /**
   * String conversion method
   */
  const std::string& getValue() const noexcept { return value_; }

  /**
   * Mnemonic equality operator
   */
  bool operator==(const Mnemonic& other) const noexcept {
    return value_ == other.value_;
  }

  /**
   * Mnemonic inequality operator
   */
  bool operator!=(const Mnemonic& other) const noexcept {
    return !(*this == other);
  }

  /**
   * Mnemonic to binary conversion method. Returns a string containing the
   * binary representation of the mnemonic.
   */
  virtual TBinary toBinary() const { return codeTable().at(value_); }

  /**
   * Virtual destructor
   */
  virtual ~Mnemonic() = default;

  friend std::ostream& operator<<(std::ostream& os, const Mnemonic& mnemonic) {
    return os << mnemonic.getValue();
  }

 protected:
  /**
   * Protected member mnemonic
   */
  const std::string value_;

  /**
   * Single argument constructor
   */
  explicit Mnemonic(std::string value) : value_(std::move(value)) {}

  /**
   * Mnemonic validation method. Returns true if the mnemonic code table
   * contains the target mnemonic as a key.
   */
  static bool isValid(const std::string& value,
                      const std::unordered_map<std::string, TBinary>& table) {
    return table.contains(value);
  }

  /**
   * Virtual mnemonic code table method. Returns a static map of mnemonics to
   * their binary representations.
   */
  virtual const std::unordered_map<std::string, TBinary>& codeTable() const = 0;
};

}  // namespace hack_assembler
