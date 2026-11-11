#ifndef UIWishingPool_H
#define UIWishingPool_H

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "UIListener.h"
#include "EffectAnim_UIAnim.h"
#include "RepeatUIComponent.h"


struct WishingPoolBubbleInfo
{
    int objectId;
    int quantity;
    int obtain;

    WishingPoolBubbleInfo()
    {
        objectId = 0;
        quantity = 0;
        obtain = 0;
    }
};

struct WishingPoolGrandInfo
{
    int Condition;
    std::vector<S2C_BonusInfo> RewardList;
    int Obtained;

    WishingPoolGrandInfo()
    {
        Condition = 0;
        Obtained = 1;
    }
};

class WishingPoolData : public INetworkData
{
public:
	RT_CLASS_DEFINE(WishingPoolData, INetworkData, RtClass);

    std::vector<std::vector<std::vector<S2C_BonusInfo>>> SelectList;
    std::vector<std::vector<WishingPoolBubbleInfo>> BubbleInfos;
    std::vector<std::vector<S2C_BonusInfo>> BundleList;
    std::vector<int> BundleLimit;
    std::vector<WishingPoolGrandInfo> GrandList;
    int Material;
    int LotteryTimes;

    std::vector<S2C_BonusInfo> RewardList;
};


class WishingPoolSelectItem : public Sexy::Widget, public Sexy::ButtonListener
{
    friend class WishingPoolSelectLine;
public:
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void InitView(class WishingPoolSelectLine* i_parent, int i_index, S2C_BonusInfo i_info);
    void SetSelect(bool i_flag);

private:
    int m_touchId;
    int m_index;
    bool m_canSelect;
    bool m_selected;

    class WishingPoolSelectLine* m_parent;
    class UIWidgetImage* m_selectedImage;
};

class WishingPoolSelectLine : public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener
{
public:
    void Draw(Graphics* i_g) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}  

    void InitView(int i_index, std::vector<S2C_BonusInfo>& i_infos);
    void SelectItem(int i_index);

    int GetSelectItemIndex();

private:
    int m_index;
    Sexy::Image* m_leftImage = nullptr;
    std::vector<WishingPoolSelectItem*> m_itemList;
};

class UIWishingPoolSelect : public UISingletonDialog<UIWishingPoolSelect>, public Sexy::ScrollWidgetListener
{
public:
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIWishingPoolSelect"; }
    void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();
    void SelectLottery();

private:
    std::vector<WishingPoolSelectLine*> m_lineList;
};

class WishingPoolBundle : public TemplateBundleWidget
{
public:
    WishingPoolBundle();
    virtual ~WishingPoolBundle();

    virtual void Init(int i_index) override;
    virtual void Draw(Sexy::Graphics* i_g) override;

    void SetData(int i_limit, const std::vector<S2C_BonusInfo>& i_rewards);

protected:
    virtual void DrawBundleTitle(Sexy::Graphics* i_g) override;
    virtual void DrawBundleRewards(Sexy::Graphics* i_g) override;
    virtual void OnPurchaseButtonDepress() override;

    void OnBuyWishBundle(int i_index);

    std::vector<S2C_BonusInfo> m_rewards;
};

class WishingPoolGrandWidget : public Widget, public Sexy::ButtonListener
{
public:
    WishingPoolGrandWidget();
    virtual ~WishingPoolGrandWidget();

    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView(int i_index, WishingPoolGrandInfo i_info);
    void Refresh();

private:
    int m_index;

    SexyString m_description;
    int m_currentLottery;
    bool m_obtained;
    int m_conditionLottery;
    class PVZ2UIButton* m_button;
};

class UIWishingPool : public UISingletonDialog<UIWishingPool>, public Sexy::ScrollWidgetListener
{
public:
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIWishingPool"; }
    void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();
    void Refresh();

private:
    void InitTab1();
    void InitTab2();
    void InitTab3();

    void InitBubbles();
    void CheckBubbles();
    void StartLottery(int i_type);

public:
    WishingPoolData m_cacheData;
};

namespace Message
{
    void WishingPoolLottery();
}

#endif