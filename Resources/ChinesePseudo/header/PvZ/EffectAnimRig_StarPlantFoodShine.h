//
//  EffectAnimRig_StarPlantFoodShine.h
//  PlantsVersusZombies2
//
//  Created by Bokun Zhao on 14-5-16.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectAnimRig_StarPlantFoodShine__
#define __PlantsVersusZombies2__EffectAnimRig_StarPlantFoodShine__

#include "Precompile.h"
#include "PopAnimRig.h"
#include "EffectAnimRig_PlantFoodShine.h"

class EffectAnimRig_StarPlantFoodShine : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_StarPlantFoodShine, PopAnimRig, RtClass);
	
	bool PlayPlantFoodShineStart();
	bool PlayPlantFoodShineEnd();
	
	bool IsPlaying() const
	{
		return m_starFoodState != SHINE_OFF;
	}
	
	void CancelEffect()
	{
		m_starFoodState = SHINE_OFF;
	}
    

	
protected:
    enum PlantFoodShinePlayState
	{
		SHINE_OFF,
		SHINE_PLAYINGSTART,
		SHINE_PLAYINGLOOP,
		SHINE_PLAYINGEND
	};
	
	bool playPlantFoodShineLoop();
	
	virtual void onPopAnimInitialized() override;
	virtual void onAnimStopped() override;
	
    PlantFoodShinePlayState m_starFoodState;
};

#endif /* defined(__PlantsVersusZombies2__EffectAnimRig_StarPlantFoodShine__) */
