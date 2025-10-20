cmake_minimum_required(VERSION 4.1)
project(HackAssembler LANGUAGES CXX)

# Use the latest C++ standard (C++23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # enforce strict standard compliance

# Enable generation of compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Main library
add_library(HackAssembler
    Assembler.cpp
    Constant.cpp
    Code.cpp
    FileUtils.cpp
    Parser.cpp
    SymbolTable.cpp
)
target_include_directories(HackAssembler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(AssemblerProg main.cpp)
target_link_libraries(AssemblerProg PRIVATE HackAssembler)

enable_testing()
include(GoogleTest)
function(add_hack_test test_name)
  add_executable(${test_name} tests/${test_name}.cpp)
  target_link_libraries(${test_name} PRIVATE HackAssembler GTest::gtest_main)
  gtest_discover_tests(${test_name})
endfunction()

set(TESTS
  test_file_utils
  test_parser
  test_utils
  test_constant
  test_binary
  test_mnemonic
  test_symbol_table
  test_symbol
)

foreach(test IN LISTS TESTS)
  add_hack_test(${test})
endforeach()
