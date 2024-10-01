#include "cli_parser.h"
#include "cli_parser_test.h"

// Test callback function for the test options
void test_callback(void* arg) {
    printf("Callback called for option %s\n", (const char*)arg);
}

// Test to check if CLI parser can correctly add an option
int test_add_option() {
    TEST_CASE("test_add_option");

    CLIParser parser;
    cli_init_parser(&parser);

    // Add an option
    cli_add_option(&parser, "--test", "Test option", test_callback, "Test", CLI_OPTION_OPTIONAL);

    // Assert that the option was added
    ASSERT_TRUE(parser.option_count == 2);  // 1 for default help and 1 for test
    ASSERT_TRUE(strcmp(parser.options[1].option, "--test") == 0);
    ASSERT_TRUE(strcmp(parser.options[1].description, "Test option") == 0);
    ASSERT_TRUE(parser.options[1].callback != NULL);

    return 0;
}

// Test to check if help option is added by default
int test_default_help_option() {
    TEST_CASE("test_default_help_option");

    CLIParser parser;
    cli_init_parser(&parser);

    // Assert that the default help option is added
    ASSERT_TRUE(parser.option_count == 1);
    ASSERT_TRUE(strcmp(parser.options[0].option, "-h") == 0);

    return 0;
}

// Test to verify parsing of mandatory and optional options
int test_parse_mandatory_and_optional() {
    TEST_CASE("test_parse_mandatory_and_optional");

    CLIParser parser;
    cli_init_parser(&parser);

    // Add mandatory and optional options
    cli_add_option(&parser, "--config", "Mandatory config option", test_callback, "--config", CLI_OPTION_MANDATORY);
    cli_add_option(&parser, "--output", "Optional output option", test_callback, "--output", CLI_OPTION_OPTIONAL);

    // Simulate command line input
    char* argv[] = {"./app", "--output", "--config"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    // Parse arguments
    int result = cli_parse_arguments(&parser, argc, argv);

    // Assert that the parsing was successful
    ASSERT_TRUE(result == 0);

    return 0;
}

// Test missing mandatory option
int test_missing_mandatory_option() {
    TEST_CASE("test_missing_mandatory_option");

    CLIParser parser;
    cli_init_parser(&parser);

    // Add mandatory and optional options
    cli_add_option(&parser, "--config", "Mandatory config option", test_callback, "--config", CLI_OPTION_MANDATORY);
    cli_add_option(&parser, "--output", "Optional output option", test_callback, "--output", CLI_OPTION_OPTIONAL);

    // Simulate command line input without the mandatory option
    char* argv[] = {"./app", "--output"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    // Parse arguments
    int result = cli_parse_arguments(&parser, argc, argv);

    // Assert that the parsing failed due to missing mandatory option
    ASSERT_TRUE(result != 0);

    return 0;
}

// Test optional option only
int test_optional_option_only() {
    TEST_CASE("test_optional_option_only");

    CLIParser parser;
    cli_init_parser(&parser);

    // Add mandatory and optional options
    cli_add_option(&parser, "--config", "Mandatory config option", test_callback, "--config", CLI_OPTION_MANDATORY);
    cli_add_option(&parser, "--output", "Optional output option", test_callback, "--output", CLI_OPTION_OPTIONAL);

    // Simulate command line input with only optional option
    char* argv[] = {"./app", "--output"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    // Parse arguments
    int result = cli_parse_arguments(&parser, argc, argv);

    // Assert that the parsing failed due to missing mandatory option
    ASSERT_TRUE(result != 0);

    return 0;
}

// Test help option
int test_help_option() {
    TEST_CASE("test_help_option");

    CLIParser parser;
    cli_init_parser(&parser);

    // Simulate command line input with the help option
    char* argv[] = {"./app", "-h"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    // Parse arguments (this should print the help menu and return 0)
    int result = cli_parse_arguments(&parser, argc, argv);

    // Assert that the parsing was successful
    ASSERT_TRUE(result == 0);

    return 0;
}

// Run all tests
TEST_SUITE_BEGIN()

    RUN_TEST(test_add_option)
    RUN_TEST(test_default_help_option)
    RUN_TEST(test_parse_mandatory_and_optional)
    RUN_TEST(test_missing_mandatory_option)
    RUN_TEST(test_optional_option_only)
    RUN_TEST(test_help_option)

TEST_SUITE_END()
