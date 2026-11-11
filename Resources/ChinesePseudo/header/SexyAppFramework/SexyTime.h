#pragma once
#ifndef SEXYTIME_H_INCLUDED
#define SEXYTIME_H_INCLUDED

#include "Common.h"
/**
 * Sexy..Time...
 *
 * SexyTime is a cross-platform replacement for GetTickCount on Windows
 * it returns time in milliseconds, but can only be trusted for relative comparisions
 * it is NOT an absolute time (and may not be from program start on some platforms)
 */
#if defined HOST_MACOSX || defined HOST_IPHONEOS
#include <mach/mach_time.h>
#endif

#if defined HOST_ANDROID
#include <sys/time.h>
#endif

namespace Sexy 
{
#if defined HOST_PS3
#include <sys/sys_time.h>
	
	inline uint64 SexyTime()
	{
		system_time_t t;
		t = sys_time_get_system_time();
		t /= 1000;
		return t;
	}

#elif defined RVL_OS

	inline uint64 SexyTime()
	{
		OSTime t;
		t = OSGetTime();
		t /= OS_TIMER_CLOCK/1000;
		return t;
	}
	
#elif defined HOST_MACOSX || defined HOST_IPHONEOS
	
	inline uint64 get_mach_frequency()
	{
		static mach_timebase_info_data_t    sTimebaseInfo;
		if ( sTimebaseInfo.denom == 0 ) {
			(void) mach_timebase_info(&sTimebaseInfo);
		}
		
		return (uint64_t)1000000 * (uint64_t)sTimebaseInfo.denom / (uint64_t)sTimebaseInfo.numer;
	}
	
	inline uint64 get_mach_perf_frequency()
	{
		static mach_timebase_info_data_t    sTimebaseInfo;
		if ( sTimebaseInfo.denom == 0 ) {
			(void) mach_timebase_info(&sTimebaseInfo);
		}
		
		return (uint64_t)1000 * (uint64_t)sTimebaseInfo.denom / (uint64_t)sTimebaseInfo.numer;
	}
	
	inline uint64 SexyTime()
	{
		uint64 t;
		t = mach_absolute_time();
		t /= get_mach_frequency();
		return t;
	}
	
	//returns time in microseconds
	inline uint64 SexyPerfTime()
	{
		uint64 t;
		t = mach_absolute_time();
		t /= get_mach_perf_frequency();
		return t;
	}

#elif defined HOST_WINDOWS
	
	inline uint64 SexyTime()
	{
		return timeGetTime();
	}
#elif defined(WINRT_CLUSTER)
	inline uint64 SexyTime()
	{
		return GetTickCount64();
	}
#elif defined HOST_XBOX360
	inline uint64 SexyTime()
	{
		return GetTickCount();
	}
#elif defined HOST_AIRPLAY
	inline uint64 SexyTime()
	{
		return s3eTimerGetMs();
	}
#elif defined HOST_VITA

	inline uint64 SexyTime()
	{
		return sceKernelGetProcessTimeWide()/1000;
	}
#elif defined HOST_ANDROID
	inline uint64 SexyTime()
	{
	    struct timeval tv;
	    gettimeofday(&tv, NULL);

	    return ((uint64)tv.tv_sec)*1000 + ((uint64)tv.tv_usec)/1000;
	}


	//returns time in microseconds
	inline uint64 SexyPerfTime()
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);

		return ((uint64)tv.tv_sec)*1000000 + (uint64)tv.tv_usec;
	}

#else
	#error "Need to define SexyTime for this platform."
#endif

}
#endif
