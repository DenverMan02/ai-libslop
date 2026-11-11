/*
 * PVZ2UINewDangerRoom.h
 *
 *  Created on: 2015-9-13
 *      Author: jianglc
 */

#ifndef PVZ2UINEWDANGERROOM_H_
#define PVZ2UINEWDANGERROOM_H_

#include "Core.h"
#include "ResourceHelpers.h"
#include "Effect_PopAnim.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "NetworkMsgProcess.h"
#include "DangerRoomScoreRewardConfig.h"

struct DangerRoomLeaderBoardInfo
{
    std::string m_playerName;
    std::string m_score;
    int m_rank;

    DangerRoomLeaderBoardInfo()
    {
        m_playerName = "";
        m_rank = 0;
        m_score = "";
    }
};

enum LeaderBoardRequestState
{
	// Only for android
	LeaderBoard_RequestSelf,
	//
	LeaderBoard_PreRequest,
	LeaderBoard_Requesting,
	LeaderBoard_Finish_Request
};

enum LeaderBoardLevel
{
	LeaderBoard_Level_0 = 0,
	LeaderBoard_Level_1 = 20,
	LeaderBoard_Level_2 = 40,
	LeaderBoard_Level_3 = 60,
	LeaderBoard_Level_4 = 80
};

enum dangerRoomButtonId{
    ENUM_RULE_OK=0,
};

//============== Add by BK ================
class DangerRoomRewardContent : public Widget, Sexy::ButtonListener
{
public:
    DangerRoomRewardContent(bool i_hasGotReward, bool i_canGetReward, bool i_needHighlight);
    ~DangerRoomRewardContent();
    
    virtual void Resize(int theX, int theY, int theWidth, int theHeight);
    virtual void Draw(Graphics *i_g);
    virtual void Update();
    virtual void ButtonDepress(int i_id);
    
    void InitView(DangerRoomRewardData * pDailyReward, bool i_bImageAmount);
    
private:
    
    Image* m_rewardImage;
    Image* m_bgImage;
    SexyString m_titleStr;
    Image* m_obtainImage;
    ImagePtr m_amountImage;
    
    int  m_nRewardAmount;
    bool m_bImageAmount;
    
    int  m_contentWidth;
    bool m_hasGotReward;
    bool m_canGetReward;	//only if m_hasGotReward == false will we need to use this bool
    bool m_needHighlight;
    
    float m_drawScale;
    
    
};
//====================================================

class DangerRoomRuleWidget : public Widget, Sexy::ButtonListener
{
public:
	DangerRoomRuleWidget();
	virtual ~DangerRoomRuleWidget();
	void Init();
	virtual void Draw(Sexy::Graphics* i_g);

	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);

private:

    PVZ2UIButton* createBtn( dangerRoomButtonId enbtn, Sexy::Image* btnimg, Sexy::Image* btnimgd );

	SexyString			m_displayStr;

	PVZ2UIButton*		m_ConfirmButton;
};

class DangerRoomLeaderBoardContent : public Widget, Sexy::ButtonListener
{
public:
	DangerRoomLeaderBoardContent(int i_rank, const SexyString& i_playerName, const SexyString& i_score);
    virtual ~DangerRoomLeaderBoardContent();

    virtual void Draw(Graphics *i_g);

    void SetInfo(DangerRoomLeaderBoardInfo* i_info);

private:
    int m_rank;
    SexyString m_playerName;
    SexyString m_score;
    int m_id;
public:
    bool m_init;
};

class DangerRoomLeaderBoardScrollPanel : public Widget
{
public:
	DangerRoomLeaderBoardScrollPanel(Sexy::Rect &i_rect, const std::vector<DangerRoomLeaderBoardInfo* >& i_info, int i_btnLine);
    virtual ~DangerRoomLeaderBoardScrollPanel();

    void SyncContents(int i_offset, const std::vector<DangerRoomLeaderBoardInfo* >& i_info);

    virtual void Update();
    void SetState(LeaderBoardRequestState i_state) { m_state = i_state; }
    int GetRankCount() { return m_offset; }
    
private:
    void	InitView();
    void 	onProcessLeaderBoardInfo(const S2C_ICloud_DangerRoomLeaderBoard * i_info, bool i_success);
    void    OnReceivedRankInfo(bool i_success);
//    void 	onProcessLeaderBoardInfo(const S2C_ICloud_DangerRoomLeaderBoard * i_info, bool i_success);
    void 	OnCloseDialog();

    std::vector<DangerRoomLeaderBoardInfo* > m_leaderBoardInfo;
    std::vector<DangerRoomLeaderBoardContent* > m_contents;

    bool m_inited;
    int m_btmLine;
    LeaderBoardRequestState m_state;

    int m_offset;

#ifdef HOST_ANDROID
    int m_iRankOffset;
#endif
};

class PVZ2UINewDangerRoom : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	PVZ2UINewDangerRoom();
	virtual ~PVZ2UINewDangerRoom();

	virtual void Draw(Sexy::Graphics* i_g);
	virtual void Update();

	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);

	virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
	virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
    
    void GotDangerRoomRankList();
    void SetDangerRoomBonusFromServer(int i_gems) { m_drRewardGems = i_gems; }
//	void SetOffset(int i_offset) { m_offset = i_offset; }
//	int GetOffset() { return m_offset; }

private:
    void    ChooseLevelAndStart();
	void OnRequestRankFinished(bool i_success);

//    void OnRequestRankFinished(bool i_success);
    void OnGetDangerRoomBonus(bool i_success);
    
    void OnAcceptStart();
    void SyncAllTexts();

    void BuyLife();

    void OnLifeBought();
    void OnBackToMap();
    void OnCloseDialog();

    void OnConfirmBuyLife();
    void ConsumeLife();
    void OnStartDangerRoomPlay(bool i_success);
//    void OnConfirmBuyLife();
    void InitView();
    void OnScoreRewardClosed();
    void HandleTutorialInputs();
    void OnTutorialFinished();

    //void onProcessLeaderBoardInfo(const S2C_ICloud_DangerRoomLeaderBoard * i_info);

	PVZ2UIButton*		m_closeButton;
    PVZ2UIButton*		m_ruleButton;
    PVZ2UIButton*		m_rewardButton;
    PVZ2UIButton*		m_startButton;
#ifdef HOST_IPHONEOS
    PVZ2UIButton*		m_levelRewardButton;
    PVZ2UIButton*       m_RankListButton;
#endif

    SexyString          m_titleTextValue;
    SexyString          m_highestScoreTextValue;
    SexyString          m_rewardText;

    class PVZ2UIScrollingWidget*  m_scrollingWidget;

    std::vector<DangerRoomLeaderBoardInfo* > m_leaderBoardInfo;

    DangerRoomLeaderBoardScrollPanel* m_panel;

    bool				m_canGetReward;

    class BouncingArrow* m_tutorialArrow;

    int                 m_drRewardGems;
    //int m_offset;
};


#endif /* PVZ2UINEWDANGERROOM_H_ */
