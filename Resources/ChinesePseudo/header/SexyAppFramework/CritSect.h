#ifndef CRITSECT_H_INCLUDED
#define CRITSECT_H_INCLUDED

#include "Common.h"

#if defined HOST_MACOSX || defined HOST_IPHONEOS || defined HOST_PS3
#include <sys/time.h>
#endif

#ifdef HOST_PS3
#include <sys/sys_time.h>
#endif

class CritSync;

namespace Sexy
{

#if defined HOST_WINDOWS || defined HOST_XBOX360
	class CritSect 
	{
	private:
		CRITICAL_SECTION mCriticalSection;
		friend class AutoCrit;

	public:
		CritSect(void)
		{
			InitializeCriticalSection(&mCriticalSection);
		}
		
		~CritSect(void)
		{
			DeleteCriticalSection(&mCriticalSection);
		}
		
		bool TryLock() { return TryEnterCriticalSection( &mCriticalSection ) != 0; }
		void Lock() {  EnterCriticalSection( &mCriticalSection ); }
		void Unlock() { LeaveCriticalSection( &mCriticalSection ); } 
	};
	
	class Condition
	{
	private:
		HANDLE mEvent;
	public:
		Condition()
		{
			mEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
		}
		
		~Condition()
		{
			CloseHandle(mEvent);
		}
		
		void Notify()
		{
			SetEvent(mEvent);
		}
		
		void Wait(uint32 timeout)
		{
			WaitForSingleObject(mEvent,timeout);
		}
		
		void Reset()
		{
			ResetEvent(mEvent);
		}
	};
	
#elif defined HOST_MACOSX || defined HOST_IPHONEOS || defined HOST_PS3 || defined HOST_ANDROID

	class CritSect 
	{
	private:
		pthread_mutex_t		mCriticalSection;
		friend class AutoCrit;
		
	public:
		CritSect(void)
		{
			pthread_mutexattr_t		attributes;
			
			pthread_mutexattr_init(&attributes);
			pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_RECURSIVE);
			pthread_mutex_init(&mCriticalSection, &attributes);
			pthread_mutexattr_destroy(&attributes);
		}
		
		~CritSect(void)
		{
			pthread_mutex_destroy(&mCriticalSection);
		}
		
		bool TryLock() { return pthread_mutex_trylock( &mCriticalSection ) == 0; }
		void Lock() {  pthread_mutex_lock( &mCriticalSection ); }
		void Unlock() { pthread_mutex_unlock( &mCriticalSection ); } 
	};
	
	class Condition
	{
	private:
		pthread_mutex_t m_mutex;
		pthread_cond_t m_condition;
		uint32	m_set;
	public:
		Condition()
		{
			m_set = 0;
			pthread_mutex_init(&m_mutex,NULL);
			pthread_cond_init(&m_condition,NULL);
		}
		
		~Condition()
		{
			pthread_cond_destroy(&m_condition);
			pthread_mutex_destroy(&m_mutex);
		}
		
		void Notify()
		{
			pthread_mutex_lock(&m_mutex);
			m_set = 1;
			pthread_cond_signal(&m_condition);
			pthread_mutex_unlock(&m_mutex);
		}
		
		void Reset()
		{
			//this should not need to be interlocked because it is an 
			//overwrite, not a read then write
			m_set=0; 
			//not necessary and dangerous!!
			/*pthread_cond_destroy(&m_condition);
			pthread_mutex_destroy(&m_mutex);
			pthread_mutex_init(&m_mutex,NULL);
			pthread_cond_init(&m_condition,NULL);*/
		}
				
		void Wait(uint32 timeout)
		{
			pthread_mutex_lock(&m_mutex);
			if (!m_set)
			{

				struct timespec ts;
#ifdef HOST_PS3
				sys_time_sec_t now_sec;
				sys_time_nsec_t now_nsec;

				sys_time_get_current_time(&now_sec,&now_nsec);

				uint64 nsec = (uint64)timeout * 1000000;
				ts.tv_nsec = now_nsec;
				ts.tv_sec = now_sec;
				
				ts.tv_nsec += nsec % 1000000000;
				ts.tv_sec += nsec /  1000000000;
				
#else
				struct timeval tv;
				gettimeofday(&tv, NULL);
				
				uint64 nsec = (uint64)timeout * 1000000;
				ts.tv_nsec = tv.tv_usec * 1000;
				ts.tv_sec = tv.tv_sec;
				
				ts.tv_nsec += nsec % 1000000000;
				ts.tv_sec += nsec /  1000000000;
				
#endif
				pthread_cond_timedwait(&m_condition,&m_mutex,&ts);
				

			}
			//this is because the windows code uses autoreset on the event which 
			//unsets the condition the first time a thread finishes waiting for it.
			m_set = 0;
			pthread_mutex_unlock(&m_mutex);
		}
	};
#elif defined HOST_WII
	class CritSect 
	{
	private:
		friend class AutoCrit;
		
	public:
		CritSect(void)
		{
		}
		
		~CritSect(void)
		{
		}
		
		bool TryLock() { return true; };
		void Lock() {  }
		void Unlock() {  } 
	};
	
	class Condition
	{
	private:
	public:
		Condition()
		{
		}
		
		~Condition()
		{
		}
		
		void Notify()
		{
		}
		
		void Wait(uint32 timeout)
		{
		}
	};
#elif defined HOST_AIRPLAY
	class CritSect 
	{
	private:
		friend class AutoCrit;
		
	public:
		CritSect(void)
		{
		}
		
		~CritSect(void)
		{
		}
		
		bool TryLock() {}
		void Lock() {}
		void Unlock() {} 
	};
	
	class Condition
	{
	private:
	public:
		Condition()
		{
		}
		
		~Condition()
		{
		}
		
		void Notify()
		{
		}
		
		void Wait(uint32 timeout)
		{
		}
	};
#elif defined HOST_VITA
class CritSect 
	{
	private:
		SceKernelLwMutexWork	mMutex;
		friend class AutoCrit;
		
	public:
		CritSect(void)
		{
			sceKernelCreateLwMutex(&mMutex, "CritSectObject",
									SCE_KERNEL_LW_MUTEX_ATTR_TH_FIFO, 0, NULL);
		}
		
		~CritSect(void)
		{
			sceKernelDeleteLwMutex(&mMutex);
		}
		
		bool TryLock()
		{
			return sceKernelTryLockLwMutex( &mMutex,1,NULL ) == SCE_OK; 
		}

		void Lock() 
		{  
			sceKernelLockLwMutex( &mMutex,1,NULL ); 
		}

		void Unlock() 
		{ 
			sceKernelUnlockLwMutex( &mMutex, 1); 
		} 

	};
	
	class Condition
	{
	private:
		SceKernelLwMutexWork mMutex;
		SceKernelLwCondWork mCondition;
		uint32	m_set;
	public:
		Condition()
		{
			m_set = 0;

			sceKernelCreateLwMutex(&mMutex, "ConditionMutexObject",
									SCE_KERNEL_LW_MUTEX_ATTR_TH_FIFO, 0, NULL);

			sceKernelCreateLwCond(&mCondition,"ConditionObject",0,&mMutex,NULL);
		}
		
		~Condition()
		{
			sceKernelDeleteLwCond(&mCondition);
			sceKernelDeleteLwMutex(&mMutex);
		}
		
		void Notify()
		{
			sceKernelLockLwMutex( &mMutex,1,NULL ); 
			m_set = 1;
			sceKernelSignalLwCond(&mCondition);
			sceKernelUnlockLwMutex( &mMutex,1); 
		}
		
		void Reset()
		{
			//this should not need to be interlocked because it is an 
			//overwrite, not a read then write
			m_set=0; 
		}
				
		void Wait(uint32 timeout)
		{
			sceKernelLockLwMutex( &mMutex,1,NULL );
			if (!m_set)
			{
				SceUInt32 timeToWait;
				timeToWait = timeout * 1000; //microseconds...
				sceKernelWaitLwCond( &mCondition,&timeToWait );

			}
			//this is because the windows code uses autoreset on the event which 
			//unsets the condition the first time a thread finishes waiting for it.
			m_set = 0;
			sceKernelUnlockLwMutex( &mMutex,1);
		}
	};
#elif defined(WINRT_CLUSTER)
	class CritSect 
	{
	private:
		CRITICAL_SECTION mCriticalSection;
		friend class AutoCrit;

	public:
		CritSect(void)
		{
			InitializeCriticalSectionEx(&mCriticalSection, 0, 0);	// Extra parms are spincount and flags
		}
		
		~CritSect(void)
		{
			DeleteCriticalSection(&mCriticalSection);
		}
		
		bool TryLock() { return TryEnterCriticalSection( &mCriticalSection ) != 0; }
		void Lock() {  EnterCriticalSection( &mCriticalSection ); }
		void Unlock() { LeaveCriticalSection( &mCriticalSection ); } 
	};
	
	class Condition
	{
	private:
		HANDLE mEvent;
	public:
		Condition()
		{
			mEvent = CreateEventEx(NULL, NULL, NULL, EVENT_ALL_ACCESS);
		}
		
		~Condition()
		{
			CloseHandle(mEvent);
		}
		
		void Notify()
		{
			SetEvent(mEvent);
		}
		
		void Wait(uint32 timeout)
		{
			WaitForSingleObjectEx(mEvent,timeout, false);
		}
		
		void Reset()
		{
			ResetEvent(mEvent);
		}
	};
#else
	#error "Need to define CritSec class for this platform!"
#endif
}
#endif // _H_CritSect
