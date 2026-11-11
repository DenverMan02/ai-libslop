//
//  ArenaStarBank.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-11-5.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArenaStarBank__
#define __PlantsVersusZombies2__ArenaStarBank__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"

class Effect_PopAnim;

class ArenaStarBank : public UIWidget
{
public:

public:
    RT_CLASS_DEFINE(ArenaStarBank, UIWidget, RtClass);
    
    ArenaStarBank();
    virtual ~ArenaStarBank();
    
    // Public Interface (Inheritable)
    virtual void				Draw(Graphics* i_g) override;
    virtual void                onUpdate() override;

    Rect GetUIRect();
    
protected:
    // Protected Interface (Inheritable)
    //OVERRIDE_STATE_ONEXIT(WidgetState, Loading);
    OVERRIDE_STATE_UPDATE(WidgetState, Ready);
    
    virtual void				initLoadingResourcesGroupList() override;
    virtual void				registerForEvents() override;
    virtual void				unregisterForEvents() override;
private:
    void                        onNotifyLostBrain(int i_leftBrain);
    void                        onStarEffectFinish(const std::string& label);
    void                        PlayStarEffect(int starIndex);
    SexyVector2                 CalcStarPos(int starIndex);
    Effect_PopAnim*             CreateStarEffect(const SexyVector2& screenPos);
    int                         m_starNum;
    std::vector<Effect_PopAnim*> m_starEffect;
};

#endif /* defined(__PlantsVersusZombies2__ArenaStarBank__) */
