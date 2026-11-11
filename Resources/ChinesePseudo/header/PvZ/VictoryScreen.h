//
//  VictoryScreen.h
//  PlantsVersusZombies2
//
//  Created by jsola on 12/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

//
//
// *************** TEMPORARY VICTORY SCREEN! *******************
//
// This is all placeholder.
// Please feel free to rip this apart and put something better here.
//
// *************************************************************
//
//

#ifndef PlantsVersusZombies2_VictoryScreen_h
#define PlantsVersusZombies2_VictoryScreen_h

#include "Widget.h"
#include "ButtonWidget.h"

#include "PresentOpeningScreen.h"
#include "PlayerInfo.h"

class VictoryScreenChallengeResultsWidget : public Sexy::Widget
{
public:
	VictoryScreenChallengeResultsWidget(const SexyString& i_message, bool i_previouslyCompleted, bool i_completedThisTime, pvztime_t i_beginPresentationAt);
	virtual ~VictoryScreenChallengeResultsWidget();
	
	virtual void Update();
	virtual void Draw(Sexy::Graphics* i_g);
	
private:
	void playCollectAnimation(const std::string& i_animLabel);
	
	class PopAnimRig* m_starRig;
	SexyString m_message;
	bool m_successful;
	pvztime_t m_presentTime;
	bool m_previouslyCompleted;
	bool m_completedThisTime;
};

class VictoryScreenWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	VictoryScreenWidget(const SexyString& i_levelName);
	void AddChallenge(const SexyString& i_challengeName, bool i_completedPreviously , bool i_completedThisTime);
	void SetPresents(const std::vector<RtWeakPtr<const class PresentTable> >& i_presentTables, const std::vector<RtWeakPtr<const class PresentType> >& i_presentContents);
	void SetDangerRoomInfo(const bool i_hasUnlockedCheckpoint, const bool i_hasNewHighestLevel, const DangerRoomInfo& i_dangerRoomInfo);
	void BuildWidgets();
	virtual ~VictoryScreenWidget();

	virtual void Update();
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void TouchBegan( Touch* touch );
	virtual void ButtonDepress(int i_id);

	enum Result
	{
		VictoryScreenResults_None,
		VictoryScreenResults_Retry,
		VictoryScreenResults_Continue
	};

	VictoryScreenWidget::Result GetResult();

private:
	SexyString m_levelName;
	
	enum ButtonTypes
	{
		BUTTON_RETRY,
		BUTTON_TOMAP,
		BUTTON_NEXT_DANGER_ROOM_LEVEL,
	};
	
	struct ChallengeStatus
	{
		SexyString ChallengeMessage;
		bool SuccessfulThisTime;
		bool SuccessfulPreviously;
	};
	std::vector<ChallengeStatus> m_challenges;
	
	std::vector<RtWeakPtr<const class PresentTable> > m_presentTables;
	std::vector<RtWeakPtr<const class PresentType> > m_presentContents;
	
	PresentOpeningScreen* m_presentOpener;
	
	Rect m_titleRect;
	Rect m_challengeResultsRect[4];
	
	bool m_bottomButtonsShown;
	Rect m_presentOpeningRect;
	Rect m_bottomButtonRect;

	bool m_dangerRoomCheckpointReached;
	bool m_dangerRoomNewHighestLevel;
	bool m_isDangerRoomVictory;
	DangerRoomInfo m_dangerRoomInfo;
	
	Result m_results;
};

#endif
