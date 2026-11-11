//
//  ChallengePlantCounterUI.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 12/19/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ChallengePlantCounterUI_h
#define PlantsVersusZombies2_ChallengePlantCounterUI_h

#include "core.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "ScrollingCounter.h"
#include "ChallengeUI.h"

class UIWidgetSheet;

class ChallengePlantCounterUI : public ChallengeUI
{
public:
	RT_CLASS_DEFINE(ChallengePlantCounterUI, ChallengeUI, RtClass);
	
	ChallengePlantCounterUI();
	virtual ~ChallengePlantCounterUI();
	
    void				SetIsOneCount(bool i_IsOneCount);
	void				SetCount(int i_count);
	void				SetTarget(int i_target);
	void				SetImage(ImagePtr i_image);

protected:

	virtual SexyString getCountText() override;
	
private:

	int					m_count;
	int					m_target;
    
    bool                m_IsOneCount;
};


#endif
