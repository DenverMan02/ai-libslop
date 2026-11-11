#ifndef __SHAREDRENDERTARGET_H__
#define __SHAREDRENDERTARGET_H__

#include "Common.h"
#include "RenderDevice.h"

namespace Sexy
{

class DeviceImage;

class SharedRenderTarget
{
public:
	class Pool
	{
	protected:
		struct Entry
		{
			DeviceImage* mImage;
			RenderSurface* mScreenSurface;
			SharedRenderTarget* mLockOwner;
			std::string mLockDebugTag;
		};
		std::vector<Entry> mEntries;

	public:
		Pool();
		~Pool();

		void Acquire(SharedRenderTarget& outTarget, int theWidth, int theHeight, uint32 theD3DFlags, const char* debugTag);
		void UpdateEntry(SharedRenderTarget& inTarget);
		void Unacquire(SharedRenderTarget& ioTarget);

		void InvalidateSurfaces();
		
		void InvalidateDevice();
		
		std::string GetInfoString();
	};

protected:
	friend class Pool;

	DeviceImage* mImage;
	RenderSurface* mScreenSurface;
	ulong mLockHandle;

public:
	enum FLAGS 
	{
		// This hints to the drivers that this is the final LockScreenImage call of the frame, which
		// will help optimize when it can start composing to the final render target.
		FLAGS_HINT_LAST_LOCK_SCREEN_IMAGE = 0x01,
	};
	
	SharedRenderTarget();
	~SharedRenderTarget();

	DeviceImage* Lock(int theWidth, int theHeight, uint32 additionalD3DFlags = 0, const char* debugTag = NULL);
	DeviceImage* LockScreenImage(const char* debugTag = NULL, uint32 flags = 0);

	bool Unlock();

	DeviceImage* GetCurrentLockImage();
};

}

#endif //__SHAREDRENDERTARGET_H__
