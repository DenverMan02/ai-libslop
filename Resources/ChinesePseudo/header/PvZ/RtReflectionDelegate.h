//
//  RtReflectionDelegate.h
//  PlantsVersusZombies2
//
//  Created by jsola on 3/6/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//
// 	Fully serializable wrapper for a delegate. Works with any object that has an RtId and
// member functions that are exposed via REFLECTION_CLASSBUILDER_METHOD_INSTANCE_ macros
//

#ifndef PlantsVersusZombies2_RtObjDelegate_h
#define PlantsVersusZombies2_RtObjDelegate_h

#include "RtObject.h"
#include "RtDb.h"
#include "RtDelegate.h"
#include "Reflection.h"

struct RtReflectionDelegateBase
{
	RtReflectionDelegateBase()
		: m_objectId(0)
	{}
	
	RtReflectionDelegateBase(RtId i_objectId, const std::string& i_methodName)
	{
		m_objectId = i_objectId;
		m_methodName = i_methodName;
	}
	RtId m_objectId;
	std::string m_methodName;
};

template<typename DELEGATE_TYPE>
struct RtReflectionDelegate : public RtReflectionDelegateBase
{
	RtReflectionDelegate()
	{
		m_delegateCached = false;
	}
	RtReflectionDelegate(RtId i_objectId, const std::string& i_methodName)
		: RtReflectionDelegateBase(i_objectId, i_methodName)
	{
//#ifdef _DEBUG
//		verifyValidParameters(i_objectId, i_methodName);
//#endif
		m_delegateCached = false;
		ensureCachedDelegate();
	}
	
	operator int() const
	{
		return (int)doesObjectExist();
	}
	
	const DELEGATE_TYPE* TryGetDelegate()
	{
		ensureCachedDelegate();
		if (doesObjectExist())
		{
			return &m_cachedDelegate;
		}
		return NULL;
	}
	
	const DELEGATE_TYPE& GetDelegate()
	{
		ensureCachedDelegate();
		DBG_ASSERT(doesObjectExist());
		return m_cachedDelegate;
	}

private:
#ifdef _DEBUG
	void verifyValidParameters(RtId i_objectId, const std::string& i_methodName)
	{
		RtObject* inObj = RtDb::GetDb()->GetObjectForId(m_objectId);
		if (inObj == NULL)
		{
			DBG_HALT_MSG("RtReflectionDelegate created with invalid RtId!");
			return;
		}
		RtClass* inClass = inObj->GetClass();
		Reflection::RMethod* method = inClass->GetBoundReflectionClass()->GetMethods(true)->GetNamed(m_methodName);
		if (method == NULL)
		{
			DBG_HALT_MSG("RtReflectionDelegate cannot find %s::%s!", inClass->GetName(), i_methodName.c_str());
			return;
		}
	}
#endif

	void ensureCachedDelegate()
	{
		RtObject* inObj = RtDb::GetDb()->GetObjectForId(m_objectId);
		if (!inObj)
		{
			m_delegateCached = true;
			m_objectId = RtId(0);
			return;
		}
		if (m_delegateCached)
		{
			return;
		}
		RtClass* inClass = inObj->GetClass();
		Reflection::RMethod* method = inClass->GetBoundReflectionClass()->GetMethods(true)->GetNamed(m_methodName);
		DBG_ASSERT_MSG(method != NULL, "RtReflectionDelegate cannot find %s::%s!", inClass->GetName(), m_methodName.c_str());
		memcpy((void*)&m_cachedDelegate, (void*)method->GetMethodDelegate(), sizeof(DELEGATE_TYPE));
		m_cachedDelegate.SetInstanceContext(inObj);
		
		m_delegateCached = true;
	}
	bool doesObjectExist() const
	{
		if (m_objectId.GetValue() == 0)
		{
			return false;
		}
		RtObject* inObj = RtDb::GetDb()->GetObjectForId(m_objectId);
		return (inObj != NULL);
	}
	
	DELEGATE_TYPE m_cachedDelegate;
	bool m_delegateCached;
};

#endif
