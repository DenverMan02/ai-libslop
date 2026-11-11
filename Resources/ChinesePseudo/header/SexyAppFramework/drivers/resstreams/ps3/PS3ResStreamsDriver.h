#pragma once
#ifndef PS3RESSTREAMSDRIVER_H_INCLUDED
#define PS3RESSTREAMSDRIVER_H_INCLUDED

#include "IResStreamsDriver.h"
#include "drivers/resstreams/BaseResStreamsDriver.h"
#include "drivers/graphics/PS3/PS3GraphicsDriver.h"

namespace Sexy 
{
	class PS3ResStreamsDriver : public BaseResStreamsDriver
	{
	public:
		PS3ResStreamsDriver();
		
		virtual						~PS3ResStreamsDriver();
		
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

		virtual uint32		GetReadBufferSize() { return 1024*256; }
		virtual uint32		GetDecompressBufferSize() { return 1024*1024; }

		virtual	uint32	GetReadBufferCount() { return 4; }
		virtual uint32	GetDecompressBufferCount() { return 4; }

		virtual IResStreamsDriver::TaskResource*  CreateHoldoverBuffer( uint32 &outSize );
	private:
		PS3GraphicsDriver*		mGraphicsDriver;

		//some memory tracking 
		uint32 mMainMemUsage;
		uint32 mLocalMemUsage;
	};
};

#endif
