//
//  AdaptorJoustLeagueInfoEntry.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 9/21/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustLeagueInfoEntry_h
#define AdaptorJoustLeagueInfoEntry_h

#include "HotUIAdaptor.h"

class AdaptorJoustLeagueInfoEntry : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorJoustLeagueInfoEntry, HotUIAdaptor, Sexy::RtClass);
	
	AdaptorJoustLeagueInfoEntry()
		: m_parent(nullptr)
	{}
	
	void Configure(Sexy::WidgetContainer *i_parent, const int i_league, const int i_leaderboardPlacement);
	
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;
	

private:
	
	void updateRewardDisplay();
	
	WidgetContainer* m_parent;
	int m_leaderboardIndex;
	int m_league;
};

#endif
