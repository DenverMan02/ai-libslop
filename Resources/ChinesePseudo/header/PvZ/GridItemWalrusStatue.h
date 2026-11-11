//
//  GridItemWalrusStatue.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-3-16.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_GridItemWalrusStatue_h
#define PlantsVersusZombies2_GridItemWalrusStatue_h

#include "GridItem.h"
#include "Zombie.h"
#include "GridItemAnimation.h"

STATE_ENUM_BASE_BEGIN(WalrusStatueState)
    StatueState_FullHeal,
    StatueState_MidHeal,
    StatueState_EmptyHeal,
STATE_ENUM_END(WalrusStatueState);

class GridItemWalrusStatuePropertySheet : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemWalrusStatuePropertySheet, GridItemAnimationProps, RtClass);
    
    GridItemWalrusStatuePropertySheet()
    {}
};


class GridItemWalrusStatue : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemWalrusStatue, GridItemAnimation, RtClass);
    
    GridItemWalrusStatue();
    
    virtual ~GridItemWalrusStatue();
    
    void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
    
    void SetPos(Sexy::SexyVector2 v2);
    
protected:
    
    void registerForEvents() override;
    void onGridItemInitialize() override;
    void onUpdate() override;
    int	 CalcRenderOrder() const override;
    
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override;
    bool IsDamageableByPlants() const override	{ return true; }
    bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override { return true; }
    void TakeDamage(const DamageInfo& i_damage) override;
    
    DECLARE_STATE_FUNCTIONS(WalrusStatueState, FullHeal);
    DECLARE_STATE_FUNCTIONS(WalrusStatueState, MidHeal);
    DECLARE_STATE_FUNCTIONS(WalrusStatueState, EmptyHeal);
    
    void setState(WalrusStatueState i_newState);
    
    WalrusStatueState getState() const;
    
    bool isInState(uint32 i_state) const;
    
    int32 getWalrusStatueStateSerialization();
    
    void setWalrusStatueStateSerialization(int32 i_state);
    
    void RenderInit();
    
private:
    
    RtWeakPtr<class Effect_WalrusStatue> m_pRenderRig;
    StateMachine<WalrusStatueState> m_WalrusStatueState;
};

class Effect_WalrusStatue : public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_WalrusStatue, Effect_PopAnim, RtClass);
    Effect_WalrusStatue() : m_bDieExit(false) {}
    virtual ~Effect_WalrusStatue() {}
    
    void PlayFullHeal();
    
    void PlayMidHeal();
    
    void PlayDieExit();
    
    void SetStatuePosition(Sexy::SexyVector2 v2);
    
protected:
    
    void onUpdate() override;
    
private:
    
    bool m_bDieExit;
    
};

#endif
