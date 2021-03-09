cmake_minimum_required(VERSION 3.5)

project(scope_guard VERSION 1.0.0 LANGUAGES CXX)

add_library(scope_guard INTERFACE)

target_sources(scope_guard INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/scope_guard.hpp)
target_include_directories(scope_guard INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
