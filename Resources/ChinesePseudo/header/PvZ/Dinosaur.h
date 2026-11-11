//
//  Dinosuar.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/15/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __DINOSAUR_H__
#define __DINOSAUR_H__

#include "Creature.h"

STATE_ENUM_CHILD_BEGIN(DinosaurState, CreatureState)
CS_DINO_Active_Ready,
CS_DINO_Active_Action,
CS_DINO_Run_Away,

CS_DINO_Charmed_Active_Ready,
CS_DINO_Charmed_Active_Action,
STATE_ENUM_END(DinosaurState);

class Dinosaur : public Creature
{
public:
	RT_CLASS_DEFINE(Dinosaur, Creature, RtClass);
	
	/// Construction
	Dinosaur();
	virtual ~Dinosaur();
	
	DECLARE_STATE_FUNCTIONS(CreatureState, Active_Ready);				// Dinosaur has reached the activation column and is ready to go
	DECLARE_STATE_FUNCTIONS(CreatureState, Active_Action);				// Dinosaur is performing his activated action
	DECLARE_STATE_FUNCTIONS(CreatureState, Run_Away);					// Dinosaur is escaping from the board
	DECLARE_STATE_FUNCTIONS(CreatureState, Charmed_Active_Ready);		// [Charmed] Dinosaur has reached the activation column and is ready to go
	DECLARE_STATE_FUNCTIONS(CreatureState, Charmed_Active_Action);		// [Charmed] Dinosaur is performing his activated action
	
	virtual bool CanBeCharmed() { return !isCharmed(); }
	virtual void Charm();
	virtual bool CanBeScared() { return m_timeout > PVZ_T(); }
	virtual void ScareAway(){ m_timeout = PVZ_T();}
	
protected:
	
	bool isCharmed();
	
	virtual bool isActivateReady();
	virtual void activate();
	
	virtual std::vector<RtWeakPtr<BoardEntity>> findAttackTargets(std::vector<RtWeakPtr<BoardEntity>> i_ignoreTargets = std::vector<RtWeakPtr<BoardEntity>>());
	
	virtual bool isValidZombieTarget(Zombie* i_zombie) { return true; }
	
	bool isTimedOut();
	void resetTimeout();
	void disableTimeout();
	
	void onCreatureInitialize() override;
	
	/// GameObject/BoardEntity interface - when deriving you must call up to the super class.
	/*void onInitialized() override;
	 void onPostLoad() override;
	 void onPlaceOnBoard() override;
	 void onUpdate() override;
	 void onDestroy() override;
	 void onDraw(class Sexy::Graphics* i_g) override;
	 void onDrawShadow(class Sexy::Graphics* i_g) override;*/
	
private:
	pvztime_t		m_timeout;
	bool			m_isZombossLevel;
};

class DinosaurPropertySheet : public CreaturePropertySheet
{
public:
	RT_CLASS_DEFINE(DinosaurPropertySheet, CreaturePropertySheet, RtClass);
	
	DinosaurPropertySheet()
	{
		ActivationGridX = 5;
		Timeout = 30;
	}
	
	int ActivationGridX;
	pvztime_t Timeout;
};

enum DinosaurAnimRigState
{
	CREATUREANIM_DINOSAUR_ACTIVE_READY = CREATUREANIM_USERDEFINED,
	CREATUREANIM_DINOSAUR_ACTIVE_ACTION,
	CREATUREANIM_DINOSAUR_RUN_AWAY,
	
	CREATUREANIM_DINOSAUR_USERDEFINED,		// Extend from this enum
};

class DinosaurAnimRig : public CreatureAnimRig
{
public:
	RT_CLASS_DEFINE(DinosaurAnimRig, CreatureAnimRig, RtClass);
	
	DinosaurAnimRig()
	:m_charmed(false)
	{}
	
	virtual bool PlayActiveReady(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {});
	virtual bool PlayActiveAction(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
	virtual bool PlayRunAway(PopAnimRig::LoopingAnimContinuedReflectionDelegate i_onAnimContinued = {});
	void SetCharmed(bool i_charmed) { m_charmed = i_charmed; }

protected:
	virtual const std::string getActiveReadyAnimationName() { return "idle"; }
	virtual const std::string getActiveActionAnimationName() { return "attack"; }
	virtual const std::string getRunAwayAnimationName() { return "walk"; }
	
	bool m_charmed;
};

#endif
