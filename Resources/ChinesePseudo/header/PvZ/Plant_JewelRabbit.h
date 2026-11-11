/*
 * 	Plant_JewelRabbit.h
 *
 * 	Created on: 2022-10-8
 * 		Author: kkdud
 */

#ifndef __PLANT_JEWELRABBIT_H__
#define __PLANT_JEWELRABBIT_H__

#include "PlantFramework.h"
#include "TimeLine.h"
#include "ZombieTosser_SubSystem.h"

STATE_ENUM_CHILD_BEGIN(JewelRabbitState, PlantState)
	STATE_JEWELRABBIT_ATTACK_DOWN,
	STATE_JEWELRABBIT_ATTACK_DOWN_LOOP,
	STATE_JEWELRABBIT_ATTACK_BACK,
	STATE_JEWELRABBIT_RECOVERY,
	STATE_JEWELRABBIT_ATTACK_UP,
STATE_ENUM_END(JewelRabbitState);

class JewelRabbitProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(JewelRabbitProps, PlantPropertySheet, RtClass);

	float AttackIntervalBase = 17.5f;
	float AttackIntervalLv3 = 13.f;
	float AttackDamageAmountBase = 1200.f;
	float PlantfoodAttackInterval = 0.5f;
	float AttackLv5LandDamageRation = 0.1f;

	std::vector<std::string> CannotTossZombieBlackList;

};

class PlantJewelRabbit : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantJewelRabbit, PlantFramework, RtClass);

	void goBack(bool i_completeSecondStage);
	bool isValidZombie(Zombie* i_zombie);
	bool canTossOffZombie(Zombie* i_zombie);
	bool canTossOutZombie(Zombie* i_zombie);
	bool isZombieInTossBlackList(Zombie* i_zombie);
	bool isValidTargetPoint(Point i_point);
	bool canIdleZombie(Zombie* i_zombie);

	void damageFunction(std::vector<Zombie*> i_zombies);
	void damageFunction2(std::vector<Zombie*> i_zombies);

protected:
	void Initialize() override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void UpdatePlantfood() override;
	void CancelPlantfood() override;

	bool CanBeShoveled() override { return !isAttacking(); }
	void onDestroy() override;

private:
	void UpdateActions() override;
	void setState(JewelRabbitState i_newState);
	bool isInState(int i_state) { return m_plant->m_state == i_state; }
	bool isAttacking();

	void findTargetAndToss();
	void lockZombie(Zombie* i_zombie);
	void unlockZombie();
	void createPioneer();

	void onIdleAnimationDone();
	void onAttackDownAnimationDone();
	void onAttackDownLoopAnimationDone();
	void onAttackBackAnimationDone();
	void onAttackCooldownAnimationDone();
	void onAttackUpAnimationDone();

	void onAnimStoppedCallback(const std::string& i_anim) override;

	void findPlantfoodTargetAndToss();
	void createPlantfoodPioneer(Point i_gridPosition, std::string i_animLabel = "");

	pvztime_t  m_nextAttackTime = PVZ_EOT();
	bool m_hasAlreadyBack = false;
	bool m_halfCoolIntervalNext = false;
	bool isPlantFoodAttack = false;
	RtWeakPtr<Zombie> m_lockedZombie = nullptr;
	Point m_lockedPoint = Point(0, 0);
	pvztime_t m_plantfoodAttackTimer = PVZ_EOT();
	RtWeakPtr<class Effect_JewelRabbit_pioneer> m_pioneer = nullptr;
};

class PlantAnimRig_JewelRabbit : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_JewelRabbit, PlantAnimRig, RtClass);

	bool playSingleAnimation(std::string i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool playLoopAnimation(std::string i_animLabel);

	std::string getIdleAnimationName() { return "idle"; }
    std::string getPlantFoodOnAnimName() { return "plantfood_start"; }
	std::string getPlantFoodMainAnimName() { return "plantfood_loop"; }
    std::string getPlantFoodOffAnimName() { return "plantfood_over"; }

	std::string getNormalAttackDownAnimationName() { return "attack_start"; }
	std::string getNormalAttackDownLoopAnimationName() { return "attack_idle"; }
	std::string getNormalAttackCooldownAnimationName() { return "attack_idle"; }
	std::string getNormalAttackUpAnimationName() { return "attack_over"; }

	std::string getLv5AttackDownAnimationName() { return "attack_lv5_start"; }
	std::string getLv5AttackDownLoopAnimationName() { return "attack_lv5_loop"; }
	std::string getLv5AttackBackAnimationName() { return "attack_lv5_over"; }
	std::string getLv5AttackCooldownAnimationName() { return "attack_idle"; }
	std::string getLv5AttackUpAnimationName() { return "attack_over"; }

	std::string getLv5AttackSecondStageAnimationName() { return "attack_lv5_second_stage"; }
	std::string getLv5AttackBackHoldAnimationName() { return "attack_lv5_back_hole"; }
};

class Effect_JewelRabbit_pioneer: public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(Effect_JewelRabbit_pioneer, Effect_PopAnim, RtClass);

	void setAnimation(std::string i_pamStr, std::string i_animLabel);
	void setGridPosition(Point i_gridPosition);
	void setDamageFunc(std::function<void(std::vector<Zombie*>)> i_damageFunc) { m_damageFunc = i_damageFunc; }
	void setDamageFunc2(std::function<void(std::vector<Zombie*>)> i_damageFunc) { m_damageFunc2 = i_damageFunc; }
	void setRetreatFunc(std::function<void(bool)> i_retreatFunc) { m_retreatFunc = i_retreatFunc; }

private:
	void OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	void onAnimStopped(const std::string& i_animLabel) override;
	void damageTargets();
	void damageTargets2();
	void onStandaloneEffectFinishedCallback(class StandaloneEffect *i_effect);

	Point m_gridPosition = Point();
	std::function<void(std::vector<Zombie*>)> m_damageFunc = nullptr;
	std::function<void(std::vector<Zombie*>)> m_damageFunc2 = nullptr;
	std::function<void(bool)> m_retreatFunc = nullptr;
	bool m_hasCompletedSecondStage = false;
};

class JewelRabbitTossSubSystem : public ZombieTosserSubSystem
{
public:
	RT_CLASS_DEFINE(JewelRabbitTossSubSystem, ZombieTosserSubSystem, RtClass);

	void Update() override;
	void onUpdate();
	void tossZombieHorizontal(Zombie* i_zombie);
	void tossZombieParabolic(Zombie* i_zombie);
	void tossZombieOff(Zombie* i_zombie);

	void onLandedCallback(class Zombie* i_zombie);
	void playDustEffect(class Zombie* i_zombie);

	void setLandDamageRation(float i_r) { m_landDamageRatio = i_r; }

private:
	float m_landDamageRatio = 0.1f;
	std::vector<ZombiePtr> m_tossedOffZombies;
};

class Effect_JewelRabbit_hole: public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(Effect_JewelRabbit_hole, Effect_PopAnim, RtClass);

	void setGridPosition(Point i_gridPosition);
	bool canSwallowZombie(Zombie* i_zombie);

private:
	void onUpdate() override;
	void onDestroy() override;
	void updateSwallowingZombie();
	void disappear(float i_defer = 0.f);
	void swallowZombie(Zombie* i_zombie);
	void setupZombieToBeSwallowed(Zombie* i_zombie);
	void killZombie(Zombie* i_zombie);

	Point m_gridPosition = Point();
	bool m_isDying = false;
	pvztime_t m_deathTime = PVZ_EOT();
	pvztime_t m_disappearTime = PVZ_EOT();
	CurveSequence_SexyVector3 m_zombieSwallowCurve;
	ZombiePtr m_swallingZombie = nullptr;
};



#endif /* __PLANT_JEWELRABBIT_H__ */
