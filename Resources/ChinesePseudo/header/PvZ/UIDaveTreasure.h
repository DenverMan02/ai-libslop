#ifndef UIDAVETREASURE_H
#define UIDAVETREASURE_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "EffectAnim_UIAnim.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "Image.h"

class DaveTask;

struct DaveTreasureIntegralReward
{
    int Index;
    int Quentity;
    int Received;
};

class DaveTreasureTaskWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    RT_CLASS_DEFINE(DaveTreasureTaskWidget, Sexy::Widget, RtClass);

    DaveTreasureTaskWidget();
    virtual ~DaveTreasureTaskWidget();

    //For Cheat
    virtual void            TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void            TouchEnded( const Sexy::Touch& i_touch ) override;

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;

    void SetTask(DaveTask* i_task);
    void InitView();
    void UpdateButtonState();
protected:
    Sexy::Image* GetTaskRewardImage(int i_id);
    void RequestReward();
    void RequestPennyReward();

    Sexy::Image* m_iBackground;
    SexyString m_strName;
    Rect m_rName;
    Rect m_rReward;
    SexyString strProgress;
    Rect m_rProgress;
    Rect m_rBanner;
    Rect m_rButton;
    PVZ2UIButton* m_btnButton;
    DaveTask* m_pTask;
    int32 m_iTouch;
};

class DaveTreasureRewardButton : public Widget
{
public:
    DaveTreasureRewardButton();
    virtual ~DaveTreasureRewardButton();
public:
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void            TouchEnded( const Sexy::Touch& i_touch ) override;

    void                    SetData(bool isNormal, int index);
    virtual void            RequestReward();
    void                    UpdateButtonState();
protected:
    bool m_isNormal;
    int m_index;
    int32 m_iTouch;
};

class PennyGuideRewardButton : public Widget
{
public:
    PennyGuideRewardButton();
    virtual ~PennyGuideRewardButton();
public:
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void            TouchEnded( const Sexy::Touch& i_touch ) override;

    void                    SetData(bool isNormal, int index);
    virtual void            RequestReward();
    void                    UpdateButtonState();
    void                    ObatinPennyPrivilege();
protected:
    bool m_isNormal;
    int m_index;
    int32 m_iTouch;
};

class DaveTreasureDisplayWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    DaveTreasureDisplayWidget();
    virtual ~DaveTreasureDisplayWidget();

    void InitView(int i_index, bool i_pennyGuide = false);

    void Update() override;
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;

    void OnNotifyBillingReward(bool i_success, const S2C_BillingReward* pData);
    void ObatinPennyPrivilege();
private:
    bool m_isPennyGuide;
    int m_index;
    Rect m_rDescription;
    PVZ2UIButton* m_btnBuy;
    Sexy::Image* m_image;
    int m_cost;// tga log
};

class DaveTreasureScrollWidget : public PVZ2UIScrollingWidget
{
public:
    DaveTreasureScrollWidget(Sexy::ScrollWidgetListener* i_listener);
    
    void disableManualScroll() { mScrollPractical = ScrollWidget::SCROLL_DISABLED; }
};

class DaveTreasureDotWidget : public Sexy::Widget
{
public:
    DaveTreasureDotWidget(int dotsCount);
    void Draw(Graphics* i_g) override;
    void SetDotIndex(int i_index) { m_dotIndex = i_index; }
    
private:
    int m_dotIndex;
    int m_dotsCount;  
};

class DaveTreasureBonusUI : public PopingWidget, public ButtonListener
{
public:
	DaveTreasureBonusUI();
    ~DaveTreasureBonusUI();
    
    virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void HideAllButtonAndAnims() override;
    virtual void RecoverAllButtonAndAnims() override;
    
    void InitView();
    void SetAward(const std::vector<LotteryBonus>& i_award);
    void SetChestAward(const std::vector<LotteryBonus>& i_award);
    Sexy::Image* GetRewardImage(int id);

private:
    void InitShiningAnims();

private:
    std::vector<LotteryBonus>           m_Award;
    std::vector<LotteryBonus>           m_ChestAward;
    bool                                m_IsDrawBonus;
    Rect                                m_bonusRect;
    Rect                                m_rewardRect;
    Rect                                m_titleImgRect;
    Rect                                m_titleRect;
    SexyString                          m_title;
    Rect                                m_submitRect;
    PVZ2UIButton*                       m_submit;
    EffectAnim_UIAnim                   m_openAnimRig;
    EffectAnim_UIAnim                   m_backAnimRig;
};

class DaveTreasureRewardWidget : public Sexy::Widget
{
public:
    DaveTreasureRewardWidget();
    virtual void TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void TouchEnded( const Sexy::Touch& i_touch ) override;
    virtual void Draw(Graphics* i_g) override;
    void SetReawrd(const DaveTreasureIntegralReward& i_reward);
private:
    Sexy::Image*        m_image;
    SexyString          m_des;
    int                 m_bonusId;
    int                 m_rewardType;
    std::string         m_bonusName;
    Sexy::Rect          m_iconRect;
    int32               m_iTouch;
    SexyString          m_description;
    class StoneLotteryItemTipUI* m_tipUI;
};

class UIDaveTreasure : public UISingletonDialog<UIDaveTreasure>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
    UIDaveTreasure();
    virtual ~UIDaveTreasure();
    
    bool OnCreate() override;
    void Update() override;
    std::string GetLayoutName() override { return "UIDaveTreasure"; }
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;
    
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();

    void OnObtainReward(bool is_normal, int i_index);
    void OnObtainIntegral(int i_add);
    void OnNotifyBillingReward(bool i_success, const S2C_BillingReward* pData);

    int GetCurrentIntegral() { return m_currentIntegral; }
    int GetCurrentProcessIndex();

private:
    void UpdateTimer();
    void UpdateIntegral();
    void InitReward();
    void InitTasks();
    void SwitchTaskWidget(int i_tab);
    void RefreshProgressBar();
private:
    //Tab1s
    pvztime_t m_autoScrollTimer;
    int m_autoScrollCounter;
    int m_totalBundleCount;
    DaveTreasureDotWidget* m_dotWidget;
    DaveTreasureScrollWidget* m_scrollBannerWidget;
    //Tab2s
    int m_currentTabTask;
private:
    int m_currentIntegral;
    int m_nextRewardIndex;
};


class UIPennyGuide : public UISingletonDialog<UIPennyGuide>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
    UIPennyGuide();
    virtual ~UIPennyGuide();
    
    bool OnCreate() override;
    void Update() override;
    std::string GetLayoutName() override { return "UIPennyGuide"; }
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;
    
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();

    void OnObtainReward(bool is_normal, int i_index);
    void OnObtainIntegral(int i_add);
    void OnNotifyBillingReward(bool i_success, const S2C_BillingReward* pData);

    int GetCurrentIntegral() { return m_currentIntegral; }
    int GetCurrentProcessIndex();

private:
    void UpdateTimer();
    void UpdateIntegral();
    void InitReward();
    void InitTasks();
    void SwitchTaskWidget(int i_tab);
    void RefreshProgressBar();
private:
    //Tab1s
    pvztime_t m_autoScrollTimer;
    int m_autoScrollCounter;
    int m_totalBundleCount;
    DaveTreasureDotWidget* m_dotWidget;
    DaveTreasureScrollWidget* m_scrollBannerWidget;
    //Tab2s
    int m_currentTabTask;
private:
    int m_currentIntegral;
    int m_nextRewardIndex;
};


class DaveTreasureData : public INetworkData
{
public:
	RT_CLASS_DEFINE(DaveTreasureData, INetworkData, RtClass);

    bool                                        Privilege;
    int                                         Integral;
    std::vector<DaveTreasureIntegralReward>     NormalReward;
    std::vector<DaveTreasureIntegralReward>     HighReward;
    std::vector<int>                            DayFinishList;
    std::vector<int>                            WeekFinishList;
    std::vector<int>                            MonthFinishList;
    std::vector<int>                            BlackList;
    int                                         ThemePlantID;
    int                                         Version;
};

class DaveTreasureDataManager : public LazySingleton<DaveTreasureDataManager>
{
public:
    DaveTreasureDataManager();
    ~DaveTreasureDataManager();

    void RefreshData();
    bool HasPrivilege();
    bool HasAnyNotReceivedReward();
    bool HasPennyPrivilege();
    DaveTreasureIntegralReward GetRewardInfo(bool isNormal, int index);
    DaveTreasureIntegralReward GetPennyRewardInfo(bool isNormal, int index);
    void ShowBonus(const std::vector<LotteryBonus>& reward, const std::vector<LotteryBonus>& chestReward);
    void CloseBonus();

private:
    DaveTreasureBonusUI* m_bonusUI;
};

#define gDaveTreasureDataManager (DaveTreasureDataManager::GetInstancePtr())

namespace Message
{
    void ObatinPrivilege();
    void ObatinPennyPrivilege();
    void ObtainPennyGuideIntegral(int i_num);
}

#endif