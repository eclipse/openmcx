/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_UNITS_UNITS_H
#define MCX_UNITS_UNITS_H

#include "CentralParts.h"

/**
 * This is the structure object describing the SI definition of an unit.
 * It should be used in combination with @a mcx_units_get_si_def.
 */
typedef struct si_def {
    int kg;
    int m;
    int s;
    int A;
    int K;
    int mol;
    int cd;
    int rad;

    double factor;
    double offset;
} si_def;

/**
 * si_def_map_element holds SI unit names together with their SI unit
 * definition.
 */
typedef struct si_def_map_element {
    const char * name;
    si_def si_definition;
} si_def_map_element;

int mcx_units_read_si_def_from_file(const char * filename);

/**
 * @param name A string representing the name of a unit.
 * @param si_unit_def The valid SI definition to add to the overall
 * list of units.
 *
 * @return 0 success
           1 failure
 */

int mcx_units_add_si_def(const char * name, si_def * si_unit_def);

/**
 * @param id A string representing the name of a unit.
 * @param si_def_container Output structure which will be filled up with the
 *        SI definition if a valid unit id string is provided.
 *
 * @return 0 if @a id is a valid unit identifier,
           1 if @a id is not a valid unit identifier,
           2 if @a id is a valid unit identifier but the unit is an empirical one.
 */
int mcx_units_get_si_def(const char * id, si_def * si_def_container);

#endif /* MCX_UNITS_UNITS_H */