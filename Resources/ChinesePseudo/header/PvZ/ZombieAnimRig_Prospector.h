//
//  ZombieAnimRig_Prospector.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/7/12
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PLANTSVERSUSZOMBIES2_ZOMBIEANIMRIG_PROSPECTOR_H
#define PLANTSVERSUSZOMBIES2_ZOMBIEANIMRIG_PROSPECTOR_H

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_Prospector : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Prospector, ZombieAnimRig, RtClass);
	
	void PlayBlastoff(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);
	void PlayFly();
	void PlayLanding(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimDone);

	void HideDynamite();
	void DefuseDynamite();
	void SetDynamiteState(pvztime_t i_totalTime, pvztime_t i_timeLeft);

	void SetDynoDamage(bool i_show);

protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	
	virtual void onPopAnimInitialized() override;

private:
	void onBlastoffEnd();
	void onLandingEnd();

	enum ProspectorDynamiteState
	{
		PROSPECTOR_DYNAMITE_NONE,
		PROSPECTOR_DYNAMITE_SMALL,
		PROSPECTOR_DYNAMITE_MEDIUM,
		PROSPECTOR_DYNAMITE_LARGE,
		PROSPECTOR_DYNAMITE_HIDDEN,
		PROSPECTOR_DYNAMITE_DEFUSED
	};
	
	void SetDynamiteState(ProspectorDynamiteState i_newState);
	
	ProspectorDynamiteState m_dynamiteState = PROSPECTOR_DYNAMITE_NONE;
};

#endif
