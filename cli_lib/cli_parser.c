#include <stdio.h>
#include <string.h>
#include "cli_parser.h"

// Default callback for the help option
void cli_default_help_callback(void* arg) {
    CLIParser* parser = (CLIParser*)arg;
    cli_display_help(parser);
}

// Initialize the parser and register the default help option (-h)
void cli_init_parser(CLIParser* parser) {
    parser->option_count = 0;
    memset(parser->app_description, 0, sizeof(parser->app_description));

    // Automatically register the help option (-h)
    cli_add_option(parser, "-h", "Show help", cli_default_help_callback, (void*)parser, CLI_OPTION_OPTIONAL);
}

// Set the application description to be displayed in the help menu
void cli_set_app_description(CLIParser* parser, const char* description) {
    strncpy(parser->app_description, description, sizeof(parser->app_description) - 1);
}

// Add a new option and description with a callback, argument, and type to the parser
void cli_add_option(CLIParser* parser, const char* option, const char* description, OptionCallback callback, void* arg, CLIOptionType type) {
    if (parser->option_count >= MAX_OPTIONS) {
        printf("Error: Maximum number of options reached\n");
        return;
    }
    
    // Add the option, description, callback, and type
    strncpy(parser->options[parser->option_count].option, option, sizeof(parser->options[parser->option_count].option) - 1);
    strncpy(parser->options[parser->option_count].description, description, sizeof(parser->options[parser->option_count].description) - 1);
    parser->options[parser->option_count].callback = callback;
    parser->options[parser->option_count].arg = arg;
    parser->options[parser->option_count].type = type;
    parser->option_count++;
}

// Parse arguments and invoke callbacks for each registered option
int cli_parse_arguments(CLIParser* parser, int argc, char* argv[]) {
    int mandatory_options_found[MAX_OPTIONS] = {0};

    // Loop through all provided arguments
    for (int i = 1; i < argc; ++i) {
        int found = 0;
        for (int j = 0; j < parser->option_count; ++j) {
            if (strcmp(argv[i], parser->options[j].option) == 0) {
                found = 1;
                mandatory_options_found[j] = 1;  // Mark mandatory option as found if applicable

                // Option found, invoke the callback with the registered argument
                if (parser->options[j].callback != NULL) {
                    parser->options[j].callback(parser->options[j].arg);
                }
                break;
            }
        }

        if (!found) {
            printf("Unknown option: %s\n", argv[i]);
            return 1;  // Exit if an unknown option is found
        }
    }

    // After processing all arguments, check for missing mandatory options
    for (int i = 0; i < parser->option_count; ++i) {
        if (parser->options[i].type == CLI_OPTION_MANDATORY && !mandatory_options_found[i]) {
            printf("Error: Missing mandatory option %s\n", parser->options[i].option);
            return 1;  // Exit if any mandatory option is missing
        }
    }

    return 0;  // Successful parsing
}

// Display all registered options with descriptions, aligned properly
void cli_display_help(CLIParser* parser) {
    // Display the application description if available
    if (strlen(parser->app_description) > 0) {
        printf("%s\n\n", parser->app_description);
    }

    // Find the maximum length of the options to format descriptions
    int max_option_len = 0;
    for (int i = 0; i < parser->option_count; ++i) {
        int len = strlen(parser->options[i].option);
        if (len > max_option_len) {
            max_option_len = len;
        }
    }

    // Display the help menu with aligned descriptions
    printf("Available options:\n");
    for (int i = 0; i < parser->option_count; ++i) {
        printf("  %-*s  %s\n", max_option_len, parser->options[i].option, parser->options[i].description);
    }
}
