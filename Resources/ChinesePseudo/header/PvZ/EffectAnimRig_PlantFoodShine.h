//
//  EffectAnimRig_PlantFoodShine.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/19/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __EFFECTANIMRIG_PLANTFOODSHINE_H__
#define __EFFECTANIMRIG_PLANTFOODSHINE_H__

#include "Precompile.h"
#include "PopAnimRig.h"

class EffectAnimRig_PlantFoodShine : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_PlantFoodShine, PopAnimRig, RtClass);
	
	bool PlayPlantFoodShineStart();
	bool PlayPlantFoodShineEnd();
	
	bool IsPlaying() const
	{
		return m_playState != SHINE_OFF;
	}
	
	void CancelEffect()
	{
		m_playState = SHINE_OFF;
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
	
	PlantFoodShinePlayState m_playState;
};

#endif // __EFFECTANIMRIG_PLANTFOODSHINE_H__
