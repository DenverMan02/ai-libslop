//
//  ZombieRomanBallista
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 11/25/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIE_ROMANBALLISTA_H__
#define __ZOMBIE_ROMANBALLISTA_H__

#include <string>
#include <vector>

#include "DamageInfo.h"
#include "Projectile.h"
#include "ProjectilePropertySheet.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieEnums.h"
#include "ZombieAnimRig.h"
#include "ProbabilityTypeContainer.h"

class ZombieRomanBallistaProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieRomanBallistaProps, ZombiePropertySheet, RtClass);

    ZombieRomanBallistaProps()
    {
        InitialShotCooldown = 3.0f;
        ShotCooldown = 8.0f;
        ChanceImpFallsInWater = 0.1f;
        VaseShotHeight = 80.f;
        VaseShotTime = 1.f;
        VaseTargetLeftmostGridXOffset = -10;
        VaseTargetRightmostGridXOffset = -1;
        VaseDefaultGridX = 3;
    }

    float InitialShotCooldown;
    float ShotCooldown;
    float ChanceImpFallsInWater;
    float TimeToWalkInToPosition;
    float VaseShotHeight;
    float VaseShotTime;
    int VaseTargetLeftmostGridXOffset;
    int VaseTargetRightmostGridXOffset;
    int VaseDefaultGridX;

    RtWeakPtr<RtObject>     VaseProjectile;
    
    ProbabilityTypeContainer    ZombieSpawnData;
    
    void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};


class ZombieRomanBallista : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieRomanBallista, Zombie, RtClass);

	bool CanApplySpecialCondition();
	bool CanApplyVenomStack() override;

protected:
    void playDeathAnimation() override;
	void onApplyCondition(ZombieConditions i_condition) override;
	bool isImmuneToShrinking() override { return true; }
    bool hasHeadParticle() const override;

protected:
    // dispatch from parent class.
	void onPlaceOnBoard() override;
	void onUpdate() override;
	void chooseDeathState(const DamageInfo& i_deathBlow) override;
    
    virtual void launchVase();
    //void launchProjectileAt(Projectile* i_projectile, const Sexy::SexyVector3 &i_targetLoc, float i_lobHeight, float i_timeOfFlight, float i_heightVariance, float i_timeOfFlightVariance);
    void launchProjectile(SexyVector3 i_source, SexyVector3 i_targetPosition, ProjectilePropertySheetPtr i_projectile, float i_apexHeight, float i_timeToHit, TeamFlags i_team, BoardEntityPtr i_target);

    float findVaseTargetX();
    Rect calcRangedTargetGridRect() override;
    
    // states
    OVERRIDE_STATE_ONENTER(ZombieState, Walk);
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);

	DECLARE_STATE_FUNCTIONS(ZombieState, CannonWaiting);
	DECLARE_STATE_FUNCTIONS(ZombieState, CannonPrepForFire);
	DECLARE_STATE_FUNCTIONS(ZombieState, CannonFiring);
	DECLARE_STATE_FUNCTIONS(ZombieState, CannonExplode);
    
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

    DamageInfo modifyBodyDamage(const DamageInfo& i_incomingDamage) override;
	
	void			onPrepAnimStopped(const std::string& i_animLabel);
	void			onFiringAnimStopped(const std::string& i_animLabel);
	void			onExplodeAnimStopped(const std::string& i_animLabel);
	
	int				m_ammoRemaining;
    SexyVector3     m_startPos;
	SexyVector3		m_endPos;
    pvztime_t       m_waitTime;
	bool			m_outOfAmmoDeath;
	
	std::vector<ZombieConditionEntry> m_pendingConditions;

};

///// AnimRig

class ZombieAnimRig_RomanBallista : public ZombieAnimRig
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_RomanBallista, ZombieAnimRig, RtClass) {}
    
    ZombieAnimRig_RomanBallista();
    
private:
    const std::vector<std::string>& getHeadLayerNames() override;
};

class RomanBallistaProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(RomanBallistaProjectile, Projectile, RtClass);
    
    RomanBallistaProjectile();
    virtual ~RomanBallistaProjectile();

    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;

    void Initialize(RtWeakPtr<PropertySheetBase> i_ballistaTypeProps);
    
    void SetRandomObject(class MTRand* i_rand) { m_randomObject = i_rand; }

private:
    RtWeakPtr<PropertySheetBase> BallistaTypeProps;
    class MTRand* m_randomObject;
};

#endif
