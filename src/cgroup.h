/* cgroup.h
 * -*- coding: utf-8 -*-
 *
 *
 */

#ifndef CGROUP_H
#define CGROUP_H

#include <libcgroup.h>
#include <string.h>
#include <stdio.h>

bool init_cgroups();

bool create_cgroup(const char * name, const char * controllers);
bool delete_cgroup(const char * name);

bool set_option(const char * group_name, const char * option_name, const char * value);
char * get_option(const char * group_name, const char * option_name);

int cgexec(char * group_name, char * controllers, char * command);

#endif

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4 fenc=utf-8
