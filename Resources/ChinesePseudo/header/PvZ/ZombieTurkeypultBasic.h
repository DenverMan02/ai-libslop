//
//  ZombieTurkeypultBasic.h
//  PlantsVersusZombies2
//
//  Created by Moss, Evelyn on 5/27/20.
//  Copyright 漏 2020 PopCap Games. All rights reserved.
//

#ifndef ZombieTurkeypultBasic_h
#define ZombieTurkeypultBasic_h

#include "StateMachine.h"
#include "Zombie.h"

class ZombieTurkeypultBasic : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieTurkeypultBasic, Zombie, RtClass);

	virtual void onInitialized() override;
	virtual void CreateZombieLevelEffect(bool i_street) override;
//	void SetPlantFamilies(std::vector<std::string> i_families, float i_resistancePiercing) override { m_plantFamilies = i_families; m_resistancePiercingOverride = i_resistancePiercing; }
	void TurkeyRefreshStats();

protected:
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Walk);
	DamageInfo calcEatDamage() override;
	bool allowAshState() const override;
	virtual void onUpdate() override;
	virtual void TakeDamage(const DamageInfo& i_damage) override;

private:
//	std::vector<std::string> m_plantFamilies;
//	float m_resistancePiercingOverride;
	pvztime_t m_time;
};

class ZombieAnimRig_TurkeypultBase : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_TurkeypultBase, ZombieAnimRig, RtClass);
};
/*
class ZombieAnimRig_TurkeypultTurkzilla : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_TurkeypultTurkzilla, ZombieAnimRig, RtClass);
};
*/
#endif /* ZombieTurkeypultBasic_h */
