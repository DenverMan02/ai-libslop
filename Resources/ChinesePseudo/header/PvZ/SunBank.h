//
//  SunBank.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/14/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  Displays the current amount of sun that the player has
//

#ifndef __SUNBANK_H__
#define __SUNBANK_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"
#include "PrimeTextWidget.h"

class UIWidgetSheet;

class SunBank : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(SunBank, UIWidget, RtClass);	
	
	SunBank();
	virtual ~SunBank();
	
	// Public Interface (Inheritable)
	
	virtual void				Draw(Graphics* i_g) override;
	virtual const Sexy::Point	GetCenterPointOnScreen() override;

	// Public Interface (Core)
	
	inline void					SetSunCurrency(const SunCurrency i_sunCurrency);
    //PVZ2_CHINESE_BEGIN
    inline void                 EnableBuySunFeature(bool i_enable);
    void                        SetIsTutorial(bool i_tutorial);
    bool                        IsTutorial(){ return m_isTutorial; }
    Rect                        GetUIRect();
    virtual const               Sexy::Rect GetHitRect() override;
    //PVZ2_CHINESE_END

protected:

	// Protected Interface (Inheritable)
	
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);

	virtual void				initLoadingResourcesGroupList() override;
	virtual void				onInitialized() override;
	virtual void				onPostLoad() override;
	virtual void 				registerForEvents() override;
	virtual void 				unregisterForEvents() override;

	// Protected Members (not serialized)
	SunCurrency					m_sunCurrency;
	SunCurrency					m_displayedCurrency;

private:	

//PVZ2_CHINESE_START
	bool handleTouch(const Sexy::Touch& i_touch);
	void cancelTouch();
//PVZ2_CHINESE_END
	// Private Interface
	
	//PVZ2_CHINESE_START
    void                    onGameplayEnded();
    void                    onSunBankMax(bool i_max);
	//PVZ2_CHINESE_END
	void					onSunBanked(int i_upcomingAmount);
	void					onSunSpent(int i_newAmount);
	//PVZ2_CHINSE_START
	void					onSunAdd(int i_newAmount);
	//PVZ2_CHINSE_END
	void					onSunIsInsufficient();
    void                    DrawText(Graphics* i_g);

	
	void					calcSpinTime();
	void 					onLevelStart();

	// Private Members (serialized)
	
	// Private Members (not serialized)
//PVZ2_CHINESE_START
	Sexy::TouchID           m_touchIdent;
	bool                    m_touchInitialized;
    bool                    m_canBuySun;
    bool                    m_reachMax;
    bool                    m_isTutorial;
    class BouncingArrow*    m_tutorialArrow;
//PVZ2_CHINESE_END
	
	pvztime_t				m_insufficientMoneyEndTime;
	pvztime_t				m_insufficientMoneyFlashStartTime;
	
	pvztime_t				m_collectSunFlashEndTime;
	
	pvztime_t				m_spinEndTime;
    
    PrimeTextWidget*        m_sunTextWidget;
	
};

inline void SunBank::SetSunCurrency(const SunCurrency i_sunCurrency)
{
	m_sunCurrency = i_sunCurrency;
}

inline void SunBank::EnableBuySunFeature(bool i_enable)
{
    m_canBuySun = i_enable;
}

namespace Message
{
	void CheckBuySunManually(bool* pIsManually);
}

#endif //__SUNBANK_H__
