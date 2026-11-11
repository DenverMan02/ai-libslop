/*
 * AdaptorRiftLeaderboardEntry.h
 *
 *  Created on: 2020-6-9
 *      Author: Administrator
 */

#ifndef ADAPTORRIFTLEADERBOARDENTRY_H_
#define ADAPTORRIFTLEADERBOARDENTRY_H_

#include "HotUIAdaptor.h"
#include "LevelOfTheDay_RewardData.h"

struct AdaptorRiftLeaderboardEntryConfig
{
	int PlayerId;
	int Place;
	int Crowns;
	int Avatar;
	bool IsLocalPlayer;
	SexyString PlayerName;
	int Color;
	bool VIP;
	int RankAvatar;
};

class AdaptorRiftLeaderboardEntry : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorRiftLeaderboardEntry, HotUIAdaptor, Sexy::RtClass);

	AdaptorRiftLeaderboardEntry();
	virtual ~AdaptorRiftLeaderboardEntry();

	void Configure(WidgetContainer* i_parent, const AdaptorRiftLeaderboardEntryConfig& i_config);

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
	AdaptorRiftLeaderboardEntryConfig m_config;
};


#endif /* ADAPTORRIFTLEADERBOARDENTRY_H_ */
