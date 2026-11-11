///////////////////////////////////
//
// time util
//
////////////////////////////////////
#ifndef __TIME_UTIL_H__
#define __TIME_UTIL_H__

class TimeUtil{
public:
	enum TimeLayout
	{
		Layout_ddhh_hhmm_mmss,
		Layout_hhmmsss,
	};

	// check if time eclapse is as certain
	static bool CheckTimeEclapse(pvztime_t delta, pvztime_t startTime);

	// check if time is the next N days
	static bool CheckTimeDayPass(time_t time, int days);

	// check if time is the next N hours
	static bool CheckTimeHourPass(time_t time, int hours);

	// check if time is today
	static bool IsToday(time_t time);

	// check if time is in this week
	static bool IsInThisWeek(time_t time);

	// GET Countdown, 1 get this day, 2 get this week, 3 get the Activity, error return INT_MAX
	static pvztime_t GetTimeCountdown(int index, int activityId = -1);

	//the format is xxxxyyzz
	static int TimeStampToFormatTime(time_t i_time);

	static time_t FormatTimeToTimeStamp(int i_time);

	static pvztime_t GetCurrentFormatTime();

	static SexyString GetTimeCountdownFormat(pvztime_t i_time, TimeLayout i_layout = TimeLayout::Layout_ddhh_hhmm_mmss);
};

#endif
