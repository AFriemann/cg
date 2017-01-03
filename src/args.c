/* args.c
 * -*- coding: utf-8 -*-
 *
 */

#include "args.h"

const char * argp_program_version = "cg 0.1";
const char * argp_program_bug_address = "<a.friemann@automate.wtf>";

static char doc[] = "\ncg -- run stuff in cgroups.";
static char args_doc[] = "[OPTIONS] COMMAND\n";

struct arguments parse(int argc, char ** argv) {
    struct argp_option options[] = {
        {"pids", 'p', "PIDS", 0, "how many pids the process can allocate"},
        {"group", 'g', "NAME", 0, "cgroup name"},
        {"controllers", 'c', "CONTROLLER", 0, "cgroup controllers"},
        {0}
    };

    struct argp argp = { options, 0, args_doc, doc };

    struct arguments defaults = { 10, "cdn_xyz", "cpu,memory,pids" };

    argp_parse(&argp, argc, argv, 0, 0, &defaults);

    return defaults;
}

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4 fenc=utf-8
