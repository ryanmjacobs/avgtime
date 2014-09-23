/**
 * @file    args.h
 * @brief   Functions dealing with program arguments.
 *
 * @detail
 *          Contains data structure for program arguments.
 *
 * @author  Ryan Jacobs <ryan.mjacobs@gmail.com>
 * @date    September 15, 2014
 * @bug     No known bugs.
 */

#ifndef ARGS_H
#define ARGS_H

struct Args {
    const char *prog_name;
    char *command;

    int quiet;
    int verbose;
    unsigned long int trials;
};

/* Function Prototypes */
struct Args *get_args(int argc, char **argv);
int print_arguments(int v, struct Args *args);

#endif /* ARGS_H */
