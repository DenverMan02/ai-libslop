#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <string>
#include "Common.h"

#include "SexyMatrix.h"
#include "Point.h"
#include "SexyCoords.h" //to handle the inlines defined in SexyVector which would otherwise cause warnings

namespace Sexy
{

typedef std::vector<uchar> ByteVector;

class Buffer
{
public:
	ByteVector				mData;
	int						mDataBitSize;
	mutable int				mReadBitPos;
	mutable int				mWriteBitPos;	

public:
	Buffer();
	virtual ~Buffer();
			
	void					SeekFront() const;
	void					Clear();

	void					Reserve(uint32 bytes);
	void					Resize(uint32 bytes);
	void					ResizeNonDestructive(size_t bytes);

	void					FromWebString(const std::string& theString);
	void					WriteByte(uchar theByte);
	void					WriteNumBits(int theNum, int theBits);
	static int				GetBitsRequired(int theNum, bool isSigned);
	void					WriteBoolean(bool theBool);
	void					WriteShort(short theShort);
	void					WriteInt(int theInt);
	void					WriteFloat(float theFloat);
	void					WriteDouble(double theDouble);
	void					WriteTransform2D(SexyTransform2D theTrans);
	void					WriteFPoint(FPoint thePoint);
	void					WriteString(const std::string& theString);
	void					WriteUTF8String(const std::wstring& theString);
	void					WriteSexyString(const SexyString &theString);
	void					WriteLine(const std::string& theString);	
	void					WriteBuffer(const ByteVector& theBuffer);
	void					WriteBuffer(const Buffer& theBuffer);
	void					WriteBytes(const uchar* theByte, size_t theCount);
	void					SetData(const ByteVector& theBuffer);
	void					SetData(const uchar* thePtr, int theCount);

	std::string				ToWebString() const;
	std::wstring			UTF8ToWideString() const;
	uchar					ReadByte() const;
	int						ReadNumBits(int theBits, bool isSigned) const;
	bool					ReadBoolean() const;
	short					ReadShort() const;
	int						ReadInt() const;
	float					ReadFloat() const;
	double					ReadDouble() const;
	SexyTransform2D			ReadTransform2D() const;
	FPoint					ReadFPoint() const;
	std::string				ReadString() const;	
	std::wstring			ReadUTF8String() const;
    std::wstring			ReadUTF8Line() const;   //PVZ2_CHINESE add.
	SexyString				ReadSexyString() const;
	std::string				ReadLine() const;
	void					ReadBytes(uchar* theData, int theLen) const;
	void					ReadBuffer(ByteVector* theByteVector) const;
	void					ReadBuffer(Buffer* theBuffer) const;


	//prime compatible types for consistency
	void					WriteInt8(int8 theInt8);
	void					WriteInt16(int16 theInt16);
	void					WriteInt32(int32 theInt32);
	void					WriteInt64(int64 theInt64);

	int8					ReadInt8() const;
	int16					ReadInt16() const;
	int32					ReadInt32() const;
	int64					ReadInt64() const;

	// base-128 varints	
	// unsigned encoding (negative values will be encoded unsigned and thus be quite large, not recommended if negatives are common)
	void					WriteBase128VarIntU32(int32 theInt32);
	void					WriteBase128VarIntU64(int64 theInt64);
	int32					ReadBase128VarIntU32() const;
	int64					ReadBase128VarIntU64() const;
	// signed encoding (zigzag encoding, both positive and negative values have equal cost and scale up in length evenly)
	void					WriteBase128VarIntS32(int32 theInt32);
	void					WriteBase128VarIntS64(int64 theInt64);
	int32					ReadBase128VarIntS32() const;
	int64					ReadBase128VarIntS64() const;

	uchar*					GetDataPtr();
	const uchar*			GetDataPtr() const;
	int						GetDataLen() const;	
	int						GetDataLenBits() const;
	ulong					GetCRC32(ulong theSeed = 0) const;

	bool					AtEnd() const;
	bool					PastEnd() const;
	int						GetBitsAvailable() const;
	int						GetBytesAvailable() const;
};

}

#endif //__BUFFER_H__
