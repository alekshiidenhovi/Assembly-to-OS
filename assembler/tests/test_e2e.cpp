#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <ios>

#include "Assembler.hpp"
#include "FileUtils.hpp"

namespace fs = ::std::filesystem;

class E2ETest : public ::testing::Test {
 protected:
  void SetUp() override {
    temp_out_dirpath = fs::temp_directory_path() / "hack_assembler_outputs";
    fs::create_directory(temp_out_dirpath);

    ASSERT_TRUE(fs::exists(temp_out_dirpath));
  }

  void TearDown() override {
    if (fs::exists(temp_out_dirpath)) {
      fs::remove_all(temp_out_dirpath);
    }
  }

  void test_asm_program(const std::string& src_filepath_str,
                        const std::string& actual_out_filepath_str,
                        const std::string& expected_out_filepath_str,
                        const std::string& temp_out_dirpath_str) {
    int argc = 3;
    char* argv[] = {(char*)kProgramName.data(), (char*)src_filepath_str.data(),
                    (char*)temp_out_dirpath_str.data()};
    auto [src_filepath, out_filepath] =
        hack_assembler::file_utils::parseAssemblyFilePaths(argc, argv);
    std::ifstream src_stream(src_filepath);
    std::ofstream out_stream(out_filepath, std::ios::out | std::ios::trunc);

    auto assembler = hack_assembler::Assembler(src_stream, out_stream);
    assembler.first_pass();
    assembler.second_pass();
    out_stream.close();

    std::ifstream actual_out_stream(actual_out_filepath_str);
    std::ifstream expected_out_stream(expected_out_filepath_str);

    ASSERT_TRUE(actual_out_stream.is_open())
        << "Could not open actual output file for reading.";
    ASSERT_TRUE(expected_out_stream.is_open())
        << "Could not open expected output file for reading.";

    std::string actual_line;
    std::string expected_line;
    int line_number = 1;

    while (std::getline(actual_out_stream, actual_line) &&
           std::getline(expected_out_stream, expected_line)) {
      ASSERT_EQ(actual_line, expected_line)
          << "Files differ at line " << line_number << ". "
          << "Actual: " << actual_line << ", "
          << "Expected: " << expected_line;
      line_number++;
    }

    ASSERT_FALSE(std::getline(actual_out_stream, actual_line))
        << "Actual output file has more lines (starts at line " << line_number
        << ").";

    ASSERT_FALSE(std::getline(expected_out_stream, expected_line))
        << "Expected output file has more lines (starts at line " << line_number
        << ").";

    actual_out_stream.close();
    expected_out_stream.close();
  }

  const std::string kProgramName = "Assembler";
  fs::path temp_out_dirpath;
};

TEST_F(E2ETest, FillProgram) {
  std::string src_filepath_str = "../programs/fill/Fill.asm";
  std::string actual_out_filepath_str = temp_out_dirpath / "Fill.hack";
  std::string expected_out_filepath_str = "../programs/fill/Fill_expected.hack";
  std::string temp_out_dirpath_str = temp_out_dirpath;

  test_asm_program(src_filepath_str, actual_out_filepath_str,
                   expected_out_filepath_str, temp_out_dirpath_str);
}

TEST_F(E2ETest, MultProgram) {
  std::string src_filepath_str = "../programs/mult/Mult.asm";
  std::string actual_out_filepath_str = temp_out_dirpath / "Mult.hack";
  std::string expected_out_filepath_str = "../programs/mult/Mult_expected.hack";
  std::string temp_out_dirpath_str = temp_out_dirpath;

  test_asm_program(src_filepath_str, actual_out_filepath_str,
                   expected_out_filepath_str, temp_out_dirpath_str);
}
