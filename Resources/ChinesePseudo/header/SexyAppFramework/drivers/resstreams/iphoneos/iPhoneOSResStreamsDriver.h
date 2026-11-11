#pragma once
#ifndef IPHONEOSRESSTREAMSDRIVER_H_INCLUDED
#define IPHONEOSRESSTREAMSDRIVER_H_INCLUDED

#include "IResStreamsDriver.h"
#include "TextureRestitchBuffer.h"
#include "drivers/resstreams/BaseGLResStreamsDriver.h"
#include "drivers/graphics/iphoneos/iPhoneOSGraphicsDriver.h"

namespace Sexy
{
	class iPhoneOSResStreamsDriver : public BaseGLResStreamsDriver
	{
	public:
		iPhoneOSResStreamsDriver();
		
		virtual						~iPhoneOSResStreamsDriver();
		
		virtual	bool				InitWithApp(SexyAppBase* theAppBase);
		virtual bool				AttachGraphicsDriver(IGraphicsDriver* theGraphicsDriver);
		
		virtual bool				AllocatePool(ResStreamsPool* thePool);
		virtual bool				AttachGroupToPool(ResStreamsPool* thePool, int theInstance, ResStreamsGroup* thePrevGroup, ResStreamsGroup* theNewGroup);

		virtual bool				IsPoolInstanceBusy(ResStreamsPool* thePool, int theInstanceId);
		
		//Xbox returns true. no other platform that I know of yet.
		virtual bool				CanReadGPUResourcesDirectly();
		
		virtual DeviceImage*		GetImageFromResStream(const std::string theFileName,
														  void* theTextureRef,
                                                          void* theTextureRefMulti,
														  ResStreamFileGPULocationInfo* theLocationInfo,
														  ResStreamTextureDescriptor* theTextureDesc);
		
		virtual Task*				CreateDecodeTask(TaskResource* theInBuffer,
													 uint32 theByteOffset,
													 ResStreamTextureDescriptor* theTextureDesc, 
													 GLuint theTextureRef,
                                                     GLuint theMultiTextureRef,
													 uint32 theTileOffset,
													 uint32 theNumTiles);
        
        void                        GetExtensionsSupported();
		
		virtual uint32				GetReadBufferSize() { return 128*1024; }
		virtual	uint32				GetReadBufferCount() { return 4; }
        
		virtual uint32				GetDecompressBufferSize() { return 512*1024; }
		virtual uint32				GetDecompressBufferCount() { return 4; }
        
        IGraphicsDriver*            GetGraphicsDriver() { return mGraphicsDriver; }
		iPhoneOSGraphicsDriver*		mGraphicsDriver;
	};
};

#endif
