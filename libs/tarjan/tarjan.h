/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef TARJAN_H
#define TARJAN_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int tarjan_init_mem(void * (* malloc)(size_t),
                    void   (* free)(void *),
                    void * (* realloc)(void *, size_t));

typedef struct {
    size_t size;
    size_t * values;
} SizeTArray;

typedef struct {
    SizeTArray nodes;

    int isLoop;

    SizeTArray cutNodes;
} NodeGroup;

typedef struct {
    size_t size; // number of components
    NodeGroup ** groups;
} OrderedNodes;

OrderedNodes * tarjan(int * A, size_t n);

void tarjan_ordered_nodes_cleanup(OrderedNodes * result);

int tarjan_add_node(SizeTArray * c, size_t v);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif /* TARJAN_H */