/*
 * PennyClassroom.h
 *
 *  Created on: 2022-2-9
 *      Author: zhousen
 */

#ifndef PENNYCLASSROOM_H_
#define PENNYCLASSROOM_H_

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "UIUtil.h"
#include "UIPlayerSurvey.h"
#include "PVZ1ModeShop.h"

namespace Message
{
	void NotifyCloseDialog();
	void NotifyUpdateTrainingWidget();
}

enum {
	PENNY_CLASSROOM_BTN_CLOSE = 1000,
	PENNY_CLASSROOM_BTN_TIPS,
	PENNY_CLASSROOM_BTN_SHOP,
	PENNY_CLASSROOM_BTN_GOTO_LEVEL_START = 2000,
	PENNY_CLASSROOM_BTN_START_LEVEL = 3000,

	PENNY_CLASSROOM_SURVEY_NEXT_BTN = 1001,
	PENNY_CLASSROOM_SURVEY_REDO_BTN = 1002,
};

// for main ui and shop tab ui.
enum {
	PENNY_CLASSROOM_TEST_LEVEL = 0,
	PENNY_CLASSROOM_EASY_LEVEL,
	PENNY_CLASSROOM_NORMAL_LEVEL,
	PENNY_CLASSROOM_HARD_LEVEL,
	PENNY_CLASSROOM_LEVEL_MAX,
};

// for start level. plant ability.
enum {
	PENNY_CLASSROOM_PLANT_ABILITY_SUN = 0,
	PENNY_CLASSROOM_PLANT_ABILITY_ATTACK,
	PENNY_CLASSROOM_PLANT_ABILITY_GUARD,
};

/////////////////////////////////
/// NetworkPennyClassroom
/////////////////////////////////
enum {
	ICON_STATUS_LOCK = 0,
	ICON_STATUS_OPEN,
	ICON_STATUS_COMPLETE,
};

struct PennyClassroomIconData
{
	int Status;// 0 - lock, 1 - open, 2 - complete
};

struct PennyClassroomShopData
{
	int Id;
	int Quantity;
	int Cost;
	int Max;
	int Cur;// how many items can we got, eg: cur / max
};

struct PennyClassroomPlantData
{
	int Id;// plant id
	int Ability;// ability type
	int Star;// start count
};

class NetworkPennyClassroomData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkPennyClassroomData, INetworkData, RtClass);

public:
	int Day;// not use
	int CoinLeft;// coins left
	std::vector<PennyClassroomPlantData> PlantList;// plant list
	std::vector<int> HeadshotList;// headshot id list
	std::vector<std::vector<PennyClassroomIconData> > StatusList;// level status list
	std::vector<std::vector<std::vector<S2C_BonusInfo> > > BonusList;// level bonus list
	std::vector<PennyClassroomShopData>  ShopList;// shop item list
	std::vector<std::vector<int> > CorrectAnswerList;// correct answer list
	std::vector<std::vector<std::vector<int> > > PlantLevelList;// level plant corporation list
};

class NetworkPennyClassroomBonusData : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkPennyClassroomBonusData, INetworkData, RtClass);

	std::vector<S2C_BonusInfo> BonusList;
};

///////////////////////////////////////
/// PennyClassroomBonusWidget
///////////////////////////////////////
class PennyClassroomBonusWidget : public UIRewardFrame, public ButtonListener
{
public:
	PennyClassroomBonusWidget(RewardType type, const std::string& reward, int rewardQuantity, bool hasFrame = true);
	virtual ~PennyClassroomBonusWidget();

    virtual void ButtonDepress(int i_id) override;
	virtual void Draw(Sexy::Graphics* i_g) override;

	void InitView();
	void SetStatus(int status) { _status = status; }
	void SetID(int id) { _id = id; }
	void SetType(int type) { _type = type; }
	void SetIndex(int index) { _index = index; }

	static PennyClassroomBonusWidget* CreateUIRewardFrame(int objectId, int num, bool hasFrame);

protected:
	int _status;// for lock , done, open
	SexyString _hasGotStr;
	int _id;// btn id
	int _type;// training type
	int _index;// level index in the training level
};

//////////////////////////////////////////////
/// PennyClassRoomTrainingItemWidgetComponent
//////////////////////////////////////////////
class PennyClassRoomTrainingItemWidgetComponent : public Sexy::Widget, public ButtonListener
{
public:
	PennyClassRoomTrainingItemWidgetComponent();
	virtual ~PennyClassRoomTrainingItemWidgetComponent();

	virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView(int index, NetworkPennyClassroomData data);

protected:
    void InitBonus(int index);
    void InitButton();
    void GotoLevel();// show level ui
    int CalcCurrentLevel(int type);// calc which level is it now
    SexyString GetTrainingTitle(int type);

protected:
    int _type;
    int _buttonID;
    int _currentLevel;
    SexyString _levelTitleStr;
    SexyString _bonusStr;
    bool _isTomorrowPlay;
	NetworkPennyClassroomData _data;
};

///////////////////////////////////////
/// PennyClassRoomTrainingItemWidget
///////////////////////////////////////
class PennyClassRoomTrainingItemWidget : public Sexy::Widget
{
public:
	PennyClassRoomTrainingItemWidget();
	virtual ~PennyClassRoomTrainingItemWidget();

	virtual void Draw(Sexy::Graphics* i_g) override;

	void InitView(int index, NetworkPennyClassroomData data);

protected:
	void SetProgress(int progress);
	SexyString GetTrainingTitle(int type);
	SexyString GetLockDesc(int type);
	int CalcFinishCount(int type);// calc lock progress
	Image* GetMainBg(int type);

protected:
	int _type;// test / easy / normal / hard
	int _progress;
	bool _isLocked;
	SexyString _trainingTitleStr;
	SexyString _lockStr;
	SexyString _lockProgressStr;
	Image* _mainBg;
	std::vector<PennyClassroomBonusWidget*> _bonusWidgetList;
	NetworkPennyClassroomData _data;
};

/////////////////////////////////////
/// PennyClassroomPlantAbilityWidget
////////////////////////////////////
class PennyClassroomPlantAbilityWidget : public Sexy::Widget
{
public:
	PennyClassroomPlantAbilityWidget(int ability, int star);
	virtual ~PennyClassroomPlantAbilityWidget();

	virtual void Draw(Sexy::Graphics* i_g) override;

	void InitView();

protected:
	Image* _mainImage;// ability image
	Rect _abilityRect;
	int _abilityType;
	int _starCount;// star count
};

/////////////////////////////////
/// UIPennyClassroomStartLevel
/////////////////////////////////
class UIPennyClassroomStartLevel : public UISingletonDialog<UIPennyClassroomStartLevel>
{
public:
	UIPennyClassroomStartLevel();
	~UIPennyClassroomStartLevel();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UIPennyClassroomStartLevel"; }
	virtual void ButtonDepress(int i_id) override;

	void InitView(int index, int currentLevel, NetworkPennyClassroomData data);

private:
    void StartLevel();
	void InitHeadshotPopanim(std::string plantName);
    std::string GetGotoLevelName(int type, int currentlevel);
    SexyString GetTitle(int type, std::string plantName);
    SexyString GetPlantDesc(std::string plantName);
    SexyString GetLevelDesc(int type, std::string plantName);

private:
	int _index;// training type
	int _currentLevel;// training level
	NetworkPennyClassroomData _data;
	Widget* _headshotContainer;
};

////////////////////////////////////////////
/// PennyClassroomPlayerSurveySelectBox
////////////////////////////////////////////
class PennyClassroomPlayerSurveySelectBox : public PlayerSurveySelectBox
{
public:
	PennyClassroomPlayerSurveySelectBox();
	virtual ~PennyClassroomPlayerSurveySelectBox();

	virtual void    Draw(Sexy::Graphics* i_g) override;
	virtual void	ButtonDepress(int i_id) override;

	void SetIsCorrectAnswer(bool correctAnswer) { _isCorrectAnswer = correctAnswer; }

protected:
	bool _isCorrectAnswer;
};

//////////////////////////////
/// UIPennyClassroomSurvey
//////////////////////////////
class UIPennyClassroomSurvey : public UISingletonDialog<UIPennyClassroomSurvey>
{
public:
	UIPennyClassroomSurvey();
	~UIPennyClassroomSurvey();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UIPennyClassroomSurvey"; }
	virtual void ButtonDepress(int i_id) override;

	void InitView(int index, NetworkPennyClassroomData data);
	bool IsInWrongState(){ return _inWrongState; }

private:
	void InitBonus();
	void CreateQuestion(int index);
	void RequestResult(int index);
	int GetCorrectAnswerID(int answerIndex);
	void FillCorrectAnswerList();
	void NotifySelectBoxCorrect(bool correct);
	void SyncPennyClassroomIndex();
	void InitHeadshotPopanim(std::string plantName);
	void TgaLogNormalResult(bool correct);

private:
	int _index;
	int _questionIndex;
	std::string _currentPlantName;
	NetworkPennyClassroomData _data;

	UIWidgetText* _questionTitleStr;
	UIWidgetText* _questionStr;
	UIWidgetText* _dialogStr;
	PVZ2UIButton* _nextBtn;
	PVZ2UIButton* _redoBtn;
	Widget* _surveyContainer;
	Widget* _headshotContainer;

	bool _inWrongState;
	std::vector<std::vector<int> > _correctAnswerList;
	std::vector<PennyClassroomPlayerSurveySelectBox*> _selects;
};

/////////////////////////////////
/// UIPennyClassroom
/////////////////////////////////
class UIPennyClassroom : public UISingletonDialog<UIPennyClassroom>, public Sexy::ScrollWidgetListener
{
public:
	UIPennyClassroom();
	~UIPennyClassroom();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UIPennyClassroom"; }
	virtual void ButtonDepress(int i_id) override;
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void InitView();
	void SetData(NetworkPennyClassroomData data);

private:
	void InitMaterial();
	void InitFinalBonus();
	void InitTrainingItemWidget();
	void UpdateTrainingItemWidget(NetworkPennyClassroomData data);
	void ShowTips();
	void NotifyCloseDialog();
	void NotifyUpdateTrainingWidget();
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

private:
	NetworkPennyClassroomData _data;// network data from server.
	PVZ2UIScrollingWidget* _scrollWidget;
	int _coin;// penny classroom coin.
};

/////////////////////////////////
/// UIPennyClassroomLockWidget
/////////////////////////////////
class PennyClassroomLockWidget : public Sexy::Widget
{
public:
	PennyClassroomLockWidget();
	virtual ~PennyClassroomLockWidget();

	virtual void Draw(Sexy::Graphics* i_g) override;

	void SetLockDescStr(SexyString str) { _lockStr = str; }
	void SetLockProgressDescStr(SexyString str) { _lockProgressStr = str; }

protected:
	SexyString _lockStr;
	SexyString _lockProgressStr;
};

/////////////////////////////////
/// PennyClassroomShopButton
/////////////////////////////////
class PennyClassroomShopButton : public PVZ1ModeShopButton
{
public:
    PennyClassroomShopButton(int buttonID);

    virtual void ButtonDepress(int i_id) override;
};

////////////////////////////////////
/// PennyClassroomShopCommonWidget
////////////////////////////////////
class PennyClassroomShopCommonWidget : public PVZ1ModeShopCommonWidget
{
public:
	PennyClassroomShopCommonWidget(int index);
	virtual ~PennyClassroomShopCommonWidget();

protected:
    virtual void InitButton() override;
    virtual void ClickCallback() override;
};

/////////////////////////////////
/// UIPennyClassroomShop
/////////////////////////////////
class UIPennyClassroomShop : public UISingletonDialog<UIPennyClassroomShop>, public Sexy::ScrollWidgetListener
{
public:
	UIPennyClassroomShop();
	~UIPennyClassroomShop();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UIPennyClassroomShopNew"; }
	virtual void ButtonDepress(int i_id) override;
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

    void InitView(NetworkPennyClassroomData data);

private:
    void initWidgets(std::vector<PennyClassroomShopData> datalist);
    void refreshMaterial();
    void OnShopBuyFinish(bool success, const S2C_ShopItemPurchaseInfo* pData);
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

private:
    std::vector<PennyClassroomShopCommonWidget*> _vecWidget;
    NetworkPennyClassroomData _data;
};

/////////////////////////////////
/// PennyClassroomManager
/////////////////////////////////
class PennyClassroomManager : public LazySingleton<PennyClassroomManager>
{
public:
	PennyClassroomManager();
	~PennyClassroomManager();

    void LoadData(NetworkPennyClassroomData data);
    NetworkPennyClassroomData GetData() { return _data; }
    bool GetShowNoticeTips();
    void SetCurrentLevel(int type, int currentLevel);
    int GetCurrentTrainingType();
    int GetCurrentLevel();
    bool IsPennyClassroomLevel();
    void RequestMainUI();
    bool CheckShopItemsSoldOut();

private:
    bool CheckNoticeTips();
    void NotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

private:
    bool _showNoticeTips;
    int _type;// training type
    int _currentLevel;// start level index
    bool _requestStatus;
    NetworkPennyClassroomData _data;
};


#endif /* PENNYCLASSROOM_H_ */
