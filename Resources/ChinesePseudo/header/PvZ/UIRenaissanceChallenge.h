#ifndef UIRENAISSANCECHALLENGE_H
#define UIRENAISSANCECHALLENGE_H

#include "UISingletonDialog.h"
#include "PopingWidget.h"
#include "PVZ2UIButton.h"
#include "EffectAnim_UIAnim.h"
#include "UIListener.h"
#include "NetworkData.h"
#include "Image.h"
#include "UIScrollWidget.h"

struct SubActivityTimeData
{
    int PlantId;
    int StartTime;
    int EndTime;
};

struct RenaissanceChallengeRewardItemData
{
    int Id;
    int Quantity;
    int Surplus;
    int Currency;
    int Maximum;
};

struct EggRechargeBundleData
{
    int BundleId;
    std::vector<S2C_BonusInfo> BundleInfo;
    int LimitTimes;
};

class RenaissanceChallengeRewardWidget : public Sexy::Widget
{
public:
    RenaissanceChallengeRewardWidget();
    virtual ~RenaissanceChallengeRewardWidget();

    virtual void			Resize(const Rect& i_Rect) override;
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;

    virtual void            TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void            TouchEnded( const Sexy::Touch& i_touch ) override;

    void                    setData(int index, const RenaissanceChallengeRewardItemData& i_data);
    void                    init();

private:
    RenaissanceChallengeRewardItemData m_data;
    SexyString m_rewardName;
    SexyString m_shopBuyTime;
    Sexy::Image* m_rewardImage;
    Rect m_itemRect;
    bool m_isPlantChip;
    bool m_soldOut;
    std::string m_bonusName;
    int m_touchId;
    int m_index;

    Sexy::Image* m_materialNeedImage;
};

class RenaissanceChallengeActivityWidget : public Sexy::Widget, public ButtonListener
{
public:
    RenaissanceChallengeActivityWidget();
    virtual ~RenaissanceChallengeActivityWidget();

    virtual void			Resize(const Rect& i_Rect) override;
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;

    virtual void			ButtonDepress(int theId) override;

    void                    setData(SubActivityTimeData i_data, int i_id);
    void                    init();

    void                    InitTimer();
    void                    DrawTimer(Sexy::Graphics* i_g);
    void                    UpdateTimer();

private:
    int m_activityId;
    bool m_InActivity;
    Rect m_descriptionRect;
    Rect m_countDownRect;
    Rect m_buttonRect;
    SubActivityTimeData m_activitydata;
    PVZ2UIButton* m_submit;
    //timer
    Rect m_rTimerBG;
    SexyString m_countDown;
    EffectAnim_UIAnim m_eTimer;
};

class RenaissanceChallengeBundleWidget : public Sexy::Widget, public ButtonListener
{
public:
    RenaissanceChallengeBundleWidget();
    ~RenaissanceChallengeBundleWidget();

    virtual void Update() override;
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int theId) override;

    void                    initData(const EggRechargeBundleData& i_data);
    void                    InitTimer();
    void                    DrawTimer(Sexy::Graphics* i_g);
    void                    UpdateTimer();
    void                    onBuyGacha(int i_index);
private:
    EggRechargeBundleData m_data;
    //timer
    Rect m_rTimerBG;
    SexyString m_countDown;
    Rect m_countDownRect;
    EffectAnim_UIAnim m_eTimer;
    Sexy::Image* m_rewardImage;
};

class UIRenaissanceChallengeShop : public UISingletonDialog<UIRenaissanceChallengeShop>
{
public:
    UIRenaissanceChallengeShop();
    virtual ~UIRenaissanceChallengeShop();

    bool OnCreate() override;
    void Update() override;
    std::string GetLayoutName() override { return "UIRenaissanceChallengeShop"; }
    void Draw(Graphics* i_g) override;
    void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void ButtonDepress(int theId) override;

    void initData(int itemId, int itemAmount, int price, int maxBuy, int index);

private:
    int m_index;
    int m_maxBuy;
};

class UIRenaissanceChallenge : public UISingletonDialog<UIRenaissanceChallenge>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
    UIRenaissanceChallenge();
    virtual ~UIRenaissanceChallenge();
    
    bool OnCreate() override;
    void Update() override;
    std::string GetLayoutName() override { return "UIRenaissanceChallenge"; }
    void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int theId) override;

    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) {}
    virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}

    virtual void TabSelectionChanged(int tabID);

    void initEntrance();
    void initShop(const std::vector<RenaissanceChallengeRewardItemData>& i_dataList);
    void initBundle(const std::vector<EggRechargeBundleData>& i_dataList);
    void requestShopInfo();
    void updateMaterial();
    void updateTime();
    void OnShopBuyFinish(bool success, const S2C_ShopItemPurchaseInfo* pData);
    void onBuyGacha(int i_index);
private:
    bool m_hasInitedShop;
};


class RenaissanceChallengeActivityData : public INetworkData
{
public:
    RT_CLASS_DEFINE(RenaissanceChallengeActivityData, INetworkData, RtClass);

    std::vector<SubActivityTimeData> activityTimeList;
    int ResourceId = 0;

};

class RenaissanceChallengeRewardData : public INetworkData
{
public:
    RT_CLASS_DEFINE(RenaissanceChallengeRewardData, INetworkData, RtClass);

    std::vector<RenaissanceChallengeRewardItemData> rewardList;
    std::vector<EggRechargeBundleData> bundleList;

};


class UIRenaissanceChallengeNew : public UISingletonDialog<UIRenaissanceChallengeNew>, public UI::TabControlListener, public Sexy::ScrollWidgetListener
{
public:
    UIRenaissanceChallengeNew();
    virtual ~UIRenaissanceChallengeNew();

    virtual bool OnCreate() override;
    virtual void Update() override;
    virtual std::string GetLayoutName() override { return "UIRenaissanceChallengeNew"; }
    virtual void ScrollTargetReached(ScrollWidget* scrollWidget) {}
    virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}
    virtual void ButtonDepress(int theId) override;

    void InitView();

private:
    void updateMaterial();
    void initShop(const std::vector<RenaissanceChallengeRewardItemData>& i_dataList);
    void initBundle(const std::vector<EggRechargeBundleData>& i_dataList);
    void OnShopBuyFinish(bool success, const S2C_ShopItemPurchaseInfo* pData);
    void onBuyGacha(int i_index);
};

class RenaissanceChallengeActivityWidgetNew : public UIScrollDisplayWidgetBase
{
public:
    RenaissanceChallengeActivityWidgetNew();
    virtual ~RenaissanceChallengeActivityWidgetNew();

    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;
    virtual void			ButtonDepress(int theId) override;

    void                    LoadData(SubActivityTimeData i_data, int i_id);

    void                    InitTimer();
    void                    DrawTimer(Sexy::Graphics* i_g);
    void                    UpdateTimer();

private:
    int m_activityId;
    bool m_locked;
    SubActivityTimeData m_activitydata;
    //timer
    SexyString m_timer;
    Rect m_timerRect;
    EffectAnim_UIAnim m_timerEffect;

    Sexy::Image* m_background;
    SexyString m_description;
};

class RenaissanceChallengeScrollNew : public UIScrollWidgetComponent
{
public:
    RenaissanceChallengeScrollNew();
    virtual ~RenaissanceChallengeScrollNew();

    void InitView();
};


class RenaissanceChallengeNewManager : public LazySingleton<RenaissanceChallengeNewManager>
{
public:
    RenaissanceChallengeNewManager();
    ~RenaissanceChallengeNewManager();

    int GetResourceId();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

private:
    void ReloadData();

    RenaissanceChallengeActivityData m_cacheData;
};


#endif
