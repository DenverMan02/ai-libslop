//
//  IntroModule.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 7/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_IntroModule_h
#define PlantsVersusZombies2_IntroModule_h

#include "LevelModule.h"
#include "TimeMgr.h"

class AnimationMgr;

class IntroModule : public LevelModule
{
public:
	RT_CLASS_DEFINE(IntroModule, LevelModule, RtClass);
	
	IntroModule();
	
	virtual void registerForEvents() override;

	virtual void AddReadySetPlantToAnimMgr(AnimationMgr* i_animMgr, float& io_endTime, Delegate0 i_delgateNameToCall, bool i_finishAfterSet = false);

	virtual float GetShowReadyTime();

protected:
	virtual void		onShowPlant();

private:
	void				onShowReady();
	void				onShowSet();
	void				onFinishReadySetPlant();

	Delegate0			m_endIntroMessageDelegate;
};

class IntroModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(IntroModuleProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{ 
		return IntroModule::StaticGetClass();
	}
};

typedef RtWeakPtr<const IntroModuleProperties> IntroModulePropertiesPtr;

#endif
