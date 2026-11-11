//
//  PVZ2UIStarSummary.h
//  PlantsVersusZombies2
//
//  Created by jsola on 3/26/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PVZ2UIStarSummary_h
#define PlantsVersusZombies2_PVZ2UIStarSummary_h

#include "PVZ2UIAwardScreen.h"

class PVZ2UIStarSummary : public Sexy::Widget
{
public:
	PVZ2UIStarSummary(const PVZ2UIAwardScreen::ScreenEntry& i_entry);
	virtual ~PVZ2UIStarSummary();
	
	virtual void			Update();
	virtual void			Draw(Graphics* i_g);
	
private:
	int						m_numStars;
	int						m_activeStarIndex;
	AwardScreenStarMode		m_mode;

	SexyString				m_challengeHeader;

	std::vector<SexyString> m_challengeDescriptions;
	std::vector<bool> 		m_challengeFailStates;
	
	class PopAnimRig*		m_rig[3];
};

#endif
