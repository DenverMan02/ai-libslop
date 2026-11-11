/*
 * GridItemRenaiStatue.h
 *
 *  Created on: 2019-8-7
 *      Author: Administrator
 */

#ifndef GRIDITEMRENAISTATUE_H_
#define GRIDITEMRENAISTATUE_H_

#include "GridItemBoardEntityConditionTarget.h"

enum StatueState
{
	PVZ_BEGIN_ENUM(STATUESTATE_),
	STATUESTATE_IDLE,
	STATUESTATE_CARVING,
	STATUESTATE_REVIVING,
	PVZ_END_ENUM(STATUESTATE_)
};

enum StatueStage
{
	STAGE_LEVEL_1,
	STAGE_LEVEL_2,
	STAGE_LEVEL_3,
	STAGE_LEVEL_4,
	STAGE_LEVEL_COUNT
};

class EffectAnimRig_ZombieStatue : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_ZombieStatue, PopAnimRig, RtClass);

	EffectAnimRig_ZombieStatue();

    virtual ~EffectAnimRig_ZombieStatue();

    void PlayIdle();
    void PlayCarve(StatueStage i_stage);
    void PlayRevive(StatueStage i_stage);
};

class GridItemRenaiStatueProps : public GridItemBreakableTargetProps
{
public:
	RT_CLASS_DEFINE(GridItemRenaiStatueProps, GridItemBreakableTargetProps, RtClass);

	GridItemRenaiStatueProps()
	{
		ZombieTypeName = "";
		CarveTime = 0.0f;
		ShakeOffset = 0.0f;
	}

	std::string ZombieTypeName;
	float CarveTime;
	float ShakeOffset;
};

class GridItemRenaiHalfStatueProps : public GridItemRenaiStatueProps
{
public:
	RT_CLASS_DEFINE(GridItemRenaiHalfStatueProps, GridItemRenaiStatueProps, RtClass);

	GridItemRenaiHalfStatueProps()
	{
		ZombiePopAnim = "";
	}

	std::string ZombiePopAnim;
};

class GridItemRenaiStatue : public GridItemBreakableTarget
{
public:
	RT_CLASS_DEFINE(GridItemRenaiStatue, GridItemBreakableTarget, RtClass);
	GridItemRenaiStatue();
	virtual ~GridItemRenaiStatue();
	void registerForEvents() override;
	bool IsDamageableByPlants() const override { return true; }
	PlantingReason GetCantPlantReason() const;
	void GatherPlantingRestrictions(const PlantType *i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	virtual void TryRevive();
	virtual void TryCarve();
	virtual void TryRecover();
	void SetWaveNumber(int i_number) { m_waveNumber = i_number; }
	void setState(StatueState i_state);
	bool IsDamageable() const override;
	virtual bool CanBeCarved() { return false; }
	virtual bool HasGravity() override;
	float GetCarveTime();
	bool IsCarving();
	virtual void OnChangeState(StatueState i_state);
	void SetCurrentStage(StatueStage i_stage) { m_currentStage = i_stage; }
	StatueStage GetCurrentStage() { return m_currentStage; }
	virtual std::string GetRockEffectName();
	virtual void PlayRockEffect();
	void PlayDustEffect();

protected:
	void onPostLoad() override;
	virtual void onAnimEnded(const std::string &i_animLabel);
	virtual void onPopAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_params);
	void onGridItemInitialize() override;
	void onUpdate() override;
	bool IsInState(uint32 state) const { return m_state == state; }
	void onDestroy() override;

private:
	void onZombieSpawned(class Zombie * i_zombie);
	void SpawnZombies();
	void CreateMinorEffects();
	void DisableEffects();
	void onDustEffectDone(const std::string& i_animName);

	int m_waveNumber;
	StatueState m_state;
	StatueStage m_currentStage;
	RtWeakPtr<Effect_PopAnim> m_rockEffect;
	RtWeakPtr<Effect_PopAnim> m_dustEffect;
	float m_shakeOffset;
};

class GridItemRenaiStatueAnimRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemRenaiStatueAnimRig, PopAnimRig, RtClass);

	virtual void PlayRevive(StatueStage i_stage, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	virtual void PlayCarve(StatueStage i_stage, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped) {}
	virtual void PlayIdle();
};

class GridItemRenaiStatueHalf : public GridItemRenaiStatue
{
public:
	RT_CLASS_DEFINE(GridItemRenaiStatueHalf, GridItemRenaiStatue, RtClass);

	virtual ~GridItemRenaiStatueHalf();

	bool CanBeCarved() override;

protected:
	void onGridItemInitialize() override;
	void onAnimEnded(const std::string &i_animLabel) override;
	void onUpdate() override;
	void onDraw(class Sexy::Graphics* i_g) override;
	void OnChangeState(StatueState i_state) override;
private:
	RtWeakPtr<class EffectAnimRig_ZombieStatue> m_zombieRig;
};

class GridItemRenaiStatueHalfAnimRig : public GridItemRenaiStatueAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemRenaiStatueHalfAnimRig, GridItemRenaiStatueAnimRig, RtClass);

	void PlayCarve(StatueStage i_stage, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped) override;
	void PlayRevive(StatueStage i_stage, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped) override;
};

namespace Message
{
    void NotifyStatueFinishCarve(GridItemRenaiStatue* i_statue);
}

#endif /* GRIDITEMRENAISTATUE_H_ */
