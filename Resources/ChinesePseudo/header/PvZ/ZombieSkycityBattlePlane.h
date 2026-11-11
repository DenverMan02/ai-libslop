//
//  ZombieSkycityBattlePlane.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/6/12.
//  Copyright (c) 2015�� PopCap Games. All rights reserved.
//

#ifndef __ZombieSkycityBattlePlane_H__
#define __ZombieSkycityBattlePlane_H__

#include "Zombie.h"
#include "Projectile.h"
#include "Effect_Barrage.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_Battleplane, ZombieState)
    ZS_BattlePlane_FlyOut,
    ZS_BattlePlane_FlyIn,
    ZS_BattlePlane_Slide,
    ZS_BattlePlane_Hit,
    ZS_BattlePlane_ZombieDie,
STATE_ENUM_END(ZombieState_Battleplane)

class ZombieSkycityBattlePlane : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieSkycityBattlePlane, Zombie, RtClass);
	
	ZombieSkycityBattlePlane();

	void				PlayHitEffect(bool bNeedPrepare);
    void				Crash(class GridItemAirship* pGridItem);
    
    Effect_Barrage *    GetBarragePtr();
    void SetPooyanBossHP(float i_hp);
protected:
	virtual bool allowElectrocuteState() const override { return false; }
    virtual bool allowAshState() const override { return false; }
	virtual void	onZombieInitialize() override;
	virtual void	onUpdate() override;
	virtual class   BoardEntity* findTarget() override;
	virtual DamageInfo modifyBodyDamage(const DamageInfo& i_incomingDamage) override;
	virtual void onTakeBodyDamage(const DamageInfo& i_damageReceived) override;
	
	virtual void	onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Walk);
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Glide);
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Attack);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyOut);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyIn);
	DECLARE_STATE_FUNCTIONS(ZombieState, Slide);
	DECLARE_STATE_FUNCTIONS(ZombieState, Hit);
	DECLARE_STATE_FUNCTIONS(ZombieState, ZombieDie);
	OVERRIDE_STATE_UPDATE(ZombieState, Die);

	void				onAnimationDone(const std::string& i_animName);
	void				onHitEffectEnd(class StandaloneEffect* pEffect);
        
private:
    bool				m_bPlayingZombieDie;
    float				m_zombieHP;
	pvztime_t			m_flyInterval;
	pvztime_t			m_nextFlyTime;
    Effect_Barrage      m_barrage;
};


class ZombieCardGameBattlePlane : public ZombieSkycityBattlePlane
{
public:
	RT_CLASS_DEFINE(ZombieCardGameBattlePlane, ZombieSkycityBattlePlane, RtClass);
protected:
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
};


class ZombieSkycityBattlePlaneProps : public ZombieTargetProps
{
public:
	RT_CLASS_DEFINE(ZombieSkycityBattlePlaneProps, ZombieTargetProps, RtClass);

	ZombieSkycityBattlePlaneProps();

	float ZombieHP;
	float SpeedSlide;
};

//enum ZombieAnimRigState_BattlePlane
//{
//	ZOMBIEANIM_BattlePlane_ZombieDie = ZOMBIEANIM_USERDEFINED,
//};

class ZombieAnimRig_BattlePlane: public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_BattlePlane, ZombieAnimRig, RtClass);
	//bool PlaySpawnWind(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayFire();
	bool PlaySlide();
	bool PlayHit();
};

class BattlePlaneProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(BattlePlaneProjectile, Projectile, RtClass);
    
    BattlePlaneProjectile() {}
    virtual ~BattlePlaneProjectile() {}
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
protected:
    virtual bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
};

#endif
