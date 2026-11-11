/*
 * RichManUIMgr.h
 *
 *  Created on: 2019-12-20
 *      Author: Administrator
 */

#ifndef RICHMANUIMGR_H_
#define RICHMANUIMGR_H_

#include "Precompile.h"
#include "RtObject.h"
#include "Singleton.h"
#include "Core.h"
#include "NetworkData.h"

namespace Message
{
    void NotifySetDice();
}

struct EventUIEntryConfig
{
	EventUIEntryConfig()
	{
		Header = "";
		Description = "";
		IconImage = "";
		BackgroundImage = "";
	}

	std::string Header;
	std::string Description;
	std::string IconImage;
	std::string BackgroundImage;
};

struct EventUIConfig
{
    int EventId;
    EventUIEntryConfig Config;

    EventUIConfig()
    {
    	EventId = 0;
    }
};

struct EventBoardConfig
{
	EventBoardConfig()
	{
		NumOfColumns = 0;
		NumOfRows = 0;
		Gap = 0;
		InitialX = 0;
		InitialY = 0;
	}

	int NumOfColumns;
	int NumOfRows;
	int Gap;
	int InitialX;
	int InitialY;
};

struct PieceConfig
{
	SexyVector2 ArtCenter;
	int TurnRightNode;
	int TurnLeftNode;
};

class NetworkRichManConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(NetworkRichManConfig, Sexy::RtObject, Sexy::RtClass);

public:
    std::vector<class RichmanTileEventConfig> eventConfigs;
    int currentPosition;
    int currentDice;
    std::vector<class S2C_BonusInfo> rewardPreview;
};

struct EventReward
{
	EventReward()
	{
		ObjectId = 0;
		Quantity = 0;
	}

	int ObjectId;
	int Quantity;
};

class New_S2C_MoveResult : public INetworkData
{
public:
    RT_CLASS_DEFINE(New_S2C_MoveResult, INetworkData, RtClass);

    int m_leftDice;
    int m_locationIndex;
    std::vector<EventReward> m_rewards;
    std::vector<class RichmanTileEventConfig> m_events;
    int m_type;
};

class EventUIPropertySheet : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(EventUIPropertySheet, Sexy::RtObject, RtClass);

    EventUIPropertySheet();
    ~EventUIPropertySheet();

    void Init();

    const EventUIEntryConfig& GetEventUIEntryConfigByIndex(int i_index);
    const EventUIEntryConfig& GetEventUIEntryConfig(int i_eventId);
    int GetConfigSize();
    const EventBoardConfig& GetEventBoardConfig();
    const PieceConfig& GetPieceConfig();

private:
    std::vector<EventUIConfig> m_eventUIConfigs;
    EventBoardConfig m_boardConfig;
    PieceConfig m_pieceConfig;
};

struct EventConfig
{
	EventConfig()
	{
		EventId = 0;
		Index = 0;
	}

	int EventId;
	int Index;
};

class RichManUIMgr : public LazySingleton <RichManUIMgr>
{
public:
	RichManUIMgr();
    ~RichManUIMgr();

    void RequestNetwork();
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    const EventUIEntryConfig& GetEventUIEntryConfigByIndex(int i_index);
    const EventUIEntryConfig& GetEventUIEntryConfig(int i_eventId);
    int GetEventConfigSize();
    const EventBoardConfig& GetEventBoardConfig();
    const PieceConfig& GetPieceConfig();
    void SetScreen(class AdaptorRichManScreen* i_screen) { m_screen = i_screen; }
    void UnloadScreen() { m_screen = NULL; }

    // chess
    void RequestRollDice(int i_num);
    void CheatDice();
    void CheatJumpPiece(const Point& i_loc);
    void CheatRoll();
    void CheatResetBoard();
    Point GetStartLocation();
    int DecideNextRoll();
    int GetNextRoll();
    void GetNextLocation(std::vector<Point>& i_locations, int i_current, bool i_reverse = false);
    bool IsCurrentNodeFacingLeft();

    void AddNode(int i_index, Point i_loc);
    Point GetNode(int i_index);
    int GetCurrentNodeIndex() { return m_prevNode; }

    int GetLeftDice();
    void SetLeftDice(int i_left);
    void SetCurrentRewards(const std::vector<EventReward>& i_rewards);
    const std::vector<EventConfig>& GetEventConfigs() { return m_eventConfigs; }

    std::string GetScreenType();

    class AdaptorRichManBoard* GetBoard();
private:
    void Init();
    void Reset();
    void onRichmanDiceShopBuyFinish(int i_amount);
    void onNotifyBoardSetup();
    void onNotifyMovingFinish(bool i_handleEvent);
    void SetPrevNode(int i_index);
    void SetCurrentNode(int i_index);
    void handleEvent();
    void InitTestData(int i_eventId);
    void InitNetworkData();
    bool SyncActivityData(const NetworkRichManConfig& i_info);
    bool SetEvents(const std::vector<class RichmanTileEventConfig>& i_events);
    void onMoveResult(const New_S2C_MoveResult& i_result);
    void ResetPieceLocation(const Point& i_loc);
    void ShowBonusRewards(const std::vector<EventReward>& i_rewards);

    //events callback
    void onTileEvent_MoveForward_Index_Post(int index);
    void onTileEvent_MoveBackward_Index_Post(int index);
    void onTileEvent_Start_Post();
    void onTileEvent_Reward_Post();
    void onTileEvent_GuessGame_Post(int bet, int result);
    void onTileEvent_ThrowAgain(int min, int max);
    void onTileEvent_MiniGame_Post();
    void onTileEvent_BossBattle_Post();
    void onTileEvent_WorldLevel_Post();
    void handleMoveEvent(bool i_reverse, int i_index);

    EventUIPropertySheet m_eventConfig;
    class AdaptorRichManScreen* m_screen;
    std::map<int, Point> m_nodes;
    int m_prevNode;
    int m_currentNode;
    int m_currentDice;
    std::vector<EventConfig> m_eventConfigs;
    NetworkRichManConfig m_networkInfo;
    bool m_requested;
};

#endif /* RICHMANUIMGR_H_ */
