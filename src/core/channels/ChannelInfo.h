/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_CORE_CHANNELS_CHANNELINFO_H
#define MCX_CORE_CHANNELS_CHANNELINFO_H

#include "CentralParts.h"
#include "core/channels/VectorChannelInfo.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// ----------------------------------------------------------------------
// ChannelInfo
typedef struct ChannelInfo ChannelInfo;
typedef struct VectorChannelInfo VectorChannelInfo;
typedef struct Channel Channel;

extern const struct ObjectClass _ChannelInfo;

typedef void (* fChannelInfoSet)(
    ChannelInfo *              info,
    struct VectorChannelInfo * vector,
    char *                     name,
    char *                     nameInTool,
    char *                     description,
    char *                     unit,
    ChannelType                type,
    ChannelMode                mode,
    char *                     id,
    ChannelValue *             min,
    ChannelValue *             max,
    ChannelValue *             scale,
    ChannelValue *             offset,
    ChannelValue *             defaultValue,
    ChannelValue *             initialValue,
    int                        writeResult);

typedef void (* fChannelInfoGet)(
    const ChannelInfo *         info,
    struct VectorChannelInfo ** vector,
    char **                     name,
    char **                     nameInTool,
    char **                     description,
    char **                     unit,
    ChannelType *               type,
    ChannelMode *               mode,
    char **                     id,
    ChannelValue **             min,
    ChannelValue **             max,
    ChannelValue **             scale,
    ChannelValue **             offset,
    ChannelValue **             defaultValue,
    ChannelValue **             initialValue,
    int *                       writeResult);

typedef ChannelInfo * (* fChannelInfoCopy)(
    const ChannelInfo * info,
    char        * name,
    char        * nameInTool,
    char        * id);

typedef McxStatus (* fChannelInfoInit)(
    ChannelInfo * info,
    const char * name,
    const char * descr,
    const char * unit,
    ChannelType  type,
    const char * id);

typedef ChannelInfo * (* fChannelInfoClone)(const ChannelInfo * info);

typedef ChannelType (* fChannelInfoGetType)(const ChannelInfo * info);
typedef ChannelMode (* fChannelInfoGetMode)(const ChannelInfo * info);

typedef McxStatus    (* fChannelInfoSetDouble)(ChannelInfo * info, double val);
typedef McxStatus    (* fChannelInfoSetInt)(ChannelInfo * info, int val);
typedef McxStatus    (* fChannelInfoSetBool)(ChannelInfo * info, int val);
typedef McxStatus    (* fChannelInfoSetChannelValue)(ChannelInfo * info, ChannelValue * val);
typedef ChannelValue * (* fChannelInfoGetChannelValue)(const ChannelInfo * info);

typedef const char * (* fChannelInfoGetString)(const ChannelInfo * info);
typedef McxStatus    (* fChannelInfoSetString)(ChannelInfo * info, const char * str);
typedef McxStatus    (* fChannelInfoSetChannelType)(ChannelInfo * info, ChannelType type);
typedef McxStatus    (* fChannelInfoSetChannelMode)(ChannelInfo * info, ChannelMode mode);
typedef McxStatus    (* fChannelInfoSetVector)(ChannelInfo * info, VectorChannelInfo * vector);

typedef ChannelValue * (* fChannelInfoGetInitialValue)(const ChannelInfo * info);

typedef int (* fChannelInfoGetInt)(const ChannelInfo * info);

struct ChannelInfo {
    Object _; // base class

    fChannelInfoSet Set;
    fChannelInfoGet Get;
    fChannelInfoClone Clone;
    fChannelInfoCopy Copy;

    fChannelInfoInit Init;

    fChannelInfoSetVector SetVector;
    fChannelInfoSetString SetName;
    fChannelInfoSetString SetNameInTool;
    fChannelInfoSetString SetID;
    fChannelInfoSetString SetDescription;
    fChannelInfoSetString SetUnit;

    fChannelInfoSetChannelValue SetMin;
    fChannelInfoSetChannelValue SetMax;
    fChannelInfoSetChannelValue SetScale;
    fChannelInfoSetChannelValue SetOffset;

    fChannelInfoSetChannelValue SetDefault;
    fChannelInfoSetChannelValue SetInitial;

    fChannelInfoSetBool SetWriteResult;

    fChannelInfoSetChannelType SetType;
    fChannelInfoSetChannelMode SetMode;

    fChannelInfoGetType GetType;
    fChannelInfoGetMode GetMode;
    fChannelInfoGetString GetName;
    fChannelInfoGetString GetNameInTool;
    fChannelInfoGetString GetDescription;
    fChannelInfoGetString GetID;
    fChannelInfoGetString GetUnit;

    fChannelInfoGetInt IsBinary;

    fChannelInfoGetInt GetWriteResultFlag;

    fChannelInfoGetInitialValue GetInitialValue;

    fChannelInfoGetChannelValue GetMin;
    fChannelInfoGetChannelValue GetMax;
    fChannelInfoGetChannelValue GetScale;
    fChannelInfoGetChannelValue GetOffset;
    fChannelInfoGetChannelValue GetDefault;

    fChannelInfoGetString GetLogName;

    /* vector must be NULL if this is a scalar. It is the *only* way
     * to distinguish between vectors of size 1 and scalar values.
     */
    struct VectorChannelInfo * vector;

    char * name;
    char * description;
    char * unitString;
    ChannelMode mode;
    char * id;
    ChannelValue * min;
    ChannelValue * max;

    int writeResult;

    char * nameInTool;

    int connected;

    ChannelType type;
    ChannelValue * defaultValue;
    ChannelValue * initialValue;

    int initialValueIsExact;

    ChannelValue * scale;
    ChannelValue * offset;

    struct Channel * channel;
};

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif /* MCX_CORE_CHANNELS_CHANNELINFO_H */