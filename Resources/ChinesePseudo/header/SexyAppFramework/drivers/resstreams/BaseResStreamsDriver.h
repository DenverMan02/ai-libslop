#ifndef BASERESSTREAMSDRIVER_H_INCLUDED
#define BASERESSTREAMSDRIVER_H_INCLUDED


#include "Common.h"
#include "IResStreamsDriver.h"
#include "SexyThread.h"
#ifdef HOST_ANDROID
#include <zlib.h>
#else
#include "ImageLib/zlib/zlib.h"
#endif
#include "MemPools.h"

namespace Sexy 
{
	/**
	 * This class has some utilities that can be optionally used 
	 * by any ResStreams driver to make them easier to write.
	 * 
	 * including decompression code, decompression threading,
	 * task management, and buffer management
	 */
	typedef std::vector<IResStreamsDriver::TaskResource*> TaskResourceList;
	
	class DriverExtensionSupport
    {
    public:
        bool                    mSupportsCompressedETC1;
        bool                    mSupportsCompressedPVRTC;
        bool                    mSupportsCompressedATITC;
        bool                    mSupportsCompressedDXT;
        bool                    mSupportsCompressed3DC;
        bool                    mRequiresPowerOf2Textures;
		bool                    mSupportsTextureSwizzle;
        
    public:
        void                    OutputDebugSupported();
        DriverExtensionSupport() {
            mSupportsCompressedETC1 = false;
            mSupportsCompressedPVRTC = false;
            mSupportsCompressedATITC = false;
            mSupportsCompressedDXT = false;
            mSupportsCompressed3DC = false;
            mRequiresPowerOf2Textures = false;
			mSupportsTextureSwizzle = false;
        };
    };

       
	class BaseResStreamsDriver : public IResStreamsDriver
	{
	protected:
		BaseResStreamsDriver();
	public:
		virtual		~BaseResStreamsDriver();
		bool		InitWithApp(SexyAppBase* theAppBase);
		
		bool		BeginDecompression(int theCompressionType);
		bool		DecompressStream(uint8* theCompressedBuffer, uint32 theCompressedBufferSize,
													 uint8* theOutBuffer, uint32 theOutBufferSize);
		
		bool		ContinueDecompressStream(uint8* theOutBuffer, uint32 theOutBufferSize);
		
		
		int32		IsDecompressionChunkComplete();
		int32		IsDecompressionFullyComplete();
		//this returns the size that was decompressed
		uint32		GetDecompressedSize();
		
		// the read task WILL NOT seek for you. that should be done before hand
		Task*		CreateReadTask(IFile* theFile, uint32 theReadLength);
		
		Task*		CreateReadTaskWithoutBuffer(IFile* theFile, uint8* theDst, uint32 theReadLength, uint32 theFileLocation);
		
		//if the prev decompress task is null, this will start a new decompression stream
		Task*		CreateDecompressTask(TaskResource* theReadBuffer, Task* thePrevDecompress);
		Task*		CreateDecompressTask(TaskResource* theReadBuffer, uint32 theSize, bool isFullReset);
		
		virtual void        GetExtensionsSupported() {}
		
		virtual uint32		GetReadBufferSize() { return 16*1024; }
		virtual uint32		GetDecompressBufferSize() { return 64*1024; }
		
		virtual	uint32	GetReadBufferCount() { return 2; }
		virtual uint32	GetDecompressBufferCount() { return 2; }
		virtual	bool	AreReadAndDecompressBuffersUnified() { return false; }


				
        uint32                      GetFileDataSizeForTexture(ResStreamTextureDescriptor* theTextureDesc) const;
        uint32                      GetGPUDataSizeForTexture(ResStreamTextureDescriptor* theTextureDesc) const;
        uint32                      GetGPUTileSizeForTexture(ResStreamTextureDescriptor* theTextureDesc) const;
		
		TaskResource*	GetDiskResource();
		TaskResource*	GetGPUResource();
		TaskResource*	GetDecompressThreadResource();
		
		TaskResource*	GetFreeReadBuffer();
		TaskResource*	GetFreeDecompressBuffer();
		TaskResource*	GetFreeHoldoverBuffer();

        void            RunDecompressProcess();
        
        void                        Align(uint32& theSize, int theBytes) const;
        
	protected:
		uint32						mDecompressionType;
		int32						mIsDecompressing;				// used in atomic-ops - must be a 32-bit type
		int32						mFinishedDecompressing;			// used in atomic-ops - must be a 32-bit type
		uint32						mDecompressedSize;
		uint8*						mCompressedBuffer;
		uint8*						mDecompressedBuffer;
		uint32						mCompressedBufferSize;
		uint32						mDecompressedBufferSize;
		Condition					mDecompressCondition;
		Condition					mDecompressShutdown;
		bool						mDecompressionQuit;
		
		//need to Refactor the ZLIB streaming code... it's too stateful
		bool						mDecompressionFullReset;
		bool						mDecompressionReset;
		
		bool						mThreadInitted;
		
		static void					DecompressionThreadProc(void*);
        
		//there will be other decompression types...
		z_stream					mZlibStream;
		
		TaskResourceList			mReadBuffers;
		TaskResourceList			mDecompressBuffers;
		TaskResourceList			mHoldoverBuffers;

		TaskResource*				mGPUResource;
		TaskResource*				mDiskResource;
		TaskResource*				mDecompressThreadResource;
        
		DriverExtensionSupport      mExtensionsSupported;
        
		virtual IResStreamsDriver::TaskResource* CreateHoldoverBuffer( uint32 &outSize );		
	};
	
		
	class BaseTaskResource : public IResStreamsDriver::TaskResource
	{
	protected:
		BaseTaskResource(IResStreamsDriver::TaskResourceType theType)
		{
			mLocked = 0;
			mType = theType;
		}
	public:
		
		IResStreamsDriver::TaskResourceType	GetType() { return mType; }

		bool				IsLocked() { return mLocked>0; }
		
		
		bool				Lock() 
		{ 
			//locks can be interleaved with the BaseTaskSystem... 
			// should investigate renaming to AddRef
			mLocked++;
			return true;
		}
		
		bool				Unlock()
		{
			mLocked--;
			return true;
		}
		
		void*  GetPtr() { return NULL; }
		uint32 GetSize() { return 0; };
		
		const char* GetName() { return mName.c_str(); }
		void		SetName(const std::string name) { mName = name; }
	private:
		int		mLocked;
		IResStreamsDriver::TaskResourceType mType;
		std::string mName;
	};

	class BaseBufferResource : public BaseTaskResource
	{
	public:
		//there may be a preallocated version at some time...
		BaseBufferResource(uint32 theSize) : BaseTaskResource(IResStreamsDriver::TASKRES_BUFFER) 
		{
			mSize = theSize;
			mBuffer = new uint8[theSize];
		}
		
		~BaseBufferResource()
		{
			delete[] mBuffer;
		}
		
		uint8* GetBuffer() { return mBuffer; }
		uint32 GetSize() { return mSize; }
		
		void*  GetPtr() { return mBuffer; }
		
	private:
		uint8*	mBuffer;
		uint32  mSize;
	};

	class BaseDiskResource : public BaseTaskResource
	{
	public:
		BaseDiskResource() : BaseTaskResource(IResStreamsDriver::TASKRES_DISK) {} 
	};

	class BaseDecompressThreadResource : public BaseTaskResource
	{
	public:
		BaseDecompressThreadResource() : BaseTaskResource(IResStreamsDriver::TASKRES_DECOMPRESS_THREAD) {} 
	};

	class BaseGPUResource : public BaseTaskResource
	{
	public:
		BaseGPUResource() : BaseTaskResource(IResStreamsDriver::TASKRES_GPU) {} 
	};
    
    SexyString GetRsbTextureFormatName(int rsbFormat);
    
    void GetAttachedTextureSize(ResStreamTextureDescriptor& theTextureDesc, int& height, int& width, int& bytes);
}

#endif