/**
 * @file    args.c
 * @brief   Functions dealing with program arguments.
 *
 * @author  Ryan Jacobs <ryan.mjacobs@gmail.com>
 * @date    September 15, 2014
 * @bug     No known bugs.
 */

#include "args.h"
#include "version.h" // const char *version[], used by print_version()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define exit_failure free(args); exit(EXIT_FAILURE)

const char *GLOBAL_PROGNAME;

/* Custom Options */
enum {
    OPT_VERSION
};

/* Program Options */
static const char *options[] = {
    "  -h,   --help               Display this help and exit\n",
    "  -n,   --trials             Number of trials\n",
    "  -s,   --suppress           Suppress command stdout and stderr\n",
    "  -v,   --verbose            Enable verbose output\n",
    "        --version            Output version information and exit\n",
    "\n"
};
static const struct option long_options[] = {
    { "help",        optional_argument, NULL, 'h'          },
    { "trials",      required_argument, NULL, 'n'          },
    { "verbose",     no_argument,       NULL, 'v'          },
    { "suppress",    no_argument,       NULL, 's'          },
    { "version",     no_argument,       NULL,  OPT_VERSION },
    { NULL, 0, NULL, 0 }
};

static const struct Args default_args = {
    "avgtime",               // program name
    "\0",                    // command
    0,                       // no verbosity
    10                       // default num. trials
};

/* Static Function Prototypes */
static int check_args(struct Args *args);
static int print_usage(FILE *stream, const char *prog_name);
static int print_options(FILE *stream);
static int print_footer(FILE *stream, const char *prog_name);
static int print_version(FILE *stream);
static int print_help(FILE *stream, const char *prog_name);

struct Args *get_args(int argc, char **argv) {
    struct Args *args = (struct Args *) malloc(sizeof(struct Args));

    memcpy(args, &default_args, sizeof(struct Args));
    args->prog_name = GLOBAL_PROGNAME = argv[0];

    char c;
    int supress = 0;
    extern char *optarg;
    while ((c = getopt_long(argc, argv, "hn:sv", long_options, NULL)) != -1) {
        switch (c) {
            case 'n':
                args->trials = strtoul(optarg, NULL, 10);
                break;
            case 'h':
                print_usage(stderr, args->prog_name);
                print_options(stderr);
                print_footer(stderr, args->prog_name);
                free(args);
                exit(EXIT_SUCCESS);
                break;
            case 's':
                supress = 1;
                break;
            case 'v':
                args->verbose = 1;
                break;
            case OPT_VERSION:
                print_version(stderr);
                exit(EXIT_SUCCESS);
                break;
            case '?':
                print_help(stderr, args->prog_name);
                exit_failure; // see #define at top of file
                break;
            default:
                break;
        }
    }

    /* Get the first non-option argument */
    if (optind < argc)
        args->command = argv[optind];

    /* Supress command output if -s flag */
    if (supress)
        strcat(args->command, "&>/dev/null");

    check_args(args);
    return args;
}

int print_arguments(int v, struct Args *args) {
    if (!v) return 1;

    #define truefalse(x) (x) ? "True" : "False"

    print_version(stderr);
    fprintf(stderr, "\n");

    fprintf(stderr, "Arguments & Options:\n");
    fprintf(stderr, "\tprog_name -> %s\n",  args->prog_name);
    fprintf(stderr, "\tcommand   -> %s\n",  args->command);
    fprintf(stderr, "\tverbose   -> %s\n",  truefalse(args->verbose));
    fprintf(stderr, "\ttrials    -> %lu\n", args->trials);
    fprintf(stderr, "\n");

    return 0;
}

static int check_args(struct Args *args) {
    const char *name = args->prog_name;

    /* Check for command */
    if (strlen(args->command) == 0) {
        fprintf(stderr, "%s: missing command\n", name);
        print_help(stderr, name);
        exit_failure; // see #define at top of file
    }

    return 0;
}

static int print_usage(FILE *stream, const char *prog_name) {
    fprintf(stream, "Usage: %s [-n num_trials] [options] <command>\n", prog_name);
    fprintf(stream, "avgtime, Command Benchmarking Tool.\n\n");

    return 0;
}

static int print_options(FILE *stream) {
    unsigned int i;

    for (i = 0; i < sizeof(options) / sizeof(options[0]); i++)
        fprintf(stream, "%s", options[i]);

    return 0;
}

static int print_footer(FILE *stream, const char *prog_name) {
    fprintf(stream, "Examples:\n");
    fprintf(stream, "  %s -n 100 'echo hi'  Find avg. execution time of the command: 'echo hi'\n", prog_name);
    fprintf(stream, "\n");

    fprintf(stream, "Report bugs to <ryan.mjacobs@gmail.com>\n");

    return 0;
}

static int print_version(FILE *stream) {
    unsigned int i;

    for (i = 0; i < sizeof(version) / sizeof(version[0]); i++)
        fprintf(stderr, "%s", version[i]);

    return 0;
}

static int print_help(FILE *stream, const char *prog_name) {
    fprintf(stderr, "Try '%s --help' for more information.\n", prog_name);

    return 0;
}
