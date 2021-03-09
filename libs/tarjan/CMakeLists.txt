################################################################################
# Copyright (c) 2020 AVL List GmbH and others
# 
# This program and the accompanying materials are made available under the
# terms of the Apache Software License 2.0 which is available at
# https://www.apache.org/licenses/LICENSE-2.0.
# 
# SPDX-License-Identifier: Apache-2.0
################################################################################

cmake_minimum_required(VERSION 3.5)

project(libtarjan VERSION 1.0.0 LANGUAGES C)

option(INSTALL_TARJAN "Toggle to install tarjan" OFF)

add_library(tarjan STATIC tarjan.c tarjan.h)

target_include_directories(
    tarjan
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(tarjan PROPERTIES FOLDER libs)

if(INSTALL_TARJAN)
    install(
        TARGETS tarjan
        EXPORT tarjan-export
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include
    )
endif()
