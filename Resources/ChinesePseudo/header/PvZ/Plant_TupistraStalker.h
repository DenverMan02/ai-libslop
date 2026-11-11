/*
 * Plant_TupistraStalker.h
 *
 *  Created on: 2020-8-31
 *      Author: Administrator
 */

#ifndef PLANT_TUPISTRASTALKER_H_
#define PLANT_TUPISTRASTALKER_H_

#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantAnimRig.h"
#include "GridItemAnimation.h"

class EffectTupistraAttack : public Effect_PopAnim
{
public:

    RT_CLASS_DEFINE(EffectTupistraAttack, Effect_PopAnim, RtClass);

    void OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    void SetOwner(PlantPtr i_owner) { m_owner = i_owner; }

private:
    PlantPtr m_owner;
};

class PlantTupistraStalker : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantTupistraStalker, PlantFramework, RtClass);

	~PlantTupistraStalker();

	void Initialize() override;
	void UpdateActions() override;

    bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
    void CancelPlantfood() override;

    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

    BoardEntityHeight GetEntityHeight() const override;

    void CallAttack();
    void CallPlantfoodAttack();
    void onStandaloneEffectFinishedCallback(class StandaloneEffect *i_effect) override;
    void TakeSmashAttack(ZombiePtr i_srcZombie) override;

protected:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

private:
	enum State
	{
		STATE_ATTACK = STATE_FRAMEWORK_BEGIN,
		STATE_SUBMERGING,
        STATE_SUBMERGED,
        STATE_RISING,
        STATE_JUMPING
	};

	void tryCreateEffectAttack(bool i_plantfood);
	RtWeakPtr<class EffectTupistraAttack> createEffectAttack(bool i_plantfood);
	void tryCreateEffectSpin(bool i_plantfood);
	RtWeakPtr<class Effect_PopAnim> createEffectSpin(bool i_plantfood);
	void tryAttack();
    void setState(const uint i_state);
    bool CanFireZombie(const Zombie* i_zombie) const;
    bool targetFound();
    void getAttackLocations(std::vector<Point>& i_locs, int i_index);
    void handleAttack(int i_index);
    void dealDamage(int i_col, int i_row);
    void dealAreaDamage();
    void createDamageEffect(int i_col, int i_row);
    float getRestTime();
    float getReducedTime();
    void spawnLeaf(int i_col, int i_row);
    void trySpawnLeaves();

    pvztime_t m_lastAttack;
    int m_attackIndex;
    int m_attackCount;
    RtWeakPtr<class EffectTupistraAttack> m_effectRig;
    RtWeakPtr<class Effect_PopAnim> m_effectRigSpin;
};

class PlantAnimRig_TupistraStalker : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_TupistraStalker, PlantAnimRig, RtClass);

	void onPopAnimInitialized() override;
    bool PlayPreviewAnim(bool bHideLayer) override;
    void setHasSubmerged(bool i_submerged) { m_submerged = i_submerged; }

    void Jumping(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped, bool i_super);
	void Submerging(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void LoopAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped, bool i_super);
	void Rising(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

protected:
	std::string getPlantFoodOnAnimName() override { return "plantfood_on"; }
	std::string getPlantFoodOffAnimName() override { return "plantfood_off"; }

private:
    std::string getIdleAnimationName() override;

    bool m_submerged = true;
};

class TupistraStalkerProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(TupistraStalkerProps, PlantPropertySheet, RtClass);

	TupistraStalkerProps()
	{
        BaseDamage = 300.0f;
        BaseRestTime = 3.0f;
        ReducedLaunchDelay = 0.0f;
        ImprovedReducedBonus = 1.0f;
        PlantfoodDamage = 600.0f;
        SpawnItemName = "leaf";
	}

    float BaseDamage;
    float BaseRestTime;
    float ReducedLaunchDelay;
    float ImprovedReducedBonus;
    float PlantfoodDamage;
    std::string SpawnItemName;
};

enum GridItemTupistraLeafState
{
    PVZ_BEGIN_ENUM(LEAFSTATE_),
    LEAFSTATE_UNKNOWN,
    LEAFSTATE_RESETTING,
    LEAFSTATE_IDLE,
    LEAFSTATE_DEAD,
    PVZ_END_ENUM(LEAFSTATE_)
};

class GridItemTupistraLeaf : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemTupistraLeaf, GridItemAnimation, RtClass);

    GridItemTupistraLeaf();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(LEAFSTATE_IDLE); }
    void SetAttackRate(float i_rate) { m_attackRate = i_rate; }
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(GridItemTupistraLeafState i_state);
    void tryAffectZombies();

    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    void onResetFinished(const std::string &i_animName);
    void onDeadFinished(const std::string &i_animName);

private:
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    pvztime_t m_creationTime;
    GridItemTupistraLeafState m_state;
    pvztime_t m_affectTime;
    float m_attackRate;
};

class GridItemTupistraLeafProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemTupistraLeafProps, GridItemAnimationProps, RtClass);
    GridItemTupistraLeafProps()
    : Lifetime(1.0)
    , AffectDamage(0.0f)
    , AffectInterval(1.0f)
    {}

    pvztime_t Lifetime;
    std::vector<std::string> ZombieBlacklist;
    float AffectDamage;
    float AffectInterval;
};

#endif /* PLANT_TUPISTRASTALKER_H_ */
