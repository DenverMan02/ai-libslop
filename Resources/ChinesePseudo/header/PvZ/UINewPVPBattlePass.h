#ifndef UINewPVPBattlePass_H_
#define UINewPVPBattlePass_H_

#include "NetworkData.h"
#include "UISingletonDialog.h"
#include "RepeatUIComponent.h"
#include "EffectAnim_UIAnim.h"
#include "NewPVPGame.h"


struct NewPVPBattlePassAward
{
    NewPVPBattlePassAward()
    :GemStone(0),
    PoolID(0),
    Obtained(false)
    {

    }

    std::vector<S2C_BonusInfo> Content;
    int GemStone;
    int PoolID;
    std::vector<S2C_BonusInfo> PoolList;
    int Obtained;
};

struct NewPVPBattlePassBundle
{
    NewPVPBattlePassBundle()
    :Experience(0)
    {

    }

    int Experience;
};

struct NewPVPBattlePassRankData
{
    int Rank = 0;
    std::string Name;
    int HeadShotID = 0;
    int Gem = 0;
    int IsGet = 0;
};

struct NewPVPBattlePassPrivilegeAward
{
    NewPVPBattlePassPrivilegeAward()
    :AwardId(0),
    Quantities(0)
    {

    }

    int AwardId;
    int Quantities;
};

struct NewPVPTaskDataInfo
{
    NewPVPTaskDataInfo()
    :Exp(0),
    IsGet(0)
    {

    }
    int Exp;
    bool IsGet;
};

class NewPVPBattlePassData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NewPVPBattlePassData, INetworkData, RtClass);

    NewPVPBattlePassData()
    :Level(0),
    Experience(0),
    Integral(0),
    Privilege(0),
    ExperienceCeiling(0),
    ExperienceCeilingSwitch(false),
    NowWeekIndex(0),
    CurrentDraw(0),
    Version(0),
    Settlement(0),
    GiftPoolGem(0),
    GiftPoolRank(0),
    LuckyPoolGem(0),
    LuckyPoolRank(0)
    {

    }

    int                                         Level;
    int                                         Experience;
    int                                         Integral;
    int                                         Privilege;
    int											ExperienceCeiling;
    bool										ExperienceCeilingSwitch;
    int											NowWeekIndex;

    std::vector<NewPVPBattlePassAward>               NormalAward;
    std::vector<NewPVPBattlePassAward>               PrivilegeAward;
    std::vector<std::vector<NewPVPBattlePassBundle>> BundleList;
    std::vector<int>                            BundleLimit;

    std::vector<NewPVPBattlePassAward>               LottryAward;
    std::vector<NewPVPBattlePassPrivilegeAward> NewPrivilegeAward;
    int                                         CurrentDraw;
    std::vector<int>                            MatRequire;

//    std::vector<std::map<std::string, int>>     DayTaskInfo;
    std::map<std::string, int>    				DayTaskInfo;
    std::map<std::string, NewPVPTaskDataInfo>   DayTaskDesc;
    std::vector<std::map<std::string, int>>		WeekTaskInfo;
    std::vector<std::map<std::string RT_COMMA NewPVPTaskDataInfo>>   WeekTaskDesc;
    int                                         Version;
    int                                         Settlement;

    int GiftPoolGem;
    int GiftPoolRank;
    NewPVPBattlePassRankData GiftPoolRankReward;
    std::vector<std::vector<NewPVPBattlePassRankData>> GiftPoolRankList;

    int LuckyPoolGem;
    int LuckyPoolRank;
    NewPVPBattlePassRankData LuckyPoolReward;
    std::vector<std::vector<NewPVPBattlePassRankData>> LuckyPoolList;
};

class NewPVPBattlePassRewardData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NewPVPBattlePassRewardData, INetworkData, RtClass);

    int AwardIndex;
    std::vector<S2C_BonusInfo> RewardList;

};


class UINewPVPBattlePassIntroduction : public UISingletonDialog<UINewPVPBattlePassIntroduction>
{
public:
    bool OnCreate() override;
    virtual void Update() override;
    virtual std::string GetLayoutName() override { return "UIBattleOrderIntroduction"; }
    virtual void ButtonDepress(int i_id) override;
};

class NewPVPBattlePassBundleWidget : public TemplateBundleWidget
{
public:
    NewPVPBattlePassBundleWidget();
    virtual ~NewPVPBattlePassBundleWidget();

    virtual void Init(int i_index) override;
    virtual void ButtonDepress(int i_id) override;
    // void SetChestNum(int num) { m_chestNum = num; }
    void ShowChest();

protected:
    virtual void UpdateButtonState() override;
    virtual void DrawBundleCenter(Sexy::Graphics* i_g) override;
    virtual void DrawBundleRewards(Sexy::Graphics* i_g) override;
    virtual void DrawBundleLimit(Sexy::Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;

    virtual void OnPurchaseButtonDepress() override;
    void OnBuyExp(int i_index); 
    void OnExtrarewards(const std::vector<S2C_BonusInfo>& bonuslist, int i_index);

private:
    int m_leastNumber;
    int m_chestNum = 0;
    // class PVZ2UIButton* m_preview;
};

class UINewPVPBattlePassBundle : public UISingletonDialog<UINewPVPBattlePassBundle>, public Sexy::ScrollWidgetListener
{
public:
    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "UIBattleOrderBundle"; }
    virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView(const std::vector<std::vector<NewPVPBattlePassBundle>>& i_budleList, const std::vector<int>& i_bundleLimit);
};


class UINewPVPBattlePassPrivilege : public UISingletonDialog<UINewPVPBattlePassPrivilege>
{
public:
    bool OnCreate() override;
    virtual std::string GetLayoutName() override; 
    virtual void ButtonDepress(int i_id) override;
};

class UINewPVPBattlePassPrivilegeRewardDisplay : public UISingletonDialog<UINewPVPBattlePassPrivilegeRewardDisplay>
{
public:
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UINewPVPRewardDisplay"; }
    void ButtonDepress(int i_id) override;
    void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    void InitView(const std::vector<S2C_BonusInfo>& i_bonus);
private:
    bool m_isChip = false;
    std::vector<S2C_BonusInfo> m_bonus;
};


class UINewPVPBattlePass : public UISingletonDialog<UINewPVPBattlePass>, public Sexy::ScrollWidgetListener
{
public:
	UINewPVPBattlePass();
    ~UINewPVPBattlePass();

    bool OnCreate() override;
    std::string GetLayoutName() override { return "UINewPVPBattlePass"; }
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    bool CheckCanSign();
    void InitView();

    int GetCurrentLevel();
    int GetCurrentExp();
    int GetCurrentDraw();
    int GetCurrentIntegral();
    bool HasPrivilege();
    void AddIntegral(int i_num);

    void AddExperience(int i_exp);
    void ShowGetExperience(int i_exp);
    void BuyBundleIndex(int i_index);
    int GetBundleExperience(int i_index);
    std::string GetBundleSku(int i_index);

    void AddDrawTimes();
    int GetLastGemCost();
    int GetCurrentGemCost();
    bool CanLottery();
    bool IsLotteryMax();

    void LockButton();
    void UnlockButton();

private:
    void InitReward();
    void InitLottery();
    void InitTasks();
//    void InitGift();
//    void InitLucky();
//
    void FillPreview(Widget* i_widget, NewPVPBattlePassAward& i_data);
    void CheckLotteryState();
//
    void SwitchTaskWidget(int i_tab);
//    void RefreshProgressBar();
//
    void OnNewPVPBattlePassPrivilege(const std::vector<S2C_BonusInfo>& i_bonus);
    void ShowRewardOfPrivilege(const std::vector<S2C_BonusInfo>& i_bonus);
    void SetHasdPrivilege(bool i_flag);
    void UpdateExpOfTask();
//
    void showDescriptionWidget();
    void closeDescriptionWidget();
//
//    void GiftOrLuckyReward(int i_type);
//
private:
    void InitTaskType();

    int m_lastPreviewIndex;
    class PVZ2UIScrollingWidget* m_orderScrollWidget;
    class NewPVPBattlePassLotteryPanel* m_lotteryPanel;
    std::vector<std::pair<int, int>> m_stepScrollOffset;
    NewPVPBattlePassData m_activityData;
    class ActivityDescriptionUI* m_descriptionUI;

////
    std::vector<Widget*> m_taskTypeButtons = {};
    std::vector<Widget*> m_taskTypeCursors = {};

    UIWidgetText* m_dayTaskNumText = nullptr;
    int m_taskTabIndex = 0;
    time_t m_activityStartTime;
};


class NewPVPBattlePassItemWidget : public Widget, public Sexy::ButtonListener
{
public:
    NewPVPBattlePassItemWidget();
    ~NewPVPBattlePassItemWidget();

    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void Update() override;

    void InitData(const NewPVPBattlePassAward& i_data, int i_index, bool i_isNormal);
    bool GetAWarded() { return m_awarded; }

private:
    void SetAwarded();
    void CheckCanReceive();
    void SelectAndRequest();
    void DetermineSelect(class UIMessageBox* box, int buttonID);
    void RequestReward(int i_boxIndex);


    int m_index;
    bool m_isNormal;
    bool m_awarded;
    NewPVPBattlePassAward m_data;
    std::vector<class UIRewardFrameSelect*> m_rewardFrameList;
    std::vector<class PVZ2UIButton*> m_receiveBtnList;
};


enum NewPVPBattlePassLotteryState
{
    NewPVPBattlePassLS_Idle,
	NewPVPBattlePassLS_Lotterying,
	NewPVPBattlePassLS_Result,
};

class NewPVPBattlePassLotteryPanel: public UISingletonDialog<NewPVPBattlePassLotteryPanel>
{
    friend class UINewPVPBattlePass;
public:
	NewPVPBattlePassLotteryPanel();
	virtual ~NewPVPBattlePassLotteryPanel();

    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "BattleOrderLotteryPanel"; }
 	virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

	void InitView(const std::vector<NewPVPBattlePassAward>& i_bonus);
	void StartLottery(int i_index);

    void RequestLottery();

protected:
    void LotteryEffect();
	void LotteryEffectFinish(const std::string& i_animLabel);
    void ShowBonusUI();
	void CloseBonusUI();

    void DetermineSelect(class UIMessageBox* box, int buttonID);
    void RequestChest(int i_index);

	bool m_bonusShown;
	class PopingBonusUI* m_lotteryBonusUI = nullptr;
	std::vector<NewPVPBattlePassAward> m_bonusInfoVec;;
    std::vector<class UIRewardFrameSelect*> m_frameVec;

	int m_bonusIndex = 0;
    int m_selectIndex = -1;
	float m_speed = 0.f;
	int m_currentStep = 0;
    int m_speedUpEndStep = 0;
    int m_speedDownEndStep = 0;
    int m_rollingEndStep = 0;
	pvztime_t m_nextItemTime = 0.f;
	EffectAnim_UIAnim m_bonusEffect;
	NewPVPBattlePassLotteryState m_state = NewPVPBattlePassLS_Idle;

	void UpdateSelectFrame();
    void StartNextLoop();
	void InitSteps();
	void ShowBonus();
	bool AlmostThere();
	void SelectNext();
	bool CanSelectNext();
	bool TryToSelectNext();

};

class NewPVPBattlePassTaskRewardDataMsg : public INetworkData
{
	RT_CLASS_DEFINE(NewPVPBattlePassTaskRewardDataMsg, INetworkData, RtClass);

	int plevel;
	int ev;
	std::vector<S2C_BonusInfo> bl;
};

class NewPVPBattlePassTaskWidget : public TemplateTaskWidget
{
public:
    RT_CLASS_DEFINE(NewPVPBattlePassTaskWidget, Sexy::Widget, RtClass);

    virtual void InitTask(GeneralTask* i_task) override;

    void SetWeekIndex(int i_index) { m_weekIndex = i_index; }
    void SetChestID(int i_chestID) { m_chestID = i_chestID; }
    class GeneralTaskData* GetTaskData();
    void SetNewExp(int i_exp) { m_rewardNum = i_exp; }

protected:
    virtual void RequestReward() override;
    virtual void DrawTaskBackground(Sexy::Graphics* i_g);
    virtual void DrawRewards(Sexy::Graphics* i_g);

    int m_weekIndex = 0;
    int m_chestID = 0;
};


class NewPVPBattlePassTurnPagesItem : public Widget
{
public:
    void InitView(int i_rank, const NewPVPBattlePassRankData& i_data);
    virtual void Draw(Graphics* i_g) override;
private:
    int m_rank;
    SexyString m_name;
    NewPVPBattlePassRankData m_data;
};

class UINewPVPBattlePassTurnPagesList : public UISingletonDialog<UINewPVPBattlePassTurnPagesList>, public Sexy::ScrollWidgetListener
{
public:
    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "UITurnPages"; }
    virtual void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitData(const std::vector<NewPVPBattlePassRankData>& i_list, int i_start);
    void ChangePage(int i_index);

public:
    int m_index;
    int m_start;
    std::vector<NewPVPBattlePassRankData> m_rankData;
};



namespace Message
{
    void NewPVPBattlePassBuyPrivilege(const std::vector<S2C_BonusInfo>& i_bonus);
    void NewPVPBattlePassBuyBundle(int i_index);
    void NewPVPBattlePassExtrarewards(const std::vector<S2C_BonusInfo>& i_bonus, int i_index);
};

#endif
