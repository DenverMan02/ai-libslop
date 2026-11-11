//
//  ActivityLevels.h
//  PlantsVersusZombies2
//
//  Created by shizf on 16/7/22.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef ActivityLevels_h
#define ActivityLevels_h

#include "UISingletonDialog.h"
#include "LawnAppEnums.h"
#include "EASquared.h"

#pragma mark ActivityLevelsData
struct Activity_Level_Data
{
    int id = 0;
    int leftTimes = 0;
    int leftBuyTimes = 0;
    std::vector<int> buyPrice;
    std::vector<int> openDays;
    
    bool CanBuyTimes();
    int GetCurrentPrice();
};

class ActivityLevelsData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(ActivityLevelsData, Sexy::RtObject, Sexy::RtClass);
    
    ActivityLevelsData(){}
    
    bool IsValid() const { return m_datas.size() > 0; }
    
    static bool isActivityLevels(FestivalGameMode i_mode);
    
public:
    std::vector<Activity_Level_Data> m_datas;
};


#pragma mark ActivityLevelsChoose
class ActivityLevelsChoose : public UISingletonDialog<ActivityLevelsChoose>
{
public:
    ActivityLevelsChoose();
    virtual ~ActivityLevelsChoose();
    
    virtual bool OnCreate() override;
    virtual void OnClose() override;
    virtual std::string GetLayoutName() override { return "ActivityLevelsChoose"; }
    
    // ButtonListener
    virtual void ButtonDepress(int i_id) override;
    
    void BuyTimes(class UIMessageBox* box, int buttonID);
    void ShowMonthlyCardUI(class UIMessageBox* box, int buttonID);
    
private:
    void InitData();
    void InitByActivityLevelData(FestivalGameMode i_mode);
    bool HaveOpenToday(const std::vector<int>& i_weekDays);
    
    void onFestivalGameModeCountChange(int i_mode, int count);
    void onFestivalGameModeLeftBuyTimesChange(int i_mode, int times, int cost);
    void onMonthlyCardBought(bool success);
    void onMonthlyCardTrial();
    void onNotifyRefreshActivityList(bool result, const std::set<int>& changeList);

     // for ads watching
     void onAdsFinish(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
     bool IsAdvertisementEnable(int index);
     void UpdateActivityLevelData(FestivalGameMode i_mode);
     void LookMonthlyCard(class UIMessageBox* box, int buttonID);
     void WatchADAddChance(class UIMessageBox* box, int buttonID);
     void onADFinished(int i_type);
    
private:
    FestivalGameMode m_cacheMode;
    bool m_watchingAD;
#ifdef HOST_ANDROID
    std::vector<PVZ2UIButton*> m_advertisementButtonList;// watch adv to get free challenge time
    int m_advertisementIndex;// which ads index button is click
	std::vector<bool> m_bIsAdsVisibleList;
    SexyString m_adsLabel;
    std::vector<UIWidgetText*> m_adsLabelList;
#endif
};

#pragma mark ActivityLevelsDifficultyChoose
class ActivityLevelsDifficultyChoose : public UISingletonDialog<ActivityLevelsDifficultyChoose>
{
public:
    ActivityLevelsDifficultyChoose();
    virtual ~ActivityLevelsDifficultyChoose();
    
    virtual bool OnCreate() override;
    virtual void OnClose() override;
    virtual std::string GetLayoutName() override { return "ActivityLevelsDifficultyChoose"; }
    
    void setChooseMode(FestivalGameMode i_mode);
    
    // ButtonListener
    virtual void ButtonDepress(int i_id) override;
    
private:
    void InitData();

private:
    FestivalGameMode m_mode;
};

#pragma mark ActivityLevelsWish

namespace Message
{
    void FestivalGameMode_CountChange(int i_mode, int count);
    void FestivalGameMode_LeftBuyTimesChange(int i_mode, int times, int cost);
}

#endif /* ActivityLevels_h */
