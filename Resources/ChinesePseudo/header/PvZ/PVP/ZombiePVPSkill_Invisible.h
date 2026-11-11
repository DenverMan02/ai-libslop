//
//  ZombiePVPSkill_Invisible.hpp
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 15/11/6.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef ZombiePVPSkill_Invisible_hpp
#define ZombiePVPSkill_Invisible_hpp

#include "ZombiePVPSkill.h"
#include "GameSubSystem.h"

class ZombiePVPSkill_Invisible : public ZombiePVPSkill
{
public:
    RT_CLASS_DEFINE(ZombiePVPSkill_Invisible, ZombiePVPSkill, RtClass);
    ZombiePVPSkill_Invisible();
    virtual ~ZombiePVPSkill_Invisible();
private:
    void	 onZombieInitialize() override;
    void	 onAnimationDone(const std::string& i_animName);
    void CreateRangeEffect();
    void DestroyRangeEffect();
    float GetSkillTime();
    // use playing state for all skills
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Playing);
protected:
    void onDestroy() override;
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
private:
    pvztime_t m_endTime;
    RtWeakPtr<class Effect_PopAnim> m_rangeEffect;
};

class ZombiePVPSkillInvisibleProps : public ZombiePVPSkillProps
{
public:
    RT_CLASS_DEFINE(ZombiePVPSkillInvisibleProps, ZombiePVPSkillProps, RtClass);
    
    ZombiePVPSkillInvisibleProps();
    
    std::vector<float> SkillTime;
};

class PVPInvisibleSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(PVPInvisibleSubsystem, GameSubSystem, RtClass);
    void Register(const ZombiePtr& skill);
    void Unregister(const ZombiePtr& skill);
    void Update() override;
    PVPInvisibleSubsystem();
private:
    bool Intersect(Zombie* zombie);
private:
    bool m_allZombieVisible;
    std::vector<ZombiePtr> m_item;
};

#endif /* ZombiePVPSkill_Invisible_hpp */
