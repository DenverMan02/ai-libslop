#pragma once
#ifndef __RTDB_H__
#define __RTDB_H__
//****************************************************************************
//**
//**  File     :  RTDB.H
//**  Summary  :  Header - Rt - Database & Id-related Classes
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
#include "RtId.h"
#include "RtUtils.h"
#include "RtObject.h"
#include "RtDelegate.h"
#include <memory>
#include <cstddef>
#include "CritSect.h"

namespace Sexy {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
// forward declarations
class RtDbTable;
class RtDb;

// external declarations
class RtObject;
class RtClass;
class RtSerialBuffer;
class RtSerialRtonSync;
class RtSerialRtonWriter;

/*
	RtDbTable
*/
class RtDbTable
{
public:
	typedef Delegate1wRet< bool, const RtId& > IterateFilterDelegateType;
	typedef Delegate1< const RtId& > IterateActionDelegateType;
	typedef Delegate2wRet<int32, const RtId&, const RtId&> SortDelegateType;

	enum EObjectDeletionMode
	{
		ODM_Auto, // normal auto-deletion, object is deleted when refcount reaches zero
		ODM_Deferred, // deferred deletion, doesn't happen until RunDeferredDeletions
		ODM_Never, // object is not deleted (used for externally-owned objects)
	};

	// Please don't use this class it is weird and terrible
	class IteratorStorage
	{
	protected:
		std::vector<uint32> mDataFloorStack;

	public:
		// returns a start index
		uint32 PushIterator(uint32 inCount, RtDbTable* inTable);
		void PopIterator(uint32 inCount);

		std::vector<RtId> mData;
	};

	struct TableOptions
	{
		uint32 mInitialSlotCount; // number of slots to start the table at when it's initially created
		RtName mTableName; // identifier for the table, independent of any particular package that might be loaded into it
		std::string mDisplayName; // human-readable table name, if any (tables don't need "names" internally, but they can be helpful in diagnostic tools etc)
		bool mIsFixedContent; // true if the intent of the table is to represent "fixed" content objects that don't tend to change significantly during runtime
		bool mSysTableActAsUserTable; // option used with system tables; if true then the table summary will represent the table as if it were a user table (for LiveLink)

		TableOptions()
		: mInitialSlotCount(0)
		, mIsFixedContent(false)
		, mSysTableActAsUserTable(false)
		{}
	};

protected:
	/*
		Slots are freelisted in a ring rather than a singly-linked list,
		because of the slot/revision size issues.  We want low slots to
		be placed at the beginning of the freelist, but high slots (those
		which use the id slot extension bit, which allow fewer revisions)
		to be placed at the end of the freelist instead so they're only
		reused as a last resort.
	*/
	class Slot
	: public RtRingItem<Slot>
	{
	public:
		enum
		{
			SLOTF_Used			= 0x80000000, // slot is currently used (linked to the used list)
			SLOTF_DeferDelete	= 0x40000000, // deferred object deletion (release uses a condemned list)
			SLOTF_NeverDelete	= 0x20000000, // never delete object (object is owned externally)
			SLOTF_Standalone	= 0x10000000, // one of the object's refcounts is an implicit strong ref from the table itself
			SLOTF_Watched		= 0x08000000, // slot is watched for access events
			SLOTF_RefTracked	= 0x04000000, // slot refcount adjustments are tracked for diagnostic purposes (debug only)

			SLOTF_FLAGMASK		= 0xfc000000,
			SLOTF_FLAGSHIFT		= 26,
			SLOTF_REFCOUNTMASK	= 0x03ffffff
		};

		RtObject* mObject;
		uint32 mRevision;
		uint32 mRefCountAndFlags;
		RtId::Uid mUid;
	};
	struct SlotCompare
	{
		static RtDbTable* sSortCurTable;
		static SortDelegateType sSortCurDelegate;

		static int Func(const void* a, const void* b);
	};

	uint32 mTableIndex;
	Slot* mSlots;
	uint32 mSlotCount;
	Slot mFreeListHead; // slots that are completely free and ready for use
	uint32 mFreeSlotCount;
	Slot mUsedListHead; // slots currently in active use
	uint32 mUsedSlotCount;
	Slot mCondemnedListHead; // slots that have their Ids released but which still have an object (deferred destruction)
	uint32 mCondemnedSlotCount;
	Slot mRetiredListHead; // slots which have expired their revision range and can no longer be used
	uint32 mRetiredSlotCount;
	IteratorStorage mIteratorStorage; // stack-like buffer used for iteration // CDH FIXME$$ whenever we add MT support, this buffer will need to be TLS for each thread
	TableOptions mTableOptions;
	RtName mCurrentPackage; // name of the package (usually based on a file name) currently loaded into the table
	std::wstring mCurrentPackageFileName; // actual system-friendly filename for the package (the mCurrentPackage RtName may be slightly different, e.g. slashes always forward, no file extension etc.)
	bool   mFromLocalFile;// is content from LocalFile

	typedef std::map<RtId::Uid, uint64> UidToIdMap;
	UidToIdMap mUidToIdMap;
	typedef std::unordered_map<RtName, RtId::Uid> AliasNameToUidMap;
	AliasNameToUidMap mAliasNameToUidMap;

	void IntegrityCheck();
	void GrowSlotVector(uint32 inSlotCount, const std::string& theFilename = "");
	Slot* AllocSlot();
	void FreeSlot(Slot* inSlot, bool inDeferDelete);
	Slot* GetSlotForId(const RtId& inId, bool inDoWarn) const;
	void SetSlotObjectDeletionMode(Slot* inSlot, EObjectDeletionMode inMode) const;

	inline RtId GetIdForSlot(Slot* inSlot) const
	{
		const auto index = inSlot - mSlots;

#ifdef HOST_WINDOWS
		DBG_ASSERT(TypeCanFitValue<uint32_t>(index));
		return RtId(mTableIndex, static_cast<uint32_t>(index), inSlot->mRevision);
#else
		DBG_ASSERT(TypeCanFitValue<uint32_t>(index));
		return{ mTableIndex, static_cast<uint32_t>(index), inSlot->mRevision };
#endif
	}

public:
	class Iterator
	{
	protected:
		std::unique_ptr<RtDbTable::IteratorStorage> mAllocatedStorage; // this is just a holder for a newed object. use mStorage instead!
		RtDbTable::IteratorStorage* mStorage;
		uint32 mIdCount;
		uint32 mStartId;
		uint32 mIdOffset;

	public:
		Iterator(RtDbTable* inTable, RtDbTable::IteratorStorage* inStorage = nullptr);
		Iterator(Iterator&& inIter);

		~Iterator();

		// copying/non-ctor moving doesn't make sense due to the way the IteratorStorage class works

#ifdef HOST_WINDOWS
		Iterator(const Iterator&);
		Iterator& operator=(Iterator&&);
		Iterator& operator=(const Iterator&);
#else
		Iterator(const Iterator&) = delete;
		Iterator& operator=(Iterator&&) = delete;
		Iterator& operator=(const Iterator&) = delete;
#endif

		RtId operator * () const;
		RtId* operator -> () const;
		Iterator& operator ++ (void);
        Iterator& operator ++ (int);
		// no post increment because of IteratorStorage
		operator bool () const;
	};

	Event1<const RtId&> OnIdCreated;
	Event1<const RtId&> OnIdDestroyed;
	Event1<const RtId&> OnWatchedIdObjectAccessFault; // called on "watched" Ids during GetObjectForId if the object is null

    Event1<const RtDbTable&> OnTableUnloadingEvent;
    Event1<const RtDbTable&> OnTableUnloadedEvent;
    Event1<const RtDbTable&> OnTableLoadingEvent;
    Event1<const RtDbTable&> OnTableLoadedEvent;

	RtDbTable(uint32 inTableIndex, const TableOptions* inOptions = NULL);
	~RtDbTable();

	void Reset(bool inHardReset); // hard reset puts the table back into a newly initialized state, soft reset just frees RtIds but keeps slot/revision incrementation intact

	inline bool IsIdValid(const RtId& inId) const
	{
		return GetSlotForId(inId, false) != NULL;
	}

	inline uint32 GetTableIndex() const { return mTableIndex; }
	inline const TableOptions* GetTableOptions() const { return &mTableOptions; }

	inline uint32 GetCondemnedSlotCount() const { return mCondemnedSlotCount; }
	inline uint32 GetRtIdCount() const { return mUsedSlotCount; }
	inline bool IsSystemTable() const { return ((mTableIndex & RtId::kSystemTableStart) != 0); }
    bool HasCurrentPackage() const;
	const RtName& GetCurrentPackageName() const;
	void SetCurrentPackageName(const RtName& inName);
	void SetFromLocalFile(bool bFromLocal);// true from net,false from local
	inline bool GetFromLocalFile(){return mFromLocalFile;}

	// convenience functions, mostly just wrap around serialize but takes care of the boilerplate.
	// If inPackageFileName is left blank (the default), the current package file name will be used.
	//PVZ2_CHINESE_START
	bool LoadPackage(const std::string& inPackageFileName = "",const bool isFileEncryption = false);
    bool RefreshPackage(const std::string& inPackageFileName = "",const bool isFileEncryption = false); //c03 add for dlc DB 2015-6-10

	bool ResizeTable(uint32 uIncreaseSlotCount, const std::string& theFilename = "");

	bool SavePackage(RtSerialRtonWriter& rtonWriter, const std::string& inPackageFileName = "", const bool inAsJSON = false, const bool doEncryption = false);
	//PVZ2_CHINESE_END
	// CDH FIXME$$ alloc/retain/release may need MT-safe versions some day, but we'll cross that bridge if/when we get to it

	RtId AllocId(RtObject* inObject = NULL, EObjectDeletionMode inObjectDeletionMode = ODM_Auto, bool inIsStandalone = true, RtId::Uid* inOptExistingUid = NULL);
	bool RetainId(const RtId& inId);
	bool ReleaseId(const RtId& inId);

	uint32 GetRefCountForId(const RtId& inId) const;
	RtObject* GetObjectForId(const RtId& inId) const;
	bool ReplaceObjectForId(const RtId& inId, RtObject* inObject) const;
	bool SetObjectDeletionMode(const RtId& inId, EObjectDeletionMode inMode) const;
	EObjectDeletionMode GetObjectDeletionMode(const RtId& inId) const;
	bool SetObjectIsStandalone(const RtId& inId, bool inIsStandalone) const;
	bool GetObjectIsStandalone(const RtId& inId) const;
	bool SetObjectIsWatched(const RtId& inId, bool inIsWatched) const;
	bool GetObjectIsWatched(const RtId& inId) const;
#ifdef _DEBUG
	bool SetObjectIsRefTracked(const RtId& inId, bool inIsRefTracked) const;
	bool GetObjectIsRefTracked(const RtId& inId) const;
#endif

	RtId::Uid GetUidForId(const RtId& inId) const;
	RtId GetIdForUid(const RtId::Uid& inUid) const;

	RtId GetIdForAlias(const RtName& inAlias) const;
	bool SetIdForAlias(const RtName& inAlias, const RtId& inId); // use empty RtId to remove the given alias; aliases starting with $ are transient and won't be serialized
	
	// Assumes the Rton writer is within an object context.
	void SerializeAllAliasesToRton(RtSerialRtonWriter& inRtonWriter, const std::string& inArrayKeyName);

	// Assumes the Rton writer is within an object context
	// Returns false if inAliasesForId is not in the current table.
	bool SerializeRtIdAliasesToRton(RtSerialRtonWriter& inRtonWriter, const RtId& inAliasesForId, const std::string& inArrayKeyName);

	
	void RunDeferredDeletions();

	inline IteratorStorage* GetSharedIteratorStorage() { return &mIteratorStorage; }
	void Iterate(const IterateFilterDelegateType& inFilterDelegate, const IterateActionDelegateType& inActionDelegate, IteratorStorage* inIteratorStorage = NULL);
	void Iterate(const IterateActionDelegateType& inActionDelegate, IteratorStorage* inIteratorStorage = NULL);

	void Sort(const SortDelegateType& inSortDelegate);

	bool SerializeTableFirstPass(RtSerialRtonSync* inSync, std::vector<RtObject*>& inoutObjectList, const std::string& fileName = "");
	bool SerializeTableSecondPass(RtSerialRtonSync* inSync, std::vector<RtObject*>& inoutObjectList);
	
	bool SerializeTable(RtSerialRtonSync* inSync, const std::string& fileName = "");

	bool WriteRtonRtIdList(RtSerialBuffer* inBuffer) const;

	// inRtonWriter must already be in an Object context.
	// This method will add rton keys and values for information 
	// about the table (i.e. table_index, display_name, table_name, 
	// current_package)
	void WriteTableRtonKeys(RtSerialRtonWriter& inRtonWriter) const;
	
	void DebugPrintTableInfo();
	
private:
	std::string MakeFileNameFromPackageNameOrFileName(const std::string& inPackageNameOrFileName);
	std::string MakePackageNameFromPackageNameOrFileName(const std::string& inPackageNameOrFileName);
	
	//PVZ2_CHINESE_START
	//raoyj
	bool saveToFile(RtSerialRtonWriter& rtonWriter, const std::string& fileName, const bool inAsJSON, const bool doEncryption = false);
	//PVZ2_CHINESE_END

#if SEXY_IS_LIVELINK_ENABLED
	static void SendLiveLinkOnRtIdCreatedEvent(const RtId& inRtIdCreated);
	static void SendLiveLinkOnRtIdDestroyedEvent(const RtId& inRtIdDestoryed);
	static void SendLiveLinkOnAliasAddedEvent(const std::string& inAlias, const RtId& inRtId);
	static void SendLiveLinkOnAliasRemovedEvent(const std::string& inAlias, const RtId& inRtId);
#endif // SEXY_IS_LIVELINK_ENABLED
};

/*
	RtDb
*/
class RtDb
{
public:
	enum ESystemTable
	{
		// all system tables start at RtId::kSystemTableStart
		SYSTEMTABLE_ReflectionSymbols			= RtId::kSystemTableStart + 1,
		SYSTEMTABLE_RtClasses					= RtId::kSystemTableStart + 2,

		SYSTEMTABLE_ResourceGroups				= RtId::kSystemTableStart + 3,
		SYSTEMTABLE_ResourceInfo				= RtId::kSystemTableStart + 4,
		SYSTEMTABLE_ResourceInfoHidden			= RtId::kSystemTableStart + 5,
		SYSTEMTABLE_ResourceInstances			= RtId::kSystemTableStart + 6,
		SYSTEMTABLE_ResourceInstancesHidden		= RtId::kSystemTableStart + 7,
		SYSTEMTABLE_ResourceInstancesUngrouped	= RtId::kSystemTableStart + 8,

		SYSTEMTABLE_ApplicationProxies			= RtId::kSystemTableStart + 9,
	};

private:
	typedef std::vector<RtDbTable*> TableVector;
	TableVector mSystemTables;
	TableVector mUserTables;
	uint32 mCreationTimeStamp; // low 32 bits of time_t that the RtDb was created, used for RtOfflineId
	
	typedef std::unordered_map<uint32, uint32> NameToTableIndexMap;
	NameToTableIndexMap mNameToTableIndexMap;

	friend class RtDbTable;

	bool InternalRemoveTable(uint32 inTableIndex);

private:
	static RtDb* sRtDb; // private pointer to the singleton of GetDb(); only used for the debugger.

public:
	static RtDb* GetDb();

	RtDb();
	~RtDb();

	inline uint32 GetCreationTimeStamp() const { return mCreationTimeStamp; }

	RtDbTable* GetTable(uint32 inTableIndex) const;
	RtDbTable* GetTable(const RtName& inName) const;

	RtDbTable* CreateTable(uint32 inTableIndex, const RtDbTable::TableOptions* inOptions = NULL);

	RtId ResolveNamedId(const RtId& inId) const;

	inline bool IsIdValid(const RtId& inId) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return false;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->IsIdValid(id) : false;
	}

	inline RtId AllocId(uint32 inTableIndex, RtObject* inObject = NULL, RtDbTable::EObjectDeletionMode inObjectDeletionMode = RtDbTable::ODM_Auto, bool inIsStandalone = true, RtId::Uid* inOptExistingUid = NULL) const
	{
		RtDbTable* table = GetTable(inTableIndex);
		return table ? table->AllocId(inObject, inObjectDeletionMode, inIsStandalone, inOptExistingUid) : RtId();
	}
	inline bool RetainId(const RtId& inId) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return false;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->RetainId(id) : false;
	}
	inline bool ReleaseId(const RtId& inId) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return false;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->ReleaseId(id) : false;
	}
	inline uint32 GetRefCountForId(const RtId& inId) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return 0;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->GetRefCountForId(id) : 0;
	}
	inline RtObject* GetObjectForId(const RtId& inId) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return NULL;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->GetObjectForId(id) : NULL;
	}
	inline bool ReplaceObjectForId(const RtId& inId, RtObject* inObject) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return false;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->ReplaceObjectForId(id, inObject) : false;
	}
	inline bool SetObjectDeletionMode(const RtId& inId, RtDbTable::EObjectDeletionMode inMode) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return false;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->SetObjectDeletionMode(id, inMode) : false;
	}
	inline RtDbTable::EObjectDeletionMode GetObjectDeletionMode(const RtId& inId) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return RtDbTable::ODM_Never;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->GetObjectDeletionMode(id) : RtDbTable::ODM_Never;
	}
	inline bool SetObjectIsStandalone(const RtId& inId, bool inIsStandalone) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return false;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->SetObjectIsStandalone(id, inIsStandalone) : false;
	}
	bool GetObjectIsStandalone(const RtId& inId) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return false;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->GetObjectIsStandalone(id) : false;
	}
	bool SetObjectIsWatched(const RtId& inId, bool inIsWatched) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return false;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->SetObjectIsWatched(id, inIsWatched) : false;
	}
	bool GetObjectIsWatched(const RtId& inId) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return false;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->GetObjectIsWatched(id) : false;
	}
#ifdef _DEBUG
	bool SetObjectIsRefTracked(const RtId& inId, bool inIsRefTracked) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return false;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->SetObjectIsRefTracked(id, inIsRefTracked) : false;
	}
	bool GetObjectIsRefTracked(const RtId& inId) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return false;
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->GetObjectIsRefTracked(id) : false;
	}
#endif
	inline RtId::Uid GetUidForId(const RtId& inId) const
	{
		RtId id = ResolveNamedId(inId);
		if (!id)
			return RtId::Uid();
		RtDbTable* table = GetTable(id.GetTableIndex());
		return table ? table->GetUidForId(id) : RtId::Uid();
	}
	
	void RunDeferredDeletions(uint32 inTableIndex = 0xffffffff) const;
	
	bool LoadPackageFromFile(uint32 inTableIndex, const std::string& inFilename);
	bool SavePackageToFile(uint32 inTableIndex, const std::string& inFilename, bool inAsJson = false);
	
	typedef std::pair<uint32, std::string> TableFilenamePair;
	bool LoadPackageGroupFromFiles(std::vector<TableFilenamePair>& inPackageGroup, uint32* outTotalBytes = NULL);
	bool SavePackageGroupToFiles(std::vector<TableFilenamePair>& inPackageGroup, bool inAsJson = false, uint32* outTotalBytes = NULL);
	
	bool WriteRtonTableSummary(RtSerialBuffer* inBuffer) const;

    // Adding delegates to this events will cause the delegate to be called 
    // anytime any table's load status changes
    Event1<const RtDbTable&> OnTableUnloadingEvent;
    Event1<const RtDbTable&> OnTableUnloadedEvent;
    Event1<const RtDbTable&> OnTableLoadingEvent;
    Event1<const RtDbTable&> OnTableLoadedEvent;
};

/*
	RtStrongPtr
	RtMixedPtr
	RtWeakPtr
*/
class RtStrongPtrBase
{
protected:
	RtId mId;

public:
	inline void SetObject(uint32 inTableIndex, RtObject* inObject, RtDbTable::EObjectDeletionMode inObjectDeletionMode = RtDbTable::ODM_Auto)
	{
		RtDb* db = RtDb::GetDb();
		if (mId)
		{
			RtObject* obj = db->GetObjectForId(mId);
			if (obj && (obj == inObject))
				return;
			db->ReleaseId(mId);
			mId = RtId();
		}
		if (inObject)
		{
			// If you alloc a new Id using an RtStrongPtr, it's non-standalone because the RtStrongPtr is the only strong ref
			// on the Id.  If you later want to switch to standalone, call RetainId on it followed by SetObjectIsStandalone.
			mId = db->AllocId(inTableIndex, inObject, inObjectDeletionMode, false);
		}
	}
	inline void SetId(const RtId& inId)
	{
		RtDb* db = RtDb::GetDb();
		if (inId == mId)
			return;
		if (mId)
			db->ReleaseId(mId);
		mId = inId;
		if (mId)
			db->RetainId(mId);
	}
	inline bool Possess()
	{
		if (!mId)
			return false;
		bool isStandalone = RtDb::GetDb()->GetObjectIsStandalone(mId);
		if (!isStandalone)
			return false; // only standalone objects can be possessed
		
		// ok to possess; remove the standalone ref
		RtDb::GetDb()->SetObjectIsStandalone(mId, false);
		RtDb::GetDb()->ReleaseId(mId);

		return true;
	}

	inline RtStrongPtrBase() {} // ID will be zero (null) by default
	inline RtStrongPtrBase(const RtStrongPtrBase& inPtr) { SetId(inPtr.mId); }
	inline RtStrongPtrBase(uint32 inTableIndex, RtObject* inObject, RtDbTable::EObjectDeletionMode inObjectDeletionMode = RtDbTable::ODM_Auto)
	{
		SetObject(inTableIndex, inObject, inObjectDeletionMode);
	}
	inline RtStrongPtrBase(const RtId& inId) { SetId(inId); }
	inline ~RtStrongPtrBase() { SetObject(0, NULL); }

	inline RtStrongPtrBase& operator = (const RtStrongPtrBase& inPtr) { SetId(inPtr.mId); return *this; }
	inline RtStrongPtrBase& operator = (const RtId& inId) { SetId(inId); return *this; }

	inline RtId GetId() const { return mId; }
	inline bool IsValid() const { return mId ? (RtDb::GetDb()->GetObjectForId(mId) != NULL) : false; }

	inline RtId& GetIdRef() { return mId; }
	inline const RtId& GetIdRef() const { return mId; }

	inline RtObject* GetObject() const { return mId ? RtDb::GetDb()->GetObjectForId(mId) : NULL; }

	inline bool AutoDelete() { return mId ? RtDb::GetDb()->SetObjectDeletionMode(mId, RtDbTable::ODM_Auto) : false; }
	inline bool DeferDelete() { return mId ? RtDb::GetDb()->SetObjectDeletionMode(mId, RtDbTable::ODM_Deferred) : false; }
	inline bool NeverDelete() { return mId ? RtDb::GetDb()->SetObjectDeletionMode(mId, RtDbTable::ODM_Never) : false; }

	inline bool operator == (const RtStrongPtrBase& inOther) const { return mId == inOther.mId; }
	inline bool operator != (const RtStrongPtrBase& inOther) const { return mId != inOther.mId; }
	inline bool operator < (const RtStrongPtrBase& inOther) const { return mId.GetValue() < inOther.mId.GetValue(); } // for sorting in STL containers
};

class RtMixedPtrBase
{
protected:
	RtId mId;
	bool mIsStrong;

public:
	inline void SetObject(uint32 inTableIndex, RtObject* inObject, RtDbTable::EObjectDeletionMode inObjectDeletionMode = RtDbTable::ODM_Auto)
	{
		RtDb* db = RtDb::GetDb();
		if (mId)
		{
			if (mIsStrong)
			{
				RtObject* obj = db->GetObjectForId(mId);
				if (obj && (obj == inObject))
					return;
				db->ReleaseId(mId);
				mIsStrong = false;
			}
			mId = RtId();
		}
		if (inObject)
		{
			mId = db->AllocId(inTableIndex, inObject, inObjectDeletionMode, false);
			mIsStrong = true;
		}
	}
	inline void SetId(const RtId& inId, bool inIsStrong)
	{
		RtDb* db = RtDb::GetDb();
		if (inIsStrong && inId)
			db->RetainId(inId);
		if (mIsStrong && mId)
			db->ReleaseId(mId);
		mId = inId;
		mIsStrong = inIsStrong;
	}
	inline bool Possess()
	{
		if (!mIsStrong || !mId)
			return false; // only strong refs can possess
		bool isStandalone = RtDb::GetDb()->GetObjectIsStandalone(mId);
		if (!isStandalone)
			return false; // only standalone objects can be possessed
		
		// ok to possess; remove the standalone ref
		RtDb::GetDb()->SetObjectIsStandalone(mId, false);
		RtDb::GetDb()->ReleaseId(mId);

		return true;
	}

	inline RtMixedPtrBase() : mIsStrong(false) {} // ID will be zero (null) by default
	inline RtMixedPtrBase(const RtMixedPtrBase& inPtr) : mIsStrong(false) { SetId(inPtr.mId, inPtr.mIsStrong); }
	inline RtMixedPtrBase(uint32 inTableIndex, RtObject* inObject, RtDbTable::EObjectDeletionMode inObjectDeletionMode = RtDbTable::ODM_Auto)
	{
		SetObject(inTableIndex, inObject, inObjectDeletionMode);
	}
	inline RtMixedPtrBase(const RtId& inId, bool inIsStrong) { SetId(inId, inIsStrong); }
	inline ~RtMixedPtrBase() { SetObject(0, NULL); }

	inline RtMixedPtrBase& operator = (const RtMixedPtrBase& inPtr) { SetId(inPtr.mId, inPtr.mIsStrong); return *this; }

	inline bool GetIsStrong() const { return mIsStrong; }
	inline void SetIsStrong(bool inIsStrong) { if (mIsStrong != inIsStrong) { SetId(mId, inIsStrong); } }

	inline RtId GetId() const { return mId; }
	inline bool IsValid() const { return mId ? (RtDb::GetDb()->GetObjectForId(mId) != NULL) : false; }

	inline RtId& GetIdRef() { return mId; }
	inline const RtId& GetIdRef() const { return mId; }

	inline RtObject* GetObject() const { return mId ? RtDb::GetDb()->GetObjectForId(mId) : NULL; }

	inline bool AutoDelete() { return mId && mIsStrong ? RtDb::GetDb()->SetObjectDeletionMode(mId, RtDbTable::ODM_Auto) : false; }
	inline bool DeferDelete() { return mId && mIsStrong ? RtDb::GetDb()->SetObjectDeletionMode(mId, RtDbTable::ODM_Deferred) : false; }
	inline bool NeverDelete() { return mId && mIsStrong ? RtDb::GetDb()->SetObjectDeletionMode(mId, RtDbTable::ODM_Never) : false; }

	inline bool operator == (const RtMixedPtrBase& inOther) const { return mId == inOther.mId; }
	inline bool operator != (const RtMixedPtrBase& inOther) const { return mId != inOther.mId; }
	inline bool operator < (const RtMixedPtrBase& inOther) const { return mId.GetValue() < inOther.mId.GetValue(); } // for sorting in STL containers
};

class RtWeakPtrBase
{
protected:
	RtId mId;

public:
	inline void SetId(const RtId& inId) { mId = inId; }
    
    inline RtWeakPtrBase() {} // ID will be zero (null) by default
	inline RtWeakPtrBase(const RtWeakPtrBase& inPtr) { SetId(inPtr.mId); }
	inline RtWeakPtrBase(const RtId& inId) { SetId(inId); }
	inline ~RtWeakPtrBase() {}

	inline RtWeakPtrBase& operator = (const RtWeakPtrBase& inPtr) { SetId(inPtr.mId); return *this; }
	inline RtWeakPtrBase& operator = (const RtId& inId) { SetId(inId); return *this; }

	inline RtId GetId() const { return mId; }
	inline bool IsValid() const { return mId ? (RtDb::GetDb()->GetObjectForId(mId) != NULL) : false; }
    inline bool NotValid() const { return !IsValid(); }

	inline RtId& GetIdRef() { return mId; }
	inline const RtId& GetIdRef() const { return mId; }

	inline RtObject* GetObject() const { return mId ? RtDb::GetDb()->GetObjectForId(mId) : NULL; }

	inline bool operator == (const RtWeakPtrBase& inOther) { return mId == inOther.mId; }
	inline bool operator != (const RtWeakPtrBase& inOther) { return mId != inOther.mId; }
	inline bool operator < (const RtWeakPtrBase& inOther) { return mId.GetValue() < inOther.mId.GetValue(); } // for sorting in STL containers
	inline bool operator == (const RtWeakPtrBase& inOther) const { return mId == inOther.GetId(); }
	inline bool operator != (const RtWeakPtrBase& inOther) const { return mId != inOther.GetId(); }

    // For default std::map comparator (less) support
	inline bool operator < (const RtWeakPtrBase& inOther) const { return mId.GetValue() < inOther.GetId().GetValue(); }

	inline void ClearId() { mId = RtId(0); }
};

template <class T> class RtStrongPtr
: public RtStrongPtrBase
{
public:
	inline RtStrongPtr() {} // ID will be zero (null) by default
	inline RtStrongPtr(const RtStrongPtrBase& inPtr) : RtStrongPtrBase(inPtr) {}
	inline RtStrongPtr(const RtMixedPtrBase& inPtr) : RtStrongPtrBase(inPtr.GetId()) {}
	inline RtStrongPtr(const RtWeakPtrBase& inPtr) : RtStrongPtrBase(inPtr.GetId()) {}
	inline RtStrongPtr(uint32 inTableIndex, RtObject* inObject, RtDbTable::EObjectDeletionMode inObjectDeletionMode = RtDbTable::ODM_Auto)
		: RtStrongPtrBase(inTableIndex, inObject, inObjectDeletionMode) {}
	inline RtStrongPtr(const RtId& inId) : RtStrongPtrBase(inId) {}
	inline ~RtStrongPtr() {}
    
	inline operator bool () const { return IsValid(); }
    inline bool operator ! () const { return !IsValid(); }
    
	inline RtStrongPtr<T>& operator = (const RtStrongPtrBase& inPtr) { SetId(inPtr.GetId()); return *this; }
	inline RtStrongPtr<T>& operator = (const RtMixedPtrBase& inPtr) { SetId(inPtr.GetId()); return *this; }
	inline RtStrongPtr<T>& operator = (const RtWeakPtrBase& inPtr) { SetId(inPtr.GetId()); return *this; }
	inline RtStrongPtr<T>& operator = (const RtId& inId) { SetId(inId); return *this; }
	
	inline operator T* () const { return RtDb::GetDb()->GetObjectForId(mId)->template Cast<T>(); }
	inline T* operator -> () const { return RtDb::GetDb()->GetObjectForId(mId)->template Cast<T>(); }
	
	inline operator RtId() const { return GetId(); }

};

template <class T> class RtMixedPtr
: public RtMixedPtrBase
{
public:
	inline RtMixedPtr() {} // ID will be zero (null) by default
	inline RtMixedPtr(const RtMixedPtrBase& inPtr) : RtMixedPtrBase(inPtr) {}
	inline RtMixedPtr(const RtStrongPtrBase& inPtr) : RtMixedPtrBase(inPtr.GetId(), true) {}
	inline RtMixedPtr(const RtWeakPtrBase& inPtr) : RtMixedPtrBase(inPtr.GetId(), false) {}
	inline RtMixedPtr(uint32 inTableIndex, RtObject* inObject, RtDbTable::EObjectDeletionMode inObjectDeletionMode = RtDbTable::ODM_Auto)
		: RtMixedPtrBase(inTableIndex, inObject, inObjectDeletionMode) {}
	inline RtMixedPtr(const RtId& inId, bool inIsStrong) : RtMixedPtrBase(inId, inIsStrong) {}
	inline ~RtMixedPtr() {}
    
	inline RtMixedPtr<T>& operator = (const RtMixedPtrBase& inPtr) { SetId(inPtr.GetId(), inPtr.GetIsStrong()); return *this; }
	inline RtMixedPtr<T>& operator = (const RtStrongPtrBase& inPtr) { SetId(inPtr.GetId(), true); return *this; }
	inline RtMixedPtr<T>& operator = (const RtWeakPtrBase& inPtr) { SetId(inPtr.GetId(), false); return *this; }
	
	inline operator T* () const { return RtDb::GetDb()->GetObjectForId(mId)->template Cast<T>(); }
	inline T* operator -> () const { return RtDb::GetDb()->GetObjectForId(mId)->template Cast<T>(); }
	
	inline operator RtId() const { return GetId(); }
    
	inline bool operator ! () const { return !IsValid(); }
};

#ifndef RELEASEFINAL
#define VerifyRTType() VerifyIdType()
#else
#define VerifyRTType()
#endif

template <class T> class RtWeakPtr
: public RtWeakPtrBase
{
public:
	inline RtWeakPtr(std::nullptr_t inPtr = nullptr) {} // ID will be zero (null) by default
	inline RtWeakPtr(const RtWeakPtrBase& inPtr) : RtWeakPtrBase(inPtr) {}
	inline RtWeakPtr(const RtMixedPtrBase& inPtr) : RtWeakPtrBase(inPtr.GetId()) {}
	inline RtWeakPtr(const RtStrongPtrBase& inPtr) : RtWeakPtrBase(inPtr.GetId()) {}
	inline RtWeakPtr(const RtId& inId) : RtWeakPtrBase(inId) {}
	inline ~RtWeakPtr() {}
    
    inline operator bool () const { return IsValid(); }
	inline bool operator ! () const { return !IsValid(); }

	inline RtWeakPtr<T>& operator = (const RtWeakPtrBase& inPtr) { SetId(inPtr.GetId()); return *this; }
	inline RtWeakPtr<T>& operator = (const RtMixedPtrBase& inPtr) { SetId(inPtr.GetId()); return *this; }
	inline RtWeakPtr<T>& operator = (const RtStrongPtrBase& inPtr) { SetId(inPtr.GetId()); return *this; }
	inline RtWeakPtr<T>& operator = (const RtId& inId) { SetId(inId); return *this; }
	
    inline T* Get() const
    {
        VerifyRTType();
        return (T*)RtDb::GetDb()->GetObjectForId(mId);
    }
    
    inline T& operator*() const
    {
        return *Get();
    }
    
    inline T* operator -> () const
    {
        VerifyRTType();
        return (T*)RtDb::GetDb()->GetObjectForId(mId);
    }
    
    inline operator T* () const
    {
        return Get();
    }
    
	inline T* GetPtr() const { return RtDb::GetDb()->GetObjectForId(mId)->template Cast<T>(); } //add for lua get ojbect pointer 2015-4-24
	inline operator RtId() const { return GetId(); }

#ifndef RELEASEFINAL
    void VerifyIdType() const
    {
        const RtObject *object = RtDb::GetDb()->GetObjectForId(mId);
        if (object)
        {
            object->template CastChecked<T>();
        }
    }
#endif
};

#undef VerifyRTType


template <class T, int TableIndex> class RtEmbeddedPtr
: public RtWeakPtr<T>
{
};


/*
	RtIdProtocol
*/
class RtIdProtocol
: public RtProtocol
{
public:
	typedef Delegate1wRet<RtId, RtObject*> GetRtIdDelegateType;

protected:
	GetRtIdDelegateType mDelegate;

public:
	RT_CLASS_DEFINE(RtIdProtocol, RtProtocol, RtProtocolClass) {}

    GetRtIdDelegateType GetDelegate();
    void SetDelegate(const GetRtIdDelegateType& inDelegate);
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
//**    END HEADER RTDB.H
//**
//****************************************************************************
#endif // __RTDB_H__
