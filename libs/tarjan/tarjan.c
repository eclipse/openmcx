/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "stdio.h"  // for sprintf
#include "tarjan.h"

#ifndef SIZE_T_ERROR
#define SIZE_T_ERROR (size_t)(-1)
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


static void * (* tarjan_malloc)(size_t) = 0;
static void   (* tarjan_free)(void *) = 0;
static void * (* tarjan_realloc)(void *, size_t) = 0;

typedef struct Stack_Def {
    size_t * values;
    size_t max_size;
    size_t stack_top;
} Stack;


static Stack * Stack_init(size_t max_size)
{
    Stack * s = NULL;
    if (max_size < 0)
        goto end0;

    s = (Stack *) tarjan_malloc(sizeof(*s));
    if (!s)
        goto end0;

    s->max_size = max_size;
    s->stack_top = 0;

    s->values = (size_t *) tarjan_malloc(max_size * sizeof(*(s->values)));
    if (!s->values)
        goto end1;

    // success
    return s;

    // failure
end1:
    tarjan_free(s);
end0:
    return 0;
}

// predicate if v is in stack
static int Stack_elem(Stack * s, size_t v)
{
    size_t i = 0;

    for (i = 0; i < s->stack_top; i++) {
        if (s->values[i] == v)
            return 1;
    }

    return 0;
}

static void Stack_push(Stack * s, size_t v)
{
    if (s->stack_top < s->max_size) {
        s->values[s->stack_top] = v;
        s->stack_top = s->stack_top + 1;
    }
}


static size_t Stack_pop(Stack * s)
{
    if (s->stack_top > 0) {
        s->stack_top = s->stack_top - 1;
        return s->values[s->stack_top];
    }
    return SIZE_T_ERROR;
}


static void Stack_cleanup(Stack * s)
{
    tarjan_free(s->values);
    tarjan_free(s);
}


typedef struct {
    int * A; // n times n adjacency matrix
    size_t n;

    size_t index; // current node in algorithm

    size_t* vindex; // index per node
    size_t* vlowlink; // lowlink per node

    Stack * s; // stack of size n

    OrderedNodes * result;
} tarjan_data;


static NodeGroup * tarjan_init_component()
{
    NodeGroup * c = (NodeGroup *)tarjan_malloc(sizeof(*c));
    if (!c)
        goto end0;

    c->nodes.size = 0;
    c->nodes.values = NULL;

    c->isLoop = 0;

    c->cutNodes.size = 0;
    c->cutNodes.values = NULL;

    return c;

end0:
    return 0;
}

int tarjan_add_node(SizeTArray * c, size_t v)
{
    c->size++;
    c->values = (size_t *)tarjan_realloc(c->values, c->size * sizeof(size_t));

    if (!c->values)
        return 0;

    c->values[c->size - 1] = v;

    return 1;
}


static int tarjan_addto_component(NodeGroup * c, size_t v)
{
    return tarjan_add_node(&(c->nodes), v);
}

static int tarjan_addto_result(OrderedNodes * result, NodeGroup * c)
{
    size_t old_size = result->size;
    result->size += 1;
    result->groups = (NodeGroup **)tarjan_realloc(result->groups, result->size * sizeof(*(result->groups)));

    if (!result->groups)
        goto end0;

    result->groups[result->size - 1] = c;

    // success
    return 1;

    // failure
end0:
    return 0;
}


static tarjan_data * tarjan_init(int* A, size_t n)
{
    size_t i;

    tarjan_data * data = 0;

    if (!tarjan_malloc || !tarjan_free || !tarjan_realloc)
        goto end0;

    data = (tarjan_data *) tarjan_malloc(sizeof(*data));
    if (!data)
        goto end0;

    data->A = A;
    data->n = n;
    data->index = 0;

    data->s = Stack_init(n);
    if (!data->s)
        goto end1;

    data->result = (OrderedNodes *) tarjan_malloc(sizeof(*(data->result)));
    if (!data->result)
        goto end2;

    data->result->size = 0;
    data->result->groups = NULL;

    data->vindex = (size_t *) tarjan_malloc(n * sizeof(*(data->vindex)));
    if (!data->vindex)
        goto end3;

    // init as "undefined" (==-1)
    for (i = 0; i < n; i++)
        data->vindex[i] = SIZE_T_ERROR;

    data->vlowlink = (size_t *) tarjan_malloc(n * sizeof(*(data->vlowlink)));
    if(!data->vlowlink)
        goto end4;

    // init as "undefined" (==-1)
    for (i = 0; i < n; i++)
        data->vlowlink[i] = SIZE_T_ERROR;

    // success
    return data;

    // failure
end4:
    tarjan_free(data->vindex);
end3:
    tarjan_free(data->result);
end2:
    Stack_cleanup(data->s);
end1:
    tarjan_free(data);
end0:
    return 0;
}

static int tarjan_connect(tarjan_data * data, size_t v)
{
    size_t w;

    data->vindex[v] = data->index;
    data->vlowlink[v] = data->index;

    data->index = data->index + 1;

    Stack_push(data->s, v);

    // for all successors of v
    for (w = 0; w < data->n; w++) {
        // (v,w) is in the graph
        if (data->A[v * data->n + w]) {
            // vindex undefined
            if (SIZE_T_ERROR == data->vindex[w]) {
                tarjan_connect(data, w);
                data->vlowlink[v] = (data->vlowlink[v] < data->vlowlink[w] ? data->vlowlink[v] : data->vlowlink[w]);
            }
            // w is on stack
            // TODO: this can be done in O(1) with flags instead of O(n) as implemented currently
            else if (Stack_elem(data->s, w)) {
                data->vlowlink[v] = (data->vlowlink[v] < data->vindex[w] ? data->vlowlink[v] : data->vindex[w]);
            }
        }
    }

    if (data->vlowlink[v] == data->vindex[v]) {
        size_t w = SIZE_T_ERROR;

        // make new component
        NodeGroup * c = tarjan_init_component();
        if (!c)
            goto end0;

        do {
            w = Stack_pop(data->s);

            // add to component
            tarjan_addto_component(c, w);

        } while(w != v);

        tarjan_addto_result(data->result, c);

        if (1 == c->nodes.size) {
            size_t idx = c->nodes.values[0];
            if (data->A[idx * data->n + idx]) {
                c->isLoop = 1; // a self-loop
            }
        } else {
            c->isLoop = 1;
        }
    }

    // success
    return 1;

    // failure
end0:
    return 0;
}

static void tarjan_cleanup(tarjan_data* data)
{
    Stack_cleanup(data->s);

    tarjan_free(data->vindex);
    tarjan_free(data->vlowlink);

    tarjan_free(data);
}


int tarjan_init_mem(void * (* malloc)(size_t),
                    void   (* free)(void *),
                    void * (* realloc)(void *, size_t)) {
    if (!malloc) {
        return -1;
    }
    if (!free) {
        return -1;
    }
    if (!realloc) {
        return -1;
    }

    tarjan_malloc  = malloc;
    tarjan_free    = free;
    tarjan_realloc = realloc;

    return 0;
}

/**
 * See wikipedia (https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm) for details
 *
 * A is  the n*n-adjacency matrix of the graph
 **/
OrderedNodes* tarjan(int* A, size_t n)
{
    size_t v;
    OrderedNodes * result = NULL;
    tarjan_data * data = tarjan_init(A, n);

    if (!data)
        goto end0;

    for (v = 0; v < data->n; v++) {
        if (SIZE_T_ERROR == data->vindex[v]) {
            if (!tarjan_connect(data, v)) {
                goto end0;
            }
        }
    }

    result = data->result;

    tarjan_cleanup(data);

    return result;

end0:
    return 0;
}

void tarjan_ordered_nodes_cleanup(OrderedNodes * result)
{
    size_t i = 0;

    if (NULL == result) {
        return;
    }

    for (i = 0; i < result->size; i++) {
        tarjan_free(result->groups[i]->nodes.values);
        if (result->groups[i]->cutNodes.values) {
            tarjan_free(result->groups[i]->cutNodes.values);
        }
        tarjan_free(result->groups[i]);
    }

    tarjan_free(result->groups);
    tarjan_free(result);
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */