//
//  RedPackUI.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15-1-16.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RedPackUI__
#define __PlantsVersusZombies2__RedPackUI__

#include <stdio.h>
#include "Precompile.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "NetworkMsgProcess.h"
#include "StoreUI.h"
#include "RedPackOpenUI.h"
#include "UIRedPacket.h"
#include "GameStateMgr.h"

namespace Message
{
    void RedPackPurchased(int i_redPackCount);
}

enum RedPackUIState
{
    RedPackState_Default = -1,
    RedPackState_Main = 0,
    RedPackState_LeaderBoard,
    RedPackState_Buy,
};

enum RedPackButton
{
    RedPackButton_Close = 100,
    RedPackButton_Buy,
    RedPackButton_LeaderBoard,
    RedPackButton_Open,
    RedPackButton_Back,
    RedPackButton_Preview,
    RedPackButton_Check,
};

struct RedPackLeaderBoardInfo
{
    std::string m_playerName;
    std::string m_score;
    int m_rank;
    
    RedPackLeaderBoardInfo()
    {
        m_playerName = "";
        m_rank = 0;
        m_score = "";
    }
};

class RedPackLeaderBoardScrollPanel : public Widget
{
public:
    RedPackLeaderBoardScrollPanel(Sexy::Rect &i_rect, const std::vector<RedPackLeaderBoardInfo* >& i_info);
    virtual ~RedPackLeaderBoardScrollPanel();
    
private:
    void	InitView();
    std::vector<RedPackLeaderBoardInfo* > m_leaderBoardInfo;
};

class RedPackLeaderBoardContent : public Widget, Sexy::ButtonListener
{
public:
    RedPackLeaderBoardContent(int i_rank, const SexyString& i_playerName, const SexyString& i_score);
    virtual ~RedPackLeaderBoardContent();
    
    virtual void Draw(Graphics *i_g);
    
private:
    int m_rank;
    SexyString m_playerName;
    SexyString m_score;
};

struct RedPackDisplayData
{
	RedPackDisplayData()
    {
    	Amount = 0;
    	ObjectId = 0;
    }

	int Amount;
	int ObjectId;
};

struct NetworkRedPackDisplayData
{
	NetworkRedPackDisplayData()
	{
		ObjectId = 0;
		Quantity = 0;
	}
	int ObjectId;
	int Quantity;
};

class NetworkRedPackDisplayInfo : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NetworkRedPackDisplayInfo, Sexy::RtObject, Sexy::RtClass);

public:
    std::vector<NetworkRedPackDisplayData>     displayInfos;
    int redPackCount;
    int useOld;
};

class NetworkBuyRedPackInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkBuyRedPackInfo, INetworkData, RtClass);

public:
	int redPackCount;
};

class RedPackDisplayContent : public Sexy::Widget
{
public:

	RedPackDisplayContent(const RedPackDisplayData & data);
	virtual ~RedPackDisplayContent();

	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

private:

    void            setupScreen();

private:

    RedPackDisplayData  m_data;
};

class UIBuyRedPacket:public DNodeWidget
{
public:
    static UIBuyRedPacket* create(bool focus = true, FestivalEventType i_type = Event_RedPack);
    //UIRedPacket();
    virtual ~UIBuyRedPacket();

    virtual void Initialize() override;
    virtual void UserInit() override;
    void AdjustInnerUI(int i_offsetx, int i_offsety);
    void BuyRedPacket(const std::string& i_sku);

public:
    static UIBuyRedPacket* s_pBuyWidgetHandler;
    static FestivalEventType m_eventType;
};

class RedPackUI : public Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    RedPackUI(FestivalEventType i_type);
    virtual ~RedPackUI();
    
    //static RedPackUI* create();

    virtual void ButtonDepress(int i_id);
    virtual void Update();
    virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
    void onProcessLeaderBoardInfo(const S2C_ICloud_RedPackLeaderBoard * i_info);
#ifdef HOST_ANDROID
    void onRedPackLeaderBoardReward();
#else
    void onRedPackLeaderBoardReward(const S2C_ICloud_RedPackLeaderBoardReward* i_info);
#endif
    void onNetworkError(int erroId);
    void onCloseDialog();
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    
    void requestBuyRedPacket(int i_num);
    void requestBuyDumpling(int i_num);

    void requestNetwork();

    static RedPackUI* s_pWidgetHandler;

private:
    void InitView();
    void SetState(RedPackUIState i_state);
    void SyncActivityData(const NetworkRedPackDisplayInfo& i_data);
    void SetupRewardDisplay();
    void SetContentsVisible(bool i_visible);
#ifdef HOST_ANDROID
    void DoOpenRedPack(int iOpenNum);
#endif
    SexyString GetRankRewardNameByConfigNameAndGetReward(std::string& strConfigName, int iCount);
    void RankMySelf(std::vector<S2C_RedPack_Public>& publicRank,  S2C_RedPack_Public& selfScore);
    void RefreshGetRewardButton();
    static bool RankSort(const S2C_RedPack_Public& item_1, const S2C_RedPack_Public& item_2);
    
    //Overall
    PVZ2UIButton*       m_closeButton;
    RedPackUIState      m_state;
    Sexy::Rect                m_bgRect;
    Image*              m_titleImg;
    
    //State_Main
    int                 m_redPackRank;
    PVZ2UIButton*       m_buyButton;
    PVZ2UIButton*       m_leaderBoardButton;
    PVZ2UIButton*       m_openButton;
    PVZ2UIButton*       m_checkButton;
    void                DrawMainState(Graphics *i_g);
    void                onBuyRedPack();
    
    //State_LeaderBoard
    std::vector<RedPackLeaderBoardInfo* > m_leaderBoardInfo;
    int                     m_redPackOpenNum;
    bool                    m_isLeaderBoardEmpty;
    Sexy::Rect                    m_bgPanelRect;
    PVZ2UIButton*           m_backButton;
    PVZ2UIButton*           m_previewButton;
    PVZ2UIScrollingWidget*  m_scrollingWidget;
    void                    DrawLeaderBoardState(Graphics *i_g);
    void                    onDialogCancel();
    
    //State_Buy
    StorePanelUI*           m_panelUI;
    pvztime_t               m_successHintTime;
    SexyString              m_hintStr;
    bool                    m_shouldDrawSuccessHint;
    Sexy::Rect                    m_hintRect;
    void                    DrawBuyState(Graphics *i_g);
    void                    onRedPackPurchased(int i_redPackNum);

    std::vector<RedPackDisplayData> m_rewardDatas;
    std::vector<RedPackDisplayContent*> m_contents;
    int m_redpackCount;
    FestivalEventType 		m_eventType;
    bool                    m_isUseOld;
};

#endif /* defined(__PlantsVersusZombies2__RedPackUI__) */
