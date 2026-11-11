//
//  GeilivableLottery.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 16/8/30.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef StoneLottery_h
#define StoneLottery_h

#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "EffectAnim_UIAnim.h"

struct StoneLotteryItemInfo
{
    int lotteryIndex = -1;
    int lotteryBonus = -1;
    int lotteryQuantity = 0;
};

enum StoneLotteryState
{
    StoneLS_Idle,
	StoneLS_Lotterying,
	StoneLS_Result,
};

class StoneLotteryBonusUI : public PopingWidget, public ButtonListener
{
public:
	StoneLotteryBonusUI();
    ~StoneLotteryBonusUI();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    bool IsInited() { return m_inited; }
    void InitView();
    void InitBonus(ImagePtr i_bonusImg, bool i_isPlantPieces, std::string i_bonusName, SexyString i_description);
    
private:
    void DrawBonus(Graphics* i_g);
    void InitBonusDes();
    void InitShiningAnims();
    
private:
    bool m_inited = false;
    bool m_isPlantPieces = false;
    int m_period = 0;
    
    Rect m_titleImgRect;
    Rect m_titleRect;
    Rect m_bonusRect;
    Rect m_submitRect;
    Rect m_descriptionRect;
    
    std::string m_bonusName = "";
    
    SexyString m_title = _S("");
    SexyString m_description= _S("");
    
    PVZ2UIButton* m_submit      = nullptr;
    ImagePtr m_bonusImg         = nullptr;
    
    EffectAnim_UIAnim       m_openAnimRig;
    EffectAnim_UIAnim       m_backAnimRig;
};

class StoneLotteryItemTipUI : public Sexy::Widget
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    void SetTip(const SexyString& tip);
    void SetJustification(DrawStringJustification justification) {m_jusstification = justification;}
    
private:
    SexyString m_tip;
    DrawStringJustification m_jusstification = DS_ALIGN_CENTER_VERTICAL_MIDDLE;
};

// for stay des...
class StoneLotteryItem : public PVZ2UIButton, public ButtonListener
{
public:
	StoneLotteryItem(int i_id);
    ~StoneLotteryItem();
    
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonPress(int i_id) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void ButtonMouseLeave(int i_id) override;
    
    void SetlotteryInfo(StoneLotteryItemInfo& i_info, int period);
    
    int GetIndex();
    int GetBonusId();
    int GetQuantity();
    bool IsPlantPieces();
    ImagePtr GetBonusImagePtr();
    std::string GetBonusName();
    SexyString GetBonusDes();
    
private:
    void KillTip();
    
private:
    int m_period                = 0;
    
    Rect m_frameRect;
    Rect m_iconRect;
    
    bool m_isPlantPieces        = false;
    
    ImagePtr m_frameImg         = nullptr;
    ImagePtr m_bonusImg         = nullptr;
    
    StoneLotteryItemTipUI* m_tipUI   = nullptr;
    
    std::string m_bonusName     = "";
    
    SexyString m_description    = _S("");    
    
	StoneLotteryItemInfo m_lotteryInfo;
};

class StoneLotteryButton : public PVZ2UIButton
{
public:
	StoneLotteryButton(int i_id, Sexy::ButtonListener* i_listener);
    ~StoneLotteryButton();
    
    virtual void Update() override;
    virtual void Resize(const Rect& theRect) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    
    void SetChances(int i_chances);
    void InitView();
    
private:
    int m_chances = 0;
    
    Rect m_titleRect;
    Rect m_chanceRect;
    
    SexyString m_titleS = _S("");
    SexyString m_chancesS = _S("");
};

class StoneLotteryPanel: public Widget, public ButtonListener
{
public:
	StoneLotteryPanel();
    ~StoneLotteryPanel();
    
    virtual void Update() override;
    virtual void Resize(const Rect& theRect) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    void InitView();
    void InitLotteryItems();
    void SetInited(bool i_init);
    bool IsInited();
    
    SexyVector2 GetLotteryItemPos(int i_index);
    void SetPeriod(int i_period);
    void SetPanelChances(int i_chances);
	
	void updateLotteryBtn();

    void StartLottery();
    void FinishLottery();
    void ShowBonus();
    void SetBonusList(std::vector<LotteryBonus>& i_bonusList);
    void SetBonus(int i_bonusId, int i_bonusQuantity);
    void ShowLotteryEffect(const std::string& i_animLabel);
    void CloseBonusEffect();
    
    void SetChanceUsed(int i_chancesUsed) { m_chancesUsed = i_chancesUsed; }
    void SetGemsUsed(int i_gemsUsed) { m_gemsUsed = i_gemsUsed; }
    
	int getAvailableChance();
	void setOncePay(int oncePay);
	void setTotalChance(int totalChance);

private:
    float GetItemW();
    float GetItemH();
    
    void InitSteps();
    void UpdateSelectFrame();
    bool AlmostThere();
    bool TryToSelectNext();
    bool CanSelectNext();
    void SelectNext();
    void OnLotteryResult(bool i_success);
    void OnNotifyBonusClosed();
    
    void DrawSelectFrame(Graphics* i_g, const Rect i_rect);
    
	StoneLotteryItemInfo GetLotteryInfoByIndex(int i_index);
    StoneLotteryItem* GetLotteryItemByIndex(int i_index);
    
private:
    bool m_inited = false;
    bool m_bonusShown = false;
    
    int m_currentStep = 0;
    int m_speedUpEndStep = 0;
    int m_speedDownEndStep = 0;
    int m_rollingEndStep = 0;
    
    int m_period = 0;
    int m_leftChance = 0;
	int m_nTotalChance = 0;
	int m_nOncePay = 1;

    int m_bonusIndex = 0;
    int m_selectIndex = -1;
    
    int m_chancesUsed = 0;
    int m_gemsUsed = 0;
    
    float m_speed = 0.f;
    
    pvztime_t m_nextItemTime = 0.f;
    
    Rect m_lotteryRect;
    Rect m_lotteryBtnRect;
    
    StoneLotteryState m_state = StoneLS_Idle;
    
    StoneLotteryButton* m_lotteryBtn = nullptr;
    ImagePtr m_imageDoll = nullptr;
    
    EffectAnim_UIAnim m_bonusEffect;
    StoneLotteryBonusUI* m_lotteryBonusUI = nullptr;
    
    std::vector<StoneLotteryItemInfo> m_lotteryItemInfos;
    std::vector<StoneLotteryItem*> m_lotteryItems;
};

class StoneLinkButton : public PVZ2UIButton
{
public:
	StoneLinkButton(int i_id, Sexy::ButtonListener* i_listener);
    ~StoneLinkButton();
    
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    void SetImage(ImagePtr i_idle, ImagePtr i_pressed);
    void SetImage(ImagePtr i_idle);
    int GetLinkButtonWidth();
    int GetLinkButtonHeight();
    ImagePtr GetButtonImage();
    bool CanDraw();
    
private:
    ImagePtr m_idleImg = nullptr;
};

class StoneLottery: public PopingWidget, public ButtonListener
{
public:
	StoneLottery();
    virtual ~StoneLottery();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    void SetDeliveryInfo(std::string i_tel, std::string i_email);
    void SetPrizeWinOrNot(bool i_win);
    bool IsInited();
    void SetBonusList(std::vector<LotteryBonus>& i_bonusList);
    void SetSourId(int i_sourId) { m_sourId = i_sourId; };
    void SetInitInfo(int i_period, int i_oncepay, int i_totalChance, int i_leftChance, bool isFirstTolottery);
    void SetBonus(int i_bonusId, int i_bonusQuantity);
    
    void Refresh();
    virtual void InitView(bool i_refresh = false);
    SexyString GetTelSexyString() { return m_tel; }
    SexyString GetEmailSexyString() { return m_email; }
    int GetPeriod() { return m_period; }
    bool GetWinOrNot() { return m_win; }
    
    virtual void ShowWindow();
    void CloseBonusEffect();
    virtual void OnNotifyRefresh(bool i_success, const std::set<int>& changeList);
    void OnStartLottery();
    void OnFinishLottery();
    void OnLotteryReward(const S2C_StoneLotteryReward& reward);
    
	int GetLeftChance() const { return m_leftChance; };
	int GetTotalChance() const { return m_nTotalChance; };
	int GetOncePay() const { return m_oncepay; };
protected:
    bool HasLoadedGroup(std::string i_loadingResGroupName);
    void AddLoadingGroup(std::string i_loadingResGroupName);
    void AddResourceGroups();
    void ReleaseResourceGroups();
    void UpdateTimeLabel();
    
    ImagePtr GetBannerImage();

protected:  
    bool m_inited = false;
    bool m_win = false;
    
    bool m_android = false;
    
    Rect m_titleRect;
    Rect m_titleImgRect;
    Rect m_closeRect;
    Rect m_bannerRect;
    Rect m_mainPanelRect;
    Rect m_lotteryRect;
    Rect m_lotteryBtnRect;
    Rect m_linkTitleRect;
    Rect m_link1Rect;
    Rect m_link2Rect;
    Rect m_link3Rect;
    Rect m_link4Rect;
    Rect m_deliveryBtnRect;
    Rect m_hintRect;
    Rect m_remainRect;
    Rect m_oncePayRect;
    Rect m_paidRect;
    Rect m_chanceRect;
    Rect m_timeRect;
    
    Rect m_linkPanelRect;
    Rect m_linkHintRect;
    Rect m_linkPayRect;
    
    SexyString m_title = _S("");
    SexyString m_remain = _S("");
    SexyString m_linkTitle = _S("");
    SexyString m_oncePay = _S("");
    SexyString m_paid = _S("");
    SexyString m_strChance = _S("");
    SexyString m_tel = _S("");
    SexyString m_email = _S("");
    SexyString m_timeLebal;
    
    Color m_timeColor = Color::White;
    
    int m_period = 0;
    int m_oncepay = 1;
    int m_totalChance = 0;
    int m_leftChance = 0;
	int m_nTotalChance = 0;
	bool m_bIsFirstToLottery;

	int m_sourId = 0;
    
    ImagePtr m_bannerImg = nullptr;
    ImagePtr m_linkHintImg = nullptr;
    
    PVZ2UIButton* m_closeBtn = nullptr;
    PVZ2UIButton* m_payBtn = nullptr;
    PVZ2UIButton* m_deliveryBtn = nullptr;
    
	StoneLinkButton* m_link1 = nullptr;
	StoneLinkButton* m_link2 = nullptr;
    StoneLinkButton* m_link3 = nullptr;
	StoneLinkButton* m_link4 = nullptr;
    
    StoneLotteryPanel* m_lotteryPanel = nullptr;
    
    std::vector<std::string>    m_loadedGroup;
};

class StoneLotteryNationalDay : public StoneLottery
{
public:
    StoneLotteryNationalDay();
    ~StoneLotteryNationalDay();

    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void InitView(bool i_refresh = false);
    virtual void ShowWindow();
    virtual void OnNotifyRefresh(bool i_success, const std::set<int>& changeList);
};

class GLStoneLotInfoWidget : public PopingWidget, public ButtonListener, public Sexy::EditListener
{
public:
	GLStoneLotInfoWidget();
    ~GLStoneLotInfoWidget();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    void SetDeliveryInfo(SexyString i_tel, SexyString i_email);
    void SetPrizeWinOrNot(bool i_win) { m_win = i_win; }
    bool IsInited() { return m_inited; }
    
    void InitView();
    bool IsTelEditWidgetFocus();
    bool IsEmailEditWidgetFocus();
    
private:
    bool ValidTel(std::string& i_tel);
    bool ValidEmail(std::string& i_email);
    void OnGLDeliverySend(bool i_success);
    
private:
    bool m_inited = false;
    bool m_win = false;
    bool m_inputting = false;
    bool m_telEdited = false;
    bool m_emailEdited = false;
    
    Rect m_titleImgRect;
    Rect m_titleRect;
    Rect m_closeRect;
    Rect m_submitRect;
    Rect m_hintRect;
    Rect m_telLabelRect;
    Rect m_emailLabelRect;
    Rect m_telEditorRect;
    Rect m_emailEditorRect;
    
    SexyString m_title;
    SexyString m_hint;
    SexyString m_labelTel;
    SexyString m_labelEmail;
    SexyString m_editTel;
    SexyString m_editEmail;
    SexyString m_orgEditTel;
    SexyString m_orgEditEmail;
    
    PVZ2UIEditWidget* m_telEditor = nullptr;
    PVZ2UIEditWidget* m_emailEditor = nullptr;
    
    PVZ2UIButton* m_submit = nullptr;
    PVZ2UIButton* m_cancel = nullptr;
};

class StoneLotteryConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(StoneLotteryConfig, RtObject, RtClass);
	StoneLotteryConfig() {}
    
public:
    int Period = 0;
    int OncePay = 0;
	int TotalChance = 0;
    int LeftChance = 0;
	bool IsFirstToLottery = false;
    std::vector<LotteryBonus> Bonus;
	int activityId = 0;
};

namespace Message
{
    void NotifyBonusClosed();
    void StartLottery();
}

#endif /* GeilivableLottery_h */
