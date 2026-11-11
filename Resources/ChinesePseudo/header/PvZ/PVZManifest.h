//
//  PVZManifest.h
//  PlantsVersusZombies2
//
//  Created by David Siems 3/6/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PVZMANIFEST_H__
#define __PVZMANIFEST_H__

#include "PropertySheetBase.h"
#include "PVZVersion.h"
#include "NetworkServiceManager.h"

struct PVZManifestFile
{
    PVZManifestFile()
    {
        name       = "";
        size_byte  = 0;
        md5        = "";
    }
    
    std::string     name;
    uint32          size_byte;
    std::string     md5;
};

class PVZManifest : public PropertySheetBase
{
public:
    
	RT_CLASS_DEFINE(PVZManifest, PropertySheetBase, RtClass);
    
    std::string                  url;
    
    std::vector<PVZManifestFile> files_res;
    
    PVZManifestFile              file_apk;
};

namespace Manifest 
{
	const PVZManifest& Get();
}

#endif
