/*
 * PlantDefenceEntrance.h
 *
 *  Created on: 2017-11-9
 *      Author: Administrator
 */

#ifndef PLANTDEFENCEENTRANCE_H_
#define PLANTDEFENCEENTRANCE_H_

#include "core.h"
#include "PVZ2UIDialog.h"
#include "PrimeTextWidget.h"
#include "LawnAppEnums.h"
#include "MagentoService.h"
#include "PVZ2UIPlantCard.h"
#include "SettingsDialog.h"
#include "FestivalManager.h"
#include "DString.h"
#include "LevelOfTheDay.h"

class GamePlantDefencePanel : public Widget
{
	virtual ~GamePlantDefencePanel();

	virtual void	Draw(Sexy::Graphics* i_g);
	virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

public:
	int  m_nHeadHeight;
};

////////////////////////

class PlantDefenceEntrance : public Sexy::Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener
{
public:

	PlantDefenceEntrance();
	virtual ~PlantDefenceEntrance();

	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
	virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}
	void onFinishBuyChallengeCount(const bool& i_Success);

	void updateBtnState();
private:

	void setupGameLevelScreen();

	void GoToPlay();

	void onDialogCancel();

	void SelectGameLevel(int i_id);

	void scrollRight();
	void scrollLeft();

	std::string GetModeType(FestivalGameMode i_mode);

	void onUseGemFinish(const bool& isSuccess);
private:
	std::string GetLeveloftheDayLevelName() const;
	DString TranslateLevelForLog(std::string i_levelName) const;
	int TranslateLevelForInt() const;
private:

	//PVZ2UIScrollingWidget*          m_scrollingWidget;

	PVZ2UIButton *                  m_button_play;
	PVZ2UIButton *                  m_button_Refresh;

	Sexy::Rect                      m_rectDialog;
	Sexy::Rect                      m_rectGameMode;
	Sexy::Rect                      m_rectWish;

	SexyString						m_Title;

	std::vector<class PlantDefenceGameWidget*> m_contents;
	//int                                    m_nLastSelect;

	std::vector<class SettingsDialogPane*> m_panes;

	TimeLineTrack<float> m_scrollTimeline;
	int m_depth;

	CurGameLevel m_curGameLevel;

	PVZ2UIButton *m_startBtn;

	std::vector<std::string> m_vecTitle;
};

////////////////////


class PlantDefenceGameWidget : public Widget
{
public:
	PlantDefenceGameWidget(FestivalGameLevel gameLevel,
		int i_id,
		ButtonListener* theButtonListener);
	virtual ~PlantDefenceGameWidget();

	void SetSelected(bool i_selected);

	FestivalGameLevel GetGameLevel() const { return m_nGameLevel; }

	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void Draw(Graphics *i_g);
	virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);

private:

	PVZ2UIButton *    m_button;

	FestivalGameLevel m_nGameLevel;

	bool              m_bSelected;
	int               m_Reward_x;
	int               m_Reward_Count;
	int               m_Reward_y;
};


#endif /* PLANTDEFENCEENTRANCE_H_ */
