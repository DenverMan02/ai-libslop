//
//  BronzeModule.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 13-12-31.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BronzeModule__
#define __PlantsVersusZombies2__BronzeModule__

#include <iostream>
#include "LevelModule.h"
#include "MTRand.h"
#include "Precompile.h"
#include "DamageInfo.h"


class GridItemBronze;

class BronzeModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(BronzeModule, LevelModule, RtClass);
    
    BronzeModule();
	GridItemBronze* AddBronze(int i_gridX, int i_gridY);
	
    void spawnBronze(int waveNum);
    void finishLoad();
    
    void increaseBronzeStumpCount();
    void decreaseBronzeStumpCount();
    int  getBronzeStumpCount();

    void onBronzeStumpDestroy(GridItemBronze* bronze);

    float  getBrokenLeftTime();
    
    int    getBronzeStumpSize();
    
protected:
	virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;

    void gameplayStarted();
    void onZombieKilled(class Zombie* i_zombie, const DamageInfo* i_deathBlow);
    void onUpdate();
    
    RtWeakPtr<class UIWidget> m_counterWidget;
    std::vector<RtWeakPtr<class GridItemBronze> > m_bronzeStumpList;
    int   m_bronzeStumpCount;
    float m_leftTime;    
    
    
    int m_currentBronzeIndex;
};

class BronzeProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(BronzeProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return BronzeModule::StaticGetClass();
	}
	
	BronzeProperties()
	{
        data.clear();
        shakeOffset = 0;
	}
	   
    struct ItemDescription
    {
        int mX;
        int mY;
        std::string type;
        float  spawnTime;
        
        ItemDescription()
        {
            mX = 0;
            mY = 0;
            type = "";
            spawnTime = 10;
        }
    };
    
    struct ModuleData
    {
        int    wave;
        std::vector<ItemDescription>   itemList;
    };
    
    float shakeOffset;    
    std::vector<ModuleData> data;
};




#endif /* defined(__PlantsVersusZombies2__BronzeModule__) */
