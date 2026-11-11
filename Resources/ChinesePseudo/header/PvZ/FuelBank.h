//
//  FuelBank.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 7/19/19.
//  Copyright (c) 2019 PopCap Games. All rights reserved.
//
//

#ifndef __FuelBank_H__
#define __FuelBank_H__

#include "PVZTypes.h"
#include "Point.h"
#include "Rect.h"
#include "RtObject.h"
#include "SequentialActionRunner.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "UIWidget.h"
//#include "WidgetAction.h"

class PVZ2UIImageWidget;
namespace Sexy {
class Graphics;
class PrimeTextWidget;
}  // namespace Sexy

enum FuelBankMode
{
	FuelBank_Rift,
	FuelBank_PVZ1_Fuel,
	FuelBank_PVZ1_Coin,
	FuelBank_PVZ1_Coin_Hard,
	FuelBank_NewPVP_Coin
};

class FuelBank : public UIWidget
{
	enum FuelBankDisplayState
	{
		NORMAL,
		SPINNING,
	};

public:
	RT_CLASS_DEFINE(FuelBank, UIWidget, RtClass);

	FuelBank();
	virtual ~FuelBank();

	void SetBankMode(FuelBankMode i_mode);
	void SetButtonImage(std::string i_imageStr);

	// Public Interface (Inheritable)

	void Draw(Graphics* i_g) override;
	const Sexy::Point GetCenterPointOnScreen() override;

	void OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	void OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	void OnMouseMove(const int i_mouseX, const int i_mouseY) override;

	// Public Interface (Core)

protected:

	// Protected Interface (Inheritable)

	OVERRIDE_STATE_ONEXIT(WidgetState, Loading);
	OVERRIDE_STATE_UPDATE(WidgetState, Ready);

	void registerForEvents() override;

	// Protected Interface

	void onFuelCurrencyBanked(int i_amount);
	void onFuelCurrencyChanged(int i_delta, const bool i_willBeBankedLater, int type);
	void onGameplayEnded();

	//void onDisplayStateDone(WidgetActionPtr widgetAction);

	// Protected Members (serialized)

	// Protected Members (not serialized)

	CoinCurrency m_FuelCurrency;

	CoinCurrency m_displayedCurrency;

private:

	virtual void updateButtonStates(const int i_screenX, const int i_screenY, const bool i_isPressed);

	void updateFuelAmount(int i_delta);
	void startDisplayState(FuelBankDisplayState newState);
	void calcSpinTime();
	const void drawText(Graphics* i_g);

	// Private Members (serialized)

	// Private Members (not serialized)

	pvztime_t m_displayStateEndTime;
	FuelBankDisplayState m_displayState;

	PrimeTextWidget* m_textWidget;
    PrimeTextWidget* m_timerWidget;

	ForeverSequentialActionRunner m_actionRunner;
	FuelBankMode m_mode;
	Sexy::ImagePtr m_buttonImg;
	Sexy::ImagePtr m_buttonImgDown;
};

#endif //__MintBank_H__
