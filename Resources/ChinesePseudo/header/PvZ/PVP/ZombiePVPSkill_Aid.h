//
//  ZombiePVPSkill_Aid.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.10.12
//  Copyright (c) 2015Äê PopCap Games. All rights reserved.
//

#ifndef __ZombiePVPSkill_Aid_H__
#define __ZombiePVPSkill_Aid_H__

#include "ZombiePVPSkill.h"
#include "GameSubSystem.h"

class ZombiePVPSkill_Aid : public ZombiePVPSkill
{
public:
	RT_CLASS_DEFINE(ZombiePVPSkill_Aid, ZombiePVPSkill, RtClass);
	ZombiePVPSkill_Aid();
	virtual ~ZombiePVPSkill_Aid();
    int CalcRenderOrder() const override;
protected:
    void onDestroy() override;
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Playing);
private:
    void CreateAidEffect();
    void DestroyAidEffect();
    void	 onAnimationDone(const std::string& i_animName);
    int GetRenderOrderBelow() const;
private:
    bool m_isDrop;
    pvztime_t m_endTime;
    RtWeakPtr<class Effect_PopAnim> m_aidEffect;
};

class ZombiePVPSkillAidProps : public ZombiePVPSkillProps
{
public:
    RT_CLASS_DEFINE(ZombiePVPSkillAidProps, ZombiePVPSkillProps, RtClass);
    
    ZombiePVPSkillAidProps();
    float SkillTime;
    std::vector<float> AddHitpoints;
};

class PVPAidSubsystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(PVPAidSubsystem, GameSubSystem, RtClass);
    void Register(const ZombiePtr& skill);
    void Unregister(const ZombiePtr& skill);
    void Update() override;
    PVPAidSubsystem();
private:
    bool Intersect(Zombie* zombie);
    float GetAddHp();
private:
    pvztime_t m_nextUpdate;
    float m_addHp;
    std::vector<ZombiePtr> m_item;
};

#endif
