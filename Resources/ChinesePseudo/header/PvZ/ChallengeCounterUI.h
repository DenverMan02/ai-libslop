//
//  ChallengeCounterUI.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 12/19/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ChallengeCounterUI_h
#define PlantsVersusZombies2_ChallengeCounterUI_h

#include "ChallengeUI.h"
#include "Image.h"
#include "RtObject.h"
#include "SexyString.h"
#include "StateMachine.h"


class ChallengeCounterUI : public ChallengeUI
{
	
public:
	RT_CLASS_DEFINE(ChallengeCounterUI, ChallengeUI, RtClass);
	
	ChallengeCounterUI();
    virtual ~ChallengeCounterUI() {}
	
    void SetCount(int i_sunCurrency) { m_count = i_sunCurrency; }
    void SetTarget(int i_sunCurrency) { m_target = i_sunCurrency; }

protected:
	SexyString getCountText() override;

private:
	int	m_count;
	int	m_target;
};

#endif
