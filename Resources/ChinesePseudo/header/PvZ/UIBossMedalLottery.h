//
//  UIBossMedalLottery.h
//  PlantsVersusZombies2
//
//  Created by Mao, Xingxing on 16/8/31.
//  Copyright © 2016年 PopCap Games. All rights reserved.
//

#ifndef UIBossMedalLottery_h
#define UIBossMedalLottery_h

#include "ActiveSummery.h"
#include "UIWidgetAnim.h"

class UIBossMedalLottery : public Sexy::Widget, public ButtonListener
{
public:
    void	ButtonDepress(int i_id) override;
    void Update() override;
    UIBossMedalLottery(UIWidgetText* materialText);
    ~UIBossMedalLottery();
private:
    void addItem(int id, int count);
    void initTabLottery();
    void initTabLottery(LotteryPanelData* data);
    void  setButtonsDisabled(bool i_bDisabled);
    void onSelectFrameStop(LotterySelectFrame* frame);
    void getLotteryResultInfo(UISummeryLotteryItem* ui, int itemCount, class LotteryResultIconInfo& dest);
    void showLackMaterial(SexyString materialName);
    void showTip(const SexyString& tip);
    void confirmBuy(class UIMessageBox* box, int buttonID);
    void onRequestSummeryLottery(int result, const class S2C_SummeryLotteryData& data);
    void onNotifySummeryMaterialBuy(class MsgResultInfo* io_result, const class S2C_ICloud_GetConsumeGemInfo* pInfo, const class S2C_PlayerInfo* pGemChanged);
    void onNetworkError(int erroId, const std::string& requestID);
    void ShowNetErrorTip();
    void refreshNewTips();
    Sexy::Widget* CreatePanel();
    Sexy::Widget* CreateLuckProgressBack();
    UIWidgetText* GetMaterialText();
    
    LotteryPanelData* m_lotteryData = nullptr;
    LuckyProgressUtil m_progressUtil;
    bool m_buttonsDisabled = false;
    Sexy::Widget* m_panel = nullptr;
    Sexy::Widget* m_luckProgress = nullptr;
    Sexy::Widget* m_ClipWidget = nullptr;
    Sexy::Widget* m_innerProgress = nullptr;
    UIWidgetAnim* m_specialBouns = nullptr;
    UIWidgetText* m_materialText = nullptr;
    bool m_requestingLottery = false;
    pvztime_t m_nextRequestTime = 0;
    int m_requestCount = 0;
};

class BossChallengeRankServerData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(BossChallengeRankServerData, Sexy::RtObject, Sexy::RtClass);
public:
    int iBeginRank = 0;
    int iEndRank = 0;
    int iDiamond = 0;
    int iCoin = 0;
    int iHeadFrameID = 0;
    int iHeadImageId = 0;
};

class BossChallengeServerData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(BossChallengeServerData, Sexy::RtObject, Sexy::RtClass);
    
public:
    int  challengeCountLeft = 0;
    int  challengeCountBuyAlready = 0;
    int  challengeCountBuyLeft = 0;
    int  bossToChallenge = 0;
    int  reward = 0;
    std::vector<BossChallengeRankServerData> rank;
    std::vector<int> price;
};

class BossChallengeMedalLotteryServerData : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(BossChallengeMedalLotteryServerData, Sexy::RtObject, Sexy::RtClass);
    
public:
    int  medalCount = 0;
    int  luck = 0;
    int  maxLuck = 1;
    int  medalEach = 0;
    std::vector<S2C_ICloud_IDCount> specialItem;
    std::vector<S2C_ICloud_IDCount> itemIdList;
};


#endif /* UIBossMedalLottery_h */
