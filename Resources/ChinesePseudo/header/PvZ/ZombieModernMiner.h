/*
 * ZombieModernMiner.h
 *
 *  Created on: 2017-7-17
 *      Author: Administrator
 */

#ifndef ZOMBIEMODERNMINER_H_
#define ZOMBIEMODERNMINER_H_

#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"

enum MinnerState
{
    PVZ_BEGIN_ENUM(MINNERSTATE_),
    MINNERSTATE_UNKNOWN,
    MINNERSTATE_ABOVEGROUND,
    MINNERSTATE_BURROWING,
    MINNERSTATE_UNDERGROUNDING,
    MINNERSTATE_UNDERGROUND,
    MINNERSTATE_ABOVEGROUNDING,
    MINNERSTATE_TURNBACK,
    MINNERSTATE_WITHOUT_TOOL,
    PVZ_END_ENUM(MINNERSTATE_)
};

STATE_ENUM_CHILD_BEGIN(ZombieModernMinerState, ZombieState)
	ZS_MINER_Aboveground,
	ZS_MINER_Underground,
	ZS_MINER_DropTool,
STATE_ENUM_END(ZombieModernMinerState)

class ZombieModernMinerProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieModernMinerProps, ZombiePropertySheet, RtClass);
	ZombieModernMinerProps()
		: ExtraSpeed(8.0f)
	{}
	std::vector<std::string> TargetByWhitelist;
	std::vector<std::string> DamageWhileUnderground;
	float ExtraSpeed;
};

class ZombieModernMiner : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieModernMiner, Zombie, RtClass);

	ZombieModernMiner();
	void setState(MinnerState i_state);
	MinnerState getState();
	void updateState();

	bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;
	bool OverrideProjectileCollision(class Projectile* i_projectile) override;

protected:
	bool canBeDamagedByAttack(Plant* i_instigator, 	DamageTypeFlags i_damageFlags);
	void onUpdate() override;
	void TakeDamage(const DamageInfo& i_damage) override;
	class ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints) override;
	void onZombieInitialize() override;
	void onSetHelm() override;
	virtual void refreshAnimRigForHelm();
	bool CanBePulledHelm() override;

	DECLARE_STATE_FUNCTIONS(ZombieState, MinerAboveground);
	DECLARE_STATE_FUNCTIONS(ZombieState, MinerUnderground);
	DECLARE_STATE_FUNCTIONS(ZombieState, MinerDropTool);

	OVERRIDE_STATE_FUNCTIONS(ZombieState, Walk);
	OVERRIDE_STATE_ONEXIT(ZombieState, RiseFromGround);
	OVERRIDE_STATE_UPDATE(ZombieState, Idle);
	OVERRIDE_STATE_ONENTER(ZombieState, BleedingOut);

private:
	void onPlaceOnBoard() override;
	bool IsInState(uint32 state) const { return m_state == state; }
	void onUndergroundAnimDone(const std::string& i_animLabelName);
	void onAbovegroundAnimDone(const std::string& i_animLabelName);
	void onDropAnimDone(const std::string& i_animLabelName);
	void BurrowIntoGround(const SexyVector3& i_boardPosition, pvztime_t i_burrowTime, float i_burrowHeight);
	Plant* GetValidPlant(int i_x, int i_y);
	bool IsUnderground() const;
	bool canPushPlant(Plant* i_plant);
	void findAndPushPlant();
	void pushRow(int i_gridX, int i_gridY);
	void pushPlant(Plant* i_plant);

	bool m_isUnderground;
	MinnerState m_state;
	float m_burrowIntoGroundHeight;
	bool m_isBurrowBottom;
	pvztime_t m_burrowBottomTime;
	pvztime_t m_burrowingTime;
	float m_burrowInitHeight;
	double m_elapsedTime;
	bool m_hasTool;
};

class ZombieAnimRig_ModernMiner : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ModernMiner, ZombieAnimRig_Basic, RtClass);

	class ZombieParticle* DropHelm(HelmType i_helmType, class Zombie* i_zombie) override;
	void PlayUnderground(PopAnimRig::AnimStoppedReflectionDelegate i_onCompletion = PopAnimRig::AnimStoppedReflectionDelegate());
	void PlayAboveground(PopAnimRig::AnimStoppedReflectionDelegate i_onCompletion = PopAnimRig::AnimStoppedReflectionDelegate());
	void PlayDropTool(PopAnimRig::AnimStoppedReflectionDelegate i_onCompletion = PopAnimRig::AnimStoppedReflectionDelegate());
	void SetUnderground(bool i_underground) { m_underground = i_underground; }
	void SetBleeding(bool i_bleeding) { m_bleeding = i_bleeding; }

protected:
	void onPopAnimInitialized() override;
	void onUpdate() override;
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	const std::vector<std::string>& getFlagHandLayerNames() override;
	const std::vector<std::string>& getNoFlagHandLayerNames() override;
	const std::vector<std::string>& getMiningToolLayerNames() override;

	const std::string getIdleAnimationName() override;
	const std::string getWalkAnimationName() override;
	const std::string getEatAnimationName() override;
	const std::string getDieAnimationName() override;

private:
	bool m_hasTool = true;
	bool m_underground = false;
	bool m_bleeding = false;
};


#endif /* ZOMBIEMODERNMINER_H_ */
