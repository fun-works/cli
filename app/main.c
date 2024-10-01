#include "cli_parser.h"
#include <stdio.h>

// Callback for the --output option
void output_callback(void* arg) {
    const char* output_flag = (const char*)arg;
    printf("Output option provided: %s\n", output_flag);
}

// Callback for the --config option (mandatory)
void config_callback(void* arg) {
    printf("Config option provided\n");
}

int main(int argc, char* argv[]) {
    CLIParser parser;
    cli_init_parser(&parser);

    // Set application description
    cli_set_app_description(&parser, "This is a CLI application with optional and mandatory options.");

    // Register the --output option (optional)
    const char* output_flag = "true";
    cli_add_option(&parser, "--output", "Specify output (optional)", output_callback, (void*)output_flag, CLI_OPTION_OPTIONAL);

    // Register the --config option (mandatory)
    cli_add_option(&parser, "--config", "Specify config (mandatory)", config_callback, NULL, CLI_OPTION_MANDATORY);

    // Parse CLI arguments
    if (cli_parse_arguments(&parser, argc, argv) != 0) {
        return 1;  // Exit on error
    }

    // Continue application logic
    printf("Application is running\n");

    return 0;
}
