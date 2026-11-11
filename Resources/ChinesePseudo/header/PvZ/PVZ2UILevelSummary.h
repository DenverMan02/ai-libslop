//
//  PVZ2UILevelSummary.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 11/11/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PVZ2UILevelSummary_h
#define PlantsVersusZombies2_PVZ2UILevelSummary_h

#include <vector>

#include "PVZ2UIAwardScreen.h"
#include "SexyString.h"
#include "Widget.h"

class PVZ2UILevelSummary : public Sexy::Widget
{
public:
	PVZ2UILevelSummary(const PVZ2UIAwardScreen::ScreenEntry& i_entry);
	virtual ~PVZ2UILevelSummary();
	
	virtual void			Draw(Graphics* i_g);
	virtual void			DrawBasicLevelObjectiveScreen(Graphics* i_g);
	virtual void			DrawSplitLevelObjectiveScreen(Graphics* i_g);
	virtual void			DrawChooseLevelObjectiveScreen(Graphics* i_g);
	virtual void			DrawUnchartedModeTipsScreen(Graphics* i_g);
	virtual void			DrawUnchartedModeDifficultyTipsScreen(Graphics* i_g);
	
	void 					SetChooseLevel(bool chooseLevel) { m_chooseLevelObjective = chooseLevel; }

protected:
	AwardScreenObjective	m_mode;

	SexyString				m_challengeHeader;

	std::vector<SexyString> m_challengeDescriptions;
	std::vector<bool> 		m_challengeFailStates;
	
	std::vector<SexyString> m_bonusChallengeDescriptions;
	std::vector<bool>		m_bonusChallengeFailStates;

	bool 					m_chooseLevelObjective;
	bool 					m_unchartedModeTips;
	bool 					m_unchartedModeDifficultyTips;
	std::vector<SexyString> m_unchartedModeTipsDescriptions;
	std::vector<SexyString> m_unchartedModeDifficultyDescriptions;
};

#endif
