#ifndef UIADSLOTTERY_H
#define UIADSLOTTERY_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "EffectAnim_UIAnim.h"
#include "EASquared.h"

struct AdsLotteryItemInfo
{
    int Index;
    int ItemID;
    int Amount;
};

enum AdsLotteryState
{
    AdsLS_Idle,
	AdsLS_Lotterying,
	AdsLS_Result,
};

class AdsLotteryBonusUI : public PopingWidget, public ButtonListener
{
public:
	AdsLotteryBonusUI();
    ~AdsLotteryBonusUI();
    
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
    std::vector<class UIRewardFrameSelect*> m_vecBonus;

    EffectAnim_UIAnim       m_openAnimRig;
    EffectAnim_UIAnim       m_backAnimRig;
};


class AdsLotteryPanel: public Widget 
{
public:
	AdsLotteryPanel();
	virtual ~AdsLotteryPanel();
 	virtual void Update() override;
    virtual void Resize(const Rect& theRect) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;

	void InitView(const std::vector<LotteryBonus>& i_bonus);
	void StartLottery(const LotteryBonus& i_bonus);

	void ShowBonusUI();
	void CloseBonusUI();
	void ShowLotteryEffect(const std::string& i_animLabel);

protected:
	bool m_bonusShown;
	AdsLotteryBonusUI* m_lotteryBonusUI = nullptr;
	std::vector<AdsLotteryItemInfo> m_vecAdsLotteryItemInfos;

	int m_bonusIndex = 0;
    int m_selectIndex = -1;
	float m_speed = 0.f;
	int m_currentStep = 0;
    int m_speedUpEndStep = 0;
    int m_speedDownEndStep = 0;
    int m_rollingEndStep = 0;
	pvztime_t m_nextItemTime = 0.f;
	EffectAnim_UIAnim m_bonusEffect;
	AdsLotteryState m_state = AdsLS_Idle;
	LotteryBonus m_bonus;
	
	void UpdateSelectFrame();
    void StartNextLoop();
	void InitSteps();
	void ShowBonus();
	bool AlmostThere();
	void SelectNext();
	bool CanSelectNext();
	bool TryToSelectNext();

	void DrawSelectFrame(Graphics* i_g, const Rect i_rect);
	SexyVector2 GetLotteryItemPos(int index);
	float GetItemW();
	float GetItemH();
};


class UIAdsLottery :public UISingletonDialog<UIAdsLottery> 
{
public:
    UIAdsLottery();
	virtual ~UIAdsLottery();
	virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "UIAdsLottery"; }
	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void Update() override;
	virtual void ButtonDepress(int i_id) override;

	void InitView();
	void StartLottery();
	void UpdateTimerLabel();
	void CloseBonusUI();
	void onAdsFinish(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);

private: 
    //主panel
    AdsLotteryPanel* m_adsLotteryPanel;
	int m_lastTimes;
	bool m_timeUp;
	bool m_buttonLock;
};

#endif