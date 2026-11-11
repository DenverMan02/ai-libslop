//
//  ZombieDarkWizard.h
//  PlantsVersusZombies2
//
//  Created by Kristen Kho on 10/8/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieDarkWizard_h
#define PlantsVersusZombies2_ZombieDarkWizard_h

#include "DamageInfo.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "RestrictionSet.h"

class BoardEntity;
class Effect_PopAnim;
class Plant;

STATE_ENUM_CHILD_BEGIN(ZombieState_DarkWizard, ZombieState)
    ZS_DARKWIZARD_Casting,
STATE_ENUM_END(ZombieState_DarkWizard)

struct SheepInfo
{
	SheepInfo()
	{

	}

	SheepInfo(const RtWeakPtr<class Plant>& i_plant, const RtWeakPtr<Effect_PopAnim>& i_sheep)
	: Plant(i_plant)
	, Sheep(i_sheep)
	{

	}

	RtWeakPtr<class Plant> Plant;
	RtWeakPtr<Effect_PopAnim> Sheep;
};

class ZombieDarkWizardProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieDarkWizardProps, ZombiePropertySheet, RtClass);
    
    ZombieDarkWizardProps()
    {
        SoundOnSpellActivate = "Play_RaZombie_WandActivate";
    }
    std::string SheepPopAnim;
    Sexy::Point SheepOffset;
    
    std::string SoundOnSpellActivate;
    ValueRange TimeBeforeFirstCasting;
    ValueRange TimeBetweenCasting;
    std::string ProjectilePopAnim;
    
    PlantRestrictionSet TargetablePlantTypes;
};

class ZombieDarkWizard : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieDarkWizard, Zombie, RtClass);

	bool HasSheepedPlantInRow(int i_row) const;

protected:
	OVERRIDE_STATE_UPDATE(ZombieState, Idle);
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);
	DECLARE_STATE_FUNCTIONS(ZombieState, Casting);

	void onUpdate() override;

private:
    void onZombieInitialize() override;
	void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
	void onMowedDown() override;
	void onDestroy() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

    void revertSheepPlants();
	bool isValidSpellTarget(PlantGroup* plantGroup);
	bool isValidSpellTarget(Zombie* zombie);
//	Plant* getValidSpellTarget();
	BoardEntity* getValidSpellTarget();
    void onAnimationDone(const std::string& i_animName);
	void onSpellImpact(BoardEntity* i_impactedEntity);

	pvztime_t m_nextCastTime = PVZ_EOT();
	std::vector<RtWeakPtr<BoardEntity> > m_plantGroups;
	std::vector<RtWeakPtr<Zombie> > m_zombies;
	std::vector<SheepInfo> m_sheep;
};

#endif
