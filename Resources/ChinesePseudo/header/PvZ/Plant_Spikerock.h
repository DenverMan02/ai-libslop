//
//  Plant_Spikerock.h
//  PlantsVersusZombies2
//
//  Created by jsola on 10/12/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Spikerock_h
#define PlantsVersusZombies2_Plant_Spikerock_h

#include "Plant_Spikeweed.h"

class PlantSpikerock : public PlantSpikeweed
{
public:
	RT_CLASS_DEFINE(PlantSpikerock, PlantSpikeweed, RtClass) {}
	
	virtual void Initialize() override;
	virtual void TakeSmashAttack(Sexy::RtWeakPtr<Zombie>) override;
	void		 TakeGridItemSmashAttack(Sexy::RtWeakPtr<GridItem> i_srcGridItem) override;
    virtual void UpdateActions() override;
	
protected:
	virtual PopAnimRig*		createPlantfoodSawEffect() override;
	
private:
	virtual void playAttackSound() override;
	virtual void stopAttackSound() override;
	
	int m_remainingSmashes;
    pvztime_t m_StartTime;
    bool m_bCoolDownFlag;
};

#endif
