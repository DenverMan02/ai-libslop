#ifndef UILIMITLOTTERY_H
#define UILIMITLOTTERY_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "EffectAnim_UIAnim.h"
#include "ActiveSummery.h"
#include "UIWidgetAnim.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"

namespace Message
{
	void NotifyInputEnable(bool enable);
}

struct LimitLotteryItemInfo
{
    int lotteryIndex = -1;
    int lotteryBonus = -1;
    int lotteryQuantity = 0;
};

struct CupShopItemData
{
    int itemId;
    int num;
    int cost;
};

enum LimitLotteryState
{
    LimitLS_Idle,
	LimitLS_Lotterying,
	LimitLS_Result,
};

enum LotteryMode
{
    Lottery_1,
    Lottery_5,
};

enum TypeOfBonus
{
    DEFAULT,
    PLANT,
    PLANT_CHIPS,
    PLANT_AVATAR,
    PLANT_AVATAR_CHIPS,
    PLANT_ACCESSORY,
    PLANT_ACCESSORY_CHIPS,
    PLANT_NEW_AVATAR,
    PLANT_NEW_AVATAR_CHIPS,
    GEM,
    COIN,
    CUP
};

class CupShopItemWidget : public Widget
{
public:
    CupShopItemWidget();
    virtual ~CupShopItemWidget();
public:
    virtual void			Resize(const Rect& i_Rect) override;
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;
    virtual void            TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void            TouchEnded( const Sexy::Touch& i_touch ) override;
    void                    SetShopData(const CupShopItemData& shopData);
    void                    ConfirmBuy(UIMessageBox* box, int buttonID);
    void                    OnNotifyShopItemBuyFinish(bool success, const S2C_S2C_LimitLotteryCupShop* pdata);
    void                    SetBought(bool i_buy);
    ImagePtr                RareFrameImage(int i_rare);
public:
    int32                   m_touchId;
    CupShopItemData         m_shopInfo;
    ImagePtr                m_shopImage;
    ImagePtr                m_frame;
    SexyString              m_description;
    SexyString              m_price;
    bool                    m_alreadyBuy;
    bool                    m_buyThis;
    TypeOfBonus             m_bonusType;
};

class LimitLotteryCupShop : public UISingletonDialog<LimitLotteryCupShop>, public Sexy::ScrollWidgetListener
{
public:
    LimitLotteryCupShop();
    virtual ~LimitLotteryCupShop();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UILimitLottryCupShop"; }
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void							ButtonDepress(int i_id) override;
    virtual void                            Update() override;
    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

    void                                    InitView();
    void                                    OnNotifyRefresh(bool i_success, const std::set<int>& changeList);
    void                                    UpdateCupNum(bool success,const S2C_S2C_LimitLotteryCupShop* pdata);
private:
    std::vector<CupShopItemWidget*>         m_cupShopItems;
    PVZ2UIScrollingWidget*                  m_pScrollContent = nullptr;
    Widget*                                 m_scrollPanel = nullptr;
    int                                     m_offset;
};

class LimitLotteryCrystalBuyItem : public Sexy::Widget
{
public:
    LimitLotteryCrystalBuyItem(Sexy::ButtonListener* i_listener);
    virtual ~LimitLotteryCrystalBuyItem();

    virtual void Draw(Sexy::Graphics* i_g) override;

    void SetIndex(int i_index);

private:
    int m_index;
    Sexy::ButtonListener* m_listener;
};

class LimitLotteryCrystalBuy : public UISingletonDialog<LimitLotteryCrystalBuy>, public Sexy::ScrollWidgetListener
{
public:
    LimitLotteryCrystalBuy();
    virtual ~LimitLotteryCrystalBuy();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UILimitLotteryCrystalBuy"; }
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void							ButtonDepress(int i_id) override;
    virtual void                            Update() override;
    virtual void                            ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void                            ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
};


class LimitLotteryItemTipUI : public Sexy::Widget
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    void SetTip(const SexyString& tip);
private:
    SexyString m_tip;
};

class LimitLotteryItem : public PVZ2UIButton, public ButtonListener
{
public:
	LimitLotteryItem(int i_id);
    ~LimitLotteryItem();
public:    
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonPress(int i_id) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void ButtonMouseLeave(int i_id) override;

    void SetlotteryInfo(LimitLotteryItemInfo& i_info,const std::vector<int>& lockList);
    
    int GetIndex();
    int GetBonusId();
    int GetQuantity();
    ImagePtr GetBonusImagePtr();
    std::string GetBonusName();
    SexyString GetBonusDes();
    void SetAlreadyGet(bool i_flag);
protected:
    void KillTip();
private:    
    Rect m_frameRect;
    Rect m_iconRect;

    bool m_alreadyGet;
    TypeOfBonus m_type          = TypeOfBonus::DEFAULT;

    ImagePtr m_frameImg         = nullptr;
    ImagePtr m_bonusImg         = nullptr;
    std::string m_bonusName     = "";
    SexyString m_description    = _S(""); 

    LimitLotteryItemTipUI* m_tipUI	= nullptr;
	LimitLotteryItemInfo m_lotteryInfo;
};

class LimitLotteryBonusUI : public PopingWidget, public ButtonListener
{
public:
	LimitLotteryBonusUI();
    ~LimitLotteryBonusUI();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    void InitView();
    void InitBonus(std::vector<LotteryBonus>& i_bonus);
private:
    void InitShiningAnims();
private:
    int m_bonusStartX;
    int m_bonusStartY;
    int m_bonusWidth;
    int m_bonusHeight;

    Rect m_titleImgRect;
    Rect m_titleRect;
    SexyString m_title = _S("");

    Rect m_bonusRect;
    
    Rect m_submitRect;
    PVZ2UIButton* m_submit      = nullptr;
    std::vector<LimitLotteryItem*> m_vecBonus;

    EffectAnim_UIAnim       m_openAnimRig;
    EffectAnim_UIAnim       m_backAnimRig;
};

class LimitLotteryButton : public PVZ2UIButton
{
public:
	LimitLotteryButton(int i_id, Sexy::ButtonListener* i_listener);
    ~LimitLotteryButton();
public:
    virtual void Update() override;
    virtual void Resize(const Rect& theRect) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    void InitView();    
private:
    int m_btnId;
	SexyString m_crystalS = _S("");
    SexyString m_timesS = _S("");
    Rect m_needCrystalRect;
    Rect m_lotteryTimesRect;
	Rect m_imageRect;
	ImagePtr m_image;
};

class LimitLotteryMidShow : public Widget
{
public:
    LimitLotteryMidShow();
    ~LimitLotteryMidShow();
public:
    virtual void Update() override;
    virtual void Resize(const Rect& theRect) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    void InitView();
public:
    void Clear();
    void SetChildVisible(bool i_visible);
    void SetBonus(std::vector<LotteryBonus>& bonus);
    void SetVisableIndex(int i_index){m_index = i_index;};
private:
    int m_count;
    int m_index;
    std::vector<LimitLotteryItem*> m_vecLimitLotteryItem;
	std::vector<LimitLotteryItemInfo> m_vecLimitLotteryItemInfos;
};

class LimitLotteryPanel: public Widget, public ButtonListener 
{
public:
	LimitLotteryPanel();
	virtual ~LimitLotteryPanel();
 	virtual void Update() override;
    virtual void Resize(const Rect& theRect) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
	virtual void InitView(); 
	void InitLotteryItems();
	void UpdateSelectFrame();
	virtual SexyVector2 GetLotteryItemPos(int index);

	void OnLotteryResult(bool i_success);
	void SetBonusList(std::vector<LotteryBonus>& i_bonus,const std::vector<int>& i_lock);
	void SetBonus(std::vector<LotteryBonus>& i_bonus);
	void StartLottery(int i_select = 0);

    void OnFinishLottery();
    void showLackMaterial(SexyString materialName);
    void UnlockLotteryButton();
protected:
	virtual float GetItemW();
	virtual float GetItemH();
    void OpenCrystalShop(UIMessageBox* box, int buttonID);
    void GiveRewards();
protected:
	bool m_inited = false;
    bool m_bonusShown = false; 
	Rect m_panelRect;
protected:
	//奖励项
	int m_bonusIndex = 0;
    int m_selectIndex = -1;
	LimitLotteryBonusUI* m_lotteryBonusUI = nullptr;
	std::vector<LimitLotteryItem*> m_vecLimitLotteryItem;
	std::vector<LimitLotteryItemInfo> m_vecLimitLotteryItemInfos;
    std::vector<int> m_lockList;

    void OnNotifyBonusClosed();
    public:
    void CloseBonusEffect();
protected:
	//动画相关
    LotteryMode lotteryMode;
	float m_speed = 0.f;
	int m_currentStep = 0;
    int m_speedUpEndStep = 0;
    int m_speedDownEndStep = 0;
    int m_rollingEndStep = 0;
	pvztime_t m_nextItemTime = 0.f;
	EffectAnim_UIAnim m_bonusEffect;
	LimitLotteryState m_state = LimitLS_Idle;
    std::vector<LotteryBonus> m_bonus;
    int m_theIndex;
	
    void StartNextLoop();
	void InitSteps();
	void ShowBonus();
	bool AlmostThere();
	void SelectNext();
	bool CanSelectNext();
	bool TryToSelectNext();
	void DrawSelectFrame(Graphics* i_g, const Rect i_rect);
	void ShowLotteryEffect(const std::string& i_animLabel);
	LimitLotteryItem* GetLotteryItemByIndex(int i_index);
protected:
	//抽奖按钮相关
	virtual void InitLotteryButtons();
	LimitLotteryButton * m_btnLottery1;
	LimitLotteryButton * m_btnLottery5;
	Rect m_lotteryBtnRect1; 
	Rect m_lotteryBtnRect5;
    bool m_buttonLock;

protected:
    //中间的信息显示界面
    LimitLotteryMidShow * m_midShow;
    Rect m_midShowRect;
    void InitMidShow();
};

class LimitLotteryPagePanel: public LimitLotteryPanel
{
public:
	LimitLotteryPagePanel();
	virtual ~LimitLotteryPagePanel();

	virtual void InitView() override;

	virtual void ButtonDepress(int i_id) override;

	SexyVector2 GetLotteryItemPos(int index) override;

    void DetermineLotteryOne(class UIMessageBox* box, int buttonID);
    void DetermineLotteryTen(class UIMessageBox* box, int buttonID);
    
protected:
	void InitLotteryButtons() override;
	float GetItemW() override;
	float GetItemH() override;
};

class UILimitLottery :public UISingletonDialog<UILimitLottery>
{
public:
    UILimitLottery();
	virtual ~UILimitLottery();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UILimitLottery"; }
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void							Update() override;
	virtual void							ButtonDepress(int i_id) override;
	virtual void							InitView(bool i_refresh = false);
	virtual void							OnNotifyRefresh(bool i_success, const std::set<int>& changeList);
	void 									Refresh();
	void									ShowWindow();

	void									OnStartLottery();
    void                                    OnFinishLottery();

	void									OnLimitLotteryReward(bool success, const S2C_LimitLotteryReward* pData);
    void                                    OnNotifyLimitLotteryBuyCrystalFinish(bool success, const S2C_LimitLotteryCrystalBuy* pData);
    void                                    CloseBonusEffect();
private:
	void									UpdateTimerLabel();
	void									UpdateViewInfo();
	void									SetBonusList(std::vector<LotteryBonus>& bonus,const std::vector<int>& lockList);
	void									SetBonus(std::vector<LotteryBonus>& i_bonus);
private:
    int                                     m_cupAmount;
    int                                     m_luckValue;
    int                                     m_crystalAmount;
private:
    //主panel
    LimitLotteryPanel*  m_limitLotteryPanel = nullptr;
    
	Rect m_panelRect;
	Rect m_lotteryBtnRect1; 
	Rect m_lotteryBtnRect5;
private:
    //幸运值
    Sexy::Widget*   m_luckyPanel = nullptr;//luck panel
    Sexy::Widget*   m_luckProgress = nullptr;//back
    Sexy::Widget*   m_AnimBg;
    Sexy::Widget*   m_AnimBox;
    Sexy::Widget*   m_ClipWidget = nullptr; //parameter 1
    Sexy::Widget*   m_innerProgress = nullptr; // parameter 2
    UIWidgetAnim*   m_specialBonus = nullptr; // parameter 3
    LuckyProgressUtil m_progressUtil;  //luck
public:
    void                                    InitLuckyWidget();
    Sexy::Widget*                           CreateLuckProgressBack();
};

class UILimitLotteryPage: public UISingletonDialog<UILimitLotteryPage>
{
public:
	UILimitLotteryPage();
	virtual ~UILimitLotteryPage();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UILimitLotteryPage"; }
	virtual void							Update() override;
	virtual void							ButtonDepress(int i_id) override;
	virtual void							InitView(bool i_refresh);
	virtual void							OnNotifyRefresh(bool i_success, const std::set<int>& changeList);

    void                                    CloseBonusEffect();

    void                                    DisabledAllButtons();
	void                                    EnabledAllButtons();

private:
	void									UpdateTimerLabel();
	void									UpdateViewInfo();

	void 									Refresh();

	void									OnStartLottery();
	void                                    OnFinishLottery();

	void									OnLimitLotteryReward(bool success, const S2C_SummeryLotteryData2018& data);
private:
    int                                     m_luckValue;
    int										m_luckyMax;

    //主panel
    LimitLotteryPagePanel*  m_limitLotteryPanel = nullptr;

	Rect m_panelRect;
	Rect m_lotteryBtnRect1;
	Rect m_lotteryBtnRect5;

    //幸运值
    Sexy::Widget*   m_luckyPanel = nullptr;//luck panel
    Sexy::Widget*   m_luckProgress = nullptr;//back
    Sexy::Widget*   m_AnimBg = nullptr;
    Sexy::Widget*   m_AnimBox = nullptr;
    Sexy::Widget*   m_ClipWidget = nullptr; //parameter 1
    Sexy::Widget*   m_innerProgress = nullptr; // parameter 2
    UIWidgetAnim*   m_specialBonus = nullptr; // parameter 3
    LuckyProgressUtil m_progressUtil;  //luck

protected:
    void                                    InitLuckyWidget();
    Sexy::Widget*                           CreateLuckProgressBack();
};

class LimitLotteryConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(LimitLotteryConfig, RtObject, RtClass);

    std::vector<LotteryBonus>   lotteryItems;
    std::vector<LotteryBonus>   cupShopItems;
    std::vector<int>            hasBuyed;
    std::vector<int>            hasBuyedShop;
	int                         crystalAmounts;
    int                         cupAmounts;
	int                         luckValue;
};

#endif
