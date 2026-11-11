//
//  EffectObject_DamageOverTime.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 5/26/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectObject_DamageOverTime__
#define __PlantsVersusZombies2__EffectObject_DamageOverTime__

#include "Core.h"
#include "EffectObject.h"
#include "DamageInfo.h"

class EffectObject_DamageOverTimeProps : public EffectObjectPropertySheet
{
public:
	RT_CLASS_DEFINE(EffectObject_DamageOverTimeProps, EffectObjectPropertySheet, RtClass);
	
	EffectObject_DamageOverTimeProps()
	{
		DurationInSeconds = 0.0f;
		DamagePerSecond = 0.0f;
	}
	
	std::string	RampUpAnimation;
	std::string	LoopingAnimation;
	std::string	RampDownAnimation;
	
	std::string RampUpAudioEvent;
	std::string RampDownAudioEvent;
	
	pvztime_t	DurationInSeconds;
	
	Rect		DamageArea;
	float		DamagePerSecond;
	std::vector<DamageTypeFlags> JSONDamageTypeFlags;
};

class EffectObject_DamageOverTime : public EffectObject
{
public:
	RT_CLASS_DEFINE(EffectObject_DamageOverTime, EffectObject, RtClass);
	
	EffectObject_DamageOverTime();
	~EffectObject_DamageOverTime();
	
protected:
	void onEffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY) override;
	void onUpdate() override;
	void onAnimStopped(const std::string &i_animLabel) override;
	
#ifndef WANTS_CHEATS_DISABLED
	void onDraw(Graphics* i_g) override;
#endif
	
private:
	AnimationSequence	createAnimationSequence() const;
	int32_t				determineAndGetNextState() const;
	Rect				calculateTargetingRect() const;
	DamageInfo			createDamageInfo() const;
	DamageTypeFlags		getDamageTypeFlags() const;
	
	Sexy::Point	m_gridPosition;
	int32_t		m_currentState;
};


#endif /* defined(__PlantsVersusZombies2__EffectObject_DamageOverTime__) */
