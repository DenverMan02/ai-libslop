//
//  AdaptorJoustLeaderboard.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 8/23/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustLeaderboard_h
#define AdaptorJoustLeaderboard_h

#include "RtObject.h"
#include "HotUIAdaptor.h"
#include "AdaptorJoustLeaderboardEntry.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"

class AdaptorJoustLeaderboardConfig
{
public:
	void OrderByScore();
	
	std::vector<AdaptorJoustLeaderboardEntryConfig> Entries;
};

class AdaptorJoustLeaderboard : public HotUIAdaptor, Sexy::ScrollWidgetListener
{
public:
	RT_CLASS_DEFINE(AdaptorJoustLeaderboard, HotUIAdaptor, Sexy::RtClass);
	
	AdaptorJoustLeaderboard();
	virtual ~AdaptorJoustLeaderboard();
	
	void Configure(WidgetContainer* i_parent, const AdaptorJoustLeaderboardConfig& i_config);

	void ScrollerMoved( Sexy::ScrollWidget* i_scrollWidget ) override;
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;
	
private:
	WidgetContainer* m_parent;
	std::vector<AdaptorJoustLeaderboardEntry*> m_leaderboardEntries;
	AdaptorJoustLeaderboardEntry* m_playerLeaderboardEntry;
	Sexy::Rect m_playerEntryRect;
	
	AdaptorJoustLeaderboardConfig m_config;
};


#endif /* AdaptorJoustLeaderboard_h */
