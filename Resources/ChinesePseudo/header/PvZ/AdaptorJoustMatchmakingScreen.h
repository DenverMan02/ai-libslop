//
//  AdaptorJoustMatchmakingScreen.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 9/13/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustMatchmakingScreen_h
#define AdaptorJoustMatchmakingScreen_h

#include "HotUIAdaptor.h"
#include "MacroStateMachine.h"

STATE_ENUM_BASE_BEGIN(MatchmakingScreenState)
	MMSS_FindingOpponent,
	MMSS_OpponentFound,
STATE_ENUM_END(MatchmakingScreenState);

EVENT_ENUM_BEGIN(MatchmakingScreenEvent)
	MMSE_CancelMatchmaking,
	MMSE_SwapState,
    MMSE_FoundOpponent,
	MMSE_FindNewOpponent,
	MMSE_Play,
EVENT_ENUM_END(MatchmakingScreenEvent)

struct HotUISeedPacketConfig;

class AdaptorJoustMatchmakingScreen : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorJoustMatchmakingScreen, HotUIAdaptor, RtClass);
	
	enum ButtonID
	{
		CancelMatchmaking,
		SwapState,
		FindNewOpponent,
		Play
	};
	
	AdaptorJoustMatchmakingScreen();
	
public:
	bool OnBackButtonPressed() override;
	void ButtonDepress(int i_buttonID) override;
    
    void ShowSwapButton();
	
	void Update() override;

	void Close();

	void SetOnCancelAction(std::function<void()> i_onCancel);
	void SetOnPlayAction(std::function<void()> i_onPlay);
	void SetOnFailAction(std::function<void ()> i_onFail);

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	
	DECLARE_FSM_HANDLER_BASE(MatchmakingScreenState);

private:
	void clearSeedPacketDisplay();
	void configureSeedPackets(const std::vector<HotUISeedPacketConfig>& i_packets);
	
	void updateSearchingDisplay();
	void showFindingOpponentDisplay(bool i_show);
	void showFoundOpponentDisplay(bool i_show);
	void updateOpponentDisplay();
	
	void signalCancel();
	
	void sendMatchRequest();
	void onMatchReceived();
	
	void onJoustNetworkResponse(int i_context, int i_status);
	void onJoustNetworkIssueDecision(int i_context, int i_decision);
	
	DECLARE_FSM_STATE_VALUE(MatchmakingScreenState);
	pvztime_t m_matchmakingStartTime;
	std::function<void()> m_onCancelCallback;
	std::function<void()> m_onFailCallback;
	std::function<void()> m_onPlayCallback;
	
	int m_matchesReceived;
};

#endif /* AdaptorJoustMatchmakingScreen_h */
