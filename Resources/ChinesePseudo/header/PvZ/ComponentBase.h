//
//  ComponentBase.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 12/2/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ComponentBase__
#define __PlantsVersusZombies2__ComponentBase__

#include "core.h"
#include "GameObject.h"

//
// Components are separately running elements that are owned by a BoardEntity.
//
// They are intended to allow you to isolate code blocks that:
//
// - Do not need to know about other components / lots of internal object data
// - Interact primarily through update or other messages
//
// It was originally constructed to isolate the concept of "WhackAZombie touch" but
// is very generic and can be used for many different things.
//

typedef RtWeakPtr<class BoardEntity> BoardEntityPtr;
typedef RtWeakPtr<class ComponentBase> ComponentBasePtr;

enum ComponentState
{
	PVZ_BEGIN_ENUM(COMPONENTSTATE_),
	COMPONENTSTATE_NotStarted,
	COMPONENTSTATE_Running,
	COMPONENTSTATE_Finished,
	PVZ_END_ENUM(COMPONENTSTATE_),
};

class ComponentBase : public GameObject
{
public:
	RT_CLASS_DEFINE(ComponentBase, GameObject, RtClass);
	
	ComponentBase() : m_state(COMPONENTSTATE_NotStarted), m_initialized(false), m_owner(nullptr) {}
	virtual ~ComponentBase() {};
	
public:
	void SetOwner(BoardEntityPtr i_owner);
	BoardEntityPtr GetOwner() { return m_owner; }
	void SetName(const std::string& i_name) { m_name = i_name; }
 
	void Initialize()
	{
		if (m_initialized)
		{
			return;
		}
		
		registerForEvents();
		
		m_initialized = true;
	}
	
	void Uninitialize()
	{
		if (m_initialized == false)
		{
			return;
		}
		
		unregisterForEvents();
		
		m_initialized = false;
	}
	
	void Begin()
	{
		DBG_ASSERT(COMPONENTSTATE_NotStarted == m_state);
		Initialize();
		onBegin();
		m_state = COMPONENTSTATE_Running;
	}
	
	void Update()
	{
		//DBG_ASSERT(COMPONENTSTATE_Running == m_state);
		onUpdate();
	}
	
	void Draw(Sexy::Graphics* i_g)
	{
		//DBG_ASSERT(COMPONENTSTATE_Running == m_state);
		onDraw(i_g);
	}
	
	void End()
	{
		DBG_ASSERT(COMPONENTSTATE_Finished != m_state);
		onEnd();
		Uninitialize();
		m_state = COMPONENTSTATE_Finished;
	}
	
	bool IsStarted() { return (COMPONENTSTATE_NotStarted != m_state); }
	bool IsRunning() { return (COMPONENTSTATE_Running == m_state); }
	bool IsFinished() { return (COMPONENTSTATE_Finished == m_state); }
	
protected:
	virtual void onBegin() {}
	virtual void onUpdate() {}
	virtual void onDraw(Sexy::Graphics* i_g) {}
	virtual void onEnd() {}
	virtual void registerForEvents() override {}
	virtual void unregisterForEvents() override {}
	
private:
	std::string m_name;
	ComponentState m_state;
	BoardEntityPtr m_owner;
	bool m_initialized;
};


class ComponentRunnerBase : public ComponentBase
{
public:
	RT_CLASS_DEFINE_ABSTRACT(ComponentRunnerBase, ComponentBase, RtClass);
	
	virtual void Clear() = 0;
	virtual int Size() const = 0;
	virtual bool IsEmpty() const = 0;
	virtual void EndAll() = 0;
	virtual void OnPostLoad() = 0;
	
protected:

};

class ComponentRunner : public ComponentRunnerBase
{
public:
	RT_CLASS_DEFINE(ComponentRunner, ComponentRunnerBase, RtClass);
	
	ComponentRunner();
	virtual ~ComponentRunner();
	
	template<typename T>
	T* Add(BoardEntityPtr i_owner, const std::string& i_name);
	
	void Add(ComponentBase* i_component, BoardEntityPtr i_owner, const std::string& i_name);
	
	void Clear() override;
	int Size() const override;
	bool IsEmpty() const override;
	void EndAll() override;
	void OnPostLoad() override;
	
protected:
	
	void onBegin() override;
	void onUpdate() override;
	void onDraw(Sexy::Graphics* i_g) override;
	void onEnd() override;
	
	void processActions();

	std::vector<ComponentBasePtr> m_components;
};

template<typename T>
T* ComponentRunner::Add(BoardEntityPtr i_owner, const std::string& i_name)
{
	T* component = GameObject::Create<T>(PVZDB::TABLE_GAMEOBJECTS);
	
	Add(component, i_owner, i_name);
	
	return component;
}

#endif /* defined(__PlantsVersusZombies2__ComponentBase__) */
