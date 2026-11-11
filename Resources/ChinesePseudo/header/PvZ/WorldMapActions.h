//
//  WorldMapActions.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 4/5/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMapActions_h
#define PlantsVersusZombies2_WorldMapActions_h

#include "LuaEngine/lua_support/LuaDef.h"
#include "WorldMap.h"
#include "GameEventMgr.h"
#include "EASquared.h"
#ifdef HOST_ANDROID
#include "drivers/purchase/android/IPurchaseAdapter.h"
#endif

// Base class for the WorldMapAction types. All actions
// will have their start function called, update will run
// every update frame, and at the end of the update, if the
// action is finished, the end function will be called
// and it will be popped off the action stack
//-----------------------------------------------------------------


class WorldMapAction : public RtObject
{
public:
    RT_CLASS_DEFINE(WorldMapAction, RtObject, RtClass) {}
    static WorldMapAction* CreateIfNeed(bool& hasTutorial)
    {
        DBG_ASSERT_MSG(false, "Error called here!");
        
        return nullptr;
    }

	WorldMapAction()
	{
		m_type = ActionType_Unknown;
		m_started = false;
		m_isFinished = false;
		m_id = -1;
	};
	WorldMapAction(WorldMapActionType i_type)
	{
		m_type = i_type;
		m_started = false;
		m_isFinished = false;
		m_id = -1;
	};
	virtual ~WorldMapAction()
	{
		gMessageRouter->Unsubscribe(this);
	};

	void				Init()
	{
        m_started = true;
		Start();
	};
	bool				IsStarted()
	{
		return m_started;
	}
	bool				IsActionFinished()
	{
		return m_isFinished;
	};
    void				SetIsFinished(bool i_isFinished)
    {
        m_isFinished = i_isFinished;
    };
    void				SetType(WorldMapActionType i_type)
    {
    	m_type = i_type;
    };
    void				SetId(int i_id)
    {
    	m_id = i_id;
    };
    const int 			GetId() const
    {
    	return m_id;
    };

	virtual void		Start()					{};
	virtual void		Update()				{};
	virtual void		End()					{};
	virtual void		OnWorldMapStateChange(WorldMapState i_newState) {};
	
	void				DisableInput();
	void				RestorePrevInput();
    std::string     GetActionName();
    WorldMapActionType	GetType()
    {
    	return m_type;
    };

protected:

	bool				m_started;
	bool				m_isFinished;
	bool				m_prevInput;
	WorldMapActionType  m_type;
	int					m_id;
};

//-----------------------------------------------------------------
// Enables or disables user input on the world map.
class ActionAllowUserInput: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionAllowUserInput, WorldMapAction, RtClass) {}
    static ActionAllowUserInput* CreateIfNeed(bool& hasTutorial, bool i_allowInput);
    
    ActionAllowUserInput() {}
	ActionAllowUserInput(const bool i_allowInput)
	{
		m_allowInput = i_allowInput;
	};

	virtual void		Start() override;

	// Public member variables
	
	bool				m_allowInput = true;
};

//-----------------------------------------------------------------
// Enables or disables user input on the world map.
class ActionDelay: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionDelay, WorldMapAction, RtClass) {}
    static ActionDelay* CreateIfNeed(const pvztime_t i_delayTime);

    ActionDelay() {}
	ActionDelay(const pvztime_t i_delayTime)
	{
		m_delayTime = i_delayTime;
	};

	virtual void		Start() override;
	virtual void		Update() override;

	// Public member variables
	
	pvztime_t			m_delayTime = 0;
};

//-----------------------------------------------------------------
class ActionCenterCameraOnPoint: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionCenterCameraOnPoint, WorldMapAction, RtClass) {}
    ActionCenterCameraOnPoint() {}
	ActionCenterCameraOnPoint(const Sexy::FPoint i_centerPoint)
	{
		m_centerPoint = i_centerPoint;
	};

	virtual void		Start() override;

	// Public member variables
	
	Sexy::FPoint		m_centerPoint;
};

//-----------------------------------------------------------------
// Sets and shows the advice text on the world map for the specifed amount
// of time, with input disabled
class ActionShowAdvice: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionShowAdvice, WorldMapAction, RtClass) {}
    ActionShowAdvice() {}
	ActionShowAdvice(SexyString i_adviceText, pvztime_t i_adviceDuration = 3.0f)
	{
		m_adviceText = i_adviceText;
		m_adviceEndTime = i_adviceDuration;
	};

	virtual void		Start() override;
	virtual void		Update() override;
	virtual void		End() override;

	// Public member variables
	
	SexyString			m_adviceText;
	pvztime_t			m_adviceEndTime = 0;
};

//-----------------------------------------------------------------
// Runs the unlocking node animations on the world map. When
// all of the nodes are done unlocking, we are finished with
// the action
class ActionUnlockNodesSequence: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionUnlockNodesSequence, WorldMapAction, RtClass) {}
    
    static ActionUnlockNodesSequence* CreateIfNeed(bool& hasTutorial);
    
    ActionUnlockNodesSequence();
    ActionUnlockNodesSequence(const std::string& i_originEventName);
    virtual ~ActionUnlockNodesSequence();
    
    // Called manually to put the worldmap in a good pre-unlock state.
    void PerformInstantSetup();
    
    // Starts the unlocking process
    void Start() override;
    void Update() override;
    void End() override;
    
protected:
    void onNotifyLoadedWorldResources();
    
private:
    void setupNodesForUnlock(const MapEventItem* i_sourceEvent);
    void setupMapPathForUnlock(MapPathGroup* i_mapPathGroup);
    
    void				onMapPathStarted();
    void				onMapPathEnded();
    
    int					m_activePaths = 0;
    
    std::string			m_originEventName;
    bool				m_suppressNodeUnlockCascading = false;
    
};

//-----------------------------------------------------------------
// Looks at the state of the Zomboss island and plays the appropriate Zomboss hologram,
// or starts random 'teaser' animation cycles
class ActionShowZombossHologram : public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionShowZombossHologram, WorldMapAction, RtClass) {}
    
    ActionShowZombossHologram()
    : m_zombossRig(nullptr)
    {}
    
    ActionShowZombossHologram(class EffectAnimRig_ZombossHologram* i_zombossRig)
    : m_zombossRig(i_zombossRig)
    {}
    
    void Start() override;
    
private:
    class EffectAnimRig_ZombossHologram* m_zombossRig;
};

//-----------------------------------------------------------------
// Runs the unlocking node animations on the world map. When
// all of the nodes are done unlocking, we are finished with
// the action
class ActionUnlockDangerRoomSequence: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionUnlockDangerRoomSequence, WorldMapAction, RtClass) {}
    
    ActionUnlockDangerRoomSequence();
    
    // Starts the unlocking process
    void Start() override;
    void End() override;
    
private:
    
    void				onDangerRoomAnimationFinished(const std::string &i_animName);
    
    std::string			m_cachedLastCompletedLevel;
    class PopAnimRig*	m_dangerRoomAnimRig;
    
};

//-----------------------------------------------------------------
// Checks if a Yeti needs to be spawned and handles it
class ActionCheckForAndSpawnYeti: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionCheckForAndSpawnYeti, WorldMapAction, RtClass) {}
    static ActionCheckForAndSpawnYeti* CreateIfNeed();

    ActionCheckForAndSpawnYeti() {}
	virtual void		Start() override;
};

//-----------------------------------------------------------------
class ActionCheckForShowReturnWorldKey:  public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionCheckForShowReturnWorldKey, WorldMapAction, RtClass) {}
    ActionCheckForShowReturnWorldKey() {}
    virtual void        Start() override;
private:
    void                OnBtnOk();
    
};

// Loads up the current specific world's resources
class ActionLoadCurrentWorldAssets: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionLoadCurrentWorldAssets, WorldMapAction, RtClass) {}
    
    static ActionLoadCurrentWorldAssets* CreateIfNeed(bool& hasTutorial);
    
    ActionLoadCurrentWorldAssets()
    {}
    
    void Start() override;
    void OnWorldMapStateChange(WorldMapState i_newState) override;
};

class ActionEnterTutorialCheck: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionEnterTutorialCheck, WorldMapAction, RtClass) {}
    static ActionEnterTutorialCheck* CreateIfNeed(bool& hasTutorial);
    ~ActionEnterTutorialCheck();

    virtual void Start() override;
    virtual void Update() override;
    virtual void End() override;
    void OnNotifyTutorialCheck(bool i_result);

    float m_timeOut = 0;
};

//--------------------------------------------------------------
// Enters the specified tutorial state
class ActionEnterTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionEnterTutorial, WorldMapAction, RtClass) {}
    static ActionEnterTutorial* CreateIfNeed(bool& hasTutorial);
	
    ActionEnterTutorial() {}
	ActionEnterTutorial(const std::string& i_eventName)
	{
		m_tutorialEventName = i_eventName;
		m_enterTutorialState = TUTORIAL_NONE;
	}
	ActionEnterTutorial(const MapTutorialState i_enterTutorialState)
	{
		m_tutorialEventName = "";
		m_enterTutorialState = i_enterTutorialState;
	}

	virtual void		Start() override;
	virtual void		End() override;
	
	void CheckSkipTutorial();

private:
	
	void				onTutorialFinished();
	static bool			isTutorialValid(MapTutorialState i_state);
	void onSkipTutorialOK(class UITutorialSkipDialog* i_dialog, int i_id);
	void onSkipTutorialCancel(class UITutorialSkipDialog* i_dialog, int i_id);
	void onSkippedTutorials();
	void onNotifyTutorialReward();
	void onNarrationFinished();
	
	std::string			m_tutorialEventName;
	MapTutorialState	m_enterTutorialState = TUTORIAL_NONE;
};

//-----------------------------------------------------------
class ActionStartNarrativeID: public WorldMapAction
{
public:
	typedef Delegate0 NarrativeFinishedDelegate;
	
    RT_CLASS_DEFINE(ActionStartNarrativeID, WorldMapAction, RtClass) {}
    static ActionStartNarrativeID* CreateIfNeed(bool& hasTutorial);
    
    ActionStartNarrativeID() {}
	ActionStartNarrativeID(const std::string& i_narrationID, const std::string& i_narrationStatusEvent, NarrativeFinishedDelegate i_onNarrativeFinishedDelegate = NarrativeFinishedDelegate())
	{
		m_narrationID = i_narrationID;
		m_narrationStatusEvent = i_narrationStatusEvent;
		m_onNarrationFinished = i_onNarrativeFinishedDelegate;
	}
	
	virtual void		Start() override;
	
private:
	
	void							onNarrationFinished();
	
	std::string						m_narrationID;
	std::string						m_narrationStatusEvent;
	NarrativeFinishedDelegate		m_onNarrationFinished;
};

//-----------------------------------------------------------
class ActionUnlockPlantHint: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionUnlockPlantHint, WorldMapAction, RtClass) {}
    
    ActionUnlockPlantHint() {}
	ActionUnlockPlantHint(PlantTypePtr i_plantType, int i_starNum)
	{
		m_plantType = i_plantType;
		m_starNum = i_starNum;
	}
	virtual void		Start() override;

private:
	PlantTypePtr m_plantType;
	int m_starNum = 0;
};

//-----------------------------------------------------------
class ActionNewerBagUI:  public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionNewerBagUI, WorldMapAction, RtClass) {}
    virtual void        Start() override;
};

//-----------------------------------------------------------
class ActionLoginReward: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionLoginReward, WorldMapAction, RtClass) {}
    static ActionLoginReward* CreateIfNeed(bool& hasTutorial);

	virtual void		Start() override;

private:
	void onLoginRewardDialogClosed();

};

//----------------------------------------------------------------------
class ActionShowBoardDlg: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionShowBoardDlg, WorldMapAction, RtClass) {}
    static ActionShowBoardDlg* CreateIfNeed(bool& hasTutorial);

    virtual void		Start() override;
    virtual void		Update() override;
    virtual void		End() override;
    
protected:
    void            onNotifyBoardInfoList(const class S2C_NoticeInfoList* pInfoList);
private:
    int     m_status = 0;
    float   m_timeOut = 0;
};

//----------------------------------------------------------------------
class ActionFestivalEntrancePrompt: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionFestivalEntrancePrompt, WorldMapAction, RtClass) {}
    
    ActionFestivalEntrancePrompt() {}
	ActionFestivalEntrancePrompt(float i_duration)
    {
		m_duration = i_duration;
	}

	virtual void		Start() override;

	float 			m_duration = 0;
};

//----------------------------------------------------------------------
class ActionPopupAlways: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionPopupAlways, WorldMapAction, RtClass) {}
    
    virtual void Start() override;
    
private:
    
    bool checkShowActiveEntrance();
    
    void onActivePopupUIClosed();
};

//----------------------------------------------------------------------
class ActionShowRatingDialog: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionShowRatingDialog, WorldMapAction, RtClass) {}
	
    virtual void		Start() override;
};

//-----------------------------------------------------------
class ActionShowPlantTrial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionShowPlantTrial, WorldMapAction, RtClass) {}
    static ActionShowPlantTrial* CreateIfNeed(bool& hasTutorial);
    
    ActionShowPlantTrial() {}
    ActionShowPlantTrial(const std::string& plant);
    virtual void	Start() override;
private:
    void OnPlantTrialClosed();
private:
    std::string m_plantName;
};

//-----------------------------------------------------------
class ActionShowPlantAdventure: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionShowPlantAdventure, WorldMapAction, RtClass) {}
    static ActionShowPlantAdventure* CreateIfNeed(bool& hasTutorial);
    
    ActionShowPlantAdventure() {}
    ActionShowPlantAdventure(const std::string &dungeonName);
    virtual void Start() override;
    
private:
    void OnPlantAdventureClosed();
    
private:
    std::string m_dungeonName;
};

//-----------------------------------------------------------
class ActionShowSalesUI: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionShowSalesUI, WorldMapAction, RtClass) {}
    static ActionShowSalesUI* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;
    
private:
    void OnShowSalesUIClosed();
    
private:
    int         m_status = 0;
    float       m_timeOut = 0;
};

//-----------------------------------------------------------
class ActionBossChallenge: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionBossChallenge, WorldMapAction, RtClass) {}
    static ActionBossChallenge* CreateIfNeed(bool& hasTutorial);

    virtual void Start() override;
    virtual void Update() override;
    virtual void End() override;
};

//-----------------------------------------------------------
class ActionLimitedGacha: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionLimitedGacha, WorldMapAction, RtClass) {}
    static ActionLimitedGacha* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;
    virtual void Update() override;
    virtual void End() override;
};

//-----------------------------------------------------------
class ActionGeilivableLottery: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionGeilivableLottery, WorldMapAction, RtClass) {}
    static ActionGeilivableLottery* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;
    
private:
    void OnGeilivableLotteryClosed();
};

//-----------------------------------------------------------
class ActionShowUserInfo: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionShowUserInfo, WorldMapAction, RtClass) {}
    static ActionShowUserInfo* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;
    virtual void Update() override;
    virtual void End() override;
    
};

//-----------------------------------------------------------
class ActionShowFirstRecharge: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionShowFirstRecharge, WorldMapAction, RtClass) {}
    static ActionShowFirstRecharge* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;
    virtual void Update() override;
    virtual void End() override;
    
private:
    void OnFirstRechargeClosed();
    
};

//-----------------------------------------------------------
class ActionShowRechargeBundle: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionShowRechargeBundle, WorldMapAction, RtClass) {}
    static ActionShowRechargeBundle* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;
    virtual void Update() override;
    virtual void End() override;
    
private:
    void OnRechargeBundleClosed();
    void OnRechargeBundleShowed();
    
    pvztime_t			m_timerCheck = PVZ_EOT();
    bool m_bNeedClose = true;
    
};

//-----------------------------------------------------------
class ActionShowOfflineBundle: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionShowOfflineBundle, WorldMapAction, RtClass) {}
    static ActionShowOfflineBundle* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;
private:
    void OnOfflineBundleClosed();
    
};

//-----------------------------------------------------------
class ActionLuaAct : public WorldMapAction
{
public:
    ActionLuaAct();
    ActionLuaAct(int iGroup);
    RT_CLASS_DEFINE(ActionLuaAct, WorldMapAction, RtClass) {}
    static ActionLuaAct* CreateIfNeed(bool& hasTutorial, int iGroup);
    
    virtual void Start() override;
    virtual void Update() override;
private:
    int m_iGroup;
};

//-------------------------------------------------------
class ActionPurchaseBroker: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionPurchaseBroker, WorldMapAction, RtClass) {}
    static ActionPurchaseBroker* CreateIfNeed(bool& hasTutorial);

    virtual void Start() override;
    
private:
    void OnActionPurchaseBrokerClosed();
};

//-------------------------------------------------------
class ActionLostPurchaseOrders: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionLostPurchaseOrders, WorldMapAction, RtClass) {}
    static ActionLostPurchaseOrders* CreateIfNeed(bool& hasTutorial);

    virtual void Start() override;

private:
    void OnNotifyRetreiveLostOrderEnd();
};

//-------------------------------------------------------
class ActionRebateReward: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionRebateReward, WorldMapAction, RtClass) {}
    
    virtual void Start() override;
    
private:
    
    void    AddMessage();
    
    void    AndroidRequestProcess();
    
    void    GotCheckRebateData(class S2C_ChristmasCheckRebate* pData);
    
    void onActionRebateRewardClosed();
};

//-------------------------------------------------------
class ActionIwatchReward: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionIwatchReward, WorldMapAction, RtClass) {}
    
    virtual void Start() override;
    
private:
    
    void onIwatchRewardClosed();
};

//--------------------------------------------------------------
// tutorial for pvp
class ActionPVPTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionPVPTutorial, WorldMapAction, RtClass) {}
    static ActionPVPTutorial* CreateIfNeed(bool& hasTutorial);
    
    virtual void		Start() override;
    virtual void		End() override;
    
protected:
    void            onNarrationFinished();
    void				onTutorialFinished();
private:
    std::string         m_narrativeID;
    std::string         m_narrativeEvent;
    MapTutorialState    m_tutorialState;
};

//--------------------------------------------------------------
class ActionHardLevelReward: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionHardLevelReward, WorldMapAction, RtClass) {}
    static ActionHardLevelReward* CreateIfNeed(bool& hasTutorial);

    virtual void		Start() override;
    virtual void		End()   override;
    
protected:
    void onHardLevelRewardFinished();
};

//--------------------------------------------------------------
class ActionRegularTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionRegularTutorial, WorldMapAction, RtClass) {}
    static ActionRegularTutorial* CreateIfNeed(bool& hasTutorial);
    
    ActionRegularTutorial() {}
    ActionRegularTutorial(MapTutorialState tutorial);
     void Start() override;
     void Update() override;
private:
    static bool HasWorldUnlockTutorial();
    static bool HasDangerRoomTutorial();
    static MapTutorialState GetTutorial();
private:
    MapTutorialState    m_tutorial = TUTORIAL_NONE;
};

//--------------------------------------------------------------
class ActionCR_StoreTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionCR_StoreTutorial, WorldMapAction, RtClass) {}
    static ActionCR_StoreTutorial* CreateIfNeed(bool& hasTutorial);
    
    ActionCR_StoreTutorial();
    ~ActionCR_StoreTutorial();
    void Start() override;
private:
    void onNarrationFinished();
    void OnLuaNotify(const std::string& tag);
private:
};

//--------------------------------------------------------------
class Action_TGTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_TGTutorial, WorldMapAction, RtClass) {}
    static Action_TGTutorial* CreateIfNeed(bool& hasTutorial);
    
    Action_TGTutorial();
    ~Action_TGTutorial();
    void Start() override;
    
private:
    void onNarrationFinished();
    void OnLuaNotify(const std::string& tag);
    
private:
};

//--------------------------------------------------------------
class Action_NewAvatarTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_NewAvatarTutorial, WorldMapAction, RtClass) {}
    static Action_NewAvatarTutorial* CreateIfNeed(bool& hasTutorial);
    
    Action_NewAvatarTutorial();
    ~Action_NewAvatarTutorial();
    void Start() override;
    
private:
    void onNarrationFinished();
        
private:
};

//--------------------------------------------------------------
class Action_GeneEnhancementTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_GeneEnhancementTutorial, WorldMapAction, RtClass) {}
    static Action_GeneEnhancementTutorial* CreateIfNeed(bool& hasTutorial);
    
    Action_GeneEnhancementTutorial();
    ~Action_GeneEnhancementTutorial();
    virtual void        Start() override;
    virtual void		End()   override;

private:
    void onNarrationFinished();
private:
};

//--------------------------------------------------------------
class Action_NewPvPTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_NewPvPTutorial, WorldMapAction, RtClass) {}
    static Action_NewPvPTutorial* CreateIfNeed(bool& hasTutorial);
    
    Action_NewPvPTutorial();
    ~Action_NewPvPTutorial();
    virtual void        Start() override;
    virtual void		End()   override;

private:
    void onNarrationFinished();
private:
};

//--------------------------------------------------------------
class Action_PlantFamilyTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_PlantFamilyTutorial, WorldMapAction, RtClass) {}
    static Action_PlantFamilyTutorial* CreateIfNeed(bool& hasTutorial);
    
    Action_PlantFamilyTutorial();
    ~Action_PlantFamilyTutorial();
    void Start() override;
    
private:
    void onNarrationFinished();
    void OnLuaNotify(const std::string& tag);
    
private:
};


//--------------------------------------------------------------
class ActionUUIDBindTip : public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionUUIDBindTip, WorldMapAction, RtClass) {}
    static ActionUUIDBindTip * CreateIfNeed(bool& hasTutorial);
    
    void Start() override;
    
private:
    void onUUIDBindClosed();
};

//--------------------------------------------------------------
class ActionActivityLevelsTutorial : public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionActivityLevelsTutorial, WorldMapAction, RtClass) {}
    static ActionActivityLevelsTutorial* CreateIfNeed(bool& hasTutorial);
    
    void Start() override;
    void End() override;
    
protected:
    void onLevelsNarrationFinished();
    void onBossChallengeNarrationFinished();
    void onTutorialFinished();
};

//--------------------------------------------------------------
class ActionClearFakeGem : public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionClearFakeGem, WorldMapAction, RtClass) {}
    static ActionClearFakeGem* CreateIfNeed();
    
    virtual void Start() override;
};

//--------------------------------------------------------------
class ActionShowAds : public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionShowAds, WorldMapAction, RtClass) {}
    static ActionShowAds* CreateIfNeed(bool& hasTutorial);
    
    void Start() override;
    void End() override;
    
protected:
    void onAdsFinish(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
};

//-----------------------------------------------------------
class ActionGemSpecialOffer: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionGemSpecialOffer, WorldMapAction, RtClass) {}
    static ActionGemSpecialOffer* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;    
    void OnGemSpecialOfferEnd();
};

//-----------------------------------------------------------
class ActionDangerRoomMain: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionDangerRoomMain, WorldMapAction, RtClass) {}
    static ActionDangerRoomMain* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;
    virtual void Update() override;
    virtual void End() override;
    
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void OnMsgErrorRequest(int erroId, const std::string& i_reqID);
private:
    float   m_timerCheck = -1.0f;
    bool    m_bRequest = false;
};

//-----------------------------------------------------------
class ActionDinosaurDanger: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionDinosaurDanger, WorldMapAction, RtClass) {}
    static ActionDinosaurDanger* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;
    virtual void Update() override;
    virtual void End() override;
};

#ifdef HOST_ANDROID
class ActionPurchaseRedeem: public WorldMapAction
{
public:
	RT_CLASS_DEFINE(ActionPurchaseRedeem, WorldMapAction, RtClass) {}
	static ActionPurchaseRedeem* CreateIfNeed(bool& hasTutorial);

	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

private:
	bool m_checkRedeemOrdersFinished;
	std::map<std::string, RedeemInfo> m_redeemOrders;
	pvztime_t m_timeout;
};
#endif

//-----------------------------------------------------------
class ActionRecallOffer: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionRecallOffer, WorldMapAction, RtClass) {}
    static ActionRecallOffer* CreateIfNeed(bool& hasTutorial);

    virtual void Start() override;
    virtual void Update() override;
    virtual void End() override;
};

//--------------------------------------------------------------
class Action_JoustTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_JoustTutorial, WorldMapAction, RtClass) {}
    static Action_JoustTutorial* CreateIfNeed(bool& hasTutorial);

    void Start() override;

private:
    void onNarrationFinished();
    void skipTutorial();
    void continueTutorial();
};

class Action_ArtifactTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_ArtifactTutorial, WorldMapAction, RtClass) {}
    static Action_ArtifactTutorial* CreateIfNeed(bool& hasTutorial);

    void Start() override;
    void End() override;

private:
    void onTutorialFinished();
};

class Action_PennyClassroomTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_PennyClassroomTutorial, WorldMapAction, RtClass) {}
    static Action_PennyClassroomTutorial* CreateIfNeed(bool& hasTutorial);

    void Start() override;
    void End() override;

private:
    void onTutorialFinished();
};

class Action_UnchartedModeTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_UnchartedModeTutorial, WorldMapAction, RtClass) {}
    static Action_UnchartedModeTutorial* CreateIfNeed(bool& hasTutorial);

    void Start() override;
    void End() override;

private:
    void onTutorialFinished();
};

class Action_UnchartedModePopUp: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_UnchartedModePopUp, WorldMapAction, RtClass) {}
    static Action_UnchartedModePopUp* CreateIfNeed(bool& hasTutorial);

    void Start() override;
    void End() override;

private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class Action_CardGameCardSelectCheck: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_CardGameCardSelectCheck, WorldMapAction, RtClass) {}
    static Action_CardGameCardSelectCheck* CreateIfNeed(bool& hasTutorial);

    void Start() override;
    void End() override;
};

class Action_ReturnGems: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_ReturnGems, WorldMapAction, RtClass) {}
    static Action_ReturnGems* CreateIfNeed(bool& hasTutorial);
    ~Action_ReturnGems();

    virtual void Start() override;
    virtual void End() override;
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class Action_AutoExchange: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_AutoExchange, WorldMapAction, RtClass) {}
    static Action_AutoExchange* CreateIfNeed(bool& hasTutorial);
    ~Action_AutoExchange();

    virtual void Start() override;
    virtual void End() override;
};

class Action_LimitedSummonReward: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_LimitedSummonReward, WorldMapAction, RtClass) {}
    static Action_LimitedSummonReward* CreateIfNeed(bool& hasTutorial);
    ~Action_LimitedSummonReward();

    virtual void Start() override;
    virtual void End() override;
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class Action_BattleOrderIntroduction: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_BattleOrderIntroduction, WorldMapAction, RtClass) {}
    static Action_BattleOrderIntroduction* CreateIfNeed(bool& hasTutorial);
    ~Action_BattleOrderIntroduction();

    virtual void Start() override;
    virtual void End() override;
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class Action_Cornucopia: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_Cornucopia, WorldMapAction, RtClass) {}
    static Action_Cornucopia* CreateIfNeed(bool& hasTutorial);
    ~Action_Cornucopia();

    virtual void Start() override;
    virtual void End() override;
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class Action_PlantCultivate: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_PlantCultivate, WorldMapAction, RtClass) {}
    static Action_PlantCultivate* CreateIfNeed(bool& hasTutorial);
    ~Action_PlantCultivate();

    virtual void Start() override;
    virtual void End() override;
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class Action_TrialCardSynchronize: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_TrialCardSynchronize, WorldMapAction, RtClass) {}
    static Action_TrialCardSynchronize* CreateIfNeed(bool& hasTutorial);

    virtual void Start() override;
    virtual void End() override;
};


//-----------------------------------------------------------
class ActionNewerPresent: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionNewerPresent, WorldMapAction, RtClass) {}
    static ActionNewerPresent* CreateIfNeed(bool& hasTutorial);

    virtual void Start() override;
    virtual void Update() override;
    virtual void End() override;
};

class Action_TravelLogTasks: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_TravelLogTasks, WorldMapAction, RtClass) {}
    static Action_TravelLogTasks* CreateIfNeed(bool& hasTutorial);
    ~Action_TravelLogTasks();

    virtual void Start() override;
    virtual void End() override;
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class Action_DaveTreasureTasks: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_DaveTreasureTasks, WorldMapAction, RtClass) {}
    static Action_DaveTreasureTasks* CreateIfNeed(bool& hasTutorial);
    ~Action_DaveTreasureTasks();

    virtual void Start() override;
    virtual void End() override;
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class Action_HappyVaseBreakerTasks: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_HappyVaseBreakerTasks, WorldMapAction, RtClass) {}
    static Action_HappyVaseBreakerTasks* CreateIfNeed(bool& hasTutorial);
    ~Action_HappyVaseBreakerTasks();

    virtual void Start() override;
    virtual void End() override;
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class Action_NoviceSevenDaysTrigger: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_NoviceSevenDaysTrigger, WorldMapAction, RtClass) {}
    static Action_NoviceSevenDaysTrigger* CreateIfNeed(bool& hasTutorial);
    ~Action_NoviceSevenDaysTrigger();
    
    virtual void Start() override;
    virtual void End() override;
};

class Action_NoviceSevenDaysTask: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_NoviceSevenDaysTask, WorldMapAction, RtClass) {}
    static Action_NoviceSevenDaysTask* CreateIfNeed(bool& hasTutorial);
    ~Action_NoviceSevenDaysTask();

    virtual void Start() override;
    virtual void End() override;
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

//-----------------------------------------------------------
class ActionAuthLimitCheck: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionAuthLimitCheck, WorldMapAction, RtClass) {}
    static ActionAuthLimitCheck* CreateIfNeed(bool& hasTutorial);

    virtual void Start() override;
};

#ifdef HOST_ANDROID
class RenaiWorldMapCheck: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(RenaiWorldMapCheck, WorldMapAction, RtClass) {}
    static RenaiWorldMapCheck* CreateIfNeed(bool& hasTutorial);
    virtual void Start() override;
};
#endif

// richman pop ui reward
class ActionRichmanRewardCheck : public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionRichmanRewardCheck, WorldMapAction, RtClass) {}
    static ActionRichmanRewardCheck* CreateIfNeed(bool& hasTutorial);
    virtual void Start() override;
};


class Action_ShowLuckBag: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_ShowLuckBag, WorldMapAction, RtClass) {}
    static Action_ShowLuckBag* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;
};

class Action_ShowFightZodiac: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_ShowFightZodiac, WorldMapAction, RtClass) {}
    static Action_ShowFightZodiac* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;
    virtual void End() override;
    
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class Action_ShowNewRecall: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_ShowNewRecall, WorldMapAction, RtClass) {}
    static Action_ShowNewRecall* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;
};

//accessory
class Action_SuperAccessory: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_SuperAccessory, WorldMapAction, RtClass) {}
    static Action_SuperAccessory* CreateIfNeed(bool& hasTutorial);
    
    virtual void Start() override;
    void onNarrationFinished();
};

// dangerroom special offer
class ActionDangerRoomSpecialOfferCheck : public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionDangerRoomSpecialOfferCheck, WorldMapAction, RtClass) {}
    static ActionDangerRoomSpecialOfferCheck* CreateIfNeed(bool& hasTutorial);

    virtual void Start() override;
};

class ActionPlantSpecialOffer: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionPlantSpecialOffer, WorldMapAction, RtClass) {}
    static ActionPlantSpecialOffer* CreateIfNeed(bool& hasTutorial);
    ~ActionPlantSpecialOffer();

    virtual void Start() override;
    virtual void End() override;
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class ActionFirstRecharge: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionFirstRecharge, WorldMapAction, RtClass) {}
    static ActionFirstRecharge* CreateIfNeed(bool& hasTutorial);
    ~ActionFirstRecharge();

    virtual void Start() override;
    virtual void End() override;
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class ActionRechargeReward: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionRechargeReward, WorldMapAction, RtClass) {}
    static ActionRechargeReward* CreateIfNeed(bool& hasTutorial);
    ~ActionRechargeReward();

    virtual void Start() override;
    virtual void End() override;
private:
    void OnNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
};

class ActionFestivalEvent: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionFestivalEvent, WorldMapAction, RtClass) {}
    static ActionFestivalEvent* CreateIfNeed(bool& hasTutorial);

    virtual void Start() override;
};

class ActionAuthReward: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionAuthReward, WorldMapAction, RtClass) {}
    static ActionAuthReward* CreateIfNeed(bool& hasTutorial);

    virtual void Start() override;
};

class ActionRiftEndSeasonNotice: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionRiftEndSeasonNotice, WorldMapAction, RtClass) {}
    static ActionRiftEndSeasonNotice* CreateIfNeed(bool& hasTutorial);

    virtual void Start() override;
private:
    void showNotice();
};

class ActionRiftLegendRankNotice: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionRiftLegendRankNotice, WorldMapAction, RtClass) {}
    static ActionRiftLegendRankNotice* CreateIfNeed(bool& hasTutorial);

    virtual void Start() override;
};

class Action_RiftWorldOpenTutorial: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(Action_RiftWorldOpenTutorial, WorldMapAction, RtClass) {}
    static Action_RiftWorldOpenTutorial* CreateIfNeed(bool& hasTutorial);
    
    Action_RiftWorldOpenTutorial();
    ~Action_RiftWorldOpenTutorial();
    void Start() override;

    static bool s_HasStartTutorial;
    
private:
    void onNarrationFinished();
    
private:
};

class ActionNewplayerActivityCollectionActivate: public WorldMapAction
{
public:
    RT_CLASS_DEFINE(ActionNewplayerActivityCollectionActivate, WorldMapAction, RtClass) {}
    static ActionNewplayerActivityCollectionActivate* CreateIfNeed(bool& hasTutorial);

    virtual void Start() override;
};

#endif
