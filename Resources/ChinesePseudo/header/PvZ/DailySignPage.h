/*
 * DailySignActivity.h
 *
 *  Created on: 2018-10-29
 *      Author: Administrator
 */

#ifndef DAILYSIGNPAGE_H_
#define DAILYSIGNPAGE_H_

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "ProfileMgr.h"
#include "UISingletonDialog.h"
#include "NetworkData.h"

namespace Message
{
	void NotifyPiggyBankRewardGot(bool success);
}

class PiggyBankRewardData: public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(PiggyBankRewardData, RtObject, RtClass);

	int canAwardDay = 0;
	std::vector<int> alreadyAwardDay;
	std::vector<S2C_DailySignContent>  m_vecRewardList;
};

class DailySignBanner : public Widget, public Sexy::ButtonListener
{
public:
	DailySignBanner(int day, bool canGot, bool hasGot, const S2C_DailySignContent& vecAwardItem, Sexy::Rect size);
	virtual ~DailySignBanner();

	void ButtonDepress(int i_id) override;
	void Draw(Sexy::Graphics* i_g) override;

	void UpdateUI(bool canGot, bool hasGot);

protected:
	void onGotReward(bool success);

protected:
	int m_day;
	PVZ2UIButton* m_GotBtn;
	UIWidgetImage* m_pUIWidgetImage;
	bool m_wait_for_response;
};

class DailySignBannerNew  : public Widget, public Sexy::ButtonListener
{
public:
	DailySignBannerNew(int day, bool canGot, bool hasGot, const S2C_DailySignContent& vecAwardItem, Sexy::Rect size);
	virtual ~DailySignBannerNew();

	void ButtonDepress(int i_id) override;
	void Draw(Sexy::Graphics* i_g) override;

	void UpdateUI(bool canGot, bool hasGot);

protected:
	void onGotReward(bool success);

protected:
	int m_day;
	PVZ2UIButton* m_GotBtn;
	UIWidgetImage* m_pUIWidgetImage;
	bool m_wait_for_response;
	bool m_canGot;
	bool m_hasGot;
	Rect m_frameRect;
};

class DailySignPage : public UISingletonDialog<DailySignPage>, public Sexy::ScrollWidgetListener
{
public:
	DailySignPage();
	virtual ~DailySignPage();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "DailySignPage"; }

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	// implement of Sexy::ScrollWidgetListener
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
	void loadData();
	void updateUIData();
	void UpdateTimeLabel();

protected:
	void InitView();
	void onBuyPiggyBank(bool success, int shop);

private:

	PVZ2UIScrollingWidget* m_scollingWdget;
	Sexy::Rect m_scollingRect;
	PiggyBankRewardData  m_piggyBankRewradData;
	UIWidgetText* m_pTimeTxt;
	time_t m_expireTime;
	bool m_canBuy;
	std::vector<DailySignBanner*> m_banners;
};


#endif /* DAILYSIGNPAGE_H_ */
