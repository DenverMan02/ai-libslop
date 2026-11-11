//
//  TutorialFinger.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2016.6.29
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef __TutorialFinger_h_
#define __TutorialFinger_h_
#pragma once
#include "TimeMgr.h"
#include "SexyVector.h"

class TutorialFinger
{
public:
    TutorialFinger();
    ~TutorialFinger();
    void        StartCurvingTutorialFinger();
    void        SetCurvingTutorialFinger(float i_startX, float i_startY, float i_endX, float i_endY, pvztime_t i_duration);
    void        StopCurvingTutorialFinger();
    void		TriggerFade(bool i_trigger);
    void        Draw(Graphics* i_g);
    void        Update();

    bool        IsActive() { return m_isTutorialFingerActive; }
    class Effect_PopAnim*   GetHandEffect() { return m_pHandEffect; }
protected:
    class Effect_PopAnim*   m_pHandEffect = nullptr;

    float                   m_tutorialFingerPosX = 0;
    float                   m_tutorialFingerPosY = 0;
    
    pvztime_t               m_tutorialFingerFlyTime = 0;
    pvztime_t               m_tutorialFingerRestTime = 0;
    
    bool                    m_isTutorialFingerActive = false;
    bool                    m_isTutorialFingerResting = true;
    
    SexyVector2             m_flyStart;
    SexyVector2             m_flyEnd;
    pvztime_t               m_duration;
    bool					m_isFadeOut = false;
    pvztime_t				m_fadeStartTime = 0.0f;
};

#endif
