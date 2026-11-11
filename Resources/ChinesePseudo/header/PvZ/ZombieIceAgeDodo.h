//
//  ZombieIceAgeDodo.h
//  PlantsVersusZombies2
//
//  Created by jemery on 11/11/14.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieIceAgeDodo_h
#define PlantsVersusZombies2_ZombieIceAgeDodo_h

#include <string>

#include "BoardEntity.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "dtypes.h"
#include "RestrictionSet.h"

class ZombieIceAgeDodoProps : public ZombieWithActionsProps
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeDodoProps, ZombieWithActionsProps, RtClass);
	
	ZombieIceAgeDodoProps() :
	MaximumGridSquaresToFlyOver(1),
	MinRandomGridSquaresToFlyOver(1),
	MaxRandomGridSquaresToFlyOver(1),
	CooldownSecondsUntilNextJumpAvailable(1),
	InitialSetRandomChanceForJump(0),
	LandedResetRandomChanceForJump(0),
	AddRandomChanceForJumpPerGridWalked(0)
	{
	}
	
	int MaximumGridSquaresToFlyOver;
	int MinRandomGridSquaresToFlyOver;
	int MaxRandomGridSquaresToFlyOver;
	int CooldownSecondsUntilNextJumpAvailable;
	float InitialSetRandomChanceForJump;
	float LandedResetRandomChanceForJump;
	float AddRandomChanceForJumpPerGridWalked;
	PlantRestrictionSet	PlantsToFlyOver;
	GridItemRestrictionSet	GridItemsToFlyOver;
	std::string	ElectrocutePAMName;
};

STATE_ENUM_CHILD_BEGIN(ZombieState_DodoRider, ZombieState)
	ZS_DODO_FlyStart,
	ZS_DODO_FlyForward,
	ZS_DODO_FlyEnd,
STATE_ENUM_END(ZombieState_DodoRider)

class ZombieIceAgeDodo : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeDodo, Zombie, RtClass);
	
	bool ShouldClipWithWater() const override;
	bool ShouldDrawShadow() const override;

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyStart);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyForward);
	DECLARE_STATE_FUNCTIONS(ZombieState, FlyEnd);
	
protected:
	bool	canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
	void	onZombieInitialize() override;
	GroundEffectType	GetTideEffect() const override { return GROUND_EFFECT_Tide_With_Tail; }
    void	onApplyCondition(ZombieConditions i_condition) override;
	
	Sexy::Rect calcCollisionRect() override;

	virtual bool allowAshState() const override
	{
		return false;
	}
	
	void updateState_Eat() override;

private:
	bool			isRestedForFlying();
	bool			findOtherObjectsToAvoid();

	void			startFlyingToAvoidObjects();
	void			startFlyingRandomly();
	
	bool			shouldFlyOverEntity(BoardEntity* i_entity);
	bool			shouldStayFlying();
	bool			shouldStartFlyingRandomly();
	
	void			onFlyStartAnimDone(const std::string& i_animLabel);
	void			onFlyEndAnimDone(const std::string& i_animLabel);
		
    std::string		getElectrocutePAMName() const override;
    void            onUpdate() override;
    
	int				m_boardSpaceLeftToFlyForward;
	int				m_flightStartX;
	int				m_flightMaximumX;
	int				m_walkStartX;
	int				m_nextCheckX;
	float			m_chanceToStartFlying;
    pvztime_t		m_timeFlyingAvailable;
    int             m_damageState;
};

class ZombieAnimRig_Dodo : public ZombieAnimRig
{
	RT_CLASS_DEFINE(ZombieAnimRig_Dodo, ZombieAnimRig, RtClass);
    
public:
	void PlayFlyStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayFlyEnd(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void PlayFlyForward();
    void SetDamageState(const int i_state);
	void DisableImpLayers();
    
private:
    void onPopAnimInitialized() override;
};

#endif
