//
//  MainMenu.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 3/19/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__MainMenu__
#define __PlantsVersusZombies2__MainMenu__

#include "ButtonListener.h"
#include "Widget.h"
#include "Dialog.h"
#include "EditListener.h"
#include "EditWidget.h"
#include "ButtonWidget.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "PlayerInfo.h"
#include "CameraPreviewWidget.h"
#include "CheckboxListener.h"


enum MainMenuButtons
{
	MAINMENUBUTTON_STARTGAME,
	///MAINMENUBUTTON_MERCH,
	//MAINMENUBUTTON_MOREGAMES,
	MAINMENUBUTTON_SETTINGS,
    MAINMENUBUTTON_PERIPHERY_STORE,
	MAINMENUBUTTON_CHANGENAME,
	MAINMENUBUTTON_PROFILESAVE,
	MAINMENUBUTTON_DELETEPROFILE,
	//MAINMENUBUTTON_TAKEPICTURE,
	MAINMENUBUTTON_BACK,
	//MAINMENUBUTTON_FACEBOOK_LOGIN,
	//MAINMENUBUTTON_FACEBOOK_LOGOUT,
	//MAINMENUBUTTON_FACEBOOK_CONNECTED,
	MAINMENUBUTTON_WECHAT_LOGIN,
	MAINMENUBUTTON_QQMOBILE_LOGIN,
	MAINMENUBUTTON_SOCIAL_LOGOUT,
	MAINMENUBUTTON_GAME_CENTER,
    MAINMENUBUTTON_RANDOM,
#ifdef HOST_ANDROID
    MAINMENUBUTTON_QIHOO,
    MAINMENUBUTTON_REDEEM,
#endif
    MAINMENUBUTTON_COMPLAIN,

	MAINMENUBUTTON_PLATFORM_LOGIN,
    MAINMENUBUTTON_IFENGFENG_LINK,
//	MAINMENUBUTTON_COMPLAIN,
//  MAINMENUBUTTON_RANDOM,
    MAINMENUBUTTON_AGE_TIP,
    MAINMENUBUTTON_BIND_UNIQUE_ID,
};

//PVZ2_CHINESE begin
#if 0
class FacebookProfileWidget : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::CheckboxListener
{
public:
	FacebookProfileWidget(const Sexy::Rect& i_rect, Sexy::ButtonListener* i_parentListener, PlayerInfoPtr i_playerInfo);
	virtual ~FacebookProfileWidget();

	virtual void Update();
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
	virtual void CheckboxChecked(int i_id, bool i_checked);

	void SetPlayerInfo(PlayerInfoPtr i_playerInfo) { m_playerInfo = i_playerInfo; }

private:

	void createOfflineButtons();
	void createLoggedInButtons();

	bool m_loggedIn;
	int m_logOutLength;
	PlayerInfoPtr m_playerInfo;
};
#endif
//PVZ2_CHINESE end

class EditProfileWidget : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::EditListener
{
public:
	EditProfileWidget(PlayerInfoPtr i_playerInfo);
	virtual ~EditProfileWidget();

	virtual void SetIgnoreMouseInput(bool i_ignore);
	virtual void Update();
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void EditWidgetText(int i_id, const SexyString& i_string);
	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
	virtual bool AllowChar(int i_id, SexyChar i_char);

private:
    
    void SplitString(std::wstring target, std::vector<std::wstring> &tokens, wchar_t delims);

	void onErrorAccepted();
	void onDeleteAccepted();
	void onDeleteCanceled();
	void onProfileIconPictureTaken(const PlayerInfo* i_playerInfo, MemoryImage* i_image);
	void createPictureButton(Image* i_iconImage);
	void addFilterNameList();
    
    std::vector<std::wstring> firstNameList;
    std::vector<std::wstring> secondNameList;
    std::vector<std::wstring> filterNameList;

	class PVZ2UIEditWidget* m_editWidget;
//	class FacebookProfileWidget* m_facebookWidget;
	class PVZ2UIButton* m_saveButton;
	//class PVZ2UIButton* m_pictureButton;  //PVZ2_CHINESE removed
	PlayerInfoPtr m_playerInfo;

	enum EditProfileState
	{
		PROFILE_FIRST,
		PROFILE_EDIT,
		PROFILE_NEW
	} m_profileState;
};

//PVZ2_CHINESE begin
#if 0
class PictureTakingWidget : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	PictureTakingWidget(PlayerInfoPtr i_playerInfo);
	virtual ~PictureTakingWidget();
	
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
	virtual void SetIgnoreMouseInput(bool i_ignore);

private:

	void onPictureTaken(Sexy::MemoryImage* i_image);
	CameraPreviewWidget* m_cameraPreview;
	PlayerInfoPtr m_playerInfo;
	bool m_takingPicture;
};
#endif
//PVZ2_CHINESE end

class ProfilesListEntry : public PVZ2UIButton, public Sexy::ButtonListener
{
public:
	ProfilesListEntry(const Rect& i_rect, const int i_id, ButtonListener* i_buttonListner, PlayerInfoPtr i_playerInfo);
	virtual ~ProfilesListEntry();

	virtual void Draw(Sexy::Graphics* i_g);
	virtual void ButtonDepress(int i_id);

	bool IsPlaceholder() const { return !m_playerInfo.IsValid(); }
	SexyString GetPlayerName() const { return m_playerInfo.IsValid() ? m_playerInfo->GetName() : _S(""); }
	PlayerInfoPtr GetPlayerInfo() const { return m_playerInfo; }
	void SetPlayerInfo(PlayerInfoPtr i_playerInfo);

private:

	PlayerInfoPtr m_playerInfo;
};

class ProfilesListContainer : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	ProfilesListContainer(class ProfilesDialog* i_profilesDialog);
	virtual ~ProfilesListContainer();

	void Initialize(int i_x, int i_y, int i_width, int i_height);
	virtual void DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g);
	virtual void AddWidget(Widget* i_widget);
	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);

private:

	void createPlaceholderEntry();
	void onProfileCreated(const PlayerInfoPtr& i_playerInfo);
	void onProfileAboutToBeDeleted(const PlayerInfoPtr& i_playerInfo);

	std::vector<ProfilesListEntry*> m_profiles;
	class ProfilesDialog* m_profilesDialog;
};

class ProfilesDialog : public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener
{
public:
	ProfilesDialog();
	virtual ~ProfilesDialog();

	virtual void Draw(Sexy::Graphics* i_g);
	virtual void ButtonDepress(int i_id);
	virtual void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) {}
	virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) {}

private:

	ProfilesListContainer* m_profilesContainer;
};

class MainMenu : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	MainMenu();
	virtual ~MainMenu();

	void Initialize();

	void continuePressStartGame();

	virtual void Update();
	virtual void Draw(Sexy::Graphics* i_g);
	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
	virtual void TouchEnded(const Sexy::Touch& i_touch);

	void CreateWelcomeDialog(PlayerInfoPtr i_playerInfo);
	//void CreateCameraDialog(PlayerInfoPtr i_playerInfo); //PVZ2_CHINESE removed
	void ScrollLeft();
    class AccountBindDialog* GetAccountBindDialog(){return m_accountBindDialog;}
    void UpdateProfieName();
    void LoginiCloudServerFinishProc(bool i_success);
    
    // for decompress
    void SetLoginCloudServersFinishSuccess(bool i_success) { m_loginCloudServersFinishSuccess = i_success; }
    bool GetLoginCloudServersFinishSuccess() { return m_loginCloudServersFinishSuccess; }
	void LoadRsbsExtraProc();

#ifdef HOST_ANDROID
	// bind unique id
	void CreateBindUniqueIDButton();
	void ShowBindUniqueID();
	void ShowBindUniqueIDHint();
	void RequesBindUniqueID();
	void SetBindBtnEnable(bool show);
#endif

private:
	void onFinishCheckAccount(bool i_success);
    void doUpgradeProfileLogic();
    void uploadLocalProfile();
    void onUploadFirstTimeFinish(bool i_success);
    
    void createWelcomeDialogIfNeeded();
	void createMainButtons();
	class PVZ2UIButton* createBottomButton(const int i_xPos, const MainMenuButtons i_button, Image* i_buttonIcon, const bool i_fromLeft);
	class PVZ2UIButton* createAgeTipsButton(const int i_xPos, const MainMenuButtons i_button, Image* i_buttonIcon, const bool i_fromLeft);
	void CreateComplainButton();
    
    class PVZ2UIButton* createBindButton(const int i_xPos, const int i_yPos, const MainMenuButtons i_button, Image* i_buttonIcon);
	void startGame();
	void syncProfileSummaryWithServer();
	void showDiffProfileSummary();
	void closeDiffProfileSummary();
	void createProfilesDialog();
	void createSettingsDialog();
    void CreateComplainDialog();
    void CreateAgeTipDialog();
    void createAccountBindDialog();
    void createPrivacyDialog();
    void checkOfflineNotice();

    void reloadData();
    void onProfileListChanged();
	void onGameCenterAuthenticationChanged(bool i_connected);
	void onLoginiCloudServerFinish(bool i_success);
	void onSyncProfileSummaryFinish(bool i_success);

    void onSyncPlayerInfoFinish(bool i_success);
	void onSyncProfileListFinish(bool i_success);
	void onSyncProfileToServer(bool i_success);
	void onSyncProfileFromServer(bool i_success);
	void onProfileSummarySelectResult(int i_result);
	void onNetworkError(int erroId);
	void onCloseNetworkErrorDialog();
	void onUseLocalStorage();
#ifdef HOST_ANDROID
	void onLoginComplete();
	void tryStartGame();
	void onNetworkProfileSyncFinish(bool i_success);
	void onPlayerInfoSyncFinish();
	void CreateRedeemButton();
	bool NeedCreateRedeemButton();
	void TryRedeem();
	void onCheckRedeemFinished(bool i_success);
#endif

    void gotoSystemSetting();
    void retryConnect();
    void SplitString(std::wstring target, std::vector<std::wstring> &tokens, wchar_t delims);
    
    void ChooseProfile(bool i_cloudOlder);


    // for decompress
    bool NeedDecompressRsbsExtra();
    float GetFirstDecompressTotalAmount();
    float GetSecondDecompressTotalAmount();
    unsigned int GetTargetRSBDecompressSize(const std::string& i_rsbName);
    void InitForDecompressRsbs();
    void InitDecompressImage();
    void DrawDecompressTips(Sexy::Graphics *g);
    int GetLeftDecompressTime();
    int GetPreviousDecompressTime();
    int GetTotalDecompressTime();

	bool m_needDecompressRsbs;
	std::vector<float> m_decompressPercents;
	int m_currentDecompressIndex;
	Rect m_meterRect;
	Rect m_fillRect;
	SexyString m_progressPercentTxt;
	Rect m_tips1Rect;
	Rect m_tipsPercentRect;
	Rect m_tips2Rect;

	Sexy::Image* m_backgrounImg;
	Sexy::Image* m_backgrounImgT;
	Sexy::Image* m_meterImg;
	Sexy::Image* m_fillImg;
	Sexy::Image* m_loaderImg;
	Sexy::Image* m_loadfillImg;
	int m_totalRsbCount;
	int m_currentLeftDuration;

	float m_loadBarProgress;
	float m_decompressBarProgress;
	//====================================

    void playBackgroundEffect();
    void updateBackgroundEffect();
    void drawBackgroundEffect(Graphics* i_g);

	class SettingsDialog* m_settingsDialog;
	class PVZ2UIScrollingPaneWidget* m_scrollingPaneWidget;
	class ComplainDialog* m_pComplainDialog;
	class AgeTipDialog* m_ageTipDialog;
    class AccountBindDialog* m_accountBindDialog;

	class PVZ2UIButton* m_startGameButton;
	class PVZ2UIButton* m_changeNameButton;
	class PVZ2UIButton* m_gameCenterButton;
    class PVZ2UIButton* m_iFengFengButton;
    class PVZ2UIButton* m_peripheryStoreButton;
#ifdef HOST_ANDROID
    class PVZ2UIButton* m_bindUniqueIDButton;
    class PVZ2UIButton* m_qihooLoginButton;
    class PVZ2UIButton* m_redeemButton;
    pvztime_t m_waitingCD;
#endif
	class ProfileSummaryComparer* m_profileSummaryComparer;
    bool m_startedGame;
    bool m_loginingiCloud;
    bool m_hasWarningDialog;
    bool m_canCreateProfile;
    
    bool m_areAllProfileValid;
    bool m_mainMenuClicked;
    bool m_startGameAfterSyncProfile;
#ifdef HOST_ANDROID
    //for oppo
    bool m_isNewUser;
#endif
    bool m_newUserLogin;

    bool m_loginCloudServersFinishSuccess;

    class PopAnimRig* m_backgroundEffect;
};

namespace Message
{
	void StartButtonPressed();
	void MainMenuLoaded();
	void ProfileSelected();
    void GameStart();
    void StartGameOffLine();
    void CheckRedeemFinished(bool i_success);
    void CheckGameCenterFinished(bool i_success);
    void GetGameCenterUrlFinished(const std::string& i_url);
    
    //For AntiHack
    void Faiicck();
}

#endif /* defined(__PlantsVersusZombies2__MainMenu__) */
