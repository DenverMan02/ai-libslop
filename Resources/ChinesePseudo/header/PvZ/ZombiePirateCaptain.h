//
//  ZombiePirateCaptain.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/11/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombiePirateCaptain_h
#define PlantsVersusZombies2_ZombiePirateCaptain_h

#include "Zombie.h"

class ZombiePirateCaptain : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePirateCaptain, Zombie, RtClass);
	
	void OnParrotReturned();
	bool HasBird() { return m_parrotShown; }
	
	static bool CanParrotPlant(PlantPtr targetPlant);
	static PlantPtr GetPlantToParrot(PlantGroupPtr i_plantGroup);

protected:
	virtual void onZombieInitialize() override;
	virtual void onPlaceOnBoard() override;
	virtual void onLostHead() override;
	virtual void onTakeFatalDamage(const DamageInfo& i_lastReceivedDamage) override;
    void onApplyCondition(ZombieConditions i_condition) override;
	
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
	
private:
	void checkForParrotRelease();
	void releaseParrot(class Plant* i_targetPlant);
	void showParrot(bool i_show);
	class Plant* findPlantForParrotToAttack();
	
	pvztime_t m_parrotLaunchTime;
	float m_parrotHealth;
	ZombiePtr m_parrotPtr;
	bool m_parrotShown;
	
	bool m_hasParrotLaunched;
};

#endif
