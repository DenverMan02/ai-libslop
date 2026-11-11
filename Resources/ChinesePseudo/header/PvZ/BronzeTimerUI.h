//
//  BronzeTimerUI.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 14-1-9.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__BronzeTimerUI__
#define __PlantsVersusZombies2__BronzeTimerUI__

#include <iostream>
#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "ScrollingCounter.h"
#include "ChallengeUI.h"

class UIWidgetSheet;

class BronzeTimerUI : public ChallengeUI
{
	
public:
	RT_CLASS_DEFINE(BronzeTimerUI, ChallengeUI, RtClass);
	
	BronzeTimerUI();
	virtual ~BronzeTimerUI();
	
	void SetSeconds(int i_seconds);

protected:
	virtual SexyString getCountText() override;
    
private:
	int m_seconds;
};


#endif /* defined(__PlantsVersusZombies2__BronzeTimerUI__) */
