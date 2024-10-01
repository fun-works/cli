#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#define MAX_OPTIONS 10
#define MAX_DESC_LEN 100
#define MAX_APP_DESC_LEN 200

// Define a type for the callback function (without opt_arg)
typedef void (*OptionCallback)(void* arg);

// Enum to differentiate between mandatory and optional options
typedef enum {
    CLI_OPTION_MANDATORY,
    CLI_OPTION_OPTIONAL
} CLIOptionType;

// Structure for a CLI option with a callback
typedef struct {
    char option[20];                         // CLI option (e.g., "-h", "--help")
    char description[MAX_DESC_LEN];          // Description of the option
    OptionCallback callback;                 // Callback function for this option
    void* arg;                               // Argument to pass to the callback
    CLIOptionType type;                      // Whether the option is mandatory or optional
} CLIOption;

// Struct to manage options, descriptions, and application description
typedef struct {
    CLIOption options[MAX_OPTIONS];
    int option_count;
    char app_description[MAX_APP_DESC_LEN];  // Application description
} CLIParser;

// Initialize CLIParser and register default help option
void cli_init_parser(CLIParser* parser);

// Set the application description
void cli_set_app_description(CLIParser* parser, const char* description);

// Add a new option with description, callback, argument, and type (mandatory/optional)
void cli_add_option(CLIParser* parser, const char* option, const char* description, OptionCallback callback, void* arg, CLIOptionType type);

// Parse the arguments as per registered options
int cli_parse_arguments(CLIParser* parser, int argc, char* argv[]);

// Display the help message with the application description
void cli_display_help(CLIParser* parser);

#endif // CLI_PARSER_H
