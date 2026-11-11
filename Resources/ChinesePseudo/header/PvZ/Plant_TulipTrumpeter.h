/*
 * Plant_TulipTrumpeter.h
 *
 *  Created on: 2018-3-9
 *      Author: Administrator
 */

#ifndef PLANT_TULIPTRUMPETER_H_
#define PLANT_TULIPTRUMPETER_H_

#include "Plant.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "PlantStatefulFramework.hpp"

STATE_ENUM_CHILD_BEGIN(TulipState, PlantState)
	TULIPTRUMPETER_BEGINCURE,
	TULIPTRUMPETER_BEGINATTACK,
STATE_ENUM_END(TulipState);

enum TulipTrumpeterState
{
    PVZ_BEGIN_ENUM(TULIPTRUMPETERSTATE_),
    TULIPTRUMPETERSTATE_UNKNOWN,
    TULIPTRUMPETERSTATE_ATTACK,
    TULIPTRUMPETERSTATE_CURE,
    TULIPTRUMPETERSTATE_ATTACK_TO_CURE,
    TULIPTRUMPETERSTATE_CURE_TO_ATTACK,
    PVZ_END_ENUM(TULIPTRUMPETERSTATE_)
};

enum CureType
{
	NORMAL_CURE,
	PLANTFOOD_CURE
};

enum IdleState
{
	ATTACK_IDLE,
	CURE_IDLE
};

class TulipTrumpeterProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(TulipTrumpeterProps, PlantPropertySheet, RtClass);

	TulipTrumpeterProps()
	{
		cureValue = 0;
		Lvl5Rate = 0.0f;
		Lvl5ComboCount = 4;
		Lvl5CDRate = 10.0f;
		SpecialRate = 1.0f;
		ImprovedSpecialBonus = 1.0f;
		PlantfoodDuration = 3.0f;
		AvatarDuration = 5.0f;
		PlantfoodInterval = 1.0f;
		PlantfoodDamage = 100.0f;
		AvatarDamage = 200.0f;
		PlantfoodCureAmount = 100.0f;
		AvatarCureAmount = 200.0f;
	}

	int cureValue;
	float Lvl5Rate;
	int Lvl5ComboCount;
	float Lvl5CDRate;
	float SpecialRate;
	float ImprovedSpecialBonus;
	float PlantfoodDuration;
	float AvatarDuration;
	float PlantfoodInterval;
	float PlantfoodDamage;
	float AvatarDamage;
	float PlantfoodCureAmount;
	float AvatarCureAmount;
};

class TulipProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(TulipProjectile, Projectile, RtClass);

protected:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
};

class TulipSpecialProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(TulipSpecialProjectile, Projectile, RtClass);

protected:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
private:
	void ChangeZombieTeam(Zombie* i_zombie) const;
};

class PlantTulipTrumpeter : public PlantStatefulFramework
{
public:
	RT_CLASS_DEFINE(PlantTulipTrumpeter, PlantStatefulFramework, RtClass);

	PlantTulipTrumpeter();
	virtual ~PlantTulipTrumpeter() {}

	void 			Initialize() override;
	void 			PostInitialize() override;
	bool			CanApplyPlantfood() override;
	bool 			CanEndPlantfood() override;
	void 			ApplyPlantfood() override;
	void 			CancelPlantfood() override;
	void 			UpdatePlantfood() override;
	Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void			DoSpecial(int i_extraParam = 0) override;

	bool			CheckNeedCure();
	void 			setState(TulipTrumpeterState i_state);
	TulipTrumpeterState getState();
	void 			updateState();
	bool 			IsInState(uint32 state) const { return m_state == state; }
	virtual void	CurePlant(const PlantAction& i_fromAction) override;
	bool     		PlantCanBeCured(Plant * plant);
	bool 			FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	ZombiePtr 		FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
	virtual void	UpdateActions() override;
	bool			IgnoreCurrentAction(PlantActionType i_type);
	void			DelayPlantfood() override;
protected:
	OVERRIDE_STATE_ONENTER(PlantState, Idle);
	OVERRIDE_STATE_UPDATE(PlantState, Idle);

	DECLARE_PLANTSTATE_FUNCTIONS(PlantState, BeginCure);
	DECLARE_PLANTSTATE_FUNCTIONS(PlantState, BeginAttack);
private:
	void            doTakeCure(Plant * plant, CureType type);
	bool            IsPlantNeedCure();
	void 			DoLvl5Attack();
	void			DamageAndHeal();

	TulipTrumpeterState m_state;
	int m_comboCount;
	bool m_waitInitPlantfood;
	pvztime_t m_nextUpdate;
	pvztime_t m_endTime;
	bool m_delayPlantfood;
};

class PlantAnimRig_TulipTrumpeter : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_TulipTrumpeter, PlantAnimRig, RtClass);

	void PlayAttackBegin(AnimStoppedReflectionDelegate i_onAnimStopped = {});
	void PlayCureBegin(AnimStoppedReflectionDelegate i_onAnimStopped = {});
	void PlayCureSpawn();
	void SetIdleState(IdleState i_state) { m_idleState = i_state; }
	void SetLvl5Attack(bool i_lvl5) { m_lvl5Attack = i_lvl5; }
	bool GetLvl5Attack() const { return m_lvl5Attack; }
protected:
	void onPopAnimInitialized() override;
	std::string getIdleAnimationName() override;
	std::string getPlantFoodMainAnimName() override;
	std::string getAttackAnimationName() override;
private:
	IdleState m_idleState;
	bool m_lvl5Attack;
};


#endif /* PLANT_TULIPTRUMPETER_H_ */
