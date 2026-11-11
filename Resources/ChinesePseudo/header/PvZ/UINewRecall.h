#ifndef UINEWRECALL_H
#define UINEWRECALL_H

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "UIRewardFrame.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"


//--------------------------------------------------------------//
#pragma mark - NewRecallSignReward

struct NewRecallSignReward
{
    int                                 ItemId;
    int                                 Amount;
    bool                                Obatained;
};

#pragma mark - NewRecallSignData

class NewRecallSignData : public INetworkData
{
public:
    RT_CLASS_DEFINE(NewRecallSignData, INetworkData, RtClass);

    std::vector<std::vector<NewRecallSignReward>>       RewardList;
    int                                                 CanAwardDays;
};

//--------------------------------------------------------------//
#pragma mark - NewRecallBankDayReward

struct NewRecallBankDayReward
{
    std::vector<S2C_BonusInfo>          ItemList;
    bool                                Obatained;
};

#pragma mark - NewRecallBankData

class NewRecallBankData : public INetworkData
{
public:
    RT_CLASS_DEFINE(NewRecallBankData, INetworkData, RtClass);

    std::vector<NewRecallBankDayReward> RewardList;
    std::vector<int>                    SelectList;
    int                                 CanAwardDays;
    bool                                Qualifications;
};

//--------------------------------------------------------------//
#pragma mark - NewRecallBundleReward

struct NewRecallBundleReward
{
    std::vector<S2C_BonusInfo>      ItemList;
    bool                            Obatained;
    int                             Price;
    int                             BundleId;
};

#pragma mark - NewRecallBundleData

class NewRecallBundleData : public INetworkData
{
public:
    RT_CLASS_DEFINE(NewRecallBundleData, INetworkData, RtClass);

    std::vector<NewRecallBundleReward>    BundleList;
};


//-----------------------------------------------------------------------------------------------------------------------//
#pragma mark - NewRecallSelectItem

class NewRecallSelectItem : public UIRewardFrame 
{
public:
    NewRecallSelectItem(RewardType type, const std::string& reward, int rewardQuantity, bool hasFrame = true);
    ~NewRecallSelectItem();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void LoadData(const S2C_BonusInfo& i_item);
    void OnItemSelect(int i_itemid, int index = -1);
    void SetItemIndex(int index) { m_index = index; }
    S2C_BonusInfo GetItem() { return m_item; }

private:
    int m_touchId;
    bool m_isSelected;
    S2C_BonusInfo m_item;
    int m_index;// item index in bonuslist
};

#pragma mark - UICommonItemSelect

class UICommonItemSelect : public UISingletonDialog<UICommonItemSelect>, public Sexy::ScrollWidgetListener
{
public:
    UICommonItemSelect();
    ~UICommonItemSelect();

    virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UICommonItemSelect"; }
    virtual void                            ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void                            ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void							Update() override;
	virtual void							ButtonDepress(int i_id) override;

    void                                    registerSelectRecall(const std::function<void(int)>& i_select);
    void                                    SetTitle(const std::string& i_title);
    void                                    SetDescription(const std::string& i_des);
    void                                    LoadData(const std::vector<S2C_BonusInfo>& i_data);
    void                                    OnItemSelect(int i_itemid, int index = -1);
    int                                     GetSelectId();
    int                                     GetSelectIndex();
    std::vector<NewRecallSelectItem*>       GetItemList();
    void                                    SetCloseButtonDisabled(bool i_flag);
    void                                    SetCloseButtonVisible(bool i_flag);

protected:
    int                                     m_selectId;
    int                                     m_selectIndex;// item index in bonuslist
    std::function<void(int)>                m_selectRecall;
    std::vector<NewRecallSelectItem*>       m_itemList;
};


//-----------------------------------------------------------------------------------------------------------------------//
#pragma mark - NewRecallSignLine

class NewRecallSignLine : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    NewRecallSignLine();
    ~NewRecallSignLine();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void init(int i_index, const std::vector<NewRecallSignReward>& i_reward, bool i_special);
    void determineSelect(class UIMessageBox* box, int buttonID);
    void setNoCondition();
    void obtainReward(int i_index, const S2C_BonusInfo& bonus);

private:
    int m_index;
    bool m_special;
    bool m_isObtained;
    SexyString m_description;
    PVZ2UIButton* m_button;
    std::vector<NewRecallSignReward> m_rewardInfo;
};

#pragma mark - NewRecallSignWidget

class NewRecallSignWidget : public Sexy::Widget, public Sexy::ScrollWidgetListener
{
public:
    NewRecallSignWidget();
    ~NewRecallSignWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void init(const NewRecallSignData& i_signData);
};


//-----------------------------------------------------------------------------------------------------------------------//
#pragma mark - NewRecallBankLine

class NewRecallBankLine : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    NewRecallBankLine();
    ~NewRecallBankLine();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void init(int i_index, const NewRecallBankDayReward& i_reward);
    void setNoCondition();
    void determineExchange(class UIMessageBox* box, int buttonID);
    void setParentBank(class NewRecallBankWidget* i_bank);
    void exchangeReward();

private:
    int m_index;
    bool m_isObtained;
    SexyString m_description;
    PVZ2UIButton* m_button;
    NewRecallBankDayReward m_rewardInfo;
    NewRecallBankWidget* m_bank;
};

#pragma mark - NewRecallBankWidget

class NewRecallBankWidget : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    NewRecallBankWidget();
    ~NewRecallBankWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void determineSelect(class UIMessageBox* box, int buttonID);
    void init(const NewRecallBankData& i_bankData);

    void ObtainedReward();

public:
    bool m_isFirstObtain;

private:
    int m_pieceId;
    SexyString m_selectStr;
    NewRecallBankData m_bankData;
    PVZ2UIButton* m_buyButton;
    PVZ2UIButton* m_selectButton;
};


//-----------------------------------------------------------------------------------------------------------------------//
#pragma mark - NewRecallBundleItem

class NewRecallBundleItem : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    NewRecallBundleItem();
    ~NewRecallBundleItem();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void init(const NewRecallBundleReward& i_bundleData);
    void buySuccess(int i_bundleid);

private:
    Sexy::Image* m_image;
    PVZ2UIButton* m_button;
    NewRecallBundleReward m_bundleData;
};

#pragma mark - NewRecallBundleWidget

class NewRecallBundleWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    NewRecallBundleWidget();
    ~NewRecallBundleWidget();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void init(const NewRecallBundleData& i_signData);
    void buySuccess(int i_bundleid);

private:
    bool m_obtainedSp;
    PVZ2UIButton* m_bundleButton;
};


//-----------------------------------------------------------------------------------------------------------------------//
#pragma mark - UINewRecall

class UINewRecall : public UISingletonDialog<UINewRecall>
{
public:
    UINewRecall();
	virtual ~UINewRecall();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UINewRecall"; }
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void							Update() override;
	virtual void							ButtonDepress(int i_id) override;
    void                                    onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

private:
    bool m_initFinish;
    Sexy::Widget* m_tab1;
    Sexy::Widget* m_tab2;
    Sexy::Widget* m_tab3;
    PVZ2UIButton* m_tabbtn1;
    PVZ2UIButton* m_tabbtn2;
    PVZ2UIButton* m_tabbtn3;
};

namespace Message
{
    void NewRecallSelect(int i_itemid, int index);
    void BundleBuySuccess(int bundleid);
}

#endif
