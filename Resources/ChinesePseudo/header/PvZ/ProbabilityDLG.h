//
//  DaveClubUI.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/23.
//  Copyright (c) 2015�� PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ProbabilityDLG__
#define __PlantsVersusZombies2__ProbabilityDLG__

#include "RtObject.h"
#include "core.h"
#include "ProbabilityConfig.h"
#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"

class ProbabilityDLG : public UISingletonDialog<ProbabilityDLG>, public Sexy::ScrollWidgetListener 
{
public:
	ProbabilityDLG();
	virtual ~ProbabilityDLG();

	virtual std::string         GetLayoutName() override { return "ProbabilityDLG"; }
	virtual void                Draw(Sexy::Graphics* i_g) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}  
	
	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	void InitView(const SexyString& config_alias);
private:
	RtWeakPtr<ProbabilityConfig> m_config;
};

#endif /* defined(__PlantsVersusZombies2__ProbabilityDLG__) */
