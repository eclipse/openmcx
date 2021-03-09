/********************************************************************************
 * Copyright (c) 2020 AVL List GmbH and others
 * 
 * This program and the accompanying materials are made available under the
 * terms of the Apache Software License 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 * 
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/

#ifndef MCX_STORAGE_PPD_H
#define MCX_STORAGE_PPD_H

#include "CentralParts.h"
#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum PpdType {
    PPD_NO_TYPE,
    PPD_ELEMENT,
    PPD_SUBSYSTEM
};

enum PpdIcon {
    PPD_NO_ICON,
    PPD_ICON_INPORT
};

struct PpdFolder;
struct PpdRootFolder;
struct PpdElement;
struct PpdLink;

typedef enum   PpdType       PpdType;
typedef enum   PpdIcon       PpdIcon;
typedef struct PpdFolder     PpdFolder;
typedef struct PpdRootFolder PpdRootFolder;
typedef struct PpdElement    PpdElement;
typedef struct PpdLink       PpdLink;


typedef const char * (* fPpdElementGetName)(PpdElement * element);
typedef McxStatus (* fPpdElementPrintIndented)(PpdElement * element, int level, FILE * stream);

extern const struct ObjectClass _PpdElement;

struct PpdElement {
    Object _; /* super class */

    fPpdElementGetName GetName;
    fPpdElementPrintIndented PrintIndented;
};


typedef McxStatus (* fPpdFolderSetup)(PpdFolder * folder, const char * id, const char * name);
typedef McxStatus (* fPpdFolderSetType)(PpdFolder * folder, PpdType type);
typedef McxStatus (* fPpdFolderSetIcon)(PpdFolder * folder, PpdIcon icon);
typedef McxStatus (* fPpdFolderAddElement)(PpdFolder * folder, PpdElement * element);
typedef PpdFolder * (* fPpdFolderInsertComponent)(PpdFolder * folder, const char * linkType, const char * compName, const char * fileNameOut, const char * fileNameIn, const char * fileNameLocal);
typedef PpdElement * (* fPpdFolderGetElementByName)(PpdFolder * folder, const char * name);
typedef char * (* fPpdFolderEncodeNameString)(PpdFolder * folder, const char * str);

extern const struct ObjectClass _PpdFolder;

struct PpdFolder {
    PpdElement _; /* super class */

    fPpdFolderSetup      Setup;
    fPpdFolderAddElement AddElement;
    fPpdFolderInsertComponent InsertComponent;
    fPpdFolderGetElementByName GetElementByName;

    fPpdFolderEncodeNameString EncodeNameString;

    fPpdFolderSetType SetType;
    fPpdFolderSetIcon SetIcon;

    PpdType type;
    PpdIcon icon;

    char * id;
    char * name;

    ObjectContainer * elements;
};


typedef McxStatus (* fPpdRootFolderSetup)(PpdRootFolder * root, const char * id, const char * name, const char * client, const char * version);
typedef McxStatus (* fPpdRootFolderPrint)(PpdRootFolder * root, const char * filename);

extern const struct ObjectClass _PpdRootFolder;

struct PpdRootFolder {
    PpdFolder _; /* super class */

    fPpdRootFolderSetup Setup;
    fPpdRootFolderPrint Print;

    char * client;
    char * version;
};


typedef struct PpdTimeOffset PpdTimeOffset;

struct PpdTimeOffset {
    double xshift;
    double xmin;
};

typedef McxStatus (* fPpdLinkSetup)(PpdLink * link, const char * type, const char * location);
typedef McxStatus (* fPpdLinkSetTimeOffset)(PpdLink * link, double xshift, double xmin);

extern const struct ObjectClass _PpdLink;

struct PpdLink {
    PpdElement _; /* super class */

    fPpdLinkSetup Setup;
    fPpdLinkSetTimeOffset SetTimeOffset;

    char * type;
    char * location;

    /* time offset */
    PpdTimeOffset * offset;
};


PpdRootFolder * PpdRootFolderMake(const char * id, const char * name, const char * client, const char * version);
PpdFolder * PpdFolderMake(const char * id, const char * name);
PpdLink * PpdLinkMake(const char * type, const char * location);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif /* __cplusplus */

#endif /* MCX_STORAGE_PPD_H */