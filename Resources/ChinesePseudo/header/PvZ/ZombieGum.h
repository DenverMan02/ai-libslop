//
//  ZombieGum.h
//  PlantsVersusZombies2
//
//  Created by Moss, Evelyn on 11/27/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef ZombieGum_h
#define ZombieGum_h

#include <stdio.h>
#include "RtDb.h"
#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "GameSubSystem.h"



struct PoisonGumInfo
{
	PoisonGumInfo()
	:StartTime(PVZ_EOT()),
	StunDuration(5),
	Hypno(false),
	Level(1),
	Destroy(false)
	{
	}
	ZombiePtr Zombie;
	pvztime_t StartTime;
	pvztime_t StunDuration;
    bool Hypno;
	int Level;
	bool Destroy;
};

class GumPoisonSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(GumPoisonSubsystem, GameSubSystem, RtClass);

	virtual void Update() override;

	void ZombieEatPoisonGum(ZombiePtr i_zombie, bool i_hypno, int i_level, float i_stuckTime = 2.0f, float i_stunTime = 5.0f);
	void StartGasEffect(ZombiePtr i_zombie, float i_stunTime);
	void SpawnGasCloudOverZombie(Zombie* i_zombie, pvztime_t i_cloudDuration);
	bool IsZombieAffectedByGas(Zombie *i_zombie);

	std::vector<PoisonGumInfo>  InfoList;
};

class Effect_GumPoisonCloud : public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_GumPoisonCloud, Effect_PopAnim, RtClass);
    
    void StartCloud(Zombie* i_zombie, pvztime_t i_cloudDuration);
    
protected:
    void onUpdate() override;
    
private:
    RtWeakPtr<Zombie> m_targetZombie;
};


STATE_ENUM_CHILD_BEGIN(ZombieGumState, ZombieState)
	ZS_GUM_GumIntro,
	ZS_GUM_GumDeath,
STATE_ENUM_END(ZombieGumState)

class ZombieGumProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieGumProps, ZombiePropertySheet, RtClass);
	
	ZombieGumProps()
	{}
	
	float HypnoRate2;
	float HypnoRate3;
	DamageLifetime DamagePhases;
};

class ZombieGum : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieGum, Zombie, RtClass);
	ZombieGum();
	virtual ~ZombieGum();
	
	void TakeDamage(const DamageInfo& i_damage) override;
	void InitializeGum(float i_hitpoints, RtWeakPtr<Zombie> i_instigator, int i_level = 1);
	bool CanDropHead() const override { return false; }
	bool CanDropArm() const override { return false; }
	bool ShouldDrawShadow() const override { return false; }
	
protected:
	DECLARE_STATE_FUNCTIONS(ZombieState, GumIntro);
	DECLARE_STATE_FUNCTIONS(ZombieState, GumDeath);
	
	void onPlaceOnBoard() override;
	void onDestroy() override;
	void onUpdate() override;
	
	void onDeathAnimComplete(const std::string i_animLabel);
	void onIntroAnimComplete(const std::string i_animLabel);
	void onZombieConditionEnded(Zombie* i_zombie, int i_condition);
	void HypnoZombie(RtWeakPtr<Zombie> i_instigator);

private:
	RtWeakPtr<Zombie> m_owner;
	int m_damagePhase;
	bool m_playingDamageAnim;
	int m_plantLevel;
	int m_calculated;
};

class ZombieAnimRig_Gum : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Gum, ZombieAnimRig, RtClass);
};

#endif /* ZombieGum_h */
