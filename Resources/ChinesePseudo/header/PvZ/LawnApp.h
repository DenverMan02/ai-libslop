#ifndef __LAWNAPP_H__
#define __LAWNAPP_H__
#include "Precompile.h"
//#include "LuaEngine/lua_support/LuaDef.h"

#include "SexyAppFramework/SexyApp.h"
#include "SexyAppFramework/PopAnimListener.h"
//#include "SexyAppFramework/PopAnim.h"
//#include "SexyAppFramework/PIEffect.h"
#include "SexyAppFramework/Mesh.h"
#include "SexyAppFramework/PrimeText/PrimeText.h"
#include "SexyAppFramework/PrimeText/PrimeTypeface.h"
//#include "PrimeText_Game.h"
#include "SexyAppFramework/IFacebookDriver.h"
#include "core.h"
#include "ScaledApp.h"
#include "ConsoleListener.h"
#include "PvZ2IDs.h"
#include "LawnAppEnums.h"
#include "PlantEnums.h"
#include "PVZTypes.h"
#include "BoardEnums.h"
//#include "GameEventMgr.h"
//#include "GameStateMgr.h"
#include "Cheats.h"
#include "IPurchaseDriver.h"
#include "PVZCachedNetworkTable.h"
//#include "NotificationManagerGame.h"
#include "PVZVersionNetwork.h"
#include "PVZRechargeCheckServer.h"
//#include "SocialInfo.h"
#include "PackageContentsProvider.h"
//#include "GachaUI.h"
#include "PVZ2UIStarLevelUp.h"
//#include "PVZ2UICompenNotice.h"
#include "ServerTime.h"
#include "ReviveUI.h"
#include "BattleStatementUI.h"
#include "RedPacketRewardInfo.h"
#include "PlantTrialConfig.h"
#include "RechargeRewardConfig.h"
#include "ConsumptionRewardInfo.h"
#include "PlantAdventureConfig.h"
#include "StarConvertConfig.h"
#include "LostNetActivityConfig.h"
#include "DailyAchievementInfo.h"
#include "LevelOfTheDayConfigInfo.h"
#include "NationalDayRewardConfigInfo.h"
#include "ArenaPlantModule.h"
//#include "ArenaBattleModule.h"
#include "ArenaPrecompile.h"
#include "RebateRewardConfig.h"
//for oppo
#ifdef HOST_ANDROID
#include "OfferBundleConfig.h"
#endif
#include "WorldCupConfig.h"
#include "EASquared.h"
#include "JoustPlantPowerConfig.h"
#include "WorldMapDefine.h"

/// Sundry global defines that have no home
#ifdef WANTS_CHEATS_DISABLED
const bool gDisableDebugKeys = true;
#else
const bool gDisableDebugKeys = false;
#endif
#define QA_CHEATS		// Comment to get rid of QA cheats
#ifdef WANTS_TIME_BOMB
	bool AppHasExpired();
#endif
#ifdef HOST_IPHONEOS
#include "iosNetworkMsgProcess.h"
#endif

#ifndef _64BIT_TRANSFER_
#define _64BIT_TRANSFER_

template <class T> T SafeTransferFromUInt64(uint64 src_value, T target_type_max)
{
    //DBG_ASSERT(0==(src_value/target_type_max));
    return static_cast<T>(src_value);
}

template <class T> T SafeTransferFromInt64(int64 src_value, T target_type_max)
{
    //DBG_ASSERT(0==(src_value/target_type_max));
    return static_cast<T>(src_value);
}

#endif

// development resource directory, used for things like reloading definitions
extern std::string gDevRelativeResPath;
const std::string k_worldResourcePrefix = "RESFILE_PACKAGES_WORLDS_";
const float k_plantingOffsetY = -10.0f;
extern class TodStringListFormat gLawnStringFormats[];
extern const int gLawnStringFormatCount;
// Forward declarations
class MagentoProductProps;
//class ArenaBattleModule;

/// LawnApp declaration
#ifdef HOST_ANDROID
#define WANTS_PVZ2_FACEBOOK_DISABLED
#endif
struct GachaGet
{
	std::string type;
	std::string sku;
	int count;
	GachaGet()
	{
		type = "";
		sku = "";
		count = 0;
	}
};
struct GachaPriceInfo
{
	int price;
	int result;
	GachaPriceInfo()
	{
		price = 0;
		result = 0;
	}
};

enum ModuleInfo
{
    PVZ_BEGIN_FLAG_ENUM(Module_),
    
    PVZ_FLAG(Module_Pooyan),
    PVZ_FLAG(Module_Fishing),
    PVZ_FLAG(Module_Besiege),    
    
    PVZ_END_FLAG_ENUM(Module_),
};
PVZ_MAKE_ENUM_BIT_OPERATORS(ModuleInfo);

enum ActivityImageType
{
	Type_Headshot_Avatar
};

struct IdNameInfo
{
    std::string name = "";
    IdType type = IdNone;
};

struct PaymentResultInfo
{
	PaymentResultInfo()
	{
		resultCode = "";
		orderId = "";
		payType = "";
		payCode = "";
	}

	std::string resultCode;
	std::string orderId;
	std::string payType;
	std::string payCode;
};

enum ServiceFlags
{
    PVZ_BEGIN_FLAG_ENUM(ServiceFlags_),
    PVZ_FLAG(Service_GemRestore),
    PVZ_FLAG(Service_Ifengfeng),
    PVZ_FLAG(Service_StoneTab),
    PVZ_FLAG(Service_ForceLua),
    PVZ_FLAG(Service_ForceConfig),
    PVZ_FLAG(Service_AdsMap),
    PVZ_FLAG(Service_AdsMission),
    PVZ_FLAG(Service_AdsPause),
    PVZ_FLAG(Service_AdsGameStart),
    PVZ_FLAG(Service_LimitVersion),
    PVZ_FLAG(Service_CodeReward),
    PVZ_FLAG(Service_Https),
    PVZ_FLAG(Service_UpdateRsb),
    PVZ_FLAG(Service_PayCheck),
    PVZ_FLAG(Service_AdsBox),
    PVZ_FLAG(Service_AdsDaveShop),
    PVZ_FLAG(Service_ShowNewAvtarSwitch),
    PVZ_FLAG(Service_Auth),
    PVZ_FLAG(Service_ShowGMInfo),
    PVZ_FLAG(Service_SyncActions),
    PVZ_FLAG(Service_ShowGMInfoSettingDialog),
    PVZ_FLAG(Service_ShowLogout),
    PVZ_FLAG(Service_ShowGMInfoComplain),
    PVZ_FLAG(Service_ShowDIYMotivateButton),
    PVZ_FLAG(Service_Reconnect),
    PVZ_FLAG(Service_HMDEvent),
    PVZ_END_FLAG_ENUM(ServiceFlags_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(ServiceFlags);

#define APP_WIDGET_DEFINE(xWidgetClass) \
class xWidgetClass* m_##xWidgetClass = nullptr; \
void Show##xWidgetClass(); \
void Kill##xWidgetClass(); \
bool IsValid##xWidgetClass() {return m_##xWidgetClass != nullptr;} \


#define APP_WIDGET_IMPLEMENT(xWidgetClass) \
void LawnApp::Show##xWidgetClass() \
{ \
    if (m_##xWidgetClass == nullptr) \
    { \
        m_##xWidgetClass = new xWidgetClass(); \
        mWidgetManager->AddWidget(m_##xWidgetClass); \
    } \
    mWidgetManager->BringToFront(m_##xWidgetClass); \
    PushOverlaysToTop(); \
    mWidgetManager->AddBaseModal(m_##xWidgetClass); \
    mWidgetManager->SetFocus(m_##xWidgetClass); \
} \
void LawnApp::Kill##xWidgetClass() \
{ \
    if (m_##xWidgetClass == nullptr) \
    { \
        return; \
    } \
    mWidgetManager->RemoveWidget(m_##xWidgetClass); \
    mWidgetManager->RemoveBaseModal(m_##xWidgetClass); \
    SafeDeleteWidget(m_##xWidgetClass); \
    m_##xWidgetClass = nullptr; \
} \


class LawnApp : public ScaledApp
#ifndef WANTS_PVZ2_FACEBOOK_DISABLED
, public IFBSessionListener
#endif // WANTS_PVZ2_FACEBOOK_DISABLED
{
public:
    enum InitReason
    {
        InitReason_FirstInit,
        InitReason_Reinit
    };
    
	LawnApp();
	virtual ~LawnApp();
	/// Virtual SexyApp interface
    //PVZ2_CHINESE_END
    virtual void Init() override
    {
        // Init() will always perform a "first-init"
        Init(InitReason_FirstInit);
    }
    std::string GetPlatformName();
	std::string GetPackageName(const std::string& i_defaultIOS = "AppStore");
    //PVZ2_CHINESE_BEGIN_
    std::string GetDeviceType();
    //PVZ_CHINISE_END
    bool DeviceNeeds50MBResolutionChange();
    virtual void Start() override;
    virtual void UpdateFrames() override;
    virtual bool UpdateApp() override;
    
    virtual void DrawScreen() override;
    virtual void Shutdown() override;
    
    virtual void LowMemoryWarning() override;
    virtual void AppEnteredBackground() override;
    virtual void AppBecomingForeground() override;
    virtual void URLOpenFailed(const std::string& theURL) override;
    virtual void URLOpenSucceeded(const std::string& theURL) override;
    virtual bool OpenURL(const std::string& theURL, bool shutdownOnOpen) override;
    virtual void SetMasterVolume(double i_volume) override; // volume = [0,1]
    virtual void SetMusicVolume(double i_volume) override; // volume = [0,1]
    virtual void SetSfxVolume(double i_volume) override;   // volume = [0,1]
    
    void CheckForUpdates();
    void LoadLocalLawnStrings();
    void ResetDatas();
    
    void PauseMusic();
    void ResumeMusic();
    void PlayMusic( char const * sEventName );
    void PlayMusicCallback(char const* sEventName, IInteractiveAudioCallbackListener* i_callbackObject);
    uint32 GetMusicCallbackID() { return m_callbackEventID; }
    void ClearMusicCallbackID() { m_callbackEventID = 0; }
    void StopMusic( char const * sEventName );
    // handlers for when the system drives a mute-message - User-music on iOS devices for example.
    virtual void			MuteMusic() override;
    virtual void			UnmuteMusic() override;
    virtual void            HandleWwiseError() override;
    
    virtual void PlaySample(SoundResource* i_sound) { DBG_ASSERT(false); } // Deprecated, use gAudioMgr->SendEvent(event-id) instead.
    virtual void PlaySample(SoundResource* i_sound, int i_pan) { DBG_ASSERT(false); } // Deprecated, use gAudioMgr->SendEvent(event-id) instead.
    
    virtual bool IsUIOrientationAllowed(UI_ORIENTATION i_orientation) override;
    virtual void UIOrientationChanged(UI_ORIENTATION theOrientation) override;
    
    virtual void GotFocus() override;
    virtual void LostFocus() override;
    virtual void OnGestureFlick(Sexy::GestureFlickDirection i_direction, Sexy::Point i_startingLocation) override;
    
    // Does the real init of LawnApp, but can also handle reinitializing the app
    virtual void Init(InitReason inInitReason, int inForceHeight = 0);
    
    // Dialog related overrides
    virtual Sexy::Dialog* DoDialog(int i_dialogId, bool isModal, const SexyString& i_dialogHeader, const SexyString& i_dialogLines, const SexyString& i_dialogFooter, int i_buttonMode) override;
    virtual Sexy::Dialog* NewDialog(int i_dialogId, bool isModal, const SexyString& i_dialogHeader, const SexyString& i_dialogLines, const SexyString& i_dialogFooter, int i_buttonMode) override;
    
    /// Virtual ButtonListener interface
    virtual void ButtonPress(int i_id) override;
    virtual void ButtonDepress(int i_id) override;
    
    /// Initial loading loop, these functions are called by TitleScreen
    //PVZ2_CHINESE_BEGIN
    void LoadingThreadProc() override;
    void StartInitialLoad();
    void FinishInitialLoad();
    void GenerateFonts();
    float InitialLoadProgress();
    void DeleteAlwaysLoadedGroups();
	// Returns 'true' if the game is the top OS-specific view visible at the moment
	// If this returns 'false' it's likely that another system (gamecenter login, etc) is visible right now
	bool IsAppTopLevel();
	
    int GetCurrentVersion() const;
	/// Dialog / Sub-Widget Control
    
    // replace board UnregisterTouchGameplayObject for miniboar when board is Null
    void UnregisterBoardTouchGameplayObject(void* i_touchOwner);
	
	// Options (in-game pause) dialog
	void DoNewOptions(const bool i_showBackToMap, const bool i_isDangerRoom);
	void KillNewOptionsDialog();
	void ShowAlmanac(ObjectTypeDescriptorPtr i_objectType);
	void KillAlmanac();
    
    void ShowAwakenWidget(ObjectTypeDescriptorPtr i_objectType);
    void KillAwakenWidget();
	
	void ShowTitleScreen();
	bool IsTitleScreenFinished();
	void KillTitleScreen();
    
    void ShowEndLevelUI();
    void KillEndLevelUI();
    class EndLevelUI* GetEndLevelUI() { return m_endLevelUI; }
    
    void ShowBoardZombieAlmanacUI(const std::vector<std::string>& i_zombieList);
    void KillBoardZombieAlmanacUI();
    class BoardZombieAlmanacUI* GetBoardZombieAlmanacUI() { return m_boardZombieAlmanacUI; }
    
    void ShowGachaDisplayerDialog(GachaType i_type);
    void KillGachaDisplayerDialog();
    class GachaDisplayerDialog* GetGachaDisplayerDialog() { return m_gachaDisplayerDialog; }
    
    void ShowMainMenu();
    void KillMainMenu();
    class MainMenu* GetMainMenu() { return m_mainMenu; }
    
    void ShowBoard();
    void KillBoard();
    void ShowWorldMap();
    void KillWorldMap();
    
    void ShowWorldPreview(const std::string& i_worldName);
    void KillWorldPreview();
    class UniverseWorldInfo*GetWorldInfoUI(){return m_universeWorldInfo;}
    class PVZ2UIWorldPreview* GetWorldPreview() { return m_worldPreview; }
    
    void ShowWorldUnlock(const std::string& i_worldName);
    void KillWorldUnlock();
    
    void ShowConfirmBackToMap();
    void OnCancelBackToMap();
    void OnConfirmBackToMap();
    
	void PushOverlaysToTop();
	
	void ShowConfirmExitGame();
    class PVZ2UIDialog* ShowDataErrorDialog();
    void  KillDataErrorDialog();
    
    class PVZ2UIDialog* ShowPVZ2MessageDialog(const SexyString& i_headerText, const SexyString& i_bodyText);
    class PVZ2UIDialog* ShowPVZ2Dialog(float i_dialogWidth, float i_dialogHeight, PVZ2UIDialog* i_dialogToUse = NULL);
    class PVZ2UIDialog* ShowPVZ2Dialog(const SexyString& i_headerText, const SexyString& i_bodyText);
    class PVZ2UIDialog* ShowPVZ2DialogOneLine(const SexyString& i_headerText);
	void KillPVZ2Dialog();
	PVZ2UIDialog* GetPVZ2Dialog() const { return m_dialog; }
    bool IsPVZ2DialogExist() const;
    void DrawDarkeningLayer(Graphics* i_g, float backgroundAlpha = 0.5);
    void ShowRechargeNotice();
    void ShowRechargeRewardDisplayer(RechargeNode i_node);
    void ShowRechargeRewardDisplayer(bool bActivityReward, int iGemCount);
    bool IsRechargeRewardDisplayerValid();
    void KillRechargeRewardDisplayer();
    
	void ShowStoreUI(const std::string &i_focusPanel="");
   	void ShowStoreUINow(const std::string &i_focusPanel="");
	void KillStoreUI();
    
    void ShowGetPlantBagUI(const MagentoProductPropsPtr& prpduct, bool isRewardCoins);
    void KillGetPlantBagUI();
    
    void ShowGetNewerBagUI(bool i_ignoreCode = false,bool i_Newer=true);
    void KillGetNewerBagUI();
    
    void ShowGetGemsRestoreUI();
    void KillGetGemsRestoreUI();
    class GetGemsRestoreUI* GetGemsRestoreUI();

    void ShowNetConnectingUI(const std::string& i_tip = "[NET_CONNECTING]");
    void KillNetConnectingUI();
    
    void ShowRatingDialog();
    void KillRatingDialog();
    
    void ShowRewardPlantUI(PlantTypePtr i_plant);
    void KillRewardPlantUI();
    
    bool IsStoreUIShowing(){ return m_storeUI != NULL; }
    
    void ShowPlantRewardDialog(PlantTypePtr i_awardedPlant, bool i_starReward = false, int i_starNum = 0, bool i_isToPiece = false, bool i_view = false);
    void KillPlantRewardDialog();
    
    void ShowAccessorySwitchDialog(PlantTypePtr i_plant);
    void KillAccessorySwitchDialog();
    void DoSwitchAccessory();

    void ShowAccessoryAwardDialog(Image* i_qualityImg, Image* i_displayImg, SexyString i_name, SexyString i_description, SexyString i_boostDescription);
    void KillAccessoryAwardDialog();

    void ShowAvatarRewardDialog(PlantTypePtr i_awardedPlant, const std::string& title, const std::string& desc, bool i_starReward = false, int i_starNum = 0, PlantAvatarType eAvatar = E_AVATAR_NORMAL, int avatarIndex = -1);
    void KillAvatarRewardDialog();
    void ShowBuyPlantDialog(MagentoProductPropsPtr i_props, bool i_quick=true);
    void KillBuyPlantDialog();
    void ShowBuyAvatarDialog(MagentoProductPropsPtr i_props, bool i_quick=true);
    void KillBuyAvatarDialog();
    
    void ShowBuyGachaDialog(MagentoProductPropsPtr i_props, bool i_quick=true);
    void KillBuyGachaDialog();
	void ShowBuyGiftDialog(MagentoProductPropsPtr i_props, bool i_quick=true);
    void KillBuyGiftDialog();
    
	void ShowNewWorldDialog(std::string i_newLevelName);
    void KillNewWorldDialog();
    
    void ShowPlantLevelUpListView();
    void KillPlantLevelUpListView();
    class PlantLevelUpListView* GetPlantLevelUpListView(){return m_plantLevelUpListView;}

    void ShowArtifactCultivationListView();
    void KillArtifactCultivationListView();
    class ArtifactCultivationListView* GetArtifactCultivationListView(){return m_artifactCultivationListView;}

    void ShowPlantGeneEnhancementView();
    void KillPlantGeneEnhancementView();
    class PlantGeneEnhancementView* GetPlantGeneEnhancementView(){return m_plantGeneEnhancementView;}

    void ShowNostalgiaPVZGameView();
    void KillNostalgiaPVZGameView();
    class NostalgiaPVZGameView* GetNostalgiaPVZGameView(){return m_nostalgiaPVZGameView;}

    void ShowCustomLevelView();
    void KillCustomLevelView();
    class CustomLevelView* GetCustomLevelView(){return m_customLevelView;}


    void KillPlantTrialView();
    void ShowPlantTrialView(const std::string strPlantName);
    class PlantTrialViewUI* GetPlantTrialView() { return m_pPlantTrialView; }
    
    void ShowGameMaskUI(Sexy::SexyVector2 maskTargetPos, int maskTargetRadius, Sexy::Widget* event, std::string lawnDesc = "");
    void KillGameMaskUI();
    class GameMaskUI* GetGameMaskUI() { return m_pGameMaskUI; }
    
    void ShowPlantFamilyUI(int i_type = 1);
    void KillPlantFamilyUI();
    
    void ShowPlantAvatarListView();
    void KillPlantAvatarListView();
    class PlantAvatarListView* GetPlantAvatarListView(){return m_plantAvatarListView;}
    
    void ShowPlantLevelUpInfoDialog(MagentoProductPropsPtr i_props, bool ShowNotice = false, bool ShowSpecialPiece = false, int SpecialPieceId = 0);
    void KillPlantLevelUpInfoDialog();
    
    void ShowPlantAvatarInfoDialog(MagentoProductPropsPtr i_props, bool ShowNotice = false);
    void KillPlantAvatarInfoDialog();

    void ShowPlantAvatarPackageView(MagentoProductPropsPtr i_props);
    void KillPlantAvatarPackageView();
    
    void ShowPlantLevelUpCheckDialog(MagentoProductPropsPtr i_props);
    void KillPlantLevelUpCheckDialog();
    
    void ShowPlantSkillTipsUI(SexyString & sTips, int iPositonX, int iPostionY, int eType = 0, std::function<void(Widget*)> adjust = nullptr, bool isResumePause = false);
    void KillPlantSkillTipsUI();
    
    void ShowPlantStarLevelUpAnimUI(PVZ2UIStarLevelUp::AnimaType eType, std::string i_name = "", int i_level = 1);
    void KillPlantStarLevelUpAnimUI();
    class PVZ2UIStarLevelUp * GetPVZ2UIStarLevelUp();

    class PVZ2UILotteryResult* ShowLotteryResultUI();
    void KillLotteryResultUI();
    class PVZ2UILotteryResult* GetLotteryResultUI() { return m_lotteryResultUI; }
    
    void ShowChooseActivityLevelsDialog();
    void KillChooseActivityLevelsDialog();
    bool IsChooseActivityLevelsDialogValid() { return m_ChooseActivityLevelsDialog != NULL; }
    
    void ShowActivityHome();
    void KillActivityHome();
    bool IsActivityHomeValid() { return m_activityHome != NULL; }
    
    void ShowActivityHomeExtra();
    void KillActivityHomeExtra();
    bool IsActivityHomeExtraValid() { return m_activityHomeExtra != NULL; }

    void ShowActivityCollection();
    void KillActivityCollection();
    bool IsActivityCollectionValid() { return m_activityCollection != NULL; }

    void ShowNewPlayerCollection();
    void KillNewPlayerCollection();
    bool IsNewPlayerCollectionValid() { return m_newPlayerCollection != NULL; }

    // new icon    
    void ShowDailyActivityChooseDialog();
    void KillDailyActivityChooseDialog();
    bool IsDailyActivityChooseDialogValid() { return m_dailyActivityChooseDialog != NULL; }

    void ShowChallengeChooseDialog();
    void KillChallengeChooseDialog();
    bool IsChallengeChooseDialogValid() { return m_challengeChooseDialog != NULL; }
    
    void ShowShopChooseDialog();
    void KillShopChooseDialog();
    bool IsShopChooseDialogValid() { return m_shopChooseDialog != NULL; }

    void ShowWelfareChooseDialog();
    void KillWelfareChooseDialog();
    bool IsWelfareChooseDialogValid() { return m_welfareChooseDialog != NULL; }

    void ShowScrollBanner();
    void KillScrollBanner();
    void SetScrollBannerVisible(bool visible);
    bool IsScrollBannerValid() { return m_scrollBanner != NULL; }
    class WorldMap_ScrollBannerButton* GetScrollBanner() { return m_scrollBanner; }

    void ShowMarqueeView();
    void KillMarqueeView();
    void SetMarqueeViewVisible(bool visible);
    bool IsMarqueeViewValid() { return m_marqueeView != NULL; }
    class WorldMap_MarqueeView* GetMarqueeView() { return m_marqueeView; }

    Widget* GetRelativeParentPosition(HomeActityType id, SexyVector2& pos, std::string& i_res);// get relative position
    void ShowActivityInnerWidget(HomeActityType id, bool i_visible);

    void SetHasShownSpringGiftUI();
    bool HasShownSpringGiftUI();
    bool IsGettingSpringGift();
    void GettingSpringGift();
    void GotSpringGift();
    
    void ShowChoosePlantsDialog();
    void KillChoosePlantsDialog();
    bool IsChoosePlantsDialogValid() { return m_ChoosePlantsDialog != NULL; }
    class WorldMapChooseDialog* GetChoosePlantsDialog() { return m_ChoosePlantsDialog; }
    
    void ShowChooseWelfareDialog();
    void KillChooseWelfareDialog();
    bool IsChooseWelfareDialogValid() { return m_ChooseWelfaleDialog != NULL; }
    
    void ShowChooseRiddlesDialog();
    void KillChooseRiddlesDialog();
    bool IsChooseRiddlesDialogValid() { return m_ChooseRiddlesDialog != NULL; }
    
    
    void ShowLevelOfTheDayRewardDialog();
    void KillLevelOfTheDayRewardDialog();
    class LevelOfTheDayRewardDialog* GetLevelOfTheDayRewardDialog() { return m_pLevelOfTheDayRewardDialog; }
    
    void ShowPVPZombieLevelUpDialog();
    void KillPVPZombieLevelUpDialog();
    
    void ShowLevelOfTheDayProgressiveAwardDialog();
    void KillLevelOfTheDayProgressiveAwardDialog();
    class LevelOfTheDay_ProgressiveAwardDialog* GetLevelOfTheDayProgressiveAwardDialog() { return m_pLevelOfTheDay_ProgressiveAwardDialog; }

    void GotoNewWorld();
    void ShareWeChatNewWorld();
    void ShareBtnCallBack();
    void ShowShareDialog(SexyString i_ShareText);
    void KillShareDialog();
    bool IsCanSetWaitingGem()	{	return mWaitingServerGemCallBack == NULL;}
    void SetWaitingGemCallBack(Sexy::Delegate1<bool> i_callBack = NULL);
    void WaitingGemCallBack(bool i_Success);
    class PVZ2WaitingDialog* ShowWaitingDialog(const SexyString& i_headLabel, int i_waitTime);
    class PVZ2WaitingDialog* ShowWaitingDialog(const SexyString& i_headLabel, int i_waitTime, int w, int h);
    void KillWaitingDialog();
    
    void ShowLotteryUI(bool bCanDoLottery = true);
    void KillLotteryUI();
    
    void ShowGachaUI(const std::string &i_objectItem, bool bDiamond);
    void ShowGachaUI(const std::string &i_objectItem, bool bDiamond, GachaType i_type);
    void KillGachaUI();
    bool IsGachaUIShowing() { return m_gachaUI != NULL; }
    class GachaUI* getGachaUI();
    void ShowPowerPKView();
    void KillPowerPKView();
    
    void ShowLoginReward();
    void KillLoginReward();

    bool ShowDailySignReward(bool bAction=false);
    void KillDailySignReward();

    APP_WIDGET_DEFINE(DailySignRewardWithTW)
    APP_WIDGET_DEFINE(CodeRewardUI)
    APP_WIDGET_DEFINE(RechargeBundleUI)

    void ShowSkycityBossWarnig();
    void KillSkycityBossWarnig();
    
    class PlantAccessoryUI* getPlantAccessoryUI();
    void ShowPlantAccessoryUI(int iInitTab=-1, PlantTypePtr i_plantType = PlantTypePtr());
    void KillPlantAccessoryUI();
    bool HasPlantAccessoryUI();

    void ShowLanternRiddlesUI(bool i_canRiddle);
    void KillLanternRiddlesUI();
    class LanternRiddlesUI* getLanternRiddlesUI() {return m_lanternRiddlesUI; }
    
    void ShowRedPackUI(FestivalEventType i_type);
    void KillRedPackUI();
    class RedPackUI* getRedPackUI() {return m_redPackUI; }
    
    void ShowConsumptionRewardUI();
    void ShowConsumptionRewardDialog();
    void KillConsumptionRewardDialog();
    
    void ShowBirthdayRewardDialog();
    void KillBirthdayRewardDialog();
    
    void ShowIwatchRewardUI();
    void KillIwatchRewardUI();
    
    void ShowDailyAchievement();
    void KillDailyAchievement();
    
    void ShowRedPackOpenUI(int i_redPackOpenNum);
    void KillRedPackOpenUI();
    class RedPackOpenUI* getRedPackOpenUI() {return m_redPackOpenUI; }
    
    void ShowBoxOpenUI(const std::string& i_type);
    void KillBoxOpenUI();
    class BoxOpenUI* getBoxOpenUI() {return m_boxOpenUI; }
    
    void ShowServerBoxOpenUI();
    void ShowServerBoxOpenUI(const std::map<int, int>& i_prizePool, SexyString i_title);
    void KillServerBoxOpenUI();
    class ServerBoxOpenUI* getServerBoxOpenUI() {return m_serverBoxOpenUI; }
    
    void ShowPlantOfferOpenUI();
    void ShowPlantOfferOpenUI(const std::map<int, int>& i_prizePool, SexyString i_title);
	void KillPlantOfferOpenUI();
	class PlantOfferOpenUI* getPlantOfferOpenUI() {return m_plantOfferOpenUI; }

    void ShowOpenSurpriseBoxUI(const std::string& i_anim);
    void KillOpenSurpriseBoxUI();
    class OpenSurpriseUI* getSurpriseBoxOpenUI() {return m_surpriseBoxOpenUI; }
    
    void ShowChristmasLotteryReward(std::string i_plantName,bool i_IsPlant,int i_nRewardNum);
    void KillChristmasLotteryReward();
    
    void ShowDangerRoomRewardUI();
    void KillDangerRoomRewardUI();
    
    void ShowPVPMapUI();
    void KillPVPMapUI();
    class PVPMapUI* GetPVPMapUI() { return m_pvpMapUI; }
    
    void ShowArenaEndingUI(ArenaResult i_result, const std::vector<ZombieRecord>& i_zombieList, bool i_league, int iStarNum = 0);
    void KillArenaEndingUI();
    
    void ShowYetiEscapeDialog();
    void YetiEscapeRestartLevel();
    void ShowGemStoreConfirm(StoreType i_type=STORE_TYPE_GEM, bool i_quick=true);
    void OnConfirmGemStore();
    void OnQuitDangerRoomToWorldMap();
    void OnConfirmQuickGemStore();
    void OnCancelStore();
    void OnCancelQuickUnlock();
    void OnCancelStartGameOffLine();
    void OnOpenSystemSetting();
    bool CheckNetWork();
    bool CheckNetWork(const SexyString& i_errorTitle, const SexyString& i_errorText);
    void CheckNetWorkWifiIssue();
    void ShowMessageDialog(const std::string& title, const std::string& detail, const Delegate0& delegate);
    void ShowMessageDialogNoCallback(const std::string& title, const std::string& detail);
    void ShowMessageDialogWithOKButton(const std::string& title, const std::string& detail, const Delegate0& delegate);
    void ShowFakeAlert(int32 i_errorCode);
	std::string GetFormation();
    void ParseFormation(std::string i_info, int *i_formation, int i_row, int i_column);
    void onConfirmExitGame();
    void onCancelExitGame();
    void OnCloseDialog();
    void OnHandleUpdateGame();
    void OnOpenSystemSettingUpdateGame();
    void goToUpdateGame();
    
    void ShowReviveUI(ReviveMode i_mode);
	void KillReviveUI();
    
    void ShowStarLevelChallengeUI(int index);
    void ShowStarLevelChallengeUINow(int index);
    void KillStarLevelChallengeUI();

    void ShowNewerPresentUI(int itype);
	void KillNewerPresentUI();
    
    void ShowBattleStatementUI(BattleStatementUI::AccountUIType eType = BattleStatementUI::AccountUIType_Normal);
	void KillBattleStatementUI();
    bool IsBattleStatementUIShow() { return m_battleStatementUI != NULL; }
    
    void ShowFestivalEntranceUI(FestivalGameMode i_mode);
    void ShowFestivalEntranceUINow(FestivalGameMode i_mode);
	void KillFestivalEntranceUI();
    
	void ShowSummerEventEntranceUI();
	void killSummerEventEntranceUI();

	void ShowTimeTravelEventEntranceUI();
	void killTimeTravelEntranceUI();

	void ShowPlantDefenceEntrance();
	void killPlantDefenceEntrance();

    void ShowActiveEntranceUI(ActiveEntranceType i_type);
	void KillActiveEntranceUI();
    
    void OnFinishedInitDangerRoom(bool i_success);
    
    class ArenaEndingUI* GetArenaEndingUI() { return m_arenaEndingUI; }

	void ShowBuyItemUI(int i_type);	// BuyType
	void KillBuyItemUI();

	bool IsRechargeGiftUIValid() { return m_RechargeGiftUI != NULL; }
	void ShowRechargeGiftUI(const std::string& name = "");
	void KillRechargeGiftUI();
	class RechargeGiftUI*		GetRechargeGiftUI() const { return m_RechargeGiftUI; }
    
    void ShowRechargeRewardUI();
    void KillRechargeRewardUI();
    class RechargeRewardUI*		GetRechargeRewardUI() const { return m_RechargeRewardUI; }
    
    void KillTwoYearBirthday();
    void KillShareRewardView();
    void ShowTwoYearBirthday();
    class TwoYearBirthday* GetTwoYearBirthday() const { return m_TwoYearBirthday; }
    class ShareRewardView* ShowShareRewardView();
    void ShowExpPlantRewardView(const std::string& i_plantName);
    void KillExpPlantRewardView();
    void ShowShareWechatUI();
    void KillShareWechatUI();
    void ShowGemOfferHintUI();
    void KillGemOfferHintUI();
    void ShowPlantBundleUI();
    void KillPlantBundleUI();
    void ShowPlantSpecialOfferUI();
    void KillPlantSpecialOfferUI();
    class PlantSpecialOfferUI* getPlantSpecialOfferUI() {return m_PlantSpecialOfferUI; }

    void ShowDangerRoomSpecialOfferUI();
	void KillDangerRoomSpecialOfferUI();
	class DangerRoomSpecialOfferUI* getDangerRoomSpecialOfferUI() {return m_DangerRoomSpecialOfferUI; }
    void ShowRecallOfferUI();
	void KillRecallOfferUI();
	class RecallOfferUI* getRecallOfferUI() {return m_RecallOfferUI; }
#ifdef HOST_ANDROID
	void ShowCollectableAdUI();
	void KillCollectableAdUI();
	class CollectableAdUI* getCollectableAdUI() {return m_CollectableAdUI; }
#endif
    void ShowNationalHolidayUI();
    void KillNationalHolidayUI();
    void ShowOppoNewerEventUI();
    void KillOppoNewerEventUI();
    class PlantBundleUI* GetPlantBundleUI() const { return m_PlantBundleUI; }

	void ShowSevenDaysRewardView(const std::vector<NDLoginRewardBonus>& i_rewardList);
	void KillSevenDaysRewardView();
	bool IsShowSevenDaysRewardView();

	void ShowDailySignActivityRewardView(const std::vector<NDLoginRewardBonus>& i_rewardList);
	void KillDailySignActivityRewardView();
	bool IsShowDailySignActivityRewardView();

    bool IsSalesUIValid() { return m_salesUI != NULL; }
    void ShowSalesUI();
    void KillSalesUI();
    void RefreshSalesInfo();
    class SalesUI* GetSalesUI() const { return m_salesUI; }
        
    bool IsTransGenosisUIValid() { return m_transGenosisUI != NULL; }
    void ShowTransGenosisUI(bool i_refreshByNetwork = true);
    void KillTransGenosisUI();
    void RefreshTransGenosisUI();
    class TransGenosisUI* GetTransGenosisUI() const { return m_transGenosisUI; }
    
    bool IsTGPieceTableUIValid() { return m_tgPieceTableUI != NULL; }
    void ShowTGPieceTableUI();
    void KillTGPieceTableUI();
    void RefreshTGPieceTableUI();
    class TGPieceTableUI* GetTGPieceTableUI() const { return m_tgPieceTableUI; }
    
    bool IsTGAvatarPieceTableUIValid() { return m_tgAvatarPieceTableUI != NULL; }
    void ShowTGAvatarPieceTableUI();
    void KillTGAvatarPieceTableUI();
    void RefreshTGAvatarPieceTableUI();
    class TGAvatarPieceTableUI* GetTGAvatarPieceTableUI() const { return m_tgAvatarPieceTableUI; }
    
    bool IsGeilivableLotteryValid() { return m_geilivableLottery != NULL; }
    void ShowGeilivableLottery(bool i_refreshByNetwork = true);
    void KillGeilivableLottery();
    void RefreshGeilivableLottery();
    class GeilivableLottery* GetGeilivableLottery() const { return m_geilivableLottery; }

	bool IsGLDeliveryUIValid() { return m_GLDeliveryUI != NULL; }
	void ShowGLDeliveryUI();
	void KillGLDeliveryUI();
	class GLDeliveryInfoWidget* GetGLDeliveryUI() const { return m_GLDeliveryUI; }

    void ShowProbabilityDialog(const SexyString& alias);
    void KillProbabilityDialog();

	bool IsStoneLotteryValid() { return m_pStoneLottery; }
	void ShowStoneLottery(bool i_refreshByNetwork = true);
	void KillStoneLottery();
	void RefreshStoneLottery();
	class StoneLottery* GetStoneLottery() const { return m_pStoneLottery; }

	bool IsGLStoneLotInfoWidget() { return m_GLGLStoneLotUI != NULL; }
	void ShowGLStoneLotInfoWidget();
	void KillGLStoneLotInfoWidget();
	class GLStoneLotInfoWidget* GetGLStoneLotInfoWidget() const { return m_GLGLStoneLotUI; }
    
	bool IsDaveClubUIValid() { return m_pDaveClubUI; }
	void ShowDaveClubUI(bool i_refreshByNetwork = true);
	void KillDaveClubUI();
	class DaveClubUI* GetDaveClubUI() const { return m_pDaveClubUI; }

    bool IsCBTutorialUIValid() { return m_cbTutorialUI != nullptr; }
    void ShowCBTutorialUI();
    void KillCBTutorialUI();
    class CBTutorialUI* GetCBTutorialUI() const { return m_cbTutorialUI; }
    
    bool IsLostNetActivityUIValid() { return m_lostNetActivityUI != nullptr; }
    void ShowLostNetActivityUI();
    void KillLostNetActivityUI();
    class LostNetActivityUI* GetLostNetActivityUI() const { return m_lostNetActivityUI; }
    
    void ShowNetworkError();
    void ShowBonus(int i_bonusId, int i_quantity);
    int GetNewHintUIIndex(class HintUI* i_UI = nullptr);
    bool IsHintUIValid(int i_index);
    void ShowHintUI(int i_index);
    void KillHintUI(int i_index);
    class HintUI* CreateHintUI();
    class HintUI* GetHintUI(int i_index);
    
    void TestLuaExecute();
    
    bool IsStarConvertIValid() { return m_starConvert != NULL; }
    bool IsStarConvertOpened() { return m_isStarConvertOpened; }
    void ShowStarConvert();
    void KillStarConvert();
    class StarConvert* GetStarConvert() const { return m_starConvert; }
    
    bool IsLevelofDayEntranceValid() { return m_levelofDayEntrance != NULL; }
    void ShowLevelofDayEntrance();
    void KillLevelofDayEntrance();
    class LevelOfDayEntrance* GetLevelofDayEntrance() const { return m_levelofDayEntrance; }
    
    bool IsPlantAdventureUIValid() { return m_PlantAdventureUI != NULL; }
    void ShowPlantAdventureUI();
    void KillPlantAdventureUI();
    class PlantAdventureUI* GetPlantAdventureUI() const { return m_PlantAdventureUI; }
    
    bool IsAdventureTeamEditorUIValid() { return m_TeamEditorUI != NULL; }
    void ShowAdventureTeamEditorUI(WorldDungeonInfo i_dungeonInfo);
    void KillAdventureTeamEditorUI();
    class AdventureTeamEditorUI* GetAdventureTeamEditorUI() const { return m_TeamEditorUI; }
    
    bool IsAdventureOpenedUIValid() { return m_AdventureOpenedUI != NULL; }
    void ShowAdventureOpenedUI();
    void KillAdventureOpenedUI();
    class AdventureOpenedUI* GetAdventureOpenedUI() const { return m_AdventureOpenedUI; }
    
    bool IsAdventureBonusUIValid() { return m_AdventureBonusUI != NULL; }
    void ShowAdventureBonusUI(int i_dungeonId, SexyString i_dungeonName);
    void ShowAdventureBonusUI();
    void KillAdventureBonusUI();
    class AdventureBonusUI* GetAdventureBonusUI() const { return m_AdventureBonusUI; }
    
    bool IsAdventureSurpriseUIValid() { return m_AdventureSurpriseUI != NULL; }
    void ShowAdventureSurpriseUI(int i_dungeonId);
    void KillAdventureSurpriseUI();
    class AdventureSurpriseUI* GetAdventureSurpriseUI() const { return m_AdventureSurpriseUI; }
    
    bool IsAccessoryBonusUIValid() { return m_dailyAccessoryBonusUI != NULL; }
    void SetAccessoryBonusUI(class DailyAccessoryBonusUI* i_accessoryBonusUI) { m_dailyAccessoryBonusUI = i_accessoryBonusUI; }
    class DailyAccessoryBonusUI* GetAccessoryBonusUI() const { return m_dailyAccessoryBonusUI; }
    
    bool IsRedeemRewardUIValid();
    void ShowRedeemRewardUI(const std::string& payTime, const std::string& payCode, const std::string& orderNumber);
    void KillRedeemRewardUI();
    class RedeemRewardUI* GetRedeemRewardUI() const { return m_RedeemRewardUI; }

    void ShowJoustLeagueInfoScreen();
    void KillJoustLeagueInfoScreen();

    bool IsGoldenEggOpenUIValid() { return m_goldenEggOpenUI != NULL; }
    void CreateGoldenEggOpenUI();
    void GoldenEggOpenUIAddBonus(std::string i_bonusName, int i_quantity, int i_posId);
    void ShowGoldenEggOpenUI();
    void KillGoldenEggOpenUI();
    bool GoldenEggHasBonus();
    class GoldenEggOpenUI* GetGoldenEggOpenUI() const { return m_goldenEggOpenUI; }
    
    bool IsGoldenEggUIValid() { return m_goldenEggUI != NULL; }
    void SetGoldenEggUI(class GoldenEggUI* i_goldenEggUI) { m_goldenEggUI = i_goldenEggUI; }
    class GoldenEggUI* GetGoldenEggUI() const { return m_goldenEggUI; }
    
    class CoinStore* GetCoinStore() { return m_coinStore; }
	void ShowCoinStore(StoreType type = STORE_TYPE_COIN);
    void ShowPvpCoinStore();
    void ShowPvpUpgrade(PVPLabItemType type);
    
    void EnableCoinStoreTutorial(bool i_enable);
    void SetOpenActivityGameUI(FestivalGameMode eGameMode) { m_eGameMode = eGameMode; }
    void GetOpenActivityGameUI(FestivalGameMode & eGameMode);
	void KillCoinStore();
    void KillPvpCoinStore();
    void KillPvpUpgrade();
	bool IsCoinStoreShowing() { return m_coinStore != NULL; }
	bool IsWorldPreviewShowing() { return m_worldPreview != NULL; }
    bool IsWorldUnlockShowing() { return m_worldUnlock != NULL; }
	bool IsNewerPresentUIShowing() { return m_newerPresentUI != NULL; }
    bool IsReviveUIShowing() { return m_reviveUI != NULL; }
    bool IsFestivalEntranceUIShowing() { return m_festivalEntranceUI != NULL; }
	bool IsSummerEntranceUIShowing() { return m_summerEventEntranceUI != NULL; }
	bool IsTimeTravelEntranceUIShowing() { return m_timeTravelEntranceUI != NULL; }
	bool IsPlantDefenceEntranceUIShowing() { return m_plantDefenceEntrance != NULL; }
    bool IsPrimeTextReady();
    bool IsDailySignRewardShowing() { return m_dailySignReward != NULL; }
    
    void SetSpecialGemOffer(bool i_offer) { m_sGemOffer = i_offer; }
    bool HasSpecialGemOffer() { return m_sGemOffer; }

    void ShowPennyFuelStore(const std::string& i_metricsContext);
	void ShowPennyFuelStore();
	void KillPennyFuelStore();
	bool IsPennyFuelStoreShowing()
	{
		return false;
	}
	
	void LaunchMoreGamesWebpage();
	void LaunchMerchWebpage(bool i_fromMainMenu);
	void LaunchFAQWebpage();
	void LaunchEULAWebpage();
	void LaunchPrivacyWebpage();
	void LaunchTermsOfServiceWebpage();
    void LaunchTmallSotreWebpage();
    void LaunchNewVersionUrl();
    
    bool TestCanShowWorldmapButton();
    bool TestCanPopWorldmapActive();
    
    bool IsServiceAvailable(ServiceFlags i_flag) const;
    void SetServiceAvailable(ServiceFlags i_flag, bool i_available);
    
    void SetAdsMapRate(int rate) { m_adsMapRate = rate; }
    int GetAdsMapRate() { return m_adsMapRate; }
    void SetCurrentAdsMapRate(int rate) { m_currentAdsMapRate = rate; }
    int GetCurrentAdsMapRate() { return m_currentAdsMapRate; }
    
    void SetAdsMissionLimit(int level) { m_adsMissionLimit = "egypt"; m_adsMissionLimit += std::to_string(level); }
    std::string GetAdsMissionLimit() { return m_adsMissionLimit; }
    
    void SetAdsMapLimit(int level) { m_adsMapLimit = "egypt"; m_adsMapLimit += std::to_string(level); }
    std::string GetAdsMapLimit() { return m_adsMapLimit; }
    
    void SetCustomLevelEvaluationParam(float value){ m_customLevelEvaluationParam = value; }
    float GetCustomLevelEvaluationParam() { return m_customLevelEvaluationParam; }

    void SetUsingSpecialBackground(bool i_special) { m_usingSpecialBackground = i_special; }
    bool IsUsingSpecialBackground() { return m_usingSpecialBackground; }

    void SetAdsTotalRateMin(int rate) { m_minAdsTotalRate = rate; }
    void SetAdsTotalRateMax(int rate) { m_maxAdsTotalRate = rate; }
    void GenerateAdsMapRate();
    bool ShouldPopAds();
    void SetMaxAdsPerDay(int rate) { m_maxAdsPerDay = rate; }
    int GetMaxAdsPerDay() { return m_maxAdsPerDay; }
    void SetDaveShopAdsRate(int rate) { m_daveShopAdsRate = rate; }
    int GetDaveShopAdsRate() { return m_daveShopAdsRate; }
    bool ShouldPopSpAds(int i_type);
    void ShowSpAds(int i_type);
    void onWatchDaveShopAds(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);

#ifdef HOST_ANDROID // for android advertisement
    void SetAdsStatus(AdvertisementType adsType, bool status);
    bool GetAdsStatus(AdvertisementType adsType);
    void InitAdsStatus();
#endif

#ifdef HOST_ANDROID
    bool IsAdActivated();
    bool IsAdChannel(ViewType i_type);
    bool HasAnyServiceAvailable();
#endif

    void SetVersionLimit(std::string strMinVersion, std::string strMaxVersion);
    bool IsFitVersionLimit(void) const;

    bool CheckProfileOpen();

    bool IsUpdateActivity(int i_id);
    Image* GetUpdateActivityImage(ActivityImageType i_type, const std::string& i_resName);

	/// WorldMap data management
	void PopulateWorldMapData();
	void RemapWorldMapEvents();
	class WorldData* LoadSerializedMapData(const std::string& i_mapName);
	
	/// Touch
    void TouchBegan(const Sexy::Touch& i_touch) override;
    void TouchEnded(const Sexy::Touch& i_touch) override;
    void TouchMoved(const Sexy::Touch& i_touch) override;
    void TouchesCanceled() override;
	
	// Given our platform and resolution, how many pixels must a touch event
	// move before it's considered a 'drag' action?
	virtual int GetDragThresholdPixels();
	// Given our platform and resolution, how many pixels outside of a cursor
	// button must the user's touch move before we consider it a 'drag off button'
	// tool selection? Used in shovel and seed packet selection buttons
	virtual int GetButtonReleaseExpansionPixels();
	
	/// Player Profile -- TODO -- Move to ProfileUtils!
	
	bool					HasPlayerUnlockedFeature(GameFeature i_featureType);
    bool                    IsWorldHaveMower(std::string theWorldName);
	int						GetMaxSeedPacketCount();
	int						GetMaxPlantfoodCount();
	int						GetBonusStartingSun();

    bool IsNameMapperContains(IdNameInfo i_idName);
    bool IsNameMapperContainsId(int i_id);
    int GetNameMapperName(IdNameInfo);
    IdNameInfo GetNameMapperInfo(int i_id);
    void DrawPiecesInRect(Graphics* i_g, int i_id, Sexy::Rect& i_rect);
    
    time_t GetServerTimeOffset();
    time_t GetRealServerTime();
    time_t GetRealBeijingTime();
    void SetServerTimeOffset(time_t i_offset);
    void InitServerTimeOffset(time_t i_time);
    bool IsTimeNeedFix();
    struct tm* BeijingTime(const time_t* i_time);
    
	/// String Utility Functions
	SexyString GetMoneyString(int i_amount);
    /// Resource Group Management
    // The group loading life cycle starts with PrepareLoadGroup, then we check the progress of the load
    // with GetGroupLoadProgress, once the group is fully loaded, we call FinalizeGroupLoad. Then we 
    // can use the data associated with that group. 
    // Groups are defined in resprops.txt
    // start the loading process. 
    void    PrepareLoadGroup(const std::string& i_groupName);
    void 	PrepareLoadGroups(const std::vector<std::string> &i_groupNames);
   
    // loads the group into the game synchronously
    void	LoadGroups(const std::vector<std::string>& i_groupNames);
    void    LoadGroup(const std::string& i_groupName);
    bool    CanLoadGroup(const std::string& i_groupName);
    bool    CanLoadGroups(const std::vector<std::string>& i_groupNames);
    bool    IsWorldRSBFileLoaded(const std::string& i_world_name);
    
    // Ask if load is complete
    bool    IsGroupLoadComplete(const std::string& i_groupName);
    bool    IsGroupLoadComplete(const std::vector<std::string>& i_groupNames);
    // call this on groups to complete the loading process
    void    FinalizeGroupLoad(const std::string& i_groupName);
    void 	FinalizeGroupLoads(const std::vector<std::string> &i_groupNames);
    // get the progress of the load of a group.
    float   GetGroupLoadProgress(const std::string& i_groupName);
    float   GetGroupLoadProgress(const std::vector<std::string>& i_groupNames);
    // queue the removal of data from memory until the next time the ResStreamsManager is ticked
    void    DeleteGroups(const std::vector<std::string>& i_groupNames);
    void    DeleteGroup(const std::string& i_groupName);
	
	// Prints out the refcount for each group load request that went through LoadGroup
	void	LogGroupLoadCounts() const;
    //void EmitCrashTrackingResourceGroupString() const;
	void ApplyNetworkContentChanges();
	bool NetworkContentCheckComplete();
	void CheckForNetworkContentChanges();
//	void CheckForNetworkContentChanges(bool result=true);
    
    PVZVersionNetworkManager&   GetVersionNetworkManager();
    PVZRechargeCheckServer&     GetRechargeCheckServer();
    
    //add string table for dlc new string id
    void AddLocalizedLawnStringFile(const std::string & fileName);
    void SetLocalizedLawnStringFile();
    virtual bool GetCheatsEnabled() override;
    virtual void SetCheatsEnabled(bool i_enabled) override;
    virtual bool KeyDown(int theKey) override;
    virtual bool DebugKeyDown(int i_key) override;
	virtual bool PhysicalKeyDown(int theKey);
	const class GameCenterProxy* GetGameCenterProxy() const { return m_gcp; }
	MagentoLanguage GetMagentoLanguage() const { return m_magentoLanguage; }
    void RemoveAllCaches();
	void showDiffProfileSummary();
	void closeDiffProfileSummary();
	void setProfileOpened(bool i_open) { m_profileOpened = i_open; }
	bool isProfileOpened() { return m_profileOpened; }
	void setSyncProfileSuccess(bool i_success) { m_syncProfileSuccess = i_success; }
	bool isSyncProfileSuccess() { return m_syncProfileSuccess; }
	void syncProfileSummaryWithServer();
	bool isProfileSyncing() { return m_isSyncing; }
	void setProfileSyncing(bool i_isSyncing) { m_isSyncing = i_isSyncing; }
	void setCanDealProfile(bool i_canDealProfile) { m_canDealProfile = i_canDealProfile; }
	bool canDealProfile() { return m_canDealProfile; }
	void setProfileConnected(bool i_connected) { m_connectedProfile = i_connected; }
	bool getProfileConnected() { return m_connectedProfile; }
	void ChooseProfile(bool i_cloudOlder);

#ifdef HOST_ANDROID

	class QiHooPlatform* GetQiHooPlatform() const { return m_qihoo; }
	void SetQiHooLogin(bool i_login) { m_hasQihooLogin = i_login; }
	bool GetQiHooLogin() { return m_hasQihooLogin; }

	//class WechatPlatform* GetWechatPlatform() const { return m_wechat; }
#endif
    
    std::string GetDangerRoomLevelName();
    std::string GetTargetDangerRoomLevelName(DangerRoomLevelType i_type);
    DangerRoomLevelType GetTargetDangerRoomLevelType(std::string i_name);
    
    void silenceRelogin();

    // in pooyan module
    
    void AddModuleInfo(ModuleInfo i_module) { m_moduleInfo |= i_module; }
    void RemoveModuleInfo(ModuleInfo i_module) { m_moduleInfo &= ~i_module; }
    bool IsInModule(ModuleInfo i_module) { return (i_module & m_moduleInfo); }
    
    virtual void WechatShareSuccess() override;
    virtual void WeChatShareFailed();
    void ShowPvpCoinBuyConfirm();
    void ShowChildrenDayUI();
    pvztime_t GetLastTouchEndTime();
    
    void SetIsInited(bool i_inited) { m_initDone = i_inited; }
    bool IsInited() { return m_initDone; }
    
    void showSpecifiedWidget(Sexy::Widget* widget, bool bFocus = true, bool bBaseModal = false);
    void removeSpecifiedWidget(Sexy::Widget* widget, bool bBaseModal = false);

	bool isSameDay(time_t time1, time_t time2) const;

	bool isOppoNewerOptimizationOpen();
	bool isOppoCukeTipShow();

    bool IsForbiddenPlatform();// for android check list
    

    void LoadRsbsExtraProc();// for android
    bool NeedDecompressRsbsExtra();
    bool NeedDelayLoadRSB();

    std::string GetMapName(int index);
    int GetMapNameIndex(std::string world);
    int GetAllMapCount();
    bool IsNormalWorld(std::string world);
    bool IsCurrentNormalWorld();

private:
	bool m_profileOpened;
	class ProfileSummaryComparer* m_profileSummaryComparer;
	void onProfileSummarySelectResult(int i_result);
	bool m_syncProfileSuccess;
	bool m_isSyncing;
	bool m_canDealProfile;
	bool m_selfSync;
	bool m_connectedProfile;
	void onLoginiCloudServerFinish(bool i_success);
	void onSyncProfileSummaryFinish(bool i_success);
	void onSyncProfileToServer(bool i_success);
	void onSyncProfileFromServer(bool i_success);
	void goToMainMenu();
private:
	bool	internalLoadGroup(const std::string& i_groupName);
public:
#ifdef LUA_COMPILE
    //c03 add for create iamge in lua
    Image * GetImagePointerFromStringId(const std::string& i_imageName);
#endif
    /// Image Resource Finders -- TODO -- Move out of here!
    
    ImagePtr GetImageFromStringId(const std::string& i_imageName, const int i_overrideRes = 0);
    ImagePtr GetUIImageFromStringId(const std::string& i_imageName);
    ResourceInfoTypes::ImageRes* GetImageInfoFromStringId(const std::string& i_imageName, const int i_overrideRes = 0);
    ResourceInfoTypes::ImageRes* GetUIImageInfoFromStringId(const std::string& i_imageName);
    ResourceInfoTypes::ImageRes* GetImageInfoFromImageRef(RtWeakPtr<Image>& i_image);
	/// Simple accessors
	
	class MetricsCollector*			GetMetricsCollector()	{	return m_metricsCollector;		}
	class CrazyNPCManager*			GetNarrationSystem()	{	return m_npcManager;			}
	class PostProcessOverlayWidget*	GetPostProcessing()		{	return m_postProcessWidget;		}
	class WorldMap*					GetWorldMap() 			{	return m_worldMap;				}
    class TransitionOverlayWidget* 	GetTransitionOverlay() 	{ 	return m_transitionOverlay; 	}
    const std::string&				GetLastCompletedLevel() {   return m_lastClearedLevel;      }
    
    // Simple Setters
    void    SetLastCompletedLevel(const std::string& i_clearedLevel)       {   m_lastClearedLevel = i_clearedLevel; }
	
	bool							IsPauseMenuOpen()			{	return (m_pauseMenu != NULL);	}

	// Arcade unlock moment management
	// Wish this wasn't in LawnApp, but didn't want to make it static.
	void QueueUnlocksFromArcadeLevel(const std::string& i_levelName)
	{
		m_queuedArcadeUnlockSource = i_levelName;
	}

	std::string GetAndClearQueuedArcadeUnlockSource()
	{
		std::string source = m_queuedArcadeUnlockSource;
		m_queuedArcadeUnlockSource.clear();
		return source;
	}

	class WorldMapList*				GetWorldMapList();
    
    //PVZ2_CHINESE_BEGIN
    int     getCurrentWorldIndex();
    int     getCurrentChallengeIndex();
    class DropOutItems*             GetDropItemsList();
    class ChallengeGroupData*    GetChallengeDropItemsList(std::string groupid);
    class ActivityDropGroup*        GetActivityDropGroup();
    //PVZ2_CHINESE_END
    
    class PHPServerConfig*          GetServerPHPConfig();
    
    class ActivityConfig*           GetActivityConfig();
    class GachaConfig*              GetGachaConfig();
    class TreasureConfig*           GetTreasureConfig();

    class TreasureConfig*           GetPedTreasureConfig();
    class StoreGiftConfig*          GetStoreGiftConfig();
    class DailyRewardConfig*		GetDailyRewardConfig();
    //class MiniGameActivity*         GetMiniGameActivity();
	// Loading profiles, potentially asynchronously over a network
	bool GetDoneLoadingProfiles(){ return m_doneLoadingProfiles; }
	bool GetNetworkRequestsCompleted();
	
	bool IsConnectOnWifi();
	bool IsConnectedOnWWAN();
    bool IsConnected();
    bool IsNetworkModuleOK();
	bool IsConnecting();
	
	void SetUserHasDisabledUsageSharing(bool i_disabled);
	bool UserHasDisabledUsageSharing();
	
	void SetUsageSharingSystemStates();
	
    int GetStartingResolution();
    
    bool CheckVersion();
    void VersionForceUpdate();
    void RequestGetRechargeAmoutFromServer();
    
    void ShowFakeSaveWarning(int32 i_errorCode); //PVZ2_CHINESE Copy Protection
    
    bool IsPlatformHD();
    bool IsDev();
    PlatformType GetPlatform();
	PlatformType GetPlatformByNewPackageName();
	std::string	 GetAppNameForiCloud();
    SexyString   GetAboutContentStringId();
    bool IsNationalDay(bool i_canUseLocalTime = true);
    uint32 GetLevelDaysByLevelString(const std::string& i_level);
    bool IsQQAndSingleDay();
    bool NeedShowLoginRewardDialog(bool i_canUseLocalTime = false);
	void loadPlayerProfiles();
    void IsNeedRefreshLoginDays(bool bRefresh)
    {
    	m_bRefreshLoginDays = bRefresh;
    }
    bool NeedRefreshLoginDays(){ return m_bRefreshLoginDays; }
    void  SetShouldBackToMapAtDangerRoom(bool bYes) { m_bBacktoMapAtDangerRoom = bYes; }
    bool  GetShouldBackToMapAtDangerRoom() { return m_bBacktoMapAtDangerRoom; }
    
    RedPacketRewardInfo&    GetRedPacketRewardInfo() { return m_stRedPacketRewardInfo; }
    class PlantTrialConfig&       GetPlantTrialConfig() { return m_stPlantTrialConfig; }
    RechargeRewardConfig&   GetRechargeRewardConfigInfo() { return m_stRechargeRewardConfig; }
    ConsumptionRewardInfo& GetConsumptionRewardInfo() { return m_stConsumptionRewardInfo; }
    DailyAchievementInfo& GetDailyAchievementInfo() { return m_stDailyAchievementInfo; }
    LevelOfTheDayConfigInfo& GetLevelOfTheDayConfigInfo() { return m_stLevelOfTheDayConfigInfo; }
    NationalDayRewardConfigInfo& GetNationalDayRewardConfigInfo() { return m_stNationalDayRewardConfigInfo; }
    RebateRewardConfig& GetRebateRewardConfig() { return m_stRebateRewardConfig; }
    void RefreshConsumptionRewardInfo(){m_stConsumptionRewardInfo.InitDate();}
    
    PlantAdventureConfig& GetPlantAdventureConfig() { return m_stPlantAdventureConfig; }
    void RefreshPlantAdventureConfig(){ m_stPlantAdventureConfig.Refresh();}
    
    StarConvertConfig& GetStarConvertConfig() { return m_stStarConvertConfig; }
    void RefreshStarConvertConfig(){ m_stStarConvertConfig.Refresh();}
    
    LostNetActivityConfig& GetLostNetActivityConfig() { return m_stLostNetActivityConfig; }
    void RefreshLostNetActivityConfig(){ m_stLostNetActivityConfig.Refresh();}
    
    int GetPlantAdventureTabIndex() { return m_PlantAdventureTabIndex; }
    void SetPlantAdventureTabIndex(int i_index){ m_PlantAdventureTabIndex = i_index; }

    WorldCupConfig& GetWorldCupConfig() { return m_stWorldCupConfig; }
    void RefreshWorldCupConfig(){ m_stWorldCupConfig.Refresh();}

    JoustPlantPowerConfig& GetJoustPlantPowerConfig() { return m_stJoustPlantPowerConfig; }
    void RefreshJoustPlantPowerConfig(){ m_stJoustPlantPowerConfig.Refresh();}

    time_t GetStartLoadingTime() { return m_startLoadingTime; }

    double GetDecompressDuration() { return m_decompressTime; }
    void SetLoadingDuration(double i_duration) { m_loadingTime = i_duration; }
    double GetLoadingDuration() { return m_loadingTime; }
    time_t GetLoadingBeginTime() { return m_loadingBeginTime; }
    const std::string GetSessionId() { return m_sessionId; }
    
    time_t GetTimeStamp(const std::string& strDate, const std::string& strDateFormat = "%Y%m%d%H%S");
    
    bool IsAutoSmoking();
    void SetAutoSmokingStart() {m_bIsAutosmoking = true;}

    void SetLoginSuccess(bool i_success) { m_bIsLoginSuccess = i_success; }
    bool IsLoginSuccess() { return m_bIsLoginSuccess; }

    void SetPaymentResultInfo(PaymentResultInfo& i_info) { m_paymentResultInfo = i_info; }
    PaymentResultInfo& GetPaymentResultInfo() { return m_paymentResultInfo; }

    bool IsPlatformChannel();
    bool IsChannelWithBigDeal();

    void SetADBlackList(const std::vector<std::string>& i_list) { m_adBlackList = i_list; }
    const std::vector<std::string>& GetADBlackList() { return m_adBlackList; }

    void SetWatchADBlackList(const std::vector<std::string>& i_list) { m_watchADBlackList = i_list; }
    bool IsInWatchADBlackList(const std::string packageName);

    //for oppo
#ifdef HOST_ANDROID
    OfferBundleConfig& GetOfferBundleConfig() { return m_offerBundleConfig; }
#endif

    void SetProfileCreatedTime(const std::string& i_time) { m_profileCreatedTime = i_time; }
    const std::string& GetProfileCreatedTime() { return m_profileCreatedTime; }

    void SetIsNewUser(bool i_new) { m_isNewUser = i_new; }
    bool GetIsNewUser() { return m_isNewUser; }

#ifdef HOST_ANDROID
    void SetAndroidSDKInitStatus(int isEnd, int status);
    int GetAndroidSDKInitStatus();
    int IsAndroidSDKInitEnd();
#endif

private:
    bool SetWidthHeight(int inNewHeight);
    
	void onDoneLoadingProfiles();
	bool m_doneLoadingProfiles;
    
	void onGameCenterAuthenticationChanged(bool i_connected);
    
    void onItemPurchasedFromStore(MagentoProductProps* i_props);
    void onEASquaredAdvertisementsWillOpen();
    void onEASquaredAdvertisementsClosed();
    void onEASquaredFlowEnded(const std::string& i_placementOrigin, int i_coinsEarned, int i_videosWatched);
    
    void OnFetchVersionComplete();
    void OnRechargeCheckComplete();
    void StartRechargeCheck();
    
    void onCopySaveWarningOK(); //PVZ2_CHINESE Copy Protection
	
    bool ChenckStartShowProgressBar();
    void OnPvpCoinBuyButtonUp(class UIMessageBox* dialog, int button);
    
    void onFaiicck();
    void onMatikck();
    
    void OnLuaNotify(const std::string& rStrEvent);
	/// Frequently accessed member variables
public:
	class Board*				m_board;
	class GameStateMgr			m_gameStateMgr;
    class PromoManager*			m_promoManager;
	class BusyAnimationManager*	m_busyManager;
    Sexy::Point GetScreenContentOffset();
    
	float m_contentResolutionWidth;
	float m_contentResolutionHeight;
    
	std::vector<GachaGet> m_vecGachaGetInfo;
	void	GatherGachaLogInfo(std::vector<class GachaRewardUI*> i_vecReward);
	GachaPriceInfo				m_gachaPriceInfo;

	std::string GetNetworkType();

	std::string GetDeviceMODEL();
	std::string GetDeviceBRAND();
	int  GetDeviceCardType();

protected:
    virtual void onPurchaseRefreshComplete(Sexy::IPurchaseDriver* purchase_driver);
private:
	std::map<std::string, int>  m_groupRefCounts;
	std::map<std::string, int>  m_preloadGroupRefCounts;
	
	/// Infrequently accessed member variables
public:
    bool                            m_bRechargeUseMoney = true;
	int                             m_appRandSeed;
	BoardResult                     m_lastBoardResult;
	int                             m_lastBoardRetries;
    
    std::string                     m_configDLCVersion;
    std::string                     m_luaDLCVersion;
    int								m_localRsbVersion;
    
    //for activity popup
    int                             m_numberOfGamesPlayed;
    int                             m_popupInterval;
    bool                            m_bNeedPopup;
    bool                            m_bGamesPlayed;
    
	class LevelProperties*          m_levelProperties;
    bool                            m_testMode;	// used by PVZRemoteControl
    bool                            m_recordStringsEnabled;	// Record all strings used in LawnStrings
    //bool                            m_ignorePatching;
	
	bool                            m_hasDisabledUsageSharing;
	//bool                            m_hasPermissionToDownloadOnWWAN;
	//bool                            m_hasAskedForPermissionToDownloadOnWWANOnce;
	
	//std::string                     m_lastPatchDownloadProgressDismissed;
    
    bool                            m_showGlyphCache;
    bool                            m_bYetiDie;
    bool                            m_hasChangeFakeData;
    bool                            m_bNeedCheckFakeFromServer;
    bool							m_bRefreshDailyRewardConfig;
    
    //DLC Log
    bool                            m_bInstalledAPK;
    bool                            m_bInstalledRES;
    bool							m_bIsNewUpdate;
    
    PVZCachedNetworkTableManager	m_networkTableManager;
    
    int                             m_iQuickUnlockGem;
    
    ModuleInfo                      m_moduleInfo;
	// for Cheat
	bool                            m_bShowPlantID;
	int								m_iTreasureChoose;
	int								m_gameChargeType;

    ArenaPlantType                  m_arenaType;
    
    bool                            m_bUseNewApp;
    
private:
    class UniverseWorldInfo*        m_universeWorldInfo;
	class TitleScreen*				m_titleScreen;
	class AlmanacWidget*			m_almanac;
    class ArenaAwakenWidget*        m_awakenWidget;
	class StoreUI*					m_storeUI;
    class RechargeRewardDisplayer*  m_rechargeRewardDisplayer;
    class LotteryUI*                m_LotteryUI;
    class GachaUI*                  m_gachaUI;
    class PowerPKWidget*            m_powerPKView;
    class LoginReward*				m_loginReward;
    class DailySignReward*          m_dailySignReward;
    class SkycityBossWarningInfo*   m_skycityBossWarningInfo;
    class LanternRiddlesUI*         m_lanternRiddlesUI;
    class RedPackUI*                m_redPackUI;
    class RedPackOpenUI*            m_redPackOpenUI;
    class BoxOpenUI*                m_boxOpenUI;
    class ServerBoxOpenUI*          m_serverBoxOpenUI;
    class PlantOfferOpenUI* 		m_plantOfferOpenUI;
    class OpenSurpriseUI*           m_surpriseBoxOpenUI;
    class PlantAccessoryUI*			m_plantAccessoryUI;
    class PVZ2UIBuyPlantDialog*     m_buyPlantDialog;
    class PVZ2UIBuyAvatarDialog*	m_buyAvatarDialog;
    class PVZ2UIBuyGachaDialog*     m_buyGachaDialog;
    class PVZ2UIBuyGiftDialog*      m_buyGiftDialog;
	class FriendListView*           m_friendListView;
    class GameRankView*             m_gameRankView;
    class ViewFormationWidget*      m_viewFormation;
    class PlantFamilyUI*            m_pPlantFamilyUI;
    class PlantLevelUpListView*     m_plantLevelUpListView;
    class PlantTrialViewUI*         m_pPlantTrialView;
    class GameMaskUI*               m_pGameMaskUI;
    class PlantAvatarListView*      m_plantAvatarListView;
    class PlantAvatarInfoDialog*    m_plantAvatarInfoDialog;
    class PlantAvatarPackageView*   m_plantAvatarPackageView;
    class PlantLevelUpInfoDialog*   m_plantLevelUpInfoDialog;
    class PlantLevelUpCheckDialog*  m_plantLevelUpCheckDialog;
    class PlantSkillTipsUI*         m_plantSkillTipsUI;
    class PVZ2UIStarLevelUp*        m_plantStarLevelUpAnimUI;
    class WorldMapChooseDialog*     m_ChooseActivityLevelsDialog;
    class WorldMapChooseDialog*     m_ChoosePlantsDialog;
    class WorldMapChooseDialog*     m_ChooseWelfaleDialog;
    class WorldMapChooseDialog*     m_ChooseRiddlesDialog;
    class WorldMapActivityHome*     m_activityHome;
    class WorldMapActivityHomeExtra* m_activityHomeExtra;
    class UIActivityCollection*     m_activityCollection;
    class UINewPlayerCollection*    m_newPlayerCollection;
    // new icon
    class WorldMapDailyActivityChooseDialog* m_dailyActivityChooseDialog;// new icons
    class WorldMapChallengeChooseDialog* m_challengeChooseDialog;
    class WorldMapShopChooseDialog* m_shopChooseDialog;
    class WorldMapWelfareChooseDialog* m_welfareChooseDialog;
    class WorldMap_ScrollBannerButton* m_scrollBanner;
    class WorldMap_MarqueeView* m_marqueeView;
    class ArtifactCultivationListView* m_artifactCultivationListView;
    class NostalgiaPVZGameView* m_nostalgiaPVZGameView;
    class CustomLevelView* m_customLevelView;
    class PlantGeneEnhancementView* m_plantGeneEnhancementView;

    class BorrowPlantUI*            m_borrowPlant;
	class CoinStore*				m_coinStore;
    class PvpCoinStore*             m_pvpCoinStore;
    Widget*                         m_pvpUpgrade;
    class NewerPresentUI*           m_newerPresentUI;
    class BuyItemUI*				m_BuyItemUI;
    class RechargeGiftUI*           m_RechargeGiftUI;
    class RechargeRewardUI*         m_RechargeRewardUI;
    class TwoYearBirthday*       	m_TwoYearBirthday;
    class ShareRewardView*       	m_ShareRewardView;
    class ExpPlantRewardView*       m_ExpPlantRewardView;
	class NDDailyLoginRewardView*   m_NDDailyLoginRewardView;
	class DailySignRewardView*   	m_DailySignRewardView;
    class ShareWechatUI*       		m_ShareWechatUI;
    class GemOfferHintUI*			m_GemOfferHintUI;
    class PlantBundleUI*			m_PlantBundleUI;
    class Widget* 					m_joustLeagueScreen;
    class PlantSpecialOfferUI*		m_PlantSpecialOfferUI;
    class DangerRoomSpecialOfferUI*	m_DangerRoomSpecialOfferUI;
    class RecallOfferUI*			m_RecallOfferUI;
#ifdef HOST_ANDROID
    class CollectableAdUI*			m_CollectableAdUI;
#endif
    class NationalHolidayUI*		m_NationalHolidayUI;
    class OppoNewerEventUI*			m_OppoNewerEventUI;
    class SalesUI*                  m_salesUI;
    class GeilivableLottery*        m_geilivableLottery;
	class StoneLottery*				m_pStoneLottery;
	class DaveClubUI*				m_pDaveClubUI;
    class TransGenosisUI*           m_transGenosisUI;
    class LostNetActivityUI*         m_lostNetActivityUI = nullptr;
    class CBTutorialUI*             m_cbTutorialUI = nullptr;
    class TGPieceTableUI*           m_tgPieceTableUI;
    class TGAvatarPieceTableUI*     m_tgAvatarPieceTableUI;
    class GLDeliveryInfoWidget*     m_GLDeliveryUI;
	class GLStoneLotInfoWidget*     m_GLGLStoneLotUI;
    std::map<int, class HintUI*>    m_hintUICollector;
    class StarConvert*              m_starConvert;
    bool                            m_isStarConvertOpened;
    class LevelOfDayEntrance*       m_levelofDayEntrance;
    class AdventureOpenedUI*        m_AdventureOpenedUI;
    class PlantAdventureUI*         m_PlantAdventureUI;
    std::string                     m_savedAdventureDungeonName;
    class AdventureTeamEditorUI*    m_TeamEditorUI;
    class AdventureBonusUI*         m_AdventureBonusUI;
    class AdventureSurpriseUI*      m_AdventureSurpriseUI;
    class DailyAccessoryBonusUI*    m_dailyAccessoryBonusUI;
    class GoldenEggOpenUI*          m_goldenEggOpenUI;
    class GoldenEggUI*              m_goldenEggUI;
    class ReviveUI*                 m_reviveUI;
    class StarLevelChallengeUI*     m_starLevelChallengeUI;
    class FestivalEntranceUI*       m_festivalEntranceUI;
	class SummerEventEntranceUI*	m_summerEventEntranceUI;
	class TimeTravelEntranceUI*		m_timeTravelEntranceUI;
	class PlantDefenceEntrance*		m_plantDefenceEntrance;
    class BattleStatementUI*        m_battleStatementUI;
    class ActiveEntranceUI*         m_ActiveEntranceUI;
	class GetPlantBagUI*            m_GetPlantBagUI;
    class GetNewerBagUI*            m_GetNewerBagUI;
    class GetGemsRestoreUI*         m_GetGemsRestoreUI;
    class NetConnectingUI*          m_netConnectingUI;
    class RedeemRewardUI*			m_RedeemRewardUI;
#ifdef HOST_IPHONEOS
    class RatingDialog*             m_ratingDialog;
#endif
    class RewardPlantUI*            m_rewardPlantUI;
    class WorldMap*					m_worldMap;
	class PVZ2UIWorldPreview*		m_worldPreview;
	class PVZ2UIUnlockPreview*		m_worldUnlock;
	class CrazyNPCManager*			m_npcManager;
	class TransitionOverlayWidget*	m_transitionOverlay;
	class MainMenu*					m_mainMenu;
	class PVZ2UIDialog*				m_dialog;
    class PVZ2UIDialog*				m_dataErrorDialog;  //show antihack
	class NewOptionsDialog*			m_pauseMenu;
	class PVZ2WaitingDialog*		m_waitingdialog;
    class ArenaEndingUI*            m_arenaEndingUI;

    class CSpringGiftActivityRewardUI*  m_SpringGiftRewardUI;
    class ConsumptionRewardDialog*  m_pConsumptionRewardDialog;
    
    class DailyAchievement*         m_dailyAchievement;
    class LevelOfTheDayRewardDialog* m_pLevelOfTheDayRewardDialog;
    class LevelOfTheDay_ProgressiveAwardDialog* m_pLevelOfTheDay_ProgressiveAwardDialog;
    class PVPZombieLevelUpDlg* m_pPVPZombieLevelUpDialog;

    class BirthdayRewardDialog*     m_pBirthdayRewardDialog;
    
    class ChristmasLotteryReward*   m_pChristmasLotteryReward;
    class IwatchRewardUI*           m_pIwatchRewardUI;

    class PVPMapUI*                 m_pvpMapUI;
    class EndLevelUI*               m_endLevelUI;
    
    class BoardZombieAlmanacUI*     m_boardZombieAlmanacUI;
    

    class PVZ2UILotteryResult*      m_lotteryResultUI;
    
    class GachaDisplayerDialog*     m_gachaDisplayerDialog;

    PVZVersionNetworkManager        m_versionNetworkManager;
    PVZRechargeCheckServer          m_rechargeCheckServer;
    
	class PostProcessOverlayWidget*	m_postProcessWidget;
    class MetricsCollector*         m_metricsCollector;
	
	RtWeakPtr<class WorldMapList>	m_worldMapList;
	std::vector<std::string>		m_featureTypeData;
	
    bool                            m_hasShownSpringGiftUI;
    bool                            m_isLoadingFontsLoaded;
	
	class GameCenterProxy*			m_gcp;
    
    bool                            m_gettingSpringGift;
	bool							m_isMusicPlaying;
	int								m_MusicPausedCount;
    uint32							m_callbackEventID;
	bool							m_bShownNotice_;
	//bool							m_bShowVersionNotice;
	bool 							m_bRefreshLoginDays;
    
    ServiceFlags                    m_serviceFlags;

    std::string                     m_strMinVersion;
    std::string                     m_strMaxVersion;
    
    int                             m_adsMapRate = -1;
    int                             m_currentAdsMapRate = 0;
    std::string                     m_adsMissionLimit;
    std::string                     m_adsMapLimit;
    float							m_customLevelEvaluationParam;

    bool							m_usingSpecialBackground;
    // Android added
    int								m_minAdsTotalRate = -1;
    int								m_maxAdsTotalRate = -1;
    int								m_maxAdsPerDay = 0;

#ifdef HOST_ANDROID
    bool 							m_adsStatus[(int)ADS_MAX];// for android advertisement status
#endif
    int								m_daveShopAdsRate = 0;

	
    std::string                     m_lastClearedLevel;
    std::string 					m_queuedArcadeUnlockSource;
   	time_t							m_nextContentCheckTime;
	Delegate0						m_onConfirmDownloadPermission;
	Delegate0						m_onRejectDownloadPermission;
	MagentoLanguage					m_magentoLanguage;
    StoreType                       m_storeType;
    FestivalGameMode                m_eGameMode;
    
    bool                            m_needFixingTime;
    time_t                          m_serverTimeOffset;
    bool                            m_bLoadVersionCompleted;
    bool                            m_bRechargeCheckCompleted;
    bool                            m_bCheckCopyCompleted;
    bool                            m_hasWwiseError;
    std::string						m_newLevelToJump;
    Delegate1<bool> 				mWaitingServerGemCallBack;//waiting call back
    
    bool                            m_bBacktoMapAtDangerRoom;
    
    RedPacketRewardInfo             m_stRedPacketRewardInfo;
    PlantTrialConfig                m_stPlantTrialConfig;
    RechargeRewardConfig            m_stRechargeRewardConfig;
    ConsumptionRewardInfo           m_stConsumptionRewardInfo;
    DailyAchievementInfo            m_stDailyAchievementInfo;
    LevelOfTheDayConfigInfo         m_stLevelOfTheDayConfigInfo;
    NationalDayRewardConfigInfo     m_stNationalDayRewardConfigInfo;
    RebateRewardConfig              m_stRebateRewardConfig;
    StarConvertConfig               m_stStarConvertConfig;
    LostNetActivityConfig               m_stLostNetActivityConfig;
    PlantAdventureConfig            m_stPlantAdventureConfig;
    int                             m_PlantAdventureTabIndex;
    WorldCupConfig               	m_stWorldCupConfig;
    JoustPlantPowerConfig			m_stJoustPlantPowerConfig;
    
    bool                            m_bIsAutosmoking;
    bool							m_bIsLoginSuccess;
#ifdef HOST_ANDROID

    class QiHooPlatform*			m_qihoo;
    bool							m_hasQihooLogin;

    //class WechatPlatform*			m_wechat;
#endif

    PackageContentsProvider*		m_packageContentsProvider;
    
    time_t							m_startLoadingTime;
    double							m_decompressTime;
    double							m_loadingTime;
    time_t							m_loadingBeginTime;
    std::string						m_sessionId;

   //std::vector<LogCacheInfo> 		m_logCacheInfo;
    int								m_currentBuyTimes;
    time_t							m_lastLogin;
    pvztime_t                       m_lastTouchEndTimne;

    class DailyRewardConfig*		m_dailyRewardConfig;

    PaymentResultInfo				m_paymentResultInfo;
    
    bool                            m_initDone;
    bool                            m_sGemOffer;
    
    int                             m_silenceReloginTimes;

    //for oppo
#ifdef HOST_ANDROID
    OfferBundleConfig				m_offerBundleConfig;

    int								m_androidSDKInitEnd;
    int 							m_androidSDKInitStatus;
#endif
    std::string						m_profileCreatedTime;
    bool							m_isNewUser;
    std::vector<std::string>		m_adBlackList;
    std::vector<std::string>		m_watchADBlackList;
};


extern LawnApp *gLawnApp;
extern GameStateMgr *gGameStateMgr;
extern PackageContentsProvider *gPackageProvider;
#ifdef HOST_IPHONEOS
extern bool IsDeviceIPad();
inline bool IsDeviceIOS() { return true; }
#else
inline bool IsDeviceIPad() { return false; } 
inline bool IsDeviceIOS() { return false; }
#endif
namespace Message
{
    void UpdateFakeCurrency();
    void ClearFakeCurrency();
	void StartPersistorLoad();
	void AppEnteredBackground();
    void AppLostFocus();
    void AppResumeFocus();
    void WechatShareSuccess();
    void WeChatShareFailed();
    void ConsumptionRewardStat(bool i_success);
    void GetConsumptionReward(bool i_success);
    void OrientationChanged();
}
#endif //__LAWNAPP_H__
