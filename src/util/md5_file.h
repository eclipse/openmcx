/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_UTIL_MD5_FILE_H
#define MCX_UTIL_MD5_FILE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

char * mcx_md5_file_fingerprint(const char * path);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif // MCX_UTIL_MD5_FILE_H