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

#include "util/time.h"
#include "util/threads.h"
#include <pthread.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


int mcx_thread_create(McxThread * handle, McxThreadStartRoutine start_routine, McxThreadParameter arg)
{
    if (pthread_create(handle, NULL, start_routine, arg)) {
        mcx_log(LOG_ERROR, "Error creating thread");
        return 1;
    }

    return 0;
}

int mcx_thread_terminate(McxThread handle) {
    return pthread_cancel(handle);
}

void mcx_thread_exit(long ret) {
    pthread_exit((void *) ret);
}

int mcx_thread_join(McxThread handle, long * ret) {
    return pthread_join(handle, (void * *) ret);
}

int mcx_thread_join_with_timeout(McxThread handle, long * ret, int secs) {
    struct timespec time;
    int status = 0;

    // Should not fail as all implementations support CLOCK_REALTIME.
    clock_gettime(CLOCK_REALTIME, &time);

    time.tv_sec += secs;

    status = pthread_timedjoin_np(handle, (void * *) ret, &time);
    if (status) {
        const char * cause = NULL;

        if (status == EDEADLK) {
            cause = "Thread would deadlock";
        } else if (status == EINVAL) {
            cause = "Invalid thread";
        } else if (status == ESRCH) {
            cause = "No such thread";
        } else if (status == ETIMEDOUT) {
            cause = "Timeout";
        } else {
            cause = "Unknown error";
        }

        mcx_log(LOG_ERROR, "thread_join_with_timeout: %s", cause);
    }

    return status;
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif // ENABLE_MT