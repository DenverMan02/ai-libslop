//
//  NDDailyAwardUI.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/10/23.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__NDDailyAwardUI__
#define __PlantsVersusZombies2__NDDailyAwardUI__

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "ProfileMgr.h"
#include "MagentoService.h"
#include "PlantAdventureConfig.h"
#include "BoxOpenUI.h"
#include "PopingWidget.h"
#include "UISingletonDialog.h"

class DailyAwardActivityWidget : public Widget, Sexy::ButtonListener
{
public:
	DailyAwardActivityWidget(int index, int alreadyAwardDaym, bool isAwardToday, std::vector<NDLoginRewardBonus>& vecAwardItem);
	virtual ~DailyAwardActivityWidget();

	virtual void Resize(const Rect& theRect) override;
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

class DailyAwardActivityScrollPanel : public Widget, public ButtonListener
{
public:
	DailyAwardActivityScrollPanel(Sexy::Rect &i_rect, DailyAwardBonus& bonus);
	virtual ~DailyAwardActivityScrollPanel();

	std::vector<DailyAwardActivityWidget *> GetDungeonList() { return m_dungeonList; }
	void RemoveAllDungeonWidget();
	void OnNotify7DaysLoginReward(bool i_success, const S2C_7DaysLoginReward* pData);
	void loadData(Rect &i_rect, DailyAwardBonus& bonus);
	void InitView();
private:
	std::vector<DailyAwardActivityWidget *> m_dungeonList;
	DailyAwardBonus m_Bonus;
};

class NDDailyAwardUI : public UISingletonDialog<NDDailyAwardUI>, public Sexy::ScrollWidgetListener
{
public:
	NDDailyAwardUI();
	virtual ~NDDailyAwardUI();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "NDDailyAwardUI"; }
	virtual void                Draw(Sexy::Graphics* i_g) override;
	virtual void                DrawOverlay(Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	// implement of Sexy::ScrollWidgetListener
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
	void loadData();
	void updateUIData();
	virtual void	Update();
	void UpdateTimeLabel();
private:

	PVZ2UIScrollingWidget* m_daveClubScollingWdget;
	DailyAwardActivityScrollPanel* m_dungeonScollingPanel;
	Sexy::Rect m_dungeonListScollRect;
	Sexy::Rect m_timeLebelRect;
	Sexy::Rect m_timeImageRect;
	DailyAwardBonus m_Bonus;
	Color m_timeColor = Color::White;
	SexyString m_timeLebal;
	ImagePtr m_ActivityTimeImage;
};


class DaliyLoginRewardContent : public Sexy::Widget
{
public:
	DaliyLoginRewardContent(const NDLoginRewardBonus & data);
	virtual ~DaliyLoginRewardContent();

	virtual void	Draw(Sexy::Graphics* i_g);
	virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

private:
	void            setupScreen();
private:
	NDLoginRewardBonus  m_data;
};


class NDDailyLoginRewardView : public Sexy::Widget, Sexy::ButtonListener
{
public:

	NDDailyLoginRewardView(const std::vector<NDLoginRewardBonus>& i_rewardList);
	~NDDailyLoginRewardView();

	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
	virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

	virtual void	ButtonDepress(int i_id);

	void InitView();

private:
	std::vector<NDLoginRewardBonus> m_rewardList;
	SexyString m_contentStr;
	PVZ2UIButton* m_getRewardBtn;

	void onRewardGot();
};


class DailyAwardConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(DailyAwardConfig, RtObject, RtClass);
	DailyAwardConfig() {}

public:
	DailyAwardBonus Bonus;
	
};

#endif /* defined(__PlantsVersusZombies2__NDDailyAwardUI__) */
