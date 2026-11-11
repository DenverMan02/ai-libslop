//
//  DailyAchievement.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/9/11.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__DailyAchievement__
#define __PlantsVersusZombies2__DailyAchievement__

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "UIWidget.h"
#include "PVZ2UIButton.h"
#include "ButtonListener.h"
#include "DailyAchievementInfo.h"
#include "Effect_PopAnim.h"
#include "PrimeTextWidget.h"
#include "NetworkData.h"

struct AchievementContentInfo
{
    AchievementItem     m_achievementItem;
    std::string         m_rewardImage;
    std::string         m_rewardType;
    int                 m_targetNum;
    int                 m_rewardCount;
    int                 m_rewardPieceCount;
    std::string         m_rewardName;
    AchievementContentInfo()
    {
        m_achievementItem = AchievementItem();
        m_targetNum = 0;
        m_rewardCount = 0;
        m_rewardPieceCount = 0;
        m_rewardName = "";
    }
};

enum AchievementButton
{
    AchievementButton_Close = 100,
};

class AchievementScrollPanel : public Widget
{
public:
    AchievementScrollPanel(Sexy::Rect &i_rect, const std::vector<AchievementContentInfo>& i_content);
    virtual ~AchievementScrollPanel();
    
private:
    void	InitView();
    
private:
    std::vector<AchievementContentInfo> m_contents;
};

class New_S2C_VaseBreakerReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(New_S2C_VaseBreakerReward, INetworkData, RtClass);

    NetworkRewardContent m_reward;
};

class AchievementContent : public Widget, public Sexy::ButtonListener
{
public:
    AchievementContent(const AchievementContentInfo& i_info, int i_index);
    virtual ~AchievementContent();
    
    virtual void Draw(Graphics *i_g) override;
    void Resize(int theX, int theY, int theWidth, int theHeight) override;
    void ButtonDepress(int i_id) override;
    void GetReward();
    std::string getSpecifiedImage(const std::string& i_specifiedType);
    void getPieceImage(const std::string& i_pieceType, const std::string& i_plantName);
    void onDailyAchievementReceived(int i_actId, int i_targetNum);
    void onNotifyAchievementReward(int i_achid, int i_num);

private:
    int m_currentNum;
    int m_targetNum;
    int m_rewardCount;
    int m_rewardPieceCount;
    int m_actId;
    
    SexyString m_targetDesc;
    SexyString m_targetNumStr;
    SexyString m_rewardCountStr;
    
    std::string m_specificSku;
    std::string m_rewardImage;
    std::string m_rewardType;
    std::string m_rewardName;
    PVZ2UIButton* m_obtainButton;
    int m_index;
    
};

class DailyAchievement : public Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    DailyAchievement();
    virtual ~DailyAchievement();
    void Update() override;
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    void ButtonPress(int i_id) override;
    void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    void SyncActivityData(const NetworkAchievementItem& i_data);
    
private:
    void InitView();
    
private:
    PVZ2UIButton*             m_closeButton;
    Sexy::Rect                m_bgRect;
    Sexy::Rect                m_bgPanelRect;
    PVZ2UIScrollingWidget*    m_scrollingWidget;
    
    SexyString               m_tips;
    int                       m_date;
    std::vector<AchievementContentInfo>          m_contents;
};

#endif /* defined(__PlantsVersusZombies2__DailyAchievement__) */
