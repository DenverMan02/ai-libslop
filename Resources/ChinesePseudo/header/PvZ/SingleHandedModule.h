//
//  SingleHandedModule.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-4-15.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SingleHandedModule__
#define __PlantsVersusZombies2__SingleHandedModule__

#include "LevelModule.h"
#include "GridItem.h"

class SingleHandedModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(SingleHandedModule, LevelModule, RtClass);

    SingleHandedModule();
    virtual ~SingleHandedModule();
	
	virtual void registerForEvents() override;

	void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
    GridItemPtr m_railcart;
	
private:
	void placeRailsAndCarts();
    void fireRockets();
    
    void update();
    void onZombieDied(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
    void onZombieAddedToBoard(class Zombie* i_zombie);
    void onTakePlantWeapon(const std::string& plant_name);
    void onTakeImmediatePlantFood();
    void gameplayStarted();
    
    float GetLaunchTimePercent(const std::string& plant_name);
    
    void onReviveCancel();
    void onReviveOK();
    
    void onPlantFoodStart();
    void onPlantFoodEnd(Plant* i_plant);
    
    void UpdatePlantUpgradePercent();
    
private:
    
    int         m_curStage;
    int         m_killnum;
    pvztime_t   m_nextFireRocket;
    std::vector<Point> rocketRandomSquares;
    bool               m_checkCondition;
    std::string        m_LastPlantName;
};

struct SingleWeaponData
{
    int         killnum;
    std::string weaponname;
    float       launchtimepercent;
    
    SingleWeaponData()
    {
        killnum = 0;
        weaponname = "";
        launchtimepercent = 0.5f;
    }
};

struct SpecialWaveData
{
    int                           wave;
    float                         ZombiesWalkSpeed;
    float                         ZombiesHitpointsPercent;
    bool                          ShowHealthBar;
    
    SpecialWaveData(int i_wave, float i_walkSpeed, float i_hp, bool i_showBar)
    {
    	wave = i_wave;
    	ZombiesWalkSpeed = i_walkSpeed;
    	ZombiesHitpointsPercent = i_hp;
    	ShowHealthBar = i_showBar;
    }

    SpecialWaveData()
    {
        wave = 0;
        
        ZombiesWalkSpeed = 0.0f;
        ZombiesHitpointsPercent = 1.0f;
        ShowHealthBar = false;
    }
};

class SingleHandedProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(SingleHandedProperties, LevelModuleProperties, RtClass);
    
    SingleHandedProperties()
    {
        InitWeapon = "peashooter";
        InitWeaponLaunchTimePercent = 0.5f;
        MissileCount = 3;
        MissileInterval = 10.0f;
        RocketHitTime = 3.0;
        RocketSpeed   = 500;
        TimeSpeed = 2.0f;
        ZombiesWalkSpeed = 0.0f;
        ZombiesHitpointsPercent = 1.0f;
    }
	
	virtual RtClass* GetModuleClass() const override
	{
		return SingleHandedModule::StaticGetClass();
	}
    
    std::vector<SpecialWaveData>  SpecialWaveDatas;
    std::vector<SingleWeaponData> DropWeaponDatas;
    std::string                   InitWeapon;
    float                         InitWeaponLaunchTimePercent;
    int                           MissileCount;
    pvztime_t                     MissileInterval;
    float                         RocketHitTime;
    float                         RocketSpeed;
    float                         TimeSpeed;
    float                         ZombiesWalkSpeed;
    float                         ZombiesHitpointsPercent;
};

#endif /* defined(__PlantsVersusZombies2__SingleHandedModule__) */
