//
//  ArmrackModule.h
//  PlantsVersusZombies2
//
//  Created by zhang xiangyu on 11/4/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_EnergyGridModule_h
#define PlantsVersusZombies2_EnergyGridModule_h

#include "LevelModule.h"
#include "MTRand.h"

class GridItemEnergyGrid;

class EnergyGridModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(EnergyGridModule, LevelModule, RtClass);

    EnergyGridModule();

	
    void spawnEnergyGrid(int waveNum);
    void finishLoad();
    
    void    update();
    
    void    onePlantfoodSpawn();
    
protected:
	virtual void registerForEvents() override;

    float       nextSpawnTime;
    int         currentWave;
    int         leftCount;
private:
    
};

class EnergyGridProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(EnergyGridProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override 
	{
		return EnergyGridModule::StaticGetClass();
	}
	
	EnergyGridProperties()
	{
        waveCD = 5;
        Overrides.clear();
	}
	

    
    struct ItemDataEnergy
    {
        int mX;
        int mY;
        float needStayTime;
        ItemDataEnergy()
        {
            mX = 0;
            mY = 0;
            needStayTime = 10;
        }
    };
    
    ///zxy changed
    struct EnergyGridData
    {
        int    wave;
        std::vector<ItemDataEnergy>   itemList;
    };

    float       waveCD;
    std::vector<EnergyGridData> Overrides;
};


#endif
