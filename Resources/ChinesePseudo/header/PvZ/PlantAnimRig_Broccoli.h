//
//  PlantAnimRig_Broccoli.h
//  PlantsVersusZombies2
//
//  Created by mao xingxing 10/21/2014.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTANIMRIG_BROCCOLI_H__
#define __PLANTANIMRIG_BROCCOLI_H__

#include "Precompile.h"
#include "PlantAnimRig.h"

class PlantAnimRig_Broccoli : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Broccoli, PlantAnimRig, RtClass);
	
	virtual bool PlayIdleLooped() override;
    void SetIsDamage(bool bDamage);
    bool PlayRestLooped();
    bool PlayAdvancedAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate() );
    bool PlayPullFail( PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate() );
    int CalcDamageStateCount() override;
protected:
	virtual void onPopAnimInitialized() override;
private:
	std::string m_lastUsedIdleAnim;
};

#endif // __PLANTANIMRIG_BROCCOLI_H__
