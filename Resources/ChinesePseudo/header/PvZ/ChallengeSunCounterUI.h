//
//  ChallengeSunCounterUI.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 12/19/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ChallengeSunCounterUI_h
#define PlantsVersusZombies2_ChallengeSunCounterUI_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "ScrollingCounter.h"
#include "ChallengeUI.h"

class UIWidgetSheet;

class ChallengeSunCounterUI : public ChallengeUI
{
	
public:
	RT_CLASS_DEFINE(ChallengeSunCounterUI, ChallengeUI, RtClass);
	
	ChallengeSunCounterUI();
	virtual ~ChallengeSunCounterUI();
	
	void SetCount(int i_sunCurrency);
	void SetTarget(int i_sunCurrency);
	void SetImage(ImagePtr i_image);
	void SetColor(Color clrCur, Color clrTarget);

	int	GetCount() const { return m_count; }
	int	GetTarget() const { return m_target; }

protected:
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);

	virtual SexyString getCountText() override;

private:
	int			m_count;
	int			m_target;
	Color		m_colorCurrency;
	Color		m_colorTarget;
};

#endif
