#ifndef UI_ARBOR_DAY_H
#define UI_ARBOR_DAY_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "Singleton.h"
#include "EffectAnim_UIAnim.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "Image.h"
#include "RepeatUIComponent.h"
#include "functional"
#include "UICarnival.h"

struct ArborDayBonus
{
    int Valid;
    int ID;
    int Amount;
};

struct ArborPresentData
{
	int GemPrice;
	std::vector<S2C_BonusInfo> BonusList;
	int LeftTimes;
};

class ArborDayGemBuyReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(ArborDayGemBuyReward, INetworkData, RtClass);

    std::vector<S2C_BonusInfo> BonusList;
    int Gem;
};

class ArborDayData : public INetworkData
{
public:
	RT_CLASS_DEFINE(ArborDayData, INetworkData, RtClass);

    int                                         Kettle;
    int                                         NextNeed;
    int                                         Process;
    int                                         PlayerProcess;
    int                                         PlantTree;
    std::vector<ArborDayBonus>                  BonusList;
    std::vector<ArborPresentData>               PresentList;

    std::vector<CarnivalRewardData>				TotalBuyReward;
    std::vector<CarnivalRewardData>				BuyReward;

    int                                         RefreshPrice;
    S2C_BonusInfo                               HarvestReward;


    std::map<std::string, int>                  TaskInfo;
    std::vector<std::vector<S2C_BonusInfo>>     BundleInfo;
    std::vector<int>                            BundleLimit;
};

class ArborDayHarvest : public Widget, public ButtonListener
{
public:
    ArborDayHarvest();
    virtual ~ArborDayHarvest();

    virtual void Draw(Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void ButtonDepress(int i_id) override;

    void Init(int i_index, const Rect& i_rect);

private:
    void RequestHarvest(int i_type);
    int m_touchId;
    int m_index;
    Rect m_rect;
    std::function<void()> m_harvest;
    std::function<void()> m_refresh;
};

class ArborDayBubbleWidget : public Widget
{
public:
    ArborDayBubbleWidget(int i_index);
    ~ArborDayBubbleWidget();

    virtual void Draw(Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void SetData(int i_itemId, int i_amount);
private:
    int m_touchId;
    int m_index;
    int m_itemId;
    int m_amount;
};

class ArborDayTaskWidget : public TemplateTaskWidget
{
public:
    RT_CLASS_DEFINE(ArborDayTaskWidget, Sexy::Widget, RtClass);

    virtual void InitTask(GeneralTask* i_task) override;
    virtual void DrawTaskBackground(Sexy::Graphics* i_g) override;

protected:
    virtual void RequestReward() override;
};

class ArborDayBundleWidget : public TemplateBundleWidget
{
public:
    ArborDayBundleWidget(ArborPresentData data);
    virtual ~ArborDayBundleWidget();

    virtual void Init(int i_index) override;
protected:
    virtual void DrawBundleRewards(Sexy::Graphics* i_g) override;
    virtual void OnPurchaseButtonDepress() override;
    void ConfirmBuy(class UIMessageBox* box, int buttonID);
    void OnBuyKettle(int i_index);
    ArborPresentData m_data;
};

//奖励
class ArborDayTotalRewardItem : public CarnivalTotalRewardItem
{
public:
    virtual void InitView(int i_index, const CarnivalRewardData& reward) override;

protected:
    virtual void CheckCondition() override;
    virtual void RequestReward() override;
};

class ArborDayRewardItem : public CarnivalRewardItem
{
public:
    virtual void InitView(int i_index, const CarnivalRewardData& i_reward, int i_type) override;

protected:
    virtual void CheckCondition() override;
    virtual void RequestReward() override;
};

class UIArborDay : public UISingletonDialog<UIArborDay>, public Sexy::ScrollWidgetListener
{
public:
    UIArborDay();
    ~UIArborDay();
    bool OnCreate() override;
    std::string GetLayoutName() override {
//    	return "UIArborDay";
    	return "UIArborDayNew";
    }
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void Init();
    void SetBubbles(const std::vector<ArborDayBonus>& i_bonus);
    void SetCurrentKettle(int i_kettleNumber);
    int GetCurrentKettle();
    void SetNextNeed(int i_nextNeed);
    int GetRefreshPrice();
    void HarvestBubble(int i_index);
    int GetBubbleItem(int i_index);
    void OnWatering();

    void CalculCache(const std::vector<ArborDayBonus>& i_bonus);
    void ShowCache(bool i_flag);

    static void ShowHarvestDialog(Widget* i_widget);
    static void CloseHarvestDialog(Widget* i_widget);

    void showDescriptionWidget();
    void closeDescriptionWidget();

    void WaterConfirm(class UIMessageBox* box, int buttonID);
    ArborDayData GetData() { return m_cacheData; }
    void Refresh(int server_process, int player_process);

private:
    void InitMain();
    void InitTask();
    void InitBundle();
    void InitTotalReward();
    void InitPersonReward();
    void RefreshBubble();

    int m_cacheIndex;
    ArborDayData m_cacheData;
    std::vector<ArborDayBubbleWidget*> m_bubbleList;
    class ActivityDescriptionUI* m_descriptionUI;
};




#endif
