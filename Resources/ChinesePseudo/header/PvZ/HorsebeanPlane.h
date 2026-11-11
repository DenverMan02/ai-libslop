//
//  HorsebeanPlane.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-7-25.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__HorsebeanPlane__
#define __PlantsVersusZombies2__HorsebeanPlane__

#include "BoardEntity.h"
#include "StateMachine.h"
#include "Projectile.h"
#include "Plant.h"

STATE_ENUM_BASE_BEGIN(HBPState)
HBPState_INIT,
HBPState_FLYTOTARGET,
HBPState_ATTACK,
HBPState_FLYAWAY,
HBPState_TURNBACK,
HBPState_END,
STATE_ENUM_END(HBPState);

enum EHorseBeanType
{
    EHorseBeanType1 = 0,
    EHorseBeanType2,
    EHorseBeanType3,
    EHorseBeanType_Count
};

class HorsebeanPlane : public BoardEntity
{
public:
	RT_CLASS_DEFINE(HorsebeanPlane, BoardEntity, RtClass);
    
	HorsebeanPlane();
	virtual ~HorsebeanPlane();
    
    void    HorsebeanPlaneInitialize(EHorseBeanType i_horseBeanType,
                                     PlantPtr i_parent,
                                     int i_index,
                                     int i_currentLevel,
                                     bool i_isAvater);
    
    int  CalcRenderOrder()  const override;
    bool ShouldDrawShadow() const override { return false; }
    
    void MoveToTarget(SexyVector2 i_endPosition);
    void SetRayTarget(BoardEntityPtr i_target) { m_target = i_target; }
    
protected:
    
    virtual void onDraw(class Sexy::Graphics* i_g) override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
    
    DECLARE_STATE_FUNCTIONS(HBPState, INIT);
    DECLARE_STATE_FUNCTIONS(HBPState, FLYTOTARGET);
    DECLARE_STATE_FUNCTIONS(HBPState, ATTACK);
    DECLARE_STATE_FUNCTIONS(HBPState, FLYAWAY);
    DECLARE_STATE_FUNCTIONS(HBPState, TURNBACK);
    DECLARE_STATE_FUNCTIONS(HBPState, END);
    
    void setState(HBPState i_newState);
    bool isInState(HBPState i_state) const;
    
    int32 getHorsebeanPlaneStateSerialization();
    void  setHorsebeanPlaneStateSerialization(int32 i_state);
    
    void onFlyToTargetDone(BoardEntity * target);
    void onFlyAwayDone(BoardEntity * target);
    void onTurnBackDone(BoardEntity * target);
    
    void onAttackAnimDone(const std::string& i_label);
    
    void onAnimCommand(const std::string& i_animLabel,
                       pvztime_t i_timeStamp,
                       const std::string& i_animCommand,
                       const std::string& i_animCommandParam);
    
private:
    RtWeakPtr<class PopAnimRig>	m_popAnimRig;
    StateMachine<HBPState> 		m_HBPState;
    
    SexyVector2                 m_posLast;
    float                       m_angle;
    bool                        m_mirrorX;
    
    SexyVector3                 m_posTakeOff;
    EHorseBeanType              m_horseBeanType;
    PlantPtr                    m_parent;
    int                         m_nIndex;
    int                         m_currentLevel;
    BoardEntityPtr				m_target;
};

class HorseBeanProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(HorseBeanProjectile, Projectile, RtClass);
    
    virtual int GetRenderOrder() const override { return RENDER_LAYER_ABOVE_UI; }
};

namespace Message
{
	void HorseBeanPlaneTurnBack(Plant * parent,int index);
}

#endif /* defined(__PlantsVersusZombies2__HorsebeanPlane__) */
