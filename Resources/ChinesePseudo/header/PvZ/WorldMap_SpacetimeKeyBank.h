/*
 * 	WorldMap_SpacetimeKeyBank.h
 *
 * 	Created on:	2022-3-23
 * 		Author:	kkdud
 */


#ifndef __WORLDMAP_SPACETIMEKEYBANK_H__
#define __WORLDMAP_SPACETIMEKEYBANK_H__


#include "RtObject.h"
#include "UIWidget.h"
#include "PVZ2UIButton.h"
#include "UIEasyButtonWidget.h"


namespace Sexy
{
	class Graphics;
}


class WorldMap_SpacetimeKeyBank : public UIWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_SpacetimeKeyBank, UIWidget, RtClass);

	WorldMap_SpacetimeKeyBank()
	{
		m_maxNum = 3;
		m_num = 0;
		m_button = nullptr;
	}

	virtual void onUpdate()	override;

	virtual void Draw(Graphics* i_g) override;
	virtual void onLoadComplete() override;

//	void setNum(int i_num) { m_num = i_num; }
	int getNum() { return m_num; }

//	void setMaxNum(int i_maxKeyNum) { m_maxNum = i_maxKeyNum; }
	int getMaxNum() { return m_maxNum; }

private:
	int m_maxNum;
	int m_num;

	class UISpacetimeKeyInfoButton* m_button;
};


// UISpacetimeKeyInfoButton

class UISpacetimeKeyInfoButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(UISpacetimeKeyInfoButton, UIEasyButtonWidget, RtClass);

    UISpacetimeKeyInfoButton();
    virtual ~UISpacetimeKeyInfoButton();

    virtual void Draw(Graphics* i_g) override;

    virtual void OnClick();
};

class UIAnniversaryInfoButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(UIAnniversaryInfoButton, UIEasyButtonWidget, RtClass);

    UIAnniversaryInfoButton();
    virtual ~UIAnniversaryInfoButton();

    virtual void Draw(Graphics* i_g) override;

    virtual void OnClick();
};

class UIAnniversarySelectLevelInfoButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(UIAnniversarySelectLevelInfoButton, UIEasyButtonWidget, RtClass);

    UIAnniversarySelectLevelInfoButton();
    virtual ~UIAnniversarySelectLevelInfoButton();

    virtual void Draw(Graphics* i_g) override;

    virtual void OnClick();
};

class UISpringFestival2024InfoButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(UISpringFestival2024InfoButton, UIEasyButtonWidget, RtClass);

    UISpringFestival2024InfoButton();
    virtual ~UISpringFestival2024InfoButton();

    virtual void OnClick();
};

class UISpringFestival2024ResetButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(UISpringFestival2024ResetButton, UIEasyButtonWidget, RtClass);

    UISpringFestival2024ResetButton();
    virtual ~UISpringFestival2024ResetButton();

    virtual void OnClick();

protected:
    void ConfirmReset(class UIMessageBox* box, int id);
    void Cancel(class UIMessageBox* box, int id);
};

#endif /* __WORLDMAP_SPACETIMEKEYBANK_H__ */
