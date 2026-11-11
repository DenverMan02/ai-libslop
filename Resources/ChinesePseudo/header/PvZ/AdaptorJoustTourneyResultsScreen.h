//
//  AdaptorJoustTourneyResultsScreen.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 9/27/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustTourneyResultsScreen_h
#define AdaptorJoustTourneyResultsScreen_h

#include "HotUIAdaptor.h"
#include "TimeLine.h"
#include "LevelOfTheDay_RewardData.h"
#include "MacroStateMachine.h"
#include <map>

STATE_ENUM_BASE_BEGIN(TournamentResultsScreenState)
	TRSS_Intro,
	TRSS_Badge,
	TRSS_PreviousLeague,
	TRSS_NewLeague,
	TRSS_Shine,
	TRSS_Stars,
	TRSS_End,
STATE_ENUM_END(TournamentResultsScreenState);

struct AdaptorJoustTourneyResultsScreenParams
{
	AdaptorJoustTourneyResultsScreenParams()
		: LeagueDelta(0)
		, FinalPlacementIndex(1)
		, NewLeagueIndex(0)
	{}
	
	int LeagueDelta;
	int FinalPlacementIndex;
	int NewLeagueIndex;
	std::vector<LevelOfTheDay_RewardItemType> Rewards;
};

enum WidgetAnimationType {
	WAT_TRANSLATION,
	WAT_HOTUIIMAGE_SCALE,
	WAT_HOTUIIMAGE_ALPHA,
	WAT_HOTUIANIM_SCALE,
	WAT_HOTUIANIM_ANIM
};

struct WidgetAnimationData {
	
	WidgetAnimationData()
	: Type(WAT_TRANSLATION)
	, State(TRSS_Intro)
	, WidgetName("")
	, AnimName("")
	, Loop(false)
	, VisibleAtStart(false)
	, VisibleAtEnd(true)
	, Complete(false)
	{
	}
	
	WidgetAnimationType Type;
	TournamentResultsScreenState State;
	std::string WidgetName;
	std::string AnimName;
	bool Loop;
	bool VisibleAtStart;
	bool VisibleAtEnd;
	bool Complete;
};

class AdaptorJoustTourneyResultsScreen : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorJoustTourneyResultsScreen, HotUIAdaptor, Sexy::RtClass);
	
public:
	enum ButtonID
	{
		Dismiss,
		Continue
	};
	
public:
	AdaptorJoustTourneyResultsScreen();
	
	bool OnBackButtonPressed() override;
	void ButtonDepress(int i_buttonID) override;
	
	void EnableFullScreenDismiss(bool i_enable);
	
	void SetParams(const AdaptorJoustTourneyResultsScreenParams& i_params);
	
	void Update() override;
	
	void Close();
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	
	void onJoustNetworkResponse(int i_context, int i_status);
	void onJoustNetworkIssueDecision(int i_context, int i_decision);
	
private:
	void setup();
	void refresh();
	void onContinueClick();
	
	void showAwardScreen();
	void giveRewards();
	void onAwardScreenDismissed();
	
	void sendTournamentRegistrationRequest();
	void onRegistrationDone();
	void setInputEnabled(bool i_enabled);

	AdaptorJoustTourneyResultsScreenParams m_params;
	class PVZ2UIAwardScreen* m_awardScreen;
	
	pvztime_t m_animStartTime;
	CurveSequenceCollection<SexyVector2> m_anims;
	std::map<std::string, WidgetAnimationData> m_animationData;
	
	DECLARE_FSM_HANDLER_BASE(TournamentResultsScreenState);
	
	DECLARE_FSM_STATE_VALUE(TournamentResultsScreenState);
	
	// Helpers
	void setupAnimationsPromotion();
	void setupAnimationsDemotion();
	void setupAnimationsStay();

	void updateLeagueData();
	void updateRewardData();
	void updateFTUE();
	
	void startHotUIAnim(WidgetAnimationData *i_animData);
	void onHotUIAnimFinished(const std::string& i_animName);
	void onHotUIAnimLoopFinished(const std::string& i_animName, const std::string& i_string2, const int i_loops);
	
	bool startAnimsForState(TournamentResultsScreenState i_state, pvztime_t i_time);
	bool updateAnimsForState(TournamentResultsScreenState i_state, pvztime_t i_time);
	void endAnimsForState(TournamentResultsScreenState i_state);
	
	void startWidgetAnimation(WidgetAnimationData *i_animData, pvztime_t i_startTime = 0.0f);
	bool updateWidgetFromAnimation(WidgetAnimationData *i_animData, pvztime_t i_time);
	
	void updateWidgetFromAnimationTranslation(WidgetAnimationData *i_animData, pvztime_t i_time);
	void updateHotUIImageWidgetFromAnimationScale(WidgetAnimationData *i_animData, pvztime_t i_time);
	void updateHotUIImageWidgetFromAnimationAlpha(WidgetAnimationData *i_animData, pvztime_t i_time);
	
	void updateHotUIAnimWidgetFromAnimationScale(WidgetAnimationData *i_animData, pvztime_t i_time);
};


#endif /* AdaptorJoustTourneyResultsScreen_h */
