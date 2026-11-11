//
//  Plant_Pokra.h
//  PlantsVersusZombies2
//
//  Created by Moss, Evelyn on 5/13/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef Plant_Pokra_h
#define Plant_Pokra_h

#include "PlantFramework.h"
#include "RtDb.h"
#include "BoardEntity.h"
#include "Projectile.h"
#include "Plant.h"
#include "RtObject.h"
#include "Zombie.h"
#include <string>

enum PlantAnimRigState_Pokra
{
	PLANTANIM_POKRA_ATTACKING = PLANTANIM_USERDEFINED
};

enum AttackPhase
{
	ATTACK_PHASE_ONE,
	ATTACK_PHASE_TWO,
	ATTACK_PHASE_THREE,
	ATTACK_PHASE_FOUR,
	ATTACK_PHASE_MAX,
};

class PlantAnimRig_Pokra : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Pokra, PlantAnimRig, RtClass);
	
	bool PlaySingleJabStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlaySingleJabLoop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlaySingleJabEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayDoubleJabStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayDoubleJabLoop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayDoubleJabEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayTripleJabLoop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}); // loop 2 + loop 1
	bool PlayQuadrupleJabLoop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {}); // loop 2 + loop 2

	// zhousen
	bool PlayLevel2JabStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayLevel2JabLoop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayLevel2JabEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	bool PlayLevel5(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});

	bool PlayProjectileFire(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	
protected:
	void finishTripleJabLoop(const std::string& i_animLabel);
	void finishQuadrupleJabLoop(const std::string& i_animLabel);
	void clearDeferredDelegate();
	
private:
	PopAnimRig::AnimStoppedReflectionDelegate m_deferredAnimStoppedDelegate;
};

enum PokraState
{
	POKRA_IDLE = STATE_FRAMEWORK_BEGIN,
	POKRA_ATTACKING,
	POKRA_RECOVERY,
	POKRA_PLANTFOOD,
};

enum AttackState
{
	ATTACK_NORMAL,
	ATTACK_LEVEL2,
	ATTACK_LEVEL5,
};

class PokraProps : PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PokraProps, PlantPropertySheet, RtClass);
	
	PokraProps()
	{
		RecoveryTime = 1.0f;
		SlowDuration = 0.5f;
		SlowDurationFinal = 1.5f;
		SlowDurationPF = 1.0f;
		TimeBetweenAttacks = 0.f;
		PhaseOneAttackRateOverrideValue = 1.0f;
		PhaseTwoAttackRateOverrideValue = 1.0f;
		PhaseThreeAttackRateOverrideValue = 1.0f;
		PhaseFourAttackRateOverrideValue = 1.0f;
		BasicProjectileAttackRateOverrideValue = 1.0f;
		PlantfoodProjectileAttackRateOverrideValue = 1.0f;
		Level2JabAttackRatio = 0.2f;
		Level5AfterLevel2JabAttackRatio = 0.1f;
		Level5JabAttackRatio = 0.3f;
		PlantFoodPlayCount1 = 3;
		PlantFoodPlayCount2 = 4;
		PlantFoodPlayCount3 = 5;
		PlantFoodPlayCount4 = 5;
		PlantFoodPlayCount5 = 6;
		Level2HitDamage = 120;
		Level5HitDamage = 300;
	}
	
	float 	RecoveryTime;
	float 	SlowDuration;
	float 	SlowDurationFinal;
	float 	SlowDurationPF;
	float	TimeBetweenAttacks;
	
	float	PhaseOneAttackRateOverrideValue;
	float	PhaseTwoAttackRateOverrideValue;
	float	PhaseThreeAttackRateOverrideValue;
	float	PhaseFourAttackRateOverrideValue;
	float	BasicProjectileAttackRateOverrideValue;
	float	PlantfoodProjectileAttackRateOverrideValue;

	// zhousen
	float Level2JabAttackRatio;// level2 skill attack ratio
	float Level5AfterLevel2JabAttackRatio;// level5 skill attack ratio after level2 skill
	float Level5JabAttackRatio;// level5 skill attack ratio

	int PlantFoodPlayCount1;// level 1 plantfood play count
	int PlantFoodPlayCount2;// level 2 plantfood play count
	int PlantFoodPlayCount3;// level 3 plantfood play count
	int PlantFoodPlayCount4;// level 4 plantfood play count
	int PlantFoodPlayCount5;// level 5 plantfood play count

	int Level2HitDamage;// level2 hit damage
	int Level5HitDamage;// level5 hit damage
};

class PlantPokra : PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantPokra, PlantFramework, RtClass);
	
	PlantPokra();
	
	void Initialize() override;
	void UpdateActions() override;
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	int	GetPlantFoodPlayCount() override;
	
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

	
protected:
	void setState(PokraState i_state);
	void advanceAttackPhase();
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

private:
	bool hasTarget();
	void doAttack();
	void fireProjectile();
	void createHitEffect(std::string &i_animationName, BoardEntity* i_target);
	
	pvztime_t m_recoveryEndTime;
	AttackPhase m_currentPhase;
	AttackState m_attackState;// check attack is in normal state or level2 or level5
	pvztime_t m_midAttackPauseEndTime;
	float m_newAvatarBoostJabRate;
};

class PokraProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(PokraProjectile, Projectile, RtClass);
	
	bool OnCollideEntity(BoardEntity* i_entity) override;
	
protected:
	void onProjectileInitialized() override;
	void onUpdate(pvztime_t i_dt) override;
    void onSetInstigator(BoardEntity* i_instigator) override;
	void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;

private:
    void spawnOrRefreshPoisonTiles();// spawn poison mist
    void addPoisonTileToBoard(Point& i_square);
	
private:
	std::vector<BoardEntityPtr> m_targetsAlreadyHit;
	bool m_isAvatar;
	float m_ExtraDPSRatio;
	bool m_isPlantfood;
};

// avatar poison mist
class PoisonMistGridItem : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(PoisonMistGridItem, GridItemAnimation, RtClass);
    
    void ResetTimer();
	void InitializeValues(bool isAvatar);
    void InitializeValues(float i_gridLifeTime, float i_gridDuration, float i_gridSpeedPercentDecrease, float i_gridDPS, float i_resistancePiercing);
	float GetResistancePiercing()  { return m_resistancePiercing; }
    void SetAvatar(bool isAvatar) { m_isAvatar = isAvatar; }

protected:
    int CalcRenderOrder() const override;
    void onGridItemInitialize() override;
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    virtual ~PoisonMistGridItem() {}
    void onUpdate() override;
	
private:
    pvztime_t m_destroyTime;
    
    void applyConditions();
    void fadeTile();
    
    bool m_isAvatar;
    float m_gridLifetime, m_gridDuration, m_gridSpeedPercentDecrease, m_gridDPS, m_resistancePiercing;
};

// avatar poison mist props
class PoisonMistGridItemProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(PoisonMistGridItemProps, GridItemAnimationProps, RtClass);
    
    PoisonMistGridItemProps()
    {
		LifeTime = 2.0f;
		PoisonDuration = 2.0f;
		PoisonDPS = 2.0f;
    }

	float LifeTime;// mist life time
	float PoisonDuration;// mist poison effect time
	float PoisonDPS;// mist pison effect damage
};


#endif /* Plant_Pokra_h */
