//
//  DinosuarRaptor.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/15/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __DINOSAURRAPTOR_H__
#define __DINOSAURRAPTOR_H__

#include "Dinosaur.h"

STATE_ENUM_CHILD_BEGIN(DinosaurRaptorState, DinosaurState)
CS_RAPTOR_Flip,
STATE_ENUM_END(DinosaurRaptorState);

class DinosaurRaptor : public Dinosaur
{
public:
	RT_CLASS_DEFINE(DinosaurRaptor, Dinosaur, RtClass);
	
	/// Construction
	DinosaurRaptor();
	virtual ~DinosaurRaptor();
	
	void onPlaceOnBoard() override;
	
	OVERRIDE_STATE_UPDATE(CreatureState, Walk);
	OVERRIDE_STATE_UPDATE(CreatureState, Idle);
	OVERRIDE_STATE_ONENTER(CreatureState, Active_Action);
	OVERRIDE_STATE_ONEXIT(CreatureState, Active_Action);
	DECLARE_STATE_FUNCTIONS(CreatureState, Flip);
	
	void SetFacing(ZombieFacing i_facing) override;
	void DrawCollisionInfo(Graphics* g) override;
	
protected:
	
	/// GameObject/BoardEntity interface - when deriving you must call up to the super class.
	void onCreatureInitialize() override;
	void onWalkAnimationCycle(const std::string&, const std::string&, int) override;
	
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	
	bool isValidZombieTarget(Zombie* i_zombie) override;
	std::vector<RtWeakPtr<BoardEntity>> findFlipAttackTargets(std::vector<RtWeakPtr<BoardEntity>> i_ignoreTargets = std::vector<RtWeakPtr<BoardEntity>>());
	
	bool CanBeCharmed() override;
	void Charm() override;
	
private:
	
	bool isBeyondPatrolRange();
	Sexy::Rect calcFlipAttackRect() const;
	void triggerKickIfNecessary();
	void kickZombie(Zombie* i_zombie);
	bool isCloseEnough(Zombie* i_zombie);
	void onDoneKick(const std::string& i_anim);
	void onPlayFlipStopped(const std::string& i_anim);
	
	float calculateKickDistance(Zombie* i_zombie);

	int m_KicksRemaining;
	bool m_wantsToFlip;
	bool m_ableToKick;
	RtWeakPtr<Zombie> m_targetZombie;
};

class DinosaurRaptorPropertySheet : public DinosaurPropertySheet
{
public:
	RT_CLASS_DEFINE(DinosaurRaptorPropertySheet, DinosaurPropertySheet, RtClass);
	
	DinosaurRaptorPropertySheet()
	{
		MaxKicks = 5;
		LeftMostKickGridX = 2;
		TossTime = 0;
		TossHeight = 0;
		TossDistance = 0;
		KickRectFudgeFactor = 40;
	}

	int MaxKicks;
	int LeftMostKickGridX;
	float TossTime;
	float TossHeight;
	float TossDistance;
	Sexy::Rect FlipAttackRect;
	int KickRectFudgeFactor;
};

enum DinosaurRaptorAnimRigState
{
	CREATUREANIM_RAPTOR_FLIP = CREATUREANIM_DINOSAUR_USERDEFINED,
	
	CREATUREANIM_RAPTOR_USERDEFINED,		// Extend from this enum
};

class DinosaurAnimRig_Raptor : public DinosaurAnimRig
{
public:
	RT_CLASS_DEFINE(DinosaurAnimRig_Raptor, DinosaurAnimRig, RtClass);
	
	void onPopAnimInitialized() override;
	
	bool PlayFlip(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	void SetAnimFacing(ZombieFacing i_facing) { m_facing = i_facing; }
	
protected:
	
	const std::string getFlipAnimationName();
	const std::string getIdleAnimationName() override;
	const std::string getWalkAnimationName() override;
	const std::string getMeleeAnimationName() override;
	const std::string getActiveReadyAnimationName() override;
	const std::string getRunAwayAnimationName() override;

	ZombieFacing m_facing;
};


#endif
