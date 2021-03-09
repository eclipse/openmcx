# Copyright: 2021 AVL List GmbH

cmake_minimum_required(VERSION 3.10)

include(ExternalProject)


externalproject_add(
    gain-fmu
    SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/gain"
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_LIST_DIR}/../fmus"
)

externalproject_add(
    sinus-generator-fmu
    SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/sinusGenerator"
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_LIST_DIR}/../fmus"
)

externalproject_add(
    vector-sum-fmu
    SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/vectorSum"
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_LIST_DIR}/../fmus"
)
