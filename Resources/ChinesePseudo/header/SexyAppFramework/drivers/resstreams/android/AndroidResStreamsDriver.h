#pragma once
#ifndef IPHONEOSRESSTREAMSDRIVER_H_INCLUDED
#define IPHONEOSRESSTREAMSDRIVER_H_INCLUDED

#include "IResStreamsDriver.h"
#include <drivers/resstreams/BaseGLResStreamsDriver.h>
#include "TextureRestitchBuffer.h"

namespace Sexy 
{
    class AndroidGraphicsDriver;
    
	class AndroidResStreamsDriver : public BaseGLResStreamsDriver
	{
	public:
		AndroidResStreamsDriver();
		
		virtual					~AndroidResStreamsDriver();
		
		virtual bool				InitWithApp(SexyAppBase* theAppBase);
		virtual bool				AttachGraphicsDriver(IGraphicsDriver* theGraphicsDriver);
		
		virtual bool				AllocatePool(ResStreamsPool* thePool);

		virtual void 				ConfigureGroupTextures( ResStreamsGroup* theGroup ) const;
		virtual void				ReallocateGroupTextures( ResStreamsGroup* theGroup ) const;
		virtual bool				AttachGroupToPool( ResStreamsPool* thePool, int theInstance, ResStreamsGroup* thePrevGroup, ResStreamsGroup* theNewGroup );
		virtual bool				DestroyPool( ResStreamsPool* thePool );
        
		bool                        ValidateTextureArray(void* textureArray, int count, int& firstIndexNeedsRealloc) const;
        
		virtual bool				IsPoolInstanceBusy( ResStreamsPool* thePool, int theInstanceId );
		
		//Xbox returns true. no other platform that I know of yet.
		virtual bool				CanReadGPUResourcesDirectly();
		
		virtual DeviceImage*        GetImageFromResStream( std::string const theFileName,
                                                                    void* theTextureData,
                                                                    void* theTextureRefMulti_Unused,
                                                                    ResStreamFileGPULocationInfo* theLocationInfo,
                                                          ResStreamTextureDescriptor* theTextureDesc);
        
		virtual Task*				CreateDecodeTask( TaskResource* theInBuffer,
												 uint32 theByteOffset,
												 ResStreamTextureDescriptor* theTextureDesc, 
												 GLuint theTextureRef,
												 GLuint theTextureRefMulti,
												 uint32 theTileOffset,
												 uint32 theNumTiles );
		
        void                        GetExtensionsSupported();
		
        virtual uint32				GetReadBufferSize() { return 512*1024; }
		virtual uint32				GetDecompressBufferSize() { return 512*1024; }

		virtual uint32				GetReadBufferCount() { return 4; }
		virtual uint32				GetDecompressBufferCount() { return 0; }

		virtual bool 				ValidateGroupTextures( ResStreamsGroup* theGroup  ) const;

        virtual IGraphicsDriver*    GetGraphicsDriver() { return (IGraphicsDriver*) mGraphicsDriver; }
        AndroidGraphicsDriver*      mGraphicsDriver;
        
	};
};

#endif
