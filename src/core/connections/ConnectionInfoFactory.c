/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#include "core/connections/ConnectionInfoFactory.h"
#include "core/connections/ConnectionInfo.h"
#include "core/Databus.h"

#include "util/string.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static ConnectionInfo * ConnectionInfoFactoryCreateConnectionInfo(ObjectContainer * components,
                                                                  ConnectionInput * connInput,
                                                                  Component * sourceCompOverride,
                                                                  Component * targetCompOverride) {
    McxStatus retVal = RETURN_OK;
    ConnectionInfo * info = NULL;

    Component * sourceComp = NULL;
    Component * targetComp = NULL;

    int sourceChannel = 0;
    int targetChannel = 0;
    int id = 0;

    int connectionInverted = 0;

    int isDecoupled = FALSE;
    InterExtrapolatingType isInterExtrapolating = INTERPOLATING;

    InterExtrapolationType interExtrapolationType;
    InterExtrapolationParams * interExtrapolationParams = NULL;

    DecoupleType decoupleType;
    int decouplePriority = 0;

    // temporary data for reading not used in info->Set()
    char * strFromChannel = NULL;
    char * strToChannel = NULL;

    // weak pointers to endpoint data
    char * inputToChannel = NULL;
    char * inputToComponent = NULL;
    char * inputFromChannel = NULL;
    char * inputFromComponent = NULL;

    Databus     * databus     = NULL;
    DatabusInfo * databusInfo = NULL;

    info = (ConnectionInfo *)object_create(ConnectionInfo);
    if (NULL == info) {
        return NULL;
    }

    // get default values
    info->Get(
        info,
        &sourceComp,
        &targetComp,
        &sourceChannel,
        &targetChannel,
        &isDecoupled,
        &isInterExtrapolating,
        &interExtrapolationType,
        &interExtrapolationParams,
        &decoupleType,
        &decouplePriority
    );

    // use conn endpoints from caller if they are not in components
    sourceComp = sourceCompOverride;
    targetComp = targetCompOverride;

    // source component
    if (sourceComp == NULL) {
        inputFromComponent = connInput->fromType == ENDPOINT_SCALAR ? connInput->from.scalarEndpoint->component :
                                                                      connInput->from.vectorEndpoint->component;
        if (inputFromComponent == NULL) {
            retVal = input_element_error((InputElement*)connInput, "Source element is not specified");
            goto cleanup;
        }

        if (0 == strlen(inputFromComponent)) {
            retVal = input_element_error((InputElement*)connInput, "Source element name is empty");
            goto cleanup;
        }

        id = components->GetNameIndex(components, inputFromComponent);
        if (id < 0) {
            retVal = input_element_error((InputElement*)connInput, "Source element %s does not exist",
                                         inputFromComponent);
            goto cleanup;
        }

        sourceComp = (Component *) components->elements[id];
    }

    // source channel
    inputFromChannel = connInput->fromType == ENDPOINT_SCALAR ? connInput->from.scalarEndpoint->channel :
                                                                connInput->from.vectorEndpoint->channel;
    strFromChannel = mcx_string_copy(inputFromChannel);
    if (0 == strlen(strFromChannel)) {
        retVal = input_element_error((InputElement*)connInput, "Source port name is empty");
        goto cleanup;
    }

    if (connInput->fromType == ENDPOINT_VECTOR) {
        mcx_free(strFromChannel);
        strFromChannel = CreateIndexedName(inputFromChannel, connInput->from.vectorEndpoint->startIndex);
        if (!strFromChannel) {
            retVal = RETURN_ERROR;
            goto cleanup;
        }
    }

    // target component
    if (targetComp == NULL) {
        inputToComponent = connInput->toType == ENDPOINT_SCALAR ? connInput->to.scalarEndpoint->component :
                                                                  connInput->to.vectorEndpoint->component;
        if (inputToComponent == NULL) {
            retVal = input_element_error((InputElement*)connInput, "Target element is not specified");
            goto cleanup;
        }

        if (0 == strlen(inputToComponent)) {
            retVal = input_element_error((InputElement*)connInput, "Target element name is empty");
            goto cleanup;
        }

        id = components->GetNameIndex(components, inputToComponent);
        if (id < 0) {
            retVal = input_element_error((InputElement*)connInput, "Target element %s does not exist",
                                         inputToComponent);
            goto cleanup;
        }

        targetComp = (Component *) components->elements[id];
    }

    // target channel
    inputToChannel = connInput->toType == ENDPOINT_SCALAR ? connInput->to.scalarEndpoint->channel :
                                                            connInput->to.vectorEndpoint->channel;
    strToChannel = mcx_string_copy(inputToChannel);
    if (0 == strlen(strToChannel)) {
        retVal = input_element_error((InputElement*)connInput, "Target port name is empty");
        goto cleanup;
    }

    if (connInput->toType == ENDPOINT_VECTOR) {
        mcx_free(strToChannel);
        strToChannel = CreateIndexedName(inputToChannel, connInput->to.vectorEndpoint->startIndex);
        if (!strToChannel) {
            retVal = RETURN_ERROR;
            goto cleanup;
        }
    }

    databus = sourceComp->GetDatabus(sourceComp);
    databusInfo = DatabusGetOutInfo(databus);
    sourceChannel = DatabusInfoGetChannelID(databusInfo, strFromChannel);
    if (sourceChannel < 0) {
        // the connection might be inverted, see SSP 1.0 specification (section 5.3.2.1, page 47)

        databusInfo = DatabusGetInInfo(databus);
        sourceChannel = DatabusInfoGetChannelID(databusInfo, strFromChannel);

        if (sourceChannel < 0) {
            mcx_log(LOG_ERROR, "Connection: Source port %s of element %s does not exist",
                strFromChannel, sourceComp->GetName(sourceComp));
            retVal = RETURN_ERROR;
            goto cleanup;
        } else {
            connectionInverted = 1;
        }
    }

    databus = targetComp->GetDatabus(targetComp);

    if (0 == connectionInverted) {
        databusInfo = DatabusGetInInfo(databus);
    } else {
        databusInfo = DatabusGetOutInfo(databus);
    }

    targetChannel = DatabusInfoGetChannelID(databusInfo, strToChannel);
    if (targetChannel < 0) {
        if (0 == connectionInverted) {
            mcx_log(LOG_ERROR, "Connection: Target port %s of element %s does not exist",
                strToChannel, targetComp->GetName(targetComp));
        } else {
            mcx_log(LOG_ERROR, "Connection: Source port %s of element %s does not exist",
                strToChannel, targetComp->GetName(targetComp));
        }
        retVal = RETURN_ERROR;
        goto cleanup;
    }

    if (connectionInverted) {
        int tmp = sourceChannel;
        Component * tmpCmp = sourceComp;

        sourceChannel = targetChannel;
        targetChannel = tmp;

        sourceComp = targetComp;
        targetComp = tmpCmp;

        mcx_log(LOG_DEBUG, "Connection: Inverted connection (%s, %s) -- (%s, %s)",
            targetComp->GetName(targetComp), strFromChannel, sourceComp->GetName(sourceComp), strToChannel);
    }

    // extrapolation
    if (connInput->interExtrapolationType.defined) {
        interExtrapolationType = connInput->interExtrapolationType.value;
    }

    if (INTEREXTRAPOLATION_POLYNOMIAL == interExtrapolationType) {
        // read the parameters of poly inter-/extrapolation
        InterExtrapolationParams * params = interExtrapolationParams;
        InterExtrapolationInput * paramsInput = connInput->interExtrapolation;

        params->extrapolationInterval = paramsInput->extrapolationType;
        params->interpolationInterval = paramsInput->interpolationType;
        params->interpolationOrder = paramsInput->interpolationOrder;
        params->extrapolationOrder = paramsInput->extrapolationOrder;
    }

    // decouple
    if (connInput->decoupleType.defined) {
        decoupleType = connInput->decoupleType.value;

        // decouple priority
        if (DECOUPLE_IFNEEDED == decoupleType) {
            DecoupleIfNeededInput * decoupleInput = (DecoupleIfNeededInput*)connInput->decoupleSettings;
            if (decoupleInput->priority.defined) {
                decouplePriority = decoupleInput->priority.value;
            }

            if (decouplePriority < 0) {
                retVal = input_element_error((InputElement*)decoupleInput, "Invalid decouple priority");
                goto cleanup;
            }
        }
    }

    info->Set(
        info,
        sourceComp,
        targetComp,
        sourceChannel,
        targetChannel,
        isDecoupled,
        isInterExtrapolating,
        interExtrapolationType,
        interExtrapolationParams,
        decoupleType,
        decouplePriority
    );

cleanup:
    if (RETURN_ERROR == retVal) { object_destroy(info); }
    if (NULL != strFromChannel) { mcx_free(strFromChannel); }
    if (NULL != strToChannel) { mcx_free(strToChannel); }

    return info;
}

ObjectContainer * ConnectionInfoFactoryCreateConnectionInfos(ObjectContainer * components,
                                                             ConnectionInput * connInput,
                                                             Component * sourceCompOverride,
                                                             Component * targetCompOverride) {
    ConnectionInfo * info  = NULL;
    ObjectContainer * list = NULL;

    list = (ObjectContainer *) object_create(ObjectContainer);
    if (!list) {
        goto cleanup;
    }

    info = ConnectionInfoFactoryCreateConnectionInfo(components, connInput,
                                                     sourceCompOverride, targetCompOverride);
    if (!info) {
        goto cleanup;
    }

    if (connInput->fromType == ENDPOINT_VECTOR || connInput->toType == ENDPOINT_VECTOR) {
        /* vector of connections */
        int fromStartIndex = connInput->fromType == ENDPOINT_VECTOR ? connInput->from.vectorEndpoint->startIndex : 0;
        int fromEndIndex = connInput->fromType == ENDPOINT_VECTOR ? connInput->from.vectorEndpoint->endIndex : 0;

        int toStartIndex = connInput->toType == ENDPOINT_VECTOR ? connInput->to.vectorEndpoint->startIndex : 0;
        int toEndIndex = connInput->toType == ENDPOINT_VECTOR ? connInput->to.vectorEndpoint->endIndex : 0;

        int i = 0;
        int fromStart = info->GetSourceChannelID(info);
        int toStart = info->GetTargetChannelID(info);

        if (fromEndIndex - fromStartIndex != toEndIndex - toStartIndex) {
            /* the lenghts of both sides do not match */
            mcx_log(LOG_ERROR, "Connection: Lengths of vectors do not match");
            goto cleanup;
        }

        for (i = 0; fromStartIndex + i <= fromEndIndex; i++) {
            ConnectionInfo * copy = info->Copy(info, fromStart + i, toStart + i);
            if (!copy) {
                goto cleanup;
            }
            list->PushBack(list, (Object *) copy);
        }

        object_destroy(info);
    } else {
        /* info is the only connection: leave as is */
        list->PushBack(list, (Object *) info);
    }

    return list;

cleanup:
    if (list) {
        list->DestroyObjects(list);
        object_destroy(list);
    }
    if (info) { object_destroy(info); }
    return NULL;
}

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */