/*
 * UIPVZ1ModeHowToPlayButton.h
 *
 *  Created on: 2021-8-3
 *      Author: zhousen
 */

#ifndef UIPVZ1MODEHOWTOPLAYBUTTON_H_
#define UIPVZ1MODEHOWTOPLAYBUTTON_H_

#include "UIEasyButtonWidget.h"
#include "Singleton.h"
#include "GameSubSystem.h"
#include "AnimationMgr.h"
#include "StandaloneEffect.h"
#include "Effect_PopAnim.h"


///
/// UIPVZ1ModeHowToPlayButton
///
class UIPVZ1ModeHowToPlayButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(UIPVZ1ModeHowToPlayButton, UIEasyButtonWidget, RtClass);

    UIPVZ1ModeHowToPlayButton();
    virtual ~UIPVZ1ModeHowToPlayButton();

    virtual void Draw(Graphics* i_g) override;

    virtual void OnClick();

protected:
};

#endif /* UIPVZ1MODEHOWTOPLAYBUTTON_H_ */
