/* args.h
 * -*- coding: utf-8 -*-
 *
 *
 */

#ifndef ARGS_H
#define ARGS_H

#include <argp.h>

struct arguments {
    int pids;
    char * group;
    char * controllers;
    //char * command;
};

struct arguments parse(int argc, char ** argv);

#endif

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4 fenc=utf-8
