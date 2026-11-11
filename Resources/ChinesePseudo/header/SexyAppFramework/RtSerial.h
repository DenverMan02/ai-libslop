#pragma once
#ifndef __RTSERIAL_H__
#define __RTSERIAL_H__
//****************************************************************************
//**
//**  File     :  RTSERIAL.H
//**  Summary  :  Header - Rt - Serialization
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
#include "RtDb.h"
#include "RtObject.h"
#include "drivers/crashtracking/CrashTracking.h"

#ifndef HOST_WINDOWS
#include <EASTL/hash_map.h>
#endif

namespace Sexy {
//============================================================================
//    DEFINITIONS / ENUMERATIONS / SIMPLE TYPEDEFS
//============================================================================
// uncomment this to make RtSerialBuffer reads/writes use "paranoid" tags for debugging purposes
//#define RTSERIALBUFFER_PARANOID

#ifdef RTSERIALBUFFER_PARANOID
#define RTSERIALBUFFER_PARANOIDARG(x) , x
#else
#define RTSERIALBUFFER_PARANOIDARG(x)
#endif

const uint32 RTSERIAL_RTON_MAGIC_BEGIN		= ('R' + ('T' << 8) + ('O' << 16) + ('N' << 24));
const uint32 RTSERIAL_RTON_MAGIC_END		= ('D' + ('O' << 8) + ('N' << 16) + ('E' << 24));

//============================================================================
//    CLASSES / STRUCTURES
//============================================================================
// external forward declarations
class RtId;
class RtInvokeVariant;

/*
	RtSerialBuffer
*/
class RtSerialBuffer
{
protected:
	uchar* mFixedData;
	uint32 mFixedDataSize;
	std::vector<uchar> mDynData;
	uint32 mCurOffset;
	bool mWriteCalcSizeOnly;
	bool mSyncReading;

	bool InternalMaybeRead(void* inPtr, uint32 inSize);
	void InternalRead(void* inPtr, uint32 inSize);
	bool InternalMaybeWrite(const void* inPtr, uint32 inSize);
	void InternalWrite(const void* inPtr, uint32 inSize);
	uint32 InternalGetUTF8EncodedLengthForChar(uint32 inChar);

public:
	enum EParanoidTag
	{
		PT_Unknown=0,
		PT_Bool,
		PT_Int8Fixed,
		PT_Int16Fixed,
		PT_Int32Fixed,
		PT_Int64Fixed,
		PT_Float,
		PT_Double,
	};

	RtSerialBuffer(uchar* inFixedData = NULL, uint32 inFixedDataSize = 0)
	: mFixedData(inFixedData)
	, mFixedDataSize(inFixedDataSize)
	, mCurOffset(0)
	, mWriteCalcSizeOnly(false)
	, mSyncReading(true)
	{}

	// memory-related methods
	inline void Reserve(uint32 inSize)
	{
		if (!mFixedData && (inSize > (uint32)mDynData.capacity()))
			mDynData.reserve(inSize);
	}
	inline uint32 GetDataSize() const { return mFixedData ? mFixedDataSize : (uint32)mDynData.size(); }
	inline uchar* GetDataPtr() const { return mFixedData ? (uchar*)mFixedData : (!mDynData.empty() ? (uchar*)&mDynData[0] : NULL); }
	inline void SetWriteCalcSizeOnly(bool inCalcSizeOnly) { mWriteCalcSizeOnly = inCalcSizeOnly; }
	inline bool GetWriteCalcSizeOnly() { return mWriteCalcSizeOnly; }

	// seek/tell
	inline void SeekStart(uint32 inOffset)
	{
		DBG_ASSERTE((inOffset <= GetDataSize()) && "RtSerialBuffer::SeekStart: Seeking out of bounds");
		mCurOffset = inOffset;
	}
	inline void SeekCurrent(int32 inOffset) { SeekStart((uint32)((int32)mCurOffset + inOffset)); }
	inline void SeekEnd(uint32 inOffset) { SeekStart(GetDataSize() - inOffset); }
	inline uint32 Tell() const { return mCurOffset; }

	// core read/write - the "Maybe" methods allow an inPtr of null, inSize of zero, checks on overruns etc;
	// the regular methods aren't so forgiving, and assert on many of these situations.  If "paranoid" mode
	// is on (via the RTSERIALBUFFER_PARANOID define), type/size tag information will be prepended to writes
	// and verified on reads, for debugging purposes (because the binary layout is different with paranoid
	// mode enabled, do not try to use the same data files in both paranoid and non-paranoid settings).
#ifdef RTSERIALBUFFER_PARANOID
	bool MaybeRead(void* inPtr, uint32 inSize, uint8 inTag = PT_Unknown);
	void Read(void* inPtr, uint32 inSize, uint8 inTag = PT_Unknown);
	bool MaybeWrite(const void* inPtr, uint32 inSize, uint8 inTag = PT_Unknown);
	void Write(const void* inPtr, uint32 inSize, uint8 inTag = PT_Unknown);
#else
	inline bool MaybeRead(void* inPtr, uint32 inSize) { return InternalMaybeRead(inPtr, inSize); }
	inline void Read(void* inPtr, uint32 inSize) { InternalRead(inPtr, inSize); }
	inline bool MaybeWrite(const void* inPtr, uint32 inSize) { return InternalMaybeWrite(inPtr, inSize); }
	inline void Write(const void* inPtr, uint32 inSize) { InternalWrite(inPtr, inSize); }
#endif

	// fixed-size read
	inline bool ReadBool() { int8 x; Read(&x, sizeof(int8) RTSERIALBUFFER_PARANOIDARG(PT_Bool)); return x!=0; }
	inline int8 ReadInt8Fixed() { int8 x; Read(&x, sizeof(int8) RTSERIALBUFFER_PARANOIDARG(PT_Int8Fixed)); return x; }
	inline int16 ReadInt16Fixed() { int16 x; Read(&x, sizeof(int16) RTSERIALBUFFER_PARANOIDARG(PT_Int16Fixed)); return x; }
	inline int32 ReadInt32Fixed() { int32 x; Read(&x, sizeof(int32) RTSERIALBUFFER_PARANOIDARG(PT_Int32Fixed)); return x; }
	inline int64 ReadInt64Fixed() { int64 x; Read(&x, sizeof(int64) RTSERIALBUFFER_PARANOIDARG(PT_Int64Fixed)); return x; }
	inline float ReadFloat() { float x; Read(&x, sizeof(float) RTSERIALBUFFER_PARANOIDARG(PT_Float)); return x; }
	inline double ReadDouble() { double x; Read(&x, sizeof(double) RTSERIALBUFFER_PARANOIDARG(PT_Double)); return x; }	

	// fixed-size write
	inline void WriteBool(bool inX) { uint8 x = inX?1:0; Write(&x, sizeof(uint8) RTSERIALBUFFER_PARANOIDARG(PT_Bool)); }
	inline void WriteInt8Fixed(int8 inX) { Write(&inX, sizeof(int8) RTSERIALBUFFER_PARANOIDARG(PT_Int8Fixed)); }
	inline void WriteInt16Fixed(int16 inX) { Write(&inX, sizeof(int16) RTSERIALBUFFER_PARANOIDARG(PT_Int16Fixed)); }
	inline void WriteInt32Fixed(int32 inX) { Write(&inX, sizeof(int32) RTSERIALBUFFER_PARANOIDARG(PT_Int32Fixed)); }
	inline void WriteInt64Fixed(int64 inX) { Write(&inX, sizeof(int64) RTSERIALBUFFER_PARANOIDARG(PT_Int64Fixed)); }
	inline void WriteFloat(float inX) { Write(&inX, sizeof(float) RTSERIALBUFFER_PARANOIDARG(PT_Float)); }
	inline void WriteDouble(double inX) { Write(&inX, sizeof(double) RTSERIALBUFFER_PARANOIDARG(PT_Double)); }

	// base-128 "varint" variable-size read/write
	// VarU methods - unsigned encoding (negative values will be encoded unsigned and thus be quite large, not recommended if negatives are common)
	// VarS methods - signed encoding (zigzag encoding, both positive and negative values have equal cost and scale up in length evenly)
	int32 ReadInt32VarU();
	int64 ReadInt64VarU();
	int32 ReadInt32VarS();
	int64 ReadInt64VarS();
	void WriteInt32VarU(int32 inX);
	void WriteInt64VarU(int64 inX);
	void WriteInt32VarS(int32 inX);
	void WriteInt64VarS(int64 inX);

	// unsigned integer read/write (reads are for convenience to avoid excessive casting due to sign-extension; matching writes are just for consistency)
	inline uint8 ReadUInt8Fixed() { return (uint8)ReadInt8Fixed(); }
	inline uint16 ReadUInt16Fixed() { return (uint16)ReadInt16Fixed(); }
	inline uint32 ReadUInt32Fixed() { return (uint32)ReadInt32Fixed(); }
	inline uint32 ReadUInt32VarU() { return (uint32)ReadInt32VarU(); }
	inline uint64 ReadUInt64Fixed() { return (uint64)ReadInt64Fixed(); }
	inline uint64 ReadUInt64VarU() { return (uint64)ReadInt64VarU(); }
	inline void WriteUInt8Fixed(uint8 inX) { WriteInt8Fixed(inX); }
	inline void WriteUInt16Fixed(uint16 inX) { WriteInt16Fixed(inX); }
	inline void WriteUInt32Fixed(uint32 inX) { WriteInt32Fixed(inX); }
	inline void WriteUInt32VarU(uint32 inX) { WriteInt32VarU(inX); }
	inline void WriteUInt64Fixed(uint64 inX) { WriteInt64Fixed(inX); }
	inline void WriteUInt64VarU(uint64 inX) { WriteInt64VarU(inX); }

	// simple string convenience read/write - Int32VarU length in characters, followed by character content (no null terminator)
	void ReadString(std::string& outStr);
	void ReadWString(std::wstring& outStr);
	void WriteString(const std::string& inStr);
	void WriteWString(const std::wstring& inStr);
	void WriteString(const char* inStr);
	void WriteWString(const wchar_t* inStr);

	// UTF-8 string read/write - Int32VarU length in characters, followed by character content (no null terminator).
	// Individual character read/write functions provided for convenience.
	void ReadUTF8String(std::wstring& outStr);
	//PVZ2_CHINESE_START
	wchar_t ReadUTF8Char();
	//PVZ2_CHINESE_END
	void WriteUTF8String(const std::wstring& inStr);
	void WriteUTF8String(const wchar_t* inStr);
	void WriteUTF8Char(uint32 inChar);

	// sync functions (either reads or writes, depending on mode)
	inline void SetIsReading(bool inIsReading) { mSyncReading = inIsReading; }
	inline void SetIsWriting(bool inIsWriting) { mSyncReading = !inIsWriting; }
	inline bool IsReading() { return mSyncReading; }
	inline bool IsWriting() { return !mSyncReading; }

	inline void SyncBool(bool& ioValue) { if (IsReading()) ioValue = ReadBool(); else WriteBool(ioValue); }
	inline void SyncFloat(float& ioValue) { if (IsReading()) ioValue = ReadFloat(); else WriteFloat(ioValue); }
	inline void SyncDouble(double& ioValue) { if (IsReading()) ioValue = ReadDouble(); else WriteDouble(ioValue); }
	inline void SyncString(std::string& ioValue) { if (IsReading()) ReadString(ioValue); else WriteString(ioValue); }
	inline void SyncWString(std::wstring& ioValue) { if (IsReading()) ReadWString(ioValue); else WriteWString(ioValue); }
	inline void SyncUTF8String(std::wstring& ioValue) { if (IsReading()) ReadUTF8String(ioValue); else WriteUTF8String(ioValue); }

#define RTSERIALBUFFER_SYNC_INT_DEFINE(xSuffix, xWriteType) \
	template <typename T> void Sync##xSuffix(T& ioValue) { if (IsReading()) ioValue = (T)Read##xSuffix(); else Write##xSuffix((xWriteType)ioValue); }

	RTSERIALBUFFER_SYNC_INT_DEFINE(Int8Fixed, int8);
	RTSERIALBUFFER_SYNC_INT_DEFINE(Int16Fixed, int16);
	RTSERIALBUFFER_SYNC_INT_DEFINE(Int32Fixed, int32);
	RTSERIALBUFFER_SYNC_INT_DEFINE(Int64Fixed, int64);
	RTSERIALBUFFER_SYNC_INT_DEFINE(Int32VarU, int32);
	RTSERIALBUFFER_SYNC_INT_DEFINE(Int64VarU, int64);
	RTSERIALBUFFER_SYNC_INT_DEFINE(Int32VarS, int32);
	RTSERIALBUFFER_SYNC_INT_DEFINE(Int64VarS, int64);
	RTSERIALBUFFER_SYNC_INT_DEFINE(UInt8Fixed, uint8);
	RTSERIALBUFFER_SYNC_INT_DEFINE(UInt16Fixed, uint16);
	RTSERIALBUFFER_SYNC_INT_DEFINE(UInt32Fixed, uint32);
	RTSERIALBUFFER_SYNC_INT_DEFINE(UInt32VarU, uint32);
	RTSERIALBUFFER_SYNC_INT_DEFINE(UInt64Fixed, uint64);
	RTSERIALBUFFER_SYNC_INT_DEFINE(UInt64VarU, uint64);

#undef RTSERIALBUFFER_SYNC_INT_DEFINE
};

namespace RtSerialRtonTag
{
	enum ETag
	{
		BoolFalse		= 0x00, // ()
		BoolTrue		= 0x01, // ()
		AtomicThis		= 0x02, // ()
		Int8Fixed		= 0x08, // (int8)
		Int8Zero		= 0x09, // ()
		UInt8Fixed		= 0x0A, // (uint8)
		UInt8Zero		= 0x0B, // ()
		Int16Fixed		= 0x10, // (int16)
		Int16Zero		= 0x11, // ()
		UInt16Fixed		= 0x12, // (uint16)
		UInt16Zero		= 0x13, // ()
		Int32Fixed		= 0x20, // (int32)
		Int32Zero		= 0x21, // ()
		Float			= 0x22, // (float)
		FloatZero		= 0x23, // ()
		Int32VarU		= 0x24, // (int32VarU)
		Int32VarS		= 0x25, // (int32VarS)
		UInt32Fixed		= 0x26, // (uint32)
		UInt32Zero		= 0x27, // ()
		UInt32VarU		= 0x28, // (int32VarU)
		Int64Fixed		= 0x40, // (int64)
		Int64Zero		= 0x41, // ()
		Double			= 0x42, // (double)
		DoubleZero		= 0x43, // ()
		Int64VarU		= 0x44, // (int64VarU)
		Int64VarS		= 0x45, // (int64VarS)
		UInt64Fixed		= 0x46, // (uint64)
		UInt64Zero		= 0x47, // ()
		UInt64VarU		= 0x48, // (int64VarU)
		AnsiString		= 0x81, // (int32VarU length in characters, int8* content (no null term))
		UTF8String		= 0x82, // (int32VarU length in original characters (encoded length may be longer), int32VarU encoded length IN BYTES, int8* content (no null term))
		RtId			= 0x83, // (0x00) OR (int32VarU revisionPlusOne, int32VarS table, int32VarU slot)
		RtIdNull		= 0x84, // ()
		Object			= 0x85, // (kvpList* 0xFF)
		Array			= 0x86, // (int8 type tag OR 0xFD for varying, int32VarU array count, valueElementList* 0xFE)
		BinaryBlob		= 0x87, // (keyElement content type, int32VarU data size in bytes that follows, int8* data)
		TrackedAnsiStringNew = 0x90, // (same as AnsiString, but anytime one of these is encountered within a Document, it is added in-order to a vector of tracked strings for reuse)
		TrackedAnsiStringExisting = 0x91, // (int32VarU, index into tracked string vector)
		TrackedUTF8StringNew = 0x92, // (same as TrackedAnsiStringNew, but with UTF8Strings, and tracked in a separate UTF8String vector)
		TrackedUTF8StringExisting = 0x93, // (int32VarU, index into tracked utf8 string vector)

		// CDH FIXME$$$ need new tags for stringbuffer-based tracked strings as well (more closely mapped to decode buffer memstrings, to avoid unnecessary map creation at runtime)

		MarkerArrayTypeVarying	= 0xFD,
		MarkerArrayEnd			= 0xFE,
		MarkerObjectEnd			= 0xFF,

		// B0 - DF reserved for applications (in-memory transient only; application tags must not be persisted or trasmitted across the network)
		ApplicationTagFirst		= 0xB0,
		ApplicationTagLast		= 0xDF,

		// application-space tags used by this specific Rton back-end (mostly for decode buffers)
		MemStringNew			= 0xB0, // (int32 size in bytes INCLUDING NULL TERM (intended solely for skipping over the string content), followed by null-terminated string)
		MemStringExisting		= 0xB1, // (int32 offset into decode buffer of null-terminated string)
		MemWStringNew			= 0xB2, // (int32 size *in bytes* INCLUDING NULL TERM (intended solely for skipping over the string content), followed by null-terminated wstring)
		MemWStringExisting		= 0xB3, // (int32 offset into decode buffer of null-terminated string)
		MemKeyStringNew			= 0xB4, // (same as MemStringNew, but followed by a uint32 decode buffer offset after the value so it can be skipped)
		MemKeyStringExisting	= 0xB5, // (same as MemStringExisting, but followed by a uint32 decode buffer offset after the value so it can be skipped)
		MemKeyWStringNew		= 0xB6, // (same as MemWStringNew, but followed by a uint32 decode buffer offset after the value so it can be skipped)
		MemKeyWStringExisting	= 0xB7, // (same as MemWStringExisting, but followed by a uint32 decode buffer offset after the value so it can be skipped)
		MemObject				= 0xB8, // (kvpList* 0xFF just like normal object, but kvpList keys are all of the MemKey string types)
		MemArray				= 0xB9, // (int8 type tag OR 0xFD for varying, uint32 array count, int32[arrayCount+1] decode buffer offset table to individual elements (+1 for offset after end of array), valueElementList* 0xFE)
		MemRtId					= 0xBA, // (uint64 raw RtId value)
		MemBinaryBlob			= 0xBB, // (keyElement content type (MemStringNew/Existing), int32 data size in bytes that follows, int8* data)
		MemBool					= 0xBC, // (int8 0 or 1) // only needed as a separate tag for display purposes
	};
    
    bool IsKnownTag(int i_tag);
};

// keys are kept as a separate structure (currently only a string) because we're probably going to
// extend it in the future to support shared string boxing via RtIds, and it'd be good for the API
// to support that switch
struct RtSerialRtonKey
{
	std::string mString;

	RtSerialRtonKey() {}
	RtSerialRtonKey(const char* inString) { if (inString) mString = inString; }
	RtSerialRtonKey(const std::string& inString) : mString(inString) {}

	bool IsValid() const { return !mString.empty(); }
};

/*
	RtSerialRtonWriter
*/
class RtSerialRtonWriter
{
public:
	template <typename T> class TWriter { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const T& inValue); };

	template <typename T> class TWriter64 { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const T& inValue); };

protected:

#ifdef HOST_WINDOWS
	typedef std::map<std::string, uint32> DTrackedAnsiStringMap;
	typedef std::map<std::wstring, uint32> DTrackedUTF8StringMap;
#else
	typedef eastl::hash_map<std::string, uint32, eastl::string_hash<std::string> > DTrackedAnsiStringMap;
    typedef eastl::hash_map<std::wstring, uint32, eastl::string_hash<std::wstring> > DTrackedUTF8StringMap;
#endif

	RtSerialBuffer* mBuffer;
	std::vector<bool> mScopeStack; // stack of outer scopes; false = object, true = array
	DTrackedAnsiStringMap mTrackedAnsiStringMap;
	uint32 mTrackedAnsiStringCount;
	DTrackedUTF8StringMap mTrackedUTF8StringMap;
	uint32 mTrackedUTF8StringCount;
	bool mDoDeleteBuffer;

	inline void WriteTag(RtSerialRtonTag::ETag inTag)
	{
        DBG_ASSERTE(RtSerialRtonTag::IsKnownTag(inTag));
		mBuffer->WriteInt8Fixed((int8)inTag);
	}
	inline void WriteKey(const RtSerialRtonKey& inKey)
	{
		if (inKey.IsValid())
		{
			DBG_ASSERTE((!mScopeStack.empty()) && "RtSerialRtonWriter::WriteKey: Attempted to write a key without a valid scope; are you within a BeginDocumentObject/EndDocumentObject block?");
			DBG_ASSERTE((mScopeStack.back() == false) && "RtSerialRtonWriter::WriteKey: Attempted to write a key within an Array scope; use an Object scope if you want to use keys");
			WriteString(NULL, inKey.mString, true); // keys are tracked since they tend to be reused
		}
	}
	inline void PushScope(bool inIsArray)
	{
		mScopeStack.push_back(inIsArray);
	}
	inline void PopScope()
	{
		DBG_ASSERTE((mScopeStack.size() > 0) && "RtSerialRtonWriter::PopScope: Object/Array scope stack underflow");
		mScopeStack.pop_back();
	}

	void WriteTrackedString(const std::string& inStr);
	void WriteTrackedUTF8String(const std::wstring& inStr);

public:
	RtSerialRtonWriter()
	: mTrackedAnsiStringCount(0)
	, mTrackedUTF8StringCount(0)
	, mDoDeleteBuffer(true)
	{
		mBuffer = new RtSerialBuffer;
		mBuffer->SetIsWriting(true);
	}
	RtSerialRtonWriter(uchar* inFixedData, uint32 inFixedDataSize)
	: mTrackedAnsiStringCount(0)
	, mTrackedUTF8StringCount(0)
	, mDoDeleteBuffer(true)
	{
		mBuffer = new RtSerialBuffer(inFixedData, inFixedDataSize);
		mBuffer->SetIsWriting(true);
	}
	RtSerialRtonWriter(RtSerialBuffer* inBuffer)
	: mBuffer(inBuffer)
	, mTrackedAnsiStringCount(0)
	, mTrackedUTF8StringCount(0)
	, mDoDeleteBuffer(false)
	{
		mBuffer->SetIsWriting(true);
	}
	~RtSerialRtonWriter()
	{
		if (mDoDeleteBuffer)
			delete mBuffer;
	}

	inline RtSerialBuffer* GetBuffer() { return mBuffer; }

	void BeginDocumentObject()
	{
		mTrackedAnsiStringMap.clear();
		mTrackedAnsiStringCount = 0;
		mTrackedUTF8StringMap.clear();
		mTrackedUTF8StringCount = 0;

		mBuffer->WriteInt32Fixed(RTSERIAL_RTON_MAGIC_BEGIN);
		mBuffer->WriteInt16Fixed(1); // version
		mBuffer->WriteInt16Fixed(0); // reserved
		PushScope(false); // begin implicit object body (no tag)
	}
	void EndDocumentObject()
	{
		EndObject(); // end the implicit object body (with ending marker)
		DBG_ASSERTE((mScopeStack.empty()) && "RtSerialRtonWriter::EndDocument: Object/Array scope stack not completely cleared");
		mBuffer->WriteInt32Fixed(RTSERIAL_RTON_MAGIC_END);
	}

	inline void BeginObject(const RtSerialRtonKey& inKey)
	{
		WriteKey(inKey);
		WriteTag(RtSerialRtonTag::Object);
		PushScope(false);
	}
	inline void EndObject()
	{
		PopScope();
		WriteTag(RtSerialRtonTag::MarkerObjectEnd);
	}

	inline void BeginArray(const RtSerialRtonKey& inKey, uint32 inArrayCount, RtSerialRtonTag::ETag inTypeTag = RtSerialRtonTag::MarkerArrayTypeVarying)
	{
		WriteKey(inKey);
		WriteTag(RtSerialRtonTag::Array);
		WriteTag(inTypeTag);
		mBuffer->WriteInt32VarU(inArrayCount);
		PushScope(true);
	}
	inline void EndArray()
	{
		PopScope();
		WriteTag(RtSerialRtonTag::MarkerArrayEnd);
	}

	inline void WriteBinaryBlob(const RtSerialRtonKey& inKey, const std::string& inContentType, const uchar* inPtr, uint32 inSizeBytes)
	{
		WriteKey(inKey);
		WriteTag(RtSerialRtonTag::BinaryBlob);
		WriteString(NULL, inContentType, true); // deliberately a fully tagged string (not just mBuffer->WriteString); acts like a key in a kvp
		mBuffer->WriteInt32VarU(inSizeBytes);
		if (inSizeBytes)
			mBuffer->Write(inPtr, inSizeBytes);
	}

	inline void WriteBool(const RtSerialRtonKey& inKey, bool inX)
	{
		WriteKey(inKey);
		WriteTag(inX ? RtSerialRtonTag::BoolTrue : RtSerialRtonTag::BoolFalse);
	}

#define RTSERIALRTONWRITER_WRITEVALUEORZERO(xValue, xNonZeroTag, xWriteMethod, xZeroTag) \
	{ \
		WriteKey(inKey); \
		if (xValue) \
		{ \
			WriteTag(RtSerialRtonTag::xNonZeroTag); \
			mBuffer->xWriteMethod(xValue); \
		} \
		else \
		{ \
			WriteTag(RtSerialRtonTag::xZeroTag); \
		} \
	}
	inline void WriteInt8Fixed(const RtSerialRtonKey& inKey, int8 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, Int8Fixed, WriteInt8Fixed, Int8Zero); }
	inline void WriteUInt8Fixed(const RtSerialRtonKey& inKey, uint8 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, UInt8Fixed, WriteUInt8Fixed, UInt8Zero); }
	inline void WriteInt16Fixed(const RtSerialRtonKey& inKey, int16 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, Int16Fixed, WriteInt16Fixed, Int16Zero); } 
	inline void WriteUInt16Fixed(const RtSerialRtonKey& inKey, uint16 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, UInt16Fixed, WriteUInt16Fixed, UInt16Zero); } 
	inline void WriteInt32Fixed(const RtSerialRtonKey& inKey, int32 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, Int32Fixed, WriteInt32Fixed, Int32Zero); } 
	inline void WriteUInt32Fixed(const RtSerialRtonKey& inKey, uint32 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, UInt32Fixed, WriteUInt32Fixed, UInt32Zero); } 
	inline void WriteInt64Fixed(const RtSerialRtonKey& inKey, int64 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, Int64Fixed, WriteInt64Fixed, Int64Zero); } 
	inline void WriteUInt64Fixed(const RtSerialRtonKey& inKey, uint64 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, UInt64Fixed, WriteUInt64Fixed, UInt64Zero); } 
	inline void WriteFloat(const RtSerialRtonKey& inKey, float inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, Float, WriteFloat, FloatZero); }
	inline void WriteDouble(const RtSerialRtonKey& inKey, double inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, Double, WriteDouble, DoubleZero); }

	inline void WriteInt32VarU(const RtSerialRtonKey& inKey, int32 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, Int32VarU, WriteInt32VarU, Int32Zero); } 
	inline void WriteUInt32VarU(const RtSerialRtonKey& inKey, uint32 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, UInt32VarU, WriteUInt32VarU, UInt32Zero); } 
	inline void WriteInt64VarU(const RtSerialRtonKey& inKey, int64 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, Int64VarU, WriteInt64VarU, Int64Zero); } 
	inline void WriteUInt64VarU(const RtSerialRtonKey& inKey, uint64 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, UInt64VarU, WriteUInt64VarU, UInt64Zero); } 
	inline void WriteInt32VarS(const RtSerialRtonKey& inKey, int32 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, Int32VarS, WriteInt32VarS, Int32Zero); } 
	inline void WriteInt64VarS(const RtSerialRtonKey& inKey, int64 inX) { RTSERIALRTONWRITER_WRITEVALUEORZERO(inX, Int64VarS, WriteInt64VarS, Int64Zero); }

	// general int32/64 writers; chooses Fixed/VarU/VarS depending on value (use these when you're not picky about the specific tag)
	void WriteInt32(const RtSerialRtonKey& inKey, int32 inX);
	void WriteUInt32(const RtSerialRtonKey& inKey, uint32 inX);
	void WriteInt64(const RtSerialRtonKey& inKey, int64 inX);
	void WriteUInt64(const RtSerialRtonKey& inKey, uint64 inX);

	void WriteString(const RtSerialRtonKey& inKey, const std::string& inStr, bool inTracked = false);
	void WriteString(const RtSerialRtonKey& inKey, const char* inStr, bool inTracked = false);
	void WriteUTF8String(const RtSerialRtonKey& inKey, const std::wstring& inStr, bool inTracked = false);
	void WriteUTF8String(const RtSerialRtonKey& inKey, const wchar_t* inStr, bool inTracked = false);

	void WriteRtId(const RtSerialRtonKey& inKey, const RtId& inId);
	void WriteRtId(const RtSerialRtonKey& inKey, const RtId::OfflineId& inOfflineId);

#undef RTSERIALRTONWRITER_WRITEVALUEORZERO

	template <typename T> void Write(const RtSerialRtonKey& inKey, const T& inValue) { TWriter<T>::Write(this, inKey, inValue); }
};

#ifdef HOST_WINDOWS
#define RTSERIAL_RTONWRITER_TYPE_UINT32(xType) template <> class RtSerialRtonWriter::TWriter<xType> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const xType& inValue) { inWriter->WriteUInt32(inKey, inValue); } };
#define RTSERIAL_RTONWRITER_TYPE_SINT32(xType) template <> class RtSerialRtonWriter::TWriter<xType> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const xType& inValue) { inWriter->WriteInt32(inKey, inValue); } };
#else
#define RTSERIAL_RTONWRITER_TYPE_UINT32(xType) template <> class RtSerialRtonWriter::TWriter<xType> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const xType& inValue) { inWriter->WriteUInt32(inKey, static_cast<uint32_t>(inValue)); } };
#define RTSERIAL_RTONWRITER_TYPE_SINT32(xType) template <> class RtSerialRtonWriter::TWriter<xType> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const xType& inValue) { inWriter->WriteInt32(inKey, static_cast<int32_t>(inValue)); } };
#endif

#define RTSERIAL_RTONWRITER_TYPE_UINT64(xType) template <> class RtSerialRtonWriter::TWriter64<xType> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const xType& inValue) { inWriter->WriteUInt64(inKey, inValue); } };
#define RTSERIAL_RTONWRITER_TYPE_SINT64(xType) template <> class RtSerialRtonWriter::TWriter64<xType> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const xType& inValue) { inWriter->WriteInt64(inKey, inValue); } };
RTSERIAL_RTONWRITER_TYPE_SINT32(char);
RTSERIAL_RTONWRITER_TYPE_SINT32(signed char);
RTSERIAL_RTONWRITER_TYPE_UINT32(unsigned char);
RTSERIAL_RTONWRITER_TYPE_SINT32(signed short);
RTSERIAL_RTONWRITER_TYPE_UINT32(unsigned short);
RTSERIAL_RTONWRITER_TYPE_SINT32(signed long);
RTSERIAL_RTONWRITER_TYPE_UINT32(unsigned long);
RTSERIAL_RTONWRITER_TYPE_SINT32(signed int);
RTSERIAL_RTONWRITER_TYPE_UINT32(unsigned int);
RTSERIAL_RTONWRITER_TYPE_UINT32(wchar_t);
RTSERIAL_RTONWRITER_TYPE_SINT64(int64);
RTSERIAL_RTONWRITER_TYPE_UINT64(uint64);
template <> class RtSerialRtonWriter::TWriter<bool> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const bool& inValue) { inWriter->WriteBool(inKey, inValue); } };
template <> class RtSerialRtonWriter::TWriter<float> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const float& inValue) { inWriter->WriteFloat(inKey, inValue); } };
template <> class RtSerialRtonWriter::TWriter<double> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const double& inValue) { inWriter->WriteDouble(inKey, inValue); } };
template <> class RtSerialRtonWriter::TWriter<char*> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const std::string& inValue) { inWriter->WriteString(inKey, inValue); } };
template <> class RtSerialRtonWriter::TWriter<const char*> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const std::string& inValue) { inWriter->WriteString(inKey, inValue); } };
template <> class RtSerialRtonWriter::TWriter<std::string> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const std::string& inValue) { inWriter->WriteString(inKey, inValue); } };
template <> class RtSerialRtonWriter::TWriter<wchar_t*> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const std::wstring& inValue) { inWriter->WriteUTF8String(inKey, inValue); } };
template <> class RtSerialRtonWriter::TWriter<const wchar_t*> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const std::wstring& inValue) { inWriter->WriteUTF8String(inKey, inValue); } };
template <> class RtSerialRtonWriter::TWriter<std::wstring> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const std::wstring& inValue) { inWriter->WriteUTF8String(inKey, inValue); } };
template <> class RtSerialRtonWriter::TWriter<RtId> { public: static void Write(RtSerialRtonWriter* inWriter, const RtSerialRtonKey& inKey, const RtId& inValue) { inWriter->WriteRtId(inKey, inValue); } };

/*
	RtSerialRtonDecodeBuffer
*/
class RtSerialRtonDecodeBuffer
{
protected:

#ifdef HOST_WINDOWS
	typedef std::map<std::string, uint32> DMemStringMap;
	typedef std::map<std::wstring, uint32> DMemWStringMap;
#else
	typedef eastl::hash_map<std::string, uint32, eastl::string_hash<std::string> > DMemStringMap;
    typedef eastl::hash_map<std::wstring, uint32, eastl::string_hash<std::wstring> > DMemWStringMap;
#endif

	RtSerialBuffer mBuffer;
	DMemStringMap mMemStringMap;
	DMemWStringMap mMemWStringMap;

	friend class RtSerialRtonReader;

public:
	RtSerialRtonDecodeBuffer() {}

	inline RtSerialBuffer* GetBuffer() { return &mBuffer; } // use caution with this; don't try to build yet another decode buffer with it, for example

	bool Build(const uchar* inPtr, uint32 inSizeBytes);
};

/*
	RtSerialRtonReader
*/
class RtSerialRtonReader
{
public:
	template <typename T> class TReader { public: static T Read(RtSerialRtonReader* inReader, const RtSerialRtonKey& inKey); };

protected:
	typedef uint32 HKey;
	typedef uint32 HValue;

public:
	class Key;
	class Value;
	friend class Key;
	friend class Value;

protected:
	struct ReaderScope
	{
		HValue mValue;
		int32 mCurArrayIndex; // -1 when in object scope

		ReaderScope(const HValue& inValue, int32 inCurArrayIndex)
		: mValue(inValue)
		, mCurArrayIndex(inCurArrayIndex)
		{}
	};

	RtSerialRtonDecodeBuffer* mDecodeBuffer;
	bool mDoDeleteBuffer;
	HValue mRootNode;
	std::vector<ReaderScope> mScopeStack;

	bool InitDecodeBuffer();
	RtSerialRtonTag::ETag PeekTag();

	// get the name of a key, or its associated value
	const char* GetKeyName(HKey inKey);
	HValue GetKeyValue(HKey inKey);

	// get the underlying tag of a value, to know how it's stored in the decode buffer
	RtSerialRtonTag::ETag GetValueTag(HValue inValue);
	
	// leaf value accessors (conversion friendly, within reason)
	bool GetBool(HValue inValue, bool inDefaultValue = false);
	int32 GetInt32(HValue inValue, int32 inDefaultValue = 0);
	uint32 GetUInt32(HValue inValue, uint32 inDefaultValue = 0);
	int64 GetInt64(HValue inValue, int64 inDefaultValue = 0);
	uint64 GetUInt64(HValue inValue, uint64 inDefaultValue = 0);
	float GetFloat(HValue inValue, float inDefaultValue = 0.f);
	double GetDouble(HValue inValue, double inDefaultValue = 0.0);
	const char* GetStringDirect(HValue inValue); // no conversions performed; returns null if value is not actually a string
	std::string GetString(HValue inValue, const std::string& inDefaultValue = "");
	const wchar_t* GetWStringDirect(HValue inValue); // no conversions performed; returns null if value is not actually a wstring
	std::wstring GetWString(HValue inValue, const std::wstring& inDefaultValue = L"");
	RtId GetRtId(HValue inValue, const RtId& inDefaultValue = RtId()); // limited conversions (must be a non-lossy conversion, such as from a uint64 or a string)
	
	// leaf value accessor to RtInvokeVariant; will attempt to use variant type compatible with underlying tag
	bool GetInvokeVariant(HValue inValue, RtInvokeVariant& outVariant);
	
	// binary blob leaf accessor; if outBuffer is non-null it will be replaced with a fixed buffer pointing to the existing content within the decode buffer (not a copy, so be careful)
	bool GetBinaryBlob(HValue inValue, RtSerialBuffer* outBuffer, std::string& outContentType);

	bool GetValueIsObject(HValue inValue);
	bool GetValueIsArray(HValue inValue);
	inline bool GetValueIsContainer(HValue inValue) { return GetValueIsObject(inValue) || GetValueIsArray(inValue); }

	HKey GetFirstChild(HValue inObject);
	HKey GetNextSibling(HKey inKey);
	HKey GetChildNamed(HValue inObject, const std::string& inName);
	
	uint32 GetArrayCount(HValue inArray);
	HValue GetArrayIndexValue(HValue inArray, uint32 inIndex);

	HValue GetInnerScopeValue(const RtSerialRtonKey& inKey)
	{
		DBG_ASSERTE(!mScopeStack.empty());
        if (mScopeStack.empty())
        {
            //CrashTracking::Log(StrFormat("GetInnerScopeValue has no scope stack. key: %s", inKey.mString.c_str()));
            return 0;
        }
		ReaderScope* rs = &mScopeStack.back();
		if (rs->mCurArrayIndex >= 0)
		{
			// array scope
			DBG_ASSERTE(!inKey.IsValid() && "RtSerialRtonReader::GetInnerScopeValue: Keys immediately within an array scope must be null");
			HValue value = GetArrayIndexValue(rs->mValue, rs->mCurArrayIndex);
			++rs->mCurArrayIndex;
			return value;
		}
		else
		{
			// object scope
			DBG_ASSERTE(inKey.IsValid() && "RtSerialRtonReader::GetInnerScopeValue: Keys immediately within an object scope must be non-empty");
			HKey key = GetChildNamed(rs->mValue, inKey.mString);
			if (!key)
				return 0;
			return GetKeyValue(key);
		}
	}

public:
	RtSerialRtonReader(uchar* inFixedData, uint32 inFixedDataSize);
	RtSerialRtonReader(RtSerialBuffer* inBuffer);
	RtSerialRtonReader(RtSerialRtonDecodeBuffer* inDecodeBuffer);
	~RtSerialRtonReader();

	inline RtSerialBuffer* GetBuffer() { return &mDecodeBuffer->mBuffer; }

	inline Value GetDocumentObjectScope() const; // get the DOM-style document root object value
	
	inline Value GetCurrentScope() const; // get the DOM-style object value for the current Begin/EndDocumentObject, Begin/EndObject, or Begin/EndArray scope
	inline uint32 GetCurrentScopeArrayIndex() const; // within a Begin/EndArray scope, gets the current array index that will be used for the next element read; returns -1 for non-array scopes

	bool BeginDocumentObject()
	{
		DBG_ASSERTE(mScopeStack.empty() && "RtSerialRtonReader::BeginDocumentObject: Scope stack is not empty; document object should always be the outermost scope");
		HValue value = mRootNode;
		if (!value)
			return false;
		mScopeStack.push_back(ReaderScope(value, -1));
		return true;
	}
	void EndDocumentObject()
	{
		DBG_ASSERTE((mScopeStack.size()==1) && "RtSerialRtonReader::EndDocumentObject: Scope stack has more than one scope; document object should always be the outermost scope");
		mScopeStack.pop_back();
	}

	bool BeginObject(const RtSerialRtonKey& inKey)
	{
		DBG_ASSERTE(!mScopeStack.empty() && "RtSerialRtonReader::BeginObject: Scope stack is empty; make sure you are in a BeginDocumentObject/EndDocumentObject block");
		HValue value = GetInnerScopeValue(inKey);
		if (!value)
			return false;
		if (!GetValueIsObject(value))
			return false;
		mScopeStack.push_back(ReaderScope(value, -1));
		return true;
	}
	void EndObject()
	{
		DBG_ASSERTE(!mScopeStack.empty() && "RtSerialRtonReader::EndObject: Scope stack is empty; check for matching BeginObject call");
		mScopeStack.pop_back();
	}
	bool BeginArray(const RtSerialRtonKey& inKey, uint32& outArrayCount)
	{
		DBG_ASSERTE(!mScopeStack.empty() && "RtSerialRtonReader::BeginArray: Scope stack is empty; make sure you are in a BeginDocumentObject/EndDocumentObject block");
		outArrayCount = 0;
		HValue value = GetInnerScopeValue(inKey);
		if (!value)
			return false;
		if (!GetValueIsArray(value))
			return false;
		mScopeStack.push_back(ReaderScope(value, 0));
		outArrayCount = GetArrayCount(value);
		return true;
	}
	void EndArray()
	{
		DBG_ASSERTE(!mScopeStack.empty() && "RtSerialRtonReader::EndArray: Scope stack is empty; check for matching BeginArray call");
		mScopeStack.pop_back();
	}

#define RTSERIALRTONREADER_READ_DEFINE(xName, xType, xArgType, xValueGetMethod, xDefault) \
	xType xName(const RtSerialRtonKey& inKey, xArgType inDefaultValue = xDefault) \
	{ \
		HValue value = GetInnerScopeValue(inKey); \
		return xValueGetMethod(value, inDefaultValue); \
	}
#define RTSERIALRTONREADER_READ_DEFINE_NODEFAULT(xName, xType, xValueGetMethod) \
	xType xName(const RtSerialRtonKey& inKey) \
	{ \
		HValue value = GetInnerScopeValue(inKey); \
		return xValueGetMethod(value); \
	}

	RTSERIALRTONREADER_READ_DEFINE(ReadBool, bool, bool, GetBool, false);
	RTSERIALRTONREADER_READ_DEFINE(ReadInt32, int32, int32, GetInt32, 0);
	RTSERIALRTONREADER_READ_DEFINE(ReadUInt32, uint32, uint32, GetUInt32, 0);
	RTSERIALRTONREADER_READ_DEFINE(ReadInt64, int64, int64, GetInt64, 0);
	RTSERIALRTONREADER_READ_DEFINE(ReadUInt64, uint64, uint64, GetUInt64, 0);
	RTSERIALRTONREADER_READ_DEFINE(ReadFloat, float, float, GetFloat, 0.f);
	RTSERIALRTONREADER_READ_DEFINE(ReadDouble, double, double, GetDouble, 0.0);
	RTSERIALRTONREADER_READ_DEFINE(ReadRtId, RtId, const RtId&, GetRtId, RtId());
	RTSERIALRTONREADER_READ_DEFINE_NODEFAULT(ReadStringDirect, const char*, GetStringDirect);
	RTSERIALRTONREADER_READ_DEFINE(ReadString, std::string, const std::string&, GetString, "");
	RTSERIALRTONREADER_READ_DEFINE_NODEFAULT(ReadWStringDirect, const wchar_t*, GetWStringDirect);
	RTSERIALRTONREADER_READ_DEFINE(ReadWString, std::wstring, const std::wstring&, GetWString, L"");
	
#undef RTSERIALRTONREADER_READ_DEFINE

	template <typename T> T Read(const RtSerialRtonKey& inKey) { return TReader<T>::Read(this, inKey); }
	template <typename T> class TReader64 { public: static T Read(RtSerialRtonReader* inReader, const RtSerialRtonKey& inKey); };

public:
	class Value
	{
	protected:
		RtSerialRtonReader* mReader;
		HValue mValue;
	public:
		Value(RtSerialRtonReader* inReader, HValue inValue)
		: mReader(inReader)
		, mValue(inValue)
		{}

		inline bool IsValid() { return mValue != 0; }
		inline operator bool () const { return mValue != 0; }
		inline bool operator ! () const { return mValue == 0; }

		inline RtSerialRtonTag::ETag GetTag() const { return mReader->GetValueTag(mValue); }
	
		inline bool GetBool(bool inDefaultValue = false) const { return mReader->GetBool(mValue, inDefaultValue); }
		inline int32 GetInt32(int32 inDefaultValue = 0) const { return mReader->GetInt32(mValue, inDefaultValue); }
		inline uint32 GetUInt32(uint32 inDefaultValue = 0) const { return mReader->GetUInt32(mValue, inDefaultValue); }
		inline int64 GetInt64(int64 inDefaultValue = 0) const { return mReader->GetInt64(mValue, inDefaultValue); }
		inline uint64 GetUInt64(uint64 inDefaultValue = 0) const { return mReader->GetUInt64(mValue, inDefaultValue); }
		inline float GetFloat(float inDefaultValue = 0.f) const { return mReader->GetFloat(mValue, inDefaultValue); }
		inline double GetDouble(double inDefaultValue = 0.0) const { return mReader->GetDouble(mValue, inDefaultValue); }
		inline const char* GetStringDirect() const { return mReader->GetStringDirect(mValue); }
		inline std::string GetString(const std::string& inDefaultValue = "") const { return mReader->GetString(mValue, inDefaultValue); }
		inline const wchar_t* GetWStringDirect() const { return mReader->GetWStringDirect(mValue); }
		inline std::wstring GetWString(const std::wstring& inDefaultValue = L"") const { return mReader->GetWString(mValue, inDefaultValue); }
		inline RtId GetRtId(const RtId& inDefaultValue = RtId()) const { return mReader->GetRtId(mValue, inDefaultValue); }
	
		inline bool GetInvokeVariant(RtInvokeVariant& outVariant) const
		{
			return mReader->GetInvokeVariant(mValue, outVariant);
		}
		inline bool GetBinaryBlob(RtSerialBuffer* outBuffer, std::string& outContentType) const
		{
			return mReader->GetBinaryBlob(mValue, outBuffer, outContentType);
		}

		inline bool IsObject() const { return mReader->GetValueIsObject(mValue); }
		inline bool IsArray() const { return mReader->GetValueIsArray(mValue); }
		// [PVZ CHANGE BEGIN] Missed a 'return'
		inline bool IsContainer() const { return mReader->GetValueIsContainer(mValue); }
		// [PVZ CHANGE END]

		inline Key GetFirstChild() const;
		inline Key GetChildNamed(const std::string& inName) const;
		
		inline uint32 GetArrayCount() const { return mReader->GetArrayCount(mValue); }
		inline Value GetArrayIndexValue(uint32 inIndex) const { return Value(mReader, mReader->GetArrayIndexValue(mValue, inIndex)); }
	};
	class Key
	{
	protected:
		RtSerialRtonReader* mReader;
		HKey mKey;
	public:
		Key(RtSerialRtonReader* inReader, HKey inKey)
		: mReader(inReader)
		, mKey(inKey)
		{}

		inline bool IsValid() { return mKey != 0; }
		inline operator bool () const { return mKey != 0; }
		inline bool operator ! () const { return mKey == 0; }

		inline const char* GetName() const { return mReader->GetKeyName(mKey); }
		
		inline Key GetNextSibling() const { return Key(mReader, mReader->GetNextSibling(mKey)); }
	
		inline Value GetValue() const { return Value(mReader, mReader->GetKeyValue(mKey)); }
	};
};
inline RtSerialRtonReader::Value RtSerialRtonReader::GetDocumentObjectScope() const
{
	return Value(const_cast<RtSerialRtonReader*>(this), mRootNode);
}
inline RtSerialRtonReader::Value RtSerialRtonReader::GetCurrentScope() const
{
	if (!mScopeStack.empty())
		return Value(const_cast<RtSerialRtonReader*>(this), mScopeStack.back().mValue);
	return Value(const_cast<RtSerialRtonReader*>(this), 0);
}
inline uint32 RtSerialRtonReader::GetCurrentScopeArrayIndex() const
{
	if (!mScopeStack.empty())
		return Value(const_cast<RtSerialRtonReader*>(this), mScopeStack.back().mCurArrayIndex);
	return -1;
}
inline RtSerialRtonReader::Key RtSerialRtonReader::Value::GetFirstChild() const
{
	return Key(mReader, mReader->GetFirstChild(mValue));
}
inline RtSerialRtonReader::Key RtSerialRtonReader::Value::GetChildNamed(const std::string& inName) const
{
	return Key(mReader, mReader->GetChildNamed(mValue, inName));
}

#define RTSERIAL_RTONREADER_TYPE_UINT32(xType) template <> class RtSerialRtonReader::TReader<xType> { public: static xType Read(RtSerialRtonReader* inReader, const RtSerialRtonKey& inKey) { return (xType)inReader->ReadUInt32(inKey); } };
#define RTSERIAL_RTONREADER_TYPE_SINT32(xType) template <> class RtSerialRtonReader::TReader<xType> { public: static xType Read(RtSerialRtonReader* inReader, const RtSerialRtonKey& inKey) { return (xType)inReader->ReadInt32(inKey); } };
#define RTSERIAL_RTONREADER_TYPE_UINT64(xType) template <> class RtSerialRtonReader::TReader64<xType> { public: static xType Read(RtSerialRtonReader* inReader, const RtSerialRtonKey& inKey) { return (xType)inReader->ReadUInt64(inKey); } };
#define RTSERIAL_RTONREADER_TYPE_SINT64(xType) template <> class RtSerialRtonReader::TReader64<xType> { public: static xType Read(RtSerialRtonReader* inReader, const RtSerialRtonKey& inKey) { return (xType)inReader->ReadInt64(inKey); } };
RTSERIAL_RTONREADER_TYPE_SINT32(char);
RTSERIAL_RTONREADER_TYPE_SINT32(signed char);
RTSERIAL_RTONREADER_TYPE_UINT32(unsigned char);
RTSERIAL_RTONREADER_TYPE_SINT32(signed short);
RTSERIAL_RTONREADER_TYPE_UINT32(unsigned short);
RTSERIAL_RTONREADER_TYPE_SINT32(signed long);
RTSERIAL_RTONREADER_TYPE_UINT32(unsigned long);
RTSERIAL_RTONREADER_TYPE_SINT32(signed int);
RTSERIAL_RTONREADER_TYPE_UINT32(unsigned int);
RTSERIAL_RTONREADER_TYPE_UINT32(wchar_t);
RTSERIAL_RTONREADER_TYPE_SINT64(int64);
RTSERIAL_RTONREADER_TYPE_UINT64(uint64);
template <> class RtSerialRtonReader::TReader<bool> { public: static bool Read(RtSerialRtonReader* inReader, const RtSerialRtonKey& inKey) { return inReader->ReadBool(inKey); } };
template <> class RtSerialRtonReader::TReader<float> { public: static float Read(RtSerialRtonReader* inReader, const RtSerialRtonKey& inKey) { return inReader->ReadFloat(inKey); } };
template <> class RtSerialRtonReader::TReader<double> { public: static double Read(RtSerialRtonReader* inReader, const RtSerialRtonKey& inKey) { return inReader->ReadDouble(inKey); } };
template <> class RtSerialRtonReader::TReader<std::string> { public: static std::string Read(RtSerialRtonReader* inReader, const RtSerialRtonKey& inKey) { return inReader->ReadString(inKey); } };
template <> class RtSerialRtonReader::TReader<std::wstring> { public: static std::wstring Read(RtSerialRtonReader* inReader, const RtSerialRtonKey& inKey) { return inReader->ReadWString(inKey); } };
template <> class RtSerialRtonReader::TReader<RtId> { public: static RtId Read(RtSerialRtonReader* inReader, const RtSerialRtonKey& inKey) { return inReader->ReadRtId(inKey); } };

/*
	RtSerialRtonSync
*/
class RtSerialRtonSync
{
protected:
	RtSerialRtonReader* mReader;
	RtSerialRtonWriter* mWriter;
	bool mSyncReading;

public:
	RtSerialRtonSync(RtSerialRtonReader* inReader, RtSerialRtonWriter* inWriter)
	: mReader(inReader)
	, mWriter(inWriter)
	, mSyncReading(true)
	{
		if (mWriter && !mReader)
			mSyncReading = false;
	}
	RtSerialRtonSync(RtSerialRtonReader* inReader)
	: mReader(inReader)
	, mWriter(NULL)
	, mSyncReading(true)
	{}
	RtSerialRtonSync(RtSerialRtonWriter* inWriter)
	: mReader(NULL)
	, mWriter(inWriter)
	, mSyncReading(false)
	{}

	inline void SetIsReading(bool inIsReading) { mSyncReading = inIsReading; }
	inline void SetIsWriting(bool inIsWriting) { mSyncReading = !inIsWriting; }
	inline bool IsReading() { return mSyncReading; }
	inline bool IsWriting() { return !mSyncReading; }

	inline RtSerialRtonReader* GetReader() { return mReader; }
	inline RtSerialRtonWriter* GetWriter() { return mWriter; }

	inline bool SyncBeginDocumentObject()
	{
		if (IsReading())
		{
			return mReader->BeginDocumentObject();
		}
		else
		{
			mWriter->BeginDocumentObject();
			return true;
		}
	}
	inline void SyncEndDocumentObject()
	{
		if (IsReading())
		{
			mReader->EndDocumentObject();
		}
		else
		{
			mWriter->EndDocumentObject();
		}
	}

	inline bool SyncBeginObject(const RtSerialRtonKey& inKey)
	{
		if (IsReading())
		{
			return mReader->BeginObject(inKey);
		}
		else
		{
			mWriter->BeginObject(inKey);
			return true;
		}
	}
	inline void SyncEndObject()
	{
		if (IsReading())
		{
			mReader->EndObject();
		}
		else
		{
			mWriter->EndObject();
		}
	}
	inline bool SyncBeginArray(const RtSerialRtonKey& inKey, uint32& ioArrayCount)
	{
		if (IsReading())
		{
			return mReader->BeginArray(inKey, ioArrayCount);
		}
		else
		{
			mWriter->BeginArray(inKey, ioArrayCount);
			return true;
		}
	}
	inline void SyncEndArray()
	{
		if (IsReading())
		{
			mReader->EndArray();
		}
		else
		{
			mWriter->EndArray();
		}
	}

#define RTSERIALRTONSYNC_SYNC_DEFINE(xName, xType, xReaderMethod, xWriterMethod) \
	inline void xName(const RtSerialRtonKey& inKey, xType& ioValue) \
	{ \
		if (IsReading()) \
		{ \
			ioValue = mReader->xReaderMethod(inKey); \
		} \
		else \
		{ \
			mWriter->xWriterMethod(inKey, ioValue); \
		} \
	}

	RTSERIALRTONSYNC_SYNC_DEFINE(SyncBool, bool, ReadBool, WriteBool);
	RTSERIALRTONSYNC_SYNC_DEFINE(SyncInt32, int32, ReadInt32, WriteInt32);
	RTSERIALRTONSYNC_SYNC_DEFINE(SyncUInt32, uint32, ReadUInt32, WriteUInt32);
	RTSERIALRTONSYNC_SYNC_DEFINE(SyncInt64, int64, ReadInt64, WriteInt64);
	RTSERIALRTONSYNC_SYNC_DEFINE(SyncUInt64, uint64, ReadUInt64, WriteUInt64);
	RTSERIALRTONSYNC_SYNC_DEFINE(SyncFloat, float, ReadFloat, WriteFloat);
	RTSERIALRTONSYNC_SYNC_DEFINE(SyncDouble, double, ReadDouble, WriteDouble);
	RTSERIALRTONSYNC_SYNC_DEFINE(SyncRtId, RtId, ReadRtId, WriteRtId);

#undef RTSERIALRTONSYNC_SYNC_DEFINE

	inline void SyncString(const RtSerialRtonKey& inKey, std::string& ioValue)
	{
		if (IsReading())
		{
			ioValue = mReader->ReadStringDirect(inKey);
		}
		else
		{
			mWriter->WriteString(inKey, ioValue, true);
		}
	}
	inline void SyncUTF8String(const RtSerialRtonKey& inKey, std::wstring& ioValue)
	{
		if (IsReading())
		{
			ioValue = mReader->ReadWStringDirect(inKey);
		}
		else
		{
			mWriter->WriteUTF8String(inKey, ioValue, true);
		}
	}
	template <typename T> inline void SyncUInt32T(const RtSerialRtonKey& inKey, T& ioValue)
	{
		if (IsReading())
		{
			ioValue = (T)mReader->ReadUInt32(inKey);
		}
		else
		{
			mWriter->WriteUInt32(inKey, (uint32)ioValue);
		}
	}
};

/*
	RtSerializeContext
*/
class RtSerializeContext
{
public:
	enum EContextType
	{
		CONTEXT_File, // serialization to/from file storage (default)
		CONTEXT_Network, // serialization to/from network
	};

protected:
	EContextType mContextType;
	RtSerialRtonSync* mSync;
	RtSerialRtonKey mKey;
	std::vector<std::string> mMemberWildcards;

public:
	RtSerializeContext(RtSerialRtonSync* inSync, const RtSerialRtonKey& inKey, EContextType inContextType = CONTEXT_File)
	: mContextType(inContextType)
	, mSync(inSync)
	, mKey(inKey)
	{}

	inline EContextType GetContextType() const { return mContextType; }
	inline RtSerialRtonSync* GetSync() const { return mSync; }
	inline const RtSerialRtonKey& GetKey() const { return mKey; }
	inline const std::vector<std::string>& GetMemberWildcards() const { return mMemberWildcards; }
	inline std::vector<std::string>& GetMutableMemberWildcards() { return mMemberWildcards; }
};

/*
	RtSerialCommand
*/
class RtSerialCommand
{
public:
	uint32 mArgCount; // number of arguments available via mArgs
	RtSerialRtonReader* mArgs; // Rton reader positioned inside array of command arguments; null if no arguments are present
	std::string mArgKey; // Key that should be used for the first argument into the function (only applicable for single-argument "getters")
	RtSerialRtonWriter* mReturns; // Rton writer that accepts return values, if any (enclosing object scope is in place, so keys should be used)
	std::string mReturnKey; // Key that should be used for the normal return value of the function, if applicable

	RtSerialCommand(uint32 inArgCount, RtSerialRtonReader* inArgs, RtSerialRtonWriter* inReturns, const std::string& inArgKey = "", const std::string& inReturnKey = "*")
	: mArgCount(inArgCount)
	, mArgs(inArgs)
	, mArgKey(inArgKey)
	, mReturns(inReturns)
	, mReturnKey(inReturnKey)
	{}
};

namespace RtSerial
{
	bool RtonToJson(const uchar* inPtr, uint32 inSizeBytes, std::string& outJson, bool inShouldOutputNewLines = true);
	bool JsonToRton(const char* inJson, RtSerialRtonWriter& outRton, std::string& outErrorString);
}

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
//**    END HEADER RTSERIAL.H
//**
//****************************************************************************
#endif // __RTSERIAL_H__
