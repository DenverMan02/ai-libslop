//
//  AdaptorJoustScreen.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 8/15/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustScreen_h
#define AdaptorJoustScreen_h

#include <string>

#include "EASquared.h"
#include "HotUIAdaptor.h"
#include "RtObject.h"

class AdaptorJoustLeaderboard;
class AdaptorJoustMatchmakingScreen;
struct AdaptorJoustLeaderboardConfig;

class AdaptorJoustScreen : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorJoustScreen, HotUIAdaptor, Sexy::RtClass);
	
public:
	enum ButtonID
	{
		Dismiss,
		FreeTickets,
		Play,
		Back,
		LeagueInfo,
		HowToPlay,
		backToMap
	};
	
public:
	AdaptorJoustScreen();
	virtual ~AdaptorJoustScreen();

	bool OnBackButtonPressed() override;
	void ButtonDepress(int i_buttonID) override;
	
	void EnableFullScreenDismiss(bool i_enable);
	
	void Update() override;
	// void Draw(Graphics* g) override;
//	void DrawAll(ModalFlags* theFlags, Graphics* g) override;
	
	void RemovedFromManager(WidgetManager* i_widgetMgr) override;
	
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;
	
private:
	AdaptorJoustLeaderboardConfig buildLeaderboard();
	void addLeaderboardOpponents(AdaptorJoustLeaderboardConfig& io_config);

	void setup();
	void close();
	
	bool canHandleInput();
	
	AdaptorJoustLeaderboard* m_leaderboard;
	AdaptorJoustMatchmakingScreen* m_matchmakingScreen;
	
	// EA Squared
	void onEASquaredAdFinished(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
	bool isEASquaredForTicketsAvailable();
	void updateEASquaredForTicketsVisible();
	
	void updatePlayButton();
	void onPlay();
	void onMatchmakingCanceled();
	void onMatchmakingFailed();
	void onMatchmakingPlay();
	void onShowLeagueInfoScreen();
	void onHowToPlayTapped();
	
	void showHowToPlayScreen();
	void startJoustTutorial();
};

#endif /* AdaptorJoustScreen_h */
