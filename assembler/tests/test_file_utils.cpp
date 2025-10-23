#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>

#include "FileUtils.hpp"

namespace fs = ::std::filesystem;

class FileUtilsTest : public ::testing::Test {
 protected:
  void SetUp() override {
    temp_src_dir_path = fs::temp_directory_path() / "hack_assembler_inputs";
    temp_out_dir_path = fs::temp_directory_path() / "hack_assembler_outputs";

    fs::create_directory(temp_src_dir_path);
    fs::create_directory(temp_out_dir_path);

    const std::string existing_src_file_path =
        (temp_src_dir_path / kExistingFileName).string();

    std::ofstream existing_src_file(existing_src_file_path);
    existing_src_file << "M=1" << std::endl;
    existing_src_file.close();

    ASSERT_TRUE(fs::exists(temp_src_dir_path));
    ASSERT_TRUE(fs::exists(temp_out_dir_path));
  }

  void TearDown() override {
    if (fs::exists(temp_src_dir_path)) {
      fs::remove_all(temp_src_dir_path);
    }

    if (fs::exists(temp_out_dir_path)) {
      fs::remove_all(temp_out_dir_path);
    }
  }

  const std::string kProgramName = "assembler";
  const std::string kExistingFileName = "test_simple_program.asm";

  fs::path temp_src_dir_path;
  fs::path temp_out_dir_path;
};

TEST_F(FileUtilsTest, ValidCLIArgumentsTwoArgs) {
  const int argc = 2;
  const std::string full_src_filepath_str =
      (temp_src_dir_path / kExistingFileName).string();

  char* argv[] = {const_cast<char*>(kProgramName.data()),
                  const_cast<char*>(full_src_filepath_str.data())};

  EXPECT_NO_THROW(
      hack_assembler::file_utils::parseAssemblyFilePaths(argc, argv));
}

TEST_F(FileUtilsTest, ValidCLIArgumentsThreeArgs) {
  const int argc = 3;
  const std::string full_src_filepath_str =
      (temp_src_dir_path / kExistingFileName).string();
  const std::string full_out_dirpath_str = temp_out_dir_path.string();

  char* argv[] = {const_cast<char*>(kProgramName.data()),
                  const_cast<char*>(full_src_filepath_str.data()),
                  const_cast<char*>(full_out_dirpath_str.data())};

  EXPECT_NO_THROW(
      hack_assembler::file_utils::parseAssemblyFilePaths(argc, argv));
}

TEST_F(FileUtilsTest, MissingSrcFileExtension) {
  const int argc = 2;
  const std::string full_src_filepath_str =
      (temp_src_dir_path / "test_simple_program").string();

  char* argv[] = {const_cast<char*>(kProgramName.data()),
                  const_cast<char*>(full_src_filepath_str.data())};

  EXPECT_THROW(hack_assembler::file_utils::parseAssemblyFilePaths(argc, argv),
               std::invalid_argument);
}

TEST_F(FileUtilsTest, InvalidSrcFileExtension) {
  const int argc = 2;
  const std::string full_src_filepath_str =
      (temp_src_dir_path / "test_simple_program.txt").string();

  char* argv[] = {const_cast<char*>(kProgramName.data()),
                  const_cast<char*>(full_src_filepath_str.data())};

  EXPECT_THROW(hack_assembler::file_utils::parseAssemblyFilePaths(argc, argv),
               std::invalid_argument);
}

TEST_F(FileUtilsTest, NonExistentSrcFile) {
  const int argc = 2;
  const std::string full_src_filepath_str =
      (temp_src_dir_path / "non_existent_file.asm").string();

  char* argv[] = {const_cast<char*>(kProgramName.data()),
                  const_cast<char*>(full_src_filepath_str.data())};

  EXPECT_THROW(hack_assembler::file_utils::parseAssemblyFilePaths(argc, argv),
               fs::filesystem_error);
}

TEST_F(FileUtilsTest, NonExistentOutputDirectory) {
  const int argc = 3;
  const std::string full_src_filepath_str =
      (temp_src_dir_path / kExistingFileName).string();
  const std::string full_out_dirpath_str =
      (temp_out_dir_path / "non_existent_dir").string();

  char* argv[] = {const_cast<char*>(kProgramName.data()),
                  const_cast<char*>(full_src_filepath_str.data()),
                  const_cast<char*>(full_out_dirpath_str.data())};

  EXPECT_THROW(hack_assembler::file_utils::parseAssemblyFilePaths(argc, argv),
               fs::filesystem_error);
}
