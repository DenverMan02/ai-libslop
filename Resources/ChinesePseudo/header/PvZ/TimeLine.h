/*

  TimeLine.h
  PlantsVersusZombies2

  Created by Joseph Sola on 4/10/12.
  Copyright (c) 2012 PopCap Games. All rights reserved.

Description:

	At its most basic level, the TimeLine class holds a collection of instantaneous events
	that occur some time in the future, and a marker that remembers its current location.
	
	This is most useful for situations in which you need to wind time forward by a large
	timestep, but want to make sure that you hit certain important events along the way.

	For example, let's say you're writing a particle emitter that should spit out a new
	particle every 0.01 seconds. If the emitter is only updated once a frame, then it's 
	very unlikely that the timestep is smaller than the emission rate, which means you will
	either miss emissions, or all emissions in one step will be emitted at the same location.
	
	If you set these time-critical events up on a TimeLine, then you can use it to move,
	step by step, along any total delta time, ensuring that you stop at each important
	point along the way. 
	
	For a PVZ-specific example of this, look at Projectile::Update
	
Usage:

		// Create a TimeLine
		TimeLine myTimeLineInstance;
		// Set its current time to 0.0
		myTimeLineInstance.Initialize(0.0f);
		// Add a couple events
		myTimeLineInstance.AddEvent(0.1f, MakeDelegate(&PrintTime));
		myTimeLineInstance.AddEvent(0.5f, MakeDelegate(&PrintTime));
		myTimeLineInstance.AddEvent(0.7f, MakeDelegate(&PrintTime));
 
	To move the TimeLine's 'current time' forward, you must use a TimeLine::Updater, like this:

		// Progress 2.5 seconds along the timeline
		TimeLine::Updater myUpdater(myTimeLineInstance, 2.5f);
		printf("Updating for 2.5 seconds...\n");
		while (!myUpdater.IsDone())
		{
			// Move forward, up to the next TimeLineEvent
			myUpdater.Progress();
			// Get the amount of time we JUST progressed through
			pvztime_t stepTime = myUpdater.GetStepTime();
			// Get the total amount of time that we have updated so far
			pvztime_t elapsedTime = myUpdater.GetElapsedTime();
			
			printf("- Stepped %.1f seconds, %.1f seconds total...\n", stepTime, elapsedTime);
			
			// Fire any TimeLineEvent that the Updater stopped at
			myUpdater.FireEvent();
		}
		printf("- Done!\n");

	In the above example, if PrintTime is a function that prints out the pvztime_t value passed 
	into it, then the log output would be:
	
		Updating for 2.5 seconds...
		- Stepped 0.1 seconds, 0.1 seconds total...
		0.1
		- Stepped 0.4 seconds, 0.5 seconds total...
		0.5
		- Stepped 0.2 seconds, 0.7 seconds total...
		0.7
		- Stepped 1.8 seconds, 2.5 seconds total...
		- Done!
*/

#ifndef __TIMELINE_H__
#define __TIMELINE_H__

#include <cstddef>
#include <deque>
#include <vector>

#include "Curve.h"
#include "PlatformAutodetect.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"
#include "SexyAppFramework/Common.h"
#include "SexyMath.h"
#include "SexyVector.h"
#include "TimeMgr.h"
#include "TodDebug.h"

template<typename T>
struct TimeLineKeyFrame
{
	T 			Value;
	pvztime_t 	Time;
	CurveType 	InterpToNextMethod;
};

/// TimeLineTrack is a utility class that holds a series of keyframes and interpolation
/// methods to use between these keyframes.
///		- Initialize() it to a value
///		- Use AddKeyFrame() to add a new keyframe time/value pair with the interpolation
///		method to use when interpolating from this keyframe to the next one
///		- Use GetValueAt() to get the interpolated value at any time


// *** USE CURVESEQUENCE INSTEAD OF TIMELINETRACK ***
// THIS IS OLD
template<typename T>
class TimeLineTrack
{
public:
	typedef T ContainedType;
	
	void Initialize(T i_initialValue)
	{
		m_initialValue = i_initialValue;
		m_keyFrames.clear();
	}
	
	void AddKeyFrame(pvztime_t i_atTime, const T& i_value, CurveType i_interpMethod)
	{
		DBG_ASSERT(m_keyFrames.size() == 0 || i_atTime >= m_keyFrames.back().Time);
		m_keyFrames.resize(m_keyFrames.size() + 1);
		TimeLineKeyFrame<T>& newKeyFrame = m_keyFrames[m_keyFrames.size() - 1];
		newKeyFrame.Value = i_value;
		newKeyFrame.Time = i_atTime;
		newKeyFrame.InterpToNextMethod = i_interpMethod;
	}
	
	T GetValueAt(pvztime_t i_atTime) const
	{
		int i_beforeIdx = -1;
		// Find the keyframe that comes just before this time
		int lastIdx = static_cast<int>(m_keyFrames.size()) - 1;
		for (int i = lastIdx; i >= 0; --i)
		{
			const TimeLineKeyFrame<T>& frame = m_keyFrames[i];
			if (i_atTime >= frame.Time)
			{
				i_beforeIdx = i;
				break;
			}
		}
		if (i_beforeIdx < 0)
		{
			// Before start? Return initial value
			return m_initialValue;
		}
		const TimeLineKeyFrame<T>& beforeFrame = m_keyFrames[i_beforeIdx];
		if (i_beforeIdx == lastIdx)
		{
			// After end? Return final value
			return beforeFrame.Value;
		}
		// Anywhere else? Interp
		const TimeLineKeyFrame<T>& afterFrame = m_keyFrames[i_beforeIdx + 1];
		float alpha = (i_atTime - beforeFrame.Time) / (afterFrame.Time - beforeFrame.Time);
		T retVal = CurveEvaluate<T>(alpha, beforeFrame.Value, afterFrame.Value, beforeFrame.InterpToNextMethod);
		return retVal;
	}

	bool Finished(pvztime_t i_atTime) const
	{
		return i_atTime >= m_keyFrames[m_keyFrames.size() - 1].Time;
	}
	
private:
	T 	m_initialValue;
	std::vector<TimeLineKeyFrame<T> > m_keyFrames;

#ifdef SUPPORT_REFLECTION
	friend class TimeLineReflectionExposer;
#endif
};

template <typename T>
struct CurveSegment
{
	T				StartValue;
	T				EndValue;
	pvztime_t		StartTime;
	pvztime_t		EndTime;
	CurveType		InterpMethod;
	
	void Set(const T& i_startValue, const T& i_endValue, pvztime_t i_startTime, pvztime_t i_endTime, CurveType i_interpMethod)
	{
		StartValue = i_startValue;
		EndValue = i_endValue;
		StartTime = i_startTime;
		EndTime = i_endTime;
		InterpMethod = i_interpMethod;
	}

	T GetValueAt(pvztime_t i_t) const
	{
		float alpha = (i_t - StartTime) / (EndTime - StartTime);
		return CurveEvaluate<T>(alpha, StartValue, EndValue, InterpMethod);
	}
};

template <typename T>
class CurveSequence
{
public:
	void StartSequence(pvztime_t i_startTime, const T& i_startValue)
	{
		m_segments.clear();
		
		CurveSegment<T> newSegment;
		newSegment.Set(i_startValue, i_startValue, i_startTime, i_startTime, CURVE_CONSTANT);
		m_segments.push_back(newSegment);
	}
	void AddCurve(pvztime_t i_duration, const T& i_startValue, const T& i_endValue, CurveType i_interpMethod)
	{
		DBG_ASSERT(i_duration >= 0.0f);
		DBG_ASSERT(!m_segments.empty());
		// New segment start time is previous segment end time
		pvztime_t newStartTime = m_segments[m_segments.size() - 1].EndTime;
		CurveSegment<T> newSegment;
		newSegment.Set(i_startValue, i_endValue, newStartTime, newStartTime + i_duration, i_interpMethod);
		m_segments.push_back(newSegment);
	}
	void AddCurve(pvztime_t i_duration, const T& i_endValue, CurveType i_interpMethod)
	{
		DBG_ASSERT(!m_segments.empty());
		// New segment start value is previous segment end value
		const T& newStartValue = m_segments[m_segments.size() - 1].EndValue;
		AddCurve(i_duration, newStartValue, i_endValue, i_interpMethod);
	}
	
	bool IsTimeInSequence(pvztime_t i_time) const
	{
		return !isTimeBeforeStart(i_time) && !isTimeAfterEnd(i_time);
	}
	T GetValueAt(pvztime_t i_time) const
	{
		if (isTimeBeforeStart(i_time))
		{
			return getStartValue();
		}
		if (isTimeAfterEnd(i_time))
		{
			return getEndValue();
		}
		DBG_ASSERT(IsTimeInSequence(i_time));
		const CurveSegment<T>* containingSegment = findSegmentAt(i_time);
		DBG_ASSERT(containingSegment);
		return containingSegment->GetValueAt(i_time);
	}
	T operator[](pvztime_t i_time) const
	{
		return GetValueAt(i_time);
	}
	
	void Clear()
	{
		m_segments.clear();
	}
	
private:
	bool isTimeBeforeStart(pvztime_t i_time) const
	{
		return (m_segments.empty() || i_time < m_segments[0].StartTime);
	}
	bool isTimeAfterEnd(pvztime_t i_time) const
	{
		return (m_segments.empty() || i_time >= m_segments[m_segments.size() - 1].EndTime);
	}
	T getStartValue() const
	{
		DBG_ASSERT(!m_segments.empty());
		return m_segments[0].StartValue;
	}
	T getEndValue() const
	{
		DBG_ASSERT(!m_segments.empty());
		return m_segments[m_segments.size() - 1].EndValue;
	}
	const CurveSegment<T>* findSegmentAt(pvztime_t i_time) const
	{
		// Before start
		if (m_segments.empty() || i_time < m_segments[0].StartTime)
		{
			return NULL;
		}
		
		for (int i = 0; i < m_segments.size(); ++i)
		{
			const CurveSegment<T>& currentSegment = m_segments[i];
			if (i_time < currentSegment.EndTime)
				return &currentSegment;
		}
		
		// After end
		return NULL;
	}
	
	std::vector<CurveSegment<T> > m_segments;
	
#ifdef SUPPORT_REFLECTION
	friend class TimeLineReflectionExposer;
#endif
};

template<typename T>
class CurveSequenceCollection
{
public:
	// Creates the sequence if it does not exist
	CurveSequence<T>& Get(const std::string& i_sequenceName)
	{
		int idx = getIdxFor(i_sequenceName);
		if (idx == -1)
		{
			idx = createIdxFor(i_sequenceName);
			DBG_ASSERT(idx >= 0);
		}
		return m_sequences[idx];
	}
	CurveSequence<T>& operator[](const std::string& i_sequenceName)
	{
		return Get(i_sequenceName);
	}
	const CurveSequence<T>& Get(const std::string& i_sequenceName) const
	{
		int idx = getIdxFor(i_sequenceName);
		DBG_ASSERT(idx >= 0);
		return m_sequences[idx];
	}
	const CurveSequence<T>& operator[](const std::string& i_sequenceName) const
	{
		return Get(i_sequenceName);
	}
	
	void Clear()
	{
		m_sequenceNames.clear();
		m_sequences.clear();
	}
    
    bool IsEmpty() const
    {
        return m_sequences.size() == 0;
    }
    
private:
	// This should be a map, but the RtSerialization code doesn't support them
	int getIdxFor(const std::string& i_sequenceName) const
	{
		for (int i = 0; i < m_sequenceNames.size(); ++i)
		{
			if (m_sequenceNames[i] == i_sequenceName)
			{
				return i;
			}
		}
		return -1;
	}
	int createIdxFor(const std::string& i_sequenceName)
	{
		DBG_ASSERT(getIdxFor(i_sequenceName) == -1);
		m_sequenceNames.push_back(i_sequenceName);
		m_sequences.push_back(CurveSequence<T>());
		return static_cast<int>(m_sequenceNames.size()) - 1;
	}
	
	std::vector<std::string> m_sequenceNames;
	std::vector<CurveSequence<T> > m_sequences;
#ifdef SUPPORT_REFLECTION
	friend class TimeLineReflectionExposer;
#endif
};

typedef Delegate1<pvztime_t> TimeLineEventCallback;
#ifdef SUPPORT_REFLECTION
typedef RtReflectionDelegate<Delegate1<pvztime_t> > TimeLineEventCallbackReflected;
#endif

struct TimeLineEvent
{
	TimeLineEvent()
		: Time(0.f)
	{}
	TimeLineEvent(pvztime_t i_atTime)
	{
		Time = i_atTime;
	}
	TimeLineEvent(pvztime_t i_atTime, TimeLineEventCallback i_eventCallback)
	{
		Time = i_atTime;
		Event = i_eventCallback;
	}
	TimeLineEvent(pvztime_t i_atTime, TimeLineEventCallbackReflected i_reflectedEventCallback)
	{
		Time = i_atTime;
		ReflectableEvent = i_reflectedEventCallback;
	}

	pvztime_t Time;
	TimeLineEventCallback Event;
#ifdef SUPPORT_REFLECTION
	TimeLineEventCallbackReflected ReflectableEvent;
#endif
};

class TimeLine
{
public:
	class Updater
	{
	public:
		/// Initialize
		
		Updater(TimeLine& i_timeLine, pvztime_t i_dt) 
		: m_timeLine(i_timeLine)
		, m_stoppedAtEvent(false)
		, m_totalDt(i_dt)
		, m_remainingDt(i_dt)
		{}
		
		/// Iterate / Test completion
		
		inline void Progress()
		{
			if (m_stoppedAtEvent)
			{
				// Progress past this event (that we hit last frame),
				// and consume it in the process
				m_timeLine.m_events.pop_front();
				m_stoppedAtEvent = false;
			}
			
			const int numEvents = (int)m_timeLine.m_events.size();
			
			// Determine how far forward we can possibly go
			if (numEvents == 0)
			{
				// No events left, run through to the end
				m_lastStep = m_remainingDt;
			}
			else
			{
				const TimeLineEvent& nextEvent = m_timeLine.m_events.front();
				if (m_timeLine.m_currTime + m_remainingDt >= nextEvent.Time)
				{
					// We're going to hit an event, run up to that point
					m_stoppedAtEvent = true;
					m_lastStep = nextEvent.Time - m_timeLine.m_currTime;
				}
				else
				{
					// No upcoming events
					m_lastStep = m_remainingDt;
				}
			}
			
			// Update time values from dt
			m_timeLine.m_currTime += m_lastStep;
			m_remainingDt -= m_lastStep;
		}

		inline bool IsDone() const
		{
			return (m_remainingDt <= 0.0f);
		}
		
		/// Access values at our stopping point
		
		inline pvztime_t GetElapsedTime() const
		{
			return m_totalDt - m_remainingDt;
		}
		inline pvztime_t GetStepLength() const
		{
			return m_lastStep;
		}
		inline void FireEvent()
		{
			if (m_stoppedAtEvent)
			{
				TimeLineEvent& nextEvent = m_timeLine.m_events.front();
				if (nextEvent.Event)
				{
					nextEvent.Event(m_timeLine.m_currTime);
				}
#ifdef SUPPORT_REFLECTION
				if (nextEvent.ReflectableEvent)
				{
					nextEvent.ReflectableEvent.GetDelegate()(m_timeLine.m_currTime);
				}
#endif
			}
		}
		
	private:
		TimeLine& m_timeLine;
		pvztime_t m_totalDt;
		pvztime_t m_remainingDt;
		pvztime_t m_lastStep;
		bool m_stoppedAtEvent;
	};
	
	
	TimeLine()
	: m_currTime(0.0)
	, m_needSort(false)
	{}
	
	inline void Initialize(pvztime_t i_startTime)
	{
		m_currTime = i_startTime;
		m_events.clear();
	}
	
	inline void AddEvent(pvztime_t i_atTime, TimeLineEventCallback i_eventCallback)
	{
		TimeLineEvent newEvent(i_atTime, i_eventCallback);
		AddEvent(newEvent);
	}
#ifdef SUPPORT_REFLECTION
	inline void AddEvent(pvztime_t i_atTime, TimeLineEventCallbackReflected i_eventCallbackReflected)
	{
		TimeLineEvent newEvent(i_atTime, i_eventCallbackReflected);
		AddEvent(newEvent);
	}
#endif
	inline void AddEvent(const TimeLineEvent& i_event)
	{
		// Make sure it's within a valid time
		DBG_ASSERT(i_event.Time >= m_currTime);
		// If this event comes before our last event, then we will re-sort on next Update()
		if (m_events.size() > 0 && i_event.Time < m_events.back().Time)
			m_needSort = true;

		m_events.push_back(i_event);
	}
	
	void Update(pvztime_t i_dt)
	{
		if (m_needSort)
		{
			auto sortEarliestToLatest = [](const TimeLineEvent& a, const TimeLineEvent& b) { return a.Time < b.Time; };
			std::sort(m_events.begin(), m_events.end(), sortEarliestToLatest);
			m_needSort = false;
		}

		Updater updater(*this, i_dt);
		while (!updater.IsDone())
		{
			updater.Progress();
			updater.FireEvent();
		}
	}
	
	pvztime_t GetCurrentTime() const
	{
		return m_currTime;
	}

#ifndef RELEASEFINAL
	class TimeLineVerifier
	{
	public: 
		TimeLineVerifier(pvztime_t i_expectedTime)
		: m_expectedValue(i_expectedTime)
		, m_success(false)
		{}
		
		void Verify(pvztime_t i_currTime)
		{
			OutputDebugStrF("> TimeLineVerifier Event HIT at %.2fs ", i_currTime);
			m_success = (SexyMath::ApproxEquals<pvztime_t>(i_currTime, m_expectedValue, SEXYMATH_EPSILON));
			if (m_success)
			{
				OutputDebugStrF("(ok!)\n");
			}
			else
			{
				OutputDebugStrF("(FAILURE: Expected %.2fs)\n", m_expectedValue);
			} 
		}
		bool DidSucceed() const
		{
			return m_success;
		}
	private:
		pvztime_t m_expectedValue;
		bool m_success;
		bool m_needSort;
	};
	
	static bool RunTimeLineTests()
	{
		// Test a simple timeline. One event at 1.0, one timestep of 2.0
		{
			TimeLine testTimeLine;
			TimeLineVerifier verify(1.0f);
			testTimeLine.AddEvent(1.0f, MakeDelegate(verify, &TimeLineVerifier::Verify));
			pvztime_t totalElapsed = 0.0;
			bool success = true;
			OutputDebugStrF("! Updating for 2.0s\n");
			TimeLine::Updater update(testTimeLine, 2.0);
			while (!update.IsDone())
			{
				update.Progress();
				update.FireEvent();
			}
			totalElapsed = update.GetElapsedTime();
			OutputDebugStrF("- Done updating, elapsed %.2fs\n", totalElapsed);
			bool rightTime = SexyMath::ApproxEquals<pvztime_t>(totalElapsed, 2.0, SEXYMATH_EPSILON);
			success &= rightTime;
			success &= verify.DidSucceed();
			if (!success)
			{
				OutputDebugStrF("XXX Test Failed! XXX\n");
			}
			else
			{
				OutputDebugStrF("+ Test succeeded!\n");
			}
		}
		
		// Test a simple timeline with a lot of updates. One event at 1.0, one hundred timesteps of 0.02
		{
			TimeLine testTimeLine;
			TimeLineVerifier verify(1.0);
			testTimeLine.AddEvent(1.0, MakeDelegate(verify, &TimeLineVerifier::Verify));
			pvztime_t totalElapsed = 0.0f;
			bool success = true;
			pvztime_t dT = 0.02f;	
			for (int i = 0; i < 100; ++i)
			{
				OutputDebugStrF("! Elapsed so far %.2fs, Updating for %.2fs\n", totalElapsed, dT);
				TimeLine::Updater update(testTimeLine, dT);
				while (!update.IsDone())
				{
					update.Progress();
					update.FireEvent();
				}
				totalElapsed += update.GetElapsedTime();
			}
			OutputDebugStrF("- Done updating, elapsed %.2fs\n", totalElapsed);
			bool rightTime = SexyMath::ApproxEquals<pvztime_t>(totalElapsed, 2.0, SEXYMATH_EPSILON);
			success &= rightTime;
			success &= verify.DidSucceed();
			if (!success)
			{
				OutputDebugStrF("XXX Test Failed! XXX\n");
			}
			else
			{
				OutputDebugStrF("+ Test succeeded!\n");
			}
		}
		
		// Test many events, one large time step
		{
			TimeLine testTimeLine;
			std::vector<TimeLineVerifier*> verifiers;
			for (int i = 0; i < 10; ++i)
			{
				TimeLineVerifier* newVerify = new TimeLineVerifier(i / 10.0);
				verifiers.push_back(newVerify); // Put an event on 0.0, 0.1, ... 0.9
				testTimeLine.AddEvent(i / 10.0, MakeDelegate(*newVerify, &TimeLineVerifier::Verify));
			}
			
			pvztime_t totalElapsed = 0.0;
			bool success = true;
			OutputDebugStrF("! Updating for 1.0s\n");
			TimeLine::Updater update(testTimeLine, 1.0);
			while (!update.IsDone())
			{
				update.Progress();
				update.FireEvent();
			}
			totalElapsed = update.GetElapsedTime();
			OutputDebugStrF("- Done updating, elapsed %.2fs\n", totalElapsed);
			bool rightTime = SexyMath::ApproxEquals<pvztime_t>(totalElapsed, 1.0, SEXYMATH_EPSILON);
			success &= rightTime;
			for (int i = 0; i < 10; ++i)
			{
				success &= verifiers[i]->DidSucceed();
				delete verifiers[i];
			}
			if (!success)
			{
				OutputDebugStrF("XXX Test Failed! XXX\n");
			}
			else
			{
				OutputDebugStrF("+ Test succeeded!\n");
			}
		}
		
		// Test many random events, many random time steps
		{
			const pvztime_t k_totalTime = 5.0f;
			const pvztime_t k_maxTimeStep = 0.1f;
			const pvztime_t k_minTimeStep = 0.01f;
			TimeLine testTimeLine;
			std::vector<TimeLineVerifier*> verifiers;
			pvztime_t currTime = 0.0;
			currTime = currTime + Rand((float)(k_maxTimeStep - k_minTimeStep)) + k_minTimeStep;
			while (currTime < k_totalTime)
			{
				TimeLineVerifier* newVerify = new TimeLineVerifier(currTime);
				verifiers.push_back(newVerify);
				testTimeLine.AddEvent(currTime, MakeDelegate(*newVerify, &TimeLineVerifier::Verify));
				currTime = currTime + Rand((float)(k_maxTimeStep - k_minTimeStep)) + k_minTimeStep;
			};

			bool success = true;
			pvztime_t elapsedTime = 0.0;
			while (elapsedTime < k_totalTime)
			{
				pvztime_t currStep = Rand((float)(k_maxTimeStep - k_minTimeStep)) + k_minTimeStep;
				if (currStep + elapsedTime > k_totalTime)
					currStep = k_totalTime - elapsedTime;
				
				OutputDebugStrF("! Elapsed so far %.2fs, Updating for %.2fs\n", elapsedTime, currStep);
				TimeLine::Updater update(testTimeLine, currStep);
				while (!update.IsDone())
				{
					update.Progress();
					update.FireEvent();
				}
				elapsedTime += currStep;
			}
			
			OutputDebugStrF("- Done updating, elapsed %.2fs\n", elapsedTime);
			bool rightTime = SexyMath::ApproxEquals<pvztime_t>(elapsedTime, k_totalTime, SEXYMATH_EPSILON);
			success &= rightTime;
			for (int i = 0; i < (int)verifiers.size(); ++i)
			{
				success &= verifiers[i]->DidSucceed();
				delete verifiers[i];
			}
			if (!success)
			{
				OutputDebugStrF("XXX Test Failed! XXX\n");
			}
			else
			{
				OutputDebugStrF("+ Test succeeded!\n");
			}
		}
		
		return true;
	}
#endif // RELEASEFINAL
	
private:
	pvztime_t m_currTime;
	std::deque<TimeLineEvent> m_events;
	bool m_needSort;

#ifdef SUPPORT_REFLECTION
	friend class TimeLineReflectionExposer;
#endif
};

#ifdef SUPPORT_REFLECTION

// This is all here to support serializing these tracks in and out
// Note that if you're using these types of TimeLineTracks, you should use TimeLineTrack_TYPE in your
// reflection builder blocks.

typedef TimeLineKeyFrame<int> TimeLineKeyFrame_Int;
typedef TimeLineTrack<int> TimeLineTrack_Int;

typedef TimeLineKeyFrame<float> TimeLineKeyFrame_Float;
typedef TimeLineTrack<float> TimeLineTrack_Float;

typedef TimeLineKeyFrame<SexyVector3> TimeLineKeyFrame_SexyVector3;
typedef TimeLineTrack<SexyVector3> TimeLineTrack_SexyVector3;

typedef CurveSegment<float>	CurveSegment_Float;
typedef CurveSequence<float> CurveSequence_Float;
typedef CurveSequenceCollection<float> CurveCollection_Float;

typedef CurveSegment<SexyVector3> CurveSegment_SexyVector3;
typedef CurveSequence<SexyVector3> CurveSequence_SexyVector3;
typedef CurveSequenceCollection<SexyVector3> CurveCollection_SexyVector3;

typedef CurveSegment<Color> CurveSegment_Color;
typedef CurveSequence<Color> CurveSequence_Color;
typedef CurveSequenceCollection<Color> CurveCollection_Color;

// This is a dummy class to ensure that these values are exposed to the serialization system
class TimeLineReflectionExposer : public RtObject
{
public:
	RT_CLASS_DEFINE(TimeLineReflectionExposer, RtObject, RtClass);
};

#endif

#endif // __TIMELINE_H__
