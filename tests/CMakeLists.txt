cmake_minimum_required(VERSION 3.5)
project(cli_parser_tests)

add_executable(cli_parser_tests cli_parser_test.c)
target_include_directories(cli_parser_tests PRIVATE ../cli_lib)
target_link_libraries(cli_parser_tests PRIVATE cli_parser_lib)

add_test( NAME cli_parser_tests
          COMMAND $<TARGET_FILE:cli_parser_tests>)
