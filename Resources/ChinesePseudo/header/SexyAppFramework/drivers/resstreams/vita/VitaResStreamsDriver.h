#pragma once
#ifndef VITARESSTREAMSDRIVER_H_INCLUDED
#define VITARESSTREAMSDRIVER_H_INCLUDED

#include "IResStreamsDriver.h"
#include "drivers/resstreams/BaseResStreamsDriver.h"
#include "drivers/graphics/vita/VitaGraphicsDriver.h"

namespace Sexy 
{
	class VitaResStreamsDriver : public BaseResStreamsDriver
	{
	public:
		VitaResStreamsDriver();
		
		virtual						~VitaResStreamsDriver();
		
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
		
		virtual uint32				GetReadBufferSize() { return 512*1024; }
		virtual uint32				GetDecompressBufferSize() { return 512*1024; }

		virtual	uint32				GetReadBufferCount() { return 2; }
		virtual uint32				GetDecompressBufferCount() { return 2; }
	private:
		VitaGraphicsDriver*		mGraphicsDriver;
	};
};

#endif
