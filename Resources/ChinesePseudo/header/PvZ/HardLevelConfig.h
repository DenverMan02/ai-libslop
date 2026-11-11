//
//  HardLevelConfig.h
//  PlantsVersusZombies2
//
//  Created by shizf on 16/5/9.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef HardLevelConfig_h
#define HardLevelConfig_h

#include "PVZDB.h"

struct HardLevelData
{
    int     iWorldIndex;
    int     iLevelIndex;
    float   iDifficulty;
    
    HardLevelData()
    {
        iWorldIndex = 0;
        iLevelIndex = 0;
        iDifficulty = 1;
    }
};

struct ZombieLevelCreater
{
    float ControlNum;
    
    ZombieLevelCreater(float i_controlNum)
    {
        ControlNum = i_controlNum;
    }
    
    int GetZombieLevel();
};

class HardLevelConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(HardLevelConfig, Sexy::RtObject, Sexy::RtClass);
    
    ZombieLevelCreater GetZombieLevelCreate(const std::string& i_levelName);
    
    static HardLevelConfig* GetConfig();
    
private:
    float GetDifficulty(const std::string& i_levelName);
    
    float GetDifficulty(int i_worldIndex, int i_levelIndex);
    
private:
    std::vector<HardLevelData>  m_dataList;
};

#endif /* HardLevelConfig_h */
