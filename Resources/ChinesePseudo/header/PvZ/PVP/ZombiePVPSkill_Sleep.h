//
//  ZombiePVPSkill_Sleep.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.10.13
//  Copyright (c) 2015Äê PopCap Games. All rights reserved.
//

#ifndef __ZombiePVPSkill_Sleep_H__
#define __ZombiePVPSkill_Sleep_H__

#include "ZombiePVPSkill.h"


class ZombiePVPSkill_Sleep : public ZombiePVPSkill
{
public:
	RT_CLASS_DEFINE(ZombiePVPSkill_Sleep, ZombiePVPSkill, RtClass);
	ZombiePVPSkill_Sleep();
	virtual ~ZombiePVPSkill_Sleep();

protected:
	virtual void		onZombieInitialize() override;
    
    std::vector<BoardEntity*> findSleepTargets();
    bool            isValidTarget(Plant * plant);
    void				onAnimationDone(const std::string& i_animName);
	
	// use playing state for all skills
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Playing);
    
    
protected:
    std::vector<PlantPtr>   m_sleepPlants;
    pvztime_t            m_sleepingEndTime;
};

class ZombiePVPSkillSleepProps : public ZombiePVPSkillProps
{
public:
    RT_CLASS_DEFINE(ZombiePVPSkillSleepProps, ZombiePVPSkillProps, RtClass);
    
    ZombiePVPSkillSleepProps();
    
    float SleepTime;
};

#endif
