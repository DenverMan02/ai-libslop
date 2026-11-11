//
//  StarConvertConfig.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/4/8.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef StarConvertConfig_h
#define StarConvertConfig_h

#include "Precompile.h"
#include "RtObject.h"

struct ConvertItem
{
    int starRequire;
    int plantStarLevel;
    int convertItemId;
    
    ConvertItem()
    {
        starRequire = 0;
        plantStarLevel = 0;
        convertItemId = 0;
    }
};

struct ConvertObject
{
//    int         starRequire;
    std::string objectType;
    std::string objectName;
    std::vector<ConvertItem> convertItems;
    
    ConvertObject()
    {
//        starRequire = 0;
        objectType  = "";
        objectName  = "";
        convertItems.clear();
    }
};

class StarConvertConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(StarConvertConfig, Sexy::RtObject, RtClass);
    
    StarConvertConfig();
    ~StarConvertConfig();
    
    void Refresh();
    
    std::vector<ConvertObject> GetConvertList();
    ConvertItem GetConvertItemInfo(std::string i_objectName, int i_level = 0);
    
    int GetStarRequire(std::string i_objectName, int i_level = 0);
    int GetPlantStarLevel(std::string i_objectName, int i_level = 0);
    int GetConvertItemId(std::string i_objectName, int i_level = 0);
    int GetMaxConvertId();
    
private:
    bool m_inited;
    std::vector<ConvertObject> m_convertList;
};

#endif /* StarConvertConfig_h */
