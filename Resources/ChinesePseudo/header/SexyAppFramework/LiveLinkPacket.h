#ifndef __SEXYAPPFRAMEWORK_PACKETS_H__
#define __SEXYAPPFRAMEWORK_PACKETS_H__

#include "Common.h"

#if SEXY_IS_LIVELINK_ENABLED

#include "RtObject.h"
#include "RtSerial.h"


namespace Sexy
{

// Order these enums such that channel types that should have a higher 
// priority should be at the top. All packets in ealier channel types
// will be processed before packets in channel types that are later.
enum ChannelType
{
	SEXY_ENUM_BEGIN(ChannelType_),
	ChannelType_HiPri,
	ChannelType_LoPri,
	ChannelType_LargeDataTransfer,
	SEXY_ENUM_END(ChannelType_)
};

SEXY_ENUM_MAKE_BIT_OPERATORS(ChannelType);
SEXY_ENUM_MAKE_MATH_OPERATORS(ChannelType);


class LiveLinkPacket;

class LiveLinkPacketMetaClass : public RtClass
{
protected:
	int32		mPacketType;
	ChannelType mChannelType;

	std::string mPacketTypeStr;

public:
	RT_CLASS_DEFINE(LiveLinkPacketMetaClass, RtClass, RtClass) {}

	Event1<const LiveLinkPacket&> OnPacketReceived; // Event

	LiveLinkPacketMetaClass()
	{
		mPacketType = 0x00000000;
		mChannelType = ChannelType_LoPri;
	}

	// $$ (avy) Move this to be with String util functions.
	static std::string FourCCToString(int32 inFourCC)
	{
		char* fourCCChars = reinterpret_cast<char*>(&inFourCC);
		char typeStr[] = { fourCCChars[0], fourCCChars[1], fourCCChars[2], fourCCChars[3], '\0' };
		return typeStr; 
	}

	inline int32 GetPacketType() { return mPacketType; }
	void SetPacketType(int32 inPacketType);

	inline const std::string& GetPacketTypeStr() const { return mPacketTypeStr; }

	inline ChannelType GetChannelType() { return mChannelType; }
	inline void SetChannelType(ChannelType inChannelType) { mChannelType = inChannelType; }
	
private:
};


class LiveLinkPacket : public RtObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(LiveLinkPacket, RtObject, LiveLinkPacketMetaClass)
	{
		StaticGetClass()->SetPacketType(0);
		StaticGetClass()->SetChannelType(ChannelType_LoPri);
	}

	LiveLinkPacket()
	{
        for (;;) 
        { 
            bool x = (GetClass()->IsA<LiveLinkPacketMetaClass>()); 
            if (!x) 
            { 
                SEXY_ERROR("Assert triggered for expression: %s", "GetClass()->IsA<LiveLinkPacketMetaClass>()"); 
                SEXY_ERROR("Classes inhieriting from LiveLinkPacket, must have LiveLinkPacketMetaClass as its meta class.") 
                assert(x); 
            }
            break; 
        }
        
		SEXY_ASSERTM(GetClass()->IsA<LiveLinkPacketMetaClass>(), "Classes inhieriting from LiveLinkPacket, must have LiveLinkPacketMetaClass as its meta class.");
	}

	int32				GetPacketType() const { return GetClass()->Cast<LiveLinkPacketMetaClass>()->GetPacketType(); }
	int32				GetChannelType() const { return GetClass()->Cast<LiveLinkPacketMetaClass>()->GetChannelType(); }

	const std::string&	GetPacketTypeStr() const  { return GetClass()->Cast<LiveLinkPacketMetaClass>()->GetPacketTypeStr(); }


	virtual bool Send(bool inShouldWaitUtilSent = false) const;
	virtual bool Read(uint8* inData, int32 inSizeBytes);

protected:
	virtual bool SyncPayload(RtSerialBuffer& inSerialBuffer) { return false; }
};


} // namespace Sexy

#endif // SEXY_IS_LIVELINK_ENABLED

//--------------------------------------------------------------------------

#endif // __SEXYAPPFRAMEWORK_PACKETS_H__

//-----------------------------------EOF!-----------------------------------