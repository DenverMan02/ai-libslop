//
//  ZMatchTicketBank.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/16/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  Displays the current coin currency that the player has
//

#ifndef __ZMatchTicketBank_H__
#define __ZMatchTicketBank_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "PrimeTextWidget.h"


class ZMatchTicketBank : public UIWidget
{
public:
    static GemCurrency         GlobalFakeCurrency;
public:
	RT_CLASS_DEFINE(ZMatchTicketBank, UIWidget, RtClass);
	
	ZMatchTicketBank();
	virtual ~ZMatchTicketBank();
	
	// Public Interface (Inheritable)
	
	virtual void				Draw(Graphics* i_g) override;
	virtual const Sexy::Point	GetCenterPointOnScreen() override;
	virtual bool				IsMouseOver(const int i_mouseX, const int i_mouseY) override;

	// Public Interface (Core)
	
	void						SetFakeCurrencyAmount(GemCurrency i_amount);
	// void						ClearFakeCurrency();
	virtual Sexy::Rect			CalcPlusButtonRect();
	//PVZ2_CHINESE_START
    Rect GetUIRect();
    virtual const Sexy::Rect GetHitRect() override;
	//PVZ2_CHINESE_END
	
protected:

	// Protected Interface (Inheritable)
	
	OVERRIDE_STATE_ONEXIT(WidgetState, Loading);
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);
	
	virtual void				initLoadingResourcesGroupList() override;
	virtual void				registerForEvents() override;
	virtual void				unregisterForEvents() override;

	// Protected Interface
    // void                        onUpdateZMatchTicketFakeCurrency();
	// void						onZmatchTicketCurrencyBanked(int i_amount);
//PVZ2_CHINESE_START
    void                        onZmatchTicketCurrencyAdd(int i_delta);
	void						onZmatchTicketCurrencyChanged(int i_amount);
//PVZ2_CHINESE_END
	void						onGameplayEnded();

	// Protected Members (serialized)
	
	// Protected Members (not serialized)
	
	int                 m_ticketCurrency;
	int                 m_fakeTicketCurrency;
	int                 m_displayedCurrency;
    bool						m_showPlusButton;
	
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
