//
//  ZombiePVPSkill_Rage.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15/10/21.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef ZombiePVPSkill_Rage_hpp
#define ZombiePVPSkill_Rage_hpp

#include "ZombiePVPSkill.h"

class ZombiePVPSkill_Rage : public ZombiePVPSkill
{
public:
    RT_CLASS_DEFINE(ZombiePVPSkill_Rage, ZombiePVPSkill, RtClass);
    ZombiePVPSkill_Rage();
    virtual ~ZombiePVPSkill_Rage();
private:
    void	 onAnimationDone(const std::string& i_animName);
    void DestroyRangeEffect();
    void CreateRangeEffect();
    // use playing state for all skills
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Playing);
    int CalcRenderOrder() const override;
protected:
    void onDestroy() override;
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    void onZombiePostLoad() override;
private:
    int GetRenderOrderBelow();
private:
    pvztime_t m_endTime;
    RtWeakPtr<class Effect_PopAnim> m_rangeEffect;
};

class ZombiePVPSkillRageProps : public ZombiePVPSkillProps
{
public:
    RT_CLASS_DEFINE(ZombiePVPSkillRageProps, ZombiePVPSkillProps, RtClass);
    
    ZombiePVPSkillRageProps();
    
    float SkillTime;
    std::vector<float> SpeedScale;
    float DamageScale;
};

#endif /* ZombiePVPSkill_Rage_h */
