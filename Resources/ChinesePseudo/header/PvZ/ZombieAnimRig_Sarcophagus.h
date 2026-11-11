//
//  ZombieAnimRig_Sarcophagus.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/9/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEANIMRIG_SARCOPHAGUS_H__
#define __ZOMBIEANIMRIG_SARCOPHAGUS_H__

#include "Precompile.h"
#include "ZombieAnimRig.h"

enum ZombieAnimRigState_Sarcophagus
{
	ZOMBIEANIM_SARC_BREAKING = ZOMBIEANIM_USERDEFINED,
	ZOMBIEANIM_SARC_BUSTINGOUT,
};

class ZombieAnimRig_Sarcophagus : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Sarcophagus, ZombieAnimRig, RtClass);
	
	// New stuff
	virtual bool PlayBustOutAnimation();
	void SetLayerVisibilityForCurrentState();
	
	void SetSarcophagusDamageIndex(int i_newIndex);

protected:
	virtual void onPopAnimInitialized() override;
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	
	const std::vector<std::string>& getSarcophagusLayerNames();
	
	virtual const std::string getIdleAnimationName() override;
	virtual const std::string getWalkAnimationName() override;
	virtual const std::string getEatAnimationName() override;
    virtual const std::string getStunAnimationName() override;
	
	bool m_hasShield;
	int m_sarcophagusDamageIndex;
};

#endif // __ZOMBIEANIMRIG_SARCOPHAGUS_H__
