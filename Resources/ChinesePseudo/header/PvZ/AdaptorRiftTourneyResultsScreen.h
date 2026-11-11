/*
 * AdaptorRiftTourneyResultsScreen.h
 *
 *  Created on: 2020-6-16
 *      Author: Administrator
 */

#ifndef ADAPTORRIFTTOURNEYRESULTSSCREEN_H_
#define ADAPTORRIFTTOURNEYRESULTSSCREEN_H_

#include "HotUIAdaptor.h"
#include "TimeLine.h"
#include "LevelOfTheDay_RewardData.h"
#include "MacroStateMachine.h"
#include <map>
#include "UISingletonDialog.h"

typedef struct SecretAwardInfo SAwardInfo;

namespace Message
{
	void NotifyAwardScreenClosed();
}

STATE_ENUM_BASE_BEGIN(RiftTournamentResultsScreenState)
	TRSS_Intro,
	TRSS_Badge,
	TRSS_PreviousLeague,
	TRSS_NewLeague,
	TRSS_Shine,
	TRSS_Stars,
	TRSS_End,
STATE_ENUM_END(RiftTournamentResultsScreenState);

struct AdaptorRiftTourneyResultsScreenParams
{
	AdaptorRiftTourneyResultsScreenParams()
		: LeagueDelta(0)
		, FinalPlacementIndex(1)
		, NewLeagueIndex(0)
	{}

	int LeagueDelta;
	int FinalPlacementIndex;
	int NewLeagueIndex;
	std::vector<LevelOfTheDay_RewardItemType> Rewards;
};

enum RiftWidgetAnimationType {
	WAT_TRANSLATION,
	WAT_HOTUIIMAGE_SCALE,
	WAT_HOTUIIMAGE_ALPHA,
	WAT_HOTUIANIM_SCALE,
	WAT_HOTUIANIM_ANIM
};

struct RiftWidgetAnimationData {

	RiftWidgetAnimationData()
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

	RiftWidgetAnimationType Type;
	RiftTournamentResultsScreenState State;
	std::string WidgetName;
	std::string AnimName;
	bool Loop;
	bool VisibleAtStart;
	bool VisibleAtEnd;
	bool Complete;
};

class AdaptorRiftTourneyResultsScreen : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorRiftTourneyResultsScreen, HotUIAdaptor, Sexy::RtClass);

public:
	enum ButtonID
	{
		Dismiss,
		Continue
	};

public:
	AdaptorRiftTourneyResultsScreen();
	virtual ~AdaptorRiftTourneyResultsScreen();

	bool OnBackButtonPressed() override;
	void ButtonDepress(int i_buttonID) override;

	void EnableFullScreenDismiss(bool i_enable);

	void SetParams(const AdaptorRiftTourneyResultsScreenParams& i_params);

	void Update() override;

	void Close();
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;

//	void onRiftNetworkResponse(int i_context, int i_status);
//	void onRiftNetworkIssueDecision(int i_context, int i_decision);

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

	AdaptorRiftTourneyResultsScreenParams m_params;
	//class PVZ2UIAwardScreen* m_awardScreen;

	pvztime_t m_animStartTime;
	CurveSequenceCollection<SexyVector2> m_anims;
	std::map<std::string, RiftWidgetAnimationData> m_animationData;

	DECLARE_FSM_HANDLER_BASE(RiftTournamentResultsScreenState);

	DECLARE_FSM_STATE_VALUE(RiftTournamentResultsScreenState);

	// Helpers
	void setupAnimationsPromotion();
	void setupAnimationsDemotion();
	void setupAnimationsStay();

	void updateLeagueData();
	void updateRewardData();
	void updateFTUE();

	void startHotUIAnim(RiftWidgetAnimationData *i_animData);
	void onHotUIAnimFinished(const std::string& i_animName);
	void onHotUIAnimLoopFinished(const std::string& i_animName, const std::string& i_string2, const int i_loops);

	bool startAnimsForState(RiftTournamentResultsScreenState i_state, pvztime_t i_time);
	bool updateAnimsForState(RiftTournamentResultsScreenState i_state, pvztime_t i_time);
	void endAnimsForState(RiftTournamentResultsScreenState i_state);

	void startWidgetAnimation(RiftWidgetAnimationData *i_animData, pvztime_t i_startTime = 0.0f);
	bool updateWidgetFromAnimation(RiftWidgetAnimationData *i_animData, pvztime_t i_time);

	void updateWidgetFromAnimationTranslation(RiftWidgetAnimationData *i_animData, pvztime_t i_time);
	void updateHotUIImageWidgetFromAnimationScale(RiftWidgetAnimationData *i_animData, pvztime_t i_time);
	void updateHotUIImageWidgetFromAnimationAlpha(RiftWidgetAnimationData *i_animData, pvztime_t i_time);

	void updateHotUIAnimWidgetFromAnimationScale(RiftWidgetAnimationData *i_animData, pvztime_t i_time);
};

class UIRiftRewardResult : public UISingletonDialog<UIRiftRewardResult>
{
public:
	UIRiftRewardResult();
	virtual ~UIRiftRewardResult();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIRiftRewardResult"; }

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	void 						InitRewards(const std::vector<class LevelOfTheDay_RewardItemType>& i_rewards);

private:
	void 						ConvertRewards(const std::vector<LevelOfTheDay_RewardItemType>& i_rewards);

	std::vector<SAwardInfo> 	m_infos;
};


#endif /* ADAPTORRIFTTOURNEYRESULTSSCREEN_H_ */
