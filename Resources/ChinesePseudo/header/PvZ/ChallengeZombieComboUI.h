//
//  ChallengeZombieComboUI.h
//  PlantsVersusZombies2
//
//  Created by David Siems 3/20/13.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ChallengeZombieComboUI_h
#define PlantsVersusZombies2_ChallengeZombieComboUI_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "ChallengeUI.h"

class UIWidgetSheet;

class ChallengeZombieComboUI : public ChallengeUI
{
	
public:
	RT_CLASS_DEFINE(ChallengeZombieComboUI, ChallengeUI, RtClass);
	
	ChallengeZombieComboUI();
	virtual ~ChallengeZombieComboUI();
	
	void				SetCount(int i_count);
	void				SetTarget(int i_target);

protected:
	virtual void		postDraw(Graphics* i_g) override;

private:
	int					m_count;
	int					m_target;
};

#endif
