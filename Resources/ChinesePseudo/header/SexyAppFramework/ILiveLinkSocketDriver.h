#ifndef __SEXYAPPFRAMEWORK_ILIVELINKSOCKETDRIVER_H__
#define __SEXYAPPFRAMEWORK_ILIVELINKSOCKETDRIVER_H__

#include "Common.h"

#if SEXY_IS_LIVELINK_ENABLED

#include "CircularBuffer.h"

namespace Sexy
{

class LiveLinkEndPoint
{
public:
	virtual bool IsNetAddress() const
	{
		return false;
	}
};

//--------------------------------------------------------------------------
// Struct NetAddress declaration.

class NetAddress : public LiveLinkEndPoint
{
public:
	uint32 Host;
	uint16 Port;

	virtual bool IsNetAddress() const
	{
		return true;
	}

	NetAddress(uint32 inHost = 0, uint16 inPort = 0)
	{
		Host = inHost;
		Port = inPort;
	}
};

//--------------------------------------------------------------------------
// ILiveLinkSocket

class ILiveLinkSocket
{
public:

	//
	// create
	//
	virtual bool CreateServer(const LiveLinkEndPoint& inEndPoint) = 0;
	virtual bool CreateClient(const LiveLinkEndPoint& inEndPoint) = 0;

	//
	// destroy
	//
	virtual ~ILiveLinkSocket() 
	{
	}

	virtual void Close() = 0;

	//
	// listen operations
	//
	virtual bool Listen() = 0;
	virtual ILiveLinkSocket* Accept() = 0;

	//
	// query
	//
	virtual bool IsValid() const = 0;
	virtual bool IsConnected() const = 0;
	virtual bool IsListening() const = 0;

	//
	// transfer
	//
	virtual int32 Send(const void* inDataToSend, int32 inSizeBytes) = 0;
	virtual int32 Send(CircularBuffer& ioBuffer) = 0;
	virtual int32 Receive(void* outReceiveBuffer, int32 inBufferSizeBytes) = 0;
	virtual int32 Receive(CircularBuffer& ioBuffer) = 0;
};


//--------------------------------------------------------------------------
// ILiveLinkSocketDriver

class ILiveLinkSocketDriver
{
public:
	virtual ~ILiveLinkSocketDriver() 
	{
	}

	static ILiveLinkSocketDriver* CreateLiveLinkSocketDriver();


	virtual ILiveLinkSocket* CreateLiveLinkSocket() = 0;
};

} // namespace Sexy


#endif // SEXY_IS_LIVELINK_ENABLED

//--------------------------------------------------------------------------

#endif // __SEXYAPPFRAMEWORK_ILIVELINKSOCKETDRIVER_H__

//-----------------------------------EOF!-----------------------------------
