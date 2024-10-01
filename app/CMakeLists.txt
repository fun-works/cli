# CMakeLists.txt in app/
cmake_minimum_required(VERSION 3.10)

# Set the project name for the application
project(CLIParserApp)

# Add executable for the application
add_executable(cli_parser_app
    main.c
)

# Link the cli_parser_lib to the application
target_link_libraries(cli_parser_app PRIVATE cli_parser_lib)

# Include the directory where cli_parser.h exists
target_include_directories(cli_parser_app PRIVATE "${PROJECT_SOURCE_DIR}/../cli_lib")

# Set C standard to C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
