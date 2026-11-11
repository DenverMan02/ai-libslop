//
//  EffectAnimRig_SodRoll.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 4/9/13.
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectAnimRig_EndLevel__
#define __PlantsVersusZombies2__EffectAnimRig_EndLevel__

#include "PopAnimRig.h"
#include "WorldMap.h"

class EffectAnimRig_EndLevel : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(EffectAnimRig_EndLevel, PopAnimRig, RtClass);
    EffectAnimRig_EndLevel();
    ~EffectAnimRig_EndLevel();
    
    void adjustParentSize(int w, int h);
    void setAchieveStarNum(int num);
    void playWindowsIn();
    void playWindowsOut();
    bool EndLevel();
    
    void hardAwardRaise();
    void hardAwardRaiseUpdate();
    void hardAwardOut();
    void hardAwardOutUpdate();
    
    void onBoxOutAnimStopped();
    void WindowsInAnimStop();
    void WindowsOutAnimStop();
    void setParentEndLevelUI(class EndLevelUI* endlevelUI);

    
private:
    
    virtual void onPopAnimCommand(pvztime_t i_atTime, const std::string& i_command, const std::string& i_param) override;
    virtual void onAnimStopped() override;
    
    class PVZ2UIButton*   m_continueBtn;
    
    bool m_showNumber;
    bool m_hardLevel;
    
    int mPWidth;
    int mPHeight;
    SexyVector2 m_boxPosOffset;
    class EndLevelUI* m_endlevelUI;
};

#endif /* defined(__PlantsVersusZombies2__EffectAnimRig_EndLevel__) */
