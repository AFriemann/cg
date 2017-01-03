/* cgroups.cpp
 * -*- coding: utf-8 -*-
 *
 */

#include "catch.hpp"

#include "../src/cgroup.h"

SCENARIO( "cgroup creation", "[cgroup]" ) {
    REQUIRE( init_cgroups() == 0 );

    GIVEN( "A name and controllers" ) {
        char * name = "foobar";
        char * controllers = "cpu,memory,pids";

        WHEN ( "creating a cgroup" ) {
            REQUIRE( create_cgroup(name, controllers) );
        }
    }
}

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4 fenc=utf-8
