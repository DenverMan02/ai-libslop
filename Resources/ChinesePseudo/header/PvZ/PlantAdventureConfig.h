//
//  PlantAdventureConfig.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/26.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantAdventureConfig__
#define __PlantsVersusZombies2__PlantAdventureConfig__

#include "Precompile.h"
#include "RtObject.h"

struct AdventureBonusResult
{
    std::string plantBonus;
    int quantity;
    
    AdventureBonusResult()
    {
        plantBonus = "";
        quantity = -1;
    }
};

struct AdventureBonusInfo
{
    int probility;
    int quantity;
    
    AdventureBonusInfo()
    {
        probility = -1;
        quantity = -1;
    }
};

struct SurpriseInfo
{
    int chipId;
    int probility;
    int quantity;
    int gemCost;
    std::string skuId;
    
    SurpriseInfo()
    {
        chipId = -1;
        probility = -1;
        quantity = -1;
        gemCost = 0;
        skuId = "";
    }
};

struct WorldDungeonInfo
{
    int coolDownTime;
    int rewardCoins;
    int maxAdventureTimes;
    int dungeonId;
    int plantChipsBonusId;
    int itemId;
    std::string worldName;
    std::string dungeonName;
    std::string plantChipsBonus;
    std::vector<std::string> plantRequire;
    std::vector<AdventureBonusInfo> bonusInfo;
    
    WorldDungeonInfo()
    {
        dungeonId = -1;
        coolDownTime = 0;
        rewardCoins = 0;
        plantChipsBonusId = -1;
        maxAdventureTimes = 0;
        worldName = "";
        dungeonName = "";
        plantChipsBonus = "";
        itemId = 0;
    }
};

struct DungeonInfo
{
    int tabIndex;
    std::string worldName;
    std::string tabIcon;
    std::string tabIconDown;
    std::vector<WorldDungeonInfo> dungeon;
    
    DungeonInfo()
    {
        tabIndex = -1;
        worldName = "";
        tabIcon = "";
        tabIconDown = "";
    }
};

class PlantAdventureConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(PlantAdventureConfig, Sexy::RtObject, RtClass);
    
    PlantAdventureConfig();
    ~PlantAdventureConfig();
    
    void Refresh();
    bool IsPlantAdventureDungenon(int i_dungeonId);
    bool IsPlantAdventureDungenon(std::string i_dungeonName);
    std::vector<DungeonInfo> GetDungeonListInfo();
    AdventureBonusResult GetDungeonBonus(int i_dungeonId);
    AdventureBonusResult GetDungeonBonus(std::string i_dungeonName);
    SurpriseInfo GetDungeonSurpriseBonus();
    int GetDungeonBonusCoins(int i_dungeonId);
    int GetDungeonMaxTimes(int i_dungeonId);
    int GetDungeonCDTime(int i_dungeonId);
    int GetDungeonIdByName(std::string i_dungeonName);
    std::string GetDungeonNameById(int i_dungeonId);
    std::vector<std::string> GetPlantRequire(std::string i_dungeonName);
    std::vector<std::string> GetPlantRequire(int i_dungeonId);
    int GetMaxTeam();
    
private:
    bool m_inited;
    int m_maxTeam;
    int m_monthlyCardTeamPro;
    std::vector<DungeonInfo> m_dungeonList;
    std::vector<SurpriseInfo> m_surpriseInfo;
};

#endif /* defined(__PlantsVersusZombies2__PlantAdventureConfig__) */
