//
//  Plant_HotDate.hpp
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 12/7/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef Plant_HotDate_h
#define Plant_HotDate_h

#include <stdio.h>
#include "Plant_SweetPotato.h"
#include "EffectAnimRig_JalapenoFireSquare.h"
#include "GridItemAnimation.h"

class ZombieType;

enum PlantAnimRigState_HotDate
{
	PLANTANIM_HOTDATE_DEATH = PLANTANIM_USERDEFINED
};

class HotDateProps : public SweetPotatoProps
{
public:
	RT_CLASS_DEFINE(HotDateProps, SweetPotatoProps, RtClass);
	
	HotDateProps()
	{
		skill5_duration = 0;
		skill5_baseDamage = 0;
	}
	
	ComponentWarmingRadiusProps NormalWarmingRadius;
	float skill2_up;
	float skill5_duration;
	float skill5_baseDamage;
};

class PlantHotDate : public PlantSweetPotato
{
public:
	RT_CLASS_DEFINE(PlantHotDate, PlantSweetPotato, RtClass);
	
	void Initialize() override;
	void UpdateActions() override;
	
	void ApplyPlantfood() override;
	bool CanApplyPlantfood() override;
	void CancelPlantfood() override;
	DamageInfo	TakeDamage(const DamageInfo& i_damage) override;
	void TakeSmashAttack(ZombiePtr i_srcZombie) override;
	
	void DoFlameBlast();
	// void DoKillPlant(DamageTypeFlags i_lastDamageType) override {}
	bool UpdateFlameBurst();
	void AddAttractionEffect(Zombie *i_zombie) override;

	bool IsInvincible() const override { return m_isInvincible; }
	bool CanBeTargeted() override;
	
protected:
	void onAnimStoppedCallback(const std::string& i_anim) override;
	
private:
	bool isBursting();
	
	bool m_isInvincible;
	bool m_flameAnimationComplete;
	pvztime_t m_explodedAtTime;
	int m_lastExplosionPropagationDistance;
	std::vector<BoardEntityPtr> m_damagedEntities;
	RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;
};

class PlantAnimRig_HotDate : public PlantAnimRig_SweetPotato
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_HotDate, PlantAnimRig_SweetPotato, RtClass);
	
	bool PlayIdleLooped() override;
	int CalcDamageStateCount() override;
	std::string getDamageIdleAnimationName() override { return "idle_damage"; }
	void PlayDeathAnimation(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	
protected:
	void onDamageStateIndexChanged(int i_oldDamageIndex) override;
};


class EffectAnimRig_HotDateFireSquare : public EffectAnimRig_JalapenoFireSquare
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_HotDateFireSquare, EffectAnimRig_JalapenoFireSquare, RtClass);

	EffectAnimRig_HotDateFireSquare();

	void setLastFireInfo(float i_damage, float i_duration, Point i_point, RtWeakPtr<class Plant> i_owner);
	
protected:
	virtual void onFireEnd() override;

private:
	float m_damage;
	float m_duration;
	Point m_point;
	RtWeakPtr<class Plant> m_owner;
};

enum HotDateFireState{
	PVZ_BEGIN_ENUM(HotDateFireState_),
	HotDateFireState_UNKNOWN,
	HotDateFireState_SPAWNING,
	HotDateFireState_IDLE,
	HotDateFireState_DISAPPEAR,
	HotDateFireState_DEAD,
    PVZ_END_ENUM(HotDateFireState_)
};

class HotDateLastFire : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(HotDateLastFire, GridItemAnimation, RtClass);

    HotDateLastFire();

    virtual int CalcRenderOrder() const override;

    void InitFire(const DamageInfo& i_damageInfo, float i_duration);

protected:
    virtual void onUpdate() override;
    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

    void setState(HotDateFireState i_state);
    void onAnimationDone(const std::string& i_tabel);
private:
    void takeEffect();
    HotDateFireState m_state;
    float m_duration;
    DamageInfo m_damageInfo;
    pvztime_t m_endTime;
    pvztime_t m_updateTime;
    RtWeakPtr<class Effect_PopAnim> m_effect;
};

#endif /* Plant_HotDate_hpp */
