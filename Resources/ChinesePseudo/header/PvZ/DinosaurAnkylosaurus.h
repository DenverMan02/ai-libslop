//
//  DinosaurAnkylosaurus.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 9/28/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DinosaurAnkylosaurus__
#define __PlantsVersusZombies2__DinosaurAnkylosaurus__

#include <stdio.h>
#include "Dinosaur.h"

STATE_ENUM_CHILD_BEGIN(AnkyloState, DinosaurState)
CS_ANKYLO_Enter,
CS_ANKYLO_Withdraw,
CS_ANKYLO_Tail_Fling_Zombies,
STATE_ENUM_END(AnkyloState);

class DinosaurAnkylosaurus : public Dinosaur
{
public:
	RT_CLASS_DEFINE(DinosaurAnkylosaurus, Dinosaur, RtClass);
	
	/// Construction
	DinosaurAnkylosaurus();
	virtual ~DinosaurAnkylosaurus();
	
	DECLARE_STATE_FUNCTIONS(AnkyloState, Enter);
	DECLARE_STATE_FUNCTIONS(AnkyloState, Withdraw);
	DECLARE_STATE_FUNCTIONS(AnkyloState, Tail_Fling_Zombies);
	OVERRIDE_STATE_FUNCTIONS(CreatureState, Idle);
	OVERRIDE_STATE_FUNCTIONS(CreatureState, Walk);
	
protected:
	Rect calculateTargetingRect() const;
	std::vector<RtWeakPtr<Zombie> > findZombiesInRect(const Rect& i_rect);
	
	void onPlaceOnBoard() override;
	RenderLayer CalcBaseCreatureRenderLayer() const override;
	bool ShouldDrawShadow() const override;
	
	bool isValidZombieTarget(Zombie* i_zombie) override;
	
	bool isActivateReady() override;
	void activate() override;
	
	void flingZombie();
	void flickOffZombie(Zombie* i_zombie);
	void launchZombie(Zombie* i_zombie);
	SexyVector3 calcTossDestination(Zombie* i_zombie);
	
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	void onPopAnimCommand_Tail_Fling_Zombies(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param);
	
	void onEnterComplete(const std::string& i_anim);
	void onIdleContinued(const std::string& i_prevAnim, const std::string& i_nextAnim, int i_count);
	void onStartCharmedComplete(const std::string& i_anim);
	void onExitComplete(const std::string&);
	void onAttackAnimComplete(const std::string&);
	void onZombieLanding(Zombie *i_zombie);
	
	bool CanBeCharmed() override;
	void Charm() override;
	
private:
	bool isTimeToFling();
	void setupTimeToFling();
	
	pvztime_t		m_timeToFling;
	int32_t			m_numZombiesTossed;
	bool			m_usedWalkState;
};

class DinosaurAnkylosaurusPropertySheet : public DinosaurPropertySheet
{
public:
	RT_CLASS_DEFINE(DinosaurAnkylosaurusPropertySheet, DinosaurPropertySheet, RtClass);
	
	DinosaurAnkylosaurusPropertySheet()
	{
		ActivationGridX = 8;
		PauseBetweenAttacks = 5.0f;
		AttackRangeMinX = 2;
		MaxZombiesToFling = 5;
		MaxGridDistanceToFling = 4;
		ExitSpeedup = 4.0f;
	}
	
	pvztime_t PauseBetweenAttacks;
	int32_t AttackRangeMinX;
	int32_t MaxZombiesToFling;
	int32_t MaxGridDistanceToFling;
};

class DinosaurAnimRig_Ankylosaurus : public CreatureAnimRig
{
public:
	RT_CLASS_DEFINE(DinosaurAnimRig_Ankylosaurus, CreatureAnimRig, RtClass);
	
	void PlayEnterAnimation( AnimStoppedReflectionDelegate i_onStopped = {});
	void PlayExitAnimation( AnimStoppedReflectionDelegate i_onStopped = {});
	void DoCharmAnimation(AnimStoppedReflectionDelegate i_onStopped = {});
	void PlayIdleAnimation(LoopingAnimContinuedReflectionDelegate i_onContinue = {});
	void PlayAttackAnimation(AnimStoppedReflectionDelegate i_onStopped = {});
	
protected:
	bool m_isCharmed = false;
};


#endif /* defined(__PlantsVersusZombies2__DinosaurAnkylosaurus__) */
