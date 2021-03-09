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

#include "core/channels/ChannelInfo.h"

#include "util/string.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ----------------------------------------------------------------------
// ChannelInfo

static const char * ChannelInfoGetLogName(const ChannelInfo * info) {
    if (info->id) {
        return info->id;
    } else {
        return info->name;
    }
}

static ChannelType ChannelInfoType(const ChannelInfo * info) {
    return info->type;
}

static ChannelMode ChannelInfoMode(const ChannelInfo * info) {
    return info->mode;
}

static const char * ChannelInfoName(const ChannelInfo * info) {
    if (info->name) {
        return info->name;
    } else {
        return "";
    }
}

static const char * ChannelInfoNameInTool(const ChannelInfo * info) {
    return info->nameInTool;
}

static const char * ChannelInfoDescription(const ChannelInfo * info) {
    return info->description;
}

static const char * ChannelInfoID(const ChannelInfo * info) {
    return info->id;
}

static const char * ChannelInfoUnit(const ChannelInfo * info) {
    return info->unitString;
}

static ChannelValue * ChannelGetMin(const ChannelInfo * info) {
    return info->min;
}

static ChannelValue * ChannelGetMax(const ChannelInfo * info) {
    return info->max;
}

static ChannelValue * ChannelInfoGetInitialValue(const ChannelInfo * info) {
    return info->initialValue;
}

static ChannelValue * ChannelInfoScale(const ChannelInfo * info) {
    return info->scale;
}

static ChannelValue * ChannelInfoOffset(const ChannelInfo * info) {
    return info->offset;
}

static ChannelValue * ChannelInfoDefault(const ChannelInfo * info) {
    return info->defaultValue;
}

static int ChannelInfoIsBinary(const ChannelInfo * info) {
    return info->type == CHANNEL_BINARY
        || info->type == CHANNEL_BINARY_REFERENCE;
}

static int ChannelInfoGetWriteResultFlag(const ChannelInfo * info) {
    return info->writeResult;
}


static McxStatus ChannelInfoSetString(char * * dst, const char * src) {
    if (*dst) {
        mcx_free(*dst);
    }

    *dst = mcx_string_copy(src);

    if (src && !*dst) {
        mcx_log(LOG_DEBUG, "ChannelInfoSetString: Could not copy string \"%s\"", src);
        return RETURN_ERROR;
    }

    return RETURN_OK;
}

static McxStatus ChannelInfoSetVector(ChannelInfo * info, VectorChannelInfo * vector) {
    if (info->vector) {
        object_destroy(info->vector);
    }

    info->vector = vector;

    return RETURN_OK;
}

static McxStatus ChannelInfoSetName(ChannelInfo * info, const char * name) {
    return ChannelInfoSetString(&info->name, name);
}

static McxStatus ChannelInfoSetNameInTool(ChannelInfo * info, const char * name) {
    return ChannelInfoSetString(&info->nameInTool, name);
}

static McxStatus ChannelInfoSetID(ChannelInfo * info, const char * name) {
    return ChannelInfoSetString(&info->id, name);
}

static McxStatus ChannelInfoSetDescription(ChannelInfo * info, const char * name) {
    return ChannelInfoSetString(&info->description, name);
}

static McxStatus ChannelInfoSetUnit(ChannelInfo * info, const char * name) {
    return ChannelInfoSetString(&info->unitString, name);
}

static McxStatus ChannelInfoSetType(ChannelInfo * info, ChannelType type) {
    if (info->type != CHANNEL_UNKNOWN) {
        mcx_log(LOG_ERROR, "Port %s: Type already set", info->GetLogName(info));
        return RETURN_ERROR;
    }

    info->type = type;

    if (info->IsBinary(info)) {
        // the default for binary is off
        info->SetWriteResult(info, FALSE);
    }

    return RETURN_OK;
}

static McxStatus ChannelInfoSetMode(ChannelInfo * info, ChannelMode mode) {
    info->mode = mode;

    return RETURN_OK;
}

static McxStatus ChannelInfoSetMin(ChannelInfo * info, ChannelValue * min) {
    info->min = min;
    return RETURN_OK;
}

static McxStatus ChannelInfoSetMax(ChannelInfo * info, ChannelValue * max) {
    info->max = max;
    return RETURN_OK;
}

static McxStatus ChannelInfoSetScale(ChannelInfo * info, ChannelValue * scale) {
    info->scale = scale;
    return RETURN_OK;
}

static McxStatus ChannelInfoSetOffset(ChannelInfo * info, ChannelValue * offset) {
    info->offset = offset;
    return RETURN_OK;
}

static McxStatus ChannelInfoSetDefault(ChannelInfo * info, ChannelValue * defaultValue) {
    info->defaultValue = defaultValue;
    return RETURN_OK;
}

static McxStatus ChannelInfoSetInitial(ChannelInfo * info, ChannelValue * initialValue) {
    info->initialValue = initialValue;
    return RETURN_OK;
}

static McxStatus ChannelInfoSetWriteResult(ChannelInfo * info, int writeResult) {
    info->writeResult = writeResult;
    return RETURN_OK;
}


static void ChannelInfoSet(
    ChannelInfo *       info,
    VectorChannelInfo * vector,
    char *              name,
    char *              nameInTool,
    char *              description,
    char *              unit,
    ChannelType         type,
    ChannelMode         mode,
    char *              id,
    ChannelValue *      min,
    ChannelValue *      max,
    ChannelValue *      scale,
    ChannelValue *      offset,
    ChannelValue *      defaultValue,
    ChannelValue *      initialValue,
    int                 writeResult)
{
    info->vector       = vector;
    info->name         = name;
    info->nameInTool   = nameInTool;
    info->description  = description;
    info->unitString   = unit;
    info->type         = type;
    info->mode         = mode;
    info->id           = id;
    info->min          = min;
    info->max          = max;
    info->scale        = scale;
    info->offset       = offset;
    info->defaultValue = defaultValue;
    info->initialValue = initialValue;
    info->writeResult  = writeResult;
}

static void ChannelInfoGet(
    const ChannelInfo *  info,
    VectorChannelInfo ** vector,
    char **              name,
    char **              nameInTool,
    char **              description,
    char **              unit,
    ChannelType *        type,
    ChannelMode *        mode,
    char **              id,
    ChannelValue **      min,
    ChannelValue **      max,
    ChannelValue **      scale,
    ChannelValue **      offset,
    ChannelValue **      defaultValue,
    ChannelValue **      initialValue,
    int *                writeResult)
{
    * vector       = info->vector;
    * name         = info->name;
    * nameInTool   = info->nameInTool;
    * description  = info->description;
    * unit         = info->unitString;
    * type         = info->type;
    * mode         = info->mode;
    * id           = info->id;
    * min          = info->min;
    * max          = info->max;
    * scale        = info->scale;
    * offset       = info->offset;
    * defaultValue = info->defaultValue;
    * initialValue = info->initialValue;
    * writeResult  = info->writeResult;
}

static ChannelInfo * ChannelInfoClone(const ChannelInfo * info) {
    ChannelInfo * clone = (ChannelInfo *) object_create(ChannelInfo);

    if (!clone) {
        return NULL;
    }

    if (info->name        && !(clone->name        = mcx_string_copy(info->name)))        { return NULL; }
    if (info->nameInTool  && !(clone->nameInTool  = mcx_string_copy(info->nameInTool)))  { return NULL; }
    if (info->description && !(clone->description = mcx_string_copy(info->description))) { return NULL; }
    if (info->unitString  && !(clone->unitString  = mcx_string_copy(info->unitString)))  { return NULL; }
    if (info->id          && !(clone->id          = mcx_string_copy(info->id)))          { return NULL; }

    clone->type = info->type;
    clone->mode = info->mode;

    if (info->min) {
        if (!(clone->min = ChannelValueClone(info->min))) { return NULL; }
    }
    if (info->max) {
        if (!(clone->max = ChannelValueClone(info->max))) { return NULL; }
    }
    if (info->scale) {
        if (!(clone->scale = ChannelValueClone(info->scale))) { return NULL; }
    }
    if (info->offset) {
        if (!(clone->offset = ChannelValueClone(info->offset))) { return NULL; }
    }
    if (info->defaultValue) {
        if (!(clone->defaultValue = ChannelValueClone(info->defaultValue))) { return NULL; }
    }
    if (info->initialValue) {
        if (!(clone->initialValue = ChannelValueClone(info->initialValue))) { return NULL; }
    }

    clone->writeResult = info->writeResult;

    return clone;
}

static ChannelInfo * ChannelInfoCopy(
    const ChannelInfo * info,
    char        * name,
    char        * nameInTool,
    char        * id) {

    ChannelInfo * copy = info->Clone(info);

    if (!copy) {
        return NULL;
    }

    copy->SetName(copy, name);
    copy->SetNameInTool(copy, nameInTool);
    copy->SetID(copy, id);

    return copy;
}

static McxStatus ChannelInfoInit(ChannelInfo * info,
                                const char * name,
                                const char * descr,
                                const char * unit,
                                ChannelType  type,
                                const char * id) {


    if (name  && RETURN_OK != info->SetName(info, name)) {
        mcx_log(LOG_DEBUG, "Port %s: Could not set name", name);
        return RETURN_ERROR;
    }
    if (descr && RETURN_OK != info->SetDescription(info, descr)) {
        mcx_log(LOG_DEBUG, "Port %s: Could not set description", name);
        return RETURN_ERROR;
    }
    if (unit  && RETURN_OK != info->SetUnit(info, unit)) {
        mcx_log(LOG_DEBUG, "Port %s: Could not set unit", name);
        return RETURN_ERROR;
    }
    if (id    && RETURN_OK != info->SetID(info, id)) {
        mcx_log(LOG_DEBUG, "Port %s: Could not set ID", name);
        return RETURN_ERROR;
    }
    if (RETURN_OK != info->SetType(info, type)) {
        mcx_log(LOG_DEBUG, "Port %s: Could not set type", name);
        return RETURN_ERROR;
    }

    return RETURN_OK;
}


static void FreeStr(char ** str) {
    if (*str) {
        mcx_free(*str);
        *str = NULL;
    }
}

static void ChannelInfoDestructor(ChannelInfo * info) {
    FreeStr(&info->name);
    FreeStr(&info->nameInTool);
    FreeStr(&info->description);
    FreeStr(&info->unitString);
    FreeStr(&info->id);

    if (info->defaultValue) {
        ChannelValueDestructor(info->defaultValue);
        mcx_free(info->defaultValue);
        info->defaultValue = NULL;
    }
    if (info->initialValue) {
        ChannelValueDestructor(info->initialValue);
        mcx_free(info->initialValue);
        info->initialValue = NULL;
    }
    if (info->vector) {
        object_destroy(info->vector);
    }
}

static ChannelInfo * ChannelInfoCreate(ChannelInfo * info) {
    info->Set  = ChannelInfoSet;
    info->Get  = ChannelInfoGet;
    info->Clone = ChannelInfoClone;
    info->Copy = ChannelInfoCopy;

    info->Init = ChannelInfoInit;

    info->SetVector = ChannelInfoSetVector;
    info->SetName = ChannelInfoSetName;
    info->SetNameInTool = ChannelInfoSetNameInTool;
    info->SetID = ChannelInfoSetID;
    info->SetDescription = ChannelInfoSetDescription;
    info->SetUnit = ChannelInfoSetUnit;
    info->SetType = ChannelInfoSetType;
    info->SetMode = ChannelInfoSetMode;

    info->SetMin = ChannelInfoSetMin;
    info->SetMax = ChannelInfoSetMax;
    info->SetScale = ChannelInfoSetScale;
    info->SetOffset = ChannelInfoSetOffset;
    info->SetDefault = ChannelInfoSetDefault;
    info->SetInitial = ChannelInfoSetInitial;
    info->SetWriteResult = ChannelInfoSetWriteResult;

    info->GetType = ChannelInfoType;
    info->GetMode = ChannelInfoMode;
    info->GetName = ChannelInfoName;
    info->GetNameInTool = ChannelInfoNameInTool;
    info->GetDescription = ChannelInfoDescription;
    info->GetID = ChannelInfoID;
    info->GetUnit = ChannelInfoUnit;
    info->GetMin = ChannelGetMin;
    info->GetMax = ChannelGetMax;

    info->GetInitialValue = ChannelInfoGetInitialValue;

    info->GetScale = ChannelInfoScale;
    info->GetOffset = ChannelInfoOffset;
    info->GetDefault = ChannelInfoDefault;

    info->IsBinary = ChannelInfoIsBinary;

    info->GetWriteResultFlag = ChannelInfoGetWriteResultFlag;

    info->GetLogName = ChannelInfoGetLogName;

    info->vector = NULL;

    info->name        = NULL;
    info->nameInTool  = NULL;
    info->description = NULL;
    info->unitString  = NULL;
    info->id          = NULL;
    info->min         = NULL;
    info->max         = NULL;

    info->writeResult = TRUE;

    info->connected = FALSE;

    info->scale = NULL;
    info->offset = NULL;

    info->type = CHANNEL_UNKNOWN;
    info->defaultValue = NULL;
    info->initialValue = NULL;

    info->initialValueIsExact = FALSE;

    info->channel = NULL;

    return info;
}

OBJECT_CLASS(ChannelInfo, Object);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */