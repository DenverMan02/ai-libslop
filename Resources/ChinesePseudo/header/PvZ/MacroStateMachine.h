//
//  MacroStateMachine.h
//  PlantsVersusZombies2
//
//	Implements a statemachine in a single virtual function using macros
//
//	Derived classes may override functionality for individual states, and extend the FSM with additional states
//
//  Created by Joseph Sola on 9/13/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_MacroStateMachine_h
#define PlantsVersusZombies2_MacroStateMachine_h

///
/// Overview
///

// This system lets you quickly create a state machine in a class heirarchy. Arbitrary state changes can be triggered
// from within or outside of the state machine definition. Derived classes may override OnEnter, Update, and OnExit
// functionality of their parent classes.
//
// This system adds a single (enum) member variable and one virtual function to your base class.
//
// Defining the statemachine is done with a set of macros that keep your state machine neat and easy to build and extend.
// Under the hood, these macros resolve down to a few switch() statements. See in-depth documentation below for more info.
//
// Requirements:
//	- Classes must participate in the RtObject system (or have ThisClass and SuperClass typedef'ed to the appropriate class names)
//	- RtDelegates must be enabled in your project

///
/// Setup and Usage
///

// 1. Declare states as an enum
//
// Create an enum to hold your possible states in the base class' header file.
// (I recommend using the STATE_ENUM_ macros, as these let you easily create additional states that are only used by child classes)
//
//		STATE_ENUM_BASE_BEGIN(ZombieState)
//			Idle,
//			Walk,
//			Eat,
//			Die,
//		STATE_ENUM_END(ZombieState);
//
// 2. Declare member variable and state handler function
//
// Creates the virtual function that does state handling and a member variable of the enum type to hold current state
//
//		class Zombie : public RtObject
//		{
//		public:
//			RT_CLASS_DEFINE(Zombie, RtObject, RtClass);
//		protected:
//			DECLARE_FSM_HANDLER_BASE(ZombieState);
//		private:
//			DECLARE_FSM_STATE_VALUE(ZombieState);
//		};
//
// 3. Initialize the FSM variable and update the state machine
//
//		void Zombie::onInitialized()
//		{
//			INITIALIZE_FSM(ZombieState);
//			SET_FSM_STATE(ZombieState, Walk);
//		}
//
//		void Zombie::onUpdate()
//		{
//			UPDATE_FSM(ZombossBattleState);
//		}
//
// 4. Define the state machine
//
// Write your state machine using DEFINE_FSM_BEGIN, FSM_STATE, and ON_ENTER/ON_UPDATE/ON_EXIT.
// Any unspecified states and ON_ sections will defer execution to the parent class' implementation (or do nothing if in the base class).
//
// Example:
//
//		DEFINE_FSM_BEGIN(Zombie, ZombieState)
//			FSM_STATE(Idle)
//				ON_ENTER()
//				{
//					playIdleAnimation();
//				}
//			FSM_STATE(Walk)
//				ON_ENTER()
//				{
//					playWalkAnimation();
//				}
//				ON_UPDATE()
//				{
//					if (hasPlantTarget())
//					{
//						SET_FSM_STATE(ZombieState, Eat);
//					}
//				}
//			FSM_STATE(Eat)
//				ON_ENTER()
//				{
//					playEatAnimation();
//				}
//				ON_UPDATE()
//				{
//					damagePlantTarget();
//					if (!hasPlantTarget())
//					{
//						SET_FSM_STATE(ZombieState, Walk);
//					}
//				}
//			FSM_STATE(Die)
//				ON_ENTER()
//				{
//					playDeathAnimation();
//				}
//				ON_UPDATE()
//				{
//					if (currentAnimationFinished())
//					{
//						Destroy();
//					}
//				}
//		DEFINE_FSM_END()
//
// 5. Other macros
//
//	- GET_FSM_STATE(state_enum) calls a member function that returns the current FSM state enum
//	- FSM_STATE_VALUE(state_enum) is replaced by the member variable name that holds the current FSM state enum
//	- SUPER() can be called from within any ON_() sections in the FSM to execute the super class' code for that section

///
/// Overriding and extending FSMs in child classes
///

// Derived classes can modify and extend functionality of parent class FSMs by adding states and changing state functions.
//
// 1. Create additional state(s)
//
//		STATE_ENUM_CHILD_BEGIN(ZombiePolevaulterState, ZombieState)
//			Polevault,
//		STATE_ENUM_END(ZombiePolevaulterState)
//
// 2. Declare state machine handler
//
//		class ZombiePolevaulter : public Zombie
//		{
//		public:
//			RT_CLASS_DEFINE(ZombiePolevaulter, Zombie, RtClass);
//		protected:
//			DECLARE_FSM_HANDLER_DERIVED(ZombieState);
//		}
//
// 3. Define new states and modify base state functionality
//
//		DEFINE_FSM_BEGIN(ZombiePolevaulter, ZombieState)
//			FSM_STATE(Walk)
//				ON_UPDATE()
//				{
//					if (hasVaultableTarget())
//					{
//						SET_FSM_STATE(ZombieState, Polevault);
//					}
//					else
//					{
//						SUPER();
//					}
//				}
//			FSM_STATE(Polevault)
//				ON_ENTER()
//				{
//					playPolevaultAnimation();
//				}
//				ON_UPDATE()
//				{
//					if (currentAnimationFinished())
//					{
//						SET_FSM_STATE(ZombieState, Walk);
//					}
//				}
//		DEFINE_FSM_END()
//

///
/// Technical details
///

// Under the hood, the state machine is implemented by a single virtual function that takes a current state and an action,
// such as 'Enter' or 'Update' or 'Exit.' Updating the state is just calling this function with STATEACTION_UPDATE. Changing
// the current state goes through a non-virtual member function that calls this function with STATEACTION_EXIT and the current
// state, changes the state member variable, and then calls it with STATEACTION_ENTER and the new state.
//
// The state machine handler function is one switch statement for the current state, and nested switch statements for
// the state actions of that state. Undefined actions and states fall through to default: case statements that pass execution
// off to a parent class implementation if one exists. The macros exist to reduce programmer workload and error in constructing
// the fairly complicated switch statement.
//
// The FSM definition macros for the first couple states of the Zombie:: example expand out into the following (with some
// explanatory comments added that are not actually within the macros)
//
//		void Zombie::HandleStateMachine_ZombieState(ZombieState i_currentState, StateAction i_action)
//		{
//			// This delegate removes the need for a base_state_enum macro parameter from FSM_STATE And DEFINE_FSM_END
//			Delegate2<ZombieState, StateAction> handleSuperFSMAction = MakeDelegate(*this, &ThisClass::HandleSuperFSMAction_ZombieState); \
//			typedef BaseEnum_t base_state_enum;
//			switch (i_currentState)
//			{
//				// This first case will exit out of a just-initialized, stateless FSM
//				case (ZombieState)(-1):
//				{
//					switch (i_action)
//					{
//						case STATEACTION_NONE:
//						break;
//						default:
//							handleSuperFSMAction(i_currentState, i_action);
//							return;
//					}
//				}
//				break;
//				
//				case (BaseEnum_t)Idle:
//				{
//					switch (i_action)
//					{
//						// This extra STATEACTION_NONE ensures that there is at least one case in the containing
//						// switch statement, since every following macro begins with 'break'
//						case STATEACTION_NONE:
//						break;
//						case STATEACTION_ENTER:
//						{
//							// This is the user-defined state code
//							playIdleAnimation();
//						}
//						break;
//						default:
//							handleSuperFSMAction(i_currentState, i_action);
//							return;
//					}
//				}
//				break;
//				
//				case (BaseEnum_t)Walk:
//				{
//					switch (i_action)
//					{
//						case STATEACTION_NONE:
//						break;
//						case STATEACTION_ENTER:
//						{
//							playWalkAnimation();
//						}
//						break;
//						case STATEACTION_UPDATE:
//						{
//							if (hasPlantTarget())
//							{
//								setState_ZombieState((ZombieState)Eat);
//							}
//						}
//						break;
//						default:
//							handleSuperFSMAction(i_currentState, i_action);
//							return;
//					}
//				}
//				break;
//
//				...
//				
//				default:
//					handleSuperFSMAction(i_currentState, i_action);
//					return;
//			}
//		}
//

#include "RtDelegate.h"
// Included for the STATE_ENUM_BASE_BEGIN + STATE_ENUM_CHILD_BEGIN functions which work very well for this method
#include "StateMachine.h"


enum StateAction
{
	STATEACTION_NONE,
	STATEACTION_ENTER,
	STATEACTION_UPDATE,
	STATEACTION_EXIT,
	STATEACTION_EVENTS_BEGIN
};
namespace Sexy
{
    RT_INVOKEVARIANT_DECLARE_TYPE_UINT32(StateAction);
}

#define EVENT_ENUM_BEGIN(enum_type) \
enum enum_type { \
	enum_type##_PRE_BEGIN = (STATEACTION_EVENTS_BEGIN - 1),
#define EVENT_ENUM_END(enum_type) \
}; \
namespace Sexy { \
RT_INVOKEVARIANT_DECLARE_TYPE_UINT32(enum_type); \
} \

//#define FSM_LOG_ENABLED

#ifdef FSM_LOG_ENABLED
	#define FSM_LOG_SETSTATE(base_state_enum, new_state) { OutputDebugStrF("[0x%08x] SetState (CurrState: %d, NewState: %d)\n", this, FSM_STATE_VALUE(base_state_enum), new_state); }
	#define FSM_LOG_HANDLESTATEMACHINE(current_state, action_enum) { OutputDebugStrF("[0x%08x] Handle (State: %d, Action: %d)\n", this, current_state, action_enum); }
#else
	#define FSM_LOG_SETSTATE(base_state_enum, new_state) {}
	#define FSM_LOG_HANDLESTATEMACHINE(current_state, action_enum) {}
#endif

#define FSM_STATE_VALUE(base_state_enum) \
	m_currentState_##base_state_enum

#define DECLARE_FSM_STATE_VALUE(base_state_enum) \
	base_state_enum FSM_STATE_VALUE(base_state_enum);

#define INITIALIZE_FSM(base_state_enum) \
	FSM_STATE_VALUE(base_state_enum) = (base_state_enum)(-1)

#define DECLARE_FSM_HANDLER_BASE(base_state_enum) \
	virtual void HandleStateMachine_##base_state_enum(base_state_enum i_currentState, StateAction i_action); \
	void setState_##base_state_enum(base_state_enum i_newState) \
	{ \
		FSM_LOG_SETSTATE(base_state_enum, i_newState) \
		if (FSM_STATE_VALUE(base_state_enum) != (base_state_enum)(-1)) \
			HandleStateMachine_##base_state_enum(m_currentState_##base_state_enum, STATEACTION_EXIT); \
		FSM_STATE_VALUE(base_state_enum) = i_newState; \
		if (FSM_STATE_VALUE(base_state_enum) != (base_state_enum)(-1)) \
			HandleStateMachine_##base_state_enum(m_currentState_##base_state_enum, STATEACTION_ENTER); \
	} \
	void HandleSuperFSMAction_##base_state_enum(base_state_enum i_currentState, StateAction i_action) \
	{ } \
	base_state_enum getState_##base_state_enum() const \
	{ \
		return FSM_STATE_VALUE(base_state_enum); \
	}

#define DECLARE_FSM_HANDLER_DERIVED(base_state_enum) \
	virtual void HandleStateMachine_##base_state_enum(base_state_enum i_currentState, StateAction i_action) override; \
	void HandleSuperFSMAction_##base_state_enum(base_state_enum i_currentState, StateAction i_action) \
	{ \
		SuperClass::HandleStateMachine_##base_state_enum(i_currentState, i_action); \
	}

#define GET_FSM_STATE(base_state_enum) \
	getState_##base_state_enum()

#define UPDATE_FSM(base_state_enum) \
	HandleStateMachine_##base_state_enum(GET_FSM_STATE(base_state_enum), STATEACTION_UPDATE)

#define SEND_FSM_EVENT(base_state_enum, event) \
	HandleStateMachine_##base_state_enum(GET_FSM_STATE(base_state_enum), (StateAction)event)

#define SET_FSM_STATE(base_state_enum, new_state) \
	setState_##base_state_enum((base_state_enum)new_state)

#define SUPER() \
	handleSuperFSMAction(i_currentState, i_action)

#define DEFINE_FSM_BEGIN(classname, base_state_enum) \
void classname::HandleStateMachine_##base_state_enum(base_state_enum i_currentState, StateAction i_action)				\
{																											\
	FSM_LOG_HANDLESTATEMACHINE(i_currentState, i_action) \
	Delegate2<base_state_enum, StateAction> handleSuperFSMAction = MakeDelegate(*this, &ThisClass::HandleSuperFSMAction_##base_state_enum); \
	typedef base_state_enum BaseEnum_t; \
	switch ((int32)i_currentState)																					\
	{																										\
		case (-1):																			\
		{																									\
			switch (i_action)																				\
			{																								\
				case STATEACTION_NONE:

#define FSM_STATE(state_name)	\
				break;							\
				default:						\
					handleSuperFSMAction(i_currentState, i_action); \
					return;						\
			}									\
		}										\
		break;									\
												\
		case (int32)state_name:			\
		{										\
			switch ((int32)i_action)			\
			{									\
				case STATEACTION_NONE:

#define ON_ENTER()								\
				break;							\
				case STATEACTION_ENTER:

#define ON_UPDATE()								\
				break;							\
				case STATEACTION_UPDATE:

#define ON_EXIT()								\
				break;							\
				case STATEACTION_EXIT:

#define ON_EVENT(x)								\
				break;							\
				case x:

#define DEFINE_FSM_END()			\
				break;							\
				default:						\
					handleSuperFSMAction(i_currentState, i_action); \
					return;						\
			}									\
		}										\
		break;									\
												\
		default:								\
			handleSuperFSMAction(i_currentState, i_action); \
			return;								\
	}											\
}

#endif
