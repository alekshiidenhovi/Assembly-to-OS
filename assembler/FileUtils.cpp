#include "FileUtils.hpp"

#include <filesystem>
#include <fstream>
#include <ios>
#include <stdexcept>
#include <string>
#include <utility>

#include "Constants.hpp"

namespace hack_assembler {

namespace fs = ::std::filesystem;

namespace {

/**
 * @brief Validates the number of command line arguments and the first argument
 * is a valid file path.
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 * @throws std::invalid_argument if the number of arguments is not 2.
 */
void validateCLIArguments(int argc, char* argv[]) {
  if (argc != 2) {
    throw std::invalid_argument(
        "Incorrect number of CLI arguments! Expected 1, received " +
        std::to_string(argc - 1) + ". Usage: " + std::string(argv[0]) +
        " <filename>");
  }
}

/**
 * @brief Validates the source file extension.
 * @param src_filepath The source file path.
 * @throws std::invalid_argument if the source file does not have an extension
 * or if the extension is not '.asm'.
 */
void validateInputFileExtension(const fs::path& src_filepath) {
  if (!src_filepath.has_extension()) {
    throw std::invalid_argument(
        "Source file path is missing a file extension. Please ensure it has "
        "an " +
        std::string(hack_assembler::kAssemblyFileExtension) + " extension.");
  }

  const std::string src_extension = src_filepath.extension().string();
  if (src_extension != hack_assembler::kAssemblyFileExtension) {
    throw std::invalid_argument(
        "Source file needs to be a Hack Assembly file with the '" +
        std::string(hack_assembler::kAssemblyFileExtension) +
        "' extension. You passed '" + src_filepath.string() + "' with '" +
        src_extension + "' extension.");
  }
}

/**
 * @brief Validates that the source file exists.
 * @param src_filepath The source file path.
 * @throws std::filesystem::filesystem_error if the file does not exist.
 */
void validateExistingInputFile(const fs::path& src_filepath) {
  if (!fs::exists(src_filepath)) {
    throw fs::filesystem_error(
        "Source file not found", src_filepath.string(),
        std::make_error_code(std::errc::no_such_file_or_directory));
  }
}

/**
 * @brief Creates the output file path from the source file path.
 * @param src_filepath The source file path.
 * @return The output file path.
 */
fs::path createOutputFilePath(const fs::path& src_filepath) {
  const std::string src_filename = src_filepath.stem().string();
  return fs::path(src_filename +
                  std::string(hack_assembler::kHackFileExtension));
}

}  // namespace

namespace file_utils {

std::pair<std::ifstream, std::ofstream> setupAssemblyFiles(int argc,
                                                           char* argv[]) {
  validateCLIArguments(argc, argv);

  const fs::path src_filepath(argv[1]);
  validateInputFileExtension(src_filepath);
  validateExistingInputFile(src_filepath);

  const fs::path out_filepath = createOutputFilePath(src_filepath);

  std::ifstream src_file(src_filepath);
  std::ofstream out_file(
      out_filepath,
      std::ios::out | std::ios::trunc);  // Wipe out a file if it exists

  return {std::move(src_file), std::move(out_file)};
}

}  // namespace file_utils
}  // namespace hack_assembler
