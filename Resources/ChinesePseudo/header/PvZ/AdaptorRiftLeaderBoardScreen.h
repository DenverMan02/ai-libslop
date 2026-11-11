/*
 * AdaptorRiftLeaderBoardScreen.h
 *
 *  Created on: 2020-6-9
 *      Author: Administrator
 */

#ifndef ADAPTORRIFTLEADERBOARDSCREEN_H_
#define ADAPTORRIFTLEADERBOARDSCREEN_H_

#include <vector>
#include <string>
#include "HotUIAdaptor.h"

class HotUIButton;
class HotUIImage;
class HotUILabel;
class AdaptorCarouselDots;
class AdaptorRiftLeaderboardConfig;
class AdaptorRiftLeaderboard;

class AdaptorRiftLeaderBoardScreen : public HotUIAdaptor
{
    RT_CLASS_DEFINE(AdaptorRiftLeaderBoardScreen, HotUIAdaptor, RtClass);
public:
    AdaptorRiftLeaderBoardScreen();
    virtual ~AdaptorRiftLeaderBoardScreen();

    void ButtonDepress(int i_buttonID) override;
    //void SetData(const HowToPlayScreenData& i_data);

    void Close();

protected:
    void onLoadUIView() override;
    void onLinkToUIViewCreated() override;
    //void onLayoutFinished() override;
    void setup();
    AdaptorRiftLeaderboardConfig buildLeaderboard();
    void addLeaderboardOpponents(AdaptorRiftLeaderboardConfig& io_config);

private:
    std::vector<class LevelOfTheDay_RewardItemType> getWeeklyRewards();
    void updateAvatarIcon(int i_widgetId, int i_rewardId);
    void showOverview();
    std::string GetScreenType();

    void ShowLegendReward(int i_index);
    void GetLegendReward(int i_index);

    AdaptorRiftLeaderboard* m_leaderboard;
};


#endif /* ADAPTORRIFTLEADERBOARDSCREEN_H_ */
