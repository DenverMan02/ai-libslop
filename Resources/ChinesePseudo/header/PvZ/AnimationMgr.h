//
//  AnimationMgr.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 12/13/11.
//  Copyright (c) 2011 PopCap. All rights reserved.
//

#ifndef PlantsVersusZombies2_AnimationMgr_h
#define PlantsVersusZombies2_AnimationMgr_h

/*
 Animation Manager. 
 
 Description: 
 
    The AnimationMgr is a time line manager used to control and manage a sequence of animations and events. 
 
    Animations and events are added to the time line to be triggered at a certain time, for a certain time. 
    
    Animations are aribitrary objects that conform to the animation controller interface. They have a time range, and are udpated. 
 
    Events are object to method bindings that are triggered at a certain time. 
 
 Usage:
    For example when the level starts a series of things happen to introduce the level to the player. The board pans, 
 gravestones are placed, zombies are spread in their starting zone. Each of these are events and actions that are 
 triggered and updated in time. 
 
    First we create the items we want to place on the time line. 
 
    CurveAnimMove is a controller that changes the values passed into a "Move(x, y)" method on an object.
 
    CurveAnimMove<Board>* slideBoardLeft = new CurveAnimMove<Board>(this, 10 (seconds), fromX, toX, fromY, toY);
 
    TimeEvent<Board>* placeZombies = new TimeEvent<Board>(this, &Board::PlaceIntroZombies);
 
 
    Now we add them to the animation manager.
 
    pvztime_t curAnimMgrTime = m_animationMgr.GetTime();
    pvztime_t endTime;
 
    // start the slideBoardLeft a second from now. Get the slide board end time. 
    m_animationMgr.Add(slideBoardLeft, curAnimMgrTime + 1.0f, endTime);
 
    // start placeZombies a second before the end of the slideBoardLeft end. 
    m_animationMgr.Add(placeZombies, endTime - 1.0f);
 

 The animation manager has to be updated each frame. It uses the game clock in its sequences.  
 
 */


#include "core.h"
#include "Curve.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"
#include "GameObject.h"

class AnimationMgr;

struct AnimatedPoint : public Sexy::Point
{
	void Move(int i_x, int i_y)
	{
		mX = i_x;
		mY = i_y;
	}
};

//
// Animation controller base type. 
// Derive from this class to make sequencable objects. 
// 
// notes: 
//  the range is inclusive (0 1) will hit both 0 and 1. 
//
//  The AnimationMgr will delete the AnimationController when its time has run out if m_deleteOnEnd is true.
//  To not autodelete the instance, set SetDeleteWhenDone(false); The caller will be responsible for deleting the animation controller. 
//
class AnimationController : public GameObject
{
  public:
    RT_CLASS_DEFINE(AnimationController, GameObject, RtClass);

    AnimationController(pvztime_t i_duration = 0.0f, bool i_deleteOnEnd=true)
    {
        m_startTime = 0;
        SetDuration(i_duration);
        m_deleteOnEnd = i_deleteOnEnd;
        
        SetDescription("AnimationController");
    }

    
    void Init(pvztime_t i_duration, bool i_deleteOnEnd=true)
    {
        m_startTime = 0;
        SetDuration(i_duration);
        m_deleteOnEnd = i_deleteOnEnd;
        
        SetDescription("AnimationController");
    }
    
    pvztime_t         GetEndTime()    { return m_endTime; }
    pvztime_t         GetStartTime()  { return m_startTime; }
    pvztime_t         GetDuration()   { return m_duration; }
    
    void SetDuration(pvztime_t i_duration)
    {
        m_duration = i_duration;
        m_endTime = m_startTime + m_duration;
    }
    
    bool InRange(pvztime_t i_time) 
    {
        // special case for duration 0 events. 
        if (GetDuration() == 0 && i_time >= GetEndTime())
        {
            return true;
        }
        
        if (i_time >= m_startTime && i_time <= m_endTime)
            return true;
        return false;
    }
    
    
    void SetDeleteWhenDone(bool i_deleteOnEnd) { m_deleteOnEnd = i_deleteOnEnd; }
    bool DeleteWhenDone() { return m_deleteOnEnd; }
    
    virtual bool IsAnimDone(pvztime_t i_time)
    {
        if (i_time >= m_endTime)
            return true;
        return false;
    }
    
    
    virtual void Update(pvztime_t i_time) {}
	virtual void AddToRenderQueue(class RenderQueue* i_queue)
    {
        
    }
	virtual void InnerDraw(Graphics* i_g) {}
    
    void SetDescription(const std::string& i_desc) { m_description = i_desc; }
    std::string GetDescription() { return m_description; }
    
    virtual void onDestroy() override;
    
private:
    friend class AnimationMgr;
    
    void SetStartTime(pvztime_t i_startTime) // available only to AnimationMgr... 
    {
        m_startTime = i_startTime; m_endTime = m_startTime + m_duration;
    }
    
    // - should we update? note that if time has passed, this will be removed from the update list. 
    bool ShouldUpdate(pvztime_t i_time) // available only to AnimationMgr
    {
        if (GetDuration() == 0 && i_time >= GetEndTime()) 
        {
            return true;
        }
        
        if (i_time >= m_startTime)
            return true;
        
        return false;
    }
    
    pvztime_t  m_startTime;     // min max time range (inclusive range). This isn't accessible to the user. Start/End time is set when the animation controller is added to the animation manager.
    pvztime_t  m_endTime;     // min max time range (inclusive range). This isn't accessible to the user. Start/End time is set when the animation controller is added to the animation manager.
    pvztime_t  m_duration;     // the duration of the motion.
    bool m_deleteOnEnd;  // if true, the animation manager has ownership of this object and will delete it when it times out. This allows for fire and forget objects. 

    std::string m_description;
};

typedef RtWeakPtr<AnimationController> AnimationControllerWkPtr;

// 
// call function at a certain time on a target. 
//
class TimeEvent: public AnimationController 
{
public:
    typedef  RtReflectionDelegate<Delegate0> TimeEventDelegate;
public:
    RT_CLASS_DEFINE(TimeEvent, AnimationController,RtClass);

    static TimeEvent* Create()
    {
        return GameObject::Create<TimeEvent>(PVZDB::TABLE_GAMEOBJECTS);
    }
    
    static TimeEvent* Create(RtId i_callee, const std::string& i_method)
    {
        TimeEvent* timeEvent = Create();
        timeEvent->Init(i_callee, i_method);
        return timeEvent;
    }
    
    TimeEvent* Init(RtId i_callee, const std::string& i_method)
    {
        m_delegate = TimeEventDelegate(i_callee, i_method);
        return this;
    }
    
    TimeEvent* Init(TimeEventDelegate i_delegate)
    {
        SuperClass::Init(0.0f);
        SetDescription("TimeEvent");
        return this;
    }
    
    void Update(pvztime_t i_time) override
    {
        m_delegate.GetDelegate()();
    }
    
private:
    
    TimeEventDelegate m_delegate;
};

//
// AnimationMgr
// 
class AnimationMgr : public GameObject
{
public:
    RT_CLASS_DEFINE(AnimationMgr, GameObject, RtClass);
    
    static AnimationMgr* Create()
    {
        return GameObject::Create<AnimationMgr>(PVZDB::TABLE_GAMEOBJECTS);
    }

	AnimationMgr()
		: m_time(0.f)
		, m_pause(false)
		, m_removing(false)
	{}
    
    void Update();
    void AddToRenderQueue(class RenderQueue* i_queue);
    void InnerDraw(Graphics* i_g);

    virtual bool Serialize(const RtSerializeContext& inContext) override;

    // fluent + passing gameobject
    AnimationMgr* Add(AnimationController* i_motion, pvztime_t i_startTime, pvztime_t& o_endTime); // o_endTime is end time of the just inserted motion.
    AnimationMgr* Add(AnimationController* i_motion, pvztime_t i_startTime)                    { pvztime_t notUsed; return Add(i_motion, i_startTime, notUsed); }
    AnimationMgr* Add(AnimationController* i_motion)                                           { return Add(i_motion, m_time); } // add for now.
    
    // old style.
    void Add(AnimationControllerWkPtr i_motion, pvztime_t i_startTime, pvztime_t& o_endTime); // o_endTime is end time of the just inserted motion.
    void Add(AnimationControllerWkPtr i_motion, pvztime_t i_startTime)                    { pvztime_t notUsed; Add(i_motion, i_startTime, notUsed); }
    void Add(AnimationControllerWkPtr i_motion)                                     { Add(i_motion, m_time); } // add for now.

    void       Pause(bool i_paused) { m_pause = i_paused; }
    bool       IsPaused()           { return m_pause; }
    void       ResetTime()          { m_time = 0.0f;}
    pvztime_t  GetTime()            { return m_time; }
    
    void       Clear(); // remove all controllers, deleting them if necessary. 
    
private:
	virtual void onInitialized() override;
    
    pvztime_t       m_time;
    bool            m_pause;
    bool            m_removing;   //Safety Latch: we're in a removing operation - we can't add / 
    
    std::vector<AnimationControllerWkPtr> m_animationControllers;
    typedef std::vector<AnimationControllerWkPtr>::iterator AnimationControllerIterator;
    
};

typedef RtWeakPtr<AnimationMgr> AnimationMgrWkPtr;

#endif
