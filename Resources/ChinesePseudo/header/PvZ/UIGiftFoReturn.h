#ifndef UIGiftFoReturn_H
#define UIGiftFoReturn_H

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "UIListener.h"
#include "EffectAnim_UIAnim.h"
#include "RepeatUIComponent.h"


struct GiftFoReturnSignInfo
{
    int IsBox = 0;
    std::vector<S2C_BonusInfo> SignReward;
    int Obtained = 0;
};

struct GiftFoReturnTaskInfo
{
    int UnlockDay = 0;
    std::vector<S2C_BonusInfo> TaskReward;
    int TaskId = 0;
    int Unlocked = 0;
    int Obtained = 0;
};

struct GiftFoReturnTaskRewardInfo
{
    int Condition = 0;
    std::vector<S2C_BonusInfo> Reward;
    int Obtained = 0;
};


class GiftFoReturnData : public INetworkData
{
public:
	RT_CLASS_DEFINE(GiftFoReturnData, INetworkData, RtClass);

    int CurrentDay;
    std::vector<GiftFoReturnSignInfo> DailySignData;
    int IsSigned;
    int SignedDays;

    int TaskIntegral = 0;
    std::vector<GiftFoReturnTaskInfo> TaskList;
    std::vector<GiftFoReturnTaskRewardInfo> TaskRewardList;

    std::vector<std::vector<S2C_BonusInfo>> BundleInfo;
    std::vector<int> BundleIndex;
    std::vector<int> BundleLimit;
    std::vector<int> TrialCardLimit;
    time_t RefreshTimer;

    int TaskScore;
    std::vector<S2C_BonusInfo> RewardList;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class GiftFoReturnTaskWidget : public TemplateTaskWidget
{
public:
    RT_CLASS_DEFINE(GiftFoReturnTaskWidget, Sexy::Widget, RtClass);

    virtual void InitTask(GeneralTask* i_task) override;
    virtual void DrawProgress(Sexy::Graphics* i_g) override;
    virtual void DrawRewards(Sexy::Graphics* i_g) override;
    virtual void DrawTaskBackground(Sexy::Graphics* i_g) override;

    void SetTaskData(GiftFoReturnTaskInfo i_rewardInfo);

protected:
    virtual void RequestReward() override;

    SexyString m_counterDown;
    GiftFoReturnTaskInfo m_rewardInfo;
};

class GiftFoReturnBundleWidget : public Widget, public Sexy::ButtonListener
{
public:
    GiftFoReturnBundleWidget();
    ~GiftFoReturnBundleWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView(int i_index, const std::vector<S2C_BonusInfo>& i_bundleInfo, int i_bundleIndex, int i_bundleLimit, int i_trialCardLimit);
    void RefreshInfo();

    void ObatainTrialCard();
    void OnBuyGiftFoReturn(int i_index);

private:
    int m_index;
    std::vector<S2C_BonusInfo> m_bundleInfo;
    int m_bundleIndex;
    int m_bundleLimit;
    int m_trialCardLimit;
    
    SexyString m_name;
    class PVZ2UIButton* m_trialButton;
    class PVZ2UIButton* m_bundleButton;
    class UIWidgetText* m_limitText;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class GiftFoReturnSignWidget : public Widget, public Sexy::ButtonListener
{
public:
    GiftFoReturnSignWidget();
    ~GiftFoReturnSignWidget();

    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView(int i_index, const GiftFoReturnSignInfo& i_signInfo, int i_signState);
    void RefreshView();
    void DetermineSelect(class UIMessageBox* box, int buttonID);

private:
    int m_index;
    GiftFoReturnSignInfo m_signInfo;
    int m_signState;
    SexyString m_title;
    Sexy::Rect m_titleRect;
    Sexy::Rect m_rewardRect;
    Sexy::Rect m_buttonRect;
}; 

////////////////////////////////////////////////////////////////////////////////////////////////////

class UIGiftFoReturn : public UISingletonDialog<UIGiftFoReturn>, public Sexy::ScrollWidgetListener
{
public:
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIGiftFoReturn"; }
    void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    virtual void Update() override;    

    void InitView();

    void SetIntegral(int i_integral);

    void showDescriptionWidget();
    void closeDescriptionWidget();    

    static bool GetHasTips();
    static bool s_tipsStatus;

private:
    void InitTab1();
    void InitTab2();
    void InitTab3();
    int GetSignState(int i_dayNumber);

public:
    void RefreshSign();
    void RefreshTask();
    void RefreshTaskReward();
private:
    void RequestTaskIntegralReward(int i_index);

    class ActivityDescriptionUI* m_descriptionUI = nullptr;
public:
    GiftFoReturnData m_cacheData;
};


class WorldMap_GiftFoReturnButton : public PVZ2UIButton
{
public:
    WorldMap_GiftFoReturnButton(int id, Sexy::ButtonListener* listener);

    virtual void Draw(Graphics* i_g) override;
};


enum ENUM_DISPLAY
{
    UpdateNews_Gameplay,
    UpdateNews_Plant,
    UpdateNews_Artifact,
    UpdateNews_Zombie,
    UpdateNews_Avatar
};

class UpdateNewsDisplayWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    UpdateNewsDisplayWidget();
    virtual ~UpdateNewsDisplayWidget() {}

    void InitView(int i_index);

    void Update() override;
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;
    
private:    
    Rect m_rDescription;
    PVZ2UIButton* m_btnGo;
    Sexy::Image* m_image;
    ENUM_DISPLAY m_displayType;
    int m_index;
};


class UIUpdateNews : public UISingletonDialog<UIUpdateNews>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
    UIUpdateNews() {}
    virtual ~UIUpdateNews() {}
    
    bool OnCreate() override;
    void Update() override;
    std::string GetLayoutName() override { return "UIUpdateNews"; }
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;
    
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();

private:
    void initTophalfBtn();
    void initLowhalfBtn();    

private:
    int m_autoScrollCounter{0};    
    // class DaveTreasureDotWidget* m_dotWidget;
    class DaveTreasureScrollWidget* m_scrollBannerWidget;
};

namespace Message
{
    void UpdateGiftFoReturnSignDays(int i_signDays);
}

#endif