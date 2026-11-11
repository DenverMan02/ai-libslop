//
//  PlantEnts.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 2/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_ENTS_H__
#define __PLANT_ENTS_H__

#include "PlantFramework.h"
#include "GameSubSystem.h"

enum EntsState
{
	BONKSTATE_IDLE = STATE_FRAMEWORK_BEGIN,
	BONKSTATE_ATTACKRIGHT,
	BONKSTATE_ATTACKLEFT,
	BONKSTATE_ATTACKBOTH_RIGHT,
	BONKSTATE_ATTACKBOTH_LEFT,
	BONKSTATE_PLANTFOOD,
};

class EntsSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(EntsSubsystem, GameSubSystem, RtClass);

    EntsSubsystem();
    ~EntsSubsystem() override;

    void StunZombies(int i_col, int i_row,float StunTime, Plant* i_instigator);
    void StunZombies2(int i_col, int i_row,float StunTime2, Plant* i_instigator);
private:
    float m_StunTime = 0;
    float m_StunTime2 = 0;
    bool shouldStun(Zombie* i_zombie);
    void onFlyingEnd(Zombie *i_zombie);
    void onFlyingEnd2(Zombie *i_zombie);
};

class EntsProps : public PlantPropertySheet
{
public:
RT_CLASS_DEFINE(EntsProps, PlantPropertySheet, RtClass);

	EntsProps()
	{
		RecoverHealth0 = 300;
		RecoverHealth = 400;
		RecoverHealthLv2 = 600;
		RecoverHealthLv3 = 900;
		RecoverHealthLv5 = 1500;
		MaxHealth = 6000;
		MaxHealthLv2 = 6000;
		MaxHealthLv3 = 6000;
		MaxHealthLv4 = 6000;
		MaxHealthLv5 = 6000;
		AmuletNum = 0;
		RecoverTriggerNum = 3;
		AttackDPS = 0;
		AttackDPSLv2 = 0;
		AttackDPSLv3 = 0;
		AttackDPSLv4 = 0;
		AttackDPSLv5 = 0;
		AttackDPSPF = 0;
		StunnedTime = 0;
		StunnedTime2 = 0;

	}

	float RecoverHealth0;
    float RecoverHealth;
    float RecoverHealthLv2;
    float RecoverHealthLv3;
    float RecoverHealthLv5;
    float MaxHealth;
    float MaxHealthLv2;
    float MaxHealthLv3;
    float MaxHealthLv4;
    float MaxHealthLv5;
    int AmuletNum;
    int RecoverTriggerNum;
    float AttackDPS;
    float AttackDPSLv2;
    float AttackDPSLv3;
    float AttackDPSLv4;
    float AttackDPSLv5;
    float AttackDPSPF;
    float StunnedTime;
    float StunnedTime2;

};

class PlantEnts : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantEnts, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual void UpdateActions() override;
	virtual void DoSpecial(int i_extraParam = 0) override;
	void DoAttackAnim(int type);
//	virtual Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
	virtual void TakeSmashAttack(ZombiePtr i_srcZombie) override;
	PopAnimRig::AnimStoppedReflectionDelegate GetAnimationStopDelegate();
	 void	 onAnimStoppedCallback(const std::string& i_animCommand) override;
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void CancelPlantfood() override;
	virtual void UpdatePlantfood() override;
	bool CanBeTarget(ZombiePtr i_zombie);
	void StuckIntoGround(Zombie* i_zombie,const SexyVector3& i_boardPosition, pvztime_t i_stuckTime, pvztime_t i_underTime, float i_stuckHeight, pvztime_t i_intoGroundTime, bool hasStuckEffect);
	virtual int CalcRenderOrder() override;
	virtual void onStandaloneEffectFinishedCallback(class StandaloneEffect* i_effect) override;
	bool IsInvincible() const override;
	float linkageCD = 0;
	bool m_invincible = false;
protected:
	virtual bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    
    //PVZ2_CHINESE_BEGIN
	virtual void DoSpecialForAvatarNormal() override;  // for avatar
    //PVZ2_CHINESE_END

private:
	bool FindTargetsAndPlayAttackAnim();
	bool MayUppercutTarget(ZombiePtr i_targetZombie);
	bool MayUppercutTarget(GridItem* i_targetGridItem);
	bool WouldKillTarget(ZombiePtr i_targetZombie);
	bool WouldKillTarget(GridItem* i_targetGridItem);
    
    void TossZombieByAttackUppercut(Zombie* i_zombie);

	GridItem* GetGridItemTarget(bool i_left);
	ZombiePtr GetZombieTarget(bool i_left);
	void CheckSupercut();
	void StunZombies();
	bool CanStunZombies();

	float plantEffectCount = 0;
	float m_AttackDPS = 0;
	float m_AttackDPSPF = 0;
	int m_AmuletNum = 0;
	float m_MaxHP = 0;
	float m_Maxrecover = 0;
	float m_interval = 0;
	bool m_isWounded = false; //大招攻击预备
	bool m_isWounded_common= false; //普通攻击预备
	bool m_searchingLeft;
    bool m_bKoHit;
	pvztime_t m_plantfoodDamageEndTime;
    bool m_isHeavyAttack = false;
    bool m_isLethal = true;
    float lethal_t = 0;
    float lethalInterval = 3;
    int  m_iAttackCount;
    float m_time;
    bool can_attack = 1;
    bool m_bAttackUppercut;
    bool m_bDoAvatarPull;
    int m_UppercutCount;
    bool m_IsSupercut;
    int pf_num = 0;
};

#endif
