/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "reader/Reader.h"

#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static MapStringInt formatExtensions[] = {
    {".ssd", FILE_FORMAT_SSD},
    {NULL, 0}
};

static FileFormat DetermineFileFormat(const char * filePath) {
    size_t filePathLen = strlen(filePath);
    size_t i = 0;

    for (i = 0; formatExtensions[i].key; i++) {
        size_t len = strlen(formatExtensions[i].key);
        if (filePathLen < len) {
            continue;
        }

        if (!strncmp(filePath + filePathLen - len, formatExtensions[i].key, len)) {
            return (FileFormat)formatExtensions[i].value;
        }
    }

    return FILE_FORMAT_UNKNOWN;
}

static McxStatus ReaderSetup(Reader * reader, const char * modelFile, Config * config) {
    McxStatus retVal = RETURN_OK;
    FileFormat format = FILE_FORMAT_UNKNOWN;

    // check that ReaderSetup was not called before
    if (reader->reader_initialised_) {
        mcx_log(LOG_ERROR, "Input file reader is already set up");
        return RETURN_ERROR;
    }

    // setup
    format = DetermineFileFormat(modelFile);
    switch (format) {
        case FILE_FORMAT_SSD:
            retVal = SSDReaderInit(modelFile);
            break;
        default:
            mcx_log(LOG_ERROR, "Unknown input file format");
            retVal = RETURN_ERROR;
            break;
    }

    if (retVal == RETURN_OK) {
        reader->format_ = format;
        reader->reader_initialised_ = TRUE;
    }

    return retVal;
}

static void ReaderCleanup(Reader * reader) {
    if (!reader->reader_initialised_) {
        mcx_log(LOG_WARNING, "Trying to clean up an uninitialised reader");
        return;
    }

    switch (reader->format_) {
        case FILE_FORMAT_SSD:
            SSDReaderCleanup();
            break;
        default:
            mcx_log(LOG_ERROR, "Unknown input file format");
            break;
    }

    reader->format_ = FILE_FORMAT_UNKNOWN;
    reader->reader_initialised_ = FALSE;
}

static InputRoot * ReadMcxExe(Reader * reader, const char * file) {
    if (!reader->reader_initialised_) {
        mcx_log(LOG_ERROR, "Input file reader not initialised");
        return NULL;
    }

    switch (reader->format_) {
        case FILE_FORMAT_SSD:
            return SSDReadMcx(file, reader->GetSSDComponents_(reader));
        default:
            mcx_log(LOG_ERROR, "Unknown input file format");
            return NULL;
    }
}

static SSDComponentSpecificDataDefinition ** ReaderGetSSDComponents(Reader * reader) {
    return ssdMcxExeComponents;
}

static void ReaderDestructor(Reader * reader) {
}

static Reader * ReaderCreate(Reader * reader) {
    reader->reader_initialised_ = FALSE;
    reader->format_ = FILE_FORMAT_UNKNOWN;

    reader->Setup = ReaderSetup;
    reader->Cleanup = ReaderCleanup;
    reader->Read = ReadMcxExe;

    reader->GetSSDComponents_ = ReaderGetSSDComponents;

    return reader;
}

OBJECT_CLASS(Reader, Object);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */