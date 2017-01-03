# <Copyright Holder>. Copyright (C) <Copyright Year(s)>. <License>.

#
# Project Properties
#
CMAKE_MINIMUM_REQUIRED (VERSION 2.6.2)
PROJECT (cg)
SET (APPLICATION_NAME "cg")
SET (APPLICATION_CODENAME "${PROJECT_NAME}")
SET (APPLICATION_COPYRIGHT_YEARS "2015")
SET (APPLICATION_VERSION_MAJOR 1)
SET (APPLICATION_VERSION_MINOR 0)
SET (APPLICATION_VERSION_PATCH 0)
SET (APPLICATION_VERSION_TYPE SNAPSHOT)
SET (APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}")

#
# Debugging Options
#
SET (CMAKE_VERBOSE_MAKEFILE 1) # Use 1 for debugging, 0 for release

#
# Project Output Paths
#
SET (MAINFOLDER ${PROJECT_SOURCE_DIR})
SET (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
SET (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

option(OPTIMIZE "build with optimization flags" ON)
option(SSE2 "build with sse2 support" ON)
option(DEBUG "build with debug stuff" OFF)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

if (SSE2)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
endif()

if (DEBUG)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")
endif()

if (OPTIMIZE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fmerge-all-constants")
endif()

################################################################################
# Project Search Paths
################################################################################

LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/tools")
SET (CMAKE_MODULE_PATH "${MAINFOLDER}/tools/share/cmake")

INCLUDE_DIRECTORIES(SYSTEM "${MAINFOLDER}/include")

################################################################################
# Libraries
################################################################################

find_library(libcgroup cgroup)

if (libcgroup-NOTFOUND)
    message( FATAL_ERROR "libcgroup not found" )
endif()

set(catch_DIR "${MAINFOLDER}/thirdparty/catch-1.5.9")
set(catch_HEADERS "${catch_DIR}/catch.hpp")
include_directories(${catch_DIR})

SET(thirdparty_LIBRARIES cgroup)
SET(thirdparty_TEST_LIBRARIES ${thirdparty_LIBRARIES})

################################################################################
# Configure Files
################################################################################

FILE (GLOB_RECURSE CONFIGINPUTS1 include/*.in.h.cmake)
FILE (GLOB_RECURSE CONFIGINPUTS2 include/*.h.in.cmake)
FILE (GLOB_RECURSE CONFIGINPUTS3 src/*.in.h.cmake)
FILE (GLOB_RECURSE CONFIGINPUTS4 src/*.h.in.cmake)
FILE (GLOB_RECURSE CONFIGINPUTS5 test/*.in.h.cmake)
FILE (GLOB_RECURSE CONFIGINPUTS6 test/*.h.in.cmake)
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS1}")
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS2}")
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS3}")
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS4}")
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS5}")
LIST (APPEND CONFIGINPUTS "${CONFIGINPUTS6}")
FOREACH (CONFIGINPUT ${CONFIGINPUTS})
    STRING (REPLACE ".in.h.cmake" ".h" CONFIGOUTPUT1 "${CONFIGINPUT}")
    STRING (REPLACE ".h.in.cmake" ".h" CONFIGOUTPUT2 "${CONFIGOUTPUT1}")
    CONFIGURE_FILE ("${CONFIGINPUT}" "${CONFIGOUTPUT2}")
ENDFOREACH (CONFIGINPUT ${CONFIGINPUTS})

################################################################################
# Add Build Targets
################################################################################

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

################################################################################
# Add Install Targets
################################################################################

IF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")
    INSTALL(DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}" DESTINATION "include")
ENDIF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")

################################################################################
# Add Documentation Targets
################################################################################

# INCLUDE (DocumentationTargets)

