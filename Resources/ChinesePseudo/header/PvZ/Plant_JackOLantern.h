//
//  Plant_JackOLantern.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 9/4/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_JackOLantern__
#define __PlantsVersusZombies2__Plant_JackOLantern__

#include "ComponentWarmingRadius.h"
#include "DamageInfo.h"
#include "GridItemAnimation.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "Zombie.h"


struct JackOLanternGhostParam {
    pvztime_t GhostLanternDurationSmall;
    pvztime_t GhostLanternDurationMid;
    pvztime_t GhostLanternDurationBig;
    pvztime_t GhostLanternFireDuration;
    float GhostLanternFireDamage;
};

class JackOLanternGhost : public Projectile
{
public:
	enum {
		Ghost_Idle,
		Ghost_Moving,
		Ghost_Return,
		Ghost_Fade,
	};

	enum {
		Ghost_Face_Left,
		Ghost_Face_Right,
	};

    RT_CLASS_DEFINE(JackOLanternGhost, Projectile, RtClass);
    JackOLanternGhost();
    void onProjectileInitialized() override;
    bool OnCollideEntity(BoardEntity* i_entity) override;
    void onDraw(Graphics* i_g) override;
    void onDestroy() override;

    void SetParam(JackOLanternGhostParam param);
    void SetPlant(RtWeakPtr<Plant> plant);
    void SetLevel(int level) { m_level = level; }
    void SetOverrideTarget(BoardEntity* i_overrideTarget);

protected:
    void moveThroughTime(pvztime_t i_dt) override;
    void moveThroughTimeIdle(pvztime_t i_dt);

    int GetFacing() const { return m_faceDirection; }
    void SetFacing(int face);

    pvztime_t CalcZombieApplyDuration(Zombie* zombie);
    void ApplyGhostLantern(BoardEntity* entity);

    BoardEntity* FindTarget();
    void FindNewTarget();
    bool CanBeTarget(BoardEntity* i_entity);
    SexyVector3 GetTargetPos(BoardEntity* i_target);

    void DrawCollisionInfo(Graphics* g);
    void OnPlantDestroyed(Plant* plant);

protected:
    pvztime_t m_ghostLanternDurationSmall;
    pvztime_t m_ghostLanternDurationMid;
    pvztime_t m_ghostLanternDurationBig;
    pvztime_t m_ghostLanternFireDuration;
    float m_ghostLanternFireDamage;
    RtWeakPtr<Plant> m_plant;
    int m_state;
    int m_faceDirection;
    SexyVector3 m_idleSpeed;
    pvztime_t m_idleTime;
    pvztime_t m_idleDuration;
    int m_level;
    RtWeakPtr<BoardEntity> m_overrideTarget;
    bool m_deflected;
};

class PlantJackOLantern : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantJackOLantern, PlantFramework, RtClass);
	
	void	Initialize() override;
	void	UpdateActions() override;
	void	UpdateUnconditionally() override;
	bool	CanApplyPlantfood() override { return true; }
	bool	OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	void	onKilled(bool i_instantKill) override;
	SexyVector2 GetShadowOffset() override;
	void	CancelOngoingEffects() override;
	void	OnRelocationBegun() override;
	void	OnRelocationComplete() override;
	void	ApplyPlantfood() override;
	void	CancelPlantfood() override;
	void	ShowPersistentEffects(bool i_show) override;
	
	void ResetGhostLantern();

protected:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;
	int GetMaxLengthOfFlameThrower();
    BoardEntity* FindTarget();
    bool CanBeTarget(BoardEntity* i_entity);
	bool ZombieIsBlacklisted(Zombie* zombie);
	float GetDamageIncrementPercent();
	
private:
	enum State
	{
		STATE_ATTACKING,
		STATE_POWERDOWN,
		STATE_SPAWN_GHOST_LANTERN,
	};
	
	enum FlameState
	{
		FLAMESTATE_CHARGING,
		FLAMESTATE_BURSTING,
		FLAMESTATE_FULL
	};
	
    std::vector<BoardEntity*> getZombiesInRange();

	void	startShootingFlames();
	void	onDestroy() override;
	void	clearFireTiles();
	
	void	setState(uint i_plantState);
	void	setFlameState(FlameState i_flameState);
	void	updateFlameState();
	
	void	createFireTiles(bool i_skipDelay);
	void	applyFlameDamage();
	void	updateFlameIndicator();
	void	updateFireTiles();
    AttachedEffect& createFireEffect();
	
	std::multimap<int, Point> calcWispTargetLocs();
	std::vector<Point> specifyWispTargetLocs(std::multimap<int, Point> i_targetLocs, int i_wispCount);
	void	addTargetToWispLocs(Point i_target, std::vector<Point> &o_wispLocs);
	std::string GetWispName();
	void SpawnGhost();
	
	float	m_fireAmount;
	FlameState m_flameState;
	pvztime_t m_timeSpentAttacking;
	std::vector<RtWeakPtr<Effect_PopAnim>> m_flameEffects;
	RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;
	bool m_showPersistentFlame;
    bool m_shouldAttack = false;
    bool m_isFuelEmpty = false;
    pvztime_t m_ghostSpawnEndTime;
    RtWeakPtr<Projectile> m_ghostLantern;
    float m_damageIncrementPercent;
};

class JackOLanternProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(JackOLanternProps, PlantPropertySheet, RtClass);
	
	JackOLanternProps()
	{
		FlameOffset = SexyVector2(0.f, 0.f);
		
		GridLengthOfFlamethrower = 3;
		GridLengthOfFlamethrowerLevel2 = 4;
		GridLengthOfFlamethrowerLevel3 = 5;
		FlamethrowerDPS = 100.f;
		
		MaximumFireAmount = 100.f;
		FlamethrowerActivateCost = 10.f;
		FlamethrowerSustainCostPerSecond = 40.f;
		FireRegenerationPerSecond = 20.f;
		FlamethrowerDamageIncrementTime = 1.f;
		FlamethrowerDamageIncrementPercent = 0.1f;
		FlamethrowerDamageIncrementPercent2 = 0.1f;
		FlamethrowerDamageIncrementPercent3 = 0.1f;
		FlamethrowerDamageIncrementPercent4 = 0.1f;
		FlamethrowerDamageIncrementPercent5 = 0.1f;
        FireAmountNeededToStart = 50.0f;
        
		PFWispCount = 3;
		GridItemDamage = 120.0f;
		GhostSpawnCooldown = 15.0f;
		GhostLanternDurationSmall = 5.0f;
		GhostLanternDurationMid = 5.0f;
		GhostLanternDurationBig = 5.0f;
		GhostLanternFireDuration = 5.0f;
		GhostLanternFireDamage = 60.0f;
	}
	
	ComponentWarmingRadiusProps WarmingRadius;
	SexyVector2 FlameOffset;
	
	int GridLengthOfFlamethrower;
	int GridLengthOfFlamethrowerLevel2;
	int GridLengthOfFlamethrowerLevel3;
	float FlamethrowerDPS;
	
	float MaximumFireAmount;
	float FlamethrowerActivateCost;
	float FlamethrowerSustainCostPerSecond;
	float FlamethrowerDamageIncrementTime;
	float FlamethrowerDamageIncrementPercent;
	float FlamethrowerDamageIncrementPercent2;
	float FlamethrowerDamageIncrementPercent3;
	float FlamethrowerDamageIncrementPercent4;
	float FlamethrowerDamageIncrementPercent5;
	float FireRegenerationPerSecond;
    float FireAmountNeededToStart;
    float GridItemDamage;

    pvztime_t GhostSpawnCooldown;
    float GhostLanternDurationSmall;
    float GhostLanternDurationMid;
    float GhostLanternDurationBig;
    float GhostLanternFireDuration;
    float GhostLanternFireDamage;

    RtWeakPtr<ProjectilePropertySheet> Projectile;
	
	int PFWispCount;

	ZombieRestrictionSet CannotBeHypnotized;
};
enum PlantAnimRigState_JackOLantern
{
    PLANTANIM_JOL_EMPTY = PLANTANIM_USERDEFINED,
};

class PlantAnimRig_JackOLantern : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_JackOLantern, PlantAnimRig, RtClass);
	
	PlantAnimRig_JackOLantern() {};
	
	void PlayAttackStart(PopAnimRig::AnimStoppedReflectionDelegate i_onStopped);
	void PlayAttackLoop();
	void PlayAttackEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onStopped);
    
    void PlayEmptyStart(PopAnimRig::AnimStoppedReflectionDelegate i_onStopped);
    void PlayEmptyLoop();
    void PlayEmptyEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onStopped);
    
	bool PlayPreviewAnim(bool bHideLayer) override { return PlayAndContinue(getPreviewAnimName()); }
	
	void PlaySpawnGhostLantern(PopAnimRig::AnimStoppedReflectionDelegate i_onStopped);

protected:
	void onPopAnimInitialized() override;
	std::string getPreviewAnimName();
};

class EffectAnimRig_JackOLanternFireSquare : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_JackOLanternFireSquare, PopAnimRig, RtClass);
	
	void SetFireDelay(pvztime_t i_delay);
	void PlayIdleSequence();
	void PlayFade();
	
	void SetOwningEffect(class Effect_PopAnim* i_effect);
	
protected:
	virtual void onPopAnimInitialized() override;
	virtual void onUpdate() override;
	
private:
	void onSequenceContinued(const std::string& i_oldAnimName, const std::string& i_newAnimName, int i_playCount);
	void onFadeEnded(const std::string& i_oldAnimName, const std::string& i_newAnimName, int i_playCount);
	
	RtWeakPtr<class Effect_PopAnim> m_owningEffect;
	pvztime_t m_activationTime;
	bool m_fadingOut;
};

enum GridItemWispState
{
	PVZ_BEGIN_ENUM(WISPSTATE_),
	WISPSTATE_UNKNOWN,
	WISPSTATE_RESETTING,
	WISPSTATE_SPAWNING,
	WISPSTATE_IDLE,
	WISPSTATE_FADING,
	WISPSTATE_DEAD,
	PVZ_END_ENUM(WISPSTATE_)
};

class GridItemWisp : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemWisp, GridItemAnimation, RtClass);
	
	GridItemWisp()
	: m_creationTime(PVZ_EOT())
	, m_state(WISPSTATE_UNKNOWN)
	, m_damageAmount(120)
	{}
	
	int	CalcRenderOrder() const override;
	void ResetTimer();
	void PlayIdle();
	void SetDamageAmount(int i_amount) { m_damageAmount = i_amount; }
	void SetAvatar(bool avatar) { m_avatar = avatar; }
	void SetExtraDPS(float dps) { m_extraDPS = dps; }
	
protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	
	void setState(GridItemWispState i_state);
	
	void onSplatFinished(const std::string &i_animName);
	void onSplatFaded(const std::string &i_animName);
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

private:
	void causeDamage();
	pvztime_t m_creationTime;
	GridItemWispState m_state;
	int m_damageAmount;
	int m_damageAvatarAmount;
	bool m_avatar;
	float m_extraDPS;
};

class GridItemWispProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemWispProps, GridItemAnimationProps, RtClass);
	GridItemWispProps()
	: Lifetime(5.0), Damage(0)
	{}
	
	pvztime_t Lifetime;
	float Damage;
};

#endif /* defined(__PlantsVersusZombies2__Plant_JackOLantern__) */
