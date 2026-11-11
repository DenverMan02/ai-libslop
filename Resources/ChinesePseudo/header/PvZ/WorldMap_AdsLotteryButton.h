//
//  WorldMap_AdsLotteryButton.h
//  PlantsVersusZombies2
//

#ifndef WorldMap_AdsLotteryButton_h
#define WorldMap_AdsLotteryButton_h

#include "UIEasyButtonWidget.h"
#include "EASquared.h"

class WorldMap_AdsLotteryButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_AdsLotteryButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_AdsLotteryButton();
    virtual ~WorldMap_AdsLotteryButton();
    
    void checkVisiable();
    
    void onEASquaredAdsAvailableChanged();
    
    void changeAvailable();
    
    void onNotifyRefreshActivityList(bool result, const std::set<int>& changeList);
private:
    bool m_show;
};

#endif /* WorldMap_AdsLotteryButton_h */
