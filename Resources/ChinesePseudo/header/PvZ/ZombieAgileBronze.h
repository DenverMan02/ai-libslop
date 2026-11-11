//
//  ZombieAgileBronze.h
//  PlantsVersusZombies2
//
//  Created by Hanj on 13-12-31.
//  Copyright (c) 2013年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieAgileBronze__
#define __PlantsVersusZombies2__ZombieAgileBronze__

#include "Zombie.h"


//forward declaration
class BoardEntity;

STATE_ENUM_CHILD_BEGIN(ZombieState_AgileBronze, ZombieState)
ZS_AB_Debut,
ZS_AB_ReadyToJump,
ZS_AB_Jumping,
ZS_AB_Landing,
ZS_AB_LandingOver,
STATE_ENUM_END(ZombieState_AgileBronze)

class ZombieAgileBronze : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieAgileBronze, Zombie, RtClass);

    virtual bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;
    virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override;
    virtual Sexy::Point GetGridExtents() const override;
    
    virtual bool CanBeFlickedOff() const override
	{
        return false;
	}
    
    virtual bool CanBeStabbed() const override
    {
        return false;
    }

protected:
    virtual void onPlaceOnBoard() override;
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
	virtual void onZombieInitialize() override;
	virtual ZombieParticle* DropArm() override;
	virtual SexyVector2 GetShadowScaling() const override;
	virtual bool DoSkill(ZombieSkillType skill_type) override;

	virtual std::string getElectrocutePAMName() const override;
	virtual std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_BRONZE_ASH"; }

    SexyVector3 GetStunnedEffectOffset() const override;
    
	DECLARE_STATE_FUNCTIONS(ZombieState, Debut);
	DECLARE_STATE_FUNCTIONS(ZombieState, ReadyToJump);
	DECLARE_STATE_FUNCTIONS(ZombieState, Jumping);
	DECLARE_STATE_FUNCTIONS(ZombieState, Landing);
	DECLARE_STATE_FUNCTIONS(ZombieState, LandingOver);

private:
	int8			findWeakestRow();

	void 			onDebutAnimDone(const std::string& i_label);
	void 			onReadyToJumpAnimDone(const std::string& i_label);
	void 			onLandingOverAnimDone(const std::string& i_label);

private:

	pvztime_t 		m_startTime;
	pvztime_t		m_endTime;

	int8 			m_targetRow;
	SexyVector2 	m_shadowScale;
};

#endif /* defined(__PlantsVersusZombies2__ZombieAgileBronze__) */
