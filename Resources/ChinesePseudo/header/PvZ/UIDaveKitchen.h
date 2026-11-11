#ifndef UI_DaveKitchen_H
#define UI_DaveKitchen_H

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "RepeatUIComponent.h"


struct DaveKitchenTaskInfo
{
    int TaskID;
    int TaskStatus;
    std::vector<S2C_BonusInfo> TaskReward;
};

class DaveKitchenData : public INetworkData
{
public:
	RT_CLASS_DEFINE(DaveKitchenData, INetworkData, RtClass);

    std::vector<std::vector<S2C_BonusInfo>>     ExchnageList;
    std::vector<int>                            ExchangeIcon;

    std::vector<DaveKitchenTaskInfo>            TaskList;

    std::vector<std::vector<S2C_BonusInfo>>     BundleInfo;


    std::vector<S2C_BonusInfo>                  RewardList;
    int                                         GemsCost;
};


class DaveKitchenExchangeLine : public Widget, public Sexy::ButtonListener
{
public:

    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView(int i_index, const std::vector<S2C_BonusInfo>& i_exchangeList, int i_exchangeIconIndex);
    void RefreshView();

private:
    void Exchange();

    int m_index;
    std::vector<S2C_BonusInfo> m_exchangeList;
    int m_exchangeIconIndex;

    std::vector<class UIWidgetText*> m_numList;
    class PVZ2UIButton* m_exchangeBtn = nullptr;
}; 

class DaveKitchenTaskWidget : public TemplateTaskWidget
{
public:
    RT_CLASS_DEFINE(DaveKitchenTaskWidget, Sexy::Widget, RtClass);

    virtual void InitTask(GeneralTask* i_task) override;
    virtual void DrawProgress(Sexy::Graphics* i_g) override;
    virtual void DrawRewards(Sexy::Graphics* i_g) override;
    virtual void DrawTaskBackground(Sexy::Graphics* i_g) override;

    void SetTaskData(int i_index, DaveKitchenTaskInfo i_serverTaskInfo);

protected:
    virtual void RequestReward() override;

    int m_index;
    DaveKitchenTaskInfo m_serverTaskInfo;
};

class DaveKitchenBundleWidget : public Widget, public Sexy::ButtonListener
{
public:
    DaveKitchenBundleWidget();
    ~DaveKitchenBundleWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView(int i_index, const std::vector<S2C_BonusInfo>& i_bundleInfo);
    void OnBuyDaveKitchenBundle(int i_index);

private:
    void BuyBundleByGems();

    int m_index;
    class PVZ2UIButton* m_bundleButton;
};




class UIDaveKitchen : public UISingletonDialog<UIDaveKitchen>, public Sexy::ScrollWidgetListener
{
public:
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIDaveKitchen"; }
    virtual void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}


    void InitView();
    void RefreshInfo();

private:
    void InitExchange();
    void InitTask();
    void InitBundle();


    DaveKitchenData m_cacheData;
    std::vector<DaveKitchenExchangeLine*> m_exchangeWidgetList;
};




#endif