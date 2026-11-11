//
//  ZombieAnimRig_Poncho.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/25/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PLANTSVERSUSZOMBIES2_ZOMBIEANIMRIG_PONCHO_H
#define PLANTSVERSUSZOMBIES2_ZOMBIEANIMRIG_PONCHO_H

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_Poncho : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Poncho, ZombieAnimRig, RtClass);
	
	void DiscardPoncho();
	void DiscardPlate();

	void SetHasPlate(bool i_hasPlate);
	void SetPlateDamageIndex(int i_newIndex);

	void SetLayerVisibilityForCurrentState();

	const std::string GetPonchoSymbolName();
	const std::string GetPonchoParticleName();
	const std::string GetPlateSymbolName();
	const std::string GetPlateParticleName();

protected:
	virtual void onPopAnimInitialized() override;

	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	
	const std::vector<std::string>& getPlateLayerNames();

private:
	bool m_hasPlate = false;
	int m_plateDamageIndex = 0;
};

#endif
