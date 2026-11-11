#pragma once
#ifndef IRESSTREAMSDRIVER_H_INCLUDED
#define IRESSTREAMSDRIVER_H_INCLUDED

#include "Common.h"
#include "SexyAppBase.h"
#include "IGraphicsDriver.h"
#include "IFileDriver.h"

#if defined HOST_ANDROID
#include <GLES2/gl2.h>
#elif defined HOST_IPHONEOS
#include <OpenGLES/ES2/gl.h>
#elif defined HOST_MACOSX
#include <OpenGL/gl.h>
#elif defined HOST_WINDOWS
//#include <OpenGL/gl.h>
#else
#error IResStreamsDriver.h not implemented for your platform
#endif

namespace Sexy 
{
	class ResStreamsPool;
	class ResStreamsGroup;
	struct ResStreamTextureDescriptor;
	struct ResStreamFileGPULocationInfo;

	class IResStreamsDriver 
	{
	public:
		enum TaskType 
		{
			TASK_READDISK,
			TASK_DECOMPRESS,
			TASK_DECODE,
			//more?
		};
		
		enum TaskResourceType
		{
			TASKRES_DISK,
			TASKRES_DECOMPRESS_THREAD,
			TASKRES_BUFFER,
			TASKRES_GPU, //may need to have more here for the decode process...
			
		};
		
		class TaskResource;
		
		class Task
		{
		protected:
			Task() 
			{
				mAuxData = (uint32)-1;
				mAuxPtr = NULL;
			}
			
		public:
			virtual ~Task() {}
			
			virtual bool				IsExecuting() = 0;
			virtual void				Update() = 0;
			
			virtual TaskType			GetType() = 0;
			virtual bool				CanExecute() = 0;
			virtual bool				Execute() = 0;
			
			virtual bool				IsDone() = 0;
			virtual bool				HasError() = 0;
			
			//unlock resources used...
			virtual bool				Finish() = 0;
			
			//at the moment a fat interface, I didn't think this needed extra classes to complicate it 
			
			//
			virtual TaskResource*		GetInBuffer() { return NULL; }
			virtual TaskResource*		GetOutBuffer() { return NULL; }
			
			//for the decompress task
			virtual bool				DidFinishDecompression() { return false; }
			virtual uint32				GetRemainingBytesToDecompress() { return 0; }
			virtual uint32				GetNumBytesRead() { return 0; }
			
			uint32						GetAuxData() { return mAuxData; }
			void*						GetAuxPtr() { return mAuxPtr; }
			
			void						SetAuxData(uint32 theAuxData) { mAuxData = theAuxData; }
			void						SetAuxPtr(void* theAuxPtr) { mAuxPtr = theAuxPtr; }
		
			virtual	bool				CanExecuteOffMainThread() { return false; }
		private:
			uint32						mAuxData;
			void*						mAuxPtr;
		};
		
		
		class TaskResource
		{
		protected:
			TaskResource() {} 
		public:
			virtual ~TaskResource() {}
			virtual TaskResourceType	GetType() = 0;
			virtual bool				IsLocked() = 0;
			virtual bool				Lock() = 0;
			virtual bool				Unlock() = 0;
			
			//only valid for some buffers...
			virtual void*				GetPtr() = 0;
			virtual uint32				GetSize() = 0;

			//used for debugging contentions
			virtual const char*			GetName() = 0;
		};
		
	public:
		static IResStreamsDriver*	CreateResStreamsDriver();
		
		virtual						~IResStreamsDriver() {}
		
		virtual	bool				InitWithApp(SexyAppBase* theAppBase) = 0;
		virtual bool				AttachGraphicsDriver(IGraphicsDriver* theGraphicsDriver) = 0;
		
		virtual bool				AllocatePool(ResStreamsPool* thePool) = 0;
        virtual bool                DestroyPool(ResStreamsPool* thePool) = 0;

#ifdef HOST_ANDROID
		virtual bool 				ValidateGroupTextures( ResStreamsGroup* theGroup  ) const { return true; }
#endif
		virtual bool				AttachGroupToPool(ResStreamsPool* thePool, int theInstance, ResStreamsGroup* thePrevGroup, ResStreamsGroup* theNewGroup) = 0;
		
		virtual bool				IsPoolInstanceBusy(ResStreamsPool* thePool, int theInstanceId) = 0;
				
		//Xbox returns true. no other platform that I know of yet.
		virtual bool				CanReadGPUResourcesDirectly() = 0;
				
		virtual DeviceImage*		GetImageFromResStream(const std::string theFileName,
														  void* theTextureRef,
                                                          void* theTextureRefMulti,
														  ResStreamFileGPULocationInfo* theLocationInfo,
														  ResStreamTextureDescriptor* theTextureDesc) = 0;
		
		
		// the read task WILL NOT seek for you. that should be done before hand
		virtual Task*				CreateReadTask(IFile* theFile, uint32 theReadLength) = 0;
		
		// this read task will read directly into the Dst, it will not require a buffer resource and is not
		// bounded by the read buffer size
		virtual Task*				CreateReadTaskWithoutBuffer(IFile* theFile, uint8* theDst, uint32 theReadLength, uint32 theFileLocation) = 0;
		
		//if the prev decompress task is null, this will start a new decompression stream
		virtual Task*				CreateDecompressTask(TaskResource* theReadBuffer, Task* thePrevDecompress) = 0;
		virtual Task*				CreateDecompressTask(TaskResource* theReadBuffer, uint32 theSize, bool isFullReset) = 0;
		
		//DECODE is really decode AND copy to GPU
		virtual uint32				GetFileDataSizeForTexture(ResStreamTextureDescriptor* theTextureDesc) const = 0;
		virtual uint32				GetGPUDataSizeForTexture(ResStreamTextureDescriptor* theTextureDesc) const = 0;
		virtual uint32				GetGPUTileSizeForTexture(ResStreamTextureDescriptor* theTextureDesc) const = 0;

#ifdef HOST_WINDOWS
		virtual Task*				CreateDecodeTask(TaskResource* theInBuffer,
													 uint32 theByteOffset,
												     ResStreamTextureDescriptor* theTextureDesc,
													 void* theTextureRef,
													 void* theTextureRefMulti,
													 uint32 theTileOffset,
													 uint32 theNumTiles) = 0;
#else
		virtual Task*				CreateDecodeTask(TaskResource* theInBuffer,
													 uint32 theByteOffset,
													 ResStreamTextureDescriptor* theTextureDesc,
													 GLuint theTextureRef,
													 GLuint theTextureRefMulti,
													 uint32 theTileOffset,
													 uint32 theNumTiles) = 0;
#endif

		virtual uint32				GetReadBufferSize() = 0;
		virtual uint32				GetDecompressBufferSize() = 0;

		virtual TaskResource*		GetFreeHoldoverBuffer( ) = 0;
	};
};

#endif
