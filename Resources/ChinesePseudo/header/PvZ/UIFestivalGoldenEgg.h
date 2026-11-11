#ifndef UI_NEW_YEAR_GOLDENEGG_H
#define UI_NEW_YEAR_GOLDENEGG_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "Singleton.h"
#include "EffectAnim_UIAnim.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "Image.h"

class FestivalGoldenEggManager : public Sexy::LazySingleton<FestivalGoldenEggManager>
{
public:
    FestivalGoldenEggManager();
    void showDescriptionWidget();
    void closeDescriptionWidget();
private:
    class ActivityDescriptionUI* m_descriptionUI;
};


//303 data
class FestivalGoldenEggData : public INetworkData
{
public:
	RT_CLASS_DEFINE(FestivalGoldenEggData, INetworkData, RtClass);

    int                                         Hammer;
    std::vector<int>                            JackpotState;
    std::vector<int>                            JackpotList;
    std::vector<std::vector<S2C_BonusInfo>>     JackpotSelectList;
    std::map<std::string, int>                  TaskInfo;
    std::vector<std::vector<S2C_BonusInfo>>     BundleInfo;
    std::vector<int>                            BundleLimit;
    int                                         CanReset;

};
//V981
struct GoldenEggReward
{
    int ID;
    int Amount;
    int State;
};

class FestivalGoldenEggPrimaryData : public INetworkData
{
public:
    RT_CLASS_DEFINE(FestivalGoldenEggPrimaryData, INetworkData, RtClass);

    int                                         Hammer;
    std::vector<int>                            HammerConsume;
    std::vector<int>                            EggState;
    std::vector<GoldenEggReward>                NormalReward;
    GoldenEggReward                             JackpotReward;
    std::vector<S2C_BonusInfo>                  EggReward;
};

//UI
class UIFestivalGoldenEggEntrance : public UISingletonDialog<UIFestivalGoldenEggEntrance>
{
public:
    UIFestivalGoldenEggEntrance();
    ~UIFestivalGoldenEggEntrance();

    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIGoldenEggEntrance"; }
    void ButtonDepress(int i_id) override;
private:
    void RefreshData();
    void ResetConfirm(class UIMessageBox* box, int buttonID);
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    bool m_thisRequest;
    FestivalGoldenEggData m_data;
};

class UIFestivalGoldenEggSelect : public UISingletonDialog<UIFestivalGoldenEggSelect>
{
public:
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIGoldenEggSelect"; }
    void ButtonDepress(int i_id) override;

    void Init(int i_index);
private:
    int m_index;
    FestivalGoldenEggData m_data;
};


class GoldenEggAnimWidget : public Widget
{
public:
    enum GoldenEggEnum
    {
        GoldenEgg_Invalid = -1,
        GoldenEgg_Normal,
        GoldenEgg_Breaking,
        GoldenEgg_Broken,
    };
public:
    GoldenEggAnimWidget();
    virtual ~GoldenEggAnimWidget();

    virtual void Update() override;
    virtual void Draw(Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void Init(int i_majorIndex, int i_eggIndex, bool i_isBroken);
    bool IsBroken();
    bool IsBreaking();
    void StartBreak();
    void OnBroken(const std::string& i_animLabel);
    void BreakConfirm(class UIMessageBox* box, int buttonID);

private:
    int m_touchID;
    int m_primaryIndex;
    int m_eggIndex;

    GoldenEggEnum m_state;
    EffectAnim_UIAnim m_eggEffect;
    std::vector<std::pair<int,int>> m_rewards;
};


class GeneralTask;
class GoldenEggTaskWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    RT_CLASS_DEFINE(GoldenEggTaskWidget, Sexy::Widget, RtClass);

    GoldenEggTaskWidget();
    virtual ~GoldenEggTaskWidget();

    //Only for Cheat
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;

    virtual void InitTask(GeneralTask* i_task);

protected:
    void UpdateButtonState();
    void RequestReward();

    Sexy::Image* m_iBackground;
    SexyString m_strName;
    Sexy::Rect m_rName;
    Sexy::Rect m_rReward;
    SexyString strProgress;
    Sexy::Rect m_rProgress;
    Sexy::Rect m_rBanner;
    Sexy::Rect m_rButton;
    PVZ2UIButton* m_btnButton;
    GeneralTask* m_pTask;
    int32 m_iTouch;
    int m_rewardNum;
};


class GoldenEggBundleWidget : public Widget, public Sexy::ButtonListener
{
public:
    GoldenEggBundleWidget();
    ~GoldenEggBundleWidget();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void Init(int i_index, int i_limit);
    void SetData(int i_gem, int i_hammer);
    void OnBuyGoldenEgg(int i_index);

private:
    int m_index;
    int m_limit;
    int m_gemNum;
    int m_hammerNum;
    class PVZ2UIButton* m_buy;
};

class UIFestivalGoldenEgg : public UISingletonDialog<UIFestivalGoldenEgg>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
    UIFestivalGoldenEgg();
    ~UIFestivalGoldenEgg();
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIGoldenEgg"; }
    void ButtonDepress(int i_id) override;
    void Draw(Graphics* i_g) override;
    void Update() override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    void TabSelectionChanged(int tabID) override;

    void Init(int i_index);
    void InitEgg();
    void InitTask();
    void InitBundle();
public:
    int GetHammerRequire();
    void SetCurrentHammer(int i_hammer);
    int GetCurrentHammer();
    bool IsLock();
    void Lock();
    void Unlock();
    void RewardGot(int i_id, int i_amount);
protected:
    bool m_lock;
    int m_index;
    int m_currentHammer;
    FestivalGoldenEggData m_data;
    FestivalGoldenEggPrimaryData m_primaryData;
    std::vector<GoldenEggAnimWidget*> m_animVector;
    std::vector<class HappyVaseDisplayItem*> m_rewardVector;
};



#endif