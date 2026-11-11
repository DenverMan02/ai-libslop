//
//  GoldRoadModule.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-12-22.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GoldRoadModule__
#define __PlantsVersusZombies2__GoldRoadModule__

#include "LevelModule.h"
#include "Core.h"
#include "BoardRegion.h"

class GoldRoadModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(GoldRoadModule, LevelModule, RtClass);
	
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
    
    void renderRunBackground(Sexy::Graphics *i_g);
    void addBackgroundToRenderQueue(class RenderQueue* i_queue);
	
private:
    void onLoadComplete();
    void onGameplayStarted();
    
    
};


class GoldRoadProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(GoldRoadProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return GoldRoadModule::StaticGetClass();
	}
	
	GoldRoadProperties()
	{
		
	}
	
    
};

class GoldRoadRegion : public BoardRegion
{
public:
    RT_CLASS_DEFINE(GoldRoadRegion, BoardRegion, RtClass) {}
    
    GoldRoadRegion();
    
    void GatherPlantingRestrictions(const Sexy::Point &i_atLocation, const class PlantType *i_plantType, std::vector<PlantingReason> *io_plantingErrors) override;
};

#endif /* defined(__PlantsVersusZombies2__GoldRoadModule__) */
