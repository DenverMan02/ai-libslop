//
//  LawnBrainModule.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-4-24.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LawnBrainModule__
#define __PlantsVersusZombies2__LawnBrainModule__

#include "LevelModule.h"
#include "GameEventMgr.h"
#include "GridItemBrain.h"

class LawnBrainModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(LawnBrainModule, LevelModule, RtClass);
    
	float GetEntryAnimDuration();
    
protected:
    virtual void initializeModule() override;
    virtual void registerForEvents() override;
    
private:
	void onReadyForBrains();
    
    bool checkWin();
    
    void onBrainDie(GridItemBrain * i_brain);
	
	void createBrains();
	
	PopAnim* getMowerAnim();
	const std::string& getMowerAudio();
    
    int m_nBrainsRemaining;
};

class LawnBrainProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(LawnBrainProperties, LevelModuleProperties, RtClass);
    
    virtual RtClass* GetModuleClass() const override
    {
        return LawnBrainModule::StaticGetClass();
    }
    
    LawnBrainProperties()
    {
		MowerEntryAnimDuration = 2.5f;
    }
	
	float			MowerEntryAnimDuration;
	std::string 	MowerPopAnim;
    std::string 	MowerActivatedAudioEvent;
};

#endif /* defined(__PlantsVersusZombies2__LawnBrainModule__) */
