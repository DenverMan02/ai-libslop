//
//  GemBank.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/16/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  Displays the current coin currency that the player has
//

#ifndef __GEMBANK_H__
#define __GEMBANK_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "PrimeTextWidget.h"


class GemBank : public UIWidget
{
public:
    static GemCurrency         GlobalFakeCurrency;
public:
	RT_CLASS_DEFINE(GemBank, UIWidget, RtClass);
	
	GemBank();
	virtual ~GemBank();
	
	// Public Interface (Inheritable)
	
	virtual void				Draw(Graphics* i_g) override;
	virtual const Sexy::Point	GetCenterPointOnScreen() override;
	virtual bool				IsMouseOver(const int i_mouseX, const int i_mouseY) override;

	// Public Interface (Core)
	
	void						SetFakeCurrencyAmount(GemCurrency i_amount);
	void						ClearFakeCurrency();
	virtual Sexy::Rect			CalcPlusButtonRect();
	//PVZ2_CHINESE_START
    Rect GetUIRect();
    virtual const Sexy::Rect GetHitRect() override;
	//PVZ2_CHINESE_END
    bool						m_showPlusButton;
	
protected:

	// Protected Interface (Inheritable)
	
	OVERRIDE_STATE_ONEXIT(WidgetState, Loading);
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);
	
	virtual void				initLoadingResourcesGroupList() override;
	virtual void				registerForEvents() override;
	virtual void				unregisterForEvents() override;

	// Protected Interface
    void                        onUpdateGemFakeCurrency();
	void						onGemCurrencyBanked(int i_amount);
//PVZ2_CHINESE_START
    void                        OnGemCurrencyAdd(int i_delta);
	void						onGemCurrencyChanged(int i_amount);
//PVZ2_CHINESE_END
	void						onGameplayEnded();

	// Protected Members (serialized)
	
	// Protected Members (not serialized)
	
	GemCurrency                 m_gemCurrency;
	GemCurrency                 m_fakeGemCurrency;
	GemCurrency                 m_displayedCurrency;

	
private:

	bool						handleTouch(const Sexy::Touch& i_touch);
	void						cancelTouch();
	
	void						calcSpinTime();

	// Private Members (serialized)
	
	// Private Members (not serialized)
	
	bool						m_alwaysVisible;
	
	pvztime_t					m_spinEndTime;

	Sexy::TouchID				m_touchIdent;
	bool						m_touchInitialized;
	
    PrimeTextWidget*            m_textWidget;
};

#endif //__COINBANK_H__
