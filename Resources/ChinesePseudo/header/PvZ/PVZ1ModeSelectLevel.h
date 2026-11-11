/*
 * PVZ1ModeSelectLevel.h
 *
 *  Created on: 2021-7-19
 *      Author: zhousen
 */

#ifndef PVZ1MODESELECTLEVEL_H_
#define PVZ1MODESELECTLEVEL_H_

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "NetworkData.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "UIUtil.h"
#include "PVZ1ModeUtils.h"

namespace Message
{
	void UpdatePVZ1ModeSelectLevelBonus(int id, int count);
	void UpdateSelectChallenge(int index, bool select);
}

enum {
	BUTTON_ID_CLOSE = 1000,
	BUTTON_ID_INFO,
	BUTTON_ID_START,
	BUTTON_ID_THEME_INDEX_START,
};

class PVZ1ModeSelectLevelThemeButton : public PVZ2UIButton, public ButtonListener
{
public:
	PVZ1ModeSelectLevelThemeButton(int i_id);

	virtual void Draw(Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;

	void InitView();
	void SetThemeIndex(int theme) { _themeIndex = theme; }
	void SetThemeName(const std::string& name) { _themeString = name; }

protected:
	void ShowDescriptionUI();

protected:
	int _themeIndex;// theme mode
	std::string _themeString;// theme string
	Image* _themeImage;// main theme image
};

class PVZ1ModeSelectLevelBonusWidget : public Sexy::Widget
{
public:
	PVZ1ModeSelectLevelBonusWidget(int id, int quantity, bool firstReward = false);
	virtual ~PVZ1ModeSelectLevelBonusWidget();

	void Draw(Sexy::Graphics* i_g) override;
	void Resize(int theX, int theY, int theWidth, int theHeight) override;

	void SetCurrentCount(int count) { _currentCount = count; }
	int GetCurrentCount() const { return _currentCount; }

protected:
	void UpdateRatio();
	void RegisterEvents();
	void InitView();
	void UpdateLevelBonus(int id, int count);

protected:
	bool _isFirstReward;// show first reward str
	SexyString _firstRewardStr;// first reward str
	bool _showRatio;// show ratio str
	SexyString _ratioStr;// calc ratio str
	UIRewardFrame* _rewardPtr;// main item reward frame ui
	int _itemID;// main item id
	int _originalCount;// original item count
	int _currentCount;// challenge bonus item count
};

class PVZ1ModeSelectLevelChallengeWidget : public PVZ2UIButton, public ButtonListener
{
public:
	PVZ1ModeSelectLevelChallengeWidget(int buttonID, std::vector<S2C_BonusInfo> data);

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void SetHardMode(bool hard) { _isHardMode = hard; }
    void SetChallengeStatus(bool complete) { _isChallengeComplete = complete; }
    void SetDescStr(SexyString str) { _descStr = str; }
    bool IsSelected() const { return _selected; }

protected:
    int _index;// challenge index
    bool _isHardMode;// is hard mode
    bool _selected;// is selected.
    SexyString _descStr;// challenge str
    std::vector<S2C_BonusInfo> _bonus;// challenge bonus
    bool _isChallengeComplete;// if this challenge is completed
};

class PVZ1ModeSelectLevel : public UISingletonDialog<PVZ1ModeSelectLevel>, public Sexy::ScrollWidgetListener
{
public:
	PVZ1ModeSelectLevel();
    virtual ~PVZ1ModeSelectLevel();
	virtual bool	                        OnCreate() override;
    virtual void 							Draw(Sexy::Graphics* i_g) override;
    virtual std::string                     GetLayoutName() override { return "UIPVZ1ModeSelectLevel"; }
	virtual void							ButtonDepress(int i_id) override;

	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void SetEventNode(MapEventItem* event);
	void SetPlayLevelCallback(Sexy::Delegate1<const std::string&> callback);
	void RemoveBonusWidget(PVZ1ModeSelectLevelBonusWidget* widget);

private:
	void InitView();
	void InitBonusWidgets();
	void InitChallengeWidgets();
	void InitThemeButtons();
	void PressStartButton();
	void UpdateSelectChallenge(int index, bool select);
	void showDescriptionWidget();
	void closeDescriptionWidget();

	void onNetworkResponse(int i_context, int i_status);
	void onSuccessRespond();

	void UpdateLevelBonus(int id, int count);

//	std::vector<PVZ1ModeSelectLevelBonusWidget> _bonusWidgets;
//	std::vector<PVZ1ModeSelectLevelChallengeWidget> _challengeWidgets;
	std::vector<bool> _challengeSelectList;// the list of challenge choose
	ActivityDescriptionUI* _descriptionUI;// tips ui
	UIScrollControl* _bonusScrollView;// bonus scroll view
	std::vector<PVZ1ModeLevelBonusData> _finalBonusDataList;// bonus list
	std::vector<PVZ1ModeSelectLevelBonusWidget*> _finalBonusWidgetList;// bonus widget list
	Widget* _bonusScrollViewContainer;
	Rect _leftArrowRect;
	Rect _rightArrowRect;
	MapEventItem* _eventNodeToPlay;
    Sexy::Delegate1<const std::string&> _playLevelCallback;
    std::vector<int> _challengeStatusList;// the challenge status list 0 = not complete 1 = complete
};


#endif /* PVZ1MODESELECTLEVEL_H_ */
