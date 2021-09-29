/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "CentralParts.h"
#include "units/Units.h"
#include "util/os.h"
#include "util/string.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

static size_t si_def_map_alloc = 0;
static size_t si_def_map_num = 0;
static si_def_map_element * si_def_map = NULL;

// units_strtod is a variant of strtod that only skips over whitespace
// in the same line
static double units_strtod(const char *nptr, char **endptr) {
    const char * start = nptr;
    char * end;
    double d;

    while (*nptr == ' ' || *nptr == '\t') { ++nptr; }

    d = strtod(nptr, &end);

    // if strtod didn't read anything, units_strtod also rewinds
    if (end == nptr) { end = (char *)start; }

    if (endptr) { *endptr = end; }

    return d;
}

// units_strtoi is the integer variant of units_strtod
static int units_strtoi(const char *nptr, char **endptr) {
    const char * start = nptr;
    char * end;
    int i;

    while (*nptr == ' ' || *nptr == '\t') { ++nptr; }

    i = atoi(nptr);

    end = (char *) nptr;
    if (*end == '+' || *end == '-') { ++end; }
    while (*end >= '0' && *end <= '9') { ++end; }

    if (end == nptr) {
        // no digits
        end = (char *) start;
    }

    if (endptr) { *endptr = end; }

    return i;
}


int mcx_units_read_si_def_from_file(const char * filename) {
    size_t length = 0;
    char * unit = ""; // used for error reporting
    char * content = NULL;
    char * pos = NULL;

    FILE * file = NULL;

    if (si_def_map) {
        mcx_log(LOG_ERROR, "Units already setup");
        return 1;
    }

    file = mcx_os_fopen(filename, "rb");
    if (!file) {
        mcx_log(LOG_ERROR, "Could not open units file: %s", filename);
        return 1;
    }

    mcx_log(LOG_DEBUG, "Reading units from file: %s", filename);

    // read file
    if (fseek(file, 0, SEEK_END)) {
        mcx_log(LOG_ERROR, "Could not seek units file: %s", filename);
        return 1;
    };
    length = ftell(file);
    if (fseek(file, 0, SEEK_SET)) {
        mcx_log(LOG_ERROR, "Could not seek units file: %s", filename);
        return 1;
    };

    if (!(content = mcx_malloc(length + 1))) { return 1; }
    if (fread(content, 1, length, file) != length) {
        mcx_log(LOG_ERROR, "Could not read units file: %s", filename);
        return 1;
    }
    mcx_os_fclose(file);

    content[length] = '\0';

    pos = content;

    si_def_map_alloc = 16;
    si_def_map = mcx_malloc(si_def_map_alloc * sizeof(si_def_map_element));
    if (!si_def_map) { return 1; }

    while (*pos) {
        si_def_map_element * element;
        char * next;

        if (si_def_map_num == si_def_map_alloc - 1) {
            si_def_map_alloc *= 2;
            si_def_map = mcx_realloc(si_def_map, si_def_map_alloc * sizeof(si_def_map_element));
        }

        element = &si_def_map[si_def_map_num];

        char * line = pos;
        char * name = line;
        while (*pos != ',') { ++pos; }
        *pos = '\0';
        if(!(element->name = mcx_string_copy(name))) {
            *pos = ',';
            unit = "name";
            goto parse_error;
        }
        *pos = ',';
        ++pos;


        element->si_definition.kg = units_strtoi(pos, &next);
        if (next == pos || *next != ',') {
            unit = "kg";
            goto parse_error;
        }
        pos = next + 1;

        element->si_definition.m = units_strtoi(pos, &next);
        if (next == pos || *next != ',') {
            unit = "m";
            goto parse_error;
        }
        pos = next + 1;

        element->si_definition.s = units_strtoi(pos, &next);
        if (next == pos || *next != ',') {
            unit = "s";
            goto parse_error;
        }
        pos = next + 1;

        element->si_definition.A = units_strtoi(pos, &next);
        if (next == pos || *next != ',') {
            unit = "A";
            goto parse_error;
        }
        pos = next + 1;

        element->si_definition.K = units_strtoi(pos, &next);
        if (next == pos || *next != ',') {
            unit = "K";
            goto parse_error;
        }
        pos = next + 1;

        element->si_definition.mol = units_strtoi(pos, &next);
        if (next == pos || *next != ',') {
            unit = "mol";
            goto parse_error;
        }
        pos = next + 1;

        element->si_definition.cd = units_strtoi(pos, &next);
        if (next == pos || *next != ',') {
            unit = "cd";
            goto parse_error;
        }
        pos = next + 1;

        element->si_definition.rad = units_strtoi(pos, &next);
        if (next == pos || *next != ',') {
            unit = "rad";
            goto parse_error;
        }
        pos = next + 1;


        element->si_definition.factor = units_strtod(pos, &next);
        if (next == pos || *next != ',') {
            unit = "factor";
            goto parse_error;
        }
        pos = next + 1;

        element->si_definition.offset = units_strtod(pos, &next);
        if (next == pos) {
            unit = "offset";
            goto parse_error;
        }
        pos = next;


        if (*pos == '\r') { ++pos; }
        if (*pos != '\n') { return 1; } else { ++pos; }

        MCX_DEBUG_LOG(
                  "Read unit %s: (%d,%d,%d,%d,%d,%d,%d,%d,%.20f,%.20f)"
                , element->name
                , element->si_definition.kg
                , element->si_definition.m
                , element->si_definition.s
                , element->si_definition.A
                , element->si_definition.K
                , element->si_definition.mol
                , element->si_definition.cd
                , element->si_definition.rad
                , element->si_definition.factor
                , element->si_definition.offset
            );

        if (element->si_definition.factor == 0.0) {
            goto value_error;
        }

        si_def_map_num += 1;

        // Skip empty lines
        while (*pos == '\n' || *pos == '\r') {
            if (*pos == '\r') { ++pos; }
            if (*pos != '\n') { return 1; } else { ++pos; }
        }

        continue;

    parse_error: {
            // replace the newline with a '\0' to only print the
            // current line
            char * end = line;
            while (*end != '\r' && *end != '\n' && *end != '\0') { ++end; }
            *end = '\0';

            mcx_log(LOG_ERROR, "Could not parse %s in line: '%s'", unit, line);
            mcx_free(content);
            mcx_free(si_def_map);
            si_def_map = NULL;
            return 1;
        }
    value_error: {
            // replace the newline with a '\0' to only print the
            // current line
            char * end = line;
            while (*end != '\r' && *end != '\n' && *end != '\0') { ++end; }
            *end = '\0';

            mcx_log(LOG_ERROR, "Unit factor is 0.0 in line: '%s'", line);
            mcx_free(content);
            mcx_free(si_def_map);
            si_def_map = NULL;
            return 1;
        }
    }

    mcx_free(content);

    return 0;
}

static si_def_map_element * si_def_map_get(si_def_map_element * si_def_map, const char * name) {
    size_t i = 0;

    if (!si_def_map) {
        return NULL;
    }

    for (i = 0; i < si_def_map_num; i++) {
        if (!strcmp(si_def_map[i].name, name)) {
            return &si_def_map[i];
        }
    }

    return NULL;
}

int mcx_units_get_si_def(const char * name, si_def * si_unit_def) {
    si_def_map_element * element = si_def_map_get(si_def_map, name);
    if (element) {
        *si_unit_def = element->si_definition;
        return 0;
    } else {
        return 1;
    }
}

int mcx_units_add_si_def(const char * name, si_def * si_unit_def) {
    si_def_map_element * element = NULL;

    if (!name) {
        return 1;
    }

    element = si_def_map_get(si_def_map, name);

    if (element) {
        return 1;
    }

    if (si_def_map_alloc == 0) {
        si_def_map_alloc = 16;
        si_def_map = mcx_realloc(si_def_map, si_def_map_alloc * sizeof(si_def_map_element));
    } else if (si_def_map_num == si_def_map_alloc - 1) {
        si_def_map_alloc *= 2;
        si_def_map = mcx_realloc(si_def_map, si_def_map_alloc * sizeof(si_def_map_element));
    }

    element = &si_def_map[si_def_map_num];

    element->name = mcx_string_copy(name);
    if (!element->name) {
        return 1;
    }

    element->si_definition.kg  = si_unit_def->kg;
    element->si_definition.m   = si_unit_def->m;
    element->si_definition.s   = si_unit_def->s;
    element->si_definition.A   = si_unit_def->A;
    element->si_definition.K   = si_unit_def->K;
    element->si_definition.mol = si_unit_def->mol;
    element->si_definition.cd  = si_unit_def->cd;
    element->si_definition.rad = si_unit_def->rad;

    element->si_definition.factor = si_unit_def->factor;
    element->si_definition.offset = si_unit_def->offset;

    ++si_def_map_num;

    MCX_DEBUG_LOG(
        "Adding unit %s: (%d,%d,%d,%d,%d,%d,%d,%d,%.20f,%.20f)"
        , element->name
        , element->si_definition.kg
        , element->si_definition.m
        , element->si_definition.s
        , element->si_definition.A
        , element->si_definition.K
        , element->si_definition.mol
        , element->si_definition.cd
        , element->si_definition.rad
        , element->si_definition.factor
        , element->si_definition.offset
        );

    return 0;
}

#ifdef __cplusplus
}
#endif // __cplusplus