//
//  ZombieSwashbuckler.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/11/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIESWASHBUCKLER_H__
#define __ZOMBIESWASHBUCKLER_H__

#include <string>

#include "DamageInfo.h"
#include "Rect.h"
#include "RtDb.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "StateMachine.h"
#include "Zombie.h"
#include "ZombieEnums.h"

class PlantType;
namespace Sexy {
class Graphics;
}  // namespace Sexy

STATE_ENUM_CHILD_BEGIN(ZombieStateSwashbuckler, ZombieState)
	ZS_SB_Intro,
	ZS_SB_SwingSucceed,
	ZS_SB_SwingFail,
STATE_ENUM_END(ZombieStateSwashbuckler);

class ZombieSwashbucklerProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieSwashbucklerProps, ZombiePropertySheet, RtClass);
	
	ZombieSwashbucklerProps()
	{
		MinLandingColumn = 5;
		MaxLandingColumn = 5;
		FallIntoDrinkChance = 0.05f;
	}
	
	int8 MinLandingColumn;
	int8 MaxLandingColumn;
	float FallIntoDrinkChance;
};

class ZombieSwashbuckler : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieSwashbuckler, Zombie, RtClass);

	virtual SexyVector3 CalcProjectileTargetLocation(float i_inTime) override;

	virtual Sexy::Rect calcCollisionRect() override;
	virtual Sexy::Rect CalcZombieAttackRect() override;

	virtual bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;
	virtual bool IsSwingingIn() const override { return m_swinging; }
    bool ShouldDrawShadow() const override;
	bool DeathOnLanding() { return m_deathOnLanding; }
	
protected:
    
    virtual int GetLandingColumn();
    
	virtual void onZombieInitialize() override;
	virtual void onPlaceOnBoard() override;

	void onApplyCondition(ZombieConditions i_condition) override;
	void chooseDeathState(const DamageInfo &i_deathBlow) override;
	
	virtual BoardEntity * findTarget() override;
    
	void onSwingIntroAnimDone(const std::string& i_animName);
	void onSwingSucceedAnimDone(const std::string& i_animName);
	void onSwingFailAnimDone(const std::string& i_animName);

	DECLARE_STATE_FUNCTIONS(ZombieState, SwingIntro);
	DECLARE_STATE_FUNCTIONS(ZombieState, SwingSucceed);
	DECLARE_STATE_FUNCTIONS(ZombieState, SwingFail);
	OVERRIDE_STATE_ONENTER(ZombieState, BleedingOut);
	
protected:
    bool m_swinging;
    bool m_doomedToFail;
    
private:
	void fallOffRope();
	SexyVector2 calcMidSwingOffset() const;
    
	bool m_deathOnLanding;
	bool m_shrinkOnLanding;
};

class ZombieAnimRig_Swashbuckler : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Swashbuckler, ZombieAnimRig, RtClass);
	
	bool PlaySwingBack(PopAnimRig::AnimStoppedReflectionDelegate i_onStopped);
	bool PlaySwingSuccess(PopAnimRig::AnimStoppedReflectionDelegate i_onStopped);
	bool PlaySwingFail(PopAnimRig::AnimStoppedReflectionDelegate i_onStopped);
	
	virtual SexyVector2 GetLocationOffset();
	virtual SexyVector2 GetSwingFootOffset();
	
protected:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
};

///////////////////////////

class ZombieHolidaySwashbuckler : public ZombieSwashbuckler
{
public:
	RT_CLASS_DEFINE(ZombieHolidaySwashbuckler, ZombieSwashbuckler, RtClass);

    //virtual ~ZombieHolidaySwashbuckler();
    
protected:
    BoardEntity * findTarget() override;
    
    int GetLandingColumn() override;
    
    virtual void DropAllLoot() override;
    
    void onZombieInitialize() override;
    
    OVERRIDE_STATE_ONENTER(ZombieState, Eat);
    OVERRIDE_STATE_UPDATE(ZombieState, Eat);
    OVERRIDE_STATE_ONEXIT(ZombieState, Eat);
    
private:
    
    bool      m_stealed = false;
    pvztime_t m_stealTime = PVZ_EOT();
};

#endif
