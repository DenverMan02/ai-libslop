//
//  Plant_LavaGuava.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 3/16/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_LavaGuava__
#define __PlantsVersusZombies2__Plant_LavaGuava__

#include "ComponentWarmingRadius.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "Projectile.h"
#include "GridItemAnimation.h"

class PlantLavaGuava : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantLavaGuava, PlantFramework, RtClass);
	
	void Initialize() override;
	void UpdateActions() override;
	
	float GetShadowScaling() override
	{
		return 0.7f;
	}
	
	bool HasShadow() override;
	
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	void UpdatePlantfood() override;
	bool IsInvincible() const override;
	CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
	void TakeSmashAttack(ZombiePtr i_instigator) override;
	bool TryBlockZombossRush(Zombie* i_zomboss) override;
	bool TryBlockPushOffBoard(Zombie* i_srcZombie, const int i_direction) override;
	
	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	
	bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
	bool CanBeTargeted() override { return true; }
    bool CanBeShoveled() override;
    
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	
private:
    void filterTargets(const std::vector<BoardEntity*>& i_entities, std::vector<BoardEntity*> *o_targets);
    void causeDamage(const std::vector<BoardEntity*>& i_targets, const DamageInfo &i_damageInfo);
    void killGridItems();
    void updatePlantfoodDamageEndtime();
    void playCrackEffect();
    void playAvatarCrackEffect();
    bool canOpenCrack();
    void openCrack();
    void causeCrackDamage(const std::vector<BoardEntity*>& i_targetableEntities);
    void LaunchProjectile(Sexy::SexyVector3 i_targetLoc);
    Sexy::Rect createCrackRect();
    
private:
	bool m_exploded = false;
    pvztime_t m_endAttackTime = PVZ_EOT();
	ZombiePtr m_forceTargetZombie;
	pvztime_t m_plantfoodDamageEndTime = -1.0f;
	RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;
};

class LavaGuavaProps : public CabbagepultProps
{
public:
	RT_CLASS_DEFINE(LavaGuavaProps, CabbagepultProps, RtClass);
	
	LavaGuavaProps()
	{
		ExplosionRadius = 2.0736f;
		ExplosionDamage = 600.0f;
		CrackLengthInNumTiles = 1.0f;
        AttackDuration = 4.5f;
	}
	
	float ExplosionRadius;
	float ExplosionDamage;
	float CrackLengthInNumTiles;
    float AttackDuration;
	ComponentWarmingRadiusProps NormalWarmingRadius;
	ComponentWarmingRadiusProps PlantfoodWarmingRadius;
};

enum GridItemLavaState
{
	PVZ_BEGIN_ENUM(LAVASTATE_),
	LAVASTATE_UNKNOWN,
	LAVASTATE_SPAWNING,
	LAVASTATE_IDLE,
	LAVASTATE_FADING,
	LAVASTATE_DEAD,
	PVZ_END_ENUM(LAVASTATE_)
};

class GridItemLava : public GridItemAnimation
{
public:
    enum TinyLavaDirection
    {
        TINYLAVA_LEFT = 0,
        TINYLAVA_RIGHT,
        TINYLAVA_UP,
        TINYLAVA_DOWN,
        TINYLAVA_DIRECTION_MAX, // keep last!
    };
    
	RT_CLASS_DEFINE(GridItemLava, GridItemAnimation, RtClass);
	
	GridItemLava();
    virtual ~GridItemLava();
	int	CalcRenderOrder() const override;
	virtual void OnWashedOut();
	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
    virtual void SetLifeTime(pvztime_t i_lifeTime) { m_lifeTime = i_lifeTime; }
    virtual pvztime_t GetLifeTime() { return m_lifeTime; }
    void SetNeedSpawnTinyLava(bool i_need) { m_needSpawnTinyLava = i_need; }
	
protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	
	virtual void setState(GridItemLavaState i_state);
	
	virtual void onSplatFinished(const std::string &i_animName);
	void onSplatFaded(const std::string &i_animName);
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    
protected:
    void causeDamage();
    virtual void onCauseDamage(class Zombie* i_zombie) {}
    pvztime_t m_creationTime;
    pvztime_t m_lifeTime;
    float m_damagePerSecond = 0.5f;
    GridItemLavaState m_state;
    RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;
    
private:
    bool m_needSpawnTinyLava;
    std::vector<RtWeakPtr<Effect_PopAnim> > m_cachedEffects;   //we need to delete these effects by ourselves
    
    bool canSpawnTinyLava(TinyLavaDirection i_direction);
    void spawnTinyLava(TinyLavaDirection i_direction);
    void onAnimStopped(const std::string &i_animName);
};

class GridItemTinyLava : public GridItemLava
{
public:
    RT_CLASS_DEFINE(GridItemTinyLava, GridItemLava, RtClass);
    
//    void SetNeedSpawnTinyLava(bool i_need) override { return; }
protected:
//    void onGridItemInitialize() override;
//    void onUpdate() override;
//    
//    void setState(GridItemLavaState i_state);
//    
    void onSplatFinished(const std::string &i_animName) override;
//    void onSplatFaded(const std::string &i_animName);
    
protected:
    void causeDamage();
    
private:
    void onAnimStopped(const std::string &i_animName) {}
};

class GridItemGroundLava : public GridItemLava
{
public:
    RT_CLASS_DEFINE(GridItemGroundLava, GridItemLava, RtClass);
    
protected:
    virtual void setState(GridItemLavaState i_state) override;
    void onSplatFinished(const std::string &i_animName) override;
    
protected:
    void causeDamage();
    
private:
    void onAnimStopped(const std::string &i_animName) {}
};

class GridItemLavaProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemLavaProps, GridItemAnimationProps, RtClass);
    GridItemLavaProps()
    : Lifetime(5.0)
    , DamagePerSecond(60.0)
    {}
    
    pvztime_t Lifetime;
    float DamagePerSecond;
    ComponentWarmingRadiusProps WarmingRadius;
    std::vector<std::string> ZombieBlacklist;
};

class GridItemTinyLavaProps : public GridItemLavaProps
{
public:
    RT_CLASS_DEFINE(GridItemTinyLavaProps, GridItemLavaProps, RtClass);
};

class GridItemGroundLavaProps : public GridItemLavaProps
{
public:
    RT_CLASS_DEFINE(GridItemGroundLavaProps, GridItemLavaProps, RtClass);
};

class LavaGuavaProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(LavaGuavaProjectileProps, ProjectilePropertySheet, RtClass);
    
    float LifeTime = 10.0f;
    std::string LavaItemName = "groundlava";
};

class LavaGuavaProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(LavaGuavaProjectile, Projectile, RtClass);
    
    LavaGuavaProjectile();
    bool OnCollideGround() override;
    
public:
    SexyVector3 m_TargetPosition;
};

enum CrackState
{
	PVZ_BEGIN_ENUM(CRACKSTATE_),
	CRACKSTATE_UNKNOWN,
	CRACKSTATE_LAND,
	CRACKSTATE_NEAR_WATER,
	CRACKSTATE_WATER,
	CRACKSTATE_PIRATE_SHIP,
	PVZ_END_ENUM(CRACKSTATE_)
};

enum CrackLocation
{
	PVZ_BEGIN_ENUM(CRACKLOC_),
	CRACKLOC_UNKNOWN,
	CRACKLOC_FRONT,
	CRACKLOC_MID,
	CRACKLOC_BACK,
	PVZ_END_ENUM(CRACKLOC_)
};

class PlantAnimRig_LavaGuava : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_LavaGuava, PlantAnimRig, RtClass);
	 
	void PlayCrackEffect(int lengthOfCrack, const Point& crackStartingSquare);
    
    void PlayAvatarCrackEffect(const Point& i_grid);
    
    void setIsAvatar(bool i_isAvatar) { m_isAvatar = i_isAvatar; }
	
protected:
	bool playPlantFoodOff() override;
	
	std::string getPlantFoodOnAnimName() override;
	std::string getPlantFoodMainAnimName() override;
	std::string getPlantFoodOffAnimName() override;
	void onDestroy() override;
	
private:
	void onUpdate() override;
	void initializeCrackEffects();
	CrackLocation calcCrackLoc(int i_crackIndex);
	CrackState calcCrackState(int i_crackIndex, CrackLocation i_crackLoc);
	void setCrackEmissionLocation();
    
    void onCrackSpawned(const std::string& i_animName);
	
	const float k_crackDelayMultiplier = 0.098f;
	int m_lengthOfCrack = 0;
	Point m_startingSquare;
	bool m_initialized = false;
    bool m_isAvatar = false;
	std::vector<RtWeakPtr<Effect_PopAnim>> m_linearCrackEffects;
};

class EffectAnimRig_LavaGuavaCrackSquare : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(EffectAnimRig_LavaGuavaCrackSquare, PopAnimRig, RtClass);
	
	void SetOwningEffect(class Effect_PopAnim* i_effect);
	void SetState(CrackState i_state) { m_crackState = i_state; }
	CrackState GetState() { return m_crackState; }
	void SetLoc(CrackLocation i_loc) { m_crackLoc = i_loc; }
	void SetMidCrackIndex(int i_index) { m_midCrackIndex = i_index; }
	
	void StartPlayingCrackEffect(pvztime_t i_delay);
	void StopPlayingCrackEffect(pvztime_t i_delay);
	
protected:
	void onPopAnimInitialized() override;
	void onUpdate() override;
	
private:
	void determineActivationTime(pvztime_t i_delay);
	void playDelayedAnimationSequence();
	std::string calcAnimName(std::string baseAnimName);
	void onCrackSequenceContinued(const std::string& i_oldAnimName, const std::string& i_newAnimName, int i_playCount);
	void onCrackSequenceEnded(const std::string& i_oldAnimName, const std::string& i_newAnimName, int i_playCount);
	
	RtWeakPtr<class Effect_PopAnim> m_owningEffect;
	pvztime_t m_activationTime = PVZ_T();
	bool m_playEndAnimation = false;
	CrackState m_crackState = CRACKSTATE_UNKNOWN;
	CrackLocation m_crackLoc = CRACKLOC_UNKNOWN;
	int m_midCrackIndex = -1;
};

#endif /* defined(__PlantsVersusZombies2__Plant_LavaGuava__) */
