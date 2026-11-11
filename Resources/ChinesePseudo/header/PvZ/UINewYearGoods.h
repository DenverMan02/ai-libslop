#ifndef __UI_NewYearGoods_H__
#define __UI_NewYearGoods_H__

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "UIListener.h"


struct NewYearGoods
{
    std::vector<S2C_BonusInfo>  StaticGoods;
    std::vector<std::vector<S2C_BonusInfo>>  SelectGoodsList;
    int                         Limit;
};

class NewYearGoodsData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NewYearGoodsData, INetworkData, RtClass);

    std::vector<NewYearGoods> NewYearGoodsList;
};


class UINewYearGoodsAnnouncement : public UISingletonDialog<UINewYearGoodsAnnouncement>
{
public:
    UINewYearGoodsAnnouncement();
    ~UINewYearGoodsAnnouncement();
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UINewYearGoodsAnnouncement"; } 
    virtual void ButtonDepress(int i_id) override;
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

};

class NewYearGoodsBundle : public Widget, public ButtonListener
{
public:
    NewYearGoodsBundle();
    virtual ~NewYearGoodsBundle();

    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView(int i_index);

private:
    void OnBuyNewYearGoods(int i_index);

    int m_index;
    int m_limit;
    Sexy::Image* m_backImage;
    class PVZ2UIButton* m_buyButton;
    class PVZ2UIButton* m_addButton;
};

class UINewYearGoods : public UISingletonDialog<UINewYearGoods>, public Sexy::ScrollWidgetListener
{
public:
    UINewYearGoods();
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UINewYearGoods"; }
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    virtual void ButtonDepress(int i_id) override;
    virtual void Update() override;

    void InitView();
    void showDescriptionWidget();
    void closeDescriptionWidget();

public:
    NewYearGoodsData m_cachedata;
    class ActivityDescriptionUI* m_descriptionUI;
};

class NewYearGoodsSelectTab : public Widget
{
public:
    NewYearGoodsSelectTab();
    virtual ~NewYearGoodsSelectTab();

    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& touch) override;
    virtual void TouchEnded(const Sexy::Touch& touch) override;

    void InitView(int i_tabIndex);
    int GetTabIndex() { return m_tabIndex; }
    S2C_BonusInfo GetBonusInfo() { return m_bonus; };
    void SelectTab(bool i_flag);
    void SetSelectInfo(const S2C_BonusInfo& i_bonus);

private:
    int32 m_touchId;
    int m_tabIndex;
    S2C_BonusInfo m_bonus;
    bool m_selected;
};

class NewYearGoodsSelectItem : public Widget
{
public:
    NewYearGoodsSelectItem();
    virtual ~NewYearGoodsSelectItem();

    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& touch) override;
    virtual void TouchEnded(const Sexy::Touch& touch) override;
    virtual void TouchesCanceled() override;

    void InitView(int i_tabIndex, int i_itemIndex, const S2C_BonusInfo& i_bonus);
    int GetItemIndex() { return m_itemIndex; }
    S2C_BonusInfo GetBonusInfo() { return m_bonus; };
    void SelectItem(bool i_flag);

private:
    int32 m_touchId;
    int m_tabIndex;
    int m_itemIndex;
    S2C_BonusInfo m_bonus;
    bool m_selected;
    class UIRewardFrameSelect* m_frameSelect;
};

class UINewYearGoodsSelect : public UISingletonDialog<UINewYearGoodsSelect>, public Sexy::ScrollWidgetListener
{
public:
    UINewYearGoodsSelect();

    bool OnCreate() override;
    std::string GetLayoutName() override { return "UINewYearGoodsSelect"; }
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    virtual void ButtonDepress(int i_id) override;

    void InitView(int i_index);
    void SelectTab(int i_tabIndex);
    void SelectGoods(int i_tabIndex, int i_itemIndex);


    void ShowUINewYearGoodsConfirm(const std::vector<S2C_BonusInfo>& i_selectList);
    void CloseUINewYearGoodsConfirm();

private:
    bool CheckAllSelect();
    void RequestConfirmSelect();

    int m_index;
    class UINewYearGoodsConfirm* m_newYearGoodsConfirm;
    std::vector<NewYearGoodsSelectTab*> m_selectTabList;
    std::vector<Widget*> m_tabWidgetList;
    std::vector<std::vector<NewYearGoodsSelectItem*>> m_selectItemLists;

};

class UINewYearGoodsConfirm : public Widget, public ButtonListener
{
public:
    UINewYearGoodsConfirm();
    ~UINewYearGoodsConfirm();

    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView(int i_index, const std::vector<S2C_BonusInfo>& i_bonusList);
private:
    void OnBuyNewYearGoods(int i_index);

    int m_index;
    SexyString m_title;
};

#endif