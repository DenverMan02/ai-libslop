//
//  ZombieAirbubble.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/4/19.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef ZombieAirbubble_h
#define ZombieAirbubble_h

#include "Zombie.h"
#include "PvZ2IDs.h"
#include "Plant.h"

STATE_ENUM_CHILD_BEGIN(ZombieStateAirbubble, ZombieState)
ZS_AB_FlyToTarget,
ZS_AB_AttachingToPlant,
ZS_AB_AttachedToPlant,
ZS_AB_PickingUpPlant,
ZS_AB_DestroyingPlant,
ZS_AB_FlyingAway,
STATE_ENUM_END(ZombieStateAirbubble)

struct PlantCache
{
    SexyVector3 plantPos;
    uint        plantState;
    int         plantRow;
    
    PlantCache()
    {
        plantPos = SexyVector3(-1, -1, 0);
        plantState = -1;
        plantRow = -1;
    }
};

class ZombieAirbubble : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieAirbubble, Zombie, RtClass);
    
    void SetTargetColAndRow(int i_col, int i_row);
    void SetToygun(ZombiePtr i_toygun);
    void OnToygunDied();
    
    virtual bool CollidesWithType(CollisionTypeFlags i_collisionFlags) const override;
    
protected:
    virtual void onZombieInitialize() override;
    virtual void onPlaceOnBoard() override;
    virtual void onApplyCondition(ZombieConditions i_condition) override;
    virtual void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
    bool willDieToShrinking() override { return true; }
    
    
    std::string getElectrocutePAMName() const override { return "POPANIM_EFFECTS_CHILDREN_AIRBUBBLE_DIE"; }
    std::string getAshPAMName() const override { return "POPANIM_EFFECTS_CHILDREN_AIRBUBBLE_DIE"; }

    virtual void onDestroy() override;
    
    // Parrot shadow changes when flying away
    virtual SexyVector2 GetShadowScaling() const override;
    
    virtual class Plant* findPlantTarget();
    
    DECLARE_STATE_FUNCTIONS(ZombieState, FlyToTarget);
    DECLARE_STATE_FUNCTIONS(ZombieState, AttachingToPlant);
    DECLARE_STATE_FUNCTIONS(ZombieState, AttachedToPlant);
    DECLARE_STATE_FUNCTIONS(ZombieState, PickingUpPlant);
    DECLARE_STATE_FUNCTIONS(ZombieState, DestroyingPlant);
    DECLARE_STATE_FUNCTIONS(ZombieState, FlyingAway);
    
protected:
    virtual bool moveToDestination(const float i_destX, const float i_destY);
    
protected:
    int				m_targetCol;
    int				m_targetRow;
    
    bool m_attaching;
    SexyVector3 m_startingPos;
    
    pvztime_t m_attachingTime;
    pvztime_t m_attachingStartTime;
    
    ZombiePtr		m_toygun;
    PlantPtr		m_pickedUpPlant;
    PlantCache      m_plantCache;
};


class ZombieWaveAirbubble : public ZombieAirbubble
{
public:
    RT_CLASS_DEFINE(ZombieWaveAirbubble, ZombieAirbubble, RtClass);

    OVERRIDE_STATE_UPDATE(ZombieState, DestroyingPlant);
    OVERRIDE_STATE_ONENTER(ZombieState, DestroyingPlant);

    virtual bool CanBeMowed() const override;

    void SetFloatInfo(float i_speed, float i_phase);
    virtual void onApplyCondition(ZombieConditions i_condition) override;
    void FlyAway();

protected:
    virtual bool moveToDestination(const float i_destX, const float i_destY);

    float m_speed;
    float m_phase;
};

#endif /* ZombieAirbubble_h */
