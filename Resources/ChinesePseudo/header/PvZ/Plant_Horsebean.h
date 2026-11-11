//
//  Plant_Horsebean.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15-7-16.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Horsebean__
#define __PlantsVersusZombies2__Plant_Horsebean__

#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantAnimRig.h"
#include "HorsebeanPlane.h"
#include "StateMachine.h"

STATE_ENUM_BASE_BEGIN(PHBState)
PHBState_IDLE,
PHBState_ATTACK,
PHBState_COOLDOWN,
PHBState_PLANTFOOD,
STATE_ENUM_END(PHBState);

class HorsebeanProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(HorsebeanProps, PlantPropertySheet, RtClass);
    
    HorsebeanProps();
    
    int     NormalPlaneCount;
    int     PlantFoodPlaneCount;
    
    float   PlantFoodTime;
    float   AttackInterval;
    float   PlantFoodAttackInterval;
    float   AvatarPlantFoodAttackInterval;
};

class PlantHorsebean : public PlantFramework
{
public:
    
    PlantHorsebean();
    virtual ~PlantHorsebean();
    
    RT_CLASS_DEFINE(PlantHorsebean, PlantFramework, RtClass);
    
    void    Initialize() override;
    
    void    UpdateActions() override;
    
    bool	CanApplyPlantfood() override;
    void    ApplyPlantfood()    override;
    
    bool    OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
    void	onKilled(bool i_instantKill) override;
    
    Sexy::Rect GetPlantAttackRect(PlantWeapon i_plantWeapon) override;
    
protected:
    
    DECLARE_STATE_FUNCTIONS(PHBState, IDLE);
    DECLARE_STATE_FUNCTIONS(PHBState, ATTACK);
    DECLARE_STATE_FUNCTIONS(PHBState, COOLDOWN);
    DECLARE_STATE_FUNCTIONS(PHBState, PLANTFOOD);
    
    void setState(PHBState i_newState);
    bool isInState(PHBState i_state) const;
    
    int32 getPlantHorsebeanStateSerialization();
    void  setPlantHorsebeanStateSerialization(int32 i_state);
    
    void TakeOff();
    
    bool FindTarget(PlantWeapon weapon,std::vector<BoardEntityPtr>& target);
    
    void onHorseBeanPlaneTurnBack(Plant * parent,int index);
    
    void onTakeOffAnimDone(const std::string& i_label);
    void onAttackOffAnimDone(const std::string& i_label);
    
private:
    
    pvztime_t                                    m_nextTakeOff;
    pvztime_t                                    m_timePlantFoodEnd;
    pvztime_t                                    m_timeAttack;
    
    int                                          m_IndexPlane;
    
    StateMachine<PHBState>                       m_PHBState;
    
    bool                                         m_bInPlantFood;
    
    std::vector<RtWeakPtr<class HorsebeanPlane>> m_planes;
};

enum PlantAnimRigState_PotatoMine
{
    PLANTANIM_POTATOMINE_TAKE_OFF = PLANTANIM_USERDEFINED,
    PLANTANIM_POTATOMINE_TAKE_OFF_IDLE,
};

class PlantAnimRig_Horsebean : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Horsebean, PlantAnimRig, RtClass);
    
    PlantAnimRig_Horsebean();
    
    bool PlayTakeOff(const std::string& i_animLabel,AnimStoppedDelegate i_onAnimStopped);
    bool PlayAttackOff(const std::string& i_animLabel,AnimStoppedDelegate i_onAnimStopped);
    
    bool PlayAttackLoop();
    bool PlayCoolDownLoop();
    
private:
    
};



#endif /* defined(__PlantsVersusZombies2__Plant_Horsebean__) */
