/**
 * @file    main.c
 * @brief   Contains main routuine of Power_Usage_Collector.
 *
 * @author  Ryan Jacobs <ryan.mjacobs@gmail.com>
 * @date    September 15, 2014
 * @bug     No known bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>

#include <sys/time.h>

#include "args.h"

/* Function Prototypes */
static void sigint_handler(int sig);
static int verbose(int verbose, const char *string);

/* Global Variables */
static int sigint = 0;

int main(int argc, char **argv) {
    /* Register ctrl-c signal */
    signal(SIGINT, sigint_handler);

    /* Get program arguments */
    struct Args *args = get_args(argc, argv);
    if (args == NULL) {
        fprintf(stderr, "Error: unable to parse arguments\n");
        exit(EXIT_FAILURE);
    }

    int v = args->verbose; // are we verbose?
    print_arguments(v, args);

    /* Main loop */
    verbose(v, "Starting main loop.\n");
    while (!sigint) {
        struct timeval cur_time;

        /* Get program uptime */
        gettimeofday(&cur_time, NULL);
      //cur_time.tv_usec;
      //cur_time.tv_sec;
    }

    /* Free memory and exit */
    fprintf(stderr, "\nQuitting.\n");
    free(args);

    return 0;
}

static void sigint_handler(int sig) {
    sigint = 1;
};


// returns 1 if it worked, and 0 if it didn't
static int verbose(int verbose, const char *string) {
    if (verbose) {
        fprintf(stderr, "%s", string);
        return 1;
    }
    else {
        return 0;
    }
}
