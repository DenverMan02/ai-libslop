//
//  StateMachine.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
// 	Manages a collection of states, defined as OnEnter, Update, and OnExit delegates.
//
//	General usage:
//		Setup
//			1. Create an enum for each of the possible states
//			2. Create a StateMachine<EnumName> object
//		Usage
//			1. Call StateMachine::UpdateStateMachine() to process CurrentState.Update()
//			2. Call StateMachine::SetState to change state. OldState.OnExit() and NewState.OnEnter() will be called
//
//	There are also a variety of macros to ease the process of setting up and transferring between states
//
//	EXAMPLE USAGE:
//
//	{base class header file}
//	
//	STATE_ENUM_BASE_BEGIN(StateEnum)
//		State_Idle,
//		State_Walk,
//	STATE_ENUM_END(StateEnum)
//
//	class BaseObj : public RtObject
//	{
//	public:
//		RT_CLASS_DEFINE(BaseObj, RtObject, RtClass) {}
//		void Init();
//		void Update();
//		void SetState(const StateDefinition<StateEnum>& i_newState);
//	protected:
//		DECLARE_STATE_FUNCTIONS(StateEnum, Idle);
//		DECLARE_STATE_FUNCTIONS(StateEnum, Walk);
//		int m_counter;
//	private:
//		StateMachine<StateEnum> m_stateMachine;
//	};
//
//	{base class CPP file}
//	
//	RT_CLASS_IMPLEMENT(BaseObj);
//
//	void BaseObj::Init() {
//		m_counter = 0;
//		m_stateMachine.SetState(STATE_DEFINITION(StateEnum, State_Idle, Idle));
//	}
//	void BaseObj::Update() {
//		m_stateMachine.UpdateStateMachine();
//	}
//	void BaseObj::SetState(const StateDefinition<StateEnum>& i_newState) {
//		m_stateMachine.SetState(i_newState);
//	}
//
//	void BaseObj::onEnterState_Idle(StateEnum i_fromState) {
//		printf("Entering Idle\n");
//	}
//	void BaseObj::updateState_Idle() {
//		if (counter < 3) {
//			printf("Idling...\n");
//			counter++;
//		}
//		else {
//			SetState(STATE_DEFINITION(StateEnum, State_Walk, Walk));
//		}
//	}
//	void BaseObj::onExitState_Idle(StateEnum i_toState) {
//		printf("Leaving Idle\n");
//	}
//	void BaseObj::onEnterState_Walk(StateEnum i_fromState) {
//		printf("Entering Walk\n");
//	}
//	void BaseObj::updateState_Walk() {
//		printf("Walking\n");
//	}
//	void BaseObj::onExitState_Walk(StateEnum i_toState) {
//		printf("Exiting Walk\n");
//	}
//
//	The above code will output (with Update() call count on the left)
//	{init}	Entering Idle
//	{1}		Idling...
// 	{2}		Idling...
//	{3}		Idling...
//	{4}		Leaving Idle
//			Entering Walk
//			Walking...
//
//	And then repeat 'Walking...' until the end of time.
//
//	Since RtDelegates will happily call through to derived versions of their targets,
//	you can override specific state functionality in child classes by overriding
//	that state's onEnter/Update/onExit functions.
//
//	If you want to add ADDITIONAL states to a derived class, do this:
//
//	{child class header}
//	
//	STATE_ENUM_CHILD_BEGIN(StateEnumChild, StateEnum)
//		StateChild_Special,
//	STATE_ENUM_END(StateEnumChild)
//
//	class ChildObj : public BaseObj
//	{
//	public:
//		RT_CLASS_DEFINE(ChildObj, BaseObj, RtClass) {}
//	protected:
//		// Override Idle Update
//		OVERRIDE_STATE_UPDATE(StateEnum, Idle);
//		// Add 'Special' State
//		DECLARE_STATE_FUNCTIONS(StateEnum, Special);
//	};
//
// {child class CPP file}
//
//	RT_CLASS_IMPLEMENT(ChildObj);
//
//	void ChildObj::updateState_Idle() {
//		if (counter < 1) {
//			printf("ChildObj Idling...\n");
//			counter++;
//		}
//		else {
//			SetState(STATE_DEFINITION(StateEnum, StateChild_Special, Special));
//		}
//	void ChildObj::onEnterState_Special(StateEnum i_fromState) {
//		printf("Entering Special\n");
//	}
//	void ChildObj::updateState_Special() {
//		printf("Special!\n");
//	}
//	void ChildObj::onExitState_Special(StateEnum i_toState) {
//		printf("Exiting Special\n");
//	}
//
//	The above code will output:
//	{init}	Entering Idle
//	{1}		ChildObj Idling...
//	{2}		Leaving Idle
//			Entering Special
//			Special!
//	{3}		Special!
//		... and so on!
//

#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include "Precompile.h"
#include "RtDelegate.h"

// DECLARE_STATE_FUNCTIONS
//	- Use this in a stateful class' declaration to declare the functions for a state
//	- Always use the base enum state name for this, not a derived name
//	- Params
//		base_enum_type		: The state name enum
//		state_fcn_name		: The suffix to use on the generated functions
//	
//	e.g., DECLARE_STATE_FUNCTIONS(StateEnum, Walk) resolves to:
//	
//	virtual void onEnterState_Walk(StateEnum i_fromState);
//	virtual void updateState_Walk();
//	virtual void onExitState_Walk(StateEnum i_toState);
//
#define DECLARE_STATE_FUNCTIONS(base_enum_type, state_fcn_name) \
    virtual STATE_ONENTER_FUNCTION_PROTOTYPE(base_enum_type, state_fcn_name); \
    virtual STATE_UPDATE_FUNCTION_PROTOTYPE(base_enum_type, state_fcn_name); \
    virtual STATE_ONEXIT_FUNCTION_PROTOTYPE(base_enum_type, state_fcn_name);

#define DECLARE_STATE_FUNCTIONS_EMPTY(base_enum_type, state_fcn_name) \
    virtual STATE_ONENTER_FUNCTION_PROTOTYPE(base_enum_type, state_fcn_name) {} \
    virtual STATE_UPDATE_FUNCTION_PROTOTYPE(base_enum_type, state_fcn_name) {} \
    virtual STATE_ONEXIT_FUNCTION_PROTOTYPE(base_enum_type, state_fcn_name) {}

// OVERRIDE_STATE_ONENTER
// OVERRIDE_STATE_UPDATE
// OVERRIDE_STATE_ONEXIT
//
//	- Allows you to declare an override for a state's enter/update/exit function
//	- If you intend to override all of the state's functions, you can also use DECLARE_STATE_FUNCTIONS
//
#define STATE_ONENTER_FUNCTION_PROTOTYPE(base_enum_type, state_fcn_name) \
    void onEnterState_##state_fcn_name(base_enum_type i_fromState)
#define STATE_UPDATE_FUNCTION_PROTOTYPE(base_enum_type, state_fcn_name) \
    void updateState_##state_fcn_name()
#define STATE_ONEXIT_FUNCTION_PROTOTYPE(base_enum_type, state_fcn_name) \
    void onExitState_##state_fcn_name(base_enum_type i_toState)

#define OVERRIDE_STATE_ONENTER(base_enum_type, state_fcn_name) \
    STATE_ONENTER_FUNCTION_PROTOTYPE(base_enum_type, state_fcn_name) override;
#define OVERRIDE_STATE_UPDATE(base_enum_type, state_fcn_name) \
    STATE_UPDATE_FUNCTION_PROTOTYPE(base_enum_type, state_fcn_name) override;
#define OVERRIDE_STATE_ONEXIT(base_enum_type, state_fcn_name) \
    STATE_ONEXIT_FUNCTION_PROTOTYPE(base_enum_type, state_fcn_name) override;

#define OVERRIDE_STATE_FUNCTIONS(base_enum_type, state_fcn_name) \
    OVERRIDE_STATE_ONENTER(base_enum_type, state_fcn_name) \
    OVERRIDE_STATE_UPDATE(base_enum_type, state_fcn_name) \
    OVERRIDE_STATE_ONEXIT(base_enum_type, state_fcn_name)

// STATE_DEFINITION
//	- Helper function to set up the StateDefinition struct for changing state
//	- Can be used to create the struct on the stack in the SetState fcn call's params
//	- Params
//		base_enum_type 		: The base state name enum
//		state_enum_name 	: The actual enum value to set state to
//		state_fcn_name 		: The state name used in DECLARE_STATE_FUNCTIONS
//	
//	e.g., STATE_DEFINITION(StateEnum, STATE_WALK, Walk) resolves to:
//
//	(StateDefinition<StateEnum>((StateEnum)STATE_WALK, 
//		MakeDelegate(*this, &ThisClass::onEnterState_Walk),
//		MakeDelegate(*this, &ThisClass::updateState_Walk),
//		MakeDelegate(*this, &ThisClass::onExitState_Walk)))
//

#define STATE_DEFINITION_EMPTY(base_enum_type, state_enum_name) \
    (StateDefinition<base_enum_type>((base_enum_type)state_enum_name, \
        #state_enum_name))

#define STATE_DEFINITION_NO_CONTEXT(base_enum_type, state_enum_name, state_fcn_name) \
    (StateDefinition<base_enum_type>((base_enum_type)state_enum_name, \
        MakeDelegate(((ThisClass*)(NULL)), &ThisClass::onEnterState_##state_fcn_name), \
        MakeDelegate(((ThisClass*)(NULL)), &ThisClass::updateState_##state_fcn_name), \
        MakeDelegate(((ThisClass*)(NULL)), &ThisClass::onExitState_##state_fcn_name), \
        #state_enum_name))

#define STATE_DEFINITION(base_enum_type, state_enum_name, state_fcn_name) \
    (StateDefinition<base_enum_type>((base_enum_type)state_enum_name, \
        MakeDelegate(*this, &ThisClass::onEnterState_##state_fcn_name), \
        MakeDelegate(*this, &ThisClass::updateState_##state_fcn_name), \
        MakeDelegate(*this, &ThisClass::onExitState_##state_fcn_name), \
        #state_enum_name))

// STATE_ENUM Macros (Optional)
//	- Use these to define the state macros for your base and child classes
//	- Handles setting up chains of 'derived' enums across classes
//	- Sets up the enum for use as an RtDelegate parameter via RT_INVOKEVARIANT_DECLARE_TYPE
//	- Example usage:
//
//	Base class:
//		STATE_ENUM_BASE_BEGIN(StateEnum)
//			State_Idle,
//			State_Walk,
//			State_Die,
//		STATE_ENUM_END(StateEnum)
//
//	Child class:
//		STATE_ENUM_CHILD_BEGIN(StateEnumChild, StateEnum)
//			StateChild_Special1,
//			StateChild_Special2,
//		STATE_ENUM_END(StateEnumChild)
//
//	This will resolve to:
//	enum StateEnum {
//		StateEnum_INVALID = -1,
//		State_Idle,
//		State_Walk,
//		State_Die,
//		StateEnum_CHILD_BEGIN
//	};
//	RT_INVOKEVARIANT_DECLARE_TYPE_UINT32(StateEnum);
//
//	enum StateEnumChild {
//		StateEnumChild_PRE_BEGIN = (StateEnum_CHILD_BEGIN - 1),
//		StateChild_Special1,
//		StateChild_Special2,
//		StateEnumChild_CHILD_BEGIN
//	};
//	RT_INVOKEVARIANT_DECLARE_TYPE_UINT32(StateEnumChild);
//
#define STATE_ENUM_BASE_BEGIN(enum_type) \
enum enum_type { \
	enum_type##_INVALID	= -1,
#define STATE_ENUM_ENTRY(enum_name) \
	enum_name,
#define STATE_ENUM_END(enum_type) \
	enum_type##_CHILD_BEGIN \
}; \
namespace Sexy { \
RT_INVOKEVARIANT_DECLARE_TYPE_UINT32(enum_type); \
} \

#define STATE_ENUM_CHILD_BEGIN(enum_type, base_enum_type) \
enum enum_type { \
	enum_type##_PRE_BEGIN = (base_enum_type##_CHILD_BEGIN - 1),


template<typename ENUM_TYPE>
struct StateDefinition
{
	typedef Delegate1<ENUM_TYPE> 	OnEnterDelegate;
	typedef Delegate0 				UpdateDelegate;
	typedef Delegate1<ENUM_TYPE> 	OnExitDelegate;
	
	StateDefinition() {}
	
    explicit StateDefinition(ENUM_TYPE i_state, const std::string& i_stateDisplayName = "")
    : State(i_state)
    {
        SetDisplayName(i_stateDisplayName);
    }
    
    StateDefinition(ENUM_TYPE i_state, const OnEnterDelegate& i_onEnter, const UpdateDelegate& i_update, const OnExitDelegate& i_onExit, const std::string& i_stateDisplayName = "")
    : State(i_state)
    , OnEnter(i_onEnter)
    , Update(i_update)
    , OnExit(i_onExit)
    {
        SetDisplayName(i_stateDisplayName);
    }
    
    void SetContext(void* i_newContext)
    {
        OnEnter.SetInstanceContext(i_newContext);
        Update.SetInstanceContext(i_newContext);
        OnExit.SetInstanceContext(i_newContext);
    }
    
    ENUM_TYPE State;
    
    OnEnterDelegate 	OnEnter;
    UpdateDelegate 		Update;
    OnExitDelegate 		OnExit;
    
    void SetDisplayName(const std::string& i_displayName)
    {
        m_displayName = i_displayName;
    }
    std::string			GetDisplayName() const
    {
        if (m_displayName.empty())
        {
            return StrFormat("<<state_id:%d>>", (int)State);
        }
        else
        {
            return m_displayName;
        }
    }
    
private:
    std::string			m_displayName;
};

template<typename ENUM_TYPE>
class StateMachine
{
public:
	StateMachine()
	{
		m_state.State = (ENUM_TYPE)-1;
#ifndef RELEASEFINAL
		m_inStateTransition = false;
#endif
	}
	
	void UpdateState();
	bool SetState(const StateDefinition<ENUM_TYPE>& i_newState);
	bool SetStateNoTransition(const StateDefinition<ENUM_TYPE>& i_newState);
	bool ReenterState();
	ENUM_TYPE GetState() const;
    const StateDefinition<ENUM_TYPE>& GetStateDefinition() const;
	
private:
	StateDefinition<ENUM_TYPE> m_state;
	
#ifndef RELEASEFINAL
	bool m_inStateTransition;
#endif
};

template<typename ENUM_TYPE>
void StateMachine<ENUM_TYPE>::UpdateState()
{
	for(;;)
	{
		ENUM_TYPE oldState = m_state.State;
		DBG_ASSERT_MSG(oldState >= 0, "StateMachine::UpdateState - State Machine in INVALID state!");
        if (m_state.Update)
        {
            m_state.Update();
        }
		ENUM_TYPE newState = m_state.State;
		// Keep looping until we stop changing state
		if (newState == oldState)
        {
			break;
        }
	}
}

template<typename ENUM_TYPE>
bool StateMachine<ENUM_TYPE>::SetState(const StateDefinition<ENUM_TYPE>& i_newState)
{
#ifndef RELEASEFINAL
	// We can't allow changing states from onEnter or onExit
	// NOTE - This check is not thread safe!
	DBG_ASSERT_MSG(!m_inStateTransition, "StateMachine::SetState - Attempted to SetState from OnEnter or OnExit!");
#endif

	if (m_state.State == i_newState.State)
	{
		return false;
	}
    
#ifndef RELEASEFINAL
	m_inStateTransition = true;
#endif
    
	DBG_ASSERT_MSG(i_newState.State >= 0, "StateMachine::SetState - State Machine set to invalid state! (State index: %d)", (int)i_newState.State);
    
	ENUM_TYPE oldState = m_state.State;
    
	if (oldState >= 0 && m_state.OnExit)
    {
		m_state.OnExit(i_newState.State);
    }
    
	m_state = i_newState;
    
    if (m_state.OnEnter)
    {
        m_state.OnEnter(oldState);
    }
    
#ifndef RELEASEFINAL
	m_inStateTransition = false;
#endif
	return true;
}

template<typename ENUM_TYPE>
bool StateMachine<ENUM_TYPE>::SetStateNoTransition(const StateDefinition<ENUM_TYPE>& i_newState)
{
	bool sameState = (m_state.State == i_newState.State);
	m_state = i_newState;
	return !sameState;
}

template<typename ENUM_TYPE>
bool StateMachine<ENUM_TYPE>::ReenterState()
{
	if (m_state.State < 0)
	{
		return false;
	}

#ifndef RELEASEFINAL
	m_inStateTransition = true;
#endif
    
	if (m_state.OnExit)
    {
		m_state.OnExit(m_state.State);
    }
    if (m_state.OnEnter)
    {
        m_state.OnEnter(m_state.State);
    }
    
#ifndef RELEASEFINAL
	m_inStateTransition = false;
#endif

	return true;
}

template<typename ENUM_TYPE>
ENUM_TYPE StateMachine<ENUM_TYPE>::GetState() const
{
	return m_state.State;
}

template<typename ENUM_TYPE>
const StateDefinition<ENUM_TYPE>& StateMachine<ENUM_TYPE>::GetStateDefinition() const
{
    return m_state;
}

#endif

