/*
 * AdaptorPVZ1ModeHowToPlayScreen.h
 *
 *  Created on: 2021-7-16
 *      Author: zhousen
 */

#ifndef ADAPTORPVZ1MODEHOWTOPLAYSCREEN_H_
#define ADAPTORPVZ1MODEHOWTOPLAYSCREEN_H_

#include "AdaptorHowToPlayScreen.h"
#include "HotUIAdaptor.h"
#include "ObjectTypeDescriptor.h"

namespace Message
{
	void  NotifyPVZ1HowToPlayClose();
    void  NotifyNewPvPHowToPlayClose();
    void  NotifyUnchartedHowToPlayClose();
}

class AdaptorPVZ1ModeHowToPlayScreen : public HowToPlayScreen
{
    RT_CLASS_DEFINE(AdaptorPVZ1ModeHowToPlayScreen, HowToPlayScreen, RtClass);

public:
    void ButtonDepress(int i_buttonID) override;

protected:
    void onLoadUIView() override;
    void onLayoutFinished() override;
    void doClose();
};

class AdaptorNewPvPHowToPlayScreen : public HowToPlayScreen
{
    RT_CLASS_DEFINE(AdaptorNewPvPHowToPlayScreen, HowToPlayScreen, RtClass);

public:
    void ButtonDepress(int i_buttonID) override;

protected:
    void onLoadUIView() override;
    void onLayoutFinished() override;
    void doClose();
};

class AdaptorUnchartedHowToPlayScreen : public HowToPlayScreen
{
    RT_CLASS_DEFINE(AdaptorUnchartedHowToPlayScreen, HowToPlayScreen, RtClass);

public:
    void ButtonDepress(int i_buttonID) override;

protected:
    void onLoadUIView() override;
    void onLayoutFinished() override;
    void doClose();
};

#endif /* ADAPTORPVZ1MODEHOWTOPLAYSCREEN_H_ */
