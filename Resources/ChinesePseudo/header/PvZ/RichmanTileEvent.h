/*
 * RichmanTileEvent.h
 *
 *  Created on: 2019-12-19
 *      Author: zhousen
 */

#ifndef RICHMANTILEEVENT_H_
#define RICHMANTILEEVENT_H_

#include "RtObject.h"
#include "RtSerial.h"
#include "RtDb.h"
#include "DRef.h"
#include "PVZDB.h"
#include "Singleton.h"
#include "NetworkData.h"
#include "GuessRatio.h"

class RichmanResultData : public INetworkData
{
public:
	RT_CLASS_DEFINE(RichmanResultData, INetworkData, RtClass);

public:
	std::vector<LotteryBonus> RewardList;
    int Step;
};

class RichmanTileEventConfig : public RtObject
{
public:
	RT_CLASS_DEFINE(RichmanTileEventConfig, RtObject, RtClass);
	RichmanTileEventConfig();
    RichmanTileEventConfig& operator=(const RichmanTileEventConfig& config);

    // richman tile event type
    RichmanTileEventType _tileEventType;

    // move (for random tiles)
    int _moveTileMin;
    int _moveTileMax;
    int _moveTileValue;

    // throw again(random value)
    int _throwMin;
    int _throwMax;
    int _throwValue;

    // start position reward & normal reward
    int _rewardID;
    int _rewardCount;

    // maybe this should be a vector
    std::vector<RichmanItemInfo> _rewardItemList;
    std::vector<RichmanItemInfo> _rewardChestList;

    // go to specify game
    std::vector<std::string> _levelNameList;
};

/// 
/// richman tile event
///

class RichmanTileEventBase 
{
public:
    RichmanTileEventBase(RichmanTileEventConfig& config){ _config = config; }
    virtual ~RichmanTileEventBase(){}
    // execute this event function
    virtual void ExecuteEvent(){ PostEventMessage(); }
    // execute this event function after battle or mini game
    virtual void ExecuteEventPost(){}
    // post message to run other module's function
    virtual void PostEventMessage(){}
    RichmanTileEventConfig GetConfig() const { return _config; }

protected:
    RichmanTileEventConfig _config;
};

class RichmanTileEvent_MoveForward : public RichmanTileEventBase
{
public:
    RichmanTileEvent_MoveForward(RichmanTileEventConfig& config);
    ~RichmanTileEvent_MoveForward();
    void ExecuteEvent() override;
    void ExecuteEventPost() override;
    void PostEventMessage() override;
};

class RichmanTileEvent_MoveBackward : public RichmanTileEventBase
{
public:
    RichmanTileEvent_MoveBackward(RichmanTileEventConfig& config);
    ~RichmanTileEvent_MoveBackward();
    void ExecuteEvent() override;
    void ExecuteEventPost() override;
    void PostEventMessage() override;
};

class RichmanTileEvent_ThrowAgain : public RichmanTileEventBase
{
public:
    RichmanTileEvent_ThrowAgain(RichmanTileEventConfig& config);
    ~RichmanTileEvent_ThrowAgain();
    void ExecuteEvent() override;
    void ExecuteEventPost() override;
    void PostEventMessage() override;
};

class RichmanTileEvent_Start : public RichmanTileEventBase
{
public:
    RichmanTileEvent_Start(RichmanTileEventConfig& config);
    ~RichmanTileEvent_Start();
    void ExecuteEvent() override;
    void ExecuteEventPost() override;
    void PostEventMessage() override;
};

class RichmanTileEvent_Reward : public RichmanTileEventBase
{
public:
    RichmanTileEvent_Reward(RichmanTileEventConfig& config);
    ~RichmanTileEvent_Reward();
    void ExecuteEvent() override;
    void ExecuteEventPost() override;
    void PostEventMessage() override;
};

/// detail reward event

class RichmanTileEvent_Reward_Big : public RichmanTileEvent_Reward
{
public:
    RichmanTileEvent_Reward_Big(RichmanTileEventConfig& config);
};

class RichmanTileEvent_Reward_Coin3 : public RichmanTileEvent_Reward
{
public:
    RichmanTileEvent_Reward_Coin3(RichmanTileEventConfig& config);
};

class RichmanTileEvent_Reward_Coin4 : public RichmanTileEvent_Reward
{
public:
    RichmanTileEvent_Reward_Coin4(RichmanTileEventConfig& config);
};

class RichmanTileEvent_Reward_PlantPiecesChest : public RichmanTileEvent_Reward
{
public:
    RichmanTileEvent_Reward_PlantPiecesChest(RichmanTileEventConfig& config);
};

class RichmanTileEvent_Reward_AvatarPiecesChest : public RichmanTileEvent_Reward
{
public:
    RichmanTileEvent_Reward_AvatarPiecesChest(RichmanTileEventConfig& config);
};

///

class RichmanTileEvent_MiniGame : public RichmanTileEventBase
{
public:
    RichmanTileEvent_MiniGame(RichmanTileEventConfig& config);
    ~RichmanTileEvent_MiniGame();
    void ExecuteEvent() override;
    void ExecuteEventPost() override;
    void PostEventMessage() override;

protected:
    void ShowEntryUI();
    void OnEscapeBtn();
    void OnEnterBtn();
};

class RichmanTileEvent_BossBattle : public RichmanTileEventBase
{
public:
    RichmanTileEvent_BossBattle(RichmanTileEventConfig& config);
    ~RichmanTileEvent_BossBattle();
    void ExecuteEvent() override;
    void ExecuteEventPost() override;
    void PostEventMessage() override;

protected:
    SexyString GetBossBattleDescription(std::string str);

    void ShowEntryUI(SexyString desc);
    void OnEscapeBtn();
    void OnEnterBtn();

protected:
    int _levelIndex;
    std::string _levelName;
    SexyString _levelTitleDescription;
};

class RichmanTileEvent_WorldLevel : public RichmanTileEventBase
{
public:
    RichmanTileEvent_WorldLevel(RichmanTileEventConfig& config);
    ~RichmanTileEvent_WorldLevel();
    void ExecuteEvent() override;
    void ExecuteEventPost() override;
    void PostEventMessage() override;

protected:
    void ShowEntryUI();
    void OnEscapeBtn();
    void OnEnterBtn();
};

class RichmanTileEvent_GuessGame : public RichmanTileEventBase
{
public:
    RichmanTileEvent_GuessGame(RichmanTileEventConfig& config);
    ~RichmanTileEvent_GuessGame();
    void ExecuteEvent() override;
    void ExecuteEventPost() override;
    void PostEventMessage() override;

    int GetGuessGameBet() const;
    void SetGuessGameResult(GuessResult result);
    GuessResult GetGuessGameResult() const;
    
protected:
    void ShowEntryUI(int coins);
    void ShowEscapeUI();
    void OnEscapeBtn();
    void OnEnterBtn_2();
    void OnEnterBtn_20();

    void OnCloseBtnCallback();

private:
    int _bet;
    GuessResult _result;
};


///
/// RichmanTileEvent Factory
///
class RichmanTileEventFactory
{
public:
    static RichmanTileEventBase* CreateTileEvent(RichmanTileEventConfig& config);
};

///
/// RichmanTileEventManager
/// 

// workflow : 
// get serialize json data to init event list
// after get server steps, run MoveSteps func to execute event.
// if event is boss battle, world level, mini game, we make event need be checked
// if need checked, then do execute event post after game battle.

class RichmanTileEventManager : public LazySingleton<RichmanTileEventManager>
{
public:
    RichmanTileEventManager();
    ~RichmanTileEventManager();

    bool InitTileEventList(std::vector<RichmanTileEventConfig> configs);// initialize events list
    void ResetTileEventList();// reset events list

    void SetCurrentIndex(int index) { _currentEventStep = index; }
    RichmanTileEventBase* GetCurrentTileEvent();// get current event ptr
    RichmanTileEventBase* GetTileEvent(int index);// get specific event ptr
    std::vector<RichmanTileEventBase*>& GetTileEvents();// get all tile events

    bool MoveSteps(int step, bool doExecute = true);// move steps in course, if should do execute func
    bool MoveIndexTile(int index, bool doExecute = true);// move index tile in course, if should od execute func
    void ExecuteEvent();// execute current event
    void ExecuteEventPost();// execute current event

    bool IsRoundOver();// if this round is over
    bool IsEventNeedChecked();// if current event need to be checked
    bool IsBattleEvent();// if current event it is battle event

    void SetEventNeedChecked(bool needChecked);// set event need checked

    void SetMoveTileIndex(int index);// get tile index from server, cached
    int  GetMoveTileIndex();

    void FillRewardList(std::vector<RichmanItemInfo> list);// get rewards from server
    std::vector<RichmanItemInfo>& GetRewardList();

    // event_type : 
    // 3 = minigame, worldlevel, boss battle, sent when boss battle failed 
    // 4 = guess game, guess result 1 : win 2 : lose 3 : draw, betCoins 2 or 20?
    // 5 = move forward
    // 6 = move backward
    void RequestRichmanProtocol(int event_type, int guessResult = 0, int betCoins = 0);

private:
    void ClearEventList();

private:
    bool _isRoundOver;// check this round is over
    bool _eventNeedChecked;// if current event need to be checked after board battle eg.(world level, boss battle, mini game)
    int _currentEventStep;// current event step
    std::vector<RichmanTileEventBase*> _courseEventList;// all events course
    int _moveTileIndex;// from server
    std::vector<RichmanItemInfo> _rewardList;// cached reward list from server
};



#endif /* RICHMANTILEEVENT_H_ */
