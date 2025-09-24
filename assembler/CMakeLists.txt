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
    code.cpp
    assembler.cpp
    parser.cpp
)

target_include_directories(assembly_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Test executable
add_executable(test_code test_code.cpp)
target_link_libraries(test_code PRIVATE assembly_lib)
