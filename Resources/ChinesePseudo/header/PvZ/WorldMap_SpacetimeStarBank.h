/*
 * 	WorldMap_SpacetimeStarBank.h
 *
 * 	Created on:	2022-3-23
 * 		Author:	kkdud
 */


#ifndef __WORLDMAP_SPACETIMESTARBANK_H__
#define __WORLDMAP_SPACETIMESTARBANK_H__


#include "RtObject.h"
#include "UIWidget.h"
#include "PVZ2UIButton.h"
#include "UIEasyButtonWidget.h"
#include "UISingletonDialog.h"

namespace Sexy
{
	class Graphics;
}


class WorldMap_SpacetimeStarBank : public UIWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_SpacetimeStarBank, UIWidget, RtClass);

	WorldMap_SpacetimeStarBank()
	{
		m_maxNum = 21;
		m_num = 0;
		m_button = nullptr;
		m_isAddNotice = false;
	}

	virtual void Draw(Graphics* i_g) override;
	virtual void onLoadComplete() override;

	virtual void onUpdate()	override;

//	void setNum(int i_num) { m_num = i_num; }
	int getNum() { return m_num; }

//	void setMaxNum(int i_maxNum) { m_maxNum = i_maxNum; }
	int getMaxNum() { return m_maxNum; }

//	void setIsAddNotice(bool i_isAddNotice) { m_isAddNotice = i_isAddNotice; }
	bool isAddNotice() { return m_isAddNotice; }

private:
	void checkHasAvailableRewards();

	int m_maxNum;
	int m_num;

	bool m_isAddNotice;

	class UISpacetimeStarRewardButton* m_button;
};


// UISpacetimeStarRewardButton

class UISpacetimeStarRewardButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(UISpacetimeStarRewardButton, UIEasyButtonWidget, RtClass);

    UISpacetimeStarRewardButton();
    virtual ~UISpacetimeStarRewardButton();

    virtual void onUpdate() override;
    virtual void Draw(Graphics* i_g) override;

    virtual void OnClick();

private:
    bool m_timeLimitWorld;
};

////////////////////////////////////////
/// UISpringFestival2024Difficulty
////////////////////////////////////////
class UISpringFestival2024Difficulty : public UIWidget
{
public:
	RT_CLASS_DEFINE(UISpringFestival2024Difficulty, UIWidget, RtClass);

	UISpringFestival2024Difficulty();

	virtual void Draw(Graphics* i_g) override;
	virtual void onLoadComplete() override;

protected:
	class UISpringFestival2024DifficultyButton* m_button;
};

////////////////////////////////////////////
/// UISpringFestival2024DifficultyButton
////////////////////////////////////////////
class UISpringFestival2024DifficultyButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(UISpringFestival2024DifficultyButton, UIEasyButtonWidget, RtClass);

    UISpringFestival2024DifficultyButton();

    virtual void OnClick();

protected:
    std::string GetCurrentLevelName();
    int GetLevelDifficulty(std::string levelName);

    std::string m_currentLevelName;
    int m_currentDifficulty;
};

////////////////////////////////////////
/// UISpringFestival2024Boost
////////////////////////////////////////
class UISpringFestival2024Boost : public UIWidget
{
public:
	RT_CLASS_DEFINE(UISpringFestival2024Boost, UIWidget, RtClass);

	UISpringFestival2024Boost();

	virtual void Draw(Graphics* i_g) override;
	virtual void onLoadComplete() override;

protected:
	class UISpringFestival2024BoostButton* m_button;
};

////////////////////////////////////////////
/// UISpringFestival2024BoostButton
////////////////////////////////////////////
class UISpringFestival2024BoostButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(UISpringFestival2024BoostButton, UIEasyButtonWidget, RtClass);

    UISpringFestival2024BoostButton();

    virtual void OnClick();
};

/////////////////////////////////////////////
/// UISpringFestival2024BoostPanel
//////////////////////////////////////////////
class UISpringFestival2024BoostPanel : public UISingletonDialog<UISpringFestival2024BoostPanel>, public Sexy::ScrollWidgetListener
{
public:
	enum {
		BTN_BOOST_CLOSE = 1000,
	};

	UISpringFestival2024BoostPanel();
    virtual ~UISpringFestival2024BoostPanel();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UISpringFestival2024BoostPanel"; }
    virtual void                            Update() override;
	virtual void							ButtonDepress(int i_id) override;

	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

	void InitView();
};

#endif /* __WORLDMAP_SPACETIMESTARBANK_H__ */
