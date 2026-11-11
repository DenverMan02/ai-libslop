//
//  DinoStage.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 9/8/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DinoStage__
#define __PlantsVersusZombies2__DinoStage__

#include <stdio.h>

#include "AudioMgr.h"
#include "PVZTypes.h"
#include "RtObject.h"
#include "StageModule.h"
#include "WaveActionSpawnZombies.h"

class DinoStage : public StageModule
{
public:
	RT_CLASS_DEFINE(DinoStage, StageModule, RtClass);
	
protected:
	void registerForEvents() override;
	
private:
	void addForegroundToRenderQueue(RenderQueue* i_queue);
	void renderForeground(Graphics* i_g);
};


class DinoStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(DinoStageProperties, StageModuleProperties, RtClass);
	
	RtClass* GetModuleClass() const override
	{
		return DinoStage::StaticGetClass();
	}
};

#endif /* defined(__PlantsVersusZombies2__DinoStage__) */
