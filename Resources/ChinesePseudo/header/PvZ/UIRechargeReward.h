//
//  UIRechargeReward.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 17/5/15.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef _UIRechargeReward_h_
#define _UIRechargeReward_h_
#include "Widget.h"
#include "UISingletonDialog.h"
#include "RtObject.h"

struct RechargeRewardData
{
	RechargeRewardData()
	{
		Amount = 0;
		ObjectId = 0;
	}

	int Amount;
	int ObjectId;
};


class NDRechargeRewardConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(NDRechargeRewardConfig, RtObject, RtClass);
	NDRechargeRewardConfig() {}

public:
	int canAwardTimes = 0;
	int maxAwardTimes = 0;
	int activityDays = 0;
	std::vector<RechargeRewardData> Bonus;
};


class NDRechargeRewardContent : public Sexy::Widget
{
public:

	NDRechargeRewardContent(const RechargeRewardData & data);
	virtual ~NDRechargeRewardContent();

	virtual void	Draw(Sexy::Graphics* i_g);
	virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

private:

	void            setupScreen();

private:

	RechargeRewardData  m_data;
};

class UIRechargeReward : public UISingletonDialog<UIRechargeReward>
{
public:
	UIRechargeReward();
	virtual ~UIRechargeReward();
	virtual bool                OnCreate() override;
	// virtual std::string         GetLayoutName() override { return "UIRechargeReward"; } // this is used in festival event
	virtual std::string         GetLayoutName() override { return "UIRechargeRewardWoldMap"; } // this is used in world map
    virtual void                Draw(Sexy::Graphics* i_g) override;
	virtual void                DrawOverlay(Graphics* i_g) override;
	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	std::string                 getAwardResName(int objectId);

	bool loadData();

	void showGemStore();
	void UpdateTimeLabel();

	Sexy::Rect m_timeLebelRect;
	Sexy::Rect m_timeImageRect;
	void updateUIData();
	void clearPLantChipUI();
	virtual void        Update() override;
private:
	ImagePtr m_plantImage;
	ImagePtr m_ActivityTimeImage;
	NDRechargeRewardConfig  m_rechargeRewardConfig;
	Color m_timeColor = Color::White;
	SexyString m_timeLebal;
	std::vector<NDRechargeRewardContent*> m_vecContent;
	class UIWidgetText* m_pTextRefresTime;
};

#endif /* defined(__PlantsVersusZombies2__DaveClubUI__) */
