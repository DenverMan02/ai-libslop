/*
 * ZombieSteamCoalMiner.h
 *
 *  Created on: 2018-5-24
 *      Author: Administrator
 */

#ifndef ZOMBIESTEAMCOALMINER_H_
#define ZOMBIESTEAMCOALMINER_H_

#include "GravestoneAnimRig.h"
#include "GridItemGravestone.h"
#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"

STATE_ENUM_CHILD_BEGIN(ZombieSteamCoalMinerState, ZombieState)
	ZS_Surfer_StartWork,
STATE_ENUM_END(ZombieSteamCoalMinerState);

class ZombieSteamCoalMinerProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieSteamCoalMinerProps, ZombiePropertySheet, RtClass);

	ZombieSteamCoalMinerProps()
	{
		TruckAttackRectOffsetX = 0;
		CoalItemName = "coal";
		MaxHelmHitCount = 5;
	};

	float TruckAttackRectOffsetX;
	std::string CoalItemName;
	int MaxHelmHitCount;
	std::vector<std::string> HelmHitPlantList;
};

class ZombieSteamCoalMiner : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieSteamCoalMiner, Zombie, RtClass);

	ZombieSteamCoalMiner();

	Rect CalcZombieAttackRect() override;

protected:
    // states
    DECLARE_STATE_FUNCTIONS(ZombieState, StartWork);
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);

	void onPlaceOnBoard() override;
	float getHeadDropFraction() const override;

	ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints) override;
	void onTakeHelmDamage(const DamageInfo& i_damageReceived) override;
	DamageInfo takeHelmDamage(const DamageInfo& i_incomingDamage) override;
	bool hasHeadParticle() const override;
	void onApplyCondition(ZombieConditions i_condition) override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

private:
	void updateTruckDamage();
	Point getDefaultTruckSpawnPosition();
	void StartWork(bool i_dropped, int i_helmHitpoints);
	void spawnTruckShatterEffect(const Sexy::Point& i_targetPosition, const std::string& i_animationName);
	bool canSpawnTruckAt(const Point& i_targetPosition) const;
	bool hasTruck();
	void onStartWorkAnimCompleted(const std::string&);
	void onBurnedTruckAnimCompleted(const std::string&);
	void onBrokenTruckAnimCompleted(const std::string&);
	bool canSpawnBoardAt(const Point& i_targetPosition) const;
	class GridItemCoalTruck* tryPlaceTruck(const Point& i_gridPosition);

	int m_specialHelmHitCount;
};

enum ZombieAnimRigState_SteamCoalMiner
{
	ZOMBIEANIM_STEAMCOALMINER_START_WORK = ZOMBIEANIM_USERDEFINED,
};

class ZombieAnimRig_SteamCoalMiner : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_SteamCoalMiner, ZombieAnimRig, RtClass);

	bool PlayStartWork(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

	void HideTruck();
	void UpdateTruckDamageState(int i_damageIndex);
	void PlayBurnedTruck(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	void PlayBrokenTruck(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

protected:
	const std::string getWalkAnimationName() override;
	const std::string getDieAnimationName() override;
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
	const bool getDieShouldBlend() override { return false; }

private:
	bool m_hasTruck = true;
};

class GridItemCoalTruckProps : public GridItemGravestonePropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemCoalTruckProps, GridItemGravestonePropertySheet, RtClass);
};

class GridItemCoalTruck : public GridItemGravestone
{
public:
	RT_CLASS_DEFINE(GridItemCoalTruck, GridItemGravestone, RtClass);

	void CalcDamageState();
	PlantingReason GetCantPlantReason() const override;

protected:
	void onGridItemInitialize() override;
	void KillGridItem() override;
private:
	void onAnimStoppedCallback(const std::string& i_animLabel);
	bool m_hasPlayDieAnim;
};

class CoalTruckAnimRig : public GravestoneAnimRig
{
public:
	RT_CLASS_DEFINE(CoalTruckAnimRig, GravestoneAnimRig, RtClass);

	CoalTruckAnimRig();

	void PlayStationary();

    void SetDamageState(int i_damageState, bool i_isAnimated) override;

    void onAnimStopped() override;

private:
    int m_queuedDamageStateAnim;
    bool m_inIntroAnim;
};

enum GridItemCoalState
{
    PVZ_BEGIN_ENUM(COALSTATE_),
    COALSTATE_UNKNOWN,
    COALSTATE_RESETTING,
    COALSTATE_BIRTH,
    COALSTATE_IDLE,
    COALSTATE_DEAD,
    PVZ_END_ENUM(COALSTATE_)
};

class GridItemCoalSteam : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemCoalSteam, GridItemAnimation, RtClass);

    GridItemCoalSteam();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(COALSTATE_IDLE); }
    void SetBirth() { setState(COALSTATE_BIRTH); }
    PlantingReason GetCantPlantReason() const;
    void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(GridItemCoalState i_state);
    GridItemCoalState GetState() const { return m_state; }

    virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

    virtual std::string GetAnimLabelName(GridItemCoalState i_state);

private:
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    void onDeathAnimStopped(const std::string &i_animName);
    void onBirthAnimStopped(const std::string &i_animName);
    pvztime_t m_creationTime;
    GridItemCoalState m_state;
};

class GridItemSteamCoalProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemSteamCoalProps, GridItemAnimationProps, RtClass);
    GridItemSteamCoalProps()
    : Lifetime(1.0)
    {}

    pvztime_t Lifetime;
};

#endif /* ZOMBIESTEAMCOALMINER_H_ */
