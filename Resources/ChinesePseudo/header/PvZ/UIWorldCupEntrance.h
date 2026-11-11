//
//  UIWorldCupEntrance.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 17/5/15.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef _UIWorldCupEntrance_h_
#define _UIWorldCupEntrance_h_

#include "UISingletonDialog.h"
#include "UIMessageBox.h"
#include "UIWidget.h"

enum figth_result 
{
	fight_fail,
	fight_win,
	fight_drawgame
};

struct worldCupInfo
{
	int m_nTeamId;
	std::vector<int> m_vecTeamPlantID;
	int m_nSunCount;
	bool m_bIsUnLock;
};

struct wcAwardInfo
{
	int m_nAwardID;
	int m_nAmount;
};

struct st_resultInfo
{
	figth_result m_FightResult;
	int m_nMyScore;
	int m_nEnemyScore;
	int m_nTeamID;

	st_resultInfo() :
	m_FightResult(fight_win),
	m_nMyScore(0),
	m_nEnemyScore(0),
	m_nTeamID(0)
	{}
};

typedef std::vector<std::vector<wcAwardInfo>> vecWorldCupAward;

class UIWorldCupConfig : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(UIWorldCupConfig, RtObject, RtClass);
	UIWorldCupConfig() : m_nLeftTickets(0), m_nCurLoopNum(0), m_curTeamId(0),m_nMaxBuyTimes(0),m_nAlreadyBuyTimes(0) {}
public:
	vecWorldCupAward m_vecWorlcCupAward;
	std::vector<worldCupInfo> m_vecWorlcCupTeam;
	int m_nLeftTickets;
	int m_nCurLoopNum;
	int m_curTeamId;
	std::vector<int> m_vecTicketPrice;
	int m_nMaxBuyTimes;
	int m_nAlreadyBuyTimes;
	std::vector<int> m_vecPassByTeamID;
};


class UIWorldCupEntrance : public UISingletonDialog<UIWorldCupEntrance>
{
public:
	UIWorldCupEntrance();
	virtual ~UIWorldCupEntrance();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIWorldCup"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void    ButtonPress(int i_id) override;
	virtual void                ButtonDepress(int i_id) override;
	virtual void	ButtonMouseLeave(int i_id) override;
	void OnMessageCallback(UIMessageBox* box, int buttonID);
	void OnContinueGameMessageCallback(UIMessageBox* box, int buttonID);
	void OnNotifyBuyWCTicket(bool i_success);
	void onUseGemFinish(const bool& isSuccess);
	void updateTicketsUI();
	void showAwardIcon(int objectId, int amount, int index);
	void updateActivityTime();
	void hideCloseBtn();

	void showClearanceTip();
	void OnGameClearanceMessageCallback(UIMessageBox* box, int buttonID);
	void OnNotifyBeginGame(bool i_success);
	void OnMessageCallbackBuyTicket(UIMessageBox* box, int buttonID);

private:
    void showConfirmBackToMap();
    void onCancelBackToMap();
    void onConfirmBackToMap();
    PVZ2UIDialog* showExitMenu_Internal(SexyString i_headerLabel, SexyString i_messageBody);

private:
	// int m_nScore1;
	// int m_nScore2;
	int m_ticketCost;
};

class UIWorldCupSelectTeam : public UISingletonDialog<UIWorldCupSelectTeam>
{
public:
	UIWorldCupSelectTeam();
	virtual ~UIWorldCupSelectTeam();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UISelecteam"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	void updateSelectState(int index);
	void updatebuttonState();
	void OnNotifyBeginGame(bool i_success);
	void OnMessageCallback(UIMessageBox* box, int buttonID);

	void OnMessageCallbackUnLockTeam(UIMessageBox* box, int buttonID);
	void ShowUnlockTeamDialog(int teamID);

	void onUseGemFinish(const bool isSuccess);
	void OnNotifyUnlockWorldCupTeam(bool i_success);
	void updateUI();
private:
	int m_nCurTeamId;
	int m_nSelectedID;
};


class UIWorldCupEndLevel : public UISingletonDialog<UIWorldCupEndLevel>
{
public:
	UIWorldCupEndLevel();
	virtual ~UIWorldCupEndLevel();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIWorldCupEndLevel"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	void initUI(const st_resultInfo info);
	void backToMap();
	void showAwardIcon(int objectId, int amount, int index);
private:
	figth_result m_elFightResult;
};

class UIWorldCupRule : public UISingletonDialog<UIWorldCupRule>
{
public:
	UIWorldCupRule();
	virtual ~UIWorldCupRule();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIWorldCupRule"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	
private:
	
};

enum  state_scall{
	state_no,
	state_Big,
	state_small
};

//-----------------------------------------------------------------
// UIWorldCupScore
//-----------------------------------------------------------------
class UIWorldCupScore : public UIWidget
{
public:
	RT_CLASS_DEFINE(UIWorldCupScore, UIWidget, RtClass);
    UIWorldCupScore();
	void setScores(uint32 *plantScore, uint32 *enemyScore);
	virtual ~UIWorldCupScore();

	virtual void					Draw(Graphics* i_g) override;
	void setScoreState(int index, state_scall state);
	void setOldPlantScore(uint32 plantScore);
	void setOldEnemyScore(uint32 enemyScore);
	void checkAnimationState();
private:
	uint32 *m_plantScore;
	uint32 *m_enemyScore;
	pvztime_t m_stateChangeStartTime;
	float m_fScall[4];
	state_scall m_State[4];
	uint32 m_oldPlantScore;
	uint32 m_oldEnemyScore;
};

//-----------------------------------------------------------------
// WorldCupManager
//-----------------------------------------------------------------
class WorldCupManager : public LazySingleton<WorldCupManager>
{
public:
	WorldCupManager();
	void setIsFinish(bool isFinish);
	bool getIsFinish() const;
	bool loadData();
	int getSunByTeamID(int teamID) const;
	int getCurStageSunNum() const;
	std::vector<int> getTeamPlantByTeamID(int teamID) const;
	std::vector<int> getCurTeamPlantByTeamID() const;
	void addWorldCupTikets(int nTikets);
	void addBuyTicketTimes();
	void subscribeWorldCupTickets(int nTikets);
	bool canPlayWorldCupGame() const;
	int getWorldCupTickets() const;
	int getCurTicketPrice() const;
	bool isCanBuyTicketNow() const;
	int getCurLoopNum() const;
	void addCurLoopNum();
	const vecWorldCupAward& getVecWorlcCupAward() const; 
	int getCurTeamID() const;
	void setCurTeamID(int teamID);

	void setIsClearance(bool isClearance);
	bool getIsClearance() const;

 	const UIWorldCupConfig& getUIWorldCupConfig() const;
	bool getIsUnLockByTeamID(int teamID) const;
	void setIsUnLockByTeamID(int teamID, bool isLock);

	void SetAndShowUnlockTeamAleart(int teamID);

	void ClearData();
	void OnMessageCallback(UIMessageBox* box, int buttonID);

	void setIsQuit(bool isQuit);
	bool getIsQuit() const;

	bool isNeedConsumeTickets();

	void UpdateWorldCupTicketLog(int i_cost);
	void UpdateWorldCupEndGameLog(int i_teamId, bool i_win, int i_rewardIndex);
private:
	bool m_bIsFinish;
	UIWorldCupConfig m_configData;
	bool m_bIsClearance;
	bool m_bIsQuit;
};

#endif
