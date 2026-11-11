#ifndef __SEXYAPPFRAMEWORK_BSDLIVELINKSOCKETDRIVER_H__
#define __SEXYAPPFRAMEWORK_BSDLIVELINKSOCKETDRIVER_H__

#include "ILiveLinkSocketDriver.h"

#if SEXY_IS_LIVELINK_ENABLED

namespace Sexy
{

//--------------------------------------------------------------------------
// BSDLiveLinkSocket

class BSDLiveLinkSocket : public ILiveLinkSocket
{
public:
	virtual ~BSDLiveLinkSocket();

	//
	// create
	//
	virtual bool CreateServer(const LiveLinkEndPoint& inEndPoint); // override
	virtual bool CreateClient(const LiveLinkEndPoint& inEndPoint); // override

	//
	// destroy
	//
	virtual void				Close(); // override

	//
	// listen operations
	//
	virtual bool				Listen(); // override
	virtual ILiveLinkSocket*	Accept(); // override

	//
	// query
	//
	virtual bool				IsValid() const; // override
	virtual bool				IsConnected() const; // override
	virtual bool				IsListening() const; // override

	//
	// transfer
	//
	virtual int32				Send(const void* inDataToSend, int32 inSizeBytes); // override
	virtual int32				Send(CircularBuffer& ioBuffer); // override
	virtual int32				Receive(void* outReceiveBuffer, int32 inBufferSizeBytes); // override
	virtual int32				Receive(CircularBuffer& ioBuffer); // override

protected:
	friend class BSDLiveLinkSocketDriver;

	// protected constructors/static-factory-methods so that only BSDLiveLinkSocketDriver can create instances.
	BSDLiveLinkSocket(); 
	
private:
	typedef int32 SOCKET;

	static SOCKET CreateGenericSocket();

	SOCKET	mSocket;
	bool	mIsConnected;
	bool	mIsListening;
};


//--------------------------------------------------------------------------
// BSDLiveLinkSocketDriver

class BSDLiveLinkSocketDriver : public ILiveLinkSocketDriver
{
public:
	virtual ILiveLinkSocket* CreateLiveLinkSocket(); // override
	
protected:
	friend class ILiveLinkSocketDriver; // No one else needs to explicitly be creating the Windows specific driver
	BSDLiveLinkSocketDriver();

private:
	// Returns true if the library has already been initialized. If the library has not been
	// initialized yet, then it will be initialized and if successful true will be returned,
	// false will only be returned if the library has not been initialized and attempting to 
	// do so failed.
	static bool		EnsureLibraryInit();

	static bool		sShouldInitLibrary;
};


} // namespace Sexy

#endif // SEXY_IS_LIVELINK_ENABLED

#endif // __SEXYAPPFRAMEWORK_BSDLIVELINKSOCKETDRIVER_H__

