//
//  AdaptorJoustWinStreakDisplayEntry.h
//  PlantsVersusZombies2
//
//  Created by Hoefler, Scarlett on 8/25/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustWinStreakDisplayEntry_h
#define AdaptorJoustWinStreakDisplayEntry_h

#include "HotUIAdaptor.h"
#include "RtDelegate.h"
#include "RtObject.h"
#include "RtReflectionDelegate.h"
#include "MacroStateMachine.h"
#include "TimeLine.h"
#include "LevelOfTheDay_RewardData.h"

STATE_ENUM_BASE_BEGIN(WinstreakEntryState)
WES_Intro,
WES_Check,
WES_End,
STATE_ENUM_END(WinstreakEntryState);

class LevelOfTheDay_RewardItemType;

struct JoustWinStreakDisplayEntryData
{
	JoustWinStreakDisplayEntryData()
	{
		IsEarned = false;
		EarnedWinNumber = -1;
		Crowns = 0;
		AnimateCheck = false;
	}
	bool IsEarned;
	bool AnimateCheck;
	int EarnedWinNumber;
	int Crowns;
	LevelOfTheDay_RewardItemType Reward;
};

class AdaptorJoustWinStreakDisplayEntry : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorJoustWinStreakDisplayEntry, HotUIAdaptor, RtClass);
public:
	void SetData(const JoustWinStreakDisplayEntryData& i_newData);
	void Update() override;
	
protected:
	void onLinkToUIViewCreated() override;
	
	
private:
	void refresh();
	
	JoustWinStreakDisplayEntryData m_data;
	float m_animStartTime;
	CurveSequenceCollection<SexyVector2> m_anims;
	
	DECLARE_FSM_HANDLER_BASE(WinstreakEntryState);
	
	DECLARE_FSM_STATE_VALUE(WinstreakEntryState);
};

#endif /* AdaptorJoustWinStreakDisplayEntry_h */
