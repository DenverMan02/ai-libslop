//
//  TowerDefendModule.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-9-11.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TowerDefendModule__
#define __PlantsVersusZombies2__TowerDefendModule__

#include "LevelModule.h"
#include "BoardEnums.h"
#include "PlantType.h"
#include "BoardConstants.h"
#include "Plant.h"

class TowerDefendModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(TowerDefendModule, LevelModule, RtClass);
    
	TowerDefendModule();
    
    const std::vector<std::string>& GetBossSkills();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
protected:
    
    struct TDRoadData
    {
        GridSquareType type;
        std::string    img_name;
        
        TDRoadData()
        {
            img_name = "";
            type     = GRIDSQUARE_TD_PLANTED;
        }
    };
    
	virtual void			registerForEvents() override;
	virtual void			onPostLoad() override;
    
    bool                    handleTouch(const Sexy::Touch& i_touch);
	void                    cancelTouch();
	
private:
    
    void                    onUpdate();
	void					onLoadComplete();
    void                    onGamePlayStarted();
    void                    onPlantUpgradeTouch(const Point& i_pos);
    void                    onPlantPlanted(class Plant* i_plant);
    void                    onPlantDied(class Plant* i_plant);
    void                    onZombieAddedToBoard(class Zombie* i_zombie);
    bool                    onWinCondition();
	
    void					addToRenderQueue(class RenderQueue* i_queue);
	void					renderRoads(Graphics* i_g);
    
    void					placeRoads();
	void					parseRoadDatas();
    
    std::string             GetPlantUpgradeType(Plant * i_plant);
    int                     GetPlantUpgradeSunSpend(Plant * i_plant);
    float                   GetPlantLaunchtimePercent(Plant * i_plant);
    
private:
    
    TDRoadData              m_RoadDatas[BoardConstants::NUMBER_OF_COLUMNS_RAW][BoardConstants::NUMBER_OF_ROWS_RAW];
    
    bool                    m_GameStarted;
};

struct TowerDefendRoad
{
	int			GridX;
	int			GridY;
    std::string Img;
    
	TowerDefendRoad()
    {
        GridX = 0;
        GridX = 0;
        Img   = "";
    }
};

struct TowerDefendPlantUpgradeInfo
{
	int			cost;
    std::string name;
    float       launchtimepercent;
    
	TowerDefendPlantUpgradeInfo()
    {
        cost = 0;
        name = "";
        launchtimepercent = 1.0f;
    }
};

struct TowerDefendPlantUpgradeTree
{
	std::vector<TowerDefendPlantUpgradeInfo> Infos;
    
	TowerDefendPlantUpgradeTree()
    {
        
    }
};

class TowerDefendProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(TowerDefendProperties, LevelModuleProperties, RtClass);
	
	TowerDefendProperties()
	{
        HouseName    = "house_3";
        HousePopAnim = "POPANIM_TOWERDEFEND_HOUSE_PIG_1";
        HitpointsPercentAddPerWave = 0.05f;
	}
	
	virtual RtClass* GetModuleClass() const override
	{
		return TowerDefendModule::StaticGetClass();
	}
    
    float                                    HitpointsPercentAddPerWave;
    std::string                              HousePopAnim;
    std::string                              HouseName;
	std::vector<struct TowerDefendRoad>      Roads;
	std::vector<TowerDefendPlantUpgradeTree> Trees;
    std::vector<std::string>                 BossSkills;
};

#endif /* defined(__PlantsVersusZombies2__TowerDefendModule__) */
