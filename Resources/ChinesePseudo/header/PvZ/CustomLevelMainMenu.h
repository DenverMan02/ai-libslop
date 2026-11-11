/*
 * CustomLevelMainMenu.h
 *
 *  Created on: 2021-12-4
 *      Author: zhousen
 */

#ifndef CUSTOMLEVELMAINMENU_H_
#define CUSTOMLEVELMAINMENU_H_

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "UIUtil.h"
#include "EditListener.h"
#include "CustomLevelMgr.h"
#include "UIListener.h"

namespace Message
{
	void CustomLevelMainMenuRefresh(int tabIndex);// refresh current tab widgets
	void CustomLevelShowRefreshButton(bool show);// check show refresh btn on current ui
	void CustomLevelPlayCoinChanged(int value);// update play coin
	void CustomLevelCreateCoinChanged(int value);// update create coin
	void CustomLevelCreateLevelRefresh(bool i_firstTutorial);// refresh create level ui widgets
	void CloseMainMenuDialog();// close mainmenu dialog, post when starting challenge
	void SelectTab(int index);// select tab
	void SwitchToMainMenu(bool mainMenu);// switch to main menu
	void ModifyLevelName(const std::string& name);
};

/////////////////////////////////////////
/// Custome Level Choose Level Tab Enum
/////////////////////////////////////////
enum {
	CustomChooseLevel_Invalid = -1,
	CustomChooseLevel_GuessLike = 1,
	CustomChooseLevel_MostPlay = 2,// UITabControll id start with 1.
	CustomChooseLevel_MoseLike = 3,
	CustomChooseLevel_Newest,// not use
	CustomChooseLevel_Filter,// not use
	CustomChooseLevel_MyFavor = 6,
	CustomChooseLevel_Search = 7,
	CustomChooseLevel_Max,
};

///////////////////////////////////////////
/// Custom Level Buttons Enum
/// (Include all ui dialog)
///////////////////////////////////////////
enum {
	CustomLevel_Btn_Close = 1000,
	CustomLevel_Btn_Refresh = 1001,// refresh btn
	CustomLevel_Btn_Search = 1002,// search btn
	CustomLevel_Btn_Setting = 1017,
	CustomLevel_Btn_Setting_Confirm = 1018,
	CustomLevel_Btn_Setting_GuessLike = 1019,

	CustomLevel_Btn_Detail_Favor = 1003,
	CustomLevel_Btn_Detail_UndoFavor = 1004,
	CustomLevel_Btn_Detail_Download = 1005,
	CustomLevel_Btn_Detail_HasDownloaded = 1006,
	CustomLevel_Btn_Detail_Challenge = 1007,
	CustomLevel_Btn_Detail_Delete = 1008,
	CustomLevel_Btn_Detial_Modify = 1009,
	CustomLevel_Btn_Detail_CopyChange = 1010,// can copy or can't copy
	CustomLevel_Btn_Detail_Upload = 1011,
	CustomLevel_Btn_Detail_Like = 1012,
	CustomLevel_Btn_Detail_Dislike = 1013,
	CustomLevel_Btn_Detail_ModifyName = 1014,
	CustomLevel_Btn_Detail_CopyLevelID = 1015,
	CustomLevel_Btn_Detail_SearchAuthor = 1016,

	CustomLevel_Btn_Detail_Share = 1999,
	CustomLevel_Btn_Share_Share = 3000,
	CustomLevel_Btn_Share_Save = 3001,
	CustomLevel_Btn_Share_Close = 3002,

	CustomLevel_Btn_Filter_Confirm = 1008,
	CustomLevel_Btn_Filter_WorldSelectAll = 1009,
	CustomLevel_Btn_Filter_PlayStyleSelectAll = 1010,

	CustomLevel_Btn_MostPlay_RankSort = 1100,
	CustomLevel_Btn_MostPlay_Filter = 1200,
	CustomLevel_Btn_MostLike_RankSort = 1300,
	CustomLevel_Btn_MostLike_Filter = 1400,
	CustomLevel_Btn_GuessLike_RankSort = 1500,
	CustomLevel_Btn_GuessLike_Filter = 1600,
	CustomLevel_Btn_Search_RankSort = 1700,
	CustomLevel_Btn_Search_Filter = 1800,
	CustomLevel_Btn_Motivate_Go = 1900,

	CustomLevel_Btn_Start = 2000,// tab index start,
	CustomLevel_Btn_ChooseLevel,
	CustomLevel_Btn_CreateLevel,
	CustomLevel_Btn_Shop,
	CustomLevel_Btn_Motivate,

	CustomLevel_Filter_Item_WorldBtnStart = 3000,
	CustomLevel_Filter_Item_PlayStyleBtnStart = 3100,

	CustomLevel_CreateLevel_StyleSelectStart = 3200,
	CustomLevel_CreateLevel_NormalModeSelectStart = 3300,// not use
};

////////////////////////////////////////
/// Custom Level Main Menu Tab Enum
////////////////////////////////////////
enum {
	CustomLevelTab_Invalid = -1,
	CustomLevelTab_ChooseLevel,
	CustomLevelTab_CreateLevel,
	CustomLevelTab_Shop,
	CustomLevelTab_Motivate,
	CustomLevelTab_Waiting,
	CustomLevelTab_Max,
};

//======================== NetworkData========================

///////////////////////////////////////
/// Custom Level Leaderboard Data
///////////////////////////////////////
struct CustomLevelLeaderBoardBaseData
{
	int a;
};

class CustomLevelLeaderBoardNetworkData : public INetworkData
{
public:
	RT_CLASS_DEFINE(CustomLevelLeaderBoardNetworkData, INetworkData, RtClass);
	std::vector<CustomLevelLeaderBoardBaseData> DataList;
	CustomLevelLeaderBoardBaseData PlayerData;
};

//======================= Widgets and Tabs =======================

//////////////////////////////////
/// Custom Level Main Menu Tab
/// (Left tabs)
//////////////////////////////////
class CustomLevelTab : public PVZ2UIButton, public ButtonListener
{
public:
    typedef Delegate0 TabCallback;

    CustomLevelTab(int tabIndex);
    virtual ~CustomLevelTab();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void InitView(int tabIndex);
    void SetCallback(TabCallback callback){ _callback = callback; }

protected:
    void SelectTab(int index);

protected:
    int _tabIndex;// tab index
    TabCallback _callback;// click callback
    Image* _selectImage;// select image
    Image* _unselectImage;// unselect image
};

///////////////////////////////////////////////
/// Preview Choose Level UI
///////////////////////////////////////////////
class CustomLevelItemWidget : public Sexy::Widget
{
public:
	typedef Delegate2<const CustomNetworkPreviewData&, const int&> TouchLevelDelegate;

	CustomLevelItemWidget(int index);
	virtual ~CustomLevelItemWidget();

    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void Draw(Sexy::Graphics* i_g) override;

    virtual void InitView(bool i_share = false);
    virtual void LoadData(const CustomNetworkPreviewData& i_data);
    CustomNetworkPreviewData GetData() const { return _data; }
    void RegisterTouchCallBackFunc(TouchLevelDelegate i_delegate) { _touchEnd = i_delegate; }
    void ShowFavour(bool show) { _showFavorImage = show; }

protected:
    void InitHead(int headID);
    Image* GetCurrentMainImage(int world, int levelmode);
    SexyString CalcStatisticValueString(int value);

protected:
    int _touchID;
    int _index;// index in list.

    // main widgets
    Image* _bgImage;
    Rect _bgRect;
    Image* _mainImage;
    Rect _mainRect;
    Image* _recommendImage;
    Rect _recommendRect;
    Image* _favorImage;
    Rect _favorRect;
    Image* _likeImage;
    Rect _likeImageRect;
    Image* _dislikeImage;
    Rect _dislikeImageRect;

    Rect _blackBarRect;

    Image* _headImage;
    Image* _headFrameImage;
    Image* _headFrameImage2;
    Rect _headRect;
    class HeadshotIconWidget* _headshotIcon;

    SexyString _levelTitle;
    Rect _levelTitleRect;
    SexyString _likeText;
    Rect _likeTextRect;
    SexyString _dislikeText;
    Rect _dislikeTextRect;

    SexyString _playerNameText;
    Rect _playerNameTextRect;
    SexyString _modeText;
    Rect _modeRect;

    TouchLevelDelegate _touchEnd;// touch call back
    CustomNetworkPreviewData _data;// widget data

    bool _showFavorImage;// check show favourite icon
};

///////////////////////////////
// For Detail UI
///////////////////////////////
class CustomLevelDetailItemWidget : public CustomLevelItemWidget, public ButtonListener
{
public:
	CustomLevelDetailItemWidget(int index);
	virtual ~CustomLevelDetailItemWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void InitView(bool i_share = false) override;

    virtual void LoadData(const CustomNetworkUploadData& i_data);
    void SetDetailType(int type) { _type = type; }
    void SetDeleteFunc(Delegate0 func) { _deleteFunc = func; }
    void SetUpload(bool isUpload) { _isUpload = isUpload; }

protected:
    CustomNetworkUploadData _detailData;
    PVZ2UIButton* _deleteBtn;
    Delegate0 _deleteFunc;
    int _type;
    bool _isUpload;
};

///////////////////////////////
// For Create Level Preview UI
///////////////////////////////
class CustomLevelCreateLevelItemWidget : public CustomLevelItemWidget
{
public:
	CustomLevelCreateLevelItemWidget(int index);
	virtual ~CustomLevelCreateLevelItemWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void InitView(bool i_share = false) override;

    void SetUploadState(bool state) { _uploadState = state; }
    void SetLevelMode(int mode) { _levelMode = mode; }

protected:
    bool _uploadState;// check is upload
    int _levelMode;// level mode

    Image* _uploadIcon;
    Rect _uploadRect;
    SexyString _modeText;
    Rect _modeTextRect;
};

////////////////////////////////////
// For Create Level UI Add Button
////////////////////////////////////
class CustomLevelCreateLevelAddItemWidget : public Sexy::Widget
{
public:
	CustomLevelCreateLevelAddItemWidget();
	virtual ~CustomLevelCreateLevelAddItemWidget();

    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;
    virtual void Draw(Sexy::Graphics* i_g) override;

    virtual void InitView();
    void RegisterTouchCallBackFunc(Delegate0 func) { _func = func; }

protected:
    int _touchID;
    Image* _addIcon;
    Rect _mainRect;
    Delegate0 _func;
};

///////////////////////////////
// For Leaderboard Item Widget
///////////////////////////////
class CustomLevelLeaderBoardItemWidget : public Sexy::Widget
{
public:
	CustomLevelLeaderBoardItemWidget();
	virtual ~CustomLevelLeaderBoardItemWidget();

	virtual void Draw(Sexy::Graphics* i_g) override;

	void LoadData(const CustomLevelLeaderBoardBaseData& data);
	void InitView();

protected:
	// main widgets
	Image* _crownImage;
	Rect _crownRect;
	Image* _headImage;
	Rect _headRect;
	SexyString _worldRecordName;
	Rect _worldRecordRect;
	SexyString _passTime;
	Rect _passTimeRect;
	CustomLevelLeaderBoardBaseData _data;// widget data
};


////////////////////////////
/// Filter Item Widget
////////////////////////////
class CustomLevelFilterItemWidget : public PVZ2UIButton, public ButtonListener
{
public:
	CustomLevelFilterItemWidget(int buttonID);
	virtual ~CustomLevelFilterItemWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void InitView();

    void SetBgImage(Image* img) { _bgImage = img; }
    void SetDesc(SexyString str) { _descStr = str; }
    void SetFilterID(int id) { _filterID = id; }
    int GetFilterID() const { return _filterID; }
    bool IsSelected() const { return _selected; }
    void SetSelected(bool selected) { _selected = selected; }
    void SetClickFunc(Delegate1<int> func) { _func = func; }

protected:
    int _filterID;// filter id
    Image* _bgImage;// background image
    Image* _frameImage;// frame image
    bool _selected;// if is selected.
    SexyString _descStr;// main desc
    Rect _descRect;// desc rect
    Delegate1<int> _func;// click func
};

/////////////////////////
/// Motivate UI.
/////////////////////////
class UICustomLevelMotivate : public UISingletonDialog<UICustomLevelMotivate>
{
public:
	UICustomLevelMotivate();
	virtual ~UICustomLevelMotivate();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UICustomLevelMotivate"; }
	virtual void ButtonDepress(int i_id) override;
};

/////////////////////////
/// Select All Button
/////////////////////////
class CustomLevelFilterSelectAllButton : public PVZ2UIButton, public ButtonListener
{
public:
	CustomLevelFilterSelectAllButton(int buttonID);

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void SetDescStr(SexyString str) { _descStr = str; }
    bool IsSelected() const { return _selected; }
    void SetSelected(bool selected) { _selected = selected; }
    void SetClickCallback(Delegate1<int> func) { _func = func; }

protected:
    bool _selected;// if is selected.
    SexyString _descStr;// desc str
    Delegate1<int> _func;// click func
};

/////////////////////////////////////
/// Create Level Choose Mode Widget
/////////////////////////////////////
class CustomLevelCreateLevelChooseItemWidget : public CustomLevelFilterItemWidget
{
public:
	CustomLevelCreateLevelChooseItemWidget(int id);
	virtual ~CustomLevelCreateLevelChooseItemWidget();

	virtual void InitView() override;
};

//=============================   Views   =====================================

//////////////////////////////
/// Custom Level View
/////////////////////////////
class CustomLevelView : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	CustomLevelView();
	virtual ~CustomLevelView();

	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;

    void InitView();
    void CheckUploadedLevels();

protected:
    void SwitchToMainMenu(bool showMainMenu);
    void CustomLevelNetworkResponseReceived(int i_context, int i_status);
    bool TryDownloadUploadedLevels();
    void onMsgError(int erroId, const std::string& requestID);

protected:
	class UICustomLevelMainMenu* _mainView;
	PVZ2UIButton* _chooseLevelBtn;
	PVZ2UIButton* _createLevelBtn;
	PVZ2UIButton* _shopBtn;
	PVZ2UIButton* _backBtn;
	Image* _bgImage;
	float _loadBarProgress;
	bool _finishLoading;
	bool _hasFinishedDownload;
};

/////////////////////////////////
/// Custom Level Main Menu
/////////////////////////////////
class UICustomLevelMainMenu : public UISingletonDialog<UICustomLevelMainMenu>, public Sexy::ScrollWidgetListener
{
public:
	UICustomLevelMainMenu();
	virtual ~UICustomLevelMainMenu();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UICustomLevelMainMenu"; }
	virtual void ButtonDepress(int i_id) override;
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
	virtual void Update() override;

	void InitView(int tabIndex = CustomLevelTab_ChooseLevel);
	void StartViewMode(int mode = CustomLevelTab_ChooseLevel) { _startViewMode = mode; }
	int GetCurrentTab() { return _currentTab; }
	void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

protected:
	void InitTab();
	void InitOtherUI();
	void AttachUI(int tabIndex);
	void DeattachUI(int tabIndex);

	void onPlayCoinChange(int value);
	void onCreateCoinChange(int value);
	void onClickChooseLevel();
	void onClickCreateLevel();
	void onClickShop();
	void onClickMotivate();
	void onCLickWaiting();
	void DoClickTab(int tabIndex);

	void ShowLeaderboard();
	void SetTitleType(int tabType);
	void ShowRefreshButton(bool show);
	void CloseMainMenuDialog();
	void CustomLevelNetworkResponseReceived(int i_context, int i_status);
	void RequestFavouriteList();

private:
	std::map<int, CustomLevelTab*> _tabsMap;// tabs map
	std::map<int, Widget*> _attachUIMap;// the ui controlled by tabs map

	Widget* _tabContainer;// tabs container
	Widget* _attachUIContainer;// ui container
	UIWidgetText* _playCoinText;
	UIWidgetText* _createCoinText;
	UIWidgetText* _titleText;// title text
	PVZ2UIButton* _refreshButton;

	int _startViewMode;// the start view mode
	int _currentTab;// the current tab is focus
	bool _initMainMenuFavoouriteList;// init favourite list first
	bool _initStartView;// init start view
};

//////////////////////
/// Choose Level UI
//////////////////////
class UICustomLevelChooseLevel : public UISingletonDialog<UICustomLevelChooseLevel>, public Sexy::ScrollWidgetListener, public UI::TabControlListener, public Sexy::EditListener
{
public:
	UICustomLevelChooseLevel();
	virtual ~UICustomLevelChooseLevel();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UICustomLevelChooseLevel"; }
	virtual void ButtonDepress(int i_id) override;
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
    virtual void TabSelectionChanged(int tabID) override;

	void InitView(int tab = CustomChooseLevel_GuessLike);
	void RequestFilter(std::vector<CustomLevelNetworkWorldType> worldList, std::vector<CustomLevelNetworkLevelMode> modeList);
	int GetCurrentTabID();
	void SetSelectTab(int i_tabID);

	void TriggerTutorial();
	void OnSetCustomLevelGuessLikeEnable(bool i_flag);

protected:
	void CreateTabItems(int type, Sexy::Widget* parent, CustomNetworkListData data);
	void CreateRankSortBtn(int type, Sexy::Widget* parent);
	void CreateRefreshBtn(int type, Sexy::Widget* parent);
	void CreateFilterBtn(int type, Sexy::Widget* parent);
	void CreateFavorUI(int type, Sexy::Widget* parent);
	void CreateSearchUI(int type, Sexy::Widget* parent);

	void onMostPlayFunc(const CustomNetworkPreviewData& data, int index);
	void onMostLikeFunc(const CustomNetworkPreviewData& data, int index);
	void onNewestFunc(const CustomNetworkPreviewData& data, int index);
	void onFavorFunc(const CustomNetworkPreviewData& data, int index);
	void onSearchFunc(const CustomNetworkPreviewData& data, int index);

	void OnRefresh(int tabIndex);
	void ShowRefreshCoolDownHint();
	void OnClickComboBox(int id);
	void CustomLevelNetworkResponseReceived(int i_context, int i_status);
	bool AllisNum(std::string str);

protected:
	bool _initTabUIFlag[CustomChooseLevel_Max];// every tab ui should be init once

	std::vector<CustomLevelNetworkWorldType> _mostPlayWorldTypeList;
	std::vector<CustomLevelNetworkLevelMode> _mostPlayModeTypeList;
	std::vector<CustomLevelNetworkWorldType> _mostLikeWorldTypeList;
	std::vector<CustomLevelNetworkLevelMode> _mostLikeModeTypeList;
	std::vector<CustomLevelNetworkWorldType> _guessLikeWorldTypeList;
	std::vector<CustomLevelNetworkLevelMode> _guessModeTypeList;
	std::vector<CustomLevelNetworkWorldType> _searchWorldTypeList;
	std::vector<CustomLevelNetworkLevelMode> _searchModeTypeList;
	ViewRankType _mostPlayRankType;
	ViewRankType _mostLikeRankType;
	ViewRankType _guessLikeRankType;
	ViewRankType _searchRankType;

	UITabControl* _tabControl;
	UIWidgetText* _hasFavorText;// has favor str
	Widget* _mostPlayContainer;
	Widget* _mostLikeContainer;
	Widget* _favourContainer;
	class EditWidget* _searchInput;
	PVZ2UIButton* _searchButton;
	Widget* _searchContainer;// it's parent is search tab widget.we need use it to recreate widget by search btn
	class CustomLevelItemWidget* m_tutorialWidget;

	pvztime_t _refreshStartTime;
};

//////////////////////////////////////
/// Custom Level Leaderboard
//////////////////////////////////////
class UICustomLevelLeaderBoard : public UISingletonDialog<UICustomLevelLeaderBoard>, public Sexy::ScrollWidgetListener
{
public:
	UICustomLevelLeaderBoard();
	virtual ~UICustomLevelLeaderBoard();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UICustomLevelLeaderBoard"; }
	virtual void ButtonDepress(int i_id) override;
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void InitView(const CustomLevelLeaderBoardNetworkData& data);
	void ShowTestDataUI();
};

//////////////////////////////////////
/// Custom Level Level Detail
//////////////////////////////////////
class UICustomLevelLevelDetail : public UISingletonDialog<UICustomLevelLevelDetail>
{
public:
	UICustomLevelLevelDetail();
	virtual ~UICustomLevelLevelDetail();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override {
		return "UICustomLevelLevelDetail";
	}
	virtual void ButtonDepress(int i_id) override;

	void LoadData(const CustomNetworkUploadData& data);
	void SetCopyStyleEnable(bool status) { _copyStyleEnable = status; }
	void InitView(int type);// CustomLevelTab_ChooseLevel or CreateLevel
	void SetUploadState(bool upload) { _isUploadState = upload; }
	void TriggerTutorial(int i_stage);
	void CreateShareDialog();

protected:
	void ShowDeleteHint();
	void ShowDownloadSuccessHint();
	void ShowCopyIDHint();
	void ShowUploadHint(bool hasFinishLevel);
	void ShowNameTooLongHint();
	void DeleteLevel(class UIMessageBox* box, int id);
	void CopyLevelID(class UIMessageBox* box, int id);
	void CustomLevelNetworkResponseReceived(int context, int status);
	void SetLevelID(int id);
	float CalcEvalutionParam(int likes, int total, float param);
	SexyString GetEvaluationString(float value);
	void CopyChange(int id);
	void ModifyLevelName(const std::string& name);

private:
	CustomNetworkUploadData _data;
	int _type;// choose level or create level.
	bool _copyStyleEnable;// copy style
	bool _isUploadState;// if is upload

	PVZ2UIButton* _favorBtn;
	PVZ2UIButton* _undoFavorBtn;
	PVZ2UIButton* _downloadBtn;
	PVZ2UIButton* _hasDownloadedBtn;
	PVZ2UIButton* _modifyBtn;
	PVZ2UIButton* _challengeBtn;
	CustomLevelFilterSelectAllButton* _copyChangeBtn;// change copy status.
	PVZ2UIButton* _uploadBtn;
	PVZ2UIButton* _modifyNameBtn;

	CustomLevelDetailItemWidget* _itemWidget;
	UIWidgetText* _likeText;
	UIWidgetText* _totalPlayText;
	UIWidgetText* _playTimeText;
	UIWidgetText* _levelNameText;

	float _evaluationParam;// the evaluation of current level.
	SexyString _evaluationText;
	Rect _evaluationRect;
};

////////////////////////////////////////
///// Custom Level Level Detail Share
////////////////////////////////////////
class UICustomLevelLevelDetailShare : public UISingletonDialog<UICustomLevelLevelDetailShare>
{
public:
	UICustomLevelLevelDetailShare();
	virtual ~UICustomLevelLevelDetailShare();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override {
		return "UICustomLevelLevelDetailShare";
	}
	virtual void ButtonDepress(int i_id) override;

	void LoadData(const CustomNetworkUploadData& data);
	void InitView(int type);// CustomLevelTab_ChooseLevel or CreateLevel
	void GetParams(int& i_x, int& i_y, int& i_width, int& i_height);

protected:
	float CalcEvalutionParam(int likes, int total, float param);
	SexyString GetEvaluationString(float value);

private:
	void DoShare();
	void DoSave();
    void OnNotifyShareSaveFinished();
    void OnNotifyShareSaveBegin();
    void OnNotifyShareRewardFinished();

	CustomNetworkUploadData _data;
	int _type;// choose level or create level.
	bool _copyStyleEnable;// copy style

	CustomLevelDetailItemWidget* _itemWidget;
	UIWidgetText* _likeText;
	UIWidgetText* _totalPlayText;
	UIWidgetText* _playTimeText;
	UIWidgetText* _levelNameText;

	float _evaluationParam;// the evaluation of current level.
	SexyString _evaluationText;
	Rect _evaluationRect;
};

//////////////////////////////////////
/// Custom Level Detail Modify Name
//////////////////////////////////////
class UICustomLevelDetailModifyName : public UISingletonDialog<UICustomLevelDetailModifyName>, public Sexy::EditListener
{
public:
	UICustomLevelDetailModifyName();
	virtual ~UICustomLevelDetailModifyName();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UICustomLevelDetailModifyName"; }
	virtual void ButtonDepress(int i_id) override;

	void SetCurrentName(SexyString str);
	void SetUploadState(bool isUpload) { _isUpload = isUpload; }

protected:
	void InitView();
	void CustomLevelNetworkResponseReceived(int i_context, int i_status);
	bool CheckNameFilter();

protected:
	bool _isUpload;
	class EditWidget* _inputName;
};

//////////////////////////////////////
/// Custom Level Create Level
//////////////////////////////////////
class UICustomLevelCreateLevel : public UISingletonDialog<UICustomLevelCreateLevel>, public Sexy::ScrollWidgetListener
{
public:
	UICustomLevelCreateLevel();
	virtual ~UICustomLevelCreateLevel();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UICustomLevelCreateLevel"; }
	virtual void ButtonDepress(int i_id) override;
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
	void TriggerTutorial();
	void SetTutorialStage(int i_stage) { m_tutorialStage = i_stage; }
    int GetCurrentLevelIndex() { return m_currentLevelIndex; }   

protected:
	void InitView();
	void onClick(const CustomNetworkPreviewData& data, int index);// normal level
	void onCreateLevelChoose();// add new level
	void OnRefresh(bool i_firstTutorial);
	void CustomLevelNetworkResponseReceived(int i_context, int i_status);

private:
	Widget* _itemParentWidget;// items container
	std::vector<CustomPreviewData> _localDataList;// all local levels.
	CustomLevelCreateLevelItemWidget* m_tutorialWidget;
	int m_tutorialStage;
    int m_currentLevelIndex;
};

//////////////////////////////////////
/// Custom Level Filter
//////////////////////////////////////
class UICustomLevelFilter : public UISingletonDialog<UICustomLevelFilter>, public Sexy::ScrollWidgetListener
{
public:
	UICustomLevelFilter();
	virtual ~UICustomLevelFilter();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UICustomLevelFilter"; }
	virtual void ButtonDepress(int i_id) override;
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	bool FilterLevels(CustomLevelItemWidget* widget);

protected:
	void InitView();
	std::vector<class CustomLevelFilterItemWidget*> CreateSelectItemWidgets(Widget* parent, std::vector<int> dataList, int startBtnID);
	class CustomLevelFilterSelectAllButton* CreateSelectAllBtn(Widget* parent, int buttonID);
	void SetSelectAllWidgets(std::vector<class CustomLevelFilterItemWidget*>& widgets, bool selected);
	void RequestFilter();
	void OnClickFilterItemWidget(int index);
	void ClickAllBtn(int id);

private:
	class CustomLevelFilterSelectAllButton* _worldSelectAllButton;
	class CustomLevelFilterSelectAllButton* _playStyleSelectAllButton;
	std::vector<class CustomLevelFilterItemWidget*> _worldSelectWidgets;
	std::vector<class CustomLevelFilterItemWidget*> _playStyleSelectWidgets;
};

///////////////////////////////////////////
/// Custom Level Create Level Choose Mode
///////////////////////////////////////////
class UICustomLevelCreateLevelChooseMode : public UISingletonDialog<UICustomLevelCreateLevelChooseMode>
{
public:
	UICustomLevelCreateLevelChooseMode();
	virtual ~UICustomLevelCreateLevelChooseMode();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UICustomLevelCreateLevelChooseMode"; }
	virtual void ButtonDepress(int i_id) override;

	void SetNewSlotIndex(int index) { _newSlotIndex = index; }

protected:
	void InitView();
	void OnClickItemWidget(int id);
	std::vector<CustomLevelCreateLevelChooseItemWidget*> CreateSelectItemWidgets(Widget* parent, std::vector<int> dataList, int startBtnID);

private:
	int _newSlotIndex;// create new data slot index
	int _styleSelectID;//level mode id
	PVZ2UIButton* _confirmBtn;// confirm btn
	std::vector<CustomLevelCreateLevelChooseItemWidget*> _styleSelectWidgets;// level mode widgets
};

//======================================================







#endif /* CUSTOMLEVELMAINMENU_H_ */
