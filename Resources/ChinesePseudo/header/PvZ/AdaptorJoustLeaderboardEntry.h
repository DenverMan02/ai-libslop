//
//  AdaptorJoustLeaderboardEntry.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 8/22/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef AdaptorJoustLeaderboardEntry_h
#define AdaptorJoustLeaderboardEntry_h

#include "HotUIAdaptor.h"
#include "LevelOfTheDay_RewardData.h"

struct AdaptorJoustLeaderboardEntryConfig
{
	int PlayerId;
	int Place;
	int Crowns;
	int Avatar;
	bool IsLocalPlayer;
	SexyString PlayerName;
	int Color;
	bool VIP;
};

class AdaptorJoustLeaderboardEntry : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorJoustLeaderboardEntry, HotUIAdaptor, Sexy::RtClass);
	
	AdaptorJoustLeaderboardEntry();
	virtual ~AdaptorJoustLeaderboardEntry();
	
	void Configure(WidgetContainer* i_parent, const AdaptorJoustLeaderboardEntryConfig& i_config);

protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onLayoutFinished() override;
	
	void onRankListEffectUpdate(const std::vector<int>& playerIdList);

private:
	void updateAvatarIcon();
	int getGemReward();
	int getFirstReward();
	LevelOfTheDay_RewardItemType getFirstRewardObject();
	
	WidgetContainer* m_parent;
	AdaptorJoustLeaderboardEntryConfig m_config;
};

#endif /* AdaptorJoustLeaderboardEntry_h */
