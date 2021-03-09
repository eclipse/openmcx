/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_COMMON_LOGGING_H
#define MCX_COMMON_LOGGING_H

#include <stdarg.h>

#include "status.h"


#define MCX_DEBUG_LOG_TIME 0.2

#ifdef MCX_DEBUG
#ifdef OS_WINDOWS
#define MCX_DEBUG_LOG(format, ...) do {                \
        mcx_log(LOG_DEBUG, format, __VA_ARGS__);        \
    } while(0)
#else /* not OS_WINDOWS */
#define MCX_DEBUG_LOG(format, ...) do {                  \
        mcx_log(LOG_DEBUG, format, ##__VA_ARGS__);        \
    } while(0)
#endif /* OS_WINDOWS */
#else
#define MCX_DEBUG_LOG(format, ...)
#endif //MCX_DEBUG


typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
} LogSeverity;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern McxStatus mcx_vlog(LogSeverity sev, const char * fmt, va_list args);
extern McxStatus mcx_vlog_no_newline(LogSeverity sev, const char * fmt, va_list args);
extern McxStatus mcx_log(LogSeverity sev, const char * fmt, ...);
extern McxStatus mcx_log_no_newline(LogSeverity sev, const char * fmt, ...);
#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */


#endif // !MCX_COMMON_LOGGING_H