//
//  UIMiniGameEntrance.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 17/5/15.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef _UIMiniGameEntrance_h_
#define _UIMiniGameEntrance_h_

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "UIMessageBox.h"

struct stMiniGame_Bonus
{
	int m_nId = 0;
	int m_nNum = 0;
};

struct stMiniGame_rank
{
	int m_nStartRank = 0;
	int m_nEedRank = 0;
	std::vector<stMiniGame_Bonus>MiniGame_Bonus;
};



class UIMiniGameEntrance : public UISingletonDialog<UIMiniGameEntrance>
{
public:
	UIMiniGameEntrance();
	virtual ~UIMiniGameEntrance();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIMiniGameEntrance"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	void OnMessageCallback(UIMessageBox* box, int buttonID);
	void onFinishBuyChallengeCount(const bool& i_Success);

	void                onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
	void showOpenErrorDialog();
private:
	void refrashCC(int times);
	int m_nMaxBuyTimes;
	int m_buyTimeCost;// for tga log
};


class UIMiniGameRule : public UISingletonDialog<UIMiniGameRule>, public Sexy::ScrollWidgetListener
{
public:
	UIMiniGameRule();
	virtual ~UIMiniGameRule();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "MiniGameRule"; }
	virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	virtual void							ScrollTargetReached(ScrollWidget* scrollWidget) {}
	virtual void							ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}

private:
	std::vector<stMiniGame_rank> m_vecRankInfo;
};

class MiniGameConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(MiniGameConfig, RtObject, RtClass);
	MiniGameConfig() {}

public:
	int m_nCurStage;
	int m_nLeftChance;
	int m_nCurDay;
	std::vector<stMiniGame_rank> m_vecRank;
	std::vector<int> m_vecChanceCost;
	int m_nArealdyBuyTimes;
	int m_nMaxBuyTimes;
};

//-----------------------------------------------------------------
// MiniGameManager
//-----------------------------------------------------------------
class MiniGameManager : public LazySingleton<MiniGameManager>
{
public:
	MiniGameManager();
	virtual ~MiniGameManager();
	void setSelectIndex(int nSelectIndex);
	int getSelectIndex() const;
	void setLeftBuyChance(int leftBuyChance);
	void subtractLeftBuyChance(int subtractNum);
	int getLeftBuyChance();
	void setLeftChellengeChance(int leftChellengeChance);
	void subtractLeftChellengeChance(int subtractNum);
	void addLeftChellengeChance(int addNum);
	int getLeftChellengeChance();


	void setChanceCost(const std::vector<int>& vecChanceCost);
	std::vector<int> getChanceCost() const;
	void loadData();
	void RequestBuyMiniGameChallenge(int id, int count);

	int getMiniGameCurCost();

	void setSecondStagescore(int score);
	int getSecondStagescore() const;

	void setMaxBuyTimes(int maxBuyTimes);
	int getMaxBuyTimes() const;

public:
	int m_nSelectIndex;
	int m_nLeftBuyChance;
	int m_nLeftChellengeChance;
	std::vector<int> m_vecChanceCost;
private:
	int m_nSecondStagescore;
	int m_nMaxBuyTimes;
};


#endif
