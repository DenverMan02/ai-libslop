//
//  ZombieZombossExplosive.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-2-13.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieZombossExplosive__
#define __PlantsVersusZombies2__ZombieZombossExplosive__

#include "Zomboss.h"
#include "ZombiePropertySheet.h"
#include "Plant.h"
#include "ZombossCrosshair.h"
#include "Projectile.h"

class BombProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BombProjectile, Projectile, RtClass);
    
    virtual ~BombProjectile();
        
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
	virtual bool OnCollideGround() override;
    
    void SetOwningRocket(const ZombossCrosshair* i_rocket);
    
private:
	RtWeakPtr<ZombossCrosshair> m_owningRocket;
};

////////////////

STATE_ENUM_CHILD_BEGIN(ZombossExplosiveState, ZombossState)
ZombossExplosive_Summon,
ZombossExplosive_DropBombs,
ZombossExplosive_LaunchImp,
ZombossExplosive_BigSummon,

ZombossExplosive_SummonIdle,
ZombossExplosive_LaunchImpIdle,
ZombossExplosive_RandomSkill,
ZombossExplosive_BigSkill,

ZombossExplosive_JumpToSky,
ZombossExplosive_SkyToLand,

ZombossExplosive_JumpToChangeLane,
ZombossExplosive_ChangeLaneToLand,

STATE_ENUM_END(ZombossExplosiveState);

struct ZombossExplosiveImp
{
	ZombossExplosiveImp()
	{
		
	}
    
	int         ImpTargetColumn = 0;
	float       ImpApex = 0;
	SexyVector3 ImpSpawnOffset;
	float       ImpFlightTime = 0;
	std::string ImpType;
};

struct ZombossExplosiveStage
{
	ZombossExplosiveStage()
	{
		AnimRateModifier				= 1.0f;
		HitPoints 						= 5000;
        Level                           = 1;

        TakeSkillInterval    = 4.0f;
        TakeBigSkillInterval = 4.0f;
        InSkyTime            = 5.0f;
        
        SummonIntervalMin = 5.0f;
        SummonIntervalMax = 6.0f;
        SummonTimes       = 2;
        
        DropBombsMin      = 2;
        DropBombsMax      = 4;
        
        LaunchImpCountMin = 3;
        LaunchImpCountMax = 5;
        LaunchImpTimes    = 2;
        LaunchImpInterval = 3.0f;
        
        BigSummonCountMin = 3;
        BigSummonCountMax = 5;
	}
    
    int									HitPoints;
    int 								Level;
	float								AnimRateModifier;

    float                               TakeSkillInterval;
    float                               TakeBigSkillInterval;
    float                               InSkyTime;
    
	//Summon
	CZombieSummonDataPool				ZombieSummonDataPool;
    float                               SummonIntervalMin;
    float                               SummonIntervalMax;
    int                                 SummonTimes;
    
    
    //DropBombs
    int                                 DropBombsMin;
    int                                 DropBombsMax;
    
    
    //LaunchImp
    int                                 LaunchImpCountMin;
    int                                 LaunchImpCountMax;
    int                                 LaunchImpTimes;
    float                               LaunchImpInterval;
    
    
    //Big Summon
    int                                 BigSummonCountMin;
    int                                 BigSummonCountMax;
};

class ZombieZombossExplosiveProps : public ZombossProps
{
public:
	RT_CLASS_DEFINE(ZombieZombossExplosiveProps, ZombossProps, RtClass);
    
	ZombieZombossExplosiveProps()
	{
        
	}
    
    std::vector<ZombossExplosiveStage> 	Stages;
    ZombossExplosiveImp                 ZombossImp;
    ProjectilePropertySheetPtr          Projectile;
};

class ZombieZombossExplosive : public Zomboss
{
public:
	RT_CLASS_DEFINE(ZombieZombossExplosive, Zomboss, RtClass);
    
    ZombieZombossExplosive();
    
	//interfaces from Zomboss
    virtual ImagePtr getHeadIcon() override;
	virtual void startFunctioning() override;
    
    virtual Sexy::Point GetGridExtents() const override;
    
    void OnRocketDestroyed(ZombossCrosshair* i_rocket);
    
    void DropAllLoot() override;
    
    virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    
    virtual bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;
    virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;
    
protected:
    
    //interfaces from Zomboss
    virtual void onChangeActiveStage(int i_activeStageIndex) override;
    virtual void onChangeStageAnimDone(const std::string& i_label) override;
    virtual bool canChangeStage() const override;

    enum EZombossExplosiveRandomAction
    {
        ZombossExplosiveInvalidAction,
        ZombossExplosiveDropBombsAction,
        ZombossExplosiveLaunchImpAction
    };
    
	virtual void onZombieInitialize() override;
    virtual void onUpdate() override;
    
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
    
    virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
    
private:
	DECLARE_STATE_FUNCTIONS(ZombieState, Summon);
	DECLARE_STATE_FUNCTIONS(ZombieState, DropBombs);
	DECLARE_STATE_FUNCTIONS(ZombieState, LaunchImp);
    DECLARE_STATE_FUNCTIONS(ZombieState, BigSummon);
    
    DECLARE_STATE_FUNCTIONS(ZombieState, SummonIdle);
    DECLARE_STATE_FUNCTIONS(ZombieState, LaunchImpIdle);
    DECLARE_STATE_FUNCTIONS(ZombieState, RandomSkill);
    DECLARE_STATE_FUNCTIONS(ZombieState, BigSkill);
    
    DECLARE_STATE_FUNCTIONS(ZombieState, JumpToSky);
    DECLARE_STATE_FUNCTIONS(ZombieState, SkyToLand);
    
    DECLARE_STATE_FUNCTIONS(ZombieState, JumpToChangeLane);
    DECLARE_STATE_FUNCTIONS(ZombieState, ChangeLaneToLand);
    
    void onSummonAnimDone(const std::string& i_label);
    void onLaunchImpAnimDone(const std::string& i_label);
    void onDropBombsAnimDone(const std::string& i_label);
    void onJumpToChangeLaneAnimDone(const std::string& i_label);
    void onChangeLaneToLandAnimDone(const std::string& i_label);
    void onBigSummonAnimDone(const std::string& i_label);
    void onJumpToSkyAnimDone(const std::string& i_label);
    void onSkyToLandAnimDone(const std::string& i_label);
    
	const ZombossExplosiveStage& getActiveStage() const;
	void initializeStageData(const ZombossExplosiveStage& stage);
    
    void OnZombieZombossDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
    
    void Reset();
    
    /// Summon
    void trySummonAction();
    
    
    /// Fire Imp!
    void tryFireImpAction();
    
    
    /// Fire Bomb!
    void getRocketTargets(std::vector<BoardEntity*>& o_entityList);
    bool tryFireRocketAction();
    void takeFireRocketAction();
    
    Projectile * NewFire();
    Projectile * fireBomb(PlantPtr targetPlant);
    
    bool pickRocketTargets();
    
    
    /// Big Summon!
    void tryBigSummonAction();
private:
    std::vector<RtWeakPtr<class ZombossCrosshair> > m_activeRockets;
    
    pvztime_t  m_startTime;
    
    EZombossExplosiveRandomAction m_previousRandomAction;
    
    
    ////
    pvztime_t  m_summonTime;
    int        m_summonCount;
    
    
    ////
    pvztime_t  m_FireImpTime;
    int        m_FireImpCount;
    
    
    ////
    pvztime_t  m_randomSkillTime;
    
    pvztime_t  m_bigSkillTime;
    
    pvztime_t  m_TimeJump;
    
    pvztime_t  m_TimeBeforeJump;
};

class RocketZombieFlickModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(RocketZombieFlickModule, LevelModule, RtClass);
    RocketZombieFlickModule();
    ~RocketZombieFlickModule();
protected:
    virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
private:
    //QTE
    bool handleTouch(const Sexy::Touch& i_touch);
    void cancelTouch();
    void QTEFlick(const SexyVector2& i_direction);
    void findQTEZombie(const SexyVector2& i_startPoint,
                       const SexyVector2& i_endPoint, std::vector<class Zombie*>& o_zombies);
    bool isValidQTETarget(class Zombie* i_zombie);
private:
    //QTE
    Sexy::TouchID   m_touchIdent = Sexy::InvalidTouchID;
    SexyVector2     m_touchStart;
};

class RocketZombieFlickModuleProperties : public LevelModuleProperties
{
public:
    RT_CLASS_DEFINE(RocketZombieFlickModuleProperties, LevelModuleProperties, RtClass);
    virtual RtClass* GetModuleClass() const override
    {
        return RocketZombieFlickModule::StaticGetClass();
    }
    
    RocketZombieFlickModuleProperties();
    ~RocketZombieFlickModuleProperties();
};

#endif /* defined(__PlantsVersusZombies2__ZombieZombossExplosive__) */
