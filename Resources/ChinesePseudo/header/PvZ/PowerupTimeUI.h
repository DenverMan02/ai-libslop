//
//  PowerupTimeUI.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 12/17/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PowerupTimeUI__
#define __PlantsVersusZombies2__PowerupTimeUI__

#include "PowerupUI.h"
#include "Effect_PopAnim.h"
#include "Effect_BouncingArrow.h"

class BasePowerup;

namespace Message
{
    void ShowCukeConfirm(bool show);
}

class PowerupTimeUI : public PowerupUI
{
public:
	RT_CLASS_DEFINE(PowerupTimeUI, PowerupUI, RtClass);
	
	PowerupTimeUI(){}
	virtual ~PowerupTimeUI(){}

	virtual void Draw(Graphics* i_g) override;
	virtual bool OnTouch(const Sexy::Touch& touch) override;
    void setTutorialIntroState(bool isIn) { m_isInCukeTutorialIntro = isIn; }

protected:
	virtual void onInitialized() override;
	virtual void onDestroy() override;
	virtual void onUpdate() override;
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;

private:

    Rect CalcConfirmationRect();
    Rect CalcCukeRect();
    
    bool handleTouch(const Sexy::Touch& touch);
    void cancelTouch();
    
	void setSomeUIsClickableInBetweenTutorial(bool isClickable) const;
    
    bool shouldShowCukePackageUI();
    void showCukePackageUI();

	RtWeakPtr<Effect_PopAnim> 	m_cukeFireEffect;
	RtWeakPtr<Effect_BouncingArrow> m_bouncingArrow;

    bool m_showCukeBuyConfirmUI = false;
    bool m_showCukeBuyConfirmUIFirst = false;
    bool m_isInCukeTutorialIntro;
    Sexy::TouchID m_touchIdent;
    bool m_collect;
};

#endif /* defined(__PlantsVersusZombies2__PowerupTimeUI__) */
