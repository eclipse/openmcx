################################################################################
# Copyright (c) 2020 AVL List GmbH and others
# 
# This program and the accompanying materials are made available under the
# terms of the Apache Software License 2.0 which is available at
# https://www.apache.org/licenses/LICENSE-2.0.
# 
# SPDX-License-Identifier: Apache-2.0
################################################################################

########################################################################
# This module takes the following files:                               #
#  - version.c.in                                                      #
#  - version.h.in,                                                     #
# replaces certain variables and copies the files (without the `in`    #
# suffix) into the cmake binary directory.                             #
#                                                                      #
# An object library `version` will be created based on the copied      #
# files.                                                               #
#                                                                      #
# The following variables are supported:                               #
#  - MCX_GIT_ID_STR                                                    #
########################################################################

find_package(Git)

function(get_short_git_hash WORK_DIR RESULT_NAME)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        OUTPUT_VARIABLE SHORT_GIT_ID
        OUTPUT_STRIP_TRAILING_WHITESPACE
        WORKING_DIRECTORY ${WORK_DIR})
    set(${RESULT_NAME}
        ${SHORT_GIT_ID}
        PARENT_SCOPE)
endfunction()

get_short_git_hash(${CMAKE_CURRENT_SOURCE_DIR} MCX_GIT_ID)
set(MCX_GIT_ID_STR ${MCX_GIT_ID})


configure_file("${PROJECT_SOURCE_DIR}/src/version.c.in" "${CMAKE_CURRENT_BINARY_DIR}/version/version.c")
configure_file("${PROJECT_SOURCE_DIR}/src/version.h.in" "${CMAKE_CURRENT_BINARY_DIR}/version/version.h")

add_library(version OBJECT "${CMAKE_CURRENT_BINARY_DIR}/version/version.c"
                           "${CMAKE_CURRENT_BINARY_DIR}/version/version.h")

target_include_directories(
    version
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src"
    PUBLIC
        "${CMAKE_CURRENT_BINARY_DIR}/version")

target_link_libraries(version PRIVATE common)

set_target_properties(version PROPERTIES FOLDER libs)

if (WIN32)
    target_compile_definitions(version PUBLIC OS_WINDOWS)
else ()
    target_compile_definitions(version PUBLIC OS_LINUX)
endif()
