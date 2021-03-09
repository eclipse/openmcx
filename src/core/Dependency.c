/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "core/Dependency.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct Dependencies {
    size_t numIn;
    size_t numOut;
    Dependency * deps;
} Dependencies;

struct Dependencies * DependenciesCreate(size_t numIn, size_t numOut) {
    Dependencies * A = NULL;
    size_t numElements = numIn * numOut;

    A = (Dependencies *) mcx_calloc(1, sizeof(Dependencies));
    if (NULL == A) {
        mcx_log(LOG_ERROR, "Dependency: Memory allocation for dependencies failed");
        return NULL;
    }

    A->numIn = numIn;
    A->numOut = numOut;

    A->deps = (Dependency *) mcx_calloc(numElements, sizeof(Dependency));
    if (NULL == A->deps) {
        mcx_log(LOG_ERROR, "Dependency: Memory allocation for dependency matrix failed");
        mcx_free(A);
        return NULL;
    }

    memset(A->deps, DEP_INDEPENDENT, sizeof(Dependency) * numElements); // works only for DEP_INDEPENDENT because it is 0

    return A;
}

void DependenciesDestroy(Dependencies * A) {
    if (NULL == A) {
        return;
    }

    if (A->deps) {
        mcx_free(A->deps);
    }

    mcx_free(A);
}

McxStatus SetDependency(Dependencies * A, size_t inIndex, size_t outIndex, Dependency dep) {
    size_t index = 0;
    if (NULL == A) {
        mcx_log(LOG_ERROR, "Dependency: Set dependency: Invalid structure");
        return RETURN_ERROR;
    }
    if (inIndex >= A->numIn) {
        mcx_log(LOG_ERROR, "Dependency: Set dependency: In index %d out of bounds [0, %d]", inIndex, A->numIn - 1);
        return RETURN_ERROR;
    }
    if (outIndex >= A->numOut) {
        mcx_log(LOG_ERROR, "Dependency: Set dependency: Out index %d out of bounds [0, %d]", outIndex, A->numOut - 1);
        return RETURN_ERROR;
    }

    index = (outIndex * A->numIn) + inIndex;

    A->deps[index] = dep;

    return RETURN_OK;
}

McxStatus GetDependency(Dependencies * A, size_t inIndex, size_t outIndex, Dependency *dep) {
    size_t index = 0;
    if (NULL == A) {
        mcx_log(LOG_ERROR, "Dependency: Get dependency: Invalid structure");
        return RETURN_ERROR;
    }
    if (0 == A->numIn) {
        mcx_log(LOG_ERROR, "Dependency: Get dependency: Structure has 0 \"In\"s");
        return RETURN_ERROR;
    }
    if (0 == A->numOut) {
        *dep = DEP_INDEPENDENT;
        return RETURN_OK;
    }
    if (inIndex >= A->numIn) {
        mcx_log(LOG_ERROR, "Dependency: Get dependency: In index %d out of bounds [0, %d]", inIndex, A->numIn - 1);
        return RETURN_ERROR;
    }
    if (outIndex >= A->numOut) {
        mcx_log(LOG_ERROR, "Dependency: Get dependency: Out index %d out of bounds [0, %d]", outIndex, A->numOut - 1);
        return RETURN_ERROR;
    }

    index = (outIndex * A->numIn) + inIndex;

    *dep = A->deps[index];

    return RETURN_OK;
}


Dependency * GetDependencyMatrix(struct Dependencies * A) {
    return A->deps;
}

// Only returns SIZE_T_ERROR if A was NULL
size_t GetDependencyNumIn(struct Dependencies * A) {
    if (!A) {
        mcx_log(LOG_ERROR, "Dependency: Get number of inputs: Invalid structure");
        return SIZE_T_ERROR;
    }

    return A->numIn;
}

// Only returns SIZE_T_ERROR if A was NULL
size_t GetDependencyNumOut(struct Dependencies * A) {
    if (!A) {
        mcx_log(LOG_ERROR, "Dependency: Get number of outputs: Invalid structure");
        return SIZE_T_ERROR;
    }

    return A->numOut;
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */