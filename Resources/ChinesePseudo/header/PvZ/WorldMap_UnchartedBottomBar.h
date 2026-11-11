/*
 * 	WorldMap_UnchartedBottomBar.h
 *
 * 	Created on:	2022-4-14
 * 		Author:	kkdud
 */

#ifndef __WORLDMAP_UNCHARTEDBOTTOMBAR_H__
#define __WORLDMAP_UNCHARTEDBOTTOMBAR_H__


#include "RtObject.h"
#include "UIWidget.h"
#include "PVZ2UIButton.h"
#include "UIEasyButtonWidget.h"
#include "WorldMap_UnchartedModeSwitchWidget.h"
#include "WorldMap_SpacetimeStarBank.h"


namespace Sexy
{
	class Graphics;
}


class WorldMap_UnchartedBottomBar : public UIWidget
{
public:
	RT_CLASS_DEFINE(WorldMap_UnchartedBottomBar, UIWidget, RtClass);

	WorldMap_UnchartedBottomBar()
	{
		m_spacetimeStar = nullptr;
		m_modeSwitchWidget = nullptr;
		m_headerText = nullptr;
		m_descText = nullptr;
		m_isSpecialWorld = false;
		m_isHeadshotBonus = false;
	}

	virtual void onUpdate()	override;

	virtual void Draw(Graphics* i_g) override;
	virtual void onLoadComplete() override;

	void createUnchartedBirthdayText(SexyString& headerText, SexyString& descText);
	void drawUnchartedBirthdayExtras(Sexy::Graphics* i_g);

private:
	WorldMap_SpacetimeStarBank* m_spacetimeStar;
	WorldMap_UnchartedModeSwitchWidget* m_modeSwitchWidget;
	PrimeTextWidget*            m_headerText;
	PrimeTextWidget*            m_descText;
	bool 						m_isSpecialWorld;
	bool 						m_isHeadshotBonus;

};

#endif /* __WORLDMAP_UNCHARTEDBOTTOMBAR_H__ */
