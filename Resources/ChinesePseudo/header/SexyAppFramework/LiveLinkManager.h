
#ifndef __SEXYAPPFRAMEWORK_LIVELINKMGR_H__
#define __SEXYAPPFRAMEWORK_LIVELINKMGR_H__

#include "Common.h"
#include "ILiveLinkSocketDriver.h"
#include "LiveLinkPacket.h"

#if SEXY_IS_LIVELINK_ENABLED

#include <vector>

#include "CritSect.h"
#include "AutoCrit.h"

#include "CircularBuffer.h"
#include "LiveLinkPacket.h"
#include "RtObject.h"


namespace Sexy
{

namespace Private
{
extern void ThreadProcToExecuteThreadWrapperMethod(void*);

class Thread
{	
	friend void ThreadProcToExecuteThreadWrapperMethod(void*);
public:
	Thread();

	bool			IsThreadRunning();
	bool			HasThreadCompleted();

protected:
	void			StartThread();	

	
	// Since correct thread stopping behaviour must be implemented correctly 
	// in decendent's OnExecuteThread(), this method is protected. If 
	// a class inherits from Thread and implements Thread stopping then
	// feel free to implement a public StopThread() in the decendent class.
	// which calls this protected StopThread() method.
	void			NotifyThreadStop();
	void			WaitForThreadStop(int inWaitMs);

	// Implement this when inheirting from Thread. This will be exectuted 
	// on a new thread when StartThread() is called.
	//
	// $ Your implementation of OnExecuteThread() should periodicly call
	// ShouldThreadReturn() and if it returns true, the thread should return
	// from OnExecuteThread(). If this is not done then StopThread() will not
	// work.
	virtual void	OnExecuteThread() = 0;

	bool			ShouldThreadReturn();


private:
	// Wraps the virtual call to onExecuteThread() and updates thread started/completed flags.
	void			ExecuteThreadWrapper();


	CritSect	mCritSect; // Used to protect all data members in this class.

	bool			mWasThreadStarted;
	bool			mHasThreadCompleted;

	//
	// Thread stop support
	//

	bool			mIsThreadStopRequested;

	// Condition will be signalled when the thead exits. Used to allow 
	// StopThread() to wait until the thread exits before returning.
	Condition mThreadStopCondition; 
};

} // Private namespace

///--------------------------------------------------------------------------
// Network support class declarations

//
// Each packet connection instance is used to transmit/recieve packets of different priorities.
//
class LiveLinkPacketChannel : public Private::Thread
{
	typedef Private::Thread super;
public:
	LiveLinkPacketChannel();
	~LiveLinkPacketChannel();

					// Starts the thread that handles establishing a connection to 
					// the pc/mac remote client begin processing packets.
	void			ActivateChannel(ChannelType inChannelType, const NetAddress& inClientAddress);

	inline void		NotifyChannelDeactivate() 
	{
		NotifyThreadStop(); 
	}

	inline void		WaitForChannelDeactivateComplete() // $$$ (AVY) should check for situation where the thread was never started.
	{
		WaitForThreadStop(2 * CONNECT_RETRY_FREQ_MS); 
	}

	inline bool		IsClientConnected() const 
	{ 
		return mIsConnected; 
	}


	//
	// Reading Packets
	//

	inline void		LockReadBuffer() 
	{
		mReadBufferCritSect.Lock();
		SEXY_ASSERTM(!mWasLockReadBufferCalled, "LockReadBuffer() called multiple times without calling UnlockReadBuffer()");
		mWasLockReadBufferCalled = true; 
	}

	// Must call LockReadBuffer() before calling GetNextPacket()
	LiveLinkPacket*	GetNextPacket(); 

	// Once you unlock the read buffer and SPackets returned from GetNextPacket() 
	// must not be used. The data in the packet can no longer be considered valid.
	inline void		UnlockReadBuffer() 
	{
		SEXY_ASSERTM(mWasLockReadBufferCalled, "UnlockReadBuffer() called without first calling LockReadBuffer()");
		mWasLockReadBufferCalled = false;
		mReadBufferCritSect.Unlock(); 
	}

	//
	// Writing Packets
	//

	bool			Write(uint32 inPacketType, const void* inDataToWrite, int inBytesToWrite, bool inShouldWaitUtilSent = false);
	
protected:
	//
	// Thread
	//
	virtual void	OnExecuteThread();

private:
	void			FreeReadWriteBuffers();

	const static int		CONNECT_RETRY_FREQ_MS = 3000;

	ChannelType				mChannelType;				// Is this channel used for hi pri packets, lo pri packets (eventually: large data transfers)
	NetAddress				mClientAddress;
	bool					mIsConnected;
	ILiveLinkSocket*		mClient;					// only one client supported currently
	CircularBuffer			mReadBuffer;				
	CircularBuffer			mWriteBuffer;

	// Don't use directly, these are just pointers to the memory given to the circular buffers. 
	// We keep track of them  here only so we can free the memory later.
	uint8*					mUnalignedReadBuffer;	// Don't use directly
	uint8*					mUnalignedWriteBuffer;  // Don't use directly

	int32					mWriteRecursionCount;

	// $$ For debugging, catches cases where LockReadBuffer()/UnlockReadBuffer() calls are not paired. Also
	// Allows testing that LockReadbuffer() is called before calling GetNextPacket().
	bool					mWasLockReadBufferCalled;	

	mutable CritSect		mGeneralCritSect;			// general thread synchronization
	mutable CritSect		mWriteBufferCritSect;		// write-buffer-specific mutex for speed (only protect the buffer)
	mutable CritSect		mReadBufferCritSect;

	uint8*					mTempAlloc; // Used to copy packet data into when the packet data wraps in the circular read buffer.
	uint32					mBytesRead;
};


class LiveLinkManager
{
public:
	Event0 OnConnected; // Event
	Event0 OnDisconnected; // Event

	virtual ~LiveLinkManager();

	static LiveLinkManager* GetSingleton()
	{
		if (sInstance == NULL) sInstance = new LiveLinkManager();
		return sInstance;
	}

	static bool		IsConnected()
	{
		if (sInstance == NULL) return false;
		return sInstance->NonStaticIsConnected();
	}

	void			Init(const NetAddress& inClientAddress);

	virtual void	Update();

	bool			Write(LiveLinkPacket const& inPacket);
	bool			Write(uint32 inPacketType, const void* inDataToWrite, int inBytesToWrite, bool inShouldWaitUtilSent = false);


	void RegisterPacketType(LiveLinkPacketMetaClass* inPacketMetaClass);
	LiveLinkPacket* CreatePacket(int32 inPacketType, uint8* inData, int32 inSizeBytes);

	void OnPacketChannelConnected(LiveLinkPacketChannel* inChannel)
	{
		AutoCrit locker(mChannelStateChangeCritSect);
		mHasChannelStateChanged = true;
	}	

	void OnPacketChannelDisconnected(LiveLinkPacketChannel* inChannel)
	{
		AutoCrit locker(mChannelStateChangeCritSect);
		mHasChannelStateChanged = true;
	}

	std::string GetAppId();
	std::string GetInstanceId();

private:

	LiveLinkManager();

	bool					NonStaticIsConnected() const;
	LiveLinkPacketChannel*	GetPacketChannel(ChannelType inChannelType);
	
	typedef std::vector<LiveLinkPacketChannel*> ChannelArray;
	ChannelArray						mChannels;

	class PacketRegistry 
	{
	public:
		void Register(int32 inType, LiveLinkPacketMetaClass* inMetaClass)
		{
			mMap[inType] = inMetaClass;
		}

		LiveLinkPacketMetaClass* Lookup(int32 inType)
		{
			std::map<int32, LiveLinkPacketMetaClass*>::iterator i = mMap.find(inType);
			if (i == mMap.end())
			{
				return NULL;
			}
			else
			{
				return i->second;
			}
		}
	private:
		std::map<int32, LiveLinkPacketMetaClass*> mMap;
	};
	
	PacketRegistry						mPacketTypeRegistry;

	mutable CritSect					mChannelStateChangeCritSect; // used to protect mHasChannelStateChanged
	bool								mHasChannelStateChanged;

	bool								mWasConnectedOnPrevUpdate;

	static LiveLinkManager*				sInstance;
};

#define gLiveLinkManager LiveLinkManager::GetSingleton()

} // namespace Sexy

#endif // SEXY_IS_LIVELINK_ENABLED




/*--------------------------------------------------------------------------*/

#endif // __SEXYAPPFRAMEWORK_LIVELINKMGR_H__

//-----------------------------------EOF!-----------------------------------
