//
//  TimeMgr.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 4/2/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_TimeMgr_h
#define PlantsVersusZombies2_TimeMgr_h

#include "Singleton.h"
#include <limits>

#define SECONDS_PER_HOUR (60 * 60)
#define SECONDS_PER_DAY (SECONDS_PER_HOUR * 24)

bool DateStringToTM(const std::string& i_date, tm& o_date);
std::string TimeToStringDHMS(time_t secondsFromNow);

typedef float pvztime_t;
typedef double pvzAccumulatedTime_t;
typedef uint64 serializable_time_t;

namespace Message
{
	void NotifyReachMaxInterval();
}

class TimeMgr: public LazySingleton<TimeMgr> 
{    
public:
	void Init();
	void Update();
    
    
    // This is the game clock.
	pvztime_t       T();
    pvztime_t       Dt();
    pvztime_t       InvDt();
    
	void			SetT(pvztime_t i_newTime);
	
    void            SetTimeScale(pvztime_t i_timeScale);
    pvztime_t       GetTimeScale();
    inline void     Pause(bool i_pause);
    bool            IsPaused();
	inline void		SetPauseAfterUpdate(bool i_shouldPause);
    
    // This is the real accumulated clock.
	pvztime_t       RealT();
	pvztime_t       RealDt();

    pvztime_t       CinematicT();
    pvztime_t       CinematicDt();

    float           GetCurrentFPS();
    
    void            PauseGameOnly(bool i_pause);

    time_t GetDate();
    void SetDateOverride(time_t i_date);
    void ClearDateOverride();
    
    void            SetFixedSPF(pvztime_t fVal);
    bool GameIsPause();
    void			SetMaxInterval(float i_maxInterval) { m_maxInterval = i_maxInterval; }
private:
    uint64      m_timeStart;         // start time of game
    uint64      m_timeCurrent;       // current time. 
    
    pvztime_t   m_realT;          // time since start not absolute.
    pvztime_t   m_realDt;

    float       m_currentFPS; // our current fps calculated by 1/dt. 
    
    // virtual time can be paused and dilated. 
	pvztime_t   m_virtualizedT;
	pvztime_t   m_virtualizedDt;
    pvztime_t   m_virtualizedInvDt;
    pvztime_t   m_timeScale;
    bool        m_paused;
	uint8		m_pauseAfterUpdateCount;

    pvztime_t   m_cinematicT;
    pvztime_t   m_cinematicDt;
    bool        m_gameOnlyPause;

    time_t      m_overrideDelta;
    
    // Calculate new FPS
    unsigned int m_frames;
    float        m_accumDT;
    
    pvztime_t   m_fixedSPF;
    float 		m_maxInterval;
    
};

#define gTimeMgr (TimeMgr::GetInstancePtr())

inline pvztime_t PVZ_T() {return gTimeMgr->T(); }

inline pvztime_t PVZ_Dt(){return gTimeMgr->Dt();}
inline pvztime_t PVZ_InvDt() { return gTimeMgr->InvDt(); }

inline pvztime_t PVZ_RealT() {return gTimeMgr->RealT(); }
inline pvztime_t PVZ_RealDt(){return gTimeMgr->RealDt();}

inline bool PVZ_IS_IT(pvztime_t time) {return gTimeMgr->T() >= time;}
inline bool	PVZ_IS_NOT(pvztime_t time) {return gTimeMgr->T() < time;}

//end of time, note: this is the maximum value of type pvztime_t.
#if defined(HOST_IPHONEOS)
inline pvztime_t        PVZ_EOT() 
{
	return std::numeric_limits<pvztime_t>::max(); 
}
#elif defined(HOST_WINDOWS)
pvztime_t        PVZ_EOT();
#else
inline pvztime_t        PVZ_EOT()
{
	return std::numeric_limits<pvztime_t>::max();
}
#endif

inline void TimeMgr::Pause(bool i_pause)
{
    m_paused = i_pause;
}

inline void TimeMgr::SetPauseAfterUpdate(bool i_shouldPause)
{
	m_paused = false;
	m_pauseAfterUpdateCount = i_shouldPause ? 1 : 0;
}

inline pvztime_t TimeMgr::T()  
{ 
    return m_virtualizedT;
}
inline pvztime_t TimeMgr::Dt() 
{ 
    return m_virtualizedDt;
}
inline void TimeMgr::SetTimeScale(pvztime_t i_timeScale) 
{
    m_timeScale = i_timeScale; 
}
inline pvztime_t TimeMgr::GetTimeScale()
{
    return m_timeScale;
}
inline bool TimeMgr::IsPaused()
{
    return m_paused; 
}

inline pvztime_t TimeMgr::RealT() 
{ 
    return m_realT; 
}
inline pvztime_t TimeMgr::RealDt() 
{ 
    return m_realDt; 
}

inline float TimeMgr::GetCurrentFPS()
{
    return m_currentFPS;
}

inline pvztime_t TimeMgr::CinematicT()
{
    return m_cinematicT;
}

inline pvztime_t TimeMgr::CinematicDt()
{
    return m_cinematicDt;
}

#endif
