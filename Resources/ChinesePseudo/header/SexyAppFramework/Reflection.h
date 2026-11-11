#pragma once
#ifndef __REFLECTION_H__
#define __REFLECTION_H__

//****************************************************************************
//**
//**  File     :  REFLECTION.H
//**  Summary  :  Header - Reflection API
//**
//----------------------------------------------------------------------------
//**       $Id:$ 
//** $DateTime:$ 
//**   $Author:$ 
//**   $Change:$ 
//****************************************************************************

#ifdef SUPPORT_REFLECTION

#include "RtDb.h"
#include "RtObject.h"
#include "RtDelegate.h"
#include "RtSerial.h"

#include "ReflectionTags.h"

//============================================================================
//    HEADERS
//============================================================================
#include <string>
#include <vector>
#include <map>

#ifdef _MSC_VER
#include <typeinfo.h>
#else
#include <typeinfo>
#endif



using namespace Sexy;

#define RT_COMMA ,

// external forward declarations
namespace Sexy
{
	class RtSerialBuffer;
	class RtSerialRtonReader;
	class RtSerialRtonWriter;
	class RtSerialRtonSync;
	struct RtSerialRtonKey;
}

namespace Reflection {

//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
typedef RtInvokeVariant CRefInvokeVariant;

//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
// forward declarations
class CRefSymbolDb;
class IRefSymbolBuilder;
class CRefPdbSymbolBuilder;
class IRefManualSymbolBuilder;
class CRefManualSymbolBuilder;
class CRefAttributeVariant;

class RSymbol; // basic symbol - all reflection types that start with "R" are derived from RSymbol
	class RType; // type symbol
		class RSimpleType; // simple type (ints, floats, etc)
		class RReferenceType; // reference types (pointers, ampersand references, arrays)
		class RFunctionType; // function types (with return value, argument types etc)
		class RCustomType; // special types with custom handling (such as strings and other low-level template classes)
		class RNamedType; // abstract named type
			class RUnknownNamedType; // placeholder unknown named type (not a recognized class or enum)
			class RClass; // class type (with fields, methods, properties, etc)
			class RClassRef; // class reference (one level of indirection; necessary for the type system)
			class REnum; // enum type (with members)
			class REnumRef; // enum reference (one level of indirection; necessary for the type system)
	class RClassMember; // class member
		class RField; // field (data)
		class RProperty; // property (pseudo-data accessed via get/set methods)
		class RMethod; // method (function)
		class REvent; // C#-style event (has elements of both fields and methods)
		class RAncestor; // ancestor (base class)
	class REnumMember; // enum member
	class RAttribute; // general key-value attribute

/*
	CRefNamedSymbolCollection
*/
class CRefNamedSymbolCollection
{
protected:
	typedef std::vector<RSymbol*> DSymbolVector;
	typedef std::map<std::string, RSymbol*> DNameToSymbolMap;
	
	DSymbolVector mSymbols;
	DNameToSymbolMap mNameToSymbolMap;
	bool mNoDeleteSymbols;

public:
	CRefNamedSymbolCollection();
	~CRefNamedSymbolCollection();

	uint32 GetCount() const
	{
		return (uint32)mSymbols.size();
	}

	void InternalAddSymbol(const std::string& inName, RSymbol* inSymbol)
	{
		mSymbols.push_back(inSymbol);
		if (!inName.empty())
			mNameToSymbolMap[inName] = inSymbol;
	}
	inline void SetNoDeleteSymbols(bool inNoDeleteSymbols)
	{
		mNoDeleteSymbols = inNoDeleteSymbols;
	}
};

/*
	TRefNamedSymbolCollection (generalized form; specializations exist below)
*/
template <class T> class TRefNamedSymbolCollection
: public CRefNamedSymbolCollection
{
public:
	T* GetIndexed(uint32 inIndex) const
	{
		return (T*)mSymbols[inIndex];
	}
	T* GetNamed(const std::string& inName) const
	{
		DNameToSymbolMap::const_iterator it = mNameToSymbolMap.find(inName);
		if (it != mNameToSymbolMap.end())
			return (T*)it->second;
		return 0;
	}
	bool AddSymbol(const std::string& inName, T* inSymbol)
	{
		if (!inName.empty() && GetNamed(inName))
			return false;
		InternalAddSymbol(inName, inSymbol);
		return true;
	}
};

template <> class TRefNamedSymbolCollection<RAttribute>
: public CRefNamedSymbolCollection
{
public:
	RAttribute* GetIndexed(uint32 inIndex) const
	{
		return (RAttribute*)mSymbols[inIndex];
	}
	RAttribute* GetNamed(const std::string& inName) const
	{
		DNameToSymbolMap::const_iterator it = mNameToSymbolMap.find(inName);
		if (it != mNameToSymbolMap.end())
			return (RAttribute*)it->second;
		return 0;
	}
	bool AddSymbol(const std::string& inName, RAttribute* inSymbol)
	{
		if (!inName.empty() && GetNamed(inName))
			return false;
		InternalAddSymbol(inName, (RSymbol*)inSymbol);
		return true;
	}

	CRefAttributeVariant GetValueForNamed(const std::string& inName, const CRefAttributeVariant& inDefaultValue) const;
};

/*
	RSymbol
*/
class RSymbol
: public RtObject
{
public:
	RT_CLASS_DEFINE(Reflection::RSymbol, RtObject, RtClass);

protected:
	RtId mRtId;
	TRefNamedSymbolCollection<RAttribute> mSymAttributes;

	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;

	union UTypePtr
	{
		RType* mPtr; // after fixup
		uint32 mHandle; // before fixup
	};

public:
	RSymbol();
	virtual ~RSymbol();

	inline const RtId& GetRtId() { return mRtId; }

	inline const TRefNamedSymbolCollection<RAttribute>* GetAttributes() const { return &mSymAttributes; }
	inline TRefNamedSymbolCollection<RAttribute>* GetMutableAttributes() { return &mSymAttributes; }
};

/*
	RType
*/
class RType
: public RSymbol
{
public:
	RT_CLASS_DEFINE_ABSTRACT(Reflection::RType, Reflection::RSymbol, RtClass) {}

public:
	enum ETypeCategory
	{
		TC_None=0,

		TC_Simple			= 1,
		TC_Reference		= 2,
		TC_Function			= 3,
		TC_Custom			= 4,

		TC_Named_MASK		= 0x1F0,
		TC_Named_Unknown	= 0x010,
		TC_Named_Class		= 0x020,
		TC_Named_ClassRef	= 0x040,
		TC_Named_Enum		= 0x080,
		TC_Named_EnumRef	= 0x100,
	};

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	enum ETypeFlags
	{
		TF_Const		= (1 << 0),
		
		TF_DisputedSize = (1 << 8),
	};

	uint32 mTypeDbIndex;
	uint32 mTypeFlags;
	uint32 mTypeSize;
	uint32 mTypeThisAdjust;

	RType() {}

public:
	virtual ETypeCategory GetTypeCategory() const = 0;
	virtual bool TypeEquals(RType* inType, bool inCheckConst=true, bool inExactMatch=false) const = 0;
	virtual std::string TypeToString(bool inCheckConst=true) const = 0;

	inline uint32 GetSize() const { return mTypeSize; }
	inline uint32 GetThisAdjust() const { return mTypeThisAdjust; }
	inline bool GetIsConst() const { return (mTypeFlags & TF_Const) != 0; }
	inline bool GetIsDisputedSize() const { return (mTypeFlags & TF_DisputedSize) != 0; }

	virtual std::string InstanceToString(const void* inInstancePtr) const
	{
		return "?";
	}
	virtual bool InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const;
	virtual bool InstanceNavigatePath(void*& ioInstancePtr, std::string& ioPath, RType*& outType) const { return false; }
};

/*
	RSimpleType
*/
class RSimpleType
: public RType
{
public:
	RT_CLASS_DEFINE(Reflection::RSimpleType, Reflection::RType, RtClass) {}

public:
	enum ESimpleTypeCategory
	{
		STC_None=0, // unknown/invalid type
		
		STC_Ellipsis, // va_arg ellipsis (only used as last arg to a function)
		
		STC_Void, // void
		STC_Bool, // bool
		STC_AChar, // char (8-bit ansi character)
		STC_WChar, // wchar_t (16-bit wide character)
		STC_SInt, // signed byte/word/dword/qword (check size)
		STC_UInt, // unsigned byte/word/dword/qword (check size)
		STC_Float, // float/double (check size)
		STC_HResult, // HRESULT (long)
	};
    
    typedef ESimpleTypeCategory SubTypeCategory;

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	ESimpleTypeCategory mSimpleTypeCategory;

public:
    static ETypeCategory StaticGetTypeCategory() { return TC_Simple; }
	virtual ETypeCategory GetTypeCategory() const override { return StaticGetTypeCategory(); }
    
	virtual bool TypeEquals(RType* inType, bool inCheckConst=true, bool inExactMatch=false) const override;
	virtual std::string TypeToString(bool inCheckConst=true) const override;

	inline ESimpleTypeCategory GetSimpleTypeCategory() const { return mSimpleTypeCategory; }
    inline SubTypeCategory GetSubTypeCategory() const { return GetSimpleTypeCategory(); }

	std::string InstanceToString(const void* inInstancePtr, bool inUseHex) const;

	virtual std::string InstanceToString(const void* inInstancePtr) const override
	{
		return InstanceToString(inInstancePtr, false);
	}

	virtual bool InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const override;
};

/*
	RReferenceType
*/
class RReferenceType
: public RType
{
public:
	RT_CLASS_DEFINE(Reflection::RReferenceType, Reflection::RType, RtClass) {}

public:
	enum EReferenceTypeCategory
	{
		RTC_Ampersand,
		RTC_Pointer,
		RTC_Array,
	};
    
    typedef EReferenceTypeCategory SubTypeCategory;

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	EReferenceTypeCategory mReferenceTypeCategory;
	UTypePtr mInnerType;
	uint32 mArrayItemCount;

public:
    static ETypeCategory StaticGetTypeCategory() { return TC_Reference; }
	virtual ETypeCategory GetTypeCategory() const override { return StaticGetTypeCategory(); }

	virtual bool TypeEquals(RType* inType, bool inCheckConst=true, bool inExactMatch=false) const override;
	virtual std::string TypeToString(bool inCheckConst=true) const override;

	inline EReferenceTypeCategory GetReferenceTypeCategory() const { return mReferenceTypeCategory; }
    inline SubTypeCategory GetSubTypeCategory() const { return GetReferenceTypeCategory(); }
	inline RType* GetInnerType() const { return mInnerType.mPtr; }
	inline uint32 GetArrayItemCount() const { return mArrayItemCount; }
    void* GetArrayElement(const void* inInstancePtr, int32 inElementIndex) const;

	std::string InstanceToString(const void* inInstancePtr, uint32 inArrayStart, uint32 inArrayCount) const;

	virtual std::string InstanceToString(const void* inInstancePtr) const override
	{
		return InstanceToString(inInstancePtr, 0, 4);
	}

	virtual bool InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const override;
	virtual bool InstanceNavigatePath(void*& ioInstancePtr, std::string& ioPath, RType*& outType) const override;
};

/*
	RFunctionType
*/
class RFunctionType
: public RType
{
public:
	RT_CLASS_DEFINE(Reflection::RFunctionType, Reflection::RType, RtClass) {}

public:
	enum ECallType
	{
		CT_None=0,

		CT_ThisCall,
		CT_Cdecl,
		CT_StdCall,
		CT_FastCall,
		CT_SysCall,

		CT_Delegate, // method delegate via manual builder, calltype is irrelevant
	};

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	ECallType mCallType;
	UTypePtr mThisType;
	UTypePtr mReturnType;
	std::vector<UTypePtr> mArgTypes;

public:
    static ETypeCategory StaticGetTypeCategory() { return TC_Function; }
	virtual ETypeCategory GetTypeCategory() const override { return StaticGetTypeCategory(); }

	virtual bool TypeEquals(RType* inType, bool inCheckConst=true, bool inExactMatch=false) const override;
	virtual std::string TypeToString(bool inCheckConst=true) const override;

	inline ECallType GetCallType() const { return mCallType; }
	inline RType* GetThisType() const { return mThisType.mPtr; }
	inline RType* GetReturnType() const { return mReturnType.mPtr; }
	inline uint32 GetArgTypeCount() const { return (uint32)mArgTypes.size(); }
	inline RType* GetArgTypeIndexed(uint32 inIndex) const { return mArgTypes[inIndex].mPtr; }
};

/*
	RCustomType
*/
class RCustomType
: public RType
{
public:
	RT_CLASS_DEFINE(Reflection::RCustomType, Reflection::RType, RtClass) {}

public:
	enum ECustomTypeCategory
	{
		// strings
		CTC_StdString, // inner type is char
		CTC_StdWString, // inner type is wchar_t

		// containers
		CTC_StdVector, // inner type should never be null; implies std::vector<InnerType>

		// RtIds
		CTC_WeakRtId, // inner type may be null (plain RtId), or if non-null implies RtWeakPtr<InnerType>
		CTC_StrongRtId, // inner type may be null (plain RtId), or if non-null implies RtStrongPtr<InnerType>

		// Types requiring an AirMarshal update to fully support
        // These must come after everything else to maintain parity with AirMarshal's list of custom types
        CTC_StdDeque,
        
        CTC_StdMap,
        CTC_StdSet,
        
        CTC_EmbeddedObject,

		CTC_COUNT
	};
    
    typedef ECustomTypeCategory SubTypeCategory;
    
    class IStdManipulator
    {
    public:
        virtual ~IStdManipulator() {}
        virtual bool InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey, RType* innerType) const = 0;
        virtual uint32 GetCount(const void* inInstancePtr) const = 0;
    };
    
    template <class T> class TStdVectorManipulator : public IStdManipulator
    {
    public:
        virtual uint32 GetCount(const void* inVector) const
        {
            std::vector<T>* v = (std::vector<T>*)inVector;
            return (uint32)v->size();
        }
        
        virtual bool InstanceRtonSync(void* inVector, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey, RType* innerType) const
        {
            if (inSync->IsWriting())
            {
                RtSerialRtonWriter* writer = inSync->GetWriter();
                std::vector<T>* v = (std::vector<T>*)inVector;
                writer->BeginArray(inKey, (uint32)v->size());
                for (auto &item : *v)
                {
                    innerType->InstanceRtonSync(&item, inSync, NULL);
                }
                writer->EndArray();
                return true;
            }
            else
            {
                RtSerialRtonReader* reader = inSync->GetReader();
                uint32 count = 0;
                if (reader->BeginArray(inKey, count))
                {
                    std::vector<T>* v = (std::vector<T>*)inVector;
                    if (count)
                    {
                        v->resize(count);
                        
                        for (uint32 i = 0; i < count; ++i)
                        {
                            innerType->InstanceRtonSync(&((*v)[i]), inSync, NULL);
                        }
                    }
                    else
                    {
                        v->clear();
                    }
                    reader->EndArray();
                    return true;
                }
            }
            
            return false;
        }
    };
    
    
    template <class T> class TStdDequeManipulator : public IStdManipulator
    {
    public:
        virtual uint32 GetCount(const void* inVector) const
        {
            std::deque<T>* v = (std::deque<T>*)inVector;
            return (uint32)v->size();
        }
        
        virtual bool InstanceRtonSync(void* inVector, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey, RType* innerType) const
        {
            if (inSync->IsWriting())
            {
                RtSerialRtonWriter* writer = inSync->GetWriter();
                std::deque<T>* v = (std::deque<T>*)inVector;
                writer->BeginArray(inKey, (uint32)v->size());
                for (auto &item : *v)
                {
                    innerType->InstanceRtonSync(&item, inSync, NULL);
                }
                writer->EndArray();
                return true;
            }
            else
            {
                RtSerialRtonReader* reader = inSync->GetReader();
                uint32 count = 0;
                if (reader->BeginArray(inKey, count))
                {
                    if (count)
                    {
                        std::deque<T>* v = (std::deque<T>*)inVector;
                        v->resize(count);
                        
                        for (uint32 i = 0; i < count; ++i)
                        {
                            innerType->InstanceRtonSync(&((*v)[i]), inSync, NULL);
                        }
                    }
                    reader->EndArray();
                    return true;
                }
            }
            
            return false;
        }
    };
    
    template <class T> class TStdMapManipulator : public IStdManipulator
    {
    public:
        virtual uint32 GetCount(const void* inMap) const
        {
            const std::map<std::string,T>* m = (const std::map<std::string,T>*)inMap;
            return (uint32)m->size();
        }
        
        virtual bool InstanceRtonSync(void* inMap, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey, RType* innerType) const
        {
            if (inSync->IsWriting())
            {
                RtSerialRtonWriter* writer = inSync->GetWriter();
                std::map<std::string,T>* m = (std::map<std::string,T>*)inMap;
                writer->BeginObject(inKey);
                for (auto &pair : *m)
                {
                    innerType->InstanceRtonSync(&pair.second, inSync, pair.first);
                }
                writer->EndObject();
                return true;
            }
            else
            {
                RtSerialRtonReader* reader = inSync->GetReader();
                if (reader->BeginObject(inKey))
                {
                    std::map<std::string,T>* m = (std::map<std::string,T>*)inMap;
                    RtSerialRtonReader::Value object = reader->GetCurrentScope();
                    RtSerialRtonReader::Key childKey = object.GetFirstChild();
                    while (childKey.IsValid())
                    {
                        innerType->InstanceRtonSync(&((*m)[childKey.GetName()]), inSync, childKey.GetName());
                        childKey = childKey.GetNextSibling();
                    }
                    
                    reader->EndObject();
                    return true;
                }
            }
            
            return false;
        }
    };
    
    template <class T, int TableId> class TEmbeddedObjectManipulator : public IStdManipulator
    {
    public:
        virtual uint32 GetCount(const void*) const
        {
            return 1;
        }
        
        virtual bool InstanceRtonSync(void* inObj, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey, RType* innerType) const
        {
            if (inSync->IsWriting())
            {
                PRIME_ERROR("Not implemented. This shouldn't be necessary, but if it is you can write out an RtId.");
            }
            else
            {
                RtSerialRtonReader* reader = inSync->GetReader();
                RtDbTable* table = RtDb::GetDb()->GetTable(TableId);
                bool success = false;
                if (reader->BeginObject(inKey))
                {
                    RtSerialRtonReader::Key childKey = reader->GetCurrentScope().GetFirstChild();
                    if (childKey.IsValid())
                    {
                        RtClass* objClass = RtClass::StaticGetClassNamed(childKey.GetName());
                        if (objClass)
                        {
                            RtObject *object = objClass->New();
                            object->Serialize(RtSerializeContext(inSync, childKey.GetName()));
                            *((RtId*)inObj) = table->AllocId(object, RtDbTable::ODM_Deferred);
                            success = true;
                        }
                    }
                    reader->EndObject();
                    return success;
                }
            }
            
            return false;
        }
    };
    
    template <class T> class TStdSetManipulator : public IStdManipulator
    {
    public:
        virtual uint32 GetCount(const void* inSet) const
        {
            const std::set<T>* s = (const std::set<T>*)inSet;
            return (uint32)s->size();
        }
        
        virtual bool InstanceRtonSync(void* inSet, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey, RType* innerType) const
        {
            if (inSync->IsWriting())
            {
                RtSerialRtonWriter* writer = inSync->GetWriter();
                std::set<T>* s = (std::set<T>*)inSet;
                writer->BeginArray(inKey, (uint32)s->size());
                for (auto &item : *s)
                {
                    innerType->InstanceRtonSync(const_cast<T*>(&item), inSync, NULL);
                }
                writer->EndArray();
                return true;
            }
            else
            {
                RtSerialRtonReader* reader = inSync->GetReader();
                uint32 count = 0;
                if (reader->BeginArray(inKey, count))
                {
                    if (count)
                    {
                        std::set<T>* s = (std::set<T>*)inSet;
                        for (uint32 i = 0; i < count; ++i)
                        {
                            T temp;
                            innerType->InstanceRtonSync(&temp, inSync, NULL);
                            s->insert(temp);
                        }
                    }
                    
                    reader->EndArray();
                    return true;
                }
            }
            
            return false;
        }
    };
    
protected:
	friend class CRefSymbolDb;
    friend class CRefPdbSymbolBuilder;
    friend class CRefManualSymbolBuilder;
    friend class RClass;
    
    ECustomTypeCategory mCustomTypeCategory;
    UTypePtr mInnerType;
    IStdManipulator* mManipulator;

public:
    RCustomType()
    : mManipulator(NULL)
    {}
    ~RCustomType()
    {
        delete mManipulator;
        mManipulator = NULL;
    }
    
    static ETypeCategory StaticGetTypeCategory() { return TC_Custom; }
	virtual ETypeCategory GetTypeCategory() const override { return StaticGetTypeCategory(); }

	bool TypeEquals(RType* inType, bool inCheckConst=true, bool inExactMatch=false) const override;
	std::string TypeToString(bool inCheckConst=true) const override;

	inline ECustomTypeCategory GetCustomTypeCategory() const { return mCustomTypeCategory; }
    inline SubTypeCategory GetSubTypeCategory() const { return GetCustomTypeCategory(); }
	inline RType* GetInnerType() const { return mInnerType.mPtr; }
	inline IStdManipulator* GetManipulator() const { return mManipulator; }

	virtual std::string InstanceToString(const void* inInstancePtr) const override;
	virtual bool InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const override;
	virtual bool InstanceNavigatePath(void*& ioInstancePtr, std::string& ioPath, RType*& outType) const override;
};

/*
	RNamedType
*/
class RNamedType
: public RType
{
public:
	RT_CLASS_DEFINE_ABSTRACT(Reflection::RNamedType, Reflection::RType, RtClass) {}

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	std::string mName;

	RNamedType() {}

public:
	virtual bool TypeEquals(RType* inType, bool inCheckConst=true, bool inExactMatch=false) const override;
	virtual std::string TypeToString(bool inCheckConst=true) const override;

	inline const char* GetName() const { return mName.c_str(); }

	virtual std::string InstanceToString(const void* inInstancePtr) const override;
	virtual RNamedType* GetDereferencedType() const { return (RNamedType*)this; }

	virtual bool InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const override;
};

/*
	RUnknownNamedType
*/
class RUnknownNamedType
: public RNamedType
{
public:
	RT_CLASS_DEFINE(Reflection::RUnknownNamedType, Reflection::RNamedType, RtClass) {}

public:
    static ETypeCategory StaticGetTypeCategory() { return TC_Named_Unknown; }
	virtual ETypeCategory GetTypeCategory() const override { return StaticGetTypeCategory(); }
};

/*
	RClass
*/
class RClass
: public RNamedType
{
public:
	RT_CLASS_DEFINE(Reflection::RClass, Reflection::RNamedType, RtClass) {}

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;

	enum EClassFlags
	{
		CF_Union					= (1 << 0),
		
		CF_DisputedFlags			= (1 << 8),
		CF_DisputedVtblSize			= (1 << 9),
		CF_DisputedFields			= (1 << 10),
		CF_DisputedMethods			= (1 << 11),
		CF_DisputedAncestors		= (1 << 12),
		CF_DisputedMembers			= (CF_DisputedFields | CF_DisputedMethods | CF_DisputedAncestors),

		CF_ResolvedVirtualBases		= (1 << 24),

		CF_Loaded					= (1 << 31),
	};

	class CPreAttribute
	{
	public:
		std::string mMethodName;
		uint32 mRVA;
	};

	CRefSymbolDb* mSymbolDb;
	uint32 mClassDbIndex;
	uint32 mClassFlags;
	uint32 mVtblSize;
	RtClass* mClassBoundRtClass;
	TRefNamedSymbolCollection<RField> mFields;
	TRefNamedSymbolCollection<RProperty> mProperties;
	TRefNamedSymbolCollection<RMethod> mMethods;
	TRefNamedSymbolCollection<REvent> mEvents;
	TRefNamedSymbolCollection<RAncestor> mAncestors;
	std::vector<CPreAttribute> mPreAttributes;

	// fields/methods/attributes including those inherited from ancestors, for convenience
	TRefNamedSymbolCollection<RField> mAllFields;
	TRefNamedSymbolCollection<RProperty> mAllProperties;
	TRefNamedSymbolCollection<RMethod> mAllMethods;
	TRefNamedSymbolCollection<REvent> mAllEvents;
	TRefNamedSymbolCollection<RAttribute> mAllAttributes;

	RMethod* FindVirtualBaseMethod(RMethod* inMethod);
	void ResolveVirtualBases();

public:
	RClass();

    static ETypeCategory StaticGetTypeCategory() { return TC_Named_Class; }
	virtual ETypeCategory GetTypeCategory() const override { return StaticGetTypeCategory(); }

	inline bool GetIsUnion() const { return (mClassFlags & CF_Union) != 0; }
	
	inline uint32 GetVtblSize() const { return mVtblSize; }

	inline const TRefNamedSymbolCollection<RField>* GetFields(bool inIncludeInherited = false) const { return inIncludeInherited ? &mAllFields : &mFields; }
	inline const TRefNamedSymbolCollection<RProperty>* GetProperties(bool inIncludeInherited = false) const { return inIncludeInherited ? &mAllProperties : &mProperties; }
	inline const TRefNamedSymbolCollection<RMethod>* GetMethods(bool inIncludeInherited = false) const { return inIncludeInherited ? &mAllMethods : &mMethods; }
	inline const TRefNamedSymbolCollection<REvent>* GetEvents(bool inIncludeInherited = false) const { return inIncludeInherited ? &mAllEvents : &mEvents; }
	inline const TRefNamedSymbolCollection<RAncestor>* GetAncestors() const { return &mAncestors; }
	inline const TRefNamedSymbolCollection<RAttribute>* GetAttributes(bool inIncludeInherited = false) const { return inIncludeInherited ? &mAllAttributes : &mSymAttributes; }

	virtual std::string InstanceToString(const void* inInstancePtr) const override;
	
	bool InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey, const std::vector<std::string>& inMemberWildcards) const;
	virtual bool InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const override
	{
		std::vector<std::string> unusedWildcards;
		return InstanceRtonSync(inInstancePtr, inSync, inKey, unusedWildcards);
	}
	virtual bool InstanceNavigatePath(void*& ioInstancePtr, std::string& ioPath, RType*& outType) const override;

	RClass* GetPrimaryAncestor() const;
	void LoadClass();
    bool CheckFieldNameValid(const std::string& inName);

	inline void SetBoundRtClass(RtClass* inRtClass) { mClassBoundRtClass = inRtClass; }
	inline RtClass* GetBoundRtClass() const { return mClassBoundRtClass; }
};

/*
	RClassRef
*/
class RClassRef
: public RNamedType
{
public:
	RT_CLASS_DEFINE(Reflection::RClassRef, Reflection::RNamedType, RtClass) {}

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	RClass* mClass;

public:
    static ETypeCategory StaticGetTypeCategory() { return TC_Named_ClassRef; }
	virtual ETypeCategory GetTypeCategory() const override { return StaticGetTypeCategory(); }

	virtual std::string InstanceToString(const void* inInstancePtr) const override
	{
		RClass* c = GetRClass();
		return c ? c->InstanceToString(inInstancePtr) : "?";
	}
	virtual bool InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const override
	{
		RClass* c = GetRClass();
		return c ? c->InstanceRtonSync(inInstancePtr, inSync, inKey) : false;
	}
	virtual bool InstanceNavigatePath(void*& ioInstancePtr, std::string& ioPath, RType*& outType) const override
	{
		RClass* c = GetRClass();
		return c ? c->InstanceNavigatePath(ioInstancePtr, ioPath, outType) : false;
	}

	inline RClass* GetRClass(bool inEnsureLoaded = true) const
	{
		if (mClass && inEnsureLoaded)
			mClass->LoadClass();
		return mClass;
	}

	virtual RNamedType* GetDereferencedType() const override { return GetRClass(); }
};

/*
	REnumMember
*/
class REnumMember
: public RSymbol
{
public:
	RT_CLASS_DEFINE(Reflection::REnumMember, Reflection::RSymbol, RtClass) {}

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class REnum;

	enum EEnumMemberFlags
	{
		EMF_Disputed	= (1 << 8),
	};

	std::string mMemberName;
	uint32 mMemberValue;
	REnum* mMemberOuter;
	uint32 mEnumMemberFlags;

public:
	inline const char* GetName() const { return mMemberName.c_str(); }
	inline uint32 GetValue() const { return mMemberValue; }
	inline REnum* GetOuter() const { return mMemberOuter; }

	inline bool GetIsDisputed() const { return (mEnumMemberFlags & EMF_Disputed) != 0; }
};

/*
	TRefNamedSymbolCollection specialization: REnumMember
*/
template <> class TRefNamedSymbolCollection<REnumMember>
: public CRefNamedSymbolCollection
{
protected:
	typedef std::map<uint32, REnumMember*> DValueToSymbolMap;
	
	DValueToSymbolMap mValueToSymbolMap;

public:
	REnumMember* GetIndexed(uint32 inIndex) const
	{
		return (REnumMember*)mSymbols[inIndex];
	}
	REnumMember* GetNamed(const std::string& inName) const
	{
		DNameToSymbolMap::const_iterator it = mNameToSymbolMap.find(inName);
		if (it != mNameToSymbolMap.end())
			return (REnumMember*)it->second;
		return 0;
	}
	REnumMember* GetByValue(uint32 inValue) const
	{
		DValueToSymbolMap::const_iterator it = mValueToSymbolMap.find(inValue);
		if (it != mValueToSymbolMap.end())
			return it->second;
		return 0;
	}
	bool AddSymbol(const std::string& inName, REnumMember* inSymbol)
	{
		if (!inName.empty() && GetNamed(inName))
			return false;
		InternalAddSymbol(inName, inSymbol);
		
		DValueToSymbolMap::const_iterator it = mValueToSymbolMap.find(inSymbol->GetValue());
		if (it == mValueToSymbolMap.end())
			mValueToSymbolMap[inSymbol->GetValue()] = inSymbol;
		
		return true;
	}
};

/*
	REnum
*/
class REnum
: public RNamedType
{
public:
	RT_CLASS_DEFINE(Reflection::REnum, Reflection::RNamedType, RtClass) {}

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	enum EEnumFlags
	{
		EF_MembersAreFlags			= (1 << 0),
		
		EF_DisputedFlags			= (1 << 8),
		EF_DisputedMembers			= (1 << 9),
	
		EF_Loaded					= (1 << 31),
	};

	CRefSymbolDb* mSymbolDb;
	uint32 mEnumDbIndex;
	uint32 mEnumFlags;
	TRefNamedSymbolCollection<REnumMember> mMembers;

public:
    static ETypeCategory StaticGetTypeCategory() { return TC_Named_Enum; }
	virtual ETypeCategory GetTypeCategory() const override { return StaticGetTypeCategory(); }

	inline bool GetIsFlags() const { return (mEnumFlags & EF_MembersAreFlags) != 0; }

	inline const TRefNamedSymbolCollection<REnumMember>* GetMembers() const { return &mMembers; }

	virtual std::string InstanceToString(const void* inInstancePtr) const override;
	virtual bool InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const override;

	void LoadEnum();
};

/*
	REnumRef
*/
class REnumRef
: public RNamedType
{
public:
	RT_CLASS_DEFINE(Reflection::REnumRef, Reflection::RNamedType, RtClass) {}

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	REnum* mEnum;

public:
    static ETypeCategory StaticGetTypeCategory() { return TC_Named_EnumRef; }
	virtual ETypeCategory GetTypeCategory() const override { return StaticGetTypeCategory(); }

	virtual std::string InstanceToString(const void* inInstancePtr) const override
	{
		REnum* e = GetREnum();
		return e ? e->InstanceToString(inInstancePtr) : "?";
	}
	virtual bool InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const override
	{
		REnum* e = GetREnum();
		return e ? e->InstanceRtonSync(inInstancePtr, inSync, inKey) : false;
	}

	inline REnum* GetREnum(bool inEnsureLoaded = true) const
	{
		if (mEnum && inEnsureLoaded)
			mEnum->LoadEnum();
		return mEnum;
	}

	virtual RNamedType* GetDereferencedType() const override { return GetREnum(); }
};

/*
	RClassMember
*/
class RClassMember
: public RSymbol
{
public:
	RT_CLASS_DEFINE(Reflection::RClassMember, Reflection::RSymbol, RtClass) {}

public:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	enum EMemberAccess
	{
		MA_Private,
		MA_Protected,
		MA_Public,
	};

protected:
	std::string mMemberName;
	EMemberAccess mMemberAccess;
	RClass* mMemberOuter;

public:
	inline const char* GetName() const { return mMemberName.c_str(); }
	inline EMemberAccess GetAccess() const { return mMemberAccess; }
	inline RClass* GetOuter() const { return mMemberOuter; }
};

/*
	RField
*/
class RField
: public RClassMember
{
public:
	RT_CLASS_DEFINE(Reflection::RField, Reflection::RClassMember, RtClass) {}

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	enum EFieldFlags
	{
		FF_Static		= (1 << 0),

		FF_Disputed		= (1 << 8),
	};

	uint32 mFieldFlags;
	uint32 mFieldOffset;
	UTypePtr mFieldType;

public:
	inline bool GetIsStatic() const { return (mFieldFlags & FF_Static) != 0; }
	inline bool GetIsDisputed() const { return (mFieldFlags & FF_Disputed) != 0; }
	
	inline uint32 GetFieldOffset() const { return mFieldOffset; }

	inline RType* GetType() const { return mFieldType.mPtr; }

	std::string InstanceToString(const void* inInstancePtr) const;
	bool InstanceRtonSync(void* inInstancePtr, RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey) const;
};

/*
	RProperty
*/
class RProperty
: public RClassMember
{
public:
	RT_CLASS_DEFINE(Reflection::RProperty, Reflection::RClassMember, RtClass) {}

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	enum EPropertyFlags
	{
		PF_Static		= (1 << 0),

		PF_Shadowed		= (1 << 7), // property is shadowed by another property of the same name in a derived class
		PF_Disputed		= (1 << 8),
	};

	uint32 mPropertyFlags;
	RMethod* mPropertyGetterMethod;
	RMethod* mPropertySetterMethod;
	UTypePtr mPropertyType;

public:
	inline bool GetIsStatic() const { return (mPropertyFlags & PF_Static) != 0; }
	inline bool GetIsShadowed() const { return (mPropertyFlags & PF_Shadowed) != 0; }
	inline bool GetIsDisputed() const { return (mPropertyFlags & PF_Disputed) != 0; }
	
	inline RMethod* GetPropertyGetterMethod() const { return mPropertyGetterMethod; }
	inline RMethod* GetPropertySetterMethod() const { return mPropertySetterMethod; }

	inline RType* GetType() const { return mPropertyType.mPtr; }
};

/*
	RMethod
*/
class RMethod
: public RClassMember
{
public:
	RT_CLASS_DEFINE(Reflection::RMethod, Reflection::RClassMember, RtClass) {}

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;
	friend class REvent;

	enum EMethodFlags
	{
		MF_Virtual				= (1 << 0),
		MF_IntroVirtual			= (1 << 1),
		MF_PureVirtual			= (1 << 2),

		MF_CanInvokeStatic		= (1 << 4), // method is statically invokable (no "this" pointer required)
		MF_CanInvokeInstance	= (1 << 5), // method is invokable when a "this" instance pointer is provided
		MF_CanInvokeSerialCommand = (1 << 6), // method uses RtSerialCommand-style invoke signature
		MF_Shadowed		= (1 << 7), // method is shadowed by another method of the same name in a derived class
		MF_Disputed		= (1 << 8),
	};

	uint32 mMethodFlags;
	uint32 mRVA;
	uint32 mVtblOffset;
	RMethod* mVirtualBase;
	UTypePtr mMethodType;
	void* mMethodInvokePtr;
	DelegateBase* mMethodDelegate;

#ifdef SUPPORT_AUTOREFLECTION
	bool BuildInvokeArgBuffer(const std::vector<CRefInvokeVariant>& inArgs, std::vector<unsigned char>& outBuffer);
	bool Invoke(CRefInvokeVariant* outReturnValue, void* inThis, const void* inArgData, uint32 inArgLen);
#endif

public:
	inline bool GetIsVirtual() const { return (mMethodFlags & MF_Virtual) != 0; }
	inline bool GetIsIntroVirtual() const { return (mMethodFlags & MF_IntroVirtual) != 0; }
	inline bool GetIsPureVirtual() const { return (mMethodFlags & MF_PureVirtual) != 0; }
	inline bool GetIsShadowed() const { return (mMethodFlags & MF_Shadowed) != 0; }
	inline bool GetIsDisputed() const { return (mMethodFlags & MF_Disputed) != 0; }

	inline RMethod* GetVirtualBase() const { return mVirtualBase; }
	inline uint32 GetVtblOffset() const { return mVtblOffset; }
	inline uint32 GetRVA() const { return mRVA; }

	inline RType* GetType() const { return mMethodType.mPtr; }

	inline bool CanInvoke(bool inHasThis) const
	{
		if (inHasThis)
			return (mMethodFlags & (MF_CanInvokeStatic|MF_CanInvokeInstance)) != 0;
		else
			return (mMethodFlags & MF_CanInvokeStatic) != 0;
	}
	inline bool CanInvokeSerialCommand(bool inHasThis) const
	{
		return ((mMethodFlags & MF_CanInvokeSerialCommand) != 0) && CanInvoke(inHasThis);
	}
	
	const DelegateBase* GetMethodDelegate() const
	{
		return mMethodDelegate;
	}

	bool Invoke(CRefInvokeVariant* outReturnValue, void* inThis, const std::vector<CRefInvokeVariant>& inArgs);

    template<typename RT>
    bool InvokeWithTypedReturn(RT* outReturnValue, void* inThis, const std::vector<CRefInvokeVariant>& inArgs)
    {
        if (mMethodDelegate)
        {
            // delegate-based manual reflection
            RFunctionType* methodType = (RFunctionType*)GetType();
            if (methodType->GetThisType() && !mMethodDelegate->NeedsInstanceContext())
            {
                // the method is an instance method, but the delegate itself doesn't involve an
                // instance (it's either a global function or static method), so push on "this"
                // as an implicit first argument (cdecl-style behavior)
                std::vector<CRefInvokeVariant> tempArgs = inArgs;
                tempArgs.insert(tempArgs.begin(), inThis);
                mMethodDelegate->InvokeWithTypedReturn(outReturnValue, &tempArgs[0]);
            }
            else
            {
                mMethodDelegate->InvokeWithTypedReturn(inThis, outReturnValue, inArgs.empty() ? NULL : &inArgs[0]);
            }
            return true;
        }
        else
        {
            DBG_ASSERT(false && "RMethod::InvokeWithTypedReturn() cannot be called on auto-reflection methods.");

            return false;
        }
    }

	inline bool Invoke(CRefInvokeVariant* outReturnValue, void* inThis)
	{
		std::vector<CRefInvokeVariant> dummyArgs;
		return Invoke(outReturnValue, inThis, dummyArgs);
	}

	static bool StaticInvokeSerialCommand(RtSerialRtonReader* inReader, RtSerialRtonWriter* inWriter);
};

/*
	REvent
*/
class REvent
: public RClassMember
{
public:
	RT_CLASS_DEFINE(Reflection::REvent, Reflection::RClassMember, RtClass) {}

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	enum EEventFlags
	{
		EF_Static		= (1 << 0),
		EF_SerialCommand = (1 << 1), // method uses RtSerialCommand-style execute signature

		EF_Disputed		= (1 << 8),
	};

	uint32 mEventFlags;
	uint32 mEventOffset;
	UTypePtr mEventType;

public:
	inline bool GetIsStatic() const { return (mEventFlags & EF_Static) != 0; }
	inline bool GetIsSerialCommand() const { return (mEventFlags & EF_SerialCommand) != 0; }
	inline bool GetIsDisputed() const { return (mEventFlags & EF_Disputed) != 0; }
	
	inline uint32 GetEventOffset() const { return mEventOffset; }

	inline RType* GetType() const { return mEventType.mPtr; }

	bool Connect(void* inThis, void* inMethodContext, RMethod* inMethod);
	bool Disconnect(void* inThis, void* inMethodContext, RMethod* inMethod);

	bool Invoke(CRefInvokeVariant* outReturnValue, void* inThis, const std::vector<CRefInvokeVariant>& inArgs);

	inline bool Invoke(CRefInvokeVariant* outReturnValue, void* inThis)
	{
		std::vector<CRefInvokeVariant> dummyArgs;
		return Invoke(outReturnValue, inThis, dummyArgs);
	}

	static bool StaticInvokeSerialCommand(RtSerialRtonReader* inReader, RtSerialRtonWriter* inWriter);
};

/*
	RAncestor
*/
class RAncestor
: public RClassMember
{
public:
	RT_CLASS_DEFINE(Reflection::RAncestor, Reflection::RClassMember, RtClass) {}

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	enum EAncestorFlags
	{
		AF_Disputed		= (1 << 8),
	};

	uint32 mAncestorFlags;
	uint32 mOffset;
	RClass* mAncestorClass;

public:
	inline bool GetIsDisputed() const { return (mAncestorFlags & AF_Disputed) != 0; }
	
	inline uint32 GetOffset() const { return mOffset; }

	inline RClass* GetRClass(bool inEnsureLoaded = true) const
	{
		if (mAncestorClass && inEnsureLoaded)
			mAncestorClass->LoadClass();
		return mAncestorClass;
	}
};

/*
	CRefAttributeVariant
*/
class CRefAttributeVariant;
template <typename T> class TRefAttributeVariantGetter { public: static T Get(const CRefAttributeVariant* v); };

class CRefAttributeVariant
{
public:
	enum EVariantType
	{
		VT_Bool,
		VT_UInt32,
		VT_SInt32,
		VT_Float,
		VT_UInt64,
		VT_SInt64,
		VT_Double,
		VT_String,
		VT_WString,
		VT_RtId
	};

	EVariantType mType;
	union
	{
		uint32 mUInt32;
		int32 mSInt32;
		float mFloat;
		uint64 mUInt64;
		int64 mSInt64;
		double mDouble;
	};
	std::string mString;
	std::wstring mWString;

	inline CRefAttributeVariant() { mType = VT_UInt32; mUInt32 = 0; }
	inline CRefAttributeVariant(bool inValue) { mType = VT_Bool; mUInt32 = inValue ? 1 : 0; }
	inline CRefAttributeVariant(char inValue) { mType = VT_SInt32; mSInt32 = inValue; }
	inline CRefAttributeVariant(signed char inValue) { mType = VT_SInt32; mSInt32 = inValue; }
	inline CRefAttributeVariant(unsigned char inValue) { mType = VT_UInt32; mUInt32 = inValue; }
	inline CRefAttributeVariant(signed short inValue) { mType = VT_SInt32; mSInt32 = inValue; }
	inline CRefAttributeVariant(unsigned short inValue) { mType = VT_UInt32; mUInt32 = inValue; }
	inline CRefAttributeVariant(int32 inValue) { mType = VT_SInt32; mSInt32 = inValue; }
	inline CRefAttributeVariant(uint32 inValue) { mType = VT_UInt32; mUInt32 = inValue; }
	inline CRefAttributeVariant(wchar_t inValue) { mType = VT_UInt32; mUInt32 = inValue; }
	inline CRefAttributeVariant(uint64 inValue) { mType = VT_UInt64; mUInt64 = inValue; }
	inline CRefAttributeVariant(int64 inValue) { mType = VT_SInt64; mSInt64 = inValue; }
    inline CRefAttributeVariant(const char* inValue) { mType = VT_String; mString = inValue; }
	inline CRefAttributeVariant(const std::string& inValue) { mType = VT_String; mString = inValue; }
    inline CRefAttributeVariant(const wchar_t* inValue) { mType = VT_WString; mWString = inValue; }
	inline CRefAttributeVariant(const std::wstring& inValue) { mType = VT_WString; mWString = inValue; }
	inline CRefAttributeVariant(float inValue) { mType = VT_Float; mFloat = inValue; }
	inline CRefAttributeVariant(double inValue) { mType = VT_Double; mDouble = inValue; }
	inline CRefAttributeVariant(const RtId& inValue) { mType = VT_RtId; mUInt64 = inValue.GetValue(); }

	bool GetBool() const;
	uint32 GetUInt32() const;
	int32 GetSInt32() const;
	uint64 GetUInt64() const;
	int64 GetSInt64() const;
	float GetFloat() const;
	double GetDouble() const;
	std::string GetString() const;
	std::wstring GetWString() const;
	RtId GetRtId() const;

	template <typename T> T Get() const { return TRefAttributeVariantGetter<T>::Get(this); }
};

#define REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_UINT32(xType) template <> class TRefAttributeVariantGetter<xType> { public: static xType Get(const CRefAttributeVariant* v) { return (xType)v->GetUInt32(); } }
#define REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_SINT32(xType) template <> class TRefAttributeVariantGetter<xType> { public: static xType Get(const CRefAttributeVariant* v) { return (xType)v->GetSInt32(); } }
#define REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_UINT64(xType) template <> class TRefAttributeVariantGetter<xType> { public: static xType Get(const CRefAttributeVariant* v) { return (xType)v->GetUInt64(); } }
#define REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_SINT64(xType) template <> class TRefAttributeVariantGetter<xType> { public: static xType Get(const CRefAttributeVariant* v) { return (xType)v->GetSInt64(); } }

REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_SINT32(char);
REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_SINT32(signed char);
REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_UINT32(unsigned char);
REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_SINT32(signed short);
REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_UINT32(unsigned short);
REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_SINT32(int32);
REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_UINT32(uint32);
REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_UINT32(wchar_t);
REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_SINT64(int64);
REFLECTION_ATTRIBUTEVARIANT_DECLARE_TYPE_UINT64(uint64);

template <> class TRefAttributeVariantGetter<bool> { public: static bool Get(const CRefAttributeVariant* v) { return (v->GetUInt32() > 0); } };
template <> class TRefAttributeVariantGetter<float> { public: static float Get(const CRefAttributeVariant* v) { return v->GetFloat(); } };
template <> class TRefAttributeVariantGetter<double> { public: static double Get(const CRefAttributeVariant* v) { return v->GetDouble(); } };
template <> class TRefAttributeVariantGetter<std::string> { public: static std::string Get(const CRefAttributeVariant* v) { return v->GetString(); } };
template <> class TRefAttributeVariantGetter<std::wstring> { public: static std::wstring Get(const CRefAttributeVariant* v) { return v->GetWString(); } };
template <> class TRefAttributeVariantGetter<RtId> { public: static RtId Get(const CRefAttributeVariant* v) { return v->GetRtId(); } };

/*
	RAttribute
*/
class RAttribute
: public RSymbol
{
public:
	RT_CLASS_DEFINE(Reflection::RAttribute, Reflection::RSymbol, RtClass) {}

protected:
	friend class CRefSymbolDb;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;
	friend class RClass;

	std::string mName;
	RMethod* mMethod;
	CRefAttributeVariant mValue;

public:
	const char* GetName() const { return mName.c_str(); }
	const CRefAttributeVariant* GetValue() const { return &mValue; }
};

/*
	TRefNamedSymbolCollection specializations: RClass and REnum
*/
template <> class TRefNamedSymbolCollection<RClass>
: public CRefNamedSymbolCollection
{
public:
	RClass* GetIndexed(uint32 inIndex, bool inEnsureLoaded = true) const
	{
		RClass* c = (RClass*)mSymbols[inIndex];
		if (c && inEnsureLoaded)
			c->LoadClass();
		return c;
	}
	RClass* GetNamed(const std::string& inName, bool inEnsureLoaded = true) const
	{
		DNameToSymbolMap::const_iterator it = mNameToSymbolMap.find(inName);
		if (it != mNameToSymbolMap.end())
		{
			RClass* c = (RClass*)it->second;
			if (c && inEnsureLoaded)
				c->LoadClass();
			return c;
		}
		return 0;
	}
	bool AddSymbol(const std::string& inName, RClass* inSymbol)
	{
		if (!inName.empty() && GetNamed(inName, false))
			return false;
		InternalAddSymbol(inName, inSymbol);
		return true;
	}
};
template <> class TRefNamedSymbolCollection<REnum>
: public CRefNamedSymbolCollection
{
public:
	REnum* GetIndexed(uint32 inIndex, bool inEnsureLoaded = true) const
	{
		REnum* e = (REnum*)mSymbols[inIndex];
		if (e && inEnsureLoaded)
			e->LoadEnum();
		return e;
	}
	REnum* GetNamed(const std::string& inName, bool inEnsureLoaded = true) const
	{
		DNameToSymbolMap::const_iterator it = mNameToSymbolMap.find(inName);
		if (it != mNameToSymbolMap.end())
		{
			REnum* e = (REnum*)it->second;
			if (e && inEnsureLoaded)
				e->LoadEnum();
			return e;
		}
		return 0;
	}
	bool AddSymbol(const std::string& inName, REnum* inSymbol)
	{
		if (!inName.empty() && GetNamed(inName, false))
			return false;
		InternalAddSymbol(inName, inSymbol);
		return true;
	}
};

/*
	IRefSymbolBuilder
*/
class IRefSymbolBuilder
{
public:
	virtual void BuilderDestroy() = 0;
	virtual void BuildClass(RClass* inClass) = 0;
	virtual void BuildEnum(REnum* inEnum) = 0;
};

/*
	IRefManualSymbolBuilder
*/
class CRefManualTypeBuilder
{
public:
	static RType* BuildNamedType(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName);
	static std::string StripPointerFromTypeName(const std::string& inTypeName);
	static std::string GetInnerTemplateTypeName(const std::string& inTypeName);
    static std::string GetMapInnerTemplateTypeName(const std::string& inTypeName);
    static std::string GetEmbeddedInnerTemplateTypeName(const std::string& inTypeName);
};
template <typename T> class TRefManualTypeBuilder
: public CRefManualTypeBuilder
{
public:
	static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName)
	{
		return BuildNamedType(inBuilder, inTypeName);
	}
};

class IRefManualSymbolBuilder
: public IRefSymbolBuilder
{
public:
	typedef void (*FClassBuilderCallback)(IRefManualSymbolBuilder* inBuilder, RClass* inClass);
	typedef std::pair<std::string, uint32> DEnumMemberPair;

	// call these to initially register a class or enum.  Because classes are more heavyweight and refer to other classes,
	// their initialization is delayed until needed and will be performed in the provided callback
	virtual void AddClass(const std::string& inName, FClassBuilderCallback inCallback, uint32 inInstanceSize, uint32 inVtblSize = 0) = 0;
	virtual void AddEnum(const std::string& inName, const std::vector<DEnumMemberPair>& inMembers, bool inMembersAreFlags) = 0;

	// call these in a class builder callback to initialize the contents of the class.  This callback will be called at most once per class

	// type builders
	virtual RSimpleType* GetSimpleType(RSimpleType::ESimpleTypeCategory inCategory, uint32 inSize) = 0;
	virtual RReferenceType* GetReferenceType(RReferenceType::EReferenceTypeCategory inCategory, RType* inInnerType, uint32 inArrayItemCount = 0) = 0;
	virtual RFunctionType* GetFunctionType(RFunctionType::ECallType inCallType, RType* inThisType, RType* inReturnType, const std::vector<RType*>& inArgTypes) = 0;
			RFunctionType* GetFunctionType(RFunctionType::ECallType inCallType, RType* inThisType, RType* inReturnType, uint32 inArgCount, ... ); // convenience form; ellipsis args are RType* arg types
	virtual RCustomType* GetCustomType(RCustomType::ECustomTypeCategory inCategory, RType* inInnerType, RCustomType::IStdManipulator* inManipulator = 0) = 0;
	virtual RNamedType* GetNamedType(const std::string& inName) = 0;
	
	// member builders (added to class automatically)
	virtual RAncestor* BuildAncestor(RClass* inClass, RClass* inAncestorClass, uint32 inOffset) = 0;
	virtual RField* BuildField(RClass* inClass, const std::string& inName, uint32 inOffset, RType* inType) = 0;
	virtual RProperty* BuildProperty(RClass* inClass, const std::string& inName, RType* inType, RMethod* inGetter, RMethod* inSetter) = 0;
	virtual RMethod* BuildMethod(RClass* inClass, const std::string& inName, DelegateBase* inDelegate, RFunctionType* inType, bool inIsSerialCommand = false) = 0;
	virtual REvent* BuildEvent(RClass* inClass, const std::string& inName, uint32 inOffset, RFunctionType* inType, bool inIsSerialCommand = false) = 0;
	
	// attribute builder (must be added to parent symbol manually via AddSymbol)
	virtual RAttribute* BuildAttribute(const std::string& inName, const CRefAttributeVariant& inValue) = 0;

	// template type builders for common types (particularly those supported as arg/return types for method invoke)
	template <typename T> RType* GetType(const std::string& inTypeName = "") { return TRefManualTypeBuilder<T>::Build(this, inTypeName); }
};

template <> class TRefManualTypeBuilder<void> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_Void, 0); } };
template <> class TRefManualTypeBuilder<bool> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_Bool, sizeof(bool)); } };
template <> class TRefManualTypeBuilder<char> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_AChar, 1); } };
template <> class TRefManualTypeBuilder<wchar_t> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_WChar, 1); } };
template <> class TRefManualTypeBuilder<int8> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_SInt, 1); } };
template <> class TRefManualTypeBuilder<uint8> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_UInt, 1); } };
template <> class TRefManualTypeBuilder<int16> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_SInt, 2); } };
template <> class TRefManualTypeBuilder<uint16> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_UInt, 2); } };
template <> class TRefManualTypeBuilder<int32> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_SInt, 4); } };
template <> class TRefManualTypeBuilder<uint32> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_UInt, 4); } };
template <> class TRefManualTypeBuilder<int64> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_SInt, 8); } };
template <> class TRefManualTypeBuilder<uint64> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_UInt, 8); } };
template <> class TRefManualTypeBuilder<float> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_Float, 4); } };
template <> class TRefManualTypeBuilder<double> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_Float, 8); } };

//#ifndef HOST_WINDOWS
#if !defined(__LP64__)
// time_t is implementation defined so serializing it is really not a good idea.
// POSIX time can fit in 4 bytes until 2037 so lets assume thats ok!
template <> class TRefManualTypeBuilder<time_t> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetSimpleType(RSimpleType::STC_UInt, 4); } };
#endif
    
template <> class TRefManualTypeBuilder<std::string> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetCustomType(RCustomType::CTC_StdString, inBuilder->GetType<char>()); } };
template <> class TRefManualTypeBuilder<std::wstring> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetCustomType(RCustomType::CTC_StdWString, inBuilder->GetType<wchar_t>()); } };
template <typename T> class TRefManualTypeBuilder<std::vector<T> > { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetCustomType(RCustomType::CTC_StdVector, inBuilder->GetType<T>(CRefManualTypeBuilder::GetInnerTemplateTypeName(inTypeName)), new RCustomType::TStdVectorManipulator<T>); } };
template <> class TRefManualTypeBuilder<RtId> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetCustomType(RCustomType::CTC_WeakRtId, NULL); } };
template <typename T> class TRefManualTypeBuilder<RtWeakPtr<T> > { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetCustomType(RCustomType::CTC_WeakRtId, inBuilder->GetType<T>(CRefManualTypeBuilder::GetInnerTemplateTypeName(inTypeName))); } };
template <typename T> class TRefManualTypeBuilder<RtStrongPtr<T> > { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetCustomType(RCustomType::CTC_StrongRtId, inBuilder->GetType<T>(CRefManualTypeBuilder::GetInnerTemplateTypeName(inTypeName))); } };

template <typename T> class TRefManualTypeBuilder<T*> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetReferenceType(RReferenceType::RTC_Pointer, inBuilder->GetType<T>(CRefManualTypeBuilder::StripPointerFromTypeName(inTypeName))); } };
template <typename T> class TRefManualTypeBuilder<const T*> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetReferenceType(RReferenceType::RTC_Pointer, inBuilder->GetType<T>(CRefManualTypeBuilder::StripPointerFromTypeName(inTypeName))); } };
template <typename T> class TRefManualTypeBuilder<T&> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetReferenceType(RReferenceType::RTC_Ampersand, inBuilder->GetType<T>(CRefManualTypeBuilder::StripPointerFromTypeName(inTypeName))); } };
template <typename T> class TRefManualTypeBuilder<const T&> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetReferenceType(RReferenceType::RTC_Ampersand, inBuilder->GetType<T>(CRefManualTypeBuilder::StripPointerFromTypeName(inTypeName))); } };
//template <typename T> class TRefManualTypeBuilder<T*> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetReferenceType(RReferenceType::RTC_Pointer, inBuilder->GetType<void>()); } };
//template <> class TRefManualTypeBuilder<void*> { public: static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName) { return inBuilder->GetReferenceType(RReferenceType::RTC_Pointer, inBuilder->GetSimpleType(RSimpleType::STC_Void, 0)); } };

template <typename T, int TableId> class TRefManualTypeBuilder<RtEmbeddedPtr<T,TableId>>
{
public:
    static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName)
    {
        return inBuilder->GetCustomType(RCustomType::CTC_EmbeddedObject, inBuilder->GetType<T>(CRefManualTypeBuilder::GetEmbeddedInnerTemplateTypeName(inTypeName)), new RCustomType::TEmbeddedObjectManipulator<T,TableId>);
    }
};

template <typename T> class TRefManualTypeBuilder<std::map<std::string,T>>
{
public:
    static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName)
    {
        static_assert(sizeof(std::map<std::string,int8>) == sizeof(std::map<std::string,T>), "Mismatched map sizes!");
        return inBuilder->GetCustomType(RCustomType::CTC_StdMap, inBuilder->GetType<T>(CRefManualTypeBuilder::GetMapInnerTemplateTypeName(inTypeName)), new RCustomType::TStdMapManipulator<T>);
    }
};

template <typename T> class TRefManualTypeBuilder<std::set<T>>
{
public:
    static RType* Build(IRefManualSymbolBuilder* inBuilder, const std::string& inTypeName)
    {
        static_assert(sizeof(std::set<int8>) == sizeof(std::set<T>), "Mismatched set sizes!");
        return inBuilder->GetCustomType(RCustomType::CTC_StdSet, inBuilder->GetType<T>(CRefManualTypeBuilder::GetInnerTemplateTypeName(inTypeName)), new RCustomType::TStdSetManipulator<T>);
    }
};

/*
	CRefSymbolDb
*/
class CRefSymbolDb
{
public:
	enum EStringFlags
	{
		STRINGF_NoShowPointers		= (1 << 0), // don't show actual pointer values when going through references
	};

protected:
	friend class RClass;
	friend class REnum;
	friend class CRefPdbSymbolBuilder;
	friend class CRefManualSymbolBuilder;

	static uint32 sStringFlags;
	TRefNamedSymbolCollection<RType> mTypes;
	TRefNamedSymbolCollection<RClass> mClasses;
	TRefNamedSymbolCollection<REnum> mEnums;
	IRefSymbolBuilder* mBuilder;
	IRefManualSymbolBuilder* mManualSymbolBuilder;
	bool mFullyLoaded;

	RNamedType* GetTypeForRTTITypeName(const char* inTypeName);

public:
	static CRefSymbolDb* GetManualReflection();

	inline static bool HasStringFlags(uint32 inFlags) { return (sStringFlags & inFlags) != 0; }
	inline static void AddStringFlags(uint32 inFlags) { sStringFlags |= inFlags; }
	inline static void RemoveStringFlags(uint32 inFlags) { sStringFlags &= ~inFlags; }
	inline static void ToggleStringFlag(uint32 inFlag) { if (HasStringFlags(inFlag)) { RemoveStringFlags(inFlag); } else { AddStringFlags(inFlag); } }

	CRefSymbolDb();
	~CRefSymbolDb();

#ifdef SUPPORT_AUTOREFLECTION
	bool InitFromModule(void* inModuleHandle, bool inModuleIsFile = false, const char* inModuleFileName = NULL, const char* inPdbFileName = NULL);
#endif

	inline bool GetIsInitialized() { return mBuilder != NULL; }
	IRefManualSymbolBuilder* GetManualSymbolBuilder();

	inline const TRefNamedSymbolCollection<RType>* GetTypes() const { return &mTypes; }
	inline const TRefNamedSymbolCollection<RClass>* GetClasses() const { return &mClasses; }
	inline const TRefNamedSymbolCollection<REnum>* GetEnums() const { return &mEnums; }

#ifdef SUPPORT_AUTOREFLECTION
	template <typename T> RNamedType* GetInstanceType(const T& inSymbol)
	{
		const std::type_info& ti = typeid(inSymbol);
		return GetTypeForRTTITypeName(ti.name());
	}
	template <typename T> RNamedType* GetInstanceType(T* inSymbol)
	{
		const std::type_info& ti = typeid(inSymbol);
		return GetTypeForRTTITypeName(ti.name());
	}
#endif

	template <typename T> static const void* GetInstancePointer(const T& inSymbol) { return &inSymbol; }
	template <typename T> static const void* GetInstancePointer(T* inSymbol) { return inSymbol; }

	void EnsureFullyLoaded(); // since RClass contents are built on-demand via callbacks, this forces all those callbacks to be run if they haven't already

	bool WriteRtonRepresentation(RtSerialBuffer* inBuffer);
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

} // namespace Reflection

//****************************************************************************
//**
//**    END HEADER REFLECTION.H
//**
//****************************************************************************


#endif //SUPPORT_REFLECTION
#endif // __REFLECTION_H__
