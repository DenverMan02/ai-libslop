//
//  Plant_Hammerflower.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 2/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_HAMMERFLOWER_H__
#define __PLANT_HAMMERFLOWER_H__

#include "PlantFramework.h"
#include "GameSubSystem.h"

enum HammerflowerState
{
	BONKSTATE_IDLE = STATE_FRAMEWORK_BEGIN,
	BONKSTATE_ATTACKRIGHT,
	BONKSTATE_ATTACKLEFT,
	BONKSTATE_ATTACKBOTH_RIGHT,
	BONKSTATE_ATTACKBOTH_LEFT,
	BONKSTATE_PLANTFOOD,
};

class HammerflowerSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(HammerflowerSubsystem, GameSubSystem, RtClass);

    HammerflowerSubsystem();
    ~HammerflowerSubsystem() override;

    void StunZombies(int i_col, int i_row, Plant* i_instigator);
private:
    bool shouldStun(Zombie* i_zombie);
    void onFlyingEnd(Zombie *i_zombie);
};

class PlantHammerflower : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantHammerflower, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual void UpdateActions() override;
	virtual void DoSpecial(int i_extraParam = 0) override;
	virtual Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void CancelPlantfood() override;
	virtual void UpdatePlantfood() override;
	bool CanBeTarget(ZombiePtr i_zombie);
	void StuckIntoGround(Zombie* i_zombie,const SexyVector3& i_boardPosition, pvztime_t i_stuckTime, pvztime_t i_underTime, float i_stuckHeight, pvztime_t i_intoGroundTime, bool hasStuckEffect);
	virtual int CalcRenderOrder() override;
	virtual void onStandaloneEffectFinishedCallback(class StandaloneEffect* i_effect) override;
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

	bool m_isWounded = false;
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
};

#endif
