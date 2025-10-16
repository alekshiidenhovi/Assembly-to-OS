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
add_library(AssemblyLib
    Constant.cpp
    CompMnemonic.cpp
    DestMnemonic.cpp
    JumpMnemonic.cpp
    Parser.cpp
    SymbolTable.cpp
)
target_include_directories(AssemblyLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Assembler assembler.cpp)
target_link_libraries(Assembler PRIVATE AssemblyLib)

enable_testing()

add_executable(test_constant tests/test_constant.cpp)
add_executable(test_binary tests/test_binary.cpp)
add_executable(test_mnemonic tests/test_mnemonic.cpp)
add_executable(test_symbol_table tests/test_symbol_table.cpp)
add_executable(test_symbol tests/test_symbol.cpp)

target_link_libraries(test_constant PRIVATE AssemblyLib GTest::gtest_main)
target_link_libraries(test_binary PRIVATE AssemblyLib GTest::gtest_main)
target_link_libraries(test_mnemonic PRIVATE AssemblyLib GTest::gtest_main)
target_link_libraries(test_symbol_table PRIVATE AssemblyLib GTest::gtest_main)
target_link_libraries(test_symbol PRIVATE AssemblyLib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_constant)
gtest_discover_tests(test_binary)
gtest_discover_tests(test_mnemonic)
gtest_discover_tests(test_symbol_table)
gtest_discover_tests(test_symbol)

