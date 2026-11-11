//
//  LotteryUI.h
//  PlantsVersusZombies2
//
//  Created by Bokun Zhao on 13-8-23.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LotteryUI_h
#define PlantsVersusZombies2_LotteryUI_h
#include "Precompile.h"

#include "Widget.h"
#include "RtObject.h"
#include "PVZ2UIButton.h"
#include "Core.h"
#include "socialInfo.h"
#include "Effect_PopAnim.h"

struct LotteryCard
{
    int mX; //used to draw posX
    int mY; //used to draw posY
    std::string m_ImgStr; //used to get resource image
    int m_Id;  //used for prize process
    int m_amount;   //used for prize amount
    int m_DisplayId; //used for processing UI logic, has nothing to do with the game logic
    int m_rateMin; //used for rolling
    int m_rateMax;
};

struct LotteryTimesReward
{
    int m_time; //times player do lottery
    int m_id;   //reward type:0 for diamond, 1 for gold, 7 for keys
    int m_rewardNum;    //reward amount
};

class LotteryUI: public Sexy::Widget, public ButtonListener
{
public:
	enum
	{
		LotteryButton_Back = 0,
		LotteryButton_Start = 1,
		LotteryDialogButton_Back = 100,
		LotteryTimesDialogButton_Back = 101,
	};
    LotteryUI(bool bCanDoLottery = true);
    ~LotteryUI();
    
    void InitView();
    
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void Update();
    //PVZ2_CHINESE_END
    
	virtual void Draw(Graphics* i_g);
	virtual void ButtonDepress(int i_id);
    
private:
    int GetCols();
    int GetRows();
    
private:
    PVZ2UIButton* m_backButton;
    PVZ2UIButton* m_startButton;
    int m_cardSelectId;
    int m_resultId;
    int m_loopingCounter;
    int m_fadingCounter;
    
    bool m_isLotterying;
    bool m_isFinished;
    pvztime_t m_animTime;
    pvztime_t m_endAnimTime;
    
    bool m_isServerError;

    int m_cardSelectorX;
    int m_cardSelectorY;
    
    Effect_PopAnim* m_popAnimEffect;
    Effect_PopAnim* m_selectAnimEffect;
//    Effect_PopAnim* m_testAnimEffect[12];
    
    void DrawCard(Graphics* i_g);
    void DrawDecoration(Graphics* i_g);
    void DrawBottomPrize(Graphics* i_g);
    
    void doHintDialog();
    void doTimesHintDialog();
    void onLotteryDisabled();

    int getLotteryCardPosX(int displayId);
    int getLotteryCardPosY(int displayId);
    
    int getLotteryResult();
    bool processLotteryResult(int m_id);
    
    void moveSelector();
    
    bool EnableToLottery();
    Rect m_dialogRect;
    Rect m_bottonRect;
    Rect m_prizeRect;
    Rect m_cardRect;
};

#endif
