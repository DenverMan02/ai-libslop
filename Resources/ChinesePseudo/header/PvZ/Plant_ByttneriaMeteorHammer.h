/*
 * 	Plant_ByttneriaMeteorHammer.h
 *
 * 	Created on: 2022-7-5
 * 		Author: kkdud
 */

#ifndef __PLANT_BYTTNERIAMETEORHAMMER_H__
#define __PLANT_BYTTNERIAMETEORHAMMER_H__

#include "PlantFramework.h"
#include "ZombieTosser_SubSystem.h"


STATE_ENUM_CHILD_BEGIN(ByttneriaMeteorHammerState, PlantState)
	HAMMER_STATE_CHARGING,
	HAMMER_STATE_ATTACK,
	HAMMER_STATE_COOLDOWN,
STATE_ENUM_END(ByttneriaMeteorHammerState);

enum ByttneriaMeteorHammerAttackType
{
	ATTACK_TYPE_DAMAGE_NORMAL,
	ATTACK_TYPE_DAMAGE_CHARGE,
	ATTACK_TYPE_PLANTFOOD,
	ATTACK_TYPE_AVATAR_FIRST,
	ATTACK_TYPE_AVATAR_SECOND
};

class ByttneriaMeteorHammerProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ByttneriaMeteorHammerProps, PlantPropertySheet, RtClass);

	float ChargeDuration = 10.f;
	float ChargeDurationLv2 = 9.f;
	float ChargeDurationLv3 = 8.f;

	float NormalAttackBaseDamageAmount = 50.f;
	float ChargeAttackBaseDamageAmount = 600.f;
	float PlantfoodAttackBaseDamageAmount = 800.f;
	float AvatarAttackBaseDamageAmount = 600.f;

	float NormalAttackCooldownDuration = 2.f;
};

class PlantByttneriaMeteorHammer : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantByttneriaMeteorHammer, PlantFramework, RtClass);

    void Initialize() override;
    void UpdateActions() override;
    void setState(uint i_plantState);
    void onAnimStoppedCallback(const std::string& name) override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

    void takeAttack(ByttneriaMeteorHammerAttackType i_attackType);
    void playGroundCracksEffect();
    void playAShockWaveEffect();
    void addHitEffect();

    void initValidTargetPoints();
    void getValidAttackRects(std::vector<Rect>& o_rects);

    bool isValidTarget(RtWeakPtr<BoardEntity> i_entity);

	bool canFindTarget();
	void findTargets(std::vector<BoardEntity*>& o_entityList);
	void reserveTheBestTarget(std::vector<BoardEntity*>& o_entityList);
	RtWeakPtr<BoardEntity> findChargeTarget();
	int getChargeAttackIndex();

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	void UpdatePlantfood() override;
	bool FindTargetAndFire(PlantWeapon i_plantWeapon) override {}

	void startCharging();

private:
    float 		m_chargeDuration;
    pvztime_t 	m_endTime;
    bool 		m_isTheChargingCompleted;
    bool 		m_isChargeingContinued;

    std::vector<Point> m_validTargetPoints;
    RtWeakPtr<BoardEntity> m_chargeTarget;

};

class PlantAnimRig_ByttneriaMeteorHammer : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_ByttneriaMeteorHammer, PlantAnimRig, RtClass){}

    bool playCharge(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    bool playCharging(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    bool playChargingFast();
    bool playNormalAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    bool playChargeAttack(int i_index, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
    bool playChargeAttackLv5(int i_index, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

    std::string getChargeStartAnim() { return "idle_start"; }
    std::string getChargingAnim() { return "attack_loop_slowly"; }
    std::string getChargingFastlyAnim() { return "attack_loop_fast"; }
    std::string getNormalAttackAnim() { return "attack"; }
    std::string getChargeAttackPrefix() { return "attack_go"; }
    std::string getChargeAttackAnim(int i_index) { return getChargeAttackPrefix() + StrFormat("_%d", i_index); }
    std::string getChargeAttackLv5Prefix() { return "attack_lv5_go"; }
    std::string getChargeAttackLv5Anim(int i_index) { return getChargeAttackLv5Prefix() + StrFormat("_%d", i_index); }

    std::string getPlantFoodMainAnimName() override;

};

class ByttneriaMeteorHammerTossSubSystem : public ZombieTosserSubSystem
{
	RT_CLASS_DEFINE(ByttneriaMeteorHammerTossSubSystem, ZombieTosserSubSystem, RtClass);

	void Update() override;
	void onUpdate();
	void tossZombie(class Zombie* i_zombie, SexyVector3 i_attackerPosition, std::function<void(BoardEntity*)> i_onUpdateFunction = nullptr);
	void onLandedCallback(class Zombie* i_zombie);
	void refreshMap();

	std::map<RtWeakPtr<Zombie>, std::function<void(BoardEntity*)> > m_zombieOnUpdateFunctionMap;
	std::map<RtWeakPtr<Zombie>, std::vector<RtWeakPtr<BoardEntity>>> m_zombieHasCollideEntityMap;
};

#endif /* __PLANT_BYTTNERIAMETEORHAMMER_H__ */
