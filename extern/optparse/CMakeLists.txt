cmake_minimum_required(VERSION 3.5)

project(optparse VERSION 1.0.0 LANGUAGES C)

add_library(optparse STATIC optparse.c optparse.h)

target_include_directories(optparse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(optparse PROPERTIES FOLDER libs)
