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

#if defined (ENABLE_MT)
#include "util/events.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


// implementation of windows CreateEvent (auto reset) SetEvent and WaitForSingleObject (INFINITE)
int mcx_event_create(McxEvent * evnt)
{
    // create an event that automatically resets after signaling
    *evnt = CreateEvent(NULL, 0, 0, NULL);
    if (!*evnt) {
        mcx_log(LOG_ERROR, "Error creating event");
        return 1;
    }

    return 0;
}

void mcx_event_destroy(McxEvent * evnt) {
    CloseHandle(*evnt);
}


int mcx_event_set(McxEvent *evnt)
{
    if ( !SetEvent(*evnt) ) {
        mcx_log(LOG_ERROR, "Error signalling event");
        return 1;
    }

    return 0;
}


int mcx_event_wait_with_timeout(McxEvent *evnt, unsigned int msTimeout)
{
    return WaitForSingleObject( *evnt, msTimeout );
}

int mcx_event_wait(McxEvent *evnt)
{
    WaitForSingleObject( *evnt, INFINITE );

    return 0;
}


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif // ENABLE_MT