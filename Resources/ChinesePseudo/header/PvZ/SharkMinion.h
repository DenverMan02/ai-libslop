//
//  SharkMinion.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 10/13/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SharkMinion__
#define __PlantsVersusZombies2__SharkMinion__

#include "BoardEntity.h"
#include "BoardEnums.h"
#include "StateMachine.h"

class Effect_PopAnim;

STATE_ENUM_BASE_BEGIN(SharkMinionState)
	SHARKMINION_IntroPan,
	SHARKMINION_Hidden,
	SHARKMINION_Appearing,
	SHARKMINION_Idle,
	SHARKMINION_Submerging,
	SHARKMINION_Attacking,
STATE_ENUM_END(SharkMinionState);

struct SharkMinionParameters
{
	SharkMinionParameters()
	: AppearanceMotionDuration(0.f)
	, AppearanceMaxRandomDelay(0.f)
	, SubmergeMotionDuration(0.f)
	, SubmergeMotionDistanceInTiles(0.f)
	, DelayFromSubmergeToAttack(0.f)
	{}
	
	float AppearanceMotionDuration;
	float AppearanceMaxRandomDelay;
	float SubmergeMotionDuration;
	float SubmergeMotionDistanceInTiles;
	float DelayFromSubmergeToAttack;
};

class SharkMinion : public BoardEntity
{
public:
	RT_CLASS_DEFINE(SharkMinion, BoardEntity, RtClass);
	SharkMinion();
	Sexy::Point GetGridExtents() const override { return Sexy::Point(2, 1); }
	
	// Call right after creation to tell the shark which row it belongs in.
	void SetRow(int i_boardRow);
	
	// Configure shark timings - can be dynamically updated!
	void SetParameters(const SharkMinionParameters& i_newParameters);
	
	// Lets the shark auto-spawn whenever it wants - no zomboss in this row
	void PatrolRow();
	
	// Hides the shark if zomboss would crush it, and stops auto-spawning.
	void SurrenderRow();
	
	// UNLEASHES the shark to sumberge and attack a plant in its row.
	void Attack();
	
	// Evaluates whether this minion can currently receive an attack command and whether a viable target exists.
	bool CanAttack();
    
    bool ShouldDrawShadow() const override { return false; }
	
protected:
	void registerForEvents()	override;
	void onInitialized()		override;
	void onUpdate()				override;
	void onDestroy()			override;
	
	DECLARE_STATE_FUNCTIONS(SharkMinionState, IntroPan);
	
	DECLARE_STATE_FUNCTIONS(SharkMinionState, Hidden);
	
	DECLARE_STATE_FUNCTIONS(SharkMinionState, Appearing);
	
	DECLARE_STATE_FUNCTIONS(SharkMinionState, Idle);
	void playIdleAnim();
	void onIdleAnimStopped(const std::string& i_animName);
	
	DECLARE_STATE_FUNCTIONS(SharkMinionState, Submerging);
	void onSubmergeAnimStopped(const std::string& i_animName);
	
	DECLARE_STATE_FUNCTIONS(SharkMinionState, Attacking);
	void doAttackOnTarget();
	void onAttackAnimStopped(const std::string& i_animName);
	
	SharkMinionState	getState() const;
	void				setState(SharkMinionState i_newState);
	bool				isInState(SharkMinionState i_newState) const;
	
private:
	void onGatherPlantingRestrictions(const Sexy::Point& i_atLocation, const class PlantType* i_plantType, std::vector<PlantingReason> *io_plantingErrors);
	
	int getRow() const;
	bool hasAttackTargetPosition() const;
	Sexy::Point pickAttackTargetPosition() const;
	void getAttackableEntitiesAtGridSquare(const Sexy::Point& i_targetPosition, std::vector<BoardEntity*>& o_entities) const;
	bool canAttackEntity(const BoardEntity* i_entity) const;
	
	RtWeakPtr<Effect_PopAnim> createSharkEffect();
	const SexyVector3 getIntroPanEffectPosition() const;
	const SexyVector3 getIdleEffectPosition() const;
	const SexyVector3 getOffscreenEffectPosition() const;
	const SexyVector3 getSubmergeEffectPosition() const;
	
	StateMachine<SharkMinionState> m_stateMachine;
	int32	getStateSerialization();
	void	setStateSerialization(int32 i_state);
	
	RtWeakPtr<Effect_PopAnim> m_sharkEffect;
	float m_motionStartTime;
	float m_motionEndTime;
	SexyVector3 m_motionStartPosition;
	SexyVector3 m_motionEndPosition;
	bool m_autoSpawnApproved;
	bool m_attackApproved;
	Sexy::Point m_attackTargetPosition;
	SharkMinionParameters m_currentParameters;
};

#endif /* defined(__PlantsVersusZombies2__SharkMinion__) */
