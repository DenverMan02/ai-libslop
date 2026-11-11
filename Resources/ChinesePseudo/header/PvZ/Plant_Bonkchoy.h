//
//  Plant_Bonkchoy.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 2/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANT_BONKCHOY_H__
#define __PLANT_BONKCHOY_H__

#include "PlantFramework.h"
#include "GameSubSystem.h"

enum BonkchoyState
{
	BONKSTATE_IDLE = STATE_FRAMEWORK_BEGIN,
	BONKSTATE_ATTACKRIGHT,
	BONKSTATE_ATTACKLEFT,
	BONKSTATE_ATTACKBOTH_RIGHT,
	BONKSTATE_ATTACKBOTH_LEFT,
	BONKSTATE_PLANTFOOD,
};

class BonkchoySubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(BonkchoySubsystem, GameSubSystem, RtClass);

    BonkchoySubsystem();
    ~BonkchoySubsystem() override;

    void StunZombies(int i_col, int i_row);
private:
    bool shouldStun(Zombie* i_zombie);
    void onFlyingEnd(Zombie *i_zombie);
};

class PlantBonkchoy : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantBonkchoy, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual void UpdateActions() override;
	virtual void DoSpecial(int i_extraParam = 0) override;
	virtual Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void CancelPlantfood() override;
	virtual void UpdatePlantfood() override;

	virtual int CalcRenderOrder() override;

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
    
	bool m_searchingLeft;
    bool m_bKoHit;
	pvztime_t m_plantfoodDamageEndTime;
    
    int  m_iAttackCount;
    bool m_bAttackUppercut;
    bool m_bDoAvatarPull;
    int m_UppercutCount;
    bool m_IsSupercut;
};

#endif
