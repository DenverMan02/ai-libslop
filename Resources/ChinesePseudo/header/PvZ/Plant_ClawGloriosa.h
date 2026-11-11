#ifndef PLANT_CLAWGLORIOSA_H
#define PLANT_CLAWGLORIOSA_H

#include "PlantFramework.h"

STATE_ENUM_CHILD_BEGIN(ClawGloriosaState, PlantState)
	STATE_CLAWGLORIOSA_IDLE,
	STATE_CLAWGLORIOSA_SHIELD,
	STATE_CLAWGLORIOSA_RECOVERY,
	STATE_CLAWGLORIOSA_ATTACKING,
STATE_ENUM_END(ClawGloriosaState);


class ClawGloriosaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ClawGloriosaProps, PlantPropertySheet, RtClass);

	pvztime_t ClawCdBase = 10.0f;
	pvztime_t Level2CdReduced = 2.0f;
	pvztime_t Level3CdReduced = 2.0f;

	float ZombieHpImprovedFactorBase = 1.0f;
	float Level2HpFactorIncreased = 0.0f;
	float Level3HpFactorIncreased = 0.0f;

	float Level5PunchRate = 0.3f;

	float ClawDestOffsetX = 0.0f;
	float ClawDestOffsetY = 0.0f;
	float ClawPullSpeed = 0.5f;

	float SuckDestOffsetX = 0.0f;
	float SuckPullSpeed = 0.2f;
	float SuckStunTime = 2.0f;

	float PlantFoodPunchGrids = 5.0f;

	float EffectOffsetX = 0;
	float EffectOffsetY = 0;

	float MaxSuckZombies = 10;

	std::vector<std::string>  ZombieClawBlacklist;
};

class PlantClawGloriosa : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantClawGloriosa, PlantFramework, RtClass);

	void Initialize() override;
	void UpdateActions() override;

    void setState(uint i_state);

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;

	void onKilled(bool i_instantKill) override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    void onAnimStoppedCallback(const std::string& i_animLabel) override;

	bool CanBeTarget(ZombiePtr i_zombie);
	bool CanBeClawedByClawGloriosa(Zombie* i_zombie);
	bool CanBesuckedByClawGloriosa(Zombie* i_zombie);
	bool zombieIsBlacklisted(const Zombie* i_zombie) const;

	void FindTargetAndClaw();
	void FindTargetsAndBox();

	void ClawTargetZombie();
	void BoxTargetZombies();

	void PunchTargetZombies();

	void PlantFoodSuckTargets();
	void PlantFoodPunchTargets();

	float CalcZombieDPS(Zombie* i_zombie);

	void onApplyCondition(PlantConditions i_condition) override;
	void onEndCondition(PlantConditions i_condition) override;

	void ResetZombie(Zombie* i_zombie);

private:
	ZombiePtr m_closestZombie;
	ZombiePtr m_clawZombie;
	std::vector<RtWeakPtr<BoardEntity>> m_boxTargets;
	std::vector<RtWeakPtr<BoardEntity>> m_suckEntities;
	pvztime_t m_recoveryEndTime;
	bool m_isClawReady;
	bool m_isBoxReady;
	bool m_isPunchReady;
	SexyVector3 m_originalPosition;
};

class PlantAnimRig_ClawGloriosa : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_ClawGloriosa, PlantAnimRig, RtClass);

	bool PlayAttackAnim(const std::string& i_animLabel, const std::string& i_animCallback);

	bool PlayShieldAnim();
	bool PlayRecoveryAnim();

	void PlayPlantFood();
	void PlaySuckEffect();

	std::string getPlantFoodMainAnimName() override;
};




#endif
