//
//  DangerRoomDropInfo.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-12-16.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_DangerRoomDropInfo_h
#define PlantsVersusZombies2_DangerRoomDropInfo_h

#include "PVZTypes.h"
#include "Utils.h"

struct DangerRoomDropTypeInfo
{
    int iWeight;
    std::string strCollectName;
};

struct WorldGateLevelKey
{
    std::string strWorlName;
    int iGate;
    int iLevel;
    
    WorldGateLevelKey() {}
    
    void SetValue(std::string strName, int iG, int iL)
    {
        strWorlName = strName;
        iGate = iG;
        iLevel = iL;
    }
    
    bool operator== (const WorldGateLevelKey& op) const
    {
        return iGate == op.iGate
        && iLevel == op.iLevel
        && strWorlName == op.strWorlName;
    }
};

struct DropInfo
{
    WorldGateLevelKey stKey;
    ValueRange DropCount;
    std::vector<DangerRoomDropTypeInfo> vDropType;
    
    int GetTotalWeight()
    {
        int iWeight = 0;
        for (auto& p : vDropType)
        {
            iWeight += p.iWeight;
        }
        
        return iWeight;
    }
};

class DangerRoomDropInfo
: public Sexy::RtObject
{
public:
    
    RT_CLASS_DEFINE(DangerRoomDropInfo, Sexy::RtObject, RtClass);
    
    DangerRoomDropInfo();
    
    std::vector<DropInfo>& GetConfig() { return m_vDropInfo; }
    
    DropInfo* GetDropInfo(WorldGateLevelKey& key);
    
    void OrderDropWave(WorldGateLevelKey& key, int iMaxWave);
    
    void OrderDropZombie(int iCurWave);
    
    void ClearDate() { m_vDropWave.clear(); }
    
    bool IsInWaves(int iCurWave);
    
private:
    
    int GetWaveDrop(int iCurWave);
    
    void RemoveWaveDrop(int iCurWave);
    
private:
    
    std::vector<DropInfo> m_vDropInfo;
    
    std::vector<int>      m_vDropWave;
    
private:
    
    void InitData();
};

#endif
