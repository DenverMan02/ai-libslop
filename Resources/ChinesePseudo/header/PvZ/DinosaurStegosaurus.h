//
//  DinosaurStegosaurus.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 9/18/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DinosaurStegosaurus__
#define __PlantsVersusZombies2__DinosaurStegosaurus__

#include <stdio.h>
#include "Dinosaur.h"

STATE_ENUM_CHILD_BEGIN(StegoState, DinosaurState)
	CS_STEGO_Enter,
	CS_STEGO_Head_Wait,
	CS_STEGO_Head_Annoyed,
	CS_STEGO_Withdraw,
	CS_STEGO_Tail_Collect_Zombies,
	CS_STEGO_Tail_Fling_Zombies,
STATE_ENUM_END(StegoState);

class DinosaurStegosaurus : public Dinosaur
{
public:
	RT_CLASS_DEFINE(DinosaurStegosaurus, Dinosaur, RtClass);
	
	/// Construction
	DinosaurStegosaurus();
	virtual ~DinosaurStegosaurus();
	
	DECLARE_STATE_FUNCTIONS(StegoState, Enter);
	DECLARE_STATE_FUNCTIONS(StegoState, Head_Wait);
	DECLARE_STATE_FUNCTIONS(StegoState, Head_Annoyed);
	DECLARE_STATE_FUNCTIONS(StegoState, Withdraw);
	DECLARE_STATE_FUNCTIONS(StegoState, Tail_Collect_Zombies);
	DECLARE_STATE_FUNCTIONS(StegoState, Tail_Fling_Zombies);
	OVERRIDE_STATE_FUNCTIONS(CreatureState, Walk);
	OVERRIDE_STATE_FUNCTIONS(CreatureState, Idle);
	
protected:
	
	/// GameObject/BoardEntity interface - when deriving you must call up to the super class.
	void onCreatureInitialize() override;
	
	/*void onInitialized() override;
	 void onPostLoad() override;
	 void onPlaceOnBoard() override;
	 void onDestroy() override;
	 void onDraw(class Sexy::Graphics* i_g) override;
	 void onDrawShadow(class Sexy::Graphics* i_g) override;*/
	
	void onUpdate() override;
	void onPlaceOnBoard() override;
	RenderLayer CalcBaseCreatureRenderLayer() const override;
	bool ShouldDrawShadow() const override;
	
	void addZombieToTail(Zombie *zombie);
	int getNumZombiesOnTail();
	bool isZombieOnTail(Zombie *zombie);
	bool isZombieOwnedByAnotherStegoasaurus(Zombie *i_zombie);
	bool isValidZombieTarget(Zombie* i_zombie) override;
	bool isValidZombieToSmash(Zombie* i_zombie);
	
	bool isActivateReady() override;
	void activate() override;
	bool isCollectingZombies();
	
	void smashZombiesOnTail();
	void flingZombies();
	void flingAZombie(Zombie *i_zombie);
	SexyVector3 calcTossDestination(Zombie* i_zombie);
	
	bool isInitialHeadEntrance();
	bool isInitialTailEntrance();
	void doCharmAnimation();
	void doFling();
	void setupCapturedZombieState(Zombie *i_zombie, bool isFlinging);
	bool zombieOverlapsZombie(Zombie *i_zombie);
	
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	void onEnterComplete(const std::string& i_anim);
	void onIdleContinued(const std::string& i_prevAnim, const std::string& i_nextAnim, int i_count);
	void onStartCharmedComplete(const std::string& i_anim);
	void onAnnoyedComplete(const std::string& i_anim);
	void onExitComplete(const std::string&);
	void onAttackAnimComplete(const std::string&);
	
	bool CanBeCharmed() override;
	void Charm() override;
	
private:
	bool isTimeToFling();
	void setupTimeToFling();
	
	std::vector<RtWeakPtr<Zombie>> m_zombiesOnTail;
	std::vector<RtWeakPtr<Zombie>> m_zombiesInAttackRange;
	pvztime_t		m_timeToFling;
	int				m_numTosses;
	bool			m_isHead;
	bool			m_hasFlung;
	bool			m_prevCharmState;
};

class DinosaurStegosaurusPropertySheet : public DinosaurPropertySheet
{
public:
	RT_CLASS_DEFINE(DinosaurStegosaurusPropertySheet, DinosaurPropertySheet, RtClass);
	
	DinosaurStegosaurusPropertySheet()
	{
		NumTimesToToss = 3;
		NumZombiesToFling = 3;
		ZombieAnnoyingGridX = BoardConstants::NUMBER_OF_COLUMNS() - 1;
		ActivationGridRangeStartX = 7.0f;
		ActivationGridRangeWidth = 0.75f;
		TossReadyUpTime = 1.5f;
		TossTime = 1;
		TossHeight = 100;
		TossDistanceMin = 100;
		TossDistanceMax = 300;
		TailDamageRadius = 1.0f;
		TailSmashDamage = 1000;
		TailAOEDamage = 200;
		ZombieTailStaggerX = 15.0f;
	}
	
	int NumTimesToToss;
	int NumZombiesToFling;
	int ZombieAnnoyingGridX;
	float ActivationGridRangeStartX;
	float ActivationGridRangeWidth;
	pvztime_t TossReadyUpTime;
	pvztime_t TossTime;
	float TossHeight;
	float TossDistanceMin;
	float TossDistanceMax;
	float TailDamageRadius;
	int TailSmashDamage;
	int TailAOEDamage;
	float ZombieTailStaggerX;
};

class DinosaurAnimRig_Stegosaurus : public CreatureAnimRig
{
public:
	RT_CLASS_DEFINE(DinosaurAnimRig_Stegosaurus, CreatureAnimRig, RtClass);
	
	void PlayEnterAnimation( AnimStoppedReflectionDelegate i_onStopped = {});
	void PlayExitAnimation( AnimStoppedReflectionDelegate i_onStopped = {});
	void DoCharmAnimation(AnimStoppedReflectionDelegate i_onStopped = {});
	void PlayIdleAnimation(LoopingAnimContinuedReflectionDelegate i_onContinue = {});
	void PlayAnnoyedAnimation( AnimStoppedReflectionDelegate i_onStopped = {});
	void PlayAttackAnimation(AnimStoppedReflectionDelegate i_onStopped = {});
	
	void SetCharmed(bool isCharmed) { m_isCharmed = isCharmed; }
	void SetIsHead(bool isHead) { m_isHead = isHead; }
	
protected:
	bool m_isCharmed = false;
	bool m_isHead = true;
};


#endif /* defined(__PlantsVersusZombies2__DinosaurStegosaurus__) */
