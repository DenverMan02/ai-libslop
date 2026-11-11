//
//  Timer.h
//  PlantsVersusZombies2
//
//  Created by Knapp, Randy on 3/3/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef Timer_h
#define Timer_h

#include "TimeMgr.h"
#include "RtDelegate.h"

namespace PvZ2 { namespace Utilities
{
	class Timer
	{
	public:
		typedef Sexy::Delegate0 TimeoutCallback;
		
	private:
		pvztime_t m_timerLength = -1;
		pvztime_t m_endTime = -1;
		TimeoutCallback m_callback;
		
	public:
		Timer();
		Timer(pvztime_t i_timerLength, const TimeoutCallback& callback);
		void Update();
		void Reset();
		void Reset(pvztime_t i_newTimerLength);
		void Clear();
		void SetCallback(const TimeoutCallback& callback);
		
	private:
		void triggerCallback();
	};
}}

#endif /* Timer_h */
