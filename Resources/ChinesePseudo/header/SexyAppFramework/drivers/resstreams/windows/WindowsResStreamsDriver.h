#pragma once
#ifndef WINDOWSRESSTREAMSDRIVER_H_INCLUDED
#define WINDOWSRESSTREAMSDRIVER_H_INCLUDED

#include "IResStreamsDriver.h"
#include "drivers/resstreams/BaseResStreamsDriver.h"
#include "drivers/graphics/windows/WindowsGraphicsDriver.h"

namespace Sexy 
{
	class WindowsResStreamsDriver : public BaseResStreamsDriver
	{
	public:
		WindowsResStreamsDriver();
		
		virtual						~WindowsResStreamsDriver();
		
		virtual	bool				InitWithApp(SexyAppBase* theAppBase);
		virtual bool				AttachGraphicsDriver(IGraphicsDriver* theGraphicsDriver);
		
		virtual bool				AllocatePool(ResStreamsPool* thePool);
		virtual bool				AttachGroupToPool(ResStreamsPool* thePool, int theInstance, ResStreamsGroup* thePrevGroup, ResStreamsGroup* theNewGroup);
		virtual bool				DestroyPool(ResStreamsPool* thePool);
		
		virtual bool				IsPoolInstanceBusy(ResStreamsPool* thePool, int theInstanceId);
		
#ifdef PRIME_FOR_BEJADVENTURES
		virtual bool				WantsGPUDataCacheThread() { return true; }
#endif // PRIME_FOR_BEJADVENTURES

		virtual bool				CanReadGPUResourcesDirectly();
		
		virtual DeviceImage*		GetImageFromResStream(const std::string theFileName,
														  void* theTextureRef,
														  void *theTextureRefMulti_Unused,
														  ResStreamFileGPULocationInfo* theLocationInfo,
														  ResStreamTextureDescriptor* theTextureDesc);
		
		virtual uint32				GetGPUDataSizeForTexture(ResStreamTextureDescriptor* theTextureDesc);
		virtual uint32				GetGPUTileSizeForTexture(ResStreamTextureDescriptor* theTextureDesc);
		
		virtual Task*				CreateDecodeTask(TaskResource* theInBuffer,
													 uint32 theByteOffset,
													 ResStreamTextureDescriptor* theTextureDesc, 
													 void* theTextureRef,
													 void *theTextureRefMulti_Unused,
													 uint32 theTileOffset,
													 uint32 theNumTiles);
		
		virtual uint32				GetReadBufferSize() { return 256*1024; }
		virtual uint32				GetDecompressBufferSize() { return 1024*1024; }

		virtual	uint32				GetReadBufferCount() { return 4; }
		virtual uint32				GetDecompressBufferCount() { return 4; }

		WindowsGraphicsDriver*		mGraphicsDriver;
	};
};

#endif
