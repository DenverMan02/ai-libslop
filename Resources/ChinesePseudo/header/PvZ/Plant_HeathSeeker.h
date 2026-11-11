//
//  Plant_HeathSeeker.h
//  PlantsVersusZombies2
//
//  Created by Sai Prasad on 12/05/21.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_HeathSeeker__
#define __PlantsVersusZombies2__Plant_HeathSeeker__

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RtObject.h"
#include "ZombieEnums.h"
#include "EntityFinder.h"

class HeathSeekerProps : public PlantPropertySheet
{
public:
RT_CLASS_DEFINE(HeathSeekerProps, PlantPropertySheet, RtClass);

    HeathSeekerProps()
	{
    	DartCount = 5;
    	DartCountLv2 = 5;
    	DartCountLv3 = 5;
        DartStartOffset = 40;
        DartSlotDegree = 25;
        PiercingDamage = 40;
        FinalDamage = 300;
        MaxTargets = 3;
        MaxTargetsLv2 = 3;
        MaxTargetsLv3 = 3;
        DartsDiffTime = 0.2;
	}

    int DartCount;
    int DartCountLv2;
    int DartCountLv3;
	int DartStartOffset;
	int DartSlotDegree;
    int PiercingDamage;
    int FinalDamage;
    int MaxTargets;
    int MaxTargetsLv2;
    int MaxTargetsLv3;
    float DartsDiffTime;
};

class PlantHeathSeeker : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantHeathSeeker, PlantFramework, RtClass);

	PlantHeathSeeker();

	void	Initialize() override;
//	bool 	MoveTop(int nId);
	void	UpdateActions() override;
	
	void	SpawnProjectile(int i_forwardSlotOffset);
//	CollisionTypeFlags GetCollisionFlags() const override;
	CollisionTypeFlags GetCollisionFlags() const;
	
	bool CanBeShoveled()		override { return false; }
	bool CanBeTargeted()		override { return false; }
	bool IsInvincible() const	override { return true; }
//	void TakeSmashAttack(BoardEntity* i_instigator) override {}
	void TakeSmashAttack(BoardEntity* i_instigator) {}
	
//	Projectile*	Fire(Zombie* targetZombie, PlantWeapon i_plantWeapon) override;
	Projectile*	Fire(Zombie* targetZombie, PlantWeapon i_plantWeapon);

private:
    enum State
    {
        STATE_START_ATTACK = STATE_FRAMEWORK_BEGIN,
        STATE_ATTACK,
        STATE_FINISH_ATTACK
    };
    void setState(const uint i_state);
    void onAnimStoppedCallback(const std::string& i_animLabel) override;
    
    std::vector<RtWeakPtr<BoardEntity>> m_pfTargets;
    std::vector<RtWeakPtr<BoardEntity>> m_priorityTargets;
	bool m_projectileStarted;
	float m_nextProjectileTime;
	int m_pfShotIndex;
    bool m_geneDoubleProjectile;
};


class PlantAnimRig_HeathSeeker : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_HeathSeeker, PlantAnimRig, RtClass);

    void StartAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void LoopAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void StopAttacking(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};

class HeathSeekerProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(HeathSeekerProjectileProps, ProjectilePropertySheet, RtClass);
	
	HeathSeekerProjectileProps()
		: SuperClass {}
		, MaxRotationsPerSecond {2.5}
		, Lifetime {5.0}
	{
	}

	float MaxRotationsPerSecond;
	float Lifetime;
};

class HeathSeekerProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(HeathSeekerProjectile, Projectile, RtClass);
	
	HeathSeekerProjectile();
    void InitializeHeathSeeker(BoardEntity* i_overrideTarget, int i_piercingDamage, int i_finalDamage, int i_maxTargets);
    bool shouldDeprioritizeTarget(const BoardEntity* i_target);
    
protected:
	void onDeflection(class BoardEntity* i_deflector) override;
	void moveThroughTime(pvztime_t i_dt) override;
	void damageEntity(BoardEntity* i_entity) override;
	float calcDesiredRot(SexyVector3 i_toTarget, float i_currentRot);
    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
//	void getCollisionEntities(std::vector<BoardEntity*> &o_entities) const override;
    void getCollisionEntities(std::vector<BoardEntity*> &o_entities,const Rect& i_projectileRect) const override;

private:
	RtWeakPtr<BoardEntity> m_overrideTarget;
	std::vector<RtWeakPtr<BoardEntity>> m_targetsAlreadyHit ;

	bool m_deflected;
	float m_createTime;
	int m_numberOfTargetsHit;
    int m_finalDamage;
    int m_maxTargets;

    bool isValidTarget(BoardEntity* i_target);
	std::vector<BoardEntity*> getTargets();
    bool checkAndMoveToNextZombie();
};

namespace EntityFinder
{
    class BoardEntitySorter_Closest_PreferNewTargets : public BoardEntitySorter
    {
    public:
        BoardEntitySorter_Closest_PreferNewTargets(SexyVector3 i_refPos, const std::vector<RtWeakPtr<BoardEntity>>& i_previousTargets, float i_nearestTargetFactor, float i_homingdistanceFactor, bool i_prioritizeZombies,  std::function<bool(const BoardEntity*)> i_shouldDeprioritizeTarget);
        bool operator()(BoardEntity* i_a, BoardEntity *i_b) const override;
        
    private:
        bool isPreviousTarget(BoardEntity* i_entity) const;
        
        SexyVector3 m_refPos;
        std::vector<RtWeakPtr<BoardEntity>> m_previousTargets;
        float m_nearestTargetFactor, m_homingdistanceFactor;
        bool m_prioritizeZombies;
        std::function<bool(const BoardEntity*)> m_shouldDeprioritizeTarget;
    };
}

#endif /* defined(__PlantsVersusZombies2__Plant_HeathSeeker__) */
