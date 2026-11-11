//
//  SpeedChange.h
//  PlantsVersusZombies2
//
//  Created by 吴 祥军 on 13-7-15.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//


//PVZ2_CHINESE_START
#ifndef __PlantsVersusZombies2_SpeedChange_h
#define __PlantsVersusZombies2_SpeedChange_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "TimeMgr.h"

class SpeedChange : public UIWidget
{
public:
	RT_CLASS_DEFINE(SpeedChange, UIWidget, RtClass);
	
	SpeedChange();
	virtual ~SpeedChange();
	
	virtual void	Draw(Graphics* i_g) override;
    
protected:
    OVERRIDE_STATE_UPDATE(WidgetState, Ready);
	
    virtual void	initLoadingResourcesGroupList() override;
    virtual void	onInitialized() override;
	virtual void	registerForEvents() override;
	virtual void	unregisterForEvents() override;
    
    virtual void    OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	
private:
    void                    onGameStart();
    void                    onCancel();
    void                    onRechargeNow();
    void					onGameplayEnded();
    
    bool                    m_isTutorial;
    class BouncingArrow*    m_tutorialArrow;
    
};

namespace Message
{
    void SpeedChangeButtonPressed(float mSpeed);
}

#endif  //_SPEEDCHANGE_H
