#include "CompMnemonic.hpp"

#include <string>
#include <unordered_map>

#include "Binary.hpp"

namespace hack_assembler {

const std::unordered_map<std::string, CompBinary>&
CompMnemonic::staticCodeTable() {
  static const std::unordered_map<std::string, CompBinary> code_table = {
      // comp  ->  a c1 c2 c3 c4 c5 c6
      {"0", CompBinary("0101010")},    // 0
      {"1", CompBinary("0111111")},    // 1
      {"-1", CompBinary("0111010")},   // -1
      {"D", CompBinary("0001100")},    // D
      {"A", CompBinary("0110000")},    // A
      {"!D", CompBinary("0001101")},   // !D
      {"!A", CompBinary("0110001")},   // !A
      {"-D", CompBinary("0001111")},   // -D
      {"-A", CompBinary("0110011")},   // -A
      {"D+1", CompBinary("0011111")},  // D+1
      {"A+1", CompBinary("0110111")},  // A+1
      {"D-1", CompBinary("0001110")},  // D-1
      {"A-1", CompBinary("0110010")},  // A-1
      {"D+A", CompBinary("0000010")},  // D+A
      {"D-A", CompBinary("0010011")},  // D-A
      {"A-D", CompBinary("0000111")},  // A-D
      {"D&A", CompBinary("0000000")},  // D&A
      {"D|A", CompBinary("0010101")},  // D|A

      // M register equivalents (a bit is set to 1)
      {"M", CompBinary("1110000")},    // M  (a=1, same c-bits as A)
      {"!M", CompBinary("1110001")},   // !M (a=1, same c-bits as !A)
      {"-M", CompBinary("1110011")},   // -M (a=1, same c-bits as -A)
      {"M+1", CompBinary("1110111")},  // M+1 (a=1, same c-bits as A+1)
      {"M-1", CompBinary("1110010")},  // M-1 (a=1, same c-bits as A-1)
      {"D+M", CompBinary("1000010")},  // D+M (a=1, same c-bits as D+A)
      {"D-M", CompBinary("1010011")},  // D-M (a=1, same c-bits as D-A)
      {"M-D", CompBinary("1000111")},  // M-D (a=1, same c-bits as A-D)
      {"D&M", CompBinary("1000000")},  // D&M (a=1, same c-bits as D&A)
      {"D|M", CompBinary("1010101")}   // D|M (a=1, same c-bits as D|A)
  };
  return code_table;
};
}  // namespace hack_assembler
