/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_UTIL_EVENTS_H
#define MCX_UTIL_EVENTS_H

#include "../CentralParts.h"

#if defined (ENABLE_MT)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(OS_WINDOWS)
#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include <windows.h>

//event
#define McxEvent          HANDLE

#elif defined(OS_LINUX)

//event
typedef struct McxEvent {
    int signalled;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} McxEvent;

#define WAIT_TIMEOUT        258L    // dderror
#define WAIT_FAILED         ((short)0xFFFFFFFF)
#define STATUS_WAIT_0       ((short)0x00000000L)
#define WAIT_OBJECT_0       ((STATUS_WAIT_0) + 0 )

#endif // OS_WINDOWS

int mcx_event_create(McxEvent *);
void mcx_event_destroy(McxEvent *);
int mcx_event_set(McxEvent *);
int mcx_event_wait(McxEvent *);
int mcx_event_wait_with_timeout(McxEvent * evnt, unsigned int msTimeout);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif // ENABLE_MT

#endif // MCX_UTIL_EVENTS_H