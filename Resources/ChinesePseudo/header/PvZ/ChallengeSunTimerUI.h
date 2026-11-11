//
//  ChallengeSunTimerUI.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 3/19/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ChallengeSunTimerUI_h
#define PlantsVersusZombies2_ChallengeSunTimerUI_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "ScrollingCounter.h"
#include "ChallengeUI.h"

class UIWidgetSheet;

class ChallengeSunTimerUI : public ChallengeUI
{
	
public:
	RT_CLASS_DEFINE(ChallengeSunTimerUI, ChallengeUI, RtClass);
	
	ChallengeSunTimerUI();
	virtual ~ChallengeSunTimerUI();
	
	void SetSeconds(int i_seconds);

protected:
	virtual SexyString getCountText() override;

	int m_seconds;
};

class ChallengeLevelTimerUI : public ChallengeSunTimerUI
{

public:
	RT_CLASS_DEFINE(ChallengeLevelTimerUI, ChallengeSunTimerUI, RtClass);

	ChallengeLevelTimerUI();
};

class ChallengeRiftTimedEventUI : public ChallengeSunTimerUI
{

public:
	RT_CLASS_DEFINE(ChallengeRiftTimedEventUI, ChallengeSunTimerUI, RtClass);

	ChallengeRiftTimedEventUI();

protected:
	SexyString getCountText() override;
};

#endif
