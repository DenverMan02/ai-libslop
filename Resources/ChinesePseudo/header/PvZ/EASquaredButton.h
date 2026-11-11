//
//  EASquaredButton.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 1/29/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EASquaredButton__
#define __PlantsVersusZombies2__EASquaredButton__

#include "EASquared.h"
#include "PVZ2UIButton.h"
#include <string>

class MagentoProductProps;

class EASquaredButton : public PVZ2UIButton, public ButtonListener
{
public:
	EASquaredButton(int i_numCoinsToReward);
	virtual ~EASquaredButton();
	
	void ButtonDepress(int i_unused);
	
	static bool shouldBeDesaturated(int i_numFreeCoinsAvailable);
private:
	void onEASquaredAdFinished(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
    void updateState();
    void updateVisibility();
    void sendMetricsReport();
	
	const int	m_numCoinsToReward;
    bool		m_IsShowing;
};



#endif /* defined(__PlantsVersusZombies2__EASquaredButton__) */
