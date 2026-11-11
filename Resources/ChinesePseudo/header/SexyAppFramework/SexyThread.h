#ifndef SEXYTHREAD_H_INCLUDED
#define SEXYTHREAD_H_INCLUDED

#include "Common.h"

#if defined HOST_WINDOWS
#include <process.h>
#elif defined HOST_XBOX360
#include <xtl.h>
#elif defined HOST_MACOSX || defined HOST_IPHONEOS
#endif

namespace Sexy 
{
	typedef void(*SexyThreadProc)(void*);
    
    enum SexyThreadPriority
    {
        STP_LOWEST,
        STP_LOW,
        STP_NORMAL,
        STP_HIGH,
        STP_HIGHEST,
    };

	void LaunchThread(SexyThreadProc proc, void* param, SexyThreadPriority pri = STP_NORMAL);
	
#if defined HOST_WINDOWS || defined HOST_XBOX360
	typedef DWORD SexyThreadId;
#elif defined HOST_PS3
	typedef sys_ppu_thread_t SexyThreadId;
#elif defined HOST_MACOSX || defined HOST_IPHONEOS || defined HOST_PS3 || defined HOST_ANDROID
	typedef pthread_t SexyThreadId;
#elif defined HOST_WII
#define WII_THREAD_STACK_SIZE 4096
	typedef OSThread* SexyThreadId;

	//We need this exposed to keep track of running threads in the AppDriver
	//so we can clean up the stacks properly after execution.
	struct WiiThreadInfo
	{
		OSThread mThread;
		uint8 mStack[WII_THREAD_STACK_SIZE];
		
		SexyThreadProc mProc;
		void* mParam;
	};

#elif defined HOST_AIRPLAY
	//airplay will just stub out threads for now
	typedef int SexyThreadId;
#elif defined HOST_VITA
	typedef SceUID SexyThreadId;
#elif defined(WINRT_CLUSTER)
	typedef int SexyThreadId;
#else
	#error "Need to defind a SexyThreadId for this platform!"
#endif
	
	SexyThreadId GetCurrentRunningThread();
}

#endif
