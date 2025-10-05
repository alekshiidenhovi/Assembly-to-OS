cmake_minimum_required(VERSION 4.1)
project(AssemblyToOS LANGUAGES CXX)

# Use the latest C++ standard (C++23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # enforce strict standard compliance

# Enable generation of compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Main library
add_library(assembly_lib
    assembler.cpp
    Symbol.cpp
    SymbolTable.cpp
)

target_include_directories(assembly_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Test executable
add_executable(symbol_table_test test_symbol_table.cpp)
target_link_libraries(symbol_table_test PRIVATE assembly_lib)
