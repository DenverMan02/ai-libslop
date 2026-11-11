//
//  PlantFamilyBoostPropertySheet.h
//  PlantsVersusZombies2
//
//  Created by shizf on 2016/11/14.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef PlantFamilyBoostPropertySheet_h
#define PlantFamilyBoostPropertySheet_h

#include "PlantBoostPropertySheet.h"
#include "RtObject.h"

typedef RtWeakPtr<class PlantFamilyBoostPropertySheet> PlantFamilyBoostPropertySheetPtr;

class PlantFamilyBoostPropertySheet : public PlantBoostPropertySheet
{
public:
    RT_CLASS_DEFINE(PlantFamilyBoostPropertySheet, PlantBoostPropertySheet, RtClass);
    
    std::string AttrType;
    // For name display
    std::string Name;
    // For plain description
    std::string Description;
    //value at which index
    int ValueIndex = 1;
    int DisplayType = 0;
    float AddValue = 0;
    std::vector<float> Qualitys;
    std::vector<float> Values;
};

typedef RtWeakPtr<class PlantFamilyPropertySheet> PlantFamilyPropertySheetPtr;

class PlantFamilyPropertySheet : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(PlantFamilyPropertySheet, PropertySheetBase, RtClass);
    
    int FamilyID = -1;
    std::string Name;
    std::string Description;
    int PlantQuality = 0;
    
    std::vector<std::string> PlantList;
    std::vector<Sexy::SexyVector2> PlantPosition;
    std::vector<PlantBoost> EnableFamilyBoost;
    PlantBoost DefaultFamilyBoost;
};

#endif /* PlantFamilyBoostPropertySheet_h */
