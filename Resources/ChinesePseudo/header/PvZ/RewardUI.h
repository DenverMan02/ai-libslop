//
//  RewardUI.h
//  PlantsVersusZombies2
//
//  Created by shizf on 16/5/18.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef RewardUI_h
#define RewardUI_h

#include "Widget.h"
#include "core.h"
#include "RtObject.h"
#include "PVZTypes.h"
#include "StateMachine.h"
#include "TimeMgr.h"

STATE_ENUM_BASE_BEGIN(RewardAniState)
    REWARD_ANI_STATE_Init,
    REWARD_ANI_STATE_Update,
    REWARD_ANI_STATE_End,
STATE_ENUM_END(RewardAniState)

class RewardUI : public Sexy::Widget
{
public:
    RT_CLASS_DEFINE(RewardUI, RtObject, RtClass);
    
    RewardUI();
    virtual ~RewardUI();
    
    virtual void Update() override;
    
protected:
    // State management
    virtual void setState(const RewardAniState i_newState);
    
    DECLARE_STATE_FUNCTIONS_EMPTY(RewardAniState, Init);
    DECLARE_STATE_FUNCTIONS_EMPTY(RewardAniState, Update);
    DECLARE_STATE_FUNCTIONS_EMPTY(RewardAniState, End);
    
    StateMachine<RewardAniState> m_stateMachine;			// Our state machine
};


class RewardPlantUI : public RewardUI
{
public:
    RewardPlantUI(PlantTypePtr i_plant, bool bStatic = true);
    virtual ~RewardPlantUI();
    
    virtual void Draw(Sexy::Graphics* i_g) override;
    
    virtual void TouchBegan(const Sexy::Touch& touch) override;
    
protected:
    OVERRIDE_STATE_FUNCTIONS(RewardAniState, Init);
    OVERRIDE_STATE_FUNCTIONS(RewardAniState, Update);
    OVERRIDE_STATE_FUNCTIONS(RewardAniState, End);
    
private:
    PlantTypePtr m_plant;
    
    class Sexy::Image* m_plantImage;
    class PlantAnimRig* m_plantAnimRig;
    class Effect_PopAnim* m_plantAnimEffect;
    class Effect_PopAnim* m_plantLightEffect;
    
    pvztime_t m_rewardFlyingTime;
    pvztime_t m_rewardFlyingEndTime;
    pvztime_t m_rewardPlantAnimTime;
    pvztime_t m_rewardPlantShowTime;
    
    float m_scale;
    bool m_bStatic;
};

#endif /* RewardDialog_h */
