#ifndef __UI_Carnival_H__
#define __UI_Carnival_H__

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "UIListener.h"
#include "EffectAnim_UIAnim.h"


struct CarnivalBundleExtra
{
    int ObjectID = 0;
    int MinValue = 0;
    int MaxValue = 0;
};

struct CarnivalBundleData
{
    int Type = 0; //0 普通， 1 限时左边， 2 限时右边, 3 预告
    int BundleID = 0;
    int ItemID = 0;
    int Limit = 0;
    int Price = 0;
    int TotalLimit = 0;
    std::vector<S2C_BonusInfo> Bonus;
    std::vector<CarnivalBundleExtra> ExtraBonus;
    std::vector<S2C_BonusInfo> AdditionBonus;
    std::string StartTime;
    std::string EndTime;
};

struct CarnivalRewardData
{
    int Condition = 99999;
    int Obtained = 0;
    std::vector<S2C_BonusInfo> Reward;
};

class CarnivalData : public INetworkData
{
public:
	RT_CLASS_DEFINE(CarnivalData, INetworkData, RtClass);

    int Tickets;
    int BuyTimes;
    int TotalBuyTimes;
    std::vector<CarnivalBundleData> FlashSale;
    std::vector<CarnivalBundleData> DailySale;
    std::vector<CarnivalBundleData> FlashSaleNotice;
    std::vector<std::vector<S2C_BonusInfo>> PacketList;
    std::vector<CarnivalRewardData> TotalBuyReward;
    std::vector<CarnivalRewardData> BuyReward;
};

class CarnivalResultData : public INetworkData
{
public:
	RT_CLASS_DEFINE(CarnivalResultData, INetworkData, RtClass);

    int BundleType;
    int BundleID;
    int MaterialNumber;
    std::vector<S2C_BonusInfo> RewardList;
};


//礼包
class CarnivalBundle : public Widget, public ButtonListener
{
public:
    CarnivalBundle();
    ~CarnivalBundle();

    virtual void Draw(Graphics* i_g) override;
    virtual void Update() override;
    virtual void ButtonDepress(int i_id) override;

    virtual void TouchBegan(const Sexy::Touch& touch) override;
    virtual void TouchEnded(const Sexy::Touch& touch) override;

    void InitView(int i_type, CarnivalBundleData& i_data);
private:
    bool IsLimitBundle();
    bool IsDailyBundle();
    bool IsPreviewBundle();
    void ConfirmBuy(class UIMessageBox* box, int buttonID);
    void OnBuyCarnivalBundle(int i_type, int i_bundleID);
private:
    int32 m_touchId;
    int m_type;
    CarnivalBundleData m_data;
private:
    SexyString m_title;
    SexyString m_timer;
    time_t m_endTime;
    class Image* m_image;
};

class UICarnivalBundleInfo : public UISingletonDialog<UICarnivalBundleInfo>
{
public:
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UICarnivalBundleInfo"; }
    void ButtonDepress(int i_id) override;

    void InitView(int i_type, const CarnivalBundleData& i_data);
};

class CarnivalBundlePreview : public Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{

public:
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView(std::vector<CarnivalBundleData>& i_flashSaleNotice);
};

//商店
class CarnivalPacket : public Widget, public ButtonListener
{
public:
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView(int i_index, const std::vector<S2C_BonusInfo>& reward);

private:
    int m_index;
    SexyString m_title;
    SexyString m_tickets;
    class Image* m_image;
};

class CarnivalPacketListWidget : public Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView(const std::vector<std::vector<S2C_BonusInfo>>& i_bonus);
};

//奖励
class CarnivalTotalRewardItem : public Widget
{
public:
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Update() override;

    virtual void InitView(int i_index, const CarnivalRewardData& reward);

protected:
    virtual void CheckCondition();
    virtual void RequestReward();

protected:
    int m_index;
    int32 m_touchId;
    CarnivalRewardData m_data;

protected:
    bool m_hasCondition = false;
    SexyString m_title;
    class UtilEasyDisplayWidget* m_receiveWidget;
};

class CarnivalRewardItem : public Widget
{
public:
    virtual void Draw(Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Update() override;

    virtual void InitView(int i_index, const CarnivalRewardData& i_reward, int i_type);

protected:
    virtual void CheckCondition();
    virtual void RequestReward();

protected:
    int m_type;
    int m_index;
    int32 m_touchId;
    CarnivalRewardData m_data;
protected:
    bool m_hasCondition = false;
    SexyString m_title;
    class UtilEasyDisplayWidget* m_receiveWidget;
};


class UICarnival : public UISingletonDialog<UICarnival>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
    UICarnival();
    virtual ~UICarnival();
    
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UICarnival"; }
    void ButtonDepress(int i_id) override;
    virtual void Update() override;
    virtual void TabSelectionChanged(int tabID);
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();
    void Refresh();

public:
    void OnBuyBundle();
    void ShowBundlePreview();
    void CloseBundlePreview();
    void ShowPacketList();
    void ClosePacketList();
    void showDescriptionWidget();
    void closeDescriptionWidget();

protected:
    void InitBundle();
    void InitTotalReward();
    void InitPersonReward();
    void OnBuyCarnivalPacket(int i_index);
	void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

private:
    time_t m_initTime;
    time_t m_nextFlashSaleStart;
    time_t m_refreshTimer;
private:
    CarnivalBundlePreview* m_bundlePreview;
    CarnivalPacketListWidget* m_packetListWidget;
    class ActivityDescriptionUI* m_descriptionUI;
public:
    CarnivalData m_cachedata;
};

namespace Message
{
    void OnBuyCarnivalBundle(int i_type, int i_bundleID);
}

// class UICarnivalTest : public LazySingleton<UICarnivalTest>
// {
// public:
//     void showdialog_test();
//     void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

// };

#endif
