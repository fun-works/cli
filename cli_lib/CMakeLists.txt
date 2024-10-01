# CMakeLists.txt in cli_lib/
cmake_minimum_required(VERSION 3.10)

# Set the project name for the library
project(CLIParserLib)

# Create a library from cli_parser.c
add_library(cli_parser_lib STATIC
    cli_parser.c
)

# Include the current directory to access cli_parser.h
target_include_directories(cli_parser_lib PUBLIC "${PROJECT_SOURCE_DIR}")

# Set C standard to C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
