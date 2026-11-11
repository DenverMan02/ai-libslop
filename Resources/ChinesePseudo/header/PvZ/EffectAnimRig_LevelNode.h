//
//  EffectAnimRig_LevelNode.h
//  PlantsVersusZombies2
//
//  Created by astajos on 3/22/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_EffectAnimRig_LevelNode_h
#define PlantsVersusZombies2_EffectAnimRig_LevelNode_h

#include <string>

#include "PopAnimRig.h"
#include "RtObject.h"

class EffectAnimRig_LevelNode : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_LevelNode, PopAnimRig, RtClass){};
	
	EffectAnimRig_LevelNode();
    
	void onPostPlayCalled() override;
	
	virtual void SetAnimationPostfix(int i_postifxNumber) { m_effectPostfix = i_postifxNumber; }
	
	virtual void PlayLockedIdle();
	virtual void PlayUnlockingAnimation();
	virtual void PlayUnlockedAnimation();
	virtual void PlayCompletingAnimation(AnimStoppedDelegate i_onAnimStopped);
	virtual void PlayCompletedAnimation();

	virtual std::string GetLockedIdleAnim();
	virtual std::string GetUnlockingAnim();
	virtual std::string GetUnlockedAnim();
	virtual std::string GetCompletingAnim();
	virtual std::string GetCompletedAnim();

private:
    
    void onLockedIdleFinished(const std::string& i_anim);
	void onUnlockingAnimFinished(const std::string& i_anim);
	
	std::string getEffectPostfix();
	
	int	m_effectPostfix;
};

#endif
