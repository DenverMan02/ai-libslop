//
//  Plant_ChardGuard.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 10/30/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_ChardGuard__
#define __PlantsVersusZombies2__Plant_ChardGuard__

#include "DamageInfo.h"
#include "PlantAnimRig.h"
#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantType.h"
#include "GameSubSystem.h"

class ChardGuardProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(ChardGuardProps, PlantPropertySheet, RtClass);
    
    ChardGuardProps()
    {
        PushesPerLeaf = 1;
        KnockbackTime = 1.0f;
        KnockbackHeight = 0.0f;
        KnockbackOffset = 96.0f;
        PFKnockbackTime = 1.0f;
        PFKnockbackHeight = 0.0f;
        PFKnockbackOffset = 96.0f;
        SuperKnockbackTime = 1.0f;
        SuperKnockbackHeight = 0.0f;
        SuperKnockbackDistance = 4;
        SuperStunDuration = 1.0f;
    }
    
    int     PushesPerLeaf;
    float   KnockbackTime;
    float   KnockbackHeight;
    float   KnockbackOffset;
    float   PFKnockbackTime;
    float   PFKnockbackHeight;
    float   PFKnockbackOffset;
    float 	SuperKnockbackTime;
    float	SuperKnockbackHeight;
    int		SuperKnockbackDistance;
    float   SuperStunDuration;

    Sexy::Rect RectZombieProximity;
    std::vector<pvztime_t> RecoverTime;
};

class PlantChardGuardTossSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(PlantChardGuardTossSystem, GameSubSystem, RtClass);
    PlantChardGuardTossSystem();

    void TossZombies(Zombie* i_zombie, const Sexy::SexyVector3 &i_target, float i_apexHeight, pvztime_t i_timeToHit);
	void onFlyingEnd(Zombie* i_zombie);
	void setStunTime(float i_time);
private:
	bool shouldStun(Zombie* i_zombie);
	void playLandEffect(const Sexy::SexyVector3 &i_pos);

	float m_time;
};

class PlantChardGuard : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantChardGuard, PlantFramework, RtClass);
    
    void Initialize() override;
    void UpdateActions() override;
    bool CanApplyPlantfood() override;
    void ApplyPlantfood() override;
    void CancelPlantfood() override;
    bool CanUpgrade(void);
    void onHealed() override;
    BoardEntityHeight GetEntityHeight() const override;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    void Idle() override;
private:
    void setState(uint i_plantState);
    void updateLeafCount(int leafCount);
    bool isFlippableZombieClose();
    bool isAnimDone();
    bool canBeFlippedByChardGuard(const Zombie* i_zombie) const;
    void damageEntitiesInGridRegion(DamageInfo i_damage, BoardEntityTypeFlag i_acceptedTypes, Rect i_rect, bool i_sameTeam);
    void flipZombie(Zombie* i_zombie);
    pvztime_t GetRecoverTime();
    
    AnimHandle m_playingAnim;
    int m_currentLeafCount;
    int m_maxLeafCount = 3;
    int m_currentFlips;
    int m_currentFlipsPerLeaf;
    pvztime_t m_recoverTime;
    pvztime_t m_recoverInterval;
};

//
// PlantAnimRig_ChardGuard
//

class PlantAnimRig_ChardGuard : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_ChardGuard, PlantAnimRig, RtClass);
    PlantAnimRig_ChardGuard();
    bool playPlantFoodOn() override;

    bool playPlantFoodMain() override;
    
	bool PlayIdleLooped() override;
	bool PlayZenGardenIdleAnim() override { return playIdleAnimation(); }
	bool PlayPreviewAnim(bool bHideLayer) override { return playIdleAnimation(); }
	pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;
	bool PlayPlantFoodEnd() override;
    
    void SetLeafCount(int leafCount);
    void SetToAttackState() { m_state = PLANTANIM_ATTACK; }
    void SetToIdleState()   { m_state = PLANTANIM_IDLE; }
    void SetToCustomState() { m_state = PLANTANIM_USERDEFINED; }
private:
    bool playIdleAnimation();
    virtual std::string getIdleAnimationName() override;
    
    int m_leafCount;
    std::string m_lastPlayedIdleAnim;
};

//
// PlantTypeChardGuard
//

class PlantTypeChardGuard : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeChardGuard, PlantType, RtClass) {}
	
	// Chard Guard can be replanted even if it's at full health as long as it's missing at least one leaf
	// void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
    bool CanPlantOnPlant(Plant* i_plant) const override;
};

#endif /* defined(__PlantsVersusZombies2__Plant_ChardGuard__) */
