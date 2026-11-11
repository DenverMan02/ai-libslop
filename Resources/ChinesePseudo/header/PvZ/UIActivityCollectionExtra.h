#ifndef ActivityCollectionExtra_H_
#define ActivityCollectionExtra_H_

#include "UIActivityCollection.h"
#include "UISingletonDialog.h"
#include "DailySignPage.h"

class ActivityCollectionContainerBase : public Widget, public Sexy::ButtonListener, public ActivityCollectionContainer, public Sexy::ScrollWidgetListener
{
public:
    ActivityCollectionContainerBase();
    virtual ~ActivityCollectionContainerBase();

    virtual void Update() override;
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    virtual void DrawBackground(Sexy::Graphics* i_g);
    virtual void DrawTimer(Sexy::Graphics* i_g, int i_startX, int i_startY);
    virtual void DrawInfo(Sexy::Graphics* i_g, int i_startX, int i_startY);
    virtual void DrawLock(Sexy::Graphics* i_g, int i_startX, int i_startY);

public:
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;

    void InitTimer(const Sexy::Point& i_timerPos);
    void InitGotoButton(const Sexy::Rect& i_btnRect, const std::function<void()>& i_func = nullptr, bool i_needRequest = true);
    void InitInfoButton(const Sexy::Point& i_archorPoint, const SexyString& i_title, const std::vector<SexyString>& i_description);
    void InitInfoButton(const Sexy::Point& i_archorPoint, const std::function<void()>& i_func);
    void InitRewardPriview(const Sexy::Rect& i_priviewRect, const std::vector<S2C_BonusInfo>& i_previewList);

    void SetActivityType(int i_activityID) { m_activityID = i_activityID; }
    void SetBackgroundImage(Sexy::Image* i_background) { m_background = i_background; }
    void SetBackgroundImage(const std::string& i_background);

    void ShowInfoWidget();
    void CloseInfoWidget();
    void SetUnlockState(bool unlock) { m_unlock = unlock; }
    virtual SexyString GetLockDesc() { return _S(""); }

protected:
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    Sexy::Image* m_background;
    int m_activityID;
    bool m_enableTimer;
    SexyString m_timer;
    Sexy::Point m_timerPos;
	bool m_gotoNeedRequest;
	bool m_gotoRequestFlag;
    std::function<void()> m_gotoFunc;
    bool m_enableInfo;
    Sexy::Point m_infoPos;
    SexyString m_infoTitle;
    std::vector<SexyString> m_infoDes;
    std::function<void()> m_infoFunc;
    class ActivityDescriptionUI* m_descriptionUI;
    bool m_enablePriview;
    Sexy::Rect m_priviewRect;
    bool m_unlock;
    Sexy::Point m_lockPos;
};


class ActivityCollectionLuckyBag : public ActivityCollectionContainerBase
{
public:
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionLimitGroupBuy : public ActivityCollectionContainerBase
{
public:
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionLimitSummon : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionCarnival : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionLevelOfDay : public ActivityCollectionContainerBase
{
public:
	ActivityCollectionLevelOfDay();
	~ActivityCollectionLevelOfDay();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
private:
	Sexy::Image* m_nameImage;
};

class ActivityCollectionOneYuan : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionGoldenEgg : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionBossChallenge : public ActivityCollectionContainerBase
{
public:
    virtual void ButtonDepress(int i_id) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionWishingPool : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionSecretStore : public ActivityCollectionContainerBase
{
public:
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionAnniversaryTreasure : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionNewYearGoods : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionPlantCultivate : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionCallofWish : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionDaveKitchen : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionFightZodiac : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionDragonTreasure : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionPlayerSurvey : public UISingletonDialog<ActivityCollectionPlayerSurvey>, public ActivityCollectionContainer, public Sexy::ScrollWidgetListener
{
public:
	ActivityCollectionPlayerSurvey();
	virtual ~ActivityCollectionPlayerSurvey();

	std::string GetLayoutName() override { return "UIPlayerSurveyActivityNew"; }
	virtual bool OnCreate() override;
    virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;
	virtual void Update() override;

    void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
    void RefreshContainer(class ActivityCollectionTabBase* i_tabBase) override;
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void InitView();
	void AdjustScreen();
	void showFestivalGameEntrance();
	void ShowErrorDialog();
	void ShowTips();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void SetButtonDisable(bool status);

protected:
	bool m_thisRequest;
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	int m_activityID;
};


class ActivityCollectionRichman : public UISingletonDialog<ActivityCollectionRichman>, public ActivityCollectionContainer, public Sexy::ScrollWidgetListener
{
public:
	ActivityCollectionRichman();
	virtual ~ActivityCollectionRichman();

	std::string GetLayoutName() override { return "UIRichmanActivityNew"; }
	virtual bool OnCreate() override;
    virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;
	virtual void Update() override;

    void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
    void RefreshContainer(class ActivityCollectionTabBase* i_tabBase) override;

	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void InitView();
	void AdjustScreen();
	void showFestivalGameEntrance();
	void ShowErrorDialog();
	void ShowTips();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

protected:
	bool m_thisRequest;
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	int m_activityID;
};


class ActivityCollectionRechargeDailySign : public UISingletonDialog<ActivityCollectionRechargeDailySign>, public ActivityCollectionContainer
{
public:
	ActivityCollectionRechargeDailySign();
	virtual ~ActivityCollectionRechargeDailySign();

	std::string GetLayoutName() override { return "UIRechargeDailySignActivityNew"; }
	virtual bool OnCreate() override;
    virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;
	virtual void Update() override;

    void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
    void RefreshContainer(class ActivityCollectionTabBase* i_tabBase) override;

	void InitView();
	void AdjustScreen();
    void UpdateUI(class RechargeDailySignData data);
    void OnRechargeCallback(MagentoProductProps* i_props);
	void showFestivalGameEntrance();
	void ShowErrorDialog();
	void ShowTips();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

protected:
	bool m_thisRequest;
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	int m_activityID;

    std::vector<class RechargeDailySignWidgetNew*> m_itemList;// for all days ui
};


class ActivityCollectionDiscountShop : public UISingletonDialog<ActivityCollectionDiscountShop>, public ActivityCollectionContainer
{
public:
	ActivityCollectionDiscountShop();
	virtual ~ActivityCollectionDiscountShop();

	std::string GetLayoutName() override { return "UIDiscountShopActivityNew"; }
	virtual bool OnCreate() override;
    virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;
	virtual void Update() override;

    void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
    void RefreshContainer(class ActivityCollectionTabBase* i_tabBase) override;

	void InitView();
	void AdjustScreen();
	void showFestivalGameEntrance();
	void ShowErrorDialog();
	void ShowTips();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void OnRechargeCallback(MagentoProductProps* i_props);
    void OnGetRewardResult(bool success, const S2C_ShopItemPurchaseInfo* pData);
    void UpdateUI(class DiscountShopData data);

protected:
	bool m_thisRequest;
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");

	UIWidgetText* m_pRefreshTime;
	SexyString m_refreshTimeLabel = _S("");

	Color m_timeColor = Color::White;
	int m_activityID;

    std::vector<class DiscountShopContentWidgetNew*> m_itemList;// shop content item list
};

class ActivityCollectionPiggyBank : public UISingletonDialog<ActivityCollectionPiggyBank>, public ActivityCollectionContainer
{
public:
	ActivityCollectionPiggyBank();
	virtual ~ActivityCollectionPiggyBank();

	std::string GetLayoutName() override { return "UIPiggyBankActivityNew"; }
	virtual bool OnCreate() override;
    virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;
	virtual void Update() override;

    void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
    void RefreshContainer(class ActivityCollectionTabBase* i_tabBase) override;

	void InitView();
	void AdjustScreen();
	void showFestivalGameEntrance();
	void ShowErrorDialog();
	void ShowTips();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void onBuyPiggyBank(bool success, int shop);
	void LoadData();
	void UpdateUIData();

protected:
	bool m_thisRequest;
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	int m_activityID;

	time_t m_expireTime;
	PiggyBankRewardData  m_piggyBankRewradData;
	bool m_canBuy;
	std::vector<class DailySignBannerNew*> m_banners;
};

class ActivityCollectionVaseBreaker : public ActivityCollectionContainerBase
{
public:
	ActivityCollectionVaseBreaker() : m_taskWidget(nullptr){}	
    void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
	void RefreshContainer(class ActivityCollectionTabBase* i_tabBase) override;	
	void DrawTimer(Sexy::Graphics* i_g, int i_startX, int i_startY) override;
	void Draw(Sexy::Graphics* i_g) override;
private:
	void RefreshTasks();	
	class DailyAchievement* m_taskWidget;
};

class ActivityCollectionUITenYearRecord : public ActivityCollectionContainerBase
{
public:
	// ActivityCollectionUITenYearRecord();
	// virtual ~ActivityCollectionUITenYearRecord();
//	std::string GetLayoutName() override { return "UITenYearRecord"; }

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

class ActivityCollectionPartyAssist : public UISingletonDialog<ActivityCollectionPartyAssist>, public ActivityCollectionContainer, public Sexy::ScrollWidgetListener
{
public:
	ActivityCollectionPartyAssist();
	virtual ~ActivityCollectionPartyAssist();

	std::string GetLayoutName() override { return "UIPartyAssistActivityNew"; }
	virtual bool OnCreate() override;
    virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;
	virtual void Update() override;

    void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
    void RefreshContainer(class ActivityCollectionTabBase* i_tabBase) override;

	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void InitView();
	void AdjustScreen();
	void showFestivalGameEntrance();
	void ShowErrorDialog();
	void ShowTips();
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

protected:
	bool m_thisRequest;
	UIWidgetText* m_pActivityTime;
	SexyString m_timeLabel = _S("");
	Color m_timeColor = Color::White;
	int m_activityID;
};


class ActivityCollectionCustomVoting : public ActivityCollectionContainerBase
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};


class ActivityCollectionUINewYearGiftBox : public ActivityCollectionContainerBase
{
public:
	// ActivityCollectionUITenYearRecord();
	// virtual ~ActivityCollectionUITenYearRecord();
//	std::string GetLayoutName() override { return "UITenYearRecord"; }

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitContainer(class ActivityCollectionTabBase* i_tabBase) override;
};

#endif
