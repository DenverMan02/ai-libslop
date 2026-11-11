//
//  CoinBank.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/16/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  Displays the current coin currency that the player has
//

#ifndef __COINBANK_H__
#define __COINBANK_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "PrimeTextWidget.h"


class CoinBank : public UIWidget
{
public:
    static CoinCurrency         GlobalFakeCurrency;
public:
	RT_CLASS_DEFINE(CoinBank, UIWidget, RtClass);	
	
	CoinBank();
	virtual ~CoinBank();
	
	// Public Interface (Inheritable)
	//PVZ2_CHINESE_START
	virtual void                onUpdate() override;
	//PVZ2_CHINESE_END
	virtual void				Draw(Graphics* i_g) override;
	virtual const Sexy::Point	GetCenterPointOnScreen() override;
	virtual bool				IsMouseOver(const int i_mouseX, const int i_mouseY) override;

	// Public Interface (Core)
	
	void						SetFakeCurrencyAmount(CoinCurrency i_amount);
	void						ClearFakeCurrency();
	virtual Sexy::Rect			CalcPlusButtonRect();
	//PVZ2_CHINESE_START
	virtual void                SetVisible(const bool i_isVisible);
    void                        SetAutoHide(const bool i_hide);
	//PVZ2_CHINESE_END
protected:

	// Protected Interface (Inheritable)
	
	OVERRIDE_STATE_ONEXIT(WidgetState, Loading);
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);
	
	virtual void				initLoadingResourcesGroupList() override;
	virtual void				registerForEvents() override;
	virtual void				unregisterForEvents() override;

	// Protected Interface
	
//PVZ2_CHINESE_START
	void						onCoinCurrencyChanged(int i_amount);
//PVZ2_CHINESE_END
	void						onGameplayEnded();
    void                        onUpdateCoinFakeCurrency();
	// Protected Members (serialized)
	
	// Protected Members (not serialized)
	
	CoinCurrency				m_coinCurrency;
	CoinCurrency				m_fakeCoinCurrency;
	
	CoinCurrency				m_displayedCurrency;
    bool						m_showPlusButton;
	//PVZ2_CHINESE_START
    bool                        m_autoHide;
	//PVZ2_CHINESE_END
	
private:

	bool						handleTouch(const Sexy::Touch& i_touch);
	void						cancelTouch();
	
	void						calcSpinTime();

	// Private Members (serialized)

	

	// Private Members (not serialized)
	
	pvztime_t					m_spinEndTime;

	Sexy::TouchID				m_touchIdent;
	bool						m_touchInitialized;

    PrimeTextWidget*            m_textWidget;
	//PVZ2_CHINESE_START
	time_t                      m_nextHideTime;
	//PVZ2_CHINESE_END
};

#endif //__COINBANK_H__
