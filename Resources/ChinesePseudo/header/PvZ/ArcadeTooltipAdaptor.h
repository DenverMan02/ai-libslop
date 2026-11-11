//
//  ArcadeTooltipAdaptor.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 8/12/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArcadeTooltipAdaptor__
#define __PlantsVersusZombies2__ArcadeTooltipAdaptor__

#include "HotUIAdaptor.h"
#include "HotUIWidget.h"

class HotUITouchLayer : public HotUIWidget
{
public:
	RT_CLASS_DEFINE(HotUITouchLayer, HotUIWidget, Sexy::RtClass);
	
	void AddTouchBeganListener(Delegate0 i_onTouchBegan) { m_onTouchBeganListeners += i_onTouchBegan; }
	void AddTouchEndedListener(Delegate0 i_onTouchEnded) { m_onTouchEndedListeners += i_onTouchEnded; }
	
	void TouchBegan( const Sexy::Touch& touch ) override;
	void TouchEnded( const Sexy::Touch& touch ) override;
	
private:
	Event0 m_onTouchBeganListeners;
	Event0 m_onTouchEndedListeners;
	
};

class HotUITouchLayerProperties : public HotUIWidgetProperties
{
public:
	RT_CLASS_DEFINE(HotUITouchLayerProperties, HotUIWidgetProperties, RtClass);
	HotUITouchLayerProperties() {}
	RtClass* GetWidgetClass() const override
	{
		return HotUITouchLayer::StaticGetClass();
	}
};

class ArcadeTooltipAdaptor : public HotUIAdaptor
{
public:
	// Allows the system to ensure it only spawns one tooltip at a time
	// Ostensibly, something like this would evolve into a system
	static int GetGlobalTooltipCount();

public:
	RT_CLASS_DEFINE(ArcadeTooltipAdaptor, HotUIAdaptor, Sexy::RtClass);
	ArcadeTooltipAdaptor();
	virtual ~ArcadeTooltipAdaptor();
	
	void SetTitle(const SexyString& i_titleText);
	void SetDescription(const SexyString& i_bodyText);
	void SetTarget(Sexy::Widget* i_targetWidget);
	
protected:
	std::string getUIFileName();
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void onAnyTouch();
	
private:
	void placeTooltip();
	void refreshLabels();
	
	Sexy::Rect m_targetRect;
	SexyString m_titleText;
	SexyString m_bodyText;
};

#endif /* defined(__PlantsVersusZombies2__ArcadeTooltipAdaptor__) */
