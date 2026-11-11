/*
 * PVZ2UnchartedModeSelectLevel.h
 *
 *  Created on: 2022-3-14
 *      Author: zhousen
 */

#ifndef PVZ2UNCHARTEDMODESELECTLEVEL_H_
#define PVZ2UNCHARTEDMODESELECTLEVEL_H_

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "NetworkData.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "UIUtil.h"
#include "PVZ1ModeSelectLevel.h"
#include "LevelBasedModifierModule.h"
#include "RepeatUIComponent.h"

namespace Message
{
	void SelectChallenge(int index, int star, bool select);
}

///////////////////////////////
/// Button ID Enum
///////////////////////////////
enum {
	PVZ2_UNCHARTED_MODE_BTN_CLOSE = 1000,
	PVZ2_UNCHARTED_MODE_BTN_TIPS,
	PVZ2_UNCHARTED_MODE_BTN_START,
	PVZ2_UNCHARTED_MODE_ANNIVERSARY_BTN_TIPS,
	PVZ2_UNCHARTED_MODE_ANNIVERSARY_BTN_TASK,
	PVZ2_UNCHARTED_MODE_ANNIVERSARY_BTN_START,
	PVZ2_UNCHARTED_MODE_ANNIVERSARY_BTN_CHALLENGE_START_OFFSET = 100,
	PVZ2_UNCHARTED_MODE_ANNIVERSARY_BTN_TASK_START = 3000,
};

struct ZombieInfo
{
    std::string   zombieType;
    int           level = 0;
};

//////////////////////////////////
/// PVZ2UnchartedModeZombieWidget
//////////////////////////////////
class PVZ2UnchartedModeZombieWidget : public Sexy::Widget
{
public:
	PVZ2UnchartedModeZombieWidget(std::string zombieType, int level = 1);
	virtual ~PVZ2UnchartedModeZombieWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;

protected:
    std::string _zombieType;
    int _level;
    Sexy::DeviceImage* _seedPacketImage;
};

//////////////////////////////////
/// PVZ2UnchartedModeBonusWidget
//////////////////////////////////
class PVZ2UnchartedModeBonusWidget : public PVZ1ModeSelectLevelBonusWidget
{
public:
	PVZ2UnchartedModeBonusWidget(int id, int quantity, bool firstReward = false);
	virtual ~PVZ2UnchartedModeBonusWidget();
};


//////////////////////////////////////
/// PVZ2UnchartedModeChallengeWidget
//////////////////////////////////////
class PVZ2UnchartedModeChallengeWidget : public PVZ1ModeSelectLevelChallengeWidget
{
public:
	PVZ2UnchartedModeChallengeWidget(int buttonID, std::vector<S2C_BonusInfo> data);
	virtual ~PVZ2UnchartedModeChallengeWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void SetStarState(bool hasStar);

protected:
    bool _hasStar;
};


//////////////////////////////////////
/// PVZ2UnchartedModeSelectLevel
//////////////////////////////////////
class PVZ2UnchartedModeSelectLevel : public UISingletonDialog<PVZ2UnchartedModeSelectLevel>, public Sexy::ScrollWidgetListener
{
public:
	PVZ2UnchartedModeSelectLevel();
	~PVZ2UnchartedModeSelectLevel();

	virtual bool	     OnCreate() override;
    virtual std::string  GetLayoutName() override { return "UIPVZ2UnchartedModeSelectLevel"; }
	virtual void		 ButtonDepress(int i_id) override;

	void SetEventNode(MapEventItem* event);
	void SetPlayLevelCallback(Sexy::Delegate1<const std::string&> callback);

    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

private:
	void InitView();
	void InitBonusWidgets();
	void InitChallengeWidgets();
	void InitThemeButtons();
	void InitZombies();
	void InitModes();
	void ApplyDifficulty();

	void PressStartButton();
	void showDescriptionWidget();

	void onNetworkResponse(int i_context, int i_status);
	void onSuccessRespond();
	bool isSpecialLevel();

private:
	std::vector<bool> _challengeSelectList;// the list of challenge choose
	UIScrollControl* _bonusScrollView;// bonus scroll view
	std::vector<UnchartedModeLevelBonusData> _finalBonusDataList;// bonus list
	std::vector<PVZ2UnchartedModeBonusWidget*> _finalBonusWidgetList;// bonus widget list
	Widget* _bonusScrollViewContainer;
	Rect _leftArrowRect;
	Rect _rightArrowRect;
	MapEventItem* _eventNodeToPlay;
    Sexy::Delegate1<const std::string&> _playLevelCallback;
    std::vector<int> _challengeStatusList;// the challenge status list 0 = not complete 1 = complete
    bool _timeLimitWorld;
};

//////////////////////////////////////
/// PVZ2UnchartedModeChallengeWidget
//////////////////////////////////////
class PVZ2UnchartedModeAnniversaryChallengeWidget : public PVZ2UIButton, public ButtonListener
{
public:
	PVZ2UnchartedModeAnniversaryChallengeWidget(int buttonID, bool isBaseIcon);

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void SetProps(LevelModifierModuleCollectionPtr ptr) { m_props = ptr; }
    void InitView();
    void SetSelected(bool select) { m_selected = select; }
    bool IsSelected() const { return m_selected; }
    bool IsBaseChallenge() const { return m_isBaseChallenge; }
    int GetIndex() { return m_index; }
    int GetStar() { return m_star; }

protected:
    LevelModifierModuleCollectionPtr m_props;
    int m_buttonID;
    int m_index;// challenge index
    bool m_selected;// is selected.
    int m_star;// star count
    Image* m_bgPress;
    Image* m_bgUnpress;
    Image* m_starPress;
    Image* m_starUnpress;
    Image* m_checkMark;
    bool m_isBaseChallenge;
};

/////////////////////////////////////////////////
/// PVZ2UnchartedModeAnniversaryChallengeDesc
/////////////////////////////////////////////////
class PVZ2UnchartedModeAnniversaryChallengeDesc : public Sexy::Widget
{
public:
	PVZ2UnchartedModeAnniversaryChallengeDesc(int index, int star, bool baseIcon);

    virtual void Draw(Sexy::Graphics* i_g) override;

    void InitView();

protected:
    SexyString m_str;
    Image* m_icon;
    int m_index;
    int m_star;
    bool m_isBaseIcon;
};

//////////////////////////////////////////////
/// PVZ2UnchartedModeSelectLevelAnniversary
//////////////////////////////////////////////
class PVZ2UnchartedModeSelectLevelAnniversary : public UISingletonDialog<PVZ2UnchartedModeSelectLevelAnniversary>, public Sexy::ScrollWidgetListener
{
public:
	PVZ2UnchartedModeSelectLevelAnniversary();
	~PVZ2UnchartedModeSelectLevelAnniversary();

	virtual bool	     OnCreate() override;
    virtual std::string  GetLayoutName() override { return "UIPVZ2UnchartedModeSelectLevelAnniversary"; }
	virtual void		 ButtonDepress(int i_id) override;

	void SetEventNode(MapEventItem* event);
	void SetPlayLevelCallback(Sexy::Delegate1<const std::string&> callback);

    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void ShowChallgenDefaultDesc(bool show);

private:
	void InitView();
	void InitBonusWidgets();
	void InitChallengeWidgets();

	void InitTaskButton();
	void ShowTaskPanel();

	void PressStartButton();
	void showDescriptionWidget();

	void onNetworkResponse(int i_context, int i_status);
	void onSuccessRespond();
	bool isSpecialLevel();
	int CalcChallengeButtonID(int index, int star);

	void SelectChallenge(int index, int star, bool select) ;
	void RefreshUI();

private:
	UIScrollControl* _bonusScrollView;// bonus scroll view
	std::vector<UnchartedModeLevelBonusData> _finalBonusDataList;// bonus list
	std::vector<PVZ2UnchartedModeBonusWidget*> _finalBonusWidgetList;// bonus widget list
	Widget* _bonusScrollViewContainer;
	Rect _leftArrowRect;
	Rect _rightArrowRect;
	MapEventItem* _eventNodeToPlay;
    Sexy::Delegate1<const std::string&> _playLevelCallback;
    std::vector<int> _challengeStatusList;// the challenge status list 0 = not complete 1 = complete
    bool _timeLimitWorld;
    std::vector<PVZ2UnchartedModeAnniversaryChallengeWidget*> _baseChallengeIcons;
    std::vector<std::vector<PVZ2UnchartedModeAnniversaryChallengeWidget*> > _challengeIcons;
    Widget* _challengeDescContainer;
};

/// Task Panel
class PVZ2UnchartedModeSelectLevelTaskPanel : public UISingletonDialog<PVZ2UnchartedModeSelectLevelTaskPanel>, public Sexy::ScrollWidgetListener
{
public:
	PVZ2UnchartedModeSelectLevelTaskPanel();
	~PVZ2UnchartedModeSelectLevelTaskPanel();

	virtual bool	     OnCreate() override;
    virtual std::string  GetLayoutName() override { return "UIPVZ2UnchartedModeSelectLevelTask"; }
	virtual void		 ButtonDepress(int i_id) override;

    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

private:
	void InitView();
};

//////////////////////////////////////////////
/// UnchartedAnniversaryTaskWidget
//////////////////////////////////////////////
class UnchartedAnniversaryTaskWidget : public TemplateTaskWidget
{
public:
    RT_CLASS_DEFINE(UnchartedAnniversaryTaskWidget, Sexy::Widget, RtClass);

    virtual void InitTask(GeneralTask* i_task) override;
    void SetIndex(int index) { m_taskIndex = index; }

protected:
    virtual void RequestReward() override;
    virtual void DrawTaskBackground(Sexy::Graphics* i_g);
    void DrawRewards(Sexy::Graphics* i_g) override;

protected:
    int m_taskIndex;
};

#endif /* PVZ2UNCHARTEDMODESELECTLEVEL_H_ */
