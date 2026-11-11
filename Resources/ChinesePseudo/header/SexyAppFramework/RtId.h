#pragma once
#ifndef __RTID_H__
#define __RTID_H__
//****************************************************************************
//**
//**  File     :  RTID.H
//**  Summary  :  Header - Rt - RtId class
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
#include "Debug.h"
#include "RtUtils.h"

namespace Sexy {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
// external forward declarations
class RtSerialBuffer;

/*
	RtNameTable

	Be aware that this is a CASE-SENSITIVE name table; we'll be putting in
	case-insensitive debugging aids for common user-facing issues, but making
	the core of the name table itself case-insensitive at its core results
	in many more types of problems (known from painful experience).
*/
// define the following to enable "paranoid" use of the name table, which checks for potential case sensitive/insensitive usage problems
// CDH FIXME$$$$ not using this yet (still need to add paranoid checks; I just wanted to add this as a placeholder reminder)
//#define RTNAMETABLE_PARANOID

// define the following to allow RtNames to contain pointers to their strings directly (alongside the indices), for debugging purposes
#define RTNAMETABLE_EMBEDSTRINGS

class RtNameTable
{
protected:
	class Entry
	: public RtRingItem<Entry>
	{
	public:
		uint32 mIndex; // index within entry vector
		std::wstring mString; // actual string data (the *only* place with backing string storage in the table; the maps etc will use const char* ptrs into here)
		uint32 mRefCount; // reference count for the name
	};

	struct NameStringCompareFunctor
	{
		bool operator() (const wchar_t* inStrA, const wchar_t* inStrB) const
		{
			return StringLess(inStrA, inStrB);
		}
	};
	struct NameStringCompareNoCaseFunctor
	{
		bool operator() (const wchar_t* inStrA, const wchar_t* inStrB) const
		{
			return StringLessNoCase(inStrA, inStrB);
		}
	};

	typedef std::map<const wchar_t*, int, NameStringCompareFunctor> StringMap;
	StringMap mStringMap; // pointers are into the fixed buffer or a dynamic entry string; no string storage in map itself

#ifdef RTNAMETABLE_PARANOID
	typedef std::map<const wchar_t*, int, NameStringCompareNoCaseFunctor> StringMapNoCase;
	StringMapNoCase mStringMapNoCase;
#endif

	std::vector<Entry*> mEntries; // entry pointers (yes there's some small allocations going on here, but the entries aren't POD and I don't feel comfortable using memcpy & patch tricks)
	Entry mEntryFreeListHead;
	Entry mEntryUsedListHead;

	Entry* FindEntry(const wchar_t* inStr);
	Entry* AddEntry(const wchar_t* inStr);
	void RemoveEntry(Entry* inEntry);

private:
	static RtNameTable* sRtNameTable; // private pointer to the singleton of GetNameTable(); only used for the debugger.

public:
	static RtNameTable* GetNameTable();

	RtNameTable();
	~RtNameTable();

	uint32 TableGetCount();
	uint32 TableIndexForString(const wchar_t* inStr);
	const wchar_t* TableStringForIndex(uint32 inIndex);
	uint32 TableGetRefCountForString(uint32 inIndex);
	uint32 TableRetainString(uint32 inIndex);
	uint32 TableReleaseString(uint32 inIndex);
};

/*
	RtName
*/
class RtName
{
private:
	uint32 mIndex;
#ifdef RTNAMETABLE_EMBEDSTRINGS
	const wchar_t* mStr;
#endif
		
	inline const wchar_t* StringForIndex() const
	{
		return RtNameTable::GetNameTable()->TableStringForIndex(mIndex);
	}
	inline uint32 Retain() const
	{
		return RtNameTable::GetNameTable()->TableRetainString(mIndex);
	}
	inline uint32 Release() const
	{
		return RtNameTable::GetNameTable()->TableReleaseString(mIndex);
	}

public:
	inline static uint32 StaticIndexForString(const wchar_t* inStr)
	{
		return RtNameTable::GetNameTable()->TableIndexForString(inStr);
	}

	inline RtName()
	: mIndex(0)
#ifdef RTNAMETABLE_EMBEDSTRINGS
	, mStr(L"")
#endif
	{}
	inline RtName(uint32 inIndex)
	: mIndex(inIndex)
	{
		Retain();
#ifdef RTNAMETABLE_EMBEDSTRINGS
		mStr = StringForIndex();
#endif
	}
	inline RtName(const RtName& inName)
	: mIndex(inName.mIndex)
	{
		Retain();
#ifdef RTNAMETABLE_EMBEDSTRINGS
		mStr = StringForIndex();
#endif
	}
	inline RtName(const wchar_t* inStr)
	{
		mIndex = StaticIndexForString(inStr);
		Retain();
#ifdef RTNAMETABLE_EMBEDSTRINGS
		mStr = StringForIndex();
#endif
	}
	inline RtName(const std::wstring& inStr)
	{
		mIndex = StaticIndexForString(inStr.c_str());
		Retain();
#ifdef RTNAMETABLE_EMBEDSTRINGS
		mStr = StringForIndex();
#endif
	}
	inline ~RtName()
	{
		Release();
#ifdef RTNAMETABLE_EMBEDSTRINGS
		mStr = L"";
#endif
	}

	inline const wchar_t* GetString() const { return StringForIndex(); }
	inline uint32 GetIndex() const { return mIndex; }
	inline uint32 GetRefCount() const
	{
		return RtNameTable::GetNameTable()->TableGetRefCountForString(mIndex);
	}

	inline operator const wchar_t* () const { return StringForIndex(); }

	inline RtName& operator = (uint32 inIndex)
	{
		if (mIndex != inIndex)
		{
			Release();
			mIndex = inIndex;
			Retain();
#ifdef RTNAMETABLE_EMBEDSTRINGS
			mStr = StringForIndex();
#endif
		}
		return *this;
	}
	inline RtName& operator = (const RtName& inStr)
	{
		if (mIndex != inStr.mIndex)
		{
			Release();
			mIndex = inStr.mIndex;
			Retain();
#ifdef RTNAMETABLE_EMBEDSTRINGS
			mStr = StringForIndex();
#endif
		}
		return *this;
	}
	inline RtName& operator = (const wchar_t* inStr)
	{
		Release();
		mIndex = StaticIndexForString(inStr);
		Retain();
#ifdef RTNAMETABLE_EMBEDSTRINGS
		mStr = StringForIndex();
#endif
		return *this;
	}

	inline bool operator == (const RtName& inName) const { return mIndex == inName.mIndex; }
	inline bool operator != (const RtName& inName) const { return mIndex != inName.mIndex; }
	inline bool operator < (const RtName& inName) const { return mIndex < inName.mIndex; }

	inline operator bool () const { return mIndex != 0; }
	inline bool operator ! () const { return mIndex == 0; }
};

/*
	RtId - 64-bit unique identifier for an object within the RtDb
*/
class RtId
{
/*
	RtId Bit Layout

        63    62-49     48                       47-0                     0
      |----|----------|----|----------------------------------------------|
      | NF |TableIndex| SX |            Revision and SlotIndex
      |    |          |    |
      |    |          |    |               47-16                  15-0
      |    |          |SX=0|----------------------------------|-----------|
      |    |          |                   Revision              SlotIndex
      |NF=0|          |
      |    |          |              47-24                   23-0
      |    |          |SX=1|-----------------------|----------------------|
      |    |          |            Revision                SlotIndex
	  |    |          |
      |----|---------------------------------------------------------------
	  |    | 62             61-31                         30-0            0
	  |    |----|----------------------------|----------------------------|
      |NF=1|Rese|    PackageOrTableName              ObjectAliasName
	  |    |rved|
      |----|----|---------------------------------------------------------|

	Bit 63 is the "Named ID Flag" (NF).  If NF is not set, the rest of the
	RtId bit layout directly addresses an object via a table, slot, and
	revision system as follows:

		Bits 62-49: 14-bit Table Index.  Bit 62 acts as a system table flag,
		            such that the upper 8k tables are reserved for the use
					by the framework, and the lower 8k tables (including
					zero, which is a valid table) are application-controlled.

		Bit 48: SlotIndex eXtension Flag (SX) (see Revision and SlotIndex).

		Bits 47-0: 48-bit Revision and SlotIndex.  Bit layout dependent on
		           SX flag.  If SX is 1, SlotIndex uses the low 24 bits,
				   and Revision the upper 24.  If SX is 0, SlotIndex only
				   uses the low 16 bits, and Revision the upper 32.

		Note that at table initialization, all slots are immediately bumped
		up to revision 1, guaranteeing that revision zero will never be used
		with a valid RtId.  This allows us to safely reserve the zero RtId
		as null.

	If the NF flag is set, then the RtId instead packs two RtName indices,
	one for a package name (or table name, if the name starts with $) and an
	object alias name within the associated table.  These RtIds act somewhat
	like "symbolic links"; there is always some indirection performed in
	order to resolve the actual RtId being referred to, which could change
	on the fly (if you have tight control over these situations, you can
	always cache the dereferenced RtId by calling the ResolveNamedId method
	of the RtDb).
*/
private:
	static const int kSystemTableStart		= 0x2000; // must remain a single bit
	static const int kMaxTableIndex			= 0x3fff;

	static uint32 sImplicitTableIndex;
	friend class RtDbTable;
	friend class RtDb;

private:
	uint64 mValue;

	inline bool IsSlotExtended() const { return (mValue & 0x1000000000000ull) != 0; }
	
	static inline bool StaticIsNamed(uint64 inValue) { return (inValue & 0x8000000000000000ull) != 0; }
	static inline uint32 StaticGetPackageNameIndex(uint64 inValue) { return (uint32)((inValue >> 31) & 0x7fffffff); }
	static inline uint32 StaticGetAliasNameIndex(uint64 inValue) { return (uint32)(inValue & 0x7fffffff); }

	inline void Set(uint64 inValue)
	{
		bool isNamed = IsNamed();
		bool isOtherNamed = StaticIsNamed(inValue);

		if (!isNamed && !isOtherNamed)
		{
			// most common case, going from unnamed to unnamed
			mValue = inValue;
			return;
		}

		if (isNamed && isOtherNamed)
		{
			// names on both sides; retain the new ones and release the old ones
			uint32 oldPkgName = GetPackageNameIndex();
			uint32 oldAliasName = GetAliasNameIndex();
			uint32 newPkgName = StaticGetPackageNameIndex(inValue);
			uint32 newAliasName = StaticGetAliasNameIndex(inValue);

			RtNameTable::GetNameTable()->TableRetainString(newPkgName);
			RtNameTable::GetNameTable()->TableRetainString(newAliasName);
			RtNameTable::GetNameTable()->TableReleaseString(oldPkgName);
			RtNameTable::GetNameTable()->TableReleaseString(oldAliasName);

			mValue = inValue;
		}
		else if (isNamed)
		{
			// currently named but new one is not named, so just release
			uint32 oldPkgName = GetPackageNameIndex();
			uint32 oldAliasName = GetAliasNameIndex();

			RtNameTable::GetNameTable()->TableReleaseString(oldPkgName);
			RtNameTable::GetNameTable()->TableReleaseString(oldAliasName);

			mValue = inValue;
		}
		else
		{
			// currently unnamed but changing to named
			uint32 newPkgName = StaticGetPackageNameIndex(inValue);
			uint32 newAliasName = StaticGetAliasNameIndex(inValue);

			RtNameTable::GetNameTable()->TableRetainString(newPkgName);
			RtNameTable::GetNameTable()->TableRetainString(newAliasName);

			mValue = inValue;
		}
	}

public:
	inline RtId() : mValue(0) {}
	inline explicit RtId(uint64 inValue) : mValue(0) { Set(inValue); }
	inline RtId(const RtId& inId) : mValue(0) { Set(inId.mValue); }
	inline RtId(uint32 inTable, uint32 inSlotIndex, uint32 inRevision)
	: mValue(0) 
	{
		uint64 v;
		if (inSlotIndex < 0x10000)
			v = (((uint64)inRevision) << 16) | (uint64)inSlotIndex;
		else
			v = ((((uint64)inRevision) << 24) | (uint64)inSlotIndex) | 0x1000000000000ull;
		v |= ((uint64)inTable) << 49;
		
		Set(v);
	}
	inline RtId(const RtName& inObjectAliasName, const RtName& inPackageName)
	: mValue(0) 
	{
		uint64 v = ((uint64)inPackageName.GetIndex()) << 31;
		v |= (uint64)inObjectAliasName.GetIndex();
		v |= 0x8000000000000000ull;

		Set(v);
	}
	inline ~RtId()
	{
		Set(0);
	}

	inline uint64 GetValue() const { return mValue; }
	
	inline bool IsNamed() const { return (mValue & 0x8000000000000000ull) != 0; }
	
	inline uint32 GetTableIndex() const
	{
		DBG_ASSERTE(!IsNamed() && "RtId::GetTableIndex: Called on named RtId (bad usage pattern)");
		return (uint32)((mValue >> 49) & kMaxTableIndex);
	}
	inline uint32 GetSlotIndex() const
	{
		DBG_ASSERTE(!IsNamed() && "RtId::GetSlotIndex: Called on named RtId (bad usage pattern)");
		return IsSlotExtended() ? (uint32)(mValue & 0xffffff) : (uint32)(mValue & 0xffff);
	}
	inline uint32 GetRevision() const
	{
		DBG_ASSERTE(!IsNamed() && "RtId::GetRevision: Called on named RtId (bad usage pattern)");
		return IsSlotExtended() ? (uint32)((mValue >> 24) & 0xffffff) : (uint32)((mValue >> 16) & 0xffffffff);
	}
	inline uint32 GetPackageNameIndex() const
	{
		DBG_ASSERTE(IsNamed() && "RtId::GetPackageNameIndex: Called on unnamed RtId (bad usage pattern)");
		return (uint32)((mValue >> 31) & 0x7fffffff);
	}
	inline uint32 GetAliasNameIndex() const
	{
		DBG_ASSERTE(IsNamed() && "RtId::GetAliasNameIndex: Called on unnamed RtId (bad usage pattern)");
		return (uint32)(mValue & 0x7fffffff);
	}

	inline RtId& operator = (uint64 inValue) { Set(inValue); return *this; }
	inline RtId& operator = (const RtId& inId) { Set(inId.mValue); return *this; }

	inline bool operator == (const RtId& inId) const { return mValue == inId.mValue; }
	inline bool operator != (const RtId& inId) const { return mValue != inId.mValue; }

	inline operator bool () const { return mValue != 0; }
	inline bool operator ! () const { return mValue == 0; }

	static void StaticSetImplicitTableIndex(uint32 inTableIndex); // 0xffffffff = unset
	static uint32 StaticGetImplicitTableIndex();
	
	void Serialize(RtSerialBuffer* inBuffer);

	void ToString(std::string& outStr, bool inMemoryOnly = false) const;
	void ToString(std::wstring& outStr, bool inMemoryOnly = false) const;
	static bool IsRtIdString(const std::string& inStr);
	static bool IsRtIdString(const std::wstring& inStr);
	static RtId StaticParse(const std::string& inStr);
	static RtId StaticParse(const std::wstring& inStr);

public:
	struct Uid
	{
		uint32 mSlot; // slot when object was first created (not just during this session, but *ever*)
		uint32 mRevision; // revision when object was first created (not just during this session, but *ever*)
		uint32 mDbTime; // creation timestamp of RtDb during session when object was first created

		Uid() : mSlot(0), mRevision(0), mDbTime(0) {}
		Uid(uint32 inSlot, uint32 inRevision, uint32 inDbTime) : mSlot(inSlot), mRevision(inRevision), mDbTime(inDbTime) {}
		explicit Uid(const RtId& inId);

		inline operator bool () const { return mSlot!=0 || mRevision!=0 || mDbTime!=0; }
		inline bool operator ! () const { return mSlot==0 && mRevision==0 && mDbTime==0; }

		inline bool operator == (const Uid& inUid) const { return mSlot==inUid.mSlot && mRevision==inUid.mRevision && mDbTime==inUid.mDbTime; }
		inline bool operator != (const Uid& inUid) const { return mSlot!=inUid.mSlot || mRevision!=inUid.mRevision || mDbTime!=inUid.mDbTime; }

		inline bool operator < (const Uid& inUid) const
		{
			if (mSlot!=inUid.mSlot)
			{
				if (mSlot<inUid.mSlot) return true;
				return false;
			}
			if (mRevision!=inUid.mRevision)
			{
				if (mRevision<inUid.mRevision) return true;
				return false;
			}
			if (mDbTime<inUid.mDbTime) return true;
			return false;
		}

		static Uid StaticParse(const std::string& inStr);
	};

	// these are only used during JSON<->RTON conversion in order to avoid data loss when using RtId as an intermediary (e.g. at ResGen time, the associated tables don't exist)
	struct OfflineId
	{
		Uid mUid;
		RtName mAlias; // if zero, use Uid instead
		RtName mPackage; // if zero, assume an "@."-style local export

		inline operator bool () const { return mUid || mAlias || mPackage; }
		inline bool operator ! () const { return !mUid && !mAlias && !mPackage; }

		void Serialize(RtSerialBuffer* inBuffer);
		void ToString(std::string& outStr);
		
		static RtId::OfflineId StaticParse(const std::string& inStr);
	};
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

namespace std {
    
    template<>
    struct hash<Sexy::RtName>
    {
        static hash<int32> m_hasher;
        size_t operator() (const Sexy::RtName& i_name) const
        {
            return m_hasher(i_name.GetIndex());
        }
    };
    
    template<>
    struct hash<Sexy::RtId>
    {
        static hash<uint64> m_hasher;
        size_t operator() (const Sexy::RtId& i_id) const
        {
            return m_hasher(i_id.GetValue());
        }
    };
    
    template<>
    struct hash<Sexy::RtId::Uid>
    {
        static hash<uint32> m_hasher;
        size_t operator() (const Sexy::RtId::Uid& i_uid) const
        {
            return m_hasher(i_uid.mSlot);
        }
    };
}

//****************************************************************************
//**
//**    END HEADER RTID.H
//**
//****************************************************************************
#endif // __RTID_H__
