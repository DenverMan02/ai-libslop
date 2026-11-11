//
//  Creature.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/14/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __CREATURE_H__
#define __CREATURE_H__

#include "BoardEntity.h"
#include "CreatureAnimRig.h"
#include "CreatureConditionTracker.h"
#include "CreaturePropertySheet.h"
#include "CreatureType.h"
#include "Zombie.h"
#include "StateMachine.h"


STATE_ENUM_BASE_BEGIN(CreatureState)
	CRS_Idle,
	CRS_Walk,
	CRS_Melee,
STATE_ENUM_END(CreatureState);

/// Creature Flags
enum CreatureFlags
{
	PVZ_BEGIN_FLAG_ENUM(CFLAG_),
	
	PVZ_FLAG(CFLAG_UseAnimTranslation),
	PVZ_FLAG(CFLAG_IsFlying),
	PVZ_FLAG(CFLAG_DrawIgnoreFacing),
	
	/*
	PVZ_FLAG(ZFLAG_UseAnimTranslation),
	PVZ_FLAG(ZFLAG_LostArm),
	PVZ_FLAG(ZFLAG_LostHead),
	PVZ_FLAG(ZFLAG_HasPlantFood),
	PVZ_FLAG(ZFLAG_HasDroppedLoot),
	PVZ_FLAG(ZFLAG_NoBlinkOnDamage),
	PVZ_FLAG(ZFLAG_IsFlying),				// This zombie is not on the ground right now
	PVZ_FLAG(ZFLAG_WinningZombie),
	PVZ_FLAG(ZFLAG_PlayedDeathAnim),
	PVZ_FLAG(ZFLAG_SuppressDeath),			// All damage is still taken, but the Zombie will not enter the BleedingOut or Death state
	PVZ_FLAG(ZFLAG_Controlled),
	PVZ_FLAG(ZFLAG_WalkAfterRise),
	PVZ_FLAG(ZFLAG_IgnoreAllDamage),
	PVZ_FLAG(ZFLAG_HasDebugHighlight),
	PVZ_FLAG(ZFLAG_ThreatsDisabled),
	PVZ_FLAG(ZFLAG_IsThreat),
	PVZ_FLAG(ZFLAG_FriendZombie),
	PVZ_FLAG(ZFLAG_NotTargetable),
	PVZ_FLAG(ZFLAG_IgnoresCollisions),
	PVZ_FLAG(ZFLAG_DamagedByNonMagnet),		// For tracking the MagnetShroom achievement
	PVZ_FLAG(ZFLAG_HasBroadcastedDeath),	// only broadcast death once - mainly used for ZombieAmbientAudioSubsystem
	PVZ_FLAG(ZFLAG_IsPulledByBeachZomboss),
	PVZ_FLAG(ZFLAG_AnimIgnoreConditionColors),
	PVZ_FLAG(ZFLAG_MarkedForDeath),			// Zombie is marked for death
	*/
	
	
	PVZ_END_FLAG_ENUM(CFLAG_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(CreatureFlags);


class Creature : public BoardEntity
{
public:
	RT_CLASS_DEFINE(Creature, BoardEntity, RtClass);
	
	/// Construction
	Creature();
	virtual ~Creature();

	void CreatureInitialize(CreatureTypePtr i_newType);
	virtual void PlaceOnStreet(int i_placementX);
	virtual void SpawnOnStreet(int i_stopAtX);
	void StartRushOnScreen();

	CreatureTypePtr GetType() const { return m_type; }
	std::string GetClassType() const { return m_type->CreatureClass; }
	CreaturePropsPtr GetProps() const { DBG_ASSERT(m_type.IsValid()); return m_type->Properties; }

	template <class T>
	const T* GetProps() const;
	CreatureAnimRig* GetAnimRig() const { return m_animRig->CastChecked<CreatureAnimRig>(); }
	template <class T>
	T* GetAnimRig() const;
 
	bool IsFlying() const;
	bool IsOnGround() const;
	bool IsOnBoard() const;

	/// Conditions
	void ApplyCondition(CreatureConditions i_condition, pvztime_t i_duration);
	void EndCondition(CreatureConditions i_condition);
	void ClearConditions();
	void EndConditions(std::vector<CreatureConditions> i_condition);
	bool HasCondition(CreatureConditions i_condition) const;
	void NotifyApplyCondition(CreatureConditions i_condition);
	void NotifyEndCondition(CreatureConditions i_condition);
	void NotifyConditionEvent(CreatureConditions i_condition) {}
	void ApplyExitSpeedup();

	ZombieFacing GetFacing() const;
	virtual void SetFacing(ZombieFacing i_facing);
	float GetFacingMultiplier() const;
	float GetDrawFacingMultiplier() const;
	
	Sexy::Point GetGridExtents() const override;
	float GetLastDistanceWalked() const;
	void SetTranslationMultiplier(float i_newMultiplier);
	void SetIsFlying(bool i_flying);
	void SetIsUsingAnimTranslation(bool i_hasAnimTranslation);
	void SetDrawIgnoreFacing(bool i_ignoreFacing) { SetFlag(m_creatureFlags, CFLAG_DrawIgnoreFacing, i_ignoreFacing); }
	void SetWaveToLeave(int i_waveDuration);
	bool IsWaveToLeave();
	bool IsStreetCreature() { return m_walkingToStreet; }
	
	Sexy::Rect calcCollisionRect() override;
	virtual void DrawCollisionInfo(Graphics* g);
	virtual Sexy::Rect CalcAttackRect() const;
	int CalcRenderOrder() const override;
	virtual RenderLayer CalcBaseCreatureRenderLayer() const;
	SexyVector3 CalcPositionInTime(pvztime_t i_time);
	
	virtual SexyVector2 GetShadowScaling() const;
	bool ShouldDrawShadow() const override;
	
protected:
	void registerForEvents() override;
	
	/// State machine!
	void updateStateMachine();
	void setState(CreatureState i_newState, bool i_reenterIfAlreadyInState = false);
	void reenterState();
	CreatureState getState() const;
	const StateDefinition<CreatureState>& getStateDefinition() const;
	bool isInState(uint32 i_state) const;
	float getStateMachineTimeScale() const;
	void setStateMachineTimeScale(float scale);
	int32 getStateSerialization();
	void setStateSerialization(int32 i_state);
	
	virtual float getWalkSpeed() const { return m_walkSpeed; }
	
	// Individual states
	DECLARE_STATE_FUNCTIONS(CreatureState, Idle);
	DECLARE_STATE_FUNCTIONS(CreatureState, Walk);
	DECLARE_STATE_FUNCTIONS(CreatureState, Melee);
	
	/// GameObject/BoardEntity interface - when deriving you must call up to the super class.
	void onInitialized() override {}
	void onPostLoad() override;
	void onPlaceOnBoard() override;
	void onUpdate() override;
	void onDestroy() override;
	void onDraw(class Sexy::Graphics* i_g) override;
	void onDrawShadow(class Sexy::Graphics* i_g) override;
	
	/// Creature interface
	virtual void onCreatureInitialize() {}
	virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) {}
	virtual void onSetIsFlying(const bool i_flying) {}
	virtual void onApplyCondition(CreatureConditions i_condition) {}
	virtual void onEndCondition(CreatureConditions i_condition) {}
	
	/// Protected helpers
	pvztime_t getTimeInState() const;
	void updateRushCondition();
	void endRushOnScreen();
	void setUseAnimTranslation(bool i_useAnimTranslation);
	
	/*AttachedEffect& AddAttachedEffect(const char* iEffectName, const char* iPanAnimName, const char* iAnimName, const SexyVector3& iOffset, int iRenderLayerOffset = 1, bool playOnce = false);
	void RemoveAttachedEffect(const char* i_entityName);
	void DetachAttachedEffect(const char* i_entityName);*/
	
	// Animation callbacks
	virtual void onWalkAnimationCycle(const std::string&, const std::string&, int);
	virtual void onIdleAnimationCycle(const std::string&, const std::string&, int);
	
	void playIdleSound();
	void playWalkSound();
	
	// Hack! Re-applies current condition effects to anim rigs and movement speed
	void forceApplyConditionEffects();
	void updateGroundEffect();
	
	virtual bool shouldDestroyWhenOffScreen();
	
	bool m_walkingToStreet;
	int m_streetStopX;
	
private:
	void setState(const StateDefinition<CreatureState>& i_newState, bool i_reenterIfAlreadyInState);
	
	void initializeAnimRig();
	void initializeAnimRigForType(CreatureTypePtr i_type);
	
	void updateSpeed();
	void updateOverlayEffects();
	void updateCheckForPitOfDoomDeath();
	void updateConditionColors();
	void applyExitSpeedup();

	void startWalk();
	float getBaseWalkSpeed();
	
	/// Serialized properties
	
	CreatureTypePtr m_type;
	CreatureAnimRigPtr m_animRig;
	AnimHandle m_playingAnim;
	
	/// Run-time state info (ie: good stuff to serialize)
	StateMachine<CreatureState> m_stateMachine;
	pvzAccumulatedTime_t m_elapsedTimeInState;
	float m_stateMachineTimeScale;
	
	CreatureFlags m_creatureFlags;
	ZombieFacing m_facing;
	float m_walkSpeed;
	float m_translationMultiplier;
	float m_rotation;
	float m_scale;
	
	int m_renderLayerOffset;
	int m_waveToLeave;
	
	//EntityComponent_GroundEffect	m_groundEffect;
	
	// Conditions;
	CreatureConditionTracker m_conditionTracker;
	//AttachedEffectManager m_attachedEffects;
	//AttachedBoardEntityManager m_attachedBoardEntities;
};


template <class T>
const T* Creature::GetProps() const
{
	CreaturePropsPtr creatureProps = GetProps();
	const T* typedProps = creatureProps->Cast<const T>();
	return typedProps;
}

template <class T>
T* Creature::GetAnimRig() const
{
	return GetAnimRig()->CastChecked<T>();
}

#endif
