//
//  ZombieAnimRig_TreasureYeti.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 1/8/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAnimRig_TreasureYeti__
#define __PlantsVersusZombies2__ZombieAnimRig_TreasureYeti__

#include "ZombieAnimRig.h"

class Zombie;

class ZombieAnimRig_TreasureYeti : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_TreasureYeti, ZombieAnimRig, RtClass);

	void PlayYetiWalk(LoopingAnimContinuedReflectionDelegate i_onSequenceContinued);
	void PlayWalkBackward();

	void SetDamageIndex(const int i_damageIndex);
	
	ZombieParticle* DropStick(Zombie* i_zombie);
	void HideStick();

protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	virtual const std::vector<std::string>& getStickLayerNames();
	virtual const std::string				GetHeadParticleName() override;
	virtual const std::string				GetStickParticleName();

	virtual void onPopAnimInitialized() override;

private:
	void prepWorldHatLayers(PASpriteInst* io_curSprite);
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_TreasureYeti__) */
