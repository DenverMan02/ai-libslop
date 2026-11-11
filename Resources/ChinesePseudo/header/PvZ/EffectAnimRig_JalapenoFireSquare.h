//
//  EffectAnimRig_JalapenoFireSquare.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/11/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_EffectAnimRig_JalapenoFireSquare_h
#define PlantsVersusZombies2_EffectAnimRig_JalapenoFireSquare_h

#include <string>

#include "PopAnimRig.h"
#include "RtDb.h"
#include "RtObject.h"
#include "TimeMgr.h"

class EffectAnimRig_JalapenoFireSquare : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_JalapenoFireSquare, PopAnimRig, RtClass);

	void SetFireDelay(pvztime_t i_delay);
	void PlayFullEffectSequence();
    
    void SetLooping(bool i_looping, int i_loopCount) { m_looping = i_looping; m_loopCount = i_loopCount; }
    pvztime_t CalculateActiveTime();
	
	void SetOwningEffect(class Effect_PopAnim* i_effect);

protected:
	virtual void onPopAnimInitialized() override;
	virtual void onUpdate() override;

	virtual void onFireEnd() {}
	
private:
	void onJalapenoSequenceContinued(const std::string& i_oldAnimName, const std::string& i_newAnimName, int i_playCount);
	
	RtWeakPtr<class Effect_PopAnim> m_owningEffect;
	pvztime_t m_activationTime = PVZ_EOT();
    pvztime_t m_endTime = PVZ_EOT();
    bool m_looping = false;
    int m_loopCount = 0;
};

#endif
