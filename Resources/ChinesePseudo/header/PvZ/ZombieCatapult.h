//
//  ZombieCatapult.h
//  PlantsVersusZombies2
//
//  Created by Zhangxy on 11/14/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieCatapult_h
#define PlantsVersusZombies2_ZombieCatapult_h

#include "Zombie.h"
#include "RtObject.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"
#include "PopAnimRig.h"


class ZombieCatapultProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieCatapultProps, ZombiePropertySheet, RtClass);
	ZombieCatapultProps()
    {
        BallShotHeight = 750.f;
        BallShotTime = 1.f;
        InitialShotCooldown = 3.0f;
        ShotCooldown = 8.0f;
    }
    RtWeakPtr<RtObject>    BallProjectile;
    float BallShotHeight;
    float BallShotTime;
    float TimeToWalkInToPosition;
    float InitialShotCooldown;
    float ShotCooldown;

};

STATE_ENUM_CHILD_BEGIN(ZombieCatapultState, ZombieState)
    ZS_PCatapult_Waiting, 
    ZS_PCatapult_Firing,
STATE_ENUM_END(ZombieCatapultState);


class ZombieCatapult : public Zombie
{
	RT_CLASS_DEFINE(ZombieCatapult, Zombie, RtClass);
    ZombieCatapult()
    {}
	virtual void onZombieInitialize() override;
	virtual void onUpdate() override;
    virtual void onPlaceOnBoard();
    void playDeathAnimation() override;
    DamageInfo modifyBodyDamage(const DamageInfo& i_incomingDamage) override;
	void onApplyCondition(ZombieConditions i_condition) override;
    virtual void launchBall();
    void launchProjectile(SexyVector3 i_source, SexyVector3 i_targetPosition, ProjectilePropertySheetPtr i_projectile, float i_apexHeight, float i_timeToHit, TeamFlags i_team, BoardEntityPtr i_target);
    // virtual ZombieParticle* DropArm();
	virtual void onDestroy() override;
	virtual void TakeDamage(const DamageInfo& i_damage) override;
    void onEndCondition(ZombieConditions i_condition) override;

     BoardEntity* findBallTargetX();
     OVERRIDE_STATE_ONENTER(ZombieState, Walk);
     OVERRIDE_STATE_ONENTER(ZombieState, Attack);
     OVERRIDE_STATE_ONENTER(ZombieState, BleedingOut);

    // OVERRIDE_STATE_UPDATE(ZombieState, Walk);

	DECLARE_STATE_FUNCTIONS(ZombieState, CannonWaiting);
	// DECLARE_STATE_FUNCTIONS(ZombieState, CannonFiring);

    void SetDestinationPosition();
	void			onFiringAnimStopped(const std::string& i_animLabel);
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
	virtual bool hasHeadParticle() const {return false;}
    virtual std::string getAshPAMName() const { return "POPANIM_EFFECTS_ZOMBIE_CATAPULT_ASH"; }
	virtual std::string getElectrocutePAMName() const { return "POPANIM_EFFECTS_ZOMBIE_CATAPULT_SHOCK";}

protected:
	bool			m_outOfAmmoDeath;
	int				m_ammoRemaining;
    SexyVector3     m_startPos;
	SexyVector3		m_endPos;
    pvztime_t       m_waitTime;
    float           m_walkInTime;
    bool            m_Isinjured;
    bool            m_hasboard;
	std::vector<ZombieConditionEntry> m_pendingConditions;

};


class ZombieAnimRig_Catapult : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Catapult, ZombieAnimRig, RtClass);
    
    ZombieAnimRig_Catapult():Ammo(20)
    {}
    
public:
    void SetRemainingAmmo(int count);
    const std::string getIdleAnimationName() override;
	const std::string getWalkAnimationName() override;
	const std::string getDieAnimationName() override;
    void PlayAttackAnim(AnimSelectionMethod i_select, AnimStoppedDelegate i_onAnimStopped);

private:
    int Ammo;
};

#endif
