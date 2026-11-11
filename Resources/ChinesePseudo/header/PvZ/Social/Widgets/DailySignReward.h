//
//  DailySignReward.h
//  PlantsVersusZombies2
//
//  Created by Bokun Zhao on 14-7-17.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#include "LuaEngine/lua_support/LuaDef.h"

#ifndef __PlantsVersusZombies2__DailySignReward__
#define __PlantsVersusZombies2__DailySignReward__

#include "Precompile.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "NetworkMsgProcess.h"
#include "DailyRewardConfig.h"
#include "Effect_PopAnim.h"
#include "EASquared.h"

namespace Message
{
	void GetCurrentDailyReward();
	void DailySignRewardReceived(int i_id);
}


// this is for supplementary sign
enum {
    SupplementarySignBtn = 1000,// daily sign reward btn
    SupplementarySignBtn_One,// supplementary sign panel btn
    SupplementarySignBtn_All,
    SupplementarySignBtn_Exit,
};

class SignButton : public PVZ2UIButton
{
public:
    SignButton(int i_id, Sexy::ButtonListener* i_listener, const SexyString& i_buttonName = _S(""), const Sexy::Color& i_fontColor = Sexy::Color::White);
    virtual ~SignButton();

    void Draw(Sexy::Graphics* i_g) override;

    void SetDescription(SexyString str);
    void SetDiamondCount(int count);

private:
    SexyString _description;// sign description
    Image* _diamondImg;
    SexyString _diamondCountStr;// use diamonds to sign
};

// this is for ios supplementary sign
class SupplementarySignPanel : public Widget, Sexy::ButtonListener
{
public:
    SupplementarySignPanel(class DailySignReward* ptr); 
    virtual ~SupplementarySignPanel();

    virtual void InitView();
    virtual void Draw(Graphics *i_g) override;
    virtual void ButtonDepress(int i_id) override;

private:
    bool CheckEnoughGem(int gem);

private:
    SexyString _description;// sign description
    SignButton* _signOneBtn;// sign one day
    SignButton* _signAllBtn;// sign all days
    PVZ2UIButton* _exitBtn;
    DailySignReward* _dailySignReward;

    int _signOneGemCount;// use gem to sign
    int _signAllGemCount;
    int _signAllDayCount;// how many days should sign
};

class SignRewardScrollPanel : public Widget
{
public:
    
	SignRewardScrollPanel(Rect &i_rect, int i_contentSize);
	SignRewardScrollPanel(Rect &i_rect, int i_contentSize, bool bShowLastFrame);
    ~SignRewardScrollPanel();
    
private:
    
    void	InitView();
    bool    m_bShowLastFrame;
    int     m_contentSize;
public:
    std::vector<class DailySignRewardContent*> m_contents;
};

enum SignRewardButtonId
{
    SIGN_REWARD_BUTTON_ID_CLOSE = 0,
};

class DailySignReward : public Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:
	DailySignReward(bool i_action);
    ~DailySignReward();
    
    virtual void ButtonDepress(int i_id);
    virtual void Update();
    virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}
    
    void getReward(int i_id, int i_amount);
    void onProcessSignRewardResult(const S2C_ICloud_DailySignInfo* i_signRewardList);
    void onProcessSignRewardException(int i_errorCode);
	
    // for ads watching
	void onAdsFinish(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
	bool IsAdvertisementEnable();
	bool IsDaySignCountAvaliable();// check if the daysign sum is smaller than now server day. 

    int GetSupplementarySignDaysCount();// how many days should supplementary sign
    void CreateSupplementarySignDescription(int days);
    void CreateSupplementarySignPanel();
    int GetSupplementarySignGems(int type);// type: 0 = all, 1 = one day
    void InitializeSupplementaryGemsArray(std::vector<int> array);
    void ConfirmWatchAD(class UIMessageBox* box, int buttonID);
    void onADFinished(int i_type);

private:
    void InitView();
    
	PVZ2UIScrollingWidget* m_scrollingWidget;
    PVZ2UIButton*           m_closeButton;
    
    int m_loginDays;
    int m_rewardPoolSize;
    ImagePtr m_titleImage;
    SexyString m_titleText;
    
    bool m_bAction;

    // ads
#ifdef HOST_ANDROID
	PVZ2UIButton* m_advertisementButton;
	SexyString m_adsLabel;
#endif
	bool m_bIsAdsVisible;

//#ifdef HOST_IPHONEOS
    bool _shouldSupplementarySign;// if should supplementary sign
    SexyString _text1;// "this mouth could"
    SexyString _text2;// "{NUM} days"
    PVZ2UIButton* _supplementarySignButton;
    SupplementarySignPanel* _supplementarySignPanel;
    std::vector<int> _supplementarySignGemsArray;
//#endif
};

class DailySignRewardContent : public Widget, Sexy::ButtonListener
{
public:
	DailySignRewardContent(int i_loginId, bool i_hasGotReward, bool i_canGetReward, bool i_needHighlight, bool bShowLastFrame);
	~DailySignRewardContent();
    
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void Draw(Graphics *i_g);
    virtual void Update();
    
    void SetSelected(bool i_selected);
	void onDailySignRewardReceived(int i_id);
    
private:
    
	Image *     m_rewardImage;
	Image *     m_bgImage;
	Image *     m_obtainImage;
    
    PVZ2UIButton *   m_getButton;
    Effect_PopAnim * m_getAnim;
    Effect_PopAnim * m_bgAnim;
    Effect_PopAnim * m_handAnim;

    ImagePtr m_amountImage;
    SexyString m_titleStr;
    
    int  m_nRewardAmount;
    
	int m_contentWidth;
	int m_loginId;
    int m_iCount;
    
	bool m_hasGotReward;
	bool m_canGetReward;	//only if m_hasGotReward == false will we need to use this bool
	bool m_needHighlight;
    bool m_bShowLastFrame;
    bool m_showAnim;
    
    float m_drawScale;

    std::string m_plantPieceType;

    bool m_CanDoubleReward;

	void InitView();
};

//add for lua process network message
void onProcessSignRewardResult(const S2C_ICloud_DailySignInfo* i_signRewardList);
void getReward(int i_id, int i_amount);

#endif /* defined(__PlantsVersusZombies2__DailySignReward__) */
