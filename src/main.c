/* main.c
 * -*- coding: utf-8 -*-
 *
 */

#include <libcgroup.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>

#include "args.h"
#include "cgroup.h"

int main(int argc, char* argv[]) {
    struct arguments args = parse(argc, argv);

    printf("creating group: %s\n", args.group);
    printf("allowing pids: %d\n", args.pids);
    printf("using controllers: %s\n", args.controllers);

    if (!init_cgroups()) {
        error(EXIT_FAILURE, 0, "failed to init cgroups");
    }

    if (!create_cgroup(args.group, args.controllers)) {
        error(EXIT_FAILURE, 0, "failed to create cgroups %s", args.group);
    }

    cgexec(args.group, args.controllers, "ls -l /");

    if (!delete_cgroup(args.group)) {
        error(EXIT_FAILURE, 0, "failed to delete cgroup %s", args.group);
    }

    return 0;
}

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4 fenc=utf-8
