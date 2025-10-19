#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <string>

#include "FileUtils.hpp"

namespace fs = ::std::filesystem;

class FileUtilsTest : public ::testing::Test {
 protected:
  void SetUp() override {
    temp_dir_path = fs::temp_directory_path() / "hack_assembler_tests";
    fs::create_directory(temp_dir_path);

    const std::string existing_file_path =
        (temp_dir_path / kExistingFileName).string();

    std::ofstream existing_file(existing_file_path);
    existing_file << "M=1" << std::endl;
    existing_file.close();

    ASSERT_TRUE(fs::exists(temp_dir_path));
  }

  void TearDown() override {
    if (fs::exists(temp_dir_path)) {
      fs::remove_all(temp_dir_path);
    }
  }

  const std::string kProgramName = "assembler";
  const std::string kExistingFileName = "test_simple_program.asm";

  fs::path temp_dir_path;
};

TEST_F(FileUtilsTest, ValidCLIArguments) {
  const int argc = 2;
  const std::string full_path = (temp_dir_path / kExistingFileName).string();

  char* argv[] = {const_cast<char*>(kProgramName.data()),
                  const_cast<char*>(full_path.data())};

  EXPECT_NO_THROW(hack_assembler::file_utils::setupAssemblyFiles(argc, argv));
}

TEST_F(FileUtilsTest, MissingFileExtension) {
  const int argc = 2;
  const std::string full_path =
      (temp_dir_path / "test_simple_program").string();

  char* argv[] = {const_cast<char*>(kProgramName.data()),
                  const_cast<char*>(full_path.data())};

  EXPECT_THROW(hack_assembler::file_utils::setupAssemblyFiles(argc, argv),
               std::invalid_argument);
}

TEST_F(FileUtilsTest, InvalidFileExtension) {
  const int argc = 2;
  const std::string full_path =
      (temp_dir_path / "test_simple_program.txt").string();

  char* argv[] = {const_cast<char*>(kProgramName.data()),
                  const_cast<char*>(full_path.data())};

  EXPECT_THROW(hack_assembler::file_utils::setupAssemblyFiles(argc, argv),
               std::invalid_argument);
}

TEST_F(FileUtilsTest, NonExistentInputFile) {
  const int argc = 2;
  const std::string full_path =
      (temp_dir_path / "non_existent_file.asm").string();

  char* argv[] = {const_cast<char*>(kProgramName.data()),
                  const_cast<char*>(full_path.data())};

  EXPECT_THROW(hack_assembler::file_utils::setupAssemblyFiles(argc, argv),
               fs::filesystem_error);
}
