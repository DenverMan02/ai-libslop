#ifndef UILUCKBAG_H
#define UILUCKBAG_H

#include "UISingletonDialog.h"
#include "NetworkData.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"


#pragma mark - LuckBagData

class LuckBagData : public INetworkData
{
public:
    RT_CLASS_DEFINE(LuckBagData, INetworkData, RtClass);

    std::vector<LotteryBonus> SelectedList;
    std::vector<std::vector<LotteryBonus>> PlantLists;
};


#pragma mark - UILuckBagAnnouncement

class UILuckBagAnnouncement : public UISingletonDialog<UILuckBagAnnouncement>
{
public:
    virtual bool OnCreate() override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual std::string GetLayoutName() override { return "UILuckBagAnnouncement"; }
};

#pragma mark - ShowLuckBagDescriptionUI

class ShowLuckBagDescriptionUI : public Widget, public ButtonListener
{
public:
    virtual void ButtonDepress(int i_id) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;

    void InitView();
};


#pragma mark - UILuckBag

class UILuckBag : public UISingletonDialog<UILuckBag>
{
public:
    UILuckBag();
	virtual ~UILuckBag();

    virtual bool OnCreate() override;
    virtual void Update() override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual std::string GetLayoutName() override { return "UILuckBag"; }

    void selectFinish();
    void OnNotifyBillingReward(bool i_success, const S2C_BillingReward* pData);

    void showDescription();
    void closeDescription();

    void LockButtons();
    void UnlockButtons();

private:
    void updateButton();
    void init();
    void updateTimer();
    void BuyByTicket(class UIMessageBox* box, int buttonID);

    bool m_isSelected;
    bool mCanUseTicket;
    ShowLuckBagDescriptionUI* m_desUI;
};


#pragma mark - LuckBagSelectItem

class LuckBagSelectItem : public Widget
{
public:
    LuckBagSelectItem(class LuckBagSelectRow* i_parent = nullptr);
    virtual ~LuckBagSelectItem();

    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void Draw(Graphics* i_g) override;

    void init(const LotteryBonus& i_bonus);
    LotteryBonus getData();

    void setIsSelected(bool i_flag);
    bool getIsSelected();
private:
    int m_rare;
    int m_touchId;
    bool m_isSelected;
    LotteryBonus m_data;
    SexyString m_name;
    Sexy::Image* m_image;
    class LuckBagSelectRow* m_parent;
};


#pragma mark - LuckBagSelectRow

class LuckBagSelectRow : public Widget, public Sexy::ScrollWidgetListener
{
public:

    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    virtual void Draw(Graphics* i_g) override;

    void init(const std::vector<LotteryBonus>& i_data, int i_row);

    void setSelect(int i_itemId);
    LotteryBonus getSelect();

private:
    int m_rowNum;
    std::vector<LuckBagSelectItem*> m_vecItem;
};


#pragma mark - ShowLuckBagSelectUI

class ShowLuckBagSelectUI : public Widget, public ButtonListener
{
public:
    virtual void ButtonDepress(int i_id) override;
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;

    void InitView(const std::vector<LotteryBonus>& i_vec);
private:
    void SelectOK();
    std::vector<LotteryBonus> m_selectVec;
};


#pragma mark - UILuckBagSelect

class UILuckBagSelect : public UISingletonDialog<UILuckBagSelect>, public Sexy::ScrollWidgetListener
{
public:
    UILuckBagSelect();
	virtual ~UILuckBagSelect();

    virtual bool OnCreate() override;
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual std::string GetLayoutName() override { return "UILuckBagSelect"; }
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void showSelectedUI();
    void closeSelectedUI();
private:
    void init();

    ShowLuckBagSelectUI* m_selectUI;
    std::vector<LuckBagSelectRow*> m_vecRow;
};

#pragma mark - LuckBagShowSelect



#endif