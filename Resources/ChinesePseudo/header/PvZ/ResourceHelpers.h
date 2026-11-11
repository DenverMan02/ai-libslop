//
//  ResourceHelpers.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 12/19/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ResourceHelpers_h
#define PlantsVersusZombies2_ResourceHelpers_h

#include <cstddef>
#include <string>

#include "Common.h"
#include "Image.h"
#include "PopAnim.h"
#include "Point.h"
#include "ResourceManager.h"
#include "RtDb.h"
#include "RtId.h"
#include "TodDebug.h"

Sexy::RtWeakPtr<Sexy::Image> GetImageByName(const std::string& i_id);
Sexy::RtWeakPtr<Sexy::Image> GetImageByNameWithUIFallback(const std::string& i_id);
Sexy::RtWeakPtr<Sexy::PopAnim> GetPAMByName(const std::string& i_id);
Sexy::RtWeakPtr<Sexy::PopAnim> GetNullPam();

inline Sexy::ResourceGroup* GetResourceGroup(const std::string& i_id)
{
	extern Sexy::ResourceManager* gResourceManager;
	// If you hit this then you tried to load a resource before this pointer was setup in LawnApp.
	DBG_ASSERT(gResourceManager);
	
	Sexy::ResourceGroup* group = gResourceManager->GetResourceGroupNamed(i_id);
	DBG_ASSERT(group);
	return group;
}

template <typename T> Sexy::RtId FindResourceIdHelper(const std::string& i_id, int i_overrideResolution = 0)
{
	extern Sexy::ResourceManager* gResourceManager;
	// If you hit this then you tried to load a resource before this pointer was setup in LawnApp.
	DBG_ASSERT(gResourceManager);

	int oldRes = gResourceManager->mCurArtRes;
	if (i_overrideResolution)
	{
		gResourceManager->mCurArtRes = i_overrideResolution;
	}

	Sexy::ResourceInfo* info = gResourceManager->GetResInfoForStringIdT<T>(i_id);

	Sexy::RtId id;
	
	if (info)
	{
		id = info->mInstanceRtId;
	}

	if (i_overrideResolution)
	{
		gResourceManager->mCurArtRes = oldRes;
	}

	return id;
}

template <typename T> Sexy::RtId FindResourceId(const std::string& i_id, int i_overrideResolution = 0)
{
    return FindResourceIdHelper<T>(i_id, i_overrideResolution);
}

template <> inline Sexy::RtId FindResourceId<Sexy::Image>(const std::string& i_id, int i_overrideResolution)
{
    Sexy::RtId id = FindResourceIdHelper<Sexy::Image>(i_id, i_overrideResolution);
    if (!id)
    {
        id = FindResourceIdHelper<Sexy::Image>("IMAGE_MISSING_IMAGE");
    }
    
    return id;
}

template <> inline Sexy::RtId FindResourceId<Sexy::PopAnim>(const std::string& i_id, int i_overrideResolution)
{
    Sexy::RtId id = FindResourceIdHelper<Sexy::PopAnim>(i_id, i_overrideResolution);
    if (!id)
    {
        id = FindResourceIdHelper<Sexy::PopAnim>("POPANIM_MISSING_POPANIM");
    }
    
    return id;
}

template <typename T> Sexy::RtId GetResourceId(const std::string& i_id, int i_overrideResolution = 0)
{
	Sexy::RtId id = FindResourceId<T>(i_id, i_overrideResolution);
	DBG_ASSERT_MSG(id.GetValue(), "GetResourceId() :: Can't find resource with id %s!", i_id.c_str());

	return id;
}

Sexy::ImagePtr GetImagePtrByFormattedName(const std::string& i_formatString, const std::string& i_specifier);

template <typename T> Sexy::RtWeakPtr<T> GetUIResource(const std::string& i_id)
{
	extern int gAppHeight;
	return Sexy::RtWeakPtr<T>(GetResourceId<T>(i_id, gAppHeight));
}

inline Sexy::Point GetImageOffset(Sexy::RtId i_imageId)
{
	if (i_imageId)
	{
		Sexy::Image::InfoClass* resourceInfo = Sexy::RtWeakPtr<Sexy::Image::InfoClass>(Sexy::RtId(Sexy::RtDb::SYSTEMTABLE_ResourceInfo, i_imageId.GetSlotIndex(), 1));
		if (resourceInfo)
		{
			return resourceInfo->mOffset;
		}
	}

	return Sexy::Point();
}

//
// A Base class that keeps track of all instances of itself via a static linked list.
// This list can then be used to invalidate all cached CachedResourcePtrBase m_ids when
// a new rsb is loaded.
//
class CachedResourcePtrBase
{
public:
    CachedResourcePtrBase();
    virtual ~CachedResourcePtrBase();
    static void FlushAllCachedIds();

    static bool DisallowConstruction;

protected:
    virtual void flushCachedId() = 0;
private:
    
    CachedResourcePtrBase* m_next;
    CachedResourcePtrBase* m_prev;
    
    static CachedResourcePtrBase* s_allCachedResourcePtrsHead;
};

template <typename T> 
class CachedResourcePtr : public CachedResourcePtrBase
{
public:
	CachedResourcePtr(const char* i_stringID)
	: m_stringID(i_stringID)
	, m_id(0)
	{
	}

    inline operator bool () { return IsValid(); }
    inline operator Sexy::RtWeakPtr<T> () { return Sexy::RtWeakPtr<T>(GetId()); }
	inline bool operator ! () { return !IsValid(); }

	inline bool IsValid() 
	{ 
		return GetId() ? Sexy::RtDb::GetDb()->GetObjectForId(GetId()) != NULL : false;
	}

	inline operator T* () 
	{ 
		return Sexy::RtDb::GetDb()->GetObjectForId(GetId())->template Cast<T>(); 
	}

	inline T* operator -> () 
	{ 
		return Sexy::RtDb::GetDb()->GetObjectForId(GetId())->template Cast<T>(); 
	}
	
	inline void SetId(Sexy::RtId i_id)
	{
		m_id = i_id;
	}

	inline Sexy::RtId GetId()
	{
		if (!m_id)
		{
			SetId(GetResourceId<T>(m_stringID));
		}

		return m_id;
	}
    
protected:
    
    //
    // CachedResourcePtrBase methods
    //
    
    void flushCachedId() override
    {
        m_id = Sexy::RtId(0);
    }

private:
	const char* m_stringID;
	Sexy::RtId m_id;
};

// Hack for our super ghetto resolution dependant UI image resources.
template <typename T>
class CachedUIResourcePtr : public CachedResourcePtrBase
{
public:
	CachedUIResourcePtr(const char* i_stringID)
	: m_stringID(i_stringID)
	, m_id(0)
	{
	}

    inline operator bool () { return IsValid(); }
    inline operator Sexy::RtWeakPtr<T> () { return Sexy::RtWeakPtr<T>(GetId()); }
	inline bool operator ! () { return !IsValid(); }

	inline bool IsValid() 
	{ 
		return GetId() ? Sexy::RtDb::GetDb()->GetObjectForId(GetId()) != NULL : false;
	}

	inline operator T* () 
	{ 
		return Sexy::RtDb::GetDb()->GetObjectForId(GetId())->template Cast<T>(); 
	}

	inline T* operator -> () 
	{ 
		return Sexy::RtDb::GetDb()->GetObjectForId(GetId())->template Cast<T>(); 
	}
	
	inline void SetId(Sexy::RtId i_id)
	{
		m_id = i_id;
	}

	Sexy::RtId GetId()
	{
		if (!m_id)
		{
			extern int gAppHeight;
			SetId(GetResourceId<T>(m_stringID, gAppHeight));
		}

		return m_id;
	}
protected:
    
    //
    // CachedResourcePtrBase methods
    //
    
    void flushCachedId() override
    {
        m_id = Sexy::RtId(0);
    }
    
private:
	const char* m_stringID;
	Sexy::RtId m_id;
};

#endif
