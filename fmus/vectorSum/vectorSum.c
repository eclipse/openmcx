// Copyright: 2021 AVL List GmbH
// Author: herwig.stuetz@avl.com

#include <string.h>

#define MODEL_IDENTIFIER vectorSum

#define MODEL_GUID "{b6487505-4749-415a-a01a-37f5a7ae6db5}"

#include "fmi2Functions.h"


typedef struct {
    char * instanceName;
    char * fmuGUID;
    char * fmuLocation;

    fmi2CallbackFunctions * functions;

    fmi2Real b[3];
    fmi2Real v_1[3];
    fmi2Real v_2[3];

} Component;


#if defined(WIN32)
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __attribute__ ((visibility ("default")))
#endif


DLL_EXPORT const char* fmi2GetTypesPlatform(void) {
    return "default";
}

DLL_EXPORT const char* fmi2GetVersion(void) {
    return "2.0";
}

DLL_EXPORT fmi2Status fmi2SetDebugLogging(fmi2Component c, fmi2Boolean loggingOn, size_t comp, const fmi2String comps[]) {
    return fmi2OK;
}


DLL_EXPORT fmi2Component fmi2Instantiate(fmi2String instanceName, fmi2Type fmuType, fmi2String fmuGUID, fmi2String fmuResourceLocation, const fmi2CallbackFunctions* functions, fmi2Boolean visible, fmi2Boolean loggingOn) {
    Component * comp = NULL;

    if (fmuType != fmi2CoSimulation) {
        return NULL;
    }

    comp = (Component *) functions->allocateMemory(1, sizeof(Component));

    comp->instanceName = (char *) functions->allocateMemory(strlen(instanceName) + 1, sizeof(char));
    strcpy(comp->instanceName, instanceName);

    comp->fmuGUID = (char *) functions->allocateMemory(strlen(fmuGUID) + 1, sizeof(char));
    strcpy(comp->fmuGUID, fmuGUID);

    comp->fmuLocation = (char *) functions->allocateMemory(strlen(fmuResourceLocation) + 1, sizeof(char));
    strcpy(comp->fmuLocation, fmuResourceLocation);

    comp->functions = (fmi2CallbackFunctions *) functions;

    comp->b[0] = 0.;
    comp->b[1] = 0.;
    comp->b[2] = 0.;
    comp->v_1[0] = 0.;
    comp->v_1[1] = 0.;
    comp->v_1[2] = 0.;
    comp->v_2[0] = 0.;
    comp->v_2[1] = 0.;
    comp->v_2[2] = 0.;

    return comp;
}

DLL_EXPORT void fmi2FreeInstance(fmi2Component c) {
    Component * comp = (Component *) c;

    comp->functions->freeMemory(comp->instanceName);
    comp->functions->freeMemory(comp->fmuGUID);
    comp->functions->freeMemory(comp->fmuLocation);

    comp->functions->freeMemory(c);
}

fmi2Status Calc(fmi2Component c) {
    Component * comp = (Component *) c;

    comp->b[0] = comp->v_1[0] + comp->v_2[0];
    comp->b[1] = comp->v_1[1] + comp->v_2[1];
    comp->b[2] = comp->v_1[2] + comp->v_2[2];

    return fmi2OK;
}

DLL_EXPORT fmi2Status fmi2SetupExperiment(fmi2Component c, fmi2Boolean toleranceDefined, fmi2Real tolerance, fmi2Real startTime, fmi2Boolean stopTimeDefined, fmi2Real stopTime) {
    return fmi2OK;
}

DLL_EXPORT fmi2Status fmi2EnterInitializationMode(fmi2Component c) {
    return fmi2OK;
}

DLL_EXPORT fmi2Status fmi2ExitInitializationMode(fmi2Component c) {
    return Calc(c);
}

DLL_EXPORT fmi2Status fmi2Terminate(fmi2Component c) {
    return fmi2OK;
}

DLL_EXPORT fmi2Status fmi2Reset(fmi2Component c) {
    return fmi2OK;
}



DLL_EXPORT fmi2Status fmi2GetReal(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Real value[]) {
    Component * comp = (Component *) c;

    size_t i;


    for (i = 0; i < nvr; i++) {
        switch (vr[i]) {
        case 0:
            value[i] = comp->b[0];
            break;
        case 1:
            value[i] = comp->b[1];
            break;
        case 2:
            value[i] = comp->b[2];
            break;
        case 3:
            value[i] = comp->v_1[0];
            break;
        case 4:
            value[i] = comp->v_1[1];
            break;
        case 5:
            value[i] = comp->v_1[2];
            break;
        case 6:
            value[i] = comp->v_2[0];
            break;
        case 7:
            value[i] = comp->v_2[1];
            break;
        case 8:
            value[i] = comp->v_2[2];
            break;
        default:
            return fmi2Error;
        }
    }
    return fmi2OK;
}

DLL_EXPORT fmi2Status fmi2GetInteger(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Integer value[]) {
    return fmi2OK;
}

DLL_EXPORT fmi2Status fmi2GetBoolean(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Boolean value[]) {
    return fmi2OK;
}

DLL_EXPORT fmi2Status fmi2GetString(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2String value[]) {
    return fmi2OK;
}


DLL_EXPORT fmi2Status fmi2SetReal(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Real value[]) {
    Component * comp = (Component *) c;

    size_t i;

    for (i = 0; i < nvr; i++) {
        switch (vr[i]) {
        case 0:
            comp->b[0] = value[i];
            break;
        case 1:
            comp->b[1] = value[i];
            break;
        case 2:
            comp->b[2] = value[i];
            break;
        case 3:
            comp->v_1[0] = value[i];
            break;
        case 4:
            comp->v_1[1] = value[i];
            break;
        case 5:
            comp->v_1[2] = value[i];
            break;
        case 6:
            comp->v_2[0] = value[i];
            break;
        case 7:
            comp->v_2[1] = value[i];
            break;
        case 8:
            comp->v_2[2] = value[i];
            break;
        default:
            return fmi2Error;
        }
    }
    return fmi2OK;
}

DLL_EXPORT fmi2Status fmi2SetInteger(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Integer value[]) {
    return fmi2OK;
}

DLL_EXPORT fmi2Status fmi2SetBoolean(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Boolean value[]) {
    return fmi2OK;
}

DLL_EXPORT fmi2Status fmi2SetString(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2String value[]) {
    return fmi2OK;
}


DLL_EXPORT fmi2Status fmi2GetFMUstate(fmi2Component c, fmi2FMUstate* s) {
    return fmi2Error;
}
DLL_EXPORT fmi2Status fmi2SetFMUstate(fmi2Component c, fmi2FMUstate s) {
    return fmi2Error;
}
DLL_EXPORT fmi2Status fmi2FreeFMUstate(fmi2Component c, fmi2FMUstate* s) {
    return fmi2Error;
}
DLL_EXPORT fmi2Status fmi2SerializedFMUstateSize(fmi2Component c, fmi2FMUstate s, size_t* n) {
    return fmi2Error;
}
DLL_EXPORT fmi2Status fmi2SerializeFMUstate(fmi2Component c, fmi2FMUstate s, fmi2Byte v[], size_t n) {
    return fmi2Error;
}
DLL_EXPORT fmi2Status fmi2DeSerializeFMUstate(fmi2Component c, const fmi2Byte v[], size_t n, fmi2FMUstate* s) {
    return fmi2Error;
}

DLL_EXPORT fmi2Status fmi2SetRealInputDerivatives (fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Integer order[], const fmi2Real value[]) {
    return fmi2OK;
}
DLL_EXPORT fmi2Status fmi2GetRealOutputDerivatives(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Integer order[], fmi2Real value[]) {
    return fmi2OK;
}

DLL_EXPORT fmi2Status fmi2GetDirectionalDerivative(fmi2Component c, const fmi2ValueReference vUnknown_ref[], size_t nUnknown, const fmi2ValueReference vKnown_ref[], size_t vKnown, const fmi2Real dvKnown[], fmi2Real dvUnkown[]) {
    return fmi2OK;
}


DLL_EXPORT fmi2Status fmi2DoStep(fmi2Component c, fmi2Real currentCommunicationPoint, fmi2Real communicationStepSize, fmi2Boolean newStep) {
    return Calc(c);
}

DLL_EXPORT fmi2Status fmi2CancelStep(fmi2Component c) {
    return fmi2OK;
}


DLL_EXPORT fmi2Status fmi2GetStatus(fmi2Component c, const fmi2StatusKind s, fmi2Status* value) {
    return fmi2OK;
}
DLL_EXPORT fmi2Status fmi2GetRealStatus(fmi2Component c, const fmi2StatusKind s, fmi2Real*   value) {
    return fmi2OK;
}
DLL_EXPORT fmi2Status fmi2GetIntegerStatus(fmi2Component c, const fmi2StatusKind s, fmi2Integer* value) {
    return fmi2OK;
}
DLL_EXPORT fmi2Status fmi2GetBooleanStatus(fmi2Component c, const fmi2StatusKind s, fmi2Boolean* value) {
    return fmi2OK;
}
DLL_EXPORT fmi2Status fmi2GetStringStatus(fmi2Component c, const fmi2StatusKind s, fmi2String* value) {
    return fmi2OK;
}
