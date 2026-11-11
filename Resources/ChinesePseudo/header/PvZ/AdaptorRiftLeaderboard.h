/*
 * AdaptorRiftLeaderboard.h
 *
 *  Created on: 2020-6-9
 *      Author: Administrator
 */

#ifndef ADAPTORRIFTLEADERBOARD_H_
#define ADAPTORRIFTLEADERBOARD_H_

#include "RtObject.h"
#include "HotUIAdaptor.h"
#include "AdaptorRiftLeaderboardEntry.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"

class AdaptorRiftLeaderboardConfig
{
public:
	void OrderByScore();

	std::vector<AdaptorRiftLeaderboardEntryConfig> Entries;
};

class AdaptorRiftLeaderboard : public HotUIAdaptor, Sexy::ScrollWidgetListener
{
public:
	RT_CLASS_DEFINE(AdaptorRiftLeaderboard, HotUIAdaptor, Sexy::RtClass);

	AdaptorRiftLeaderboard();
	virtual ~AdaptorRiftLeaderboard();

	void Configure(WidgetContainer* i_parent, const AdaptorRiftLeaderboardConfig& i_config);

	void ScrollerMoved( Sexy::ScrollWidget* i_scrollWidget ) override;
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;

private:
	WidgetContainer* m_parent;
	std::vector<AdaptorRiftLeaderboardEntry*> m_leaderboardEntries;
	AdaptorRiftLeaderboardEntry* m_playerLeaderboardEntry;
	Sexy::Rect m_playerEntryRect;

	AdaptorRiftLeaderboardConfig m_config;
};


#endif /* ADAPTORRIFTLEADERBOARD_H_ */
