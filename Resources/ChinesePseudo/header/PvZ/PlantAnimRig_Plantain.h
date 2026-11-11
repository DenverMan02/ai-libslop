//
//  PlantAnimRig_Plantain.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/20/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantAnimRig_Plantain_h
#define PlantsVersusZombies2_PlantAnimRig_Plantain_h

#include "Precompile.h"
#include "PlantAnimRig.h"
#include "RtObject.h"

class PlantAnimRig_Plantain : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Plantain, PlantAnimRig, RtClass);
	PlantAnimRig_Plantain();
	/// Overrides
	
	virtual bool PlayIdleLooped() override;
	virtual bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;
	virtual bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
	virtual bool PlayPlantFoodEnd() override;
	virtual pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;

	/// Custom functionality
	bool PlayRecoverIn();
	bool PlayRecoverLooped();
	bool PlayRecoverEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

	void setIsSuperSkill(bool isSuperSkill);
private:
	std::string m_lastUsedIdleAnim;
	bool m_bIsSuperSkill;
};


class EffectAnimRig_Plantainball : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_Plantainball, PopAnimRig, RtClass) {}

	bool PlayNormalFlightLooped();
	bool PlayPlantFoodFlightLooped();
	bool PlayPlantFoodFlightFuse(PopAnimRig::AnimStoppedReflectionDelegate onStop = PopAnimRig::AnimStoppedReflectionDelegate());
	bool PlayExplosion(PopAnimRig::AnimStoppedReflectionDelegate onStop = PopAnimRig::AnimStoppedReflectionDelegate());
    
    //Star Effect
    bool PlayStarPlantFoodFlightLooped();
	bool PlayStarPlantFoodFlightFuse(PopAnimRig::AnimStoppedReflectionDelegate onStop = PopAnimRig::AnimStoppedReflectionDelegate());
	bool PlayStarExplosion(PopAnimRig::AnimStoppedReflectionDelegate onStop = PopAnimRig::AnimStoppedReflectionDelegate());
	
	pvztime_t CalcFuseAnimLength();
	
private:
};


#endif
