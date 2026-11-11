//
//  EntityConditionTracker.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 8/1/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __ENTITY_CONDITION_TRACKER_H__
#define __ENTITY_CONDITION_TRACKER_H__

#include <vector>

#include "dtypes.h"
#include "TimeMgr.h"

inline uint64 EntityConditionToFlag(int i_condition) { return (uint64)1 << i_condition; }
inline uint32 EntityModifierToFlag(int i_modifier) { return 1 << i_modifier; }

/// Zombie Flags
enum EntityConditionModifierFlags
{
	PVZ_BEGIN_FLAG_ENUM(CMODIFIER_),
	PVZ_FLAG(CMODIFIER_Dirty),
	PVZ_FLAG(CMODIFIER_Suspended),
    PVZ_FLAG(CMODIFIER_SuspendedWanted),
	PVZ_FLAG(CMODIFIER_HasDrawShaderColor),
	PVZ_FLAG(CMODIFIER_HasDrawOverlayColor),
	PVZ_FLAG(CMODIFIER_PlantfoodRenderOrder),
	PVZ_END_FLAG_ENUM(CMODIFIER_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(EntityConditionModifierFlags);

//
// Conditions are modifying flags that can exist on an Entity (such as Zombies or Plants).
//
// They are not full-blown objects, per-se, although that is a possible refactoring to consider.  Right now the
// entity adds the conditions and does all the graphical / special modifications.  This could be better encapsulated,
// although at the moment they're pretty specialized for Plants vs Zombies, so that wouldn't be a huge benefit.
//
// Each has a duration and typically affect the status of the entity and various numerical attributes or effects.
//
// Condition priorities are determined in ComputeCachedValues.
//

struct EntityCondition
{
	EntityCondition()
	: m_startTime(PVZ_EOT())
	, m_endTime(PVZ_EOT())
	, m_eventTime(PVZ_EOT())
    , m_additionalDataValue(0.0f)
	, m_extraAdditionalDataValue(0.0f)
	, m_extraAdditionalDataValue2(0.0f)
	{}

	pvztime_t	m_startTime;
	pvztime_t	m_endTime;
	pvztime_t	m_eventTime;
    float		m_additionalDataValue; // to overload per condition.  Shrinking uses this for the target size.
    float 		m_extraAdditionalDataValue;
    float 		m_extraAdditionalDataValue2;
};

template<class T, typename E> class EntityConditionTracker
{
public:
	virtual ~EntityConditionTracker() {}
	EntityConditionTracker(int i_conditionMaxCount)
	: m_cachedSpeed(0.0f)
	, m_cachedDps(0.0f)
	, m_cachedDot(0.0f)
	, m_cachedScaledDamage(1.0f)
	, m_conditionModifierFlags(0)
	{
		m_conditions.resize(i_conditionMaxCount);
		m_conditionFlags.resize(i_conditionMaxCount, false);
		m_conditionModifierFlags = 0;
		SetFlag(m_conditionModifierFlags, EntityModifierToFlag(CMODIFIER_Dirty), true);
	}

	void Update(T* i_zombie);
	EntityCondition& ApplyCondition(T* i_zombie, E i_condition, pvztime_t i_duration, pvztime_t i_delay = 0);
	EntityCondition& GetCondition(E i_condition);
	void EndCondition(T* i_zombie, E i_condition);
	void ClearConditions(T* i_zombie);
	bool HasCondition(E i_condition) const;
	pvztime_t GetConditionDuration(E i_condition) const;
	void ClearConditionsNotMatching(T* i_zombie, std::vector<E> i_conditions);

	void SetDirty() { SetFlag(m_conditionModifierFlags, EntityModifierToFlag(CMODIFIER_Dirty), true); }
	bool TestModifierFlag(EntityConditionModifierFlags i_flag);

	// Status modifiers
	float GetSpeedModifier();
	float GetDPSModifier();
	float GetDamageOverTime();
	float GetScaledDamage();
	Color GetDrawOverlayColor();
	Color GetDrawShaderColor();
	RtWeakPtr<T> GetOwningEntity() { return m_owningEntity; }

protected:
	virtual int getConditionMaxCount() const = 0;
	virtual void recomputeModifierValues() = 0;
	
	void computeCachedValues();

	void setDrawOverlayColor(const Color& color);
	
public:
	std::vector<uint8_t> m_conditionFlags;
	std::vector<EntityCondition> m_conditions;
	
protected:
	// Cached values.
	float m_cachedSpeed;
	float m_cachedDps;
	float m_cachedDot;
	float m_cachedScaledDamage;
	uint32 m_conditionModifierFlags;
	Color m_cachedDrawShaderColor;
	Color m_cachedDrawOverlayColor;
	RtWeakPtr<T> m_owningEntity;
};


template<class T, typename E> EntityCondition& EntityConditionTracker<T,E>::ApplyCondition(T* i_entity, E i_condition, pvztime_t i_duration, pvztime_t i_eventCallbackDelay)
{	
	DBG_ASSERT (i_condition >= 0 && i_condition < getConditionMaxCount());
    
    EntityCondition &condition = m_conditions[i_condition];
	
    if (i_duration > 0.0f)
    {
        // EOT would overflow when added to PVZ_T, so just set end to EOT if it's passed in.
        const pvztime_t end = i_duration == PVZ_EOT() ? i_duration : PVZ_T() + i_duration;
        
        // Apply the condition if the condition is not already applied, or if applying it would extend
        // the duration.
        if (!HasCondition(i_condition) || condition.m_endTime < end)
        {
            condition.m_startTime = PVZ_T();
            condition.m_endTime = end;
            SetFlag(m_conditionModifierFlags, EntityModifierToFlag(CMODIFIER_Dirty), true);
            //SetFlag(m_conditionFlags, EntityConditionToFlag(i_condition), true);
            m_conditionFlags[i_condition] = true;
            
            if (i_eventCallbackDelay)
            {
                condition.m_eventTime = PVZ_T() + i_eventCallbackDelay;
            }
            
            i_entity->NotifyApplyCondition(i_condition);
        }
    }
	
	return condition;
}

template<class T, typename E> void EntityConditionTracker<T,E>::EndCondition(T* i_entity, E i_condition)
{
	DBG_ASSERT (i_condition >= 0 && i_condition < m_conditions.size());
	
	EntityCondition &condition = m_conditions[i_condition];
	condition.m_startTime = PVZ_EOT();
	condition.m_endTime = PVZ_EOT();
	
	SetFlag(m_conditionModifierFlags, EntityModifierToFlag(CMODIFIER_Dirty), true);
	//SetFlag(m_conditionFlags, EntityConditionToFlag(i_condition), false);
	m_conditionFlags[i_condition] = false;
	
	i_entity->NotifyEndCondition(i_condition);
}

template<class T, typename E> EntityCondition& EntityConditionTracker<T, E>::GetCondition(E i_condition)
{
	DBG_ASSERT(i_condition >= 0 && i_condition < m_conditions.size());

	EntityCondition &condition = m_conditions[i_condition];
	return condition;
}

template<class T, typename E> void EntityConditionTracker<T,E>::ClearConditions(T* i_entity)
{
	for (int i = (int) 0; i < (int) m_conditions.size(); ++i)
	{
		if (HasCondition((E) i))
		{
			EndCondition(i_entity, (E)i);
		}
	}
}

template<class T, typename E> void EntityConditionTracker<T,E>::ClearConditionsNotMatching(T* i_entity, std::vector<E> i_conditions)
{
	for (int i = (int) 0; i < (int) m_conditions.size(); ++i)
	{
		bool match = std::find(i_conditions.begin(), i_conditions.end(), (E) i) != i_conditions.end();
		
		if (match == false)
		{
			if (HasCondition((E) i))
			{
				EndCondition(i_entity, (E) i);
			}
		}
	}
}

template<class T, typename E> bool EntityConditionTracker<T,E>::HasCondition(E i_condition) const
{
	DBG_ASSERT (i_condition >= 0 && i_condition < getConditionMaxCount());
	//return TestFlag(m_conditionFlags, EntityConditionToFlag(i_condition));
	return m_conditionFlags[i_condition];
}

template<class T, typename E> pvztime_t EntityConditionTracker<T,E>::GetConditionDuration(E i_condition) const
{
	if (!HasCondition(i_condition))
	{
		return 0.f;
	}
	const EntityCondition &condition = m_conditions[i_condition];
	pvztime_t remainingTime = max(condition.m_endTime - PVZ_T(), 0.f);
	return remainingTime;
}

template<class T, typename E> void EntityConditionTracker<T,E>::Update(T* i_entity)
{
	const pvztime_t currentTime = PVZ_T();
	m_owningEntity = i_entity->GetPtr();
	
	for (int i = 0; i < (int) m_conditions.size(); ++i)
	{
		EntityCondition &condition = m_conditions[i];
		
		if (HasCondition((E) i))
		{
			if (currentTime > condition.m_eventTime)
			{
				condition.m_eventTime = PVZ_EOT();
				i_entity->NotifyConditionEvent((E) i);
			}
			
			if (currentTime > condition.m_endTime)
			{
				EndCondition(i_entity,(E) i);
			}
		}
	}
}

// This function is what ultimately determines priorities if
// multiple conditions have been applied that affect the same modifiers.
template<class T, typename E> void EntityConditionTracker<T,E>::computeCachedValues()
{
	if (TestFlag(m_conditionModifierFlags, EntityModifierToFlag(CMODIFIER_Dirty)))
	{
		recomputeModifierValues();
		SetFlag(m_conditionModifierFlags, EntityModifierToFlag(CMODIFIER_Dirty), false);
	}
}

template<class T, typename E> float EntityConditionTracker<T,E>::GetSpeedModifier()
{
	computeCachedValues();
	return m_cachedSpeed;
}

template<class T, typename E> float EntityConditionTracker<T,E>::GetDPSModifier()
{
	computeCachedValues();
	return m_cachedDps;
}

template<class T, typename E> float EntityConditionTracker<T,E>::GetDamageOverTime()
{
	computeCachedValues();
	return m_cachedDot;
}

template<class T, typename E> float EntityConditionTracker<T,E>::GetScaledDamage()
{
	computeCachedValues();
	return m_cachedScaledDamage;
}

template<class T, typename E> Color EntityConditionTracker<T,E>::GetDrawOverlayColor()
{
	computeCachedValues();
	return m_cachedDrawOverlayColor;
}

template<class T, typename E> Color EntityConditionTracker<T,E>::GetDrawShaderColor()
{
	computeCachedValues();
	return m_cachedDrawShaderColor;
}


template<class T, typename E> 	bool EntityConditionTracker<T,E>::TestModifierFlag(EntityConditionModifierFlags i_flag)
{
	computeCachedValues();
	return TestFlag(m_conditionModifierFlags, EntityModifierToFlag(i_flag));
}

//
// Common effect calculations
// TODO: Consider a repository for these as they grow.
//
extern void calculateConditionColor_Flash(const EntityCondition& i_condition, const Color& i_flashColor, Color& io_overlayColor);
extern void calculateConditionColor_FlashWhiteAlpha(const EntityCondition& i_condition, const Color& i_flashColor, Color& io_overlayColor);


#endif
