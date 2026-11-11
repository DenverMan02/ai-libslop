//
//  WorldMapActionManager.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2016.5.19.
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef _WorldMapActionManager_h_
#define _WorldMapActionManager_h_

#include "NetworkData.h"

enum WorldMapActionType
{
	ActionType_Unknown = -1,
	ActionTypeClearFakeGem,
	ActionTypeDisableUserInput,
	ActionTypeLoadCurrentWorldAssets,
	ActionTypePurchaseRedeem,
	ActionTypeLostPurchaseOrders,
	ActionTypeAuthLimitCheck,
	ActionTypeDangerRoomMain,
	ActionTypeShowAds,
	ActionTypeShowBoardDlg,
	ActionTypeShowRechargeBundle,
	ActionTypeShowOfflineBundle,
	ActionTypeUnlockNodesSequence,
	ActionTypeDelay,
	ActionTypeCheckForAndSpawnYeti,
	ActionTypeAllowUserInput,
	ActionTypeLoginReward,
	ActionTypeStartNarrativeID,
	ActionTypeEnterTutorial,
	ActionTypeActivityLevelsTutorial,
	ActionTypeCR_StoreTutorial,
	ActionType_TGTutorial,
	ActionType_NewAvatarTutorial,
	ActionType_PlantFamilyTutorial,
	ActionTypeShowPlantTrial,
	ActionTypeHardLevelReward,
	ActionType_ReturnGems,
	ActionType_TravelLogTasks,
	ActionType_DaveTreasureTasks,
	ActionType_HappyVaseBreakerTasks,
	ActionType_ShowLuckBag,
	ActionTypeShowNewRecall,
	ActionTypeRichmanRewardCheck,
	ActionTypeDangerRoomSpecialOfferCheck,
	ActionTypeRenaiWorldMapCheck,
	ActionTypeMonthlyCard,
	ActionTypeBossChallenge,
	ActionTypeLimitedGacha,
	ActionTypeWorldUnlockPack,
	ActionTypeAnniversary,
	ActionTypeShowSalesUI,
	ActionTypeDinosaurDanger,
	ActionTypePurchaseBroker,
	ActionTypeRegularTutorial,
	ActionTypeUUIDBindTip,
	ActionTypeShowPlantAdventure,
	ActionTypeGemSpecialOffer,
	ActionTypeRecallOffer,
	ActionType_JoustTutorial,
	ActionTypeNewerPresent,
	ActionTypePlantSpecialOffer,
	ActionTypeFirstRecharge,
	ActionTypeRechargeReward,
	ActionTypeFestivalEvent,
	ActionTypeAuthReward,
	ActionTypeSuperAccessory,
	ActionTypeRiftWoldOpen,
	ActionTypeRiftEndNotice,
	ActionTypeRiftLegendRankNotice,
	ActionType_ShowFightZodiac,
	ActionType_NoviceSevenDaysTrigger,
	ActionType_NoviceSevenDaysTask,
	ActionTypeEnterTutorialCheck,
	ActionType_ArtifactTutorial,
	ActionType_PennyClassroomTutorial,
	ActionType_UnchartedModeTutorial,
	ActionType_UnchartedModePopup,
	ActionType_CardGameSelectCheck,
	ActionType_LimitedSummonReward,
	ActionType_BattleOrder,
	ActionType_GeneEnhancementTutorial,
	ActionType_NewPvPTutorial,
	ActionType_Cornucopia,
	ActionType_PlantCultivate,
	ActionType_SynchronizeTrialCard,
	ActionType_NewplayerActivityCollectionActivate,
	ActionType_AutoExchange,
	ActionTypeCount
};

enum ActionInitState
{
	Action_Invalid,
	Action_InitActions,
	Action_SyncActions,
	Action_FinishActions
};

class NetworkActionInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkActionInfo, INetworkData, RtClass);

public:
	std::vector<int> m_infos;
};

class WorldMapActionManager
{
public:
    WorldMapActionManager();
    ~WorldMapActionManager();
    void        ClearActions();
    bool        AddAction(class WorldMapAction* i_action, WorldMapActionType i_type);
    void        Update();
    void        SetRequiresInit(bool setting) { m_requiresInitActions = setting; }
    void        QueueAllInitActions();
    size_t      Size() const { return m_queuedActions.size(); }
    class WorldMapAction*   GetCurrentAction();
    void        StopActions();

    static void ResetStaticData();
    static void AddCachedAction(int i_group, const std::string& i_name, int i_popupNumAdd);
    void		AssignIds(const std::vector<int>& i_list);
    void 		ApplySequence();
    void		SetState(ActionInitState i_state);
    ActionInitState GetState() { return m_state; }
    bool IsInState(uint32 state) const { return m_state == state; }
protected:
    void        queueAllInitActions_impl();
    void		SyncActions();
    void 		OnNetworkError(int erroId, const std::string& i_reqID);
    void		InitTestData();
    bool 		needSyncActions();
protected:
    std::vector<class WorldMapAction*> m_queuedActions;
    bool        m_requiresInitActions = false;
    bool        m_bNeedQueueActions = false;
    ActionInitState m_state;
};


#endif
