//
//  EASquaredCoinBankButton.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 4/8/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EASquaredCoinBankButton__
#define __PlantsVersusZombies2__EASquaredCoinBankButton__

#include "EASquared.h"
#include "RtObject.h"
#include "SlidingWidget.h"

namespace Sexy
{
	class Graphics;
	class PrimeTextWidget;
}

class EASquaredCoinBankButton : public SlidingWidget
{
public:
	RT_CLASS_DEFINE(EASquaredCoinBankButton, SlidingWidget, RtClass);
	
	EASquaredCoinBankButton();
	virtual ~EASquaredCoinBankButton();
	
	void CalculateInitialVisibility();
	
	virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void OnMouseMove(const int i_mouseX, const int i_mouseY) override;
	
protected:
	void onUpdate() override;
	
private:
	void createTextWidget();
	void setUpSlide();
	void drawButton(Sexy::Graphics* i_g);
	void drawText(Sexy::Graphics* i_g);
	void onButtonPush();
	void updateVisibility();
	void queueUpdateVisibility();
	bool shouldBeVisible();
	Sexy::Color getAlphaColorFromSlide();
    void sendMetricsReport();
	
	void onEASquaredAdFinished(EASquaredAdFinishedReason::EASquaredAdFinishedReason i_reason);
	
	virtual void updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
	
	Sexy::PrimeTextWidget* mTextWidget;
	class PopAnimRig* mPopAnimRig;
	const int mNumCoinsToReward;
	bool mIsSlideSetUp;
    bool mIsShowing;
	bool mNeedUpdateVisibility;
};

#endif /* defined(__PlantsVersusZombies2__EASquaredCoinBankButton__) */
