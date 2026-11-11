//
//  Plant_Jackfruit.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-12-4.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PlantJackfruit_h
#define PlantsVersusZombies2_PlantJackfruit_h

#include "PlantFramework.h"
#include "Projectile.h"
#include "ZombieLostcityGuide.h"

enum JACKFRUITANIMSTATE
{
    JACKFRUIT_RUN = PLANTANIM_USERDEFINED + 1,
    JACKFRUIT_JUMP
};


class GridItemJackFruitPropertySheet : public GridItemPropertySheet
{
public:
    RT_CLASS_DEFINE(GridItemJackFruitPropertySheet, GridItemPropertySheet, RtClass);
    
    GridItemJackFruitPropertySheet()
    {}

};


class GridItemJackFruit : public GridItem
{
public:
    RT_CLASS_DEFINE(GridItemJackFruit, GridItem, RtClass);
    
    GridItemJackFruit();
    
    virtual ~GridItemJackFruit();
    
    bool IsDamageableByPlants() const override { return false; }
    void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
    
protected:
    
    void registerForEvents() override;
    void onGridItemInitialize() override;
    void onUpdate() override;
    void onDraw(class Sexy::Graphics* i_g) override;
    
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
    void TakeDamage(const DamageInfo& i_damage) override;
    
private:
    
    RtWeakPtr<class Effect_PopAnim> m_pRenderRig;
    
};

class PlantJackfruit : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantJackfruit, PlantFramework, RtClass);
    
    PlantJackfruit() : m_iJumpSpeed(0) {}
    
    virtual ~PlantJackfruit() {}
    
    void DestorySelf();

protected:
    
    bool CanApplyPlantfood() override;
    
	void Initialize() override;
    
    void UpdateActions() override;
    
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
    
    GridItemPtr FindTargetDamageableGridItem(Rect& i_gridRect, PlantWeapon i_plantWeapon) override;
    
    bool CanBeTargeted() override;
    
    bool CanBeTargetedBy(const BoardEntity* i_entity) override;
    
private:
    
    void UpdateLogic();
    
    void UpdateAnimation();
    
    void UpdateJackfruitPosition(float iSpeed);
    
    void PlayHitEffect();
    
    GuideEndDoor* GetValidGuideEndDoor();
    
    bool HaveDamage(BoardEntityPtr ptr);
    
private:
    
    float m_iJumpSpeed;
    
    GuideEndDoorPtr m_ptrTargetGuideEndDoor;
    
    std::vector<BoardEntityPtr> m_vDamageBoardEntity;
    
};


class JackfruitPropertySheet : public PlantPropertySheet
{
    
public:
    
    RT_CLASS_DEFINE(JackfruitPropertySheet, PlantPropertySheet, RtClass);
    
    JackfruitPropertySheet()
    : NormalSpeed(40)
    , AttackingSpeed(40)
    , GuideInterval(100) {}
    
    float NormalSpeed;
    float AttackingSpeed;
    int GuideInterval;
    
};


class PlantAnimRig_Jackfruit : public PlantAnimRig
{
public:
    
    RT_CLASS_DEFINE(PlantAnimRig_Jackfruit, PlantAnimRig, RtClass);
    
    PlantAnimRig_Jackfruit() {}
    
    void PlayNormalRun();
    
    void PlayJump();
    
    pvztime_t GetJumpTimeLength();
    
    void SetAttachTarget(PlantPtr ptr) { m_ptrAttachTarget = ptr; }
    
protected:
    
    void onAnimStopped() override;
    
    void onUpdate() override;
    
private:
    
    bool PlayOnceCommon(JACKFRUITANIMSTATE pstate, const std::string& strLabel);
    
    void PlayLoopCommon(JACKFRUITANIMSTATE pstate, const std::string& strLabel);
    
private:
    
    PlantPtr m_ptrAttachTarget;
    
};

#endif
