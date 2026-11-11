//
//  ArmrackModule.h
//  PlantsVersusZombies2
//
//  Created by zhang xiangyu on 11/4/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ArmrackModule_h
#define PlantsVersusZombies2_ArmrackModule_h

#include "LevelModule.h"
#include "MTRand.h"
#include "GridItemArmrack.h"


class ArmrackModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(ArmrackModule, LevelModule, RtClass) {}

	GridItemArmrack* AddArmrack(int i_gridX, int i_gridY);
	
    void spawnArmrack(int waveNum);
    void finishLoad();
    
protected:
	virtual void registerForEvents() override;
    //virtual void unregisterForEvents();

private:
	void addArmrack(int i_minGridX, int i_maxGridX, int i_count, MTRand &i_levelRNG);
};

class ArmrackProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(ArmrackProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return ArmrackModule::StaticGetClass();
	}
	
	ArmrackProperties()
	{
		ArmrackCount = 0;
		SpawnColumnStart = 0;
		SpawnColumnEnd = 0;
        Overrides.clear();
	}
	
	int ArmrackCount;
	int SpawnColumnStart;
	int SpawnColumnEnd;

    
    struct ItemData
    {
        int mX;
        int mY;
        ArmrackType type;
        int level;
        ItemData()
        {
            mX = 0;
            mY = 0;
            type = ArmrackRandom;
            level = 1;
        }
    };
    
    ///zxy changed
    struct ArmrackData
    {
        int    wave;
        std::vector<ItemData>   itemList;
    };
    
    
    
	//std::vector<Point> Overrides;
    std::vector<ArmrackData> Overrides;
};


#endif
