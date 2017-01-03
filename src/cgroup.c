/* cgroup.c
 * -*- coding: utf-8 -*-
 *
 */

#include "cgroup.h"

bool init_cgroups() {
    int ret;

    if (ret = cgroup_init() != 0) {
        fprintf(stderr, "Error: libcgroup initialization failed, %s\n", cgroup_strerror(ret));
        return false;
    }

    return true;
}

bool create_cgroup(const char * name, const char * controllers) {
    int ret;

    struct cgroup * cgroup;

    cgroup = cgroup_new_cgroup(name);

    if (!cgroup) {
        fprintf(stderr, "Error: failed to allocate cgroup\n");
        return false;
    }

    char * str = strdup(controllers);
    char * token;

    while ((token = strsep(&str, ","))) {
        if (!token) continue;

        if (!cgroup_add_controller(cgroup, token)) {
            fprintf(stderr, "Error: failed to add controller %s, %s\n", token, cgroup_strerror(ret));
            return false;
        }
    }

    if (ret = cgroup_create_cgroup(cgroup, true) != 0) {
        fprintf(stderr, "Error: cgroup creation failed, %s\n", cgroup_strerror(ret));
        return false;
    }

    return true;
}

bool delete_cgroup(const char * name) {
    int ret;

    struct cgroup * cgroup;

    cgroup = cgroup_new_cgroup(name);

    if (!cgroup) {
        fprintf(stderr, "Error: failed to allocate cgroup\n");
        return false;
    }

    if (ret = cgroup_delete_cgroup(cgroup, 1) != 0) {
        fprintf(stderr, "Error: failed to delete cgroup, %s\n", cgroup_strerror(ret));
        return false;
    }

    return true;
}

bool set_option(const char * group_name, const char * option_name, const char * value) {
    return -1;
}

char * get_option(const char * group_name, const char * option_name) {
    return "";
}

int cgexec(char * group_name, char * controllers, char * command) {
    char buffer[256];

    snprintf(buffer, sizeof buffer, "cgexec -g %s:%s -- %s", controllers, group_name, command);

    return system(buffer);
}

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4 fenc=utf-8
