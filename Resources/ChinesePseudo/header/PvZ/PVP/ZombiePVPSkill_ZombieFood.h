//
//  ZombiePVPSkill_ZombieFood.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15/11/10.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef ZombiePVPSkill_ZombieFood_hpp
#define ZombiePVPSkill_ZombieFood_hpp

#include "ZombiePVPSkill.h"

class ZombiePVPSkill_ZombieFood : public ZombiePVPSkill
{
public:
    RT_CLASS_DEFINE(ZombiePVPSkill_ZombieFood, ZombiePVPSkill, RtClass);
    ZombiePVPSkill_ZombieFood();
    virtual ~ZombiePVPSkill_ZombieFood();
private:
    void	 onAnimationDone(const std::string& i_animName);
    void DestroyRangeEffect();
    RtWeakPtr<class Effect_PopAnim> CreateRangeEffect();
    // use playing state for all skills
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Playing);
protected:
    void onDestroy() override;
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    void onZombiePostLoad() override;
private:
    int GetRenderOrderBelow();
private:
    bool m_takeEffect;
    RtWeakPtr<class Effect_PopAnim> m_rangeEffect;
    RtWeakPtr<class Effect_PopAnim> m_rangeEffect2;
};

#endif /* ZombiePVPSkill_ZombieFood_hpp */
