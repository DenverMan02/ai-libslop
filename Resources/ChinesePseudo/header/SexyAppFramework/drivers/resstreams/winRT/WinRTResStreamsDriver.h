#pragma once
#ifndef __WINRTRESSTREAMSDRIVER__
#define __WINRTRESSTREAMSDRIVER__ 

#include "IResStreamsDriver.h"
#include "drivers/resstreams/BaseResStreamsDriver.h"
#include "drivers/graphics/dx11/Dx11GraphicsDriver.h"

namespace Sexy 
{
	class WinRTResStreamsDriver : public BaseResStreamsDriver
	{
	public:
		WinRTResStreamsDriver();
		
		virtual						~WinRTResStreamsDriver();
		
		virtual	bool				InitWithApp(SexyAppBase* theAppBase);
		virtual bool				AttachGraphicsDriver(IGraphicsDriver* theGraphicsDriver);
		
		virtual bool				AllocatePool(ResStreamsPool* thePool);
		virtual bool				DestroyPool(ResStreamsPool* thePool);

		virtual bool				AttachGroupToPool(ResStreamsPool* thePool, int theInstance, ResStreamsGroup* thePrevGroup, ResStreamsGroup* theNewGroup);
		
		virtual bool				IsPoolInstanceBusy(ResStreamsPool* thePool, int theInstanceId);
		
		virtual bool				CanReadGPUResourcesDirectly();
		
		virtual DeviceImage*		GetImageFromResStream(const std::string theFileName,
														  void* theTextureRef,
														  ResStreamFileGPULocationInfo* theLocationInfo,
														  ResStreamTextureDescriptor* theTextureDesc);
		
		virtual uint32				GetGPUDataSizeForTexture(ResStreamTextureDescriptor* theTextureDesc);
		virtual uint32				GetGPUTileSizeForTexture(ResStreamTextureDescriptor* theTextureDesc);
		
		virtual Task*				CreateDecodeTask(TaskResource* theInBuffer,
													 uint32 theByteOffset,
													 ResStreamTextureDescriptor* theTextureDesc, 
													 void* theTextureRef,
													 uint32 theTileOffset,
													 uint32 theNumTiles);
		
		virtual uint32				GetReadBufferSize() { return 256*1024; }
		virtual uint32				GetDecompressBufferSize() { return 1024*1024; }

		virtual	uint32				GetReadBufferCount() { return 4; }
		virtual uint32				GetDecompressBufferCount() { return 4; }
//	private:
		Dx11GraphicsDriver*		mGraphicsDriver;
	};
};

#endif
