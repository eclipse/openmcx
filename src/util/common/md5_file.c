/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include <string.h>

#include "common/memory.h"

#include "util/md5.h"
#include "util/md5_file.h"
#include "util/os.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

char * mcx_md5_file_fingerprint(const char * path)
{
    MD5_CTX context;
    char * md5String = NULL;
    FILE * file = mcx_os_fopen(path, "rb");

    if (NULL != file) {
        unsigned long len = 0;
        unsigned char buffer[1024], digest[16];
        size_t i = 0, pos = 0;

        mcx_md5_init(&context);
        while ((len = (unsigned long) fread(buffer, 1, 1024, file))) {
            mcx_md5_update(&context, buffer, len);
        }
        mcx_md5_final(digest, &context);
        mcx_os_fclose(file);

        md5String = (char *) mcx_calloc(16*2 + 1, sizeof(char));
        for (i = 0; i < 16; i++) {
            snprintf(md5String + pos, 16*2 + 1 - pos, "%02x", digest[i]);
            pos = strlen(md5String);
        }
    }

    return md5String;
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */