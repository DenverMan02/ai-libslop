//
//  StateMachineTableBuilder.h
//  PlantsVersusZombies2
//
//  Created by jsola on 3/1/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_StateMachineTableBuilder_h
#define PlantsVersusZombies2_StateMachineTableBuilder_h

#include "Singleton.h"
#include "StateMachine.h"

#define STATEMACHINE_BUILDER_BEGIN(base_enum_type) \
{	\
	typedef base_enum_type xxStateMachineBuilder_Enum_Type; \
	StateMachineTable<base_enum_type>& table = StateMachineTableBuilder::GetInstance().RegisterClass<base_enum_type>(StaticGetClass());

#define STATEMACHINE_BUILDER_ADDSTATE(state_function_suffix, enum_name) \
	table.AddStateDefinition((xxStateMachineBuilder_Enum_Type)enum_name, STATE_DEFINITION_NO_CONTEXT(xxStateMachineBuilder_Enum_Type, enum_name, state_function_suffix));

#define STATEMACHINE_BUILDER_ADDSTATE_MANUAL(state_definition, enum_name) \
	table.AddStateDefinition((xxStateMachineBuilder_Enum_Type)enum_name, state_definition);

#define STATEMACHINE_BUILDER_END() \
}

#define STATEMACHINE_GET_STATE(base_enum_type, enum_value) \
	( StateMachineTableBuilder::GetInstancePtr()->GetTable<base_enum_type>(GetClass()) \
		->GetStateDefinitionWithContext(enum_value, (void*)this) )

struct StateMachineTableBase
{
};

template<typename T>
struct StateMachineTable : public StateMachineTableBase
{
    virtual ~StateMachineTable() {}
    
	void AddStateDefinition(T i_enumValue, const StateDefinition<T>& i_stateDefinition)
	{
		// These should all be added in order
		DBG_ASSERT(i_enumValue == m_stateDefinitions.size());
		m_stateDefinitions.push_back(i_stateDefinition);
	}
	const StateDefinition<T>& GetStateDefinition(T i_enumValue) const
	{
		DBG_ASSERT(i_enumValue >= 0 && i_enumValue < m_stateDefinitions.size());
		return m_stateDefinitions[i_enumValue];
	}
	StateDefinition<T> GetStateDefinitionWithContext(T i_enumValue, void* i_context) const
	{
		StateDefinition<T> output = GetStateDefinition(i_enumValue);
		output.SetContext(i_context);
		return output;
	}
	
	void FillFrom(const StateMachineTable<T>& i_parentTable)
	{
		for (int i = 0; i < i_parentTable.m_stateDefinitions.size(); ++i)
		{
			AddStateDefinition((T)i, i_parentTable.GetStateDefinition((T)i));
		}
	}
	
private:
	
	std::vector<StateDefinition<T> > m_stateDefinitions;
};

class StateMachineTableBuilder : public LazySingleton<StateMachineTableBuilder>
{
public:
	StateMachineTableBuilder()
	{
	}
	virtual ~StateMachineTableBuilder();
	
	template<typename T>
	StateMachineTable<T>& RegisterClass(class RtClass* i_class)
	{
		// Can't register the same class twice
		DBG_ASSERT(m_stateMachineTables.find(i_class) == m_stateMachineTables.end());
		
		// Build it up
		StateMachineTable<T>* stateTable = new StateMachineTable<T>();
		m_stateMachineTableStorage.push_back(stateTable);
		m_stateMachineTables[i_class] = stateTable;
		
		// Fill it with our parents' states
		RtClass* parentClass = i_class->GetSuper();
		while (parentClass != NULL)
		{
			const StateMachineTable<T>* parentTable = GetTable<T>(parentClass);
			if (parentTable != NULL)
			{
				// Fill from this table, skip the rest (it already contains all parents)
				stateTable->FillFrom(*parentTable);
				break;
			}
			parentClass = parentClass->GetSuper();
		};
		return *stateTable;
	}
	
	template<typename T>
	const StateMachineTable<T>* GetTable(class RtClass* i_class)
	{
		StateMachineTableMap::const_iterator iter = m_stateMachineTables.find(i_class);
		if (iter != m_stateMachineTables.end())
		{
			const StateMachineTable<T>* table = (StateMachineTable<T>*)((*iter).second);
			return table;
		}
		// If we're here, we have no state machine table for ourselves
		// Our parent class, or some other class up the chain, might have specified one, though.
		// If so, find it, and Register that table as our own
		RtClass* parentClass = i_class->GetSuper();
		if (parentClass != NULL)
		{
			// Recursive call, will fill out ALL parents appropriately
			const StateMachineTable<T>* parentTable = GetTable<T>(parentClass);
			if (parentTable)
			{
				// This will give ourselves a unique copy of the parent's state table,
				// and cache it in our map for quicker retrieval in subsequent calls
				return &(RegisterClass<T>(i_class));
			}
		}
		// No luck, no states here!
		return NULL;
	}
	
private:
	std::vector<StateMachineTableBase*> m_stateMachineTableStorage;
	typedef std::map<class RtClass*, StateMachineTableBase*> StateMachineTableMap;
	StateMachineTableMap m_stateMachineTables;
};

#endif
