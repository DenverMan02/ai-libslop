//
//  LanternRiddlesUI.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15-1-9.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__LanternRiddlesUI__
#define __PlantsVersusZombies2__LanternRiddlesUI__

#include <stdio.h>
#include "Precompile.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "NetworkMsgProcess.h"
#include "Effect_PopAnim.h"

#define ANSWER_NUM 4
#define RIDDLES_NUM 5
#define PRIZE_POOL_NUM 5
#define RIDDLE_DAYS_TOTAL 16

#define TOPIC_NAME                      "RedPack"
#define REWARD_PLANT                    "cracker"
#define IMAGE_RIDDLE_TITLE              "IMAGE_UI_DIALOG_ASSET_DIALOG_MAIN_TITLE_RED"
#define IMAGE_RIDDLE_TITLE_STR          "IMAGE_UI_LANTERN_TITLE_STR"
#define IMAGE_ANIM_ZONGZI               "POPANIM_EFFECTS_RED_PACKET"
#define IMAGE_ANIM_ZONGZI_OPEN          "POPANIM_EFFECTS_REDPACK_OPEN"
#define IMAGE_BUY1                      "IMAGE_UI_REDPACK_REDPACK_BUY_SMALL"
#define IMAGE_BUY10                     "IMAGE_UI_REDPACK_REDPACK_BUY_LARGE"
#define IMAGE_LITTLE_ICON               "IMAGE_UI_LANTERN_RED_PACK"
#define IMAGE_BIG_ICON                  "IMAGE_UI_REDPACK_RED_PACK"
#define IMAGE_REWARD_TITLE_STR          "IMAGE_UI_REDPACK_REDPACK_STR"
#define IMAGE_REWARD_AVATAR             "IMAGE_UI_LANTERN_AVATAR_PAMEGRANATE"
#define IMAGE_PLANT                     "IMAGE_UI_LANTERN_PAMEGRANATE"
#define IMAGE_ASS                       "IMAGE_UI_LANTERN_POLE"

enum LanternDiamond
{
    Diamond_Cheat = 10101,
    Diamond_Extra = 10102,
};

enum LanternButton
{
    LanternButton_Close = 100,
    LanternButton_Start,
    LanternButton_Next,
    LanternButton_Cheat,
    LanternButton_Extra,
    LanternButton_Prize,
    LanternButton_GetPrize,
    LanternButton_RedPack,
};

enum LanternUIState
{
    LanternState_Default = -1,
    LanternState_Main = 0,
    LanternState_Riddle,
    LanternState_End,
    LanternState_Prize,
};

struct LanternBonus
{
	int itemId;
	int quantity;
};

class LanternRiddlesInfo: public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(LanternRiddlesInfo, Sexy::RtObject, RtClass);

	LanternRiddlesInfo();

	int m_finishedDays;
	int m_finishedToday;
	int m_correctTotal;
	int m_specialReward;
	std::vector<LanternBonus> m_todaysBonus;
};

class LanternRiddlesUI : public Widget, public Sexy::ButtonListener
{
public:
    LanternRiddlesUI(bool i_canRiddle);
    virtual ~LanternRiddlesUI();
    
    virtual void ButtonDepress(int i_id);
    virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void Update();
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
    
    void OnCheatSuccess(const bool& i_success);
    void OnExtraRiddleSuccess(const bool& i_success);
    void OnRefreshLanternUIState();
    void setCanRiddle(bool i_canRiddle) {m_canRiddle = i_canRiddle; }
    
private:
    void InitView();
    void SetState(LanternUIState i_state);
    void CalcRewardResult();
    void OnGetPrize();
    void RefreshPrizeGetButton();
    
    void onLanternRiddlesComplete(const S2C_LanternRiddlesResult& result);

    //Overall
    PVZ2UIButton*       m_closeButton;
    PVZ2UIButton*       m_prizeButton;
    PVZ2UIButton*       m_redPackButton;
    LanternUIState      m_state;
    LanternUIState      m_lastState;
    bool                m_canRiddle;
    Rect                m_bgRectCommon;
    Rect                m_bgRectLarge;
    void                DrawPrizePool(Graphics *i_g);
    int                 m_riddleDays;
    int                 m_riddleDaysTotal;
    Effect_PopAnim*     m_prizeBtnEffect;
    
    //State_Main
    SexyString          m_riddlesDesc;
    PVZ2UIButton*       m_startButton;
    void                DrawMainState(Graphics *i_g);
    
    //State_Riddle
    std::vector<int>    m_riddlesToday;
    int                 m_correctAnswerId;
    int                 m_currentRiddleId;  //Only used for UI display
    bool                m_hasCheated;
    bool                m_hasAnswered;
    int                 m_correctNum;
    
    SexyString          m_riddleStr;
    SexyString          m_riddleNumStr;
    
    PVZ2UIButton*       m_nextButton;
    PVZ2UIButton*       m_cheatButton;
    PVZ2UIButton*       m_answerButtons[ANSWER_NUM];
    
    PopAnimRig*         m_pAnimRig;
    Effect_PopAnim*     m_correctEffect;
    Effect_PopAnim*     m_wrongEffect;
    
    std::string			m_PlantPieceReward;
    int					m_PlantPieceCount;
    int					m_CoinCount;

    void                createRiddle(int i_riddleId);
    void                DrawRiddleState(Graphics *i_g);
    
    //State_End
    SexyString          m_riddleResult;
    int                 m_redPackNum;
    PVZ2UIButton*       m_extraButton;
    void                DrawEndState(Graphics *i_g);
    
    //State_Prize
    int                 m_riddlePrizeGotIndex;
    void                DrawPrizeState(Graphics *i_g);
    PVZ2UIButton*       m_getPrizeButton;
    bool                m_canGetRiddlePrize;

    static int			m_correctAnswerCount;
    static int			m_currentRiddleCount;

    class UIRewardFrame* m_UIPlantPieceReward;
    class UIRewardFrame* m_UICoinReward;
    class UIRewardFrame* m_UISpecialReward;

    class Effect_PopAnim*		m_specialReward;
};

#endif /* defined(__PlantsVersusZombies2__LanternRiddlesUI__) */
