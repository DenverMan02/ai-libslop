//
//  StaminaDisplayPanel.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 13-12-6.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StaminaDisplayPanel__
#define __PlantsVersusZombies2__StaminaDisplayPanel__

#include <iostream>
#include "core.h"
#include "UIWidget.h"
#include "RtObject.h"
#include "ButtonListener.h"
#include "StateMachine.h"
#include "SexyAppFramework/Point.h"


class StandaloneEffect;
class Effect_PopAnim;

class StaminaDisplayPanel : public UIWidget
{
public:

    enum SlidingState
	{
		STATE_INVALID,
		STATE_IDLE,
		STATE_SLIDING_IN,
		STATE_SLIDING_OUT,
		STATE_WAITING,
	};
    
	RT_CLASS_DEFINE(StaminaDisplayPanel, UIWidget, RtClass);

	StaminaDisplayPanel();
	virtual ~StaminaDisplayPanel();
    
    virtual void			Draw(Graphics* i_g) override;
    
    virtual void			OnMouseMove(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseUp(const int i_mouseX, const int i_mouseY) override;
    virtual bool            IsMouseOver(const int i_mouseX, const int i_mouseY) override;
    
    void    startFlyAnimation(Sexy::Point ptDestination);
    void    startSlideInAnimation();
    void    startSlideOutAnimation();

    bool    isPlayingFlyAnimation;

    void	SetVisible(const bool i_isVisible);
    
    
protected:
    Sexy::Rect CalcLayerRect();
    Sexy::Rect CalcPlusButtonRect();

    bool    buttonDown;
    
    int     halfCoord(int in);
    
    void 	onLeafDisappearEnd(StandaloneEffect* i_effect);

    
	virtual void							onUpdate() override;
    
    void    drawFlyAnimation(Graphics* i_g);
    
    
    Sexy::Point     originLeafPosition;
    Sexy::Point     destLeafPosition;
    pvztime_t       m_slideTimeStart;
    float           currentXLocation;
    float           currentYLocation;

    RtWeakPtr<Effect_PopAnim> m_leafDisappearEffect;
    pvztime_t       startFlyingTime;
    float           m_slideTimeDuration;
    SlidingState	m_slidingState;
    
    bool            m_visible;
};



#endif /* defined(__PlantsVersusZombies2__StaminaDisplayPanel__) */
