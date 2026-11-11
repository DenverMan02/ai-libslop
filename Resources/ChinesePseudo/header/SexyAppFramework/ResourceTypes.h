#pragma once
#ifndef __RESOURCETYPES_H__
#define __RESOURCETYPES_H__
//****************************************************************************
//**
//**  File     :  RESOURCETYPES.H
//**  Summary  :  Header - Resource Types
//**
//----------------------------------------------------------------------------
//**       $Id:$ 
//** $DateTime:$ 
//**   $Author:$ 
//**   $Change:$ 
//****************************************************************************
//============================================================================
//    HEADERS
//============================================================================
#include "Common.h"
#include "RtObject.h"
#include "RtId.h"
#include "RtDb.h"

namespace Sexy {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
class ResourceInfoClass;

class ResourceClass
: public RtClass
{
protected:
	ResourceInfoClass* mInfoClass;

public:
	RT_CLASS_DEFINE(ResourceClass, RtClass, RtClass) {}

	ResourceClass()
	: mInfoClass(NULL)
	{}

	void SetInfoClass(ResourceInfoClass* inInfoClass) { mInfoClass = inInfoClass; }
	ResourceInfoClass* GetInfoClass(bool inInherited = true) const
	{
		if (mInfoClass || !inInherited)
			return mInfoClass;
	
		for (const ResourceClass* cls = this; cls; cls = cls->GetSuper()->Cast<ResourceClass>())
		{
			if (cls->mInfoClass)
				return cls->mInfoClass;
		}
		DBG_ASSERTE(false && "ResourceClass::GetInfoClass: Info class expected but not found");
		return NULL;
	}
};

class BaseResource
: public RtObject
{
protected:
	RtId mResourceRtId;
	RtId mInfoRtId;
	friend class ResourceManager;

public:
	RT_CLASS_DEFINE_ABSTRACT(BaseResource, RtObject, ResourceClass);

	enum EResourceRegistrationType
	{
		RRT_Unregistered=0, // unregistered resource (has no valid RtId)
		RRT_Normal,			// normal resource (slotted with backing manifest res info, resides within a group)
		RRT_Hidden,			// hidden resource (has backing manifest res info and resides in a group, but is unslotted; used for things like Font layer images)
		RRT_Ungrouped		// ungrouped resource (has no backing manifest res info, does not live in a group, lifetime must be managed independently)
	};

	inline RtId GetRtId() { return mResourceRtId; }
	inline RtId GetResourceInfoRtId() { return mInfoRtId; }

	EResourceRegistrationType GetRegistrationType();
};

//============================================================================
//    GLOBAL DATA
//============================================================================
//============================================================================
//    GLOBAL FUNCTIONS
//============================================================================
//============================================================================
//    INLINE CLASS METHODS
//============================================================================
//============================================================================
//    TRAILING HEADERS
//============================================================================

} // namespace Sexy
//****************************************************************************
//**
//**    END HEADER RESOURCETYPES.H
//**
//****************************************************************************
#endif // __RESOURCETYPES_H__
