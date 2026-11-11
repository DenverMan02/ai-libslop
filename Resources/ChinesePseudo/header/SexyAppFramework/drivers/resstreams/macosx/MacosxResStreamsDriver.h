#pragma once
#ifndef MACOSXRESSTREAMSDRIVER_H_INCLUDED
#define MACOSXRESSTREAMSDRIVER_H_INCLUDED

#include "IResStreamsDriver.h"
#include "drivers/resstreams/BaseGLResStreamsDriver.h"
#include "drivers/graphics/macosx/MacosxGraphicsDriver.h"
#include "ImageLib/zlib/zlib.h"

namespace Sexy 
{
	class MacosxResStreamsDriver : public BaseResStreamsDriver
	{
	public:
		MacosxResStreamsDriver();
		
		virtual						~MacosxResStreamsDriver();
		
		virtual	bool				InitWithApp(SexyAppBase* theAppBase);
		virtual bool				AttachGraphicsDriver(IGraphicsDriver* theGraphicsDriver);
		
		virtual bool				AllocatePool(ResStreamsPool* thePool);
		virtual bool				AttachGroupToPool(ResStreamsPool* thePool, int theInstance, ResStreamsGroup* thePrevGroup, ResStreamsGroup* theNewGroup);
		virtual bool				DestroyPool(ResStreamsPool* thePool);
		
		virtual bool				IsPoolInstanceBusy(ResStreamsPool* thePool, int theInstanceId);
		
		//Xbox returns true. no other platform that I know of yet.
		virtual bool				CanReadGPUResourcesDirectly();
		
		/*virtual uint32				GetGPUDataSize(ResStreamTextureDescriptor* theTextureDesc);
		virtual bool				BeginGPUDataCopy(void* theTextureRef,ResStreamTextureDescriptor* theTextureDesc);
		virtual bool				EndGPUDataCopy(void* theTextureRef);
		virtual bool				CopyDataToTexture(void* theTextureRef, uint8* theBuffer, uint32 theSize);*/
		
		virtual DeviceImage*		GetImageFromResStream(const std::string theFileName,
														  void* theTextureRef,
                                                          void* theTextureRefMulti,
														  ResStreamFileGPULocationInfo* theLocationInfo,
														  ResStreamTextureDescriptor* theTextureDesc);
		
		virtual uint32				GetGPUDataSizeForTexture(ResStreamTextureDescriptor* theTextureDesc);
		virtual uint32				GetGPUTileSizeForTexture(ResStreamTextureDescriptor* theTextureDesc);
		
		virtual Task*				CreateDecodeTask(TaskResource* theInBuffer,
													 uint32 theByteOffset,
													 ResStreamTextureDescriptor* theTextureDesc, 
													 GLuint theTextureRef,
                                                     GLuint theTextureRefMulti,
													 uint32 theTileOffset,
													 uint32 theNumTiles);
		
		virtual uint32		GetReadBufferSize() { return 1024*1024; }
		virtual uint32		GetDecompressBufferSize() { return 1024*1024; }

		virtual	uint32	GetReadBufferCount() { return 2; }
		virtual uint32	GetDecompressBufferCount() { return 2; }
        
        virtual void        GetExtensionsSupported() {};
        
        virtual IGraphicsDriver*    GetGraphicsDriver() { return mGraphicsDriver; }
        
	private:
		MacosxGraphicsDriver*		mGraphicsDriver;
		
		
		//info for copying data to the texture
		/*uint32						mCurX;
		uint32						mCurY;
		uint32						mWidth;
		uint32						mPitch;
		uint32						mHeight;
		uint32						mFormat;
		uint32						mNumLeftOverBytes;
		uint8						mLeftOverBytes[4];*/
		
		
	};
};

#endif
