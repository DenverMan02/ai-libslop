/*
 * 	WorldMap_UnchartedModeSwitchWidget.h
 *
 * 	Created on:	2022-3-25
 * 		Author:	kkdud
 */


#ifndef __WORLDMAP_UNCHARTEDMODESWITCHWIDGET_H__
#define __WORLDMAP_UNCHARTEDMODESWITCHWIDGET_H__


#include "RtObject.h"
#include "UIWidget.h"
#include "PVZ2UIButton.h"
#include "UIEasyButtonWidget.h"


namespace Sexy
{
	class Graphics;
}


// WorldMap_UnchartedModeSwitchWidget

class WorldMap_UnchartedModeSwitchWidget : public UIWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_UnchartedModeSwitchWidget, UIWidget, RtClass);

	WorldMap_UnchartedModeSwitchWidget()
	{
		m_normalButton = nullptr;
		m_hardButton = nullptr;
		m_isHardModeUnlocked = true;
		m_isOnHardMode = false;
	}

	virtual void Draw(Graphics* i_g) override;
	virtual void onLoadComplete() override;

	virtual void onUpdate()	override;

//	void setIsHardModeUnlocked(bool i_isHardModeUnlocked) { m_isHardModeUnlocked = i_isHardModeUnlocked; }
	bool isHardModeUnlocked() { return m_isHardModeUnlocked; }

	bool isOnHardMode() { return m_isOnHardMode; }
	void setIsOnHardMode(bool i_isOnHardMode);

private:
	class UIUnchartedModeNormalButton* m_normalButton;
	class UIUnchartedModeHardButton* m_hardButton;

	bool m_isHardModeUnlocked;
	bool m_isOnHardMode;
};


// UIUnchartedModeNormalButton

class UIUnchartedModeNormalButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(UIUnchartedModeNormalButton, UIEasyButtonWidget, RtClass);

    UIUnchartedModeNormalButton();
    virtual ~UIUnchartedModeNormalButton();

    virtual void Draw(Graphics* i_g) override;
    virtual void onUpdate() override;

//    virtual void updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);

    virtual void OnClick();
};


// UIUnchartedModeHardButton

class UIUnchartedModeHardButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(UIUnchartedModeHardButton, UIEasyButtonWidget, RtClass);

    UIUnchartedModeHardButton();
    virtual ~UIUnchartedModeHardButton();

    virtual void Draw(Graphics* i_g) override;
    virtual void onUpdate() override;

//    virtual void updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);

    virtual void OnClick();
};


#endif /* __WORLDMAP_UNCHARTEDMODESWITCHWIDGET_H__ */
