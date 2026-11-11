#pragma once

#include "CritSect.h"
#include "SexyThread.h"

#include "DeviceImage.h"
#include "PakLib/PakInterface.h"

#include <cell/codec.h>

#include <queue>

namespace Sexy
{
	class PS3OptimizedPngLoader;

	struct PngLoadContext
	{	
		PngLoadContext()
		{
			mDisableSPU = false;
			
			mImage = NULL;

			mFileBuffer = NULL;
			mFileSize = 0;
			mFile = NULL;
		}

		bool mDisableSPU;

		std::string mFilename;
		DeviceImage *mImage;

		uint8* mFileBuffer;
		uint32 mFileSize;
		PFILE* mFile;

		CellPngDecSubHandle	mPngSubHandle;

		CellPngDecSrc		mPngDecSrc;
		CellPngDecOpnInfo	mPngDecOpenInfo;

		CellPngDecInfo		mPngDecInfo;
		CellPngDecInParam 	mPngDecInParam;
		CellPngDecOutParam 	mPngDecOutParam;

		CellPngDecDataCtrlParam		mPngDecCtrlParam;
		CellPngDecDataOutInfo 		mPngDecDataOutInfo;
	};

	struct PngLoadThreadContext
	{
		uint8 mId;
		PS3OptimizedPngLoader *mLoader;

		//libpngdec state
		CellPngDecMainHandle		mPngMainHandle;
		CellPngDecThreadInParam		mPngThreadInParam;
		CellPngDecThreadOutParam	mPngThreadOutParam;
	};

#define NUM_PNG_LOAD_THREADS 1

	class PS3OptimizedPngLoader
	{
	public:
		PS3OptimizedPngLoader(void);
		~PS3OptimizedPngLoader(void);

		bool Init();
		void Update();

		DeviceImage *LoadImage( std::string theFilename, bool commitBits, bool allowTrireps );

	private:
		static void loadThreadMain( void *param);

		CritSect mLoadQueueCritSect;
		Condition mLoadQueueCondition;
		Condition mLoadQueueShutdown;

		std::queue<PngLoadContext> mLoadQueue;

		PngLoadThreadContext mLoadThreads[NUM_PNG_LOAD_THREADS];

		//malloc and free callbacks for libpngdec
		static void *pngMallocCallback( uint32_t size,	void *cbCtrlMallocArg );
		static int32_t pngFreeCallback( void *ptr, void *cbCtrlFreeArg );

		//libpngdec state
		CellPngDecMainHandle		mPngMainHandle;
		CellPngDecThreadInParam		mPngThreadInParam;
		CellPngDecThreadOutParam	mPngThreadOutParam;
	};
};
