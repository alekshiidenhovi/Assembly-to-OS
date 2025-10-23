#include "FileUtils.hpp"

#include <filesystem>
#include <stdexcept>
#include <string>
#include <utility>

#include "Constants.hpp"

namespace hack_assembler {

namespace file_utils {

namespace fs = ::std::filesystem;

std::pair<fs::path, fs::path> parseAssemblyFilePaths(int argc, char* argv[]) {
  if (argc < 2 || argc > 3) {
    throw std::invalid_argument(
        "Incorrect number of CLI arguments! Expected 1 or 2, received " +
        std::to_string(argc - 1) + ". Usage: " + std::string(argv[0]) +
        " <filename> [<output directory>]");
  }

  const fs::path src_filepath(argv[1]);
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

  if (!fs::exists(src_filepath)) {
    throw fs::filesystem_error(
        "Source file not found", src_filepath.string(),
        std::make_error_code(std::errc::no_such_file_or_directory));
  }

  fs::path absolute_out_dirpath;
  if (argc == 3) {
    const fs::path out_dirpath(argv[2]);

    if (!fs::exists(out_dirpath)) {
      throw fs::filesystem_error(
          "Output directory does not exist!", out_dirpath.string(),
          std::make_error_code(std::errc::no_such_file_or_directory));
    }

    if (out_dirpath.is_relative()) {
      absolute_out_dirpath = fs::current_path() / out_dirpath;
    } else {
      absolute_out_dirpath = out_dirpath;
    }
  } else if (argc == 2) {
    if (src_filepath.is_relative()) {
      absolute_out_dirpath = fs::current_path() / src_filepath.parent_path();
    } else {
      absolute_out_dirpath = src_filepath.parent_path();
    }
  } else {
    throw std::invalid_argument(
        "Invalid number of CLI arguments, should be either 1 or 2!");
  }

  const std::string src_filestem = src_filepath.stem().string();
  const fs::path out_filepath =
      fs::path(absolute_out_dirpath) /
      (src_filestem + hack_assembler::kHackFileExtension);

  return {src_filepath, out_filepath};
}

}  // namespace file_utils
}  // namespace hack_assembler
