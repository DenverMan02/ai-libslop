//
//  ZombieZombossMech_SkyCity.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-8-12.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieZombossMech_SkyCity__
#define __PlantsVersusZombies2__ZombieZombossMech_SkyCity__

#include "ZombieZombossMech.h"
#include "ZombieAnimRig_ZombossMech.h"
#include "BoardEntity.h"
#include "Projectile.h"
#include "Effect_Barrage.h"

class ZombossSkyCityLineShoot
{
public:
	ZombossSkyCityLineShoot();
	
	void Start(pvztime_t i_duration,
               int i_shotTotal,
               float i_extraDamage);
    
	void Update(ZombieZombossMech * i_owner,
                const SexyVector3& i_zombossPosition,
                float i_zombossScale);
	
	void SetBackwardsProjectiles(bool i_backwards);
    void SetRotation(float i_rotation);
    
	pvztime_t m_shotsPerSecond;
	pvztime_t m_startTime;
	int       m_shotsFired;
	int       m_shotTotal;
	bool      m_backwardsProjectiles;
    
private:
	float m_rotation;
    float m_extraDamage;
};


#pragma mark - Custom Actions

#pragma mark SkyCity Spawn Action

class ZombossSkyCitySpawnActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSkyCitySpawnActionDefinition, ZombieActionDefinition, RtClass);
    
	ZombossSkyCitySpawnActionDefinition()
    : SpawnDistanceVariance(150)
    , SpawnWavesBetweenPlantFood(1.f, 1.f)
    , SpawnStartTime(1.f)
    , SpawnEndTime(1.5f)
    , SpawnZombieWavePointRange(1500, 7500)
	{
        
    }
    
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
    
	int SpawnDistanceVariance;
	std::vector<std::string> SpawnZombieTypes;
	float SpawnStartTime;
	float SpawnEndTime;
	ValueRange SpawnWavesBetweenPlantFood;
	ValueRange SpawnZombieWavePointRange;
};

class ZombossSkyCitySpawnActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSkyCitySpawnActionHandler, ZombieActionHandler, RtClass);
    
protected:
	void onStartAction()  override;
	void onUpdateAction() override;
	void onEndAction()    override;
    
private:
	void pickZombiesForSpawn();
	class Zombie* spawnZombie(ZombieTypePtr i_zombieType) const;
	int pickPlantfoodSpawnDelay() const;
	bool waveHasPlantfoodCarryingZombie(const std::vector<ZombieTypePtr> i_zombies) const;
	bool isZombieValidForSpawnLocation(const ZombieTypePtr i_zombieType) const;
	void onSummonAnimationEnd(const std::string& i_animLabel);
    
	std::vector<ZombieTypePtr> m_zombiesToSpawn;
	pvztime_t m_startSpawningTime = PVZ_EOT();
	int m_spawnedSoFar = 0;
};

#pragma mark SkyCity Walk Action

class ZombossSkyCityWalkActionDefinition : public ZombossWalkActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSkyCityWalkActionDefinition, ZombossWalkActionDefinition, RtClass);
    
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombossSkyCityWalkActionHandler : public ZombossWalkActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSkyCityWalkActionHandler, ZombossWalkActionHandler, RtClass);
    
protected:
	void onStartAction() override;
	void onUpdateAction() override;
private:
	pvztime_t m_nextStepTime = PVZ_EOT();
};

#pragma mark SkyCity LineShoot Action

class ZombossSkyCityLineShootActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSkyCityLineShootActionDefinition, ZombieActionDefinition, RtClass);
    
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombossSkyCityLineShootActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSkyCityLineShootActionHandler, ZombieActionHandler, RtClass);
    
protected:
	void onStartAction()  override;
	void onUpdateAction() override;
    
    void onLineShootStartEnded(const std::string &i_animName);
    //void onLineShootActionEnded(const std::string &i_animName);
    //void onLineShootEndEnded(const std::string &i_animName);
    
private:
    ZombossSkyCityLineShoot m_LineShoot;
};

#pragma mark SkyCity ThrowAircraft Action

class ZombossSkyCityThrowAircraftActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSkyCityThrowAircraftActionDefinition, ZombieActionDefinition, RtClass);
    
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombossSkyCityThrowAircraftActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSkyCityThrowAircraftActionHandler, ZombieActionHandler, RtClass);
    
protected:
	void onStartAction()  override;
	void onUpdateAction() override;
    
    void onThrowAircraftEnded(const std::string &i_animName);
    
private:
    
};

#pragma mark SkyCity Sandstorm Action

class ZombossSkyCitySandstormActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSkyCitySandstormActionDefinition, ZombieActionDefinition, RtClass);
    
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombossSkyCitySandstormActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSkyCitySandstormActionHandler, ZombieActionHandler, RtClass);
    
protected:
	void onStartAction()  override;
	void onUpdateAction() override;
    
    void onSandstormEnded(const std::string &i_animName);
    
private:
    
    std::vector<RtWeakPtr<Effect_PopAnim> > m_Clouds;
};

#pragma mark SkyCity RushDown Action

class ZombossSkyCityRushDownActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSkyCityRushDownActionDefinition, ZombieActionDefinition, RtClass);
    
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombossSkyCityRushDownActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSkyCityRushDownActionHandler, ZombieActionHandler, RtClass);
    
protected:
	void onStartAction()  override;
	void onUpdateAction() override;
    
    void onRushDownFlyEnded(const std::string &i_animName);
    void onRushDownEnded(const std::string &i_animName);
    
private:
    
};

#pragma mark SkyCity AttackNearBy Action

class ZombossSkyCityAttackNearByActionDefinition : public ZombieActionDefinition
{
public:
	RT_CLASS_DEFINE(ZombossSkyCityAttackNearByActionDefinition, ZombieActionDefinition, RtClass);
    
	bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
};

class ZombossSkyCityAttackNearByActionHandler : public ZombieActionHandler
{
public:
	RT_CLASS_DEFINE(ZombossSkyCityAttackNearByActionHandler, ZombieActionHandler, RtClass);
    
protected:
	void onStartAction()  override;
	void onUpdateAction() override;
    
    void onAttackNearByEnded(const std::string &i_animName);
    
private:
    BoardEntityPtr m_target;
};

#pragma mark SkyCity Barrage Action

class ZombossSkyCityBarrageProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ZombossSkyCityBarrageProjectile, Projectile, RtClass);
    
    ZombossSkyCityBarrageProjectile() {} 
    virtual ~ZombossSkyCityBarrageProjectile() {}
};

class ZombossSkyCityBarrageActionDefinition : public ZombieActionDefinition
{
public:
    RT_CLASS_DEFINE(ZombossSkyCityBarrageActionDefinition, ZombieActionDefinition, RtClass);
    
    ZombossSkyCityBarrageActionDefinition()
    : BarrageSpan(0.2f)
    , BarrageTime(5.0f)
    , BarrageCountPerTime(10)
    {
        
    }
    
    bool TryStartAction(ZombieActionDefinitionPtr i_actionDef, class ZombieWithActions* i_zombie) const override;
    
    float BarrageSpan;
    float BarrageTime;
    int   BarrageCountPerTime;
};

class ZombossSkyCityBarrageActionHandler : public ZombieActionHandler
{
public:
    RT_CLASS_DEFINE(ZombossSkyCityBarrageActionHandler, ZombieActionHandler, RtClass);
    
protected:
    void onStartAction()  override;
    void onUpdateAction() override;
    
    void onCollectEnergyEnded(const std::string &i_animName);
    void onBarrageEnded(const std::string &i_animName);
    
    void onStartCollectEnergy();
    void onSendProjectile();
    
private:
    bool            isShowWarning;
    bool            isBarrageStart;
    float           lastTime;
    float           runTime;
    int             barrageIdx;
};

#pragma mark - Props

class ZombieZombossMechSkyCityProps : public ZombieZombossMechProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossMechSkyCityProps, ZombieZombossMechProps, RtClass);
    
	ZombieZombossMechSkyCityProps()
	{
        AircraftHitpoints = 500.0f;
        AircraftLineDamage = 100.0f;
        AircraftSingleDamage = 100.0f;
        CanTakeThunder = true;
    }
    
    float		AircraftHitpoints;
    float		AircraftLineDamage;
    float		AircraftSingleDamage;
    bool        CanTakeThunder;
};

#pragma mark - Zomboss

STATE_ENUM_CHILD_BEGIN(ZombossSkyCityMechState, ZombossMechState)
ZombossSkyCityMagnetStun,
STATE_ENUM_END(ZombossSkyCityMechState);


class ZombieZombossMech_SkyCity : public ZombieZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieZombossMech_SkyCity, ZombieZombossMech, RtClass);
    
	ZombieZombossMech_SkyCity();
    ~ZombieZombossMech_SkyCity();
    
    void       createLaserCannonEffect();
    Sexy::Rect CalcBellyFootprint() const;
    void FindRushDownTargets(BoardEntityTypeFlag i_acceptedTypes,
                             std::vector<BoardEntity*>& o_targets) const;
    
    
    void FindNearByTargets(BoardEntityTypeFlag i_acceptedTypes,
                           std::vector<BoardEntity*>& o_targets) const;
    int GetNearByTargets(BoardEntityTypeFlag i_acceptedTypes, std::vector<BoardEntity*>& o_targets);
    
    void thunderStart();
    
    void takeLineShoot();
    void takeSandStorm();
    
	void Retreat(ZombieState i_endState) override;
    
    
    int  m_shotsFired;
    bool m_bTransform;
    
protected:
	void onUpdate() override;
    
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    
	bool isPlantAllowedUnderZomboss(const PlantType* i_plant) override;
    
    void takeThunder();
    
    void onStartedNewStage(int i_newStageIndex) override;
    
	DECLARE_STATE_FUNCTIONS(ZombieState, MagnetStun);
    
private:
    
    float m_nextThunderTime;
    int   m_indexThunder;
    bool  m_activeThunder;
    
    int   m_indexAircraft;
};

#pragma mark - Anim Rig

class ZombieAnimRig_ZombossMech_SkyCity : public ZombieAnimRig_ZombossMech
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombossMech_SkyCity, ZombieAnimRig_ZombossMech, RtClass);
    
	ZombieAnimRig_ZombossMech_SkyCity()
    {
        m_bTransform  = false;
        m_playingIdle = false;
    }
    
    const char* getIdleAnimName() const override;
    const char* getSummoningAnimName() const override { return "attack04"; }
    const char* getStunAnimName() const override;
    const char* getStunLoopAnimName() const override;
    const char* getStunEndAnimName() const override;
    
    
    bool PlayThrowAircraftStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
    bool PlayLineShootStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
    bool PlayRushDownFly(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayRushDown(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
    bool PlaySandstorm(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
    bool PlayAttackMiddleNearBy(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayAttackUpNearBy(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayAttackDownNearBy(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
    bool PlaySpwanInAirplane(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
    bool PlayCollectEnergy(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayBarrage();
    bool PlayBarrageEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
    void PlayIdle(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {}) override;
    
	void PlayWalkForDirection(ZombossWalkDirection i_walkDir, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped) override;
	
	const Sexy::FPoint getTeleportationEffectOffset() const override;
    
    bool m_bTransform;
	
protected:
	const std::vector<std::string>& getDamageLayerList(ZombieAnimRig_ZombossMech::DamagePhase i_damagePhase) const override;
	void onPostPlayCalled() override;    
private:
	bool m_playingIdle;
};

////////
class BossTornadoProjectileProps : public ProjectilePropertySheet
{
public:
    RT_CLASS_DEFINE(BossTornadoProjectileProps, ProjectilePropertySheet, RtClass);
    
    BossTornadoProjectileProps()
    {
        AirshipDamage = 1000.0f;
    }
    
    float		AirshipDamage;
};

class BossTornadoProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BossTornadoProjectile, Projectile, RtClass);
    
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    
    virtual void onProjectileInitialized() override;
    
    bool    isCollideWithAirship;
private:
    
};

#endif /* defined(__PlantsVersusZombies2__ZombieZombossMech_SkyCity__) */
