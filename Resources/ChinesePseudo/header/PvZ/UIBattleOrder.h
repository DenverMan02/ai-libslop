#ifndef UIBattleOrder_H_
#define UIBattleOrder_H_

#include "NetworkData.h"
#include "UISingletonDialog.h"
#include "RepeatUIComponent.h"
#include "EffectAnim_UIAnim.h"


struct BattleOrderAward
{
    BattleOrderAward()
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

struct BattleOrderBundle
{
    BattleOrderBundle()
    :Experience(0)
    {

    }

    int Experience;
};

struct BattleOrderRankData
{
    int Rank = 0;
    std::string Name;
    int HeadShotID = 0;
    int Gem = 0;
    int IsGet = 0;
};

class BattleOrderData : public INetworkData
{
public:
	RT_CLASS_DEFINE(BattleOrderData, INetworkData, RtClass);

    BattleOrderData()
    :Level(0),
    Experience(0),
    Integral(0),
    Privilege(0),
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

    std::vector<BattleOrderAward>               NormalAward;    
    std::vector<BattleOrderAward>               PrivilegeAward;
    std::vector<std::vector<BattleOrderBundle>> BundleList;
    std::vector<int>                            BundleLimit;

    std::vector<BattleOrderAward>               LottryAward;
    int                                         CurrentDraw;
    std::vector<int>                            MatRequire;

    std::vector<std::map<std::string, int>>     TaskInfo;
    int                                         Version;
    int                                         Settlement;

    int GiftPoolGem;
    int GiftPoolRank;
    BattleOrderRankData GiftPoolRankReward;
    std::vector<std::vector<BattleOrderRankData>> GiftPoolRankList;

    int LuckyPoolGem;
    int LuckyPoolRank;
    BattleOrderRankData LuckyPoolReward;
    std::vector<std::vector<BattleOrderRankData>> LuckyPoolList;

    std::string                                    ThemeVersion;
    int                                            ExperienceBase = 1000;
};

class BattleOrderRewardData : public INetworkData
{
public:
	RT_CLASS_DEFINE(BattleOrderRewardData, INetworkData, RtClass);

    int AwardIndex;
    std::vector<S2C_BonusInfo> RewardList;

};


class UIBattleOrderIntroduction : public UISingletonDialog<UIBattleOrderIntroduction>
{
public:
    bool OnCreate() override;
    virtual void Update() override;
    virtual std::string GetLayoutName() override { return "UIBattleOrderIntroduction"; }
    virtual void ButtonDepress(int i_id) override;
    void CheckThemeVersion();
};

class BattleOrderBundleWidget : public TemplateBundleWidget
{
public:
    BattleOrderBundleWidget();
    virtual ~BattleOrderBundleWidget();

    virtual void Init(int i_index) override;
    
protected:
    virtual void UpdateButtonState() override;
    virtual void DrawBundleCenter(Sexy::Graphics* i_g) override;
    virtual void DrawBundleRewards(Sexy::Graphics* i_g) override;
    virtual void DrawBundleLimit(Sexy::Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;

    virtual void OnPurchaseButtonDepress() override;
    void OnBuyExp(int i_index);

    int m_leastNumber;
};

class UIBattleOrderBundle : public UISingletonDialog<UIBattleOrderBundle>, public Sexy::ScrollWidgetListener
{
public:
    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "UIBattleOrderBundle"; }
    virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView(const std::vector<std::vector<BattleOrderBundle>>& i_budleList, const std::vector<int>& i_bundleLimit);
};


class UIBattleOrderPrivilege : public UISingletonDialog<UIBattleOrderPrivilege>
{
public:
    bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "UIBattleOrderPrivilege"; }
    virtual void ButtonDepress(int i_id) override;
    void CheckThemeVersion();
};

class UIBattleOrder : public UISingletonDialog<UIBattleOrder>, public Sexy::ScrollWidgetListener
{
public:
    UIBattleOrder();
    ~UIBattleOrder();

    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIBattleOrder"; }
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

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

    void AddDrawTimes();
    int GetLastGemCost();
    int GetCurrentGemCost();
    bool CanLottery();
    bool IsLotteryMax();

    void LockButton();
    void UnlockButton();

    int GetExperienceBase();
    std::string GetThemeVersionSuffix();
    std::string GetThemeVersionSuffixUpper();
private:
    void InitReward();
    void InitLottery();
    void InitTasks();
    void InitGift();
    void InitLucky();

    void FillPreview(Widget* i_widget, BattleOrderAward& i_data);
    void CheckLotteryState();

    void SwitchTaskWidget(int i_tab);
    void RefreshProgressBar();

    void OnBuyBattleOrderPrivilege();
    void SetHasdPrivilege(bool i_flag);

    void showDescriptionWidget();
    void closeDescriptionWidget();

    void GiftOrLuckyReward(int i_type);

    void CheckThemeVersion();
private:
    int m_lastPreviewIndex;
    class PVZ2UIScrollingWidget* m_orderScrollWidget;
    class BattleOrderLotteryPanel* m_lotteryPanel;
    std::vector<std::pair<int, int>> m_stepScrollOffset;
    BattleOrderData m_activityData;
    class ActivityDescriptionUI* m_descriptionUI;
};


class BattleOrderItemWidget : public Widget, public Sexy::ButtonListener
{
public:
    BattleOrderItemWidget();
    ~BattleOrderItemWidget();

    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void Update() override;

    void InitData(const BattleOrderAward& i_data, int i_index, bool i_isNormal);

private:
    void SetAwarded();
    void CheckCanReceive();
    void SelectAndRequest();
    void DetermineSelect(class UIMessageBox* box, int buttonID);
    void RequestReward(int i_boxIndex);


    int m_index;
    bool m_isNormal;
    bool m_awarded;
    BattleOrderAward m_data;
    std::vector<class UIRewardFrameSelect*> m_rewardFrameList;
    std::vector<class PVZ2UIButton*> m_receiveBtnList;
};


enum BattleOrderLotteryState
{
    BattleOrderLS_Idle,
	BattleOrderLS_Lotterying,
	BattleOrderLS_Result,
};

class BattleOrderLotteryPanel: public UISingletonDialog<BattleOrderLotteryPanel> 
{
    friend class UIBattleOrder;
public:
	BattleOrderLotteryPanel();
	virtual ~BattleOrderLotteryPanel();

    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "BattleOrderLotteryPanel"; }
 	virtual void Update() override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

	void InitView(const std::vector<BattleOrderAward>& i_bonus);
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
	std::vector<BattleOrderAward> m_bonusInfoVec;;
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
	BattleOrderLotteryState m_state = BattleOrderLS_Idle;
	
	void UpdateSelectFrame();
    void StartNextLoop();
	void InitSteps();
	void ShowBonus();
	bool AlmostThere();
	void SelectNext();
	bool CanSelectNext();
	bool TryToSelectNext();

};


class BattleOrderTaskWidget : public TemplateTaskWidget
{
public:
    RT_CLASS_DEFINE(BattleOrderTaskWidget, Sexy::Widget, RtClass);

    virtual void InitTask(GeneralTask* i_task) override;

protected:
    virtual void RequestReward() override;
};


class BattleOrderTurnPagesItem : public Widget
{
public:
    void InitView(int i_rank, const BattleOrderRankData& i_data);
    virtual void Draw(Graphics* i_g) override;
private:
    int m_rank;
    SexyString m_name;
    BattleOrderRankData m_data;
};

class UIBattleOrderTurnPagesList : public UISingletonDialog<UIBattleOrderTurnPagesList>, public Sexy::ScrollWidgetListener
{
public:
    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "UITurnPages"; }
    virtual void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitData(const std::vector<BattleOrderRankData>& i_list, int i_start);
    void ChangePage(int i_index);

public:
    int m_index;
    int m_start;
    std::vector<BattleOrderRankData> m_rankData;
};



namespace Message
{
    void BuyBattleOrderPrivilege();
    void BuyBattleOrderBundle(int i_index);
};

#endif