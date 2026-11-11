//
//  UIChagreDouble.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 17/5/15.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef _UIChagreDouble_h_
#define _UIChagreDouble_h_

#include "UISingletonDialog.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "NetworkData.h"
#include "PVZ2UIButton.h"

namespace Message
{
	void GetOppoDailyReward();
	void GetOppoRechargeReward();
}

struct stChargeDoubleFesival
{
	int m_nAmount = 0;
	std::vector<S2C_WechatReward> m_vecRewardOne;
};

struct stAward
{
	int m_nMoneyAmount = 0;
	int m_nPlantPieceNum = 0;
};

struct stRewardInfo
{
	std::vector<stAward> m_vecOrange;
	std::vector<stAward> m_vecvViolet;
};

struct stThirdAward
{
	int m_nMoneyAmount = 0;
	int m_nPlantPieceNum = 0;
	int m_nAvatarNum = 0;
};

struct stThirdAwardInfo
{
	std::vector<stThirdAward> m_vecThirdOrange;
	std::vector<stThirdAward> m_vecThirdViolet;
};


class ChagreDoubleFesivalConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(ChagreDoubleFesivalConfig, RtObject, RtClass);
	ChagreDoubleFesivalConfig() : m_nAreadyAwardIndex(0), m_tGivePlantIDTime(0), m_nNumTodayChargeCurrency(0) {}

public:
	std::vector<int> m_vecOriginalList;
	std::vector<int> m_vecAlreadyUsedList;
	stRewardInfo m_firstReward;
	stRewardInfo m_secondReward;
	stThirdAwardInfo m_thirdReward;
	int m_nAreadyAwardIndex;
	time_t m_tGivePlantIDTime;
	int m_nNumTodayChargeCurrency;
};

class UIChagreDouble : public UISingletonDialog<UIChagreDouble>
{
public:
	UIChagreDouble();
	virtual ~UIChagreDouble();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UISpringFestivalLogin"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	void showGemStore();
	void Update() override;
	virtual void                DrawOverlay(Graphics* i_g) override;
	void defalutUI();
	float getCurPercent() const;
protected:
	bool loadData();
	ChagreDoubleFesivalConfig m_configInfo;
	Sexy::Rect m_priceLabelRect1;
	SexyString m_priceLabel1 = _S("");
	Sexy::Rect m_priceLabelRect2;
	SexyString m_priceLabel2 = _S("");
	Sexy::Rect m_priceLabelRect3;
	SexyString m_priceLabel3 = _S("");
	Sexy::Rect m_timeLabelRect;
	SexyString m_timeLabel = _S("");
	Sexy::Rect m_refrashTimeLabelRect;
	SexyString m_refrashTimeLabel = _S("");
	Color m_timeColor = Color::White;
	float m_fCurpercent;
	float m_fCurWidth;
	Sexy::Rect m_bgRect;
	UIWidgetText* m_pActivityTime;
	UIWidgetText* m_pRefrashTime;
};

class UIOppoNewerChargeDouble: public UISingletonDialog<UIOppoNewerChargeDouble>
{
public:
	UIOppoNewerChargeDouble();
	virtual ~UIOppoNewerChargeDouble();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "OppoNewerRechargePanel"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	void showGemStore();
	void Update() override;
	virtual void                DrawOverlay(Graphics* i_g) override;
	void defalutUI();
protected:

	Sexy::Rect m_timeLabelRect;
	SexyString m_timeLabel = _S("");

	std::vector<S2C_WechatReward> m_vecRewards;
};

class OppoNewerRechargeMgr: public LazySingleton<OppoNewerRechargeMgr>
{
public:
	OppoNewerRechargeMgr();
	virtual ~OppoNewerRechargeMgr();

protected:
	void onNotifyOppoRechargeReward();

private:
	int m_todayRecharge;
};


class ChristmasAwardActivityWidget : public Widget, Sexy::ButtonListener
{
public:
	ChristmasAwardActivityWidget(int index, int alreadyAwardDaym, bool isAwardToday, std::vector<NDLoginRewardBonus>& vecAwardItem);
	virtual ~ChristmasAwardActivityWidget();

	virtual void Resize(const Sexy::Rect& theRect) override;
	virtual void Update() override;
	virtual void Draw(Graphics *i_g) override;
	virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;

	void Init();
	void ClearDaveClubInfo();
	Sexy::Widget* GetStartBtn() { return m_startButton; }

	void setIsCanAwardToday(bool isCanAwardToday);
	void setAlreadyAwardDay(int alreadyAwardDay);
	void addAwardButton(int theX, int theY, int theWidth, int theHeight);
private:
	Sexy::Rect m_dialogRect;
	Sexy::Rect m_contentRect;
	Sexy::Rect m_nameRect;
	Sexy::Rect m_iconRect;
	Sexy::Rect m_dayRect;
	Sexy::Rect m_dayBg;
	Sexy::Rect m_alreadyAward;
	PVZ2UIButton* m_startButton;
	ImagePtr m_bgImage;
	ImagePtr m_iconImage;
	ImagePtr m_daysImage;
	ImagePtr m_cellBg;
	ImagePtr m_AwardBg;

	SexyString m_content;
	SexyString m_ActivityName;
	bool m_inited;
	bool m_bIsCanAwardToday;
	std::vector<NDLoginRewardBonus> m_vecAwardItem;
	int m_nAlreadyAwardDay;
	int m_nIndex;
};

class ChristmasAwardActivityScrollPanel : public Widget, public ButtonListener
{
public:
	ChristmasAwardActivityScrollPanel(Sexy::Rect &i_rect, DailyAwardBonus& bonus);
	virtual ~ChristmasAwardActivityScrollPanel();

	std::vector<ChristmasAwardActivityWidget *> GetDungeonList() { return m_dungeonList; }
	void RemoveAllDungeonWidget();
	void OnNotifyChristmasLoginReward(bool i_success, const S2C_7DaysLoginReward* pData);
	void loadData(Sexy::Rect &i_rect, DailyAwardBonus& bonus);
	void InitView();
private:
	std::vector<ChristmasAwardActivityWidget *> m_dungeonList;
	DailyAwardBonus m_Bonus;
};

class ChristmasDailyAwardUI : public UISingletonDialog<ChristmasDailyAwardUI>, public Sexy::ScrollWidgetListener
{
public:
	ChristmasDailyAwardUI();
	virtual ~ChristmasDailyAwardUI();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "ChristmasDailyAwardUI"; }
	virtual void                Draw(Sexy::Graphics* i_g) override;
	virtual void                DrawOverlay(Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	// implement of Sexy::ScrollWidgetListener
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
	virtual void loadData();
	virtual void updateUIData();
	void Update() override;
	void UpdateTimeLabel();
private:

	class PVZ2UIScrollingWidget* m_daveClubScollingWdget;
	class ChristmasAwardActivityScrollPanel* m_dungeonScollingPanel;
	Sexy::Rect m_dungeonListScollRect;
	Sexy::Rect m_timeLebelRect;
	Sexy::Rect m_timeImageRect;
	DailyAwardBonus m_Bonus;
	Color m_timeColor = Color::White;
	SexyString m_timeLebal;
	ImagePtr m_ActivityTimeImage;
};

class OppoAwardActivityWidget: public ChristmasAwardActivityWidget
{
public:
	OppoAwardActivityWidget(int index, int alreadyAwardDaym, bool isAwardToday, std::vector<NDLoginRewardBonus>& vecAwardItem);
	virtual ~OppoAwardActivityWidget();

	virtual void ButtonDepress(int i_id) override;
};

class OppoAwardActivityScrollPanel : public Widget, public ButtonListener
{
public:
	OppoAwardActivityScrollPanel(Sexy::Rect &i_rect, DailyAwardBonus& bonus);
	virtual ~OppoAwardActivityScrollPanel();

	std::vector<OppoAwardActivityWidget*> GetDungeonList() { return m_dungeonList; }
	void RemoveAllDungeonWidget();

	void loadData(Sexy::Rect &i_rect, DailyAwardBonus& bonus);
	void InitView();
private:
	std::vector<OppoAwardActivityWidget *> m_dungeonList;
	DailyAwardBonus m_Bonus;
};

class OppoNewerDailyAwardUI : public UISingletonDialog<OppoNewerDailyAwardUI>, public Sexy::ScrollWidgetListener
{
public:
	OppoNewerDailyAwardUI();
	virtual ~OppoNewerDailyAwardUI();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "OppoNewerDailyAwardPanel"; }
	virtual void                Draw(Sexy::Graphics* i_g) override;
	virtual void                DrawOverlay(Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	// implement of Sexy::ScrollWidgetListener
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
	virtual void loadData();
	virtual void updateUIData();
	void Update() override;
	void UpdateTimeLabel();
protected:
	void OnNotifyOppoLoginReward();

private:

	class PVZ2UIScrollingWidget* m_daveClubScollingWdget;
	class OppoAwardActivityScrollPanel* m_dungeonScollingPanel;
	Sexy::Rect m_dungeonListScollRect;
	Sexy::Rect m_timeLebelRect;
	Sexy::Rect m_timeImageRect;
	DailyAwardBonus m_Bonus;
	Color m_timeColor = Color::White;
	SexyString m_timeLebal;
	ImagePtr m_ActivityTimeImage;
};


//-----------------------------------------------------------------
// ChristmasChargeManager
//-----------------------------------------------------------------
class ChristmasChargeManager : public LazySingleton<ChristmasChargeManager>
{
public:
	ChristmasChargeManager();
	virtual ~ChristmasChargeManager();
	void setAlreadyAwardIndex(int alreadyAwardIndex);
	int getAlreadyAwardIndex();

	void loadData();

	int getOriginalID(const std::vector<int>& vecOriginal,const std::vector<int>& vecAreadyUse) const;
	int getOriginalUnLockID(const std::vector<int>& vecOriginal, const std::vector<int>& vecAreadyUse) const;


	int getAlreadyUsedID(const std::vector<int>& vecAreadyUse);
	bool IsVecContainID(const std::vector<int>& vec, int id) const;
	int getChristmasValuablePlantID();
	int getCurPlantIDFromServer();
	void setCurPlantID(int plantID);
	int getCurPlantID() const;

	int getAvatarIdByPlantID(int plantID) const;

	void NewYearChargeAward();

	time_t getGivePlantIDTime() const;
	bool isActivitySameDay() const;

	int getPlantChipIdByPlantID(int plantID);

	int getNumTodayChargeCurrency() const;
	void setNumTodayChargeCurrency(int Currency);
	void addNumTodayChargeCurrency(int currency);

	void addAward(const CDFReceiveReward& reward);
	std::vector<S2C_WechatReward> trimAwardData(const std::vector<S2C_WechatReward>& data);

	void UpdateRewardBehaviorEventLog(std::vector<S2C_WechatReward>& rewardData);

	bool GetConfig(ChagreDoubleFesivalConfig& result);
private:
	bool isExistenceRewardData(const std::vector<S2C_WechatReward>& data, const S2C_WechatReward& dataReward) const;

	int m_nAlreadyAwardIndex;
	int m_nCurPlantID;
	int m_nNumTodayChargeCurrency;
};

class NewYearRewardData :public INetworkData
{
public:
	RT_CLASS_DEFINE(NewYearRewardData, RtObject, RtClass);
	NewYearRewardData(){};
public:
	std::vector<stThirdAward> m_vecAwardList;
};

class NewYearChargeConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(NewYearChargeConfig, RtObject, RtClass);
	NewYearChargeConfig() : m_plantId(0), m_nNumWeekChargeIndex(0), m_nNumWeekChargeCurrency(0) {}
public:
	int m_plantId;
	int m_nNumWeekChargeIndex;
	int m_nNumWeekChargeCurrency;
	std::vector<stThirdAward> m_vecAwardList;
};

class NewYearChargeManager : public LazySingleton<NewYearChargeManager>
{
public:
	NewYearChargeManager();
	virtual ~NewYearChargeManager();

public:
	bool IsDuringAcivity();

	void setAlreadyAwardIndex(int alreadyAwardIndex);
	int getAlreadyAwardIndex();

	int getCurPlantIDFromServer();
	void setCurPlantID(int plantID);
	int getCurPlantID() const;

	int getNumWeeklyChargeCurrency() const;
	void setNumWeeklyChargeCurrency(int Currency);
	void addNumWeeklyChargeCurrency(int currency);

	bool GetConfig(NewYearChargeConfig& result);

	void CheckChargeAward();
	void CheckAlter();

	void addAward(const NewYearRewardData& rewards);
	std::vector<S2C_WechatReward> trimAwardData(const std::vector<S2C_WechatReward>& data);

private:
	bool isExistenceRewardData(const std::vector<S2C_WechatReward>& data, const S2C_WechatReward& dataReward) const;

	int m_nAlreadyAwardIndex;
	int m_nCurPlantID;
	int m_nNumWeeklyChargeCurrency;
};


#endif
