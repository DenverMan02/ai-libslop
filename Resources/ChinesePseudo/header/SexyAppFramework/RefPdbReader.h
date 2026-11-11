#pragma once
#ifndef __REFPDBREADER_H__
#define __REFPDBREADER_H__
//****************************************************************************
//**
//**  File     :  REFPDBREADER.H
//**  Summary  :  Header - Reflection - Program Database (PDB) File Reader
//**
//----------------------------------------------------------------------------
//**       $Id:$ 
//** $DateTime:$ 
//**   $Author:$ 
//**   $Change:$ 
//****************************************************************************
#ifdef SUPPORT_AUTOREFLECTION

//============================================================================
//    HEADERS
//============================================================================
#include <string>
#include <vector>

namespace Reflection {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
typedef std::string DPdbString;

//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
// forward declarations
class CPdbType;
class IPdbReader;

/*
	IPdbTypeCollection

	Collection of indexable CPdbType instances
*/
class IPdbTypeCollection
{
public:
	virtual unsigned long TypeCollGetTypeCount()=0;
	virtual CPdbType* TypeCollGetTypeIndexed(unsigned long inIndex)=0;
};

/*
	HPdbType

	Handle to a CPdbType, stored internally as a one-based index into
	a backing type collection
*/
class HPdbType
{
protected:
	unsigned long mIndex;

public:
	inline HPdbType() : mIndex(0) {}
	inline HPdbType(const HPdbType& inType) : mIndex(inType.mIndex) {}
	inline HPdbType(unsigned long inIndex) : mIndex(inIndex) {}
	
	inline bool IsValid() { return mIndex != 0; }
	inline unsigned long GetIndex() { return mIndex; }
	inline CPdbType* Resolve(IPdbTypeCollection* inTypeColl) const
	{
		return mIndex ? inTypeColl->TypeCollGetTypeIndexed(mIndex - 1) : 0;
	}

	inline operator bool () { return IsValid(); }
	inline bool operator ! () { return !IsValid(); }

	bool Equals(const HPdbType& inType, IPdbTypeCollection* inTypeColl, bool inCheckConst = true);
};

/*
	CPdbType
*/
class CPdbType
{
public:
	// type flags
	enum ETypeFlags
	{
		TYPEF_Const			= 0x01 // type has "const" modifier
	};
	// fundamental types
	enum EType
	{
		TYPE_Unknown			= 0,	// unknown/invalid

		// simple types
		TYPE_Simple_MASK		= 0x10, // mask for all simple types
		TYPE_Simple_Void		= 0x11, // void
		TYPE_Simple_Bool		= 0x12, // bool
		TYPE_Simple_AChar		= 0x13, // char (8-bit ansi character)
		TYPE_Simple_WChar		= 0x14, // wchar_t (16-bit wide character)
		TYPE_Simple_SInt		= 0x15, // signed byte/word/dword/qword (check size)
		TYPE_Simple_UInt		= 0x16, // unsigned byte/word/dword/qword (check size)
		TYPE_Simple_FloatDouble	= 0x17, // float/double (check size)
		TYPE_Simple_Ellipsis	= 0x18, // va_arg ellipsis (only used as last arg to a function)
		TYPE_Simple_HResult		= 0x19, // HRESULT (long)

		// reference types; will have a valid "inner" type
		TYPE_Reference_MASK		= 0x20, // mask for all reference types
		TYPE_Reference_Ampersand= 0x21, // C++ ampersand reference
		TYPE_Reference_Pointer	= 0x22, // pointer reference
		TYPE_Reference_Array	= 0x23, // array reference (check size; divide by inner type size to get array size, zero is [])

		// function types
		TYPE_Function_MASK		= 0x40, // mask for all function types
		TYPE_Function_UnkCall	= 0x41, // function with unknown calling convention
		TYPE_Function_ThisCall	= 0x42, // thiscall function
		TYPE_Function_Cdecl		= 0x43, // cdecl function
		TYPE_Function_StdCall	= 0x44, // stdcall function
		TYPE_Function_FastCall	= 0x45, // fastcall function
		TYPE_Function_SysCall	= 0x46, // syscall function

		// named types
		TYPE_Named_MASK			= 0x80, // mask for all named types
		TYPE_Named_Generic		= 0x81, // generic named type (UDTs etc)
	};

	// common
	HPdbType mHandle; // handle to this type
	unsigned long mType; // EType
	unsigned long mTypeFlags; // ETypeFlags
	unsigned long mSize; // size of type in bytes
	unsigned long mThisAdjust; // adjuster for virtual-inherited classes, generally zero otherwise

	// reference types
	HPdbType mRefTypeInnerType; // inner type of the pointer/reference/array

	// function types
	HPdbType mFuncTypeThisType; // "this" type for member functions
	HPdbType mFuncTypeReturnType; // return type
	std::vector<HPdbType> mFuncTypeArgTypes; // argument types

	// named types
	DPdbString mNamedTypeName; // name of the named type

	// runtime convenience data
	IPdbTypeCollection* mTypeColl; // type collection this type is stored in

	// ctor
	CPdbType()
	: mType(TYPE_Unknown)
	, mTypeFlags(0)
	, mSize(0)
	, mThisAdjust(0)
	, mTypeColl(0)
	{}

	std::string ToString();
	bool Equals(CPdbType* inType, bool inCheckConst = true);
};

/*
	CPdbStructForm
*/
class CPdbStructForm
{
public:
	// structure flags
	enum EStructFlags
	{
		STRUCTF_Union					= 0x0001, // structure is a union (all field offsets zero)
		
		STRUCTF_Dispute_MASK			= 0xFFF0, // mask for all dispute flags (disputed values differ among alternates)
		STRUCTF_Dispute_Flags			= 0x0010, // structure flags are disputed (does not factor in the dispute flags themselves)
		STRUCTF_Dispute_SizeInstance	= 0x0020, // instance size is disputed
		STRUCTF_Dispute_IntroVtblSize	= 0x0040, // intro vtbl size is disputed
		STRUCTF_Dispute_Bases			= 0x0080, // one or more bases are disputed
		STRUCTF_Dispute_Fields			= 0x0100, // one or more fields are disputed
		STRUCTF_Dispute_Methods			= 0x0200, // one or more methods are disputed
	};
	// access rights
	enum EAccess
	{
		ACCESS_Unknown		= 0,
		ACCESS_Private		= 1,
		ACCESS_Protected	= 2,
		ACCESS_Public		= 3,
	};

	// key-value attributes
	class CAttribute
	{
	public:
		DPdbString mKey; // key name of attribute (must be an identifier; no spaces etc)
		DPdbString mValueMethod; // name of static method which fetches value; return type is attribute type; no params
	};

	// bases/fields/methods
	class CBase
	{
	public:
		enum EBaseFlags
		{
			BASEF_Disputed			= 0x0010, // base is disputed (is not identical in all alternate structures)
		
			BASEF_Reserved			= 0x8000, // reserved, do not use
		};

		DPdbString mName; // name of base type
		unsigned long mBaseFlags; // EBaseFlags
		unsigned long mOffset; // offset of base type data from start of instance

		CBase()
		: mBaseFlags(0)
		, mOffset(0)
		{}

		bool Equals(CBase* inBase);
	};
	class CField
	{
	public:
		enum EFieldFlags
		{
			FIELDF_Static			= 0x0001, // field is a static (non-instance) field; offset is fixed address
			
			FIELDF_Disputed			= 0x0010, // field is disputed (is not identical in all alternate structures)
		
			FIELDF_Reserved			= 0x8000, // reserved, do not use
		};

		DPdbString mName; // name of field
		HPdbType mType; // type of the field
		unsigned long mFieldFlags; // EFieldFlags
		unsigned long mOffset; // offset of field, either this-relative (default) or static (check flags)
		EAccess mAccess; // access rights
		std::vector<CAttribute> mAttributes; // key-value attributes

		CField()
		: mFieldFlags(0)
		, mOffset(0)
		, mAccess(ACCESS_Unknown)
		{}

		bool Equals(CField* inField, IPdbTypeCollection* inTypeColl);
	};
	class CMethod
	{
	public:
		enum EMethodFlags
		{
			METHODF_Virtual				= 0x0001, // method is a virtual function
			METHODF_IntroVirtual		= 0x0002, // method is intro-virtual (initial declaration)
			METHODF_PureVirtual			= 0x0004, // method is pure-virtual (= 0)
		
			METHODF_Disputed			= 0x0010, // method is disputed (is not identical in all alternate structures)
		
			METHODF_Reserved			= 0x8000, // reserved, do not use
		};

		DPdbString mName; // name of method
		HPdbType mType; // type of the method
		unsigned long mMethodFlags; // EMethodFlags
		unsigned long mRVA; // relative virtual address for function
		unsigned long mVtblOffset; // vtbl offset for virtual functions (only valid for intro virtual!)
		EAccess mAccess; // access rights
		std::vector<CAttribute> mAttributes; // key-value attributes

		CMethod()
		: mMethodFlags(0)
		, mRVA(0)
		, mVtblOffset(0)
		, mAccess(ACCESS_Unknown)
		{}

		bool Equals(CMethod* inMethod, IPdbTypeCollection* inTypeColl);
	};

	DPdbString mStructName; // name of struct/class
	unsigned long mStructFlags; // EStructFlags
	unsigned long mSizeInstance; // size of individual instances, including vtbl overhead
	unsigned long mIntroVtblSize; // size of intro-virtual vtbl in bytes
	std::vector<CBase> mBases; // bases
	std::vector<CField> mFields; // fields
	std::vector<CMethod> mMethods; // methods
	std::vector<CAttribute> mAttributes; // key-value attributes

	// ctor
	CPdbStructForm()
	: mStructFlags(0)
	, mSizeInstance(0)
	, mIntroVtblSize(0)
	{}

	bool Equals(CPdbStructForm* inStruct, IPdbTypeCollection* inTypeColl);
};

/*
	CPdbStruct
*/
class CPdbStruct
{
public:
	DPdbString mStructName;
	std::vector<unsigned long> mSymIds;
	std::vector<CPdbStructForm> mForms;

	CPdbStruct()
	{}
};

/*
	CPdbEnumForm
*/
class CPdbEnumForm
{
public:
	// enumeration flags
	enum EEnumFlags
	{
		ENUMF_Dispute_MASK			= 0xFFF0, // mask for all dispute flags (disputed values differ among alternates)
		ENUMF_Dispute_Flags			= 0x0010, // enumeration flags are disputed (does not factor in the dispute flags themselves)
		ENUMF_Dispute_Members		= 0x0020, // enumeration members are disputed	
	};

	// members
	class CMember
	{
	public:
		enum
		{
			MEMBERF_Disputed	= 0x0010, // member is disputed (is not identical in all alternate enums)

			MEMBERF_Reserved	= 0x8000, // reserved, do not use
		};

		DPdbString mName; // name of enumeration member
		signed long mValue; // integer value of member
		unsigned long mMemberFlags; // EMemberFlags

		CMember()
		: mValue(0)
		, mMemberFlags(0)
		{}
	
		bool Equals(CMember* inMember);
	};
	
	DPdbString mEnumName; // name of enumeration type
	unsigned long mEnumFlags; // EEnumFlags
	std::vector<CMember> mMembers; // enumeration members

	// ctor
	CPdbEnumForm()
	: mEnumFlags(0)
	{}

	bool Equals(CPdbEnumForm* inEnum);
};

/*
	CPdbEnum
*/
class CPdbEnum
{
public:
	DPdbString mEnumName;
	std::vector<unsigned long> mSymIds;
	std::vector<CPdbEnumForm> mForms;

	CPdbEnum()
	{}
};

/*
	IPdbReader
*/
class IPdbReader
: public IPdbTypeCollection
{
public:
	// destroy the reader; interface becomes invalid afterwards
	virtual void ReaderDestroy()=0;

	// get the number of structs, or a given struct by index or name
	virtual unsigned long ReaderGetStructCount()=0;
	virtual CPdbStruct* ReaderGetStructIndexed(unsigned long inIndex, bool inEnsureLoaded = true)=0;
	virtual CPdbStruct* ReaderGetStructNamed(const char* inStructName, bool inEnsureLoaded = true)=0;

	// get the number of enums, or a given enum by index or name
	virtual unsigned long ReaderGetEnumCount()=0;
	virtual CPdbEnum* ReaderGetEnumIndexed(unsigned long inIndex, bool inEnsureLoaded = true)=0;
	virtual CPdbEnum* ReaderGetEnumNamed(const char* inEnumName, bool inEnsureLoaded = true)=0;
};

//============================================================================
//    GLOBAL DATA
//============================================================================
//============================================================================
//    GLOBAL FUNCTIONS
//============================================================================
/*
	Create a PDB reader for a given file; returns reader interface if successful
	or null otherwise.
*/
IPdbReader* PDB_CreateReader(const char* inPdbFileName, bool inForceFullLoad = false);

//============================================================================
//    INLINE CLASS METHODS
//============================================================================
//============================================================================
//    TRAILING HEADERS
//============================================================================

} // namespace Reflection

#endif // #ifdef SUPPORT_AUTOREFLECTION
//****************************************************************************
//**
//**    END HEADER REFPDBREADER.H
//**
//****************************************************************************
#endif // __REFPDBREADER_H__
