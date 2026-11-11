//
//  ZombiePVPSkill_Bomb.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.9.30
//  Copyright (c) 2015Äê PopCap Games. All rights reserved.
//

#ifndef __ZombiePVPSkill_Bomb_H__
#define __ZombiePVPSkill_Bomb_H__

#include "ZombiePVPSkill.h"
#include "CannonRocket.h"

//-----------------------------------------------------
//-----------------------------------------------------
class ZombiePVPSkill_Bomb : public ZombiePVPSkill
{
public:
	RT_CLASS_DEFINE(ZombiePVPSkill_Bomb, ZombiePVPSkill, RtClass);
	ZombiePVPSkill_Bomb();
	virtual ~ZombiePVPSkill_Bomb();

protected:
	virtual void		onZombieInitialize() override;
	virtual class   BoardEntity* findTarget() override;
    
    void				onAnimationDone(const std::string& i_animName);
    void            onPVPSkillBombRocketExploded(class PVPSkillBombRocket* pRocket);
	
	// use playing state for all skills
	virtual void		onEnterState_Playing(ZombieState i_oldState) override;
	virtual void		updateState_Playing() override;
	virtual void		onExitState_Playing(ZombieState i_newState) override;
    
protected:
    RtWeakPtr<class PVPSkillBombRocket> m_rocketPtr;
};

//-----------------------------------------------------
//-----------------------------------------------------
class PVPSkillBombRocket : public CannonRocket
{
public:
    RT_CLASS_DEFINE(PVPSkillBombRocket, CannonRocket, RtClass);
    PVPSkillBombRocket();
    
    virtual void OnRocketHitGround() override;
    
    
};


//-----------------------------------------------------
//-----------------------------------------------------
namespace Message
{
    void PVPSkillBombRocketExploded(class PVPSkillBombRocket* pRocket);
}



#endif
