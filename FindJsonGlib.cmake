# - Try to find JSONGLIB
# Once done this will define
#
#  JSONGLIB_FOUND - system has JSONGLIB
#  JSONGLIB_INCLUDE_DIR - the JSONGLIB include directory
#  JSONGLIB_LIBRARIES - Link these to use JSONGLIB
#  GTHREAD2_LIBRARIES - Link these to use gthread2
#  JSONGLIB_DEFINITIONS - Compiler switches required for using JSONGLIB
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

# Copyright (c) 2010, Ni Hui <shuizhuyuanluo@126.com>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

if(JSONGLIB_INCLUDE_DIR AND JSONGLIB_LIBRARIES)
    # in cache already
    set(JSONGLIB_FOUND_QUIETLY TRUE)
endif(JSONGLIB_INCLUDE_DIR AND JSONGLIB_LIBRARIES)

if(NOT WIN32)
    find_package(PkgConfig)
    pkg_check_modules(PKG_JSONGLIB json-glib-1.0)
    set(JSONGLIB_DEFINITIONS ${PKG_JSONGLIB_CFLAGS})
endif(NOT WIN32)

find_path(JSONGLIB_MAIN_INCLUDE_DIR NAMES json-glib.h
        PATHS
        ${PKG_JSONGLIB_INCLUDE_DIRS}
        PATH_SUFFIXES json-glib-1.0
        )

find_library(JSONGLIB_LIBRARIES NAMES json-glib-1.0
        PATHS
        ${PKG_JSONGLIB_LIBRARY_DIRS}
        )

set(JSONGLIB_INCLUDE_DIR ${JSONGLIB_MAIN_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JSONGLIB DEFAULT_MSG JSONGLIB_INCLUDE_DIR JSONGLIB_LIBRARIES GTHREAD2_LIBRARIES JSONGLIB_MAIN_INCLUDE_DIR)

mark_as_advanced(JSONGLIB_INCLUDE_DIR JSONGLIB_LIBRARIES GTHREAD2_LIBRARIES JSONGLIB_MAIN_INCLUDE_DIR)