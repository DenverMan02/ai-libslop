//
//  UIMiniGameRank.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 17/5/15.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef _UIMiniGameRank_h_
#define _UIMiniGameRank_h_

#include "UISingletonDialog.h"
#include "gameNetWork/NetworkData.h"

struct stMiniGame_rankItemInfo
{
	int m_nProfileID;
	int m_nRankOrder = 0;
	int m_nScore = 0;
	int m_nHeadId = 0;
	std::string m_strName;
};

struct stMiniGameAward_Bonus
{
	int m_nId = 0;
	int m_nNum = 0;
};

class UIMiniGameRank : public UISingletonDialog<UIMiniGameRank>
{
public:
	UIMiniGameRank();
	virtual ~UIMiniGameRank();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIMiniGameRank"; }
	virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

private:
	UIScrollControl* m_pScrollToday;
	UIScrollControl* m_pScrollMonth;
	class LoadingWidget* m_pDayLoading;
	class LoadingWidget* m_pMonthLoading;
};


class UIMiniGameRankAward : public UISingletonDialog<UIMiniGameRankAward>
{
public:
	UIMiniGameRankAward();
	virtual ~UIMiniGameRankAward();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "MiniGameReward"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	void loadData(const std::vector<stMiniGameAward_Bonus>& info, int rank, std::string strPeriod);
	void initView();
	int getMiniCoinNum() const;
private:
	void OnRequestBossRewardEnd(bool i_success);
	std::vector<stMiniGameAward_Bonus> m_vecMiniGameAward;
	int m_nRank;
	std::string m_strPeriod;
};


class ChristmasChargeReward : public UISingletonDialog<ChristmasChargeReward>
{
public:
	ChristmasChargeReward();
	virtual ~ChristmasChargeReward();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "ChristmasChargeReward"; }
	virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	void loadData(const std::vector<S2C_WechatReward>& info);
	void initView();
private:
	std::vector<S2C_WechatReward> m_vecChristmasChargeAward;
};

class OppoNewerRechargeChargeReward : public UISingletonDialog<OppoNewerRechargeChargeReward>
{
public:
	OppoNewerRechargeChargeReward();
	virtual ~OppoNewerRechargeChargeReward();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "OppoNewerReChargeReward"; }
	virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	void loadData(const std::vector<S2C_WechatReward>& info);
	void initView();
private:
	std::vector<S2C_WechatReward> m_vecChristmasChargeAward;
};

class MiniGameRankRewardContent : public Sexy::Widget
{
public:
	MiniGameRankRewardContent(const NDLoginRewardBonus & data);
	virtual ~MiniGameRankRewardContent();

	virtual void	Draw(Sexy::Graphics* i_g);
	virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

private:
	void            setupScreen();
private:
	NDLoginRewardBonus  m_data;
};

class MiniGameRankItemConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(MiniGameRankItemConfig, RtObject, RtClass);
	MiniGameRankItemConfig() {}
public:
	std::vector<stMiniGame_rankItemInfo> m_vecRankItem;
	std::vector<stMiniGame_rankItemInfo> m_vecMonthRankItem;

	int m_nMyTodayRankOrder;
	int m_nMyTodayBest;
	int m_nLastMonthOrder;
	std::vector<stMiniGameAward_Bonus> m_vecMiniGameAward;
	int m_nMyMonthRankOrder;
	int m_nMyMonthBest;
	std::string m_strPeriod;
};


#endif
