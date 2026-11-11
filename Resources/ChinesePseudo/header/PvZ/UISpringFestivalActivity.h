//
//  UISpringFestivalActivity.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 17/5/15.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef _UISpringFestivalActivity_h_
#define _UISpringFestivalActivity_h_

#include "UISingletonDialog.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "NetworkData.h"
#include "PVZ2UIButton.h"
#include "UIRewardFrame.h"
#include "GameCommon.h"

struct stSpringRewardInfo
{
	stSpringRewardInfo() : m_nPlantID(0), m_tSustainedTime(0.f) {}
	int m_nPlantID;
	int m_tSustainedTime;
};

struct stExperPlantInfo
{
	stExperPlantInfo() : m_nPlantID(0), m_tEndTime(0.f) {}
	int m_nPlantID;
	time_t m_tEndTime;
};

struct stExPlantData
{
	stExPlantData() : m_nPlantID(0), m_nPrice(0) {}
	int m_nPlantID;
	int m_nPrice;
};

struct ExpPlantLoginData
{
	ExpPlantLoginData(int i_sumdays, bool i_rewarded)
	{
		SumDays = i_sumdays;
		Rewarded = i_rewarded;
	}
	ExpPlantLoginData()
	{
		SumDays = 0;
		Rewarded = false;
	}
	int SumDays;
	bool Rewarded;
};

class SpringDailyLoginConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(SpringDailyLoginConfig, RtObject, RtClass);
	SpringDailyLoginConfig() : m_nAreadyAwardDay(0) {}
public:
	int m_nAreadyAwardDay;
	bool m_bIsRewardToday;
	std::vector<time_t> m_vecExpEndTime;
	std::vector<int> m_vecExperPlant;
	std::vector<std::vector<stSpringRewardInfo>>  m_vecRewardInfo;
	std::vector<stExPlantData> m_vecExperPlantData;
	stSpringRewardInfo m_stConversionGems;
	std::vector<int> m_vecAlreadyBuyExpPlants;
	std::vector<ExpPlantLoginData> m_loginConfigs;
};

class SpringLoginRewardContent : public UIRewardFrame
{
public:
	SpringLoginRewardContent(RewardType type, const std::string& reward, int rewardQuantity,bool bIsShowExp = true);
	virtual ~SpringLoginRewardContent();
	virtual void Draw(Sexy::Graphics* i_g) override;
private:
	bool m_bIsShowExp;	
};

class SpringAwardActivityWidget : public Widget, Sexy::ButtonListener
{
public:
	SpringAwardActivityWidget(int index, int alreadyAwardDaym, bool isAwardToday, std::vector<stSpringRewardInfo>& vecAwardItem, int i_requiredDays);
	virtual ~SpringAwardActivityWidget();

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
	std::vector<stSpringRewardInfo> m_vecAwardItem;
	int m_nAlreadyAwardDay;
	int m_nIndex;
	int m_requiredDays;
};

class SpringAwardActivityScrollPanel : public Widget, public ButtonListener
{
public:
	SpringAwardActivityScrollPanel(Sexy::Rect &i_rect, SpringDailyLoginConfig& bonus);
	virtual ~SpringAwardActivityScrollPanel();

	std::vector<SpringAwardActivityWidget *> GetDungeonList() { return m_dungeonList; }
	void RemoveAllDungeonWidget();
	void OnNotifySpringLoginReward(bool i_success, const S2C_7DaysLoginSpringReward* pData);
	void loadData(Sexy::Rect &i_rect, SpringDailyLoginConfig& bonus);
	void InitView();
	GAME_ITEM_INFO ProfileChangeItemAmountExpPlant(int nTypeId, int nDeltaAmount, bool bLocalGen);
private:
	std::vector<SpringAwardActivityWidget *> m_dungeonList;
	SpringDailyLoginConfig m_configInfo;
	Rect m_conRect;
};

class SpringDailyAwardUI : public UISingletonDialog<SpringDailyAwardUI>, public Sexy::ScrollWidgetListener
{
public:
	SpringDailyAwardUI();
	virtual ~SpringDailyAwardUI();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "SpringDailyAwardUI"; }
	//virtual void				DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* i_g) override;
	virtual void                Draw(Sexy::Graphics* i_g) override;
	virtual void                DrawOverlay(Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	// implement of Sexy::ScrollWidgetListener
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
	virtual void updateUIData();
	void Update() override;
	void UpdateTimeLabel();
private:

	class PVZ2UIScrollingWidget* m_daveClubScollingWdget;
	class SpringAwardActivityScrollPanel* m_dungeonScollingPanel;
	Sexy::Rect m_dungeonListScollRect;
	Sexy::Rect m_timeLebelRect;
	Sexy::Rect m_loginLabelRect;
	Sexy::Rect m_timeImageRect;
	Color m_timeColor = Color::White;
	SexyString m_timeLabel;
	SexyString m_loginLabel;
	ImagePtr m_ActivityTimeImage;
	
};

//-----------------------------------------------------------------
// UISpringBuyPlant
//-----------------------------------------------------------------
class UISpringBuyPlant : public UISingletonDialog<UISpringBuyPlant>
{
public:
	UISpringBuyPlant();
	virtual ~UISpringBuyPlant();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UISpringBuyPlant"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	void onUseGemFinish(const bool& isSuccess);
	void initUI();
	void setPlantID(int plantID);

	void OnNotifyBuyPlant(bool i_success, int plantID);
private:
	int m_nPlantID; 
};

//-----------------------------------------------------------------
// SpringChargeManager
//-----------------------------------------------------------------
class SpringChargeManager : public LazySingleton<SpringChargeManager>
{
public:
	SpringChargeManager();
	virtual ~SpringChargeManager();
	void loadData(const SpringDailyLoginConfig& m_configInfo);
	void eraseExpPlantInfoByID(int plantID);

	time_t getEndTimeByPlantId(int plantID);
	bool isHaveExpPlantID(int plantID);
	void setEndTimeByPlantId(int plantID, time_t time);
	bool isPlantAlreadyBuy(int plantID);
	int getExChangeGem() const;
	int getExChangePrice(int plantID) const;
	void eraseNotBuyExpPlants(int plantID);
	void addAlreadyBuyPlant(int plantID);
	void updateExpPlants();
	bool isExpPlantUseful(int plantID);
	void onSaveDialogOK();
	std::vector<int> GetCurrentLoginLevel();
	void UpdateLoginDatas(const std::vector<ExpPlantLoginConfig>& i_loginDatas);
	void InitTestData();
	std::vector<ExpPlantLoginData> GetLoginDatas() { return m_logindatas; }
	int GetTargetRequiredDays(int i_index);
	void UpdateBehaviorEventLog();
	void UpdateBehaviorPurchaseLog(int i_plantId);
private:
	std::vector<stExperPlantInfo> m_vecExperPlantInfo;
	std::vector<int> m_vecAlreadyBuyExpPlants;
	int m_enExChangeGem;
	std::vector<stExPlantData> m_vecExperPlantData;
	std::vector<ExpPlantLoginData> m_logindatas;
	SpringDailyLoginConfig m_configInfo;
	int m_currentExpiredPlantId;
};

class ExpPlantRewardView : public Sexy::Widget, Sexy::ButtonListener
{
public:

	ExpPlantRewardView(const std::string& i_plantName);
    ~ExpPlantRewardView();

    virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	void InitView();
private:
	const std::string GetLevelIconString(int i_level);
	std::string m_plantName;
	int m_level;
	Image* m_plantImg;
	Rect m_plantImgRect;
	Image* m_plantBg;
	Rect m_plantBgRect;
	PVZ2UIButton* m_confirmButton;
	Rect m_dialogRect;
};

#endif
