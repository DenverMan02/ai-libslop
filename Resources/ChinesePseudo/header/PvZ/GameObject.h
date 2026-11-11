//
//  GameObject.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/4/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "RtObject.h"
#include "RtSerial.h"
#include "RtDb.h"
#include "PVZDB.h"

class GameObject : public RtObject
{
public:
	RT_CLASS_DEFINE(GameObject, RtObject, RtClass);
	
protected:
	GameObject() {}
public:

	virtual ~GameObject();

	/// -- Public interface
	// static GameObject::Create(RtClass*, TableIndex)
	//	- Constructs a GameObject and stores it in the given table
	//	- Initializes the GameObject, calling the following
	//		registerForEvents()
	//		onInitialized()
	static GameObject* Create(RtClass* i_class, PVZDB::TableIndex i_inTable);
	template<typename T> static T* Create(PVZDB::TableIndex i_inTable) {
		return Create(T::StaticGetClass(), i_inTable)->template CastChecked<T>();
	}
	// static GameObject::CreateOutsideTable(RtClass*)
	//	- Constructs a GameObject, but does not store it in a table
	//	- Initialization still occurs
	static GameObject* CreateOutsideTable(RtClass* i_class)	{
		return Create(i_class, PVZDB::TABLE_INVALID);
	}
	template<typename T> static T* CreateOutsideTable()	{
		return Create<T>(PVZDB::TABLE_INVALID);
	}
	
	// Destroy()
	//	- If constructed via Create(), then we must be destroyed via Destroy()
	//	- Calls the following
	//		onDestroy()
	//		unRegisterForEvents() (will also automatically remove this from GameEventMgr)
	//	- Removes this object from its owning RtDbTable
	virtual void Destroy();
	
	// IsDestroyed()
	// - Evaluates whether or not the GameObject has been Destroyed via the Destroy method
	bool IsDestroyed() const;
	
	/// -- Accessors
	inline RtWeakPtr<GameObject> GetPtr() const;

	/// -- RtSerializableObject interface
	// Serialize(RtSerializeContext&)
	//	- Mostly a wrapper around the normal RtObject serialize protocol, but also
	//	sets up a callback to postLoad(). This occurs once ALL game packages and
	// 	objects have been loaded back in.
	//	- Override to do additional manual serialization.
	virtual bool Serialize(const RtSerializeContext& inContext) override;
    
    void PostLoad();

    void CallInitialize(RtId i_id);

protected:
	/// -- Virtual protected interface
	// RegisterForEvents is the load/save-safe place to register for game events
	virtual void registerForEvents()
	{}
	// UnregisterForEvents is a safe place to clean up from additional delegate hookups
	// (GameEventMgr unregistration is done for you!)
	virtual void unregisterForEvents()
	{}
	
	// onInitialized is called when we're first spawned, but not called after a game state load
	virtual void onInitialized()
	{}
	// onPostLoad is called after a game state load, after all objects have serialized
	virtual void onPostLoad()
	{}
	// onDestroy is called from Destroy(), before event unregistration and object teardown
	virtual void onDestroy()
	{}
	
private:
	/// -- Internal functions
	void initialize(RtId i_id);
	
	RtWeakPtr<GameObject> m_thisPtr;
};


/// Inline function definitions

RtWeakPtr<GameObject> GameObject::GetPtr() const
{
	return m_thisPtr;
}

namespace Message
{
	void GameObjectSerializedIn(GameObject *i_object);
}

#endif // __GAMEOBJECT_H__
