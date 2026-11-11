/*
 * DailySignActivity.h
 *
 *  Created on: 2018-10-29
 *      Author: Administrator
 */

#ifndef DAILYSIGNACTIVITY_H_
#define DAILYSIGNACTIVITY_H_

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
#include "EASquared.h"

namespace Message
{
	void UpdateSumDays(int i_days);
}

struct DailySignBonus
{
	int alreadyAwardDay = 0;
	bool isRewardToday = false;
	std::string rewardTime;
	int curNationDay = 0;
	std::vector<std::vector<NDLoginRewardBonus>>  m_vecRewardBonus;
	int index = 0;
};

class DailySignActivityWidget : public Widget, Sexy::ButtonListener
{
public:
	DailySignActivityWidget(int index, int alreadyAwardDaym, bool isAwardToday, std::vector<NDLoginRewardBonus>& vecAwardItem);
	virtual ~DailySignActivityWidget();

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

class DailySignActivityScrollPanel : public Widget, public ButtonListener
{
public:
	DailySignActivityScrollPanel(Sexy::Rect &i_rect, DailySignBonus& bonus);
	virtual ~DailySignActivityScrollPanel();

	std::vector<DailySignActivityWidget *> GetDungeonList() { return m_dungeonList; }
	void RemoveAllDungeonWidget();
	void OnNotify7DaysLoginReward(bool i_success, const S2C_7DaysLoginReward* pData);
	void loadData(Rect &i_rect, DailySignBonus& bonus);
	void InitView();
private:
	std::vector<DailySignActivityWidget *> m_dungeonList;
	DailySignBonus m_Bonus;
};

class DailySignUI : public UISingletonDialog<DailySignUI>, public Sexy::ScrollWidgetListener
{
public:
	DailySignUI();
	virtual ~DailySignUI();
	virtual bool                OnCreate() override;
	bool						OnCreatePage();
	virtual std::string         GetLayoutName() override { return m_layout; }
	virtual void                Draw(Sexy::Graphics* i_g) override;
	virtual void				DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g) override;
	virtual void                DrawOverlay(Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	// implement of Sexy::ScrollWidgetListener
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
	void loadData();
	void updateUIData();
	void updateUIPage();
	virtual void	Update();
	void UpdateTimeLabel();

	static void RequestNetwork(bool i_showDialog);
	static void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	static DailySignUI* ShowPage(const std::string& layout);

	void OnUpdateSumDays(int i_days);

private:
	PVZ2UIScrollingWidget* m_daveClubScollingWdget;
	DailySignActivityScrollPanel* m_dungeonScollingPanel;
	Sexy::Rect m_dungeonListScollRect;
	Sexy::Rect m_timeLebelRect;
	Sexy::Rect m_timeImageRect;
	DailySignBonus m_Bonus;
	Color m_timeColor = Color::White;
	SexyString m_timeLebal;
	ImagePtr m_ActivityTimeImage;
	// gray bg
	Image* m_grayBg;
	Rect m_grayBgRect;
	// time bg
	Image* m_timeBg;
	Rect m_timeBgRect;
	// sum bg
	Image* m_sumBg;
	Rect m_sumBgRect;
	SexyString m_sumLabel;
	Rect m_sumRect;
	std::string m_layout;
	static bool s_requested;
	bool m_isPage;
};


class DaliySignRewardContent : public Sexy::Widget
{
public:
	DaliySignRewardContent(const NDLoginRewardBonus & data);
	virtual ~DaliySignRewardContent();

	virtual void	Draw(Sexy::Graphics* i_g);
	virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

	virtual void 	TouchBegan( const Sexy::Touch& i_touch ) override;
    virtual void 	TouchEnded( const Sexy::Touch& i_touch ) override;
	virtual void	TouchesCanceled() override;

private:
	void            setupScreen();
private:
	NDLoginRewardBonus  			m_data;
	SexyString 						m_description;
	class StoneLotteryItemTipUI* 	m_tipUI;
};


class DailySignRewardView : public Sexy::Widget, Sexy::ButtonListener
{
public:

	DailySignRewardView(const std::vector<NDLoginRewardBonus>& i_rewardList);
	~DailySignRewardView();

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


class DailySignConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(DailySignConfig, RtObject, RtClass);
	DailySignConfig() {}

public:
	int ShowInEvent;
	DailySignBonus Bonus;
	std::string Key;

};


#endif /* DAILYSIGNACTIVITY_H_ */
