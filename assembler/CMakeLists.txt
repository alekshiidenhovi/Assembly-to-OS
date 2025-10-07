cmake_minimum_required(VERSION 4.1)
project(HackAssembler LANGUAGES CXX)

# Use the latest C++ standard (C++23)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # enforce strict standard compliance

# Enable generation of compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Main library
add_library(AssemblyLib
    Parser.cpp
    Symbol.cpp
    SymbolTable.cpp
)
target_include_directories(AssemblyLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Assembler assembler.cpp)
target_link_libraries(Assembler PRIVATE AssemblyLib)

add_executable(symbol_table_test test_symbol_table.cpp)
target_link_libraries(symbol_table_test PRIVATE AssemblyLib)
