#ifndef UI_DragonTreasure_H
#define UI_DragonTreasure_H

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "RepeatUIComponent.h"


struct DragonTreasureItemData
{
    int id;
    int quantity;
    int obtained;
};

struct DragonTreasureShopData
{
    int id;
    int quantity;
    int currency;
    int limit;
};

class DragonTreasureData : public INetworkData
{
public:
	RT_CLASS_DEFINE(DragonTreasureData, INetworkData, RtClass);

    int Crystal;//龙晶数量
    int Integral;//积分数量

    int LotteryCost;//抽奖消耗
    int ResetCost;//重置消耗

    int CanReset;//是否可以重置

    int ResetStatus;//重置状态

    std::vector<DragonTreasureItemData> DTreasureList;
    std::vector<std::vector<DragonTreasureItemData>> DTreasureSelectList;
    int BigAward;

    std::vector<std::vector<S2C_BonusInfo>> DTrasureBundleList;
    std::vector<int> DTrasureBundleLimit;

    std::vector<DragonTreasureShopData> DTrasureShopList;

    std::vector<S2C_BonusInfo> RewardList;
};

//礼包

class DragonTreasureBundleWidget : public Widget, public Sexy::ButtonListener
{
public:
    DragonTreasureBundleWidget();
    ~DragonTreasureBundleWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView(int i_index, const std::vector<S2C_BonusInfo>& i_bundleInfo, int i_bundleLimit);
    void OnBuyDragonTreasure(int i_index);

private:
    int m_index;
    int m_limit;
    Sexy::Image* m_background;
    class PVZ2UIButton* m_bundleButton;
};

//商店

class DragonTreasureShopWidget : public Widget, public Sexy::ButtonListener
{
public:
    DragonTreasureShopWidget();
    ~DragonTreasureShopWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
	virtual void Update() override;

    void InitView(int i_index, const DragonTreasureShopData& i_shopData);

private:
    void BuyShopItem();

    int m_index;
    int m_limit;
    SexyString m_name;
    DragonTreasureShopData m_shopData;

    class UIWidgetText* m_limitText;
    class PVZ2UIButton* m_bundleButton;
};

//ui

class UIDragonTreasure : public UISingletonDialog<UIDragonTreasure>, public Sexy::ScrollWidgetListener
{
public:
    UIDragonTreasure();
    ~UIDragonTreasure();

    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIDragonTreasure"; }
    virtual void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}


    void InitView();
    void RefreshInfo();

    void RequestNetwork();
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    void showDescriptionWidget();
    void closeDescriptionWidget();

private:
    void InitTeasure();
    void InitBundle();
    void InitShop();

    void Reset();
    void Lottery();

    bool m_thisRequest;
public:
    DragonTreasureData m_cacheData;
    class ActivityDescriptionUI* m_descriptionUI;
};

//select

class DragonTreasureSelectItem : public Sexy::Widget, public Sexy::ButtonListener
{
    friend class DragonTreasureSelectLine;
public:
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void InitView(class DragonTreasureSelectLine* i_parent, int i_index, DragonTreasureItemData i_info);
    void SetSelect(bool i_flag);

private:
    int m_touchId;
    int m_index;
    bool m_canSelect;
    bool m_selected;

    class DragonTreasureSelectLine* m_parent;
    class UIWidgetImage* m_selectedImage;
};

class DragonTreasureSelectLine : public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener
{
public:
    void Draw(Graphics* i_g) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}  

    void InitView(int i_index, std::vector<DragonTreasureItemData>& i_infos);
    void SelectItem(int i_index);

    int GetSelectItemIndex();

private:
    int m_index;
    Sexy::Image* m_leftImage = nullptr;
    std::vector<DragonTreasureSelectItem*> m_itemList;
};

class UIDragonTreasureSelect : public UISingletonDialog<UIDragonTreasureSelect>, public Sexy::ScrollWidgetListener
{
public:
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIDragonTreasureSelect"; }
    void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();
    void SelectLottery();

private:
    std::vector<DragonTreasureSelectLine*> m_lineList;
};



#endif