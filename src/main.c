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
    unsigned long int num_runs;
    double total;
    verbose(v, "Start main loop.\n\n");
    fprintf(stdout, "========================================\n");
    for (num_runs = 1; num_runs <= args->trials; num_runs++) {
        if (sigint) break;

        struct timeval start, end;
        long int sec, usec;
        double runtime;

        gettimeofday(&start, NULL);
        verbose(v, "Start command.\n");
        system(args->command);
        verbose(v, "Finish command.\n");
        gettimeofday(&end, NULL);

        sec  = end.tv_sec  - start.tv_sec;
        usec = end.tv_usec - start.tv_usec;

        runtime  = (double) sec;
        runtime += (double) usec / 1000000;
        total   += runtime;

        fprintf(stdout, "Run #%03lu -> %0.3fs\n", num_runs, runtime);
    }

    fprintf(stdout, "========================================\n\n");
    fprintf(stdout, "Total = %0.3fs\n", total);
    fprintf(stdout, "Avg.  = %0.3fs\n", total / num_runs);

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
