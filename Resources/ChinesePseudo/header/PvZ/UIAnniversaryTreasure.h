#ifndef UIANNIVERSARYTREASURE_H
#define UIANNIVERSARYTREASURE_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "Singleton.h"
#include "EffectAnim_UIAnim.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "Image.h"


#pragma mark - AnniversaryTreasureData

struct AnniversaryTreasureReward
{
    int ItemID;
    int Quantity;
    int Obtained;
};

class AnniversaryTreasureData : public INetworkData
{
public:
	RT_CLASS_DEFINE(AnniversaryTreasureData, INetworkData, RtClass);

    std::vector<int>                            VaseStateList;
    std::vector<AnniversaryTreasureReward>      RewardList;
    std::vector<AnniversaryTreasureReward>      Jackpot;
    std::vector<int>                            TreasureNeed;
    int                                         LimitTimes;
};

class AnniversaryTreasureVaseData : public INetworkData
{
public:
	RT_CLASS_DEFINE(AnniversaryTreasureVaseData, INetworkData, RtClass);

    std::vector<AnniversaryTreasureReward>      VaseList;
    std::vector<AnniversaryTreasureReward>      RewardList;
    std::vector<AnniversaryTreasureReward>      JackPotList;
    int                                         VaseIndex;
    int                                         ConsumeGems;
};


#pragma mark - HappyVaseAnimWidget

enum AnniversaryTreasureVaseEnum
{
    AnniversaryTreasureVase_Invalid = -1,
    AnniversaryTreasureVase_Droping,
    AnniversaryTreasureVase_Normal,
    AnniversaryTreasureVase_Breaking,
    AnniversaryTreasureVase_Broken,
};

class AnniversaryTreasureVaseWidget : public Widget
{
public:
    AnniversaryTreasureVaseWidget();
    virtual ~AnniversaryTreasureVaseWidget();

    virtual void Update() override;
    virtual void Draw(Graphics* i_g) override;

    void Init(int i_index, bool i_isBroken);
    bool IsBroken();
    void StartBreak();
    void OnAnimFinish(const std::string& i_animLabel);
    void Respawn(float i_delay = 0);

private:
    int m_index;
    float m_delay;
    AnniversaryTreasureVaseEnum m_state;
    EffectAnim_UIAnim m_vaseEffect;
};


#pragma mark - AnniversaryTreasureRewardWidget

class AnniversaryTreasureRewardWidget : public Widget
{
public:
    AnniversaryTreasureRewardWidget();
    virtual ~AnniversaryTreasureRewardWidget();

    virtual void Update() override;
    virtual void Draw(Graphics* i_g) override;
    virtual void TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void TouchEnded( const Sexy::Touch& i_touch ) override;

    void Init(int i_index, AnniversaryTreasureReward i_data);
    void SetObtain(bool i_flag);

    void ShowBonus();

private:
    void ShowBonusFinish(const std::string& i_animLabel);

    int m_type;
    int m_index;
    bool m_obtained;
    ImagePtr m_image;
    SexyString m_quantity;
    SexyString m_description;
    EffectAnim_UIAnim m_rewardEffect;
    AnniversaryTreasureReward m_data;    
    class StoneLotteryItemTipUI* m_tipUI;
};


#pragma mark - AnniversaryTreasureJackPotImage

class AnniversaryTreasureJackPotImage : public Widget
{
public:
    AnniversaryTreasureJackPotImage();
    virtual void Draw(Graphics* i_g) override;
    virtual void TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void TouchEnded( const Sexy::Touch& i_touch ) override;

    void InitBonus(const std::pair<int,int>& i_bonus);
private:
    SexyString m_description;
    class StoneLotteryItemTipUI* m_tipUI;
    std::pair<int,int> m_bonus;
};


#pragma mark - AnniversaryTreasureJackPotWidget

class AnniversaryTreasureJackPotWidget : public PopingWidget, public ButtonListener
{
public:
	AnniversaryTreasureJackPotWidget();
    ~AnniversaryTreasureJackPotWidget();

    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;

    void InitBonus(const std::pair<int,int>& i_bonus);

private:
    void InitShiningAnims();

    ImagePtr                m_pieceImg;
    ImagePtr                m_rareImg;
    PVZ2UIButton*           m_submit;
    std::pair<int,int>      m_bonus;
    EffectAnim_UIAnim       m_openAnimRig;
    EffectAnim_UIAnim       m_backAnimRig;
};


#pragma mark - UIAnniversaryTreasure

class UIAnniversaryTreasure : public UISingletonDialog<UIAnniversaryTreasure>
{
public:
    UIAnniversaryTreasure();
    virtual ~UIAnniversaryTreasure();
    
    bool OnCreate() override;
    void Update() override;
    std::string GetLayoutName() override { return "UIAnniversaryTreasure"; }
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;
    void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;

    void InitView(bool i_refresh = false);

    void VaseAnimFinish();
    void RewardAnimFinish();
    void JackPotAnimFinish();

    void showJackPotWidget();
    void closeJackPotWidget();

    void showDescriptionWidget();
    void closeDescriptionWidget();

    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    void lockButtons();
    void unlockButtons();

private:
    void UpdateTimer();
    void OnResultClosed();
    int GetCurrentGemCost();
    bool IsRewardObtained(int i_index);
    void BuyConfirm(class UIMessageBox* box, int buttonID);

    int m_currentPoolNumber;
    class ActivityDescriptionUI*                        m_descriptionUI;
    AnniversaryTreasureJackPotWidget*                   m_jackPotWidget;
    std::vector<AnniversaryTreasureVaseWidget*>         m_vaseWidget;
    std::vector<AnniversaryTreasureRewardWidget*>       m_rewardWidget;

    std::vector<std::pair<int,int>>                     m_vaseCache;
    std::vector<std::pair<int,std::pair<int,int>>>      m_rewardCache;
    std::vector<std::pair<int,int>>                     m_jackPotCache;
};


namespace Message
{
    void AnniversaryTreasureVaseEnd();
};

#endif