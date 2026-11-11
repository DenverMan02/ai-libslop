//
//  PlantAnimRig_Snapdragon.h
//  PlantsVersusZombies2
//
//  Created by Andy Seavy on 4/6/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_SNAPDRAGON_H__
#define __PLANTANIMRIG_SNAPDRAGON_H__

#include "Precompile.h"
#include "PlantAnimRig.h"

class PlantAnimRig_Snapdragon : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Snapdragon, PlantAnimRig, RtClass);
	
	virtual bool PlayInitialFrame() override;
	virtual bool PlayIdleLooped() override;
	virtual bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
    virtual bool PlayAttackFireDragon(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    
public:
    float m_plantfoodRate = 0.5f;
    bool  m_isNewPlantfood = false;
    
private:
	std::string m_lastUsedIdleAnim;
};

#endif // __PLANTANIMRIG_SNAPDRAGON_H__
