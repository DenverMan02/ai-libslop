//
//  EntityComponent.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/21/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_EntityComponent_h
#define PlantsVersusZombies2_EntityComponent_h

#include "RtObject.h"
#include "core.h"

class Effect_PopAnim;

//
// This is the result of a timeboxed abstraction of some code being duplicated across different entity types.
//
// The result is a partial refactoring into a more generalized set of components that can be attached as needed to
// provide functionality to different entity types without overburdening the Entity base class.
//
// The AttachedEffectManager has some similarities, although is more specialized and slower due to its string-key
// lookup.  These components must be fast as they will be referenced every tick.  These concepts could merge in the future.
//
// Thoughts on further abstraction:
//
//	- State-styled component slots.
//	- Generalize more and try to fit in with the AttachedEffectManager.
//		Cons: Speed of lookup as some effects are per-tick updated.  Components want to interact more with their owner.
//
//  - Both systems could be merged.  AttachedEffectManager could have the concept of multiple slots of effect lists.
//		This would allow for ground effects that are complex and have several attachments.
//

enum GroundEffectType
{
	PVZ_BEGIN_ENUM(GROUND_EFFECT_),
	GROUND_EFFECT_Tide,
	GROUND_EFFECT_Tide_With_Tail,
	GROUND_EFFECT_Tide_Gargantuar,
	GROUND_EFFECT_Rise_From_Ground,
	GROUND_EFFECT_Just_Clip,
	GROUND_EFFECT_Surf,
    GROUND_EFFECT_Stuck_Under_Ground,
    GROUND_EFFECT_Stuck_Into_Ground,
    GROUND_EFFECT_Burrowed,
	PVZ_END_ENUM(GROUND_EFFECT_)
};

class EntityComponent_GroundEffect : public RtObject
{
public:
	RT_CLASS_DEFINE(EntityComponent_GroundEffect, RtObject, RtClass);
	
	EntityComponent_GroundEffect();
	
	void Destroy();
	
	void ClearGroundEffect(class RealObject* i_entity);
	void SetGroundEffect(class RealObject* i_entity, GroundEffectType i_groundEffect, bool i_isManual);
	bool IsCurrentEffectManual() { return m_isManual; }
	GroundEffectType CurrentEffect() { return m_type; }
	RtWeakPtr<Effect_PopAnim> GetEffect() const { return m_effect; }
	
private:
	bool							m_isManual;
	GroundEffectType				m_type;
	RtWeakPtr<Effect_PopAnim>		m_effect;
	RtWeakPtr<Effect_PopAnim>		m_effect_2;

};

#endif
