#ifndef __SEXY_PERFTIMER_H__
#define __SEXY_PERFTIMER_H__

#include "Common.h"
#include "SexyTime.h"

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4005)
#endif

#ifdef SUPPORT_RADTELEMETRY
#include "SexyAppFramework/extern/radtelemetry/TelemetrySDKWin32/include/telemetry.h"
extern HTELEMETRY gRadTelemetry;
extern uchar* gRadTelemetryStaticBuffer;
const int kRadTelemetryStaticBufferSize = 2*1024*1024;
#endif

namespace Sexy
{
//JVW - PerfTiming will require different code per plat
// for now, I'll ifdef it 


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#if defined HOST_WINDOWS
class PerfTimer 
{
protected:
	LARGE_INTEGER mStart;
	double mDuration;
	bool mRunning;

	void CalcDuration();

public:
	PerfTimer();
	void Start();
	void Stop();

	double	GetDuration();
	bool	IsRunning() const	{return mRunning;}

	static int64 GetCPUSpeed(); // in Hz
	static int GetCPUSpeedMHz(); 
};
	
#else
	
	//default implementation will just use SexyTime
	class PerfTimer 
	{
	protected:
		uint64 mStart;
		double mDuration;
		bool mRunning;
		
		//returns time in milliseconds
		void CalcDuration() { mDuration = (double)(SexyTime() - mStart); }
	public:
		PerfTimer() { mRunning = false; }
		
		void Start() { mStart = SexyTime(); mRunning = true; }
		void Stop()  { CalcDuration(); mRunning = false; }
		
		double	GetDuration() { if (mRunning) CalcDuration(); return mDuration; }
		bool	IsRunning() const	{return mRunning;}
		
		static int64 GetCPUSpeed(); // in Hz
		static int GetCPUSpeedMHz(); 
	};
#endif

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class SexyPerf
{
public:
	static void BeginPerf(bool measurePerfOverhead = false, bool recordSession = false);
	static void EndPerf();
	static bool IsPerfOn();
	static bool IsPerfRecording();

	static bool StartTiming(const char *theName);
	static void StopTiming(const char *theName);

	static void ClearFrameInfo();

	static std::string GetResults();
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class SexyAutoPerf
{
public:
	const char *mName;
	bool mIsStarted;

	SexyAutoPerf(const char *theName) : mName(theName), mIsStarted(false) 
    { 
        if (SexyPerf::StartTiming(theName))
            mIsStarted = true;
    }
	SexyAutoPerf(const char *theName, bool doStart) : mIsStarted(false), mName(theName) 
	{ 
		if(doStart) 
        {
			if (SexyPerf::StartTiming(theName))
                mIsStarted = true;
        }
	}

	~SexyAutoPerf() { Stop(); }

	void Start()
	{
		if(!mIsStarted)
		{
			if (SexyPerf::StartTiming(mName))
                mIsStarted = true;
		}
	}

	void Stop() 
	{ 
		if(mIsStarted) 
		{ 
			SexyPerf::StopTiming(mName);
			mIsStarted = false;
		}
	}
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define SEXY_PERF_ENABLED

#if defined(SEXY_PERF_ENABLED) && (!defined(RELEASEFINAL) || defined(PVZ2_PROFILE))

#define SEXY_PERF_BEGIN(theName) SexyPerf::StartTiming(theName)
#define SEXY_PERF_END(theName) SexyPerf::StopTiming(theName)
#define SEXY_AUTO_PERF_MULTI(theName,theSuffix) Sexy::SexyAutoPerf anAutoPerf##theSuffix(theName)
#define SEXY_AUTO_PERF_2(theName,theSuffix) SEXY_AUTO_PERF_MULTI(theName,theSuffix)
#define SEXY_AUTO_PERFL(theName) SEXY_AUTO_PERF_2(theName,__LINE__) // __LINE__ doesn't work correctly if Edit-and-Continue (/ZI) is enabled
#define SEXY_AUTO_PERF(theName) SEXY_AUTO_PERF_2(theName,UNIQUE)

#define SEXY_PERF_BEGIN_COND(theName,theCond) if(theCond) SexyPerf::StartTiming(theName)
#define SEXY_PERF_END_COND(theName,theCond) if(theCond) SexyPerf::StopTiming(theName)
#define SEXY_AUTO_PERF_MULTI_COND(theName,theSuffix,theCond) SexyAutoPerf anAutoPerf##theSuffix(theName,theCond); 
#define SEXY_AUTO_PERF_COND_2(theName,theSuffix,theCond) SEXY_AUTO_PERF_MULTI_COND(theName,theSuffix,theCond); 
#define SEXY_AUTO_PERF_CONDL(theName,theCond) SEXY_AUTO_PERF_COND_2(theName,__LINE__,theCond)
#define SEXY_AUTO_PERF_COND(theName,theCond) SEXY_AUTO_PERF_COND_2(theName,UNIQUE,theCond)

#ifdef SUPPORT_RADTELEMETRY
#undef SEXY_AUTO_PERF
#define SEXY_AUTO_PERF(theName) tmZone(gRadTelemetry, TMZF_NONE, theName)
#endif

#else

#define SEXY_PERF_BEGIN(theName) 
#define SEXY_PERF_END(theName) 
#define SEXY_AUTO_PERF_MULTI(theName,theSuffix)
#define SEXY_AUTO_PERF_2(theName,theSuffix)
#define SEXY_AUTO_PERFL(theName)
#define SEXY_AUTO_PERF(theName)

#define SEXY_PERF_BEGIN_COND(theName,theCond) 
#define SEXY_PERF_END_COND(theName,theCond) 
#define SEXY_AUTO_PERF_MULTI_COND(theName,theSuffix,theCond) 
#define SEXY_AUTO_PERF_COND_2(theName,theSuffix,theCond)
#define SEXY_AUTO_PERF_CONDL(theName,theCond)
#define SEXY_AUTO_PERF_COND(theName,theCond) 

#endif

}
#ifdef WIN32
#pragma warning(pop)
#endif

#endif
