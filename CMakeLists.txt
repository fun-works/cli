cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CLIParserProject VERSION 1.0)

# Add the library directory
add_subdirectory(cli_lib)

# Add the application directory
add_subdirectory(app)

# Add the test directory

enable_testing()
add_subdirectory(tests)
