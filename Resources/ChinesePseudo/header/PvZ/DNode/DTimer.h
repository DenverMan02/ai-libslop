//
//  DTimer.h
//  DCore
//
//  Created by lzjseed on 16/1/27.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef DTimer_h
#define DTimer_h

#include <map>
#include <vector>
#include <string>

class DActionManager;

class DTimerManager
{
public:
    struct DTimerElement
    {
        float  startTime = 0.0f;
        float  endTime = 0.0f;
        size_t repeatTime = 1;
        float  newEndTime = 0.0f;
        size_t newRepeatTime = 1;
        bool   needChanged = false;
        std::function<void(float dt)> callback = nullptr;
    };
    
    static DTimerManager* getInstane();
    static void purge();
    
    inline DActionManager* getActionManager() const {return m_pActionManager;}
    void   update();
    
    inline bool isPause()const {return m_bPause;}
    void  setPause(bool pause);
    void  addTimer(const std::string& name,const std::function<void(float dt)>& fun,float time = 0.0f,size_t repeatTime = 1);
    void  setTimer(const std::string& name,float time,size_t repeatTime);
    void  removeTimer(const std::string& name);
    void  updateTimer(float dt);
private:
    void calculateDeltaTime();
    DTimerManager();
    ~DTimerManager();
    
    DActionManager* m_pActionManager;
    
    float  m_deltaTime;
    bool   m_nextDeltaTimeZero;
    bool   m_bPause;
    struct timeval* m_lastUpdate;
    
    std::string      m_currentTimer;
    bool             m_currentTimerIsDead = false;
    
    std::map<std::string,DTimerElement> m_schedule;
    
    static DTimerManager* s_pTimeManager;
};

#endif
