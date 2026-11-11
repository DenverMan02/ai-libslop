/*
 * StatueMazeUI.h
 *
 *  Created on: 2019-11-13
 *      Author: Administrator
 */

#ifndef STATUEMAZEUI_H_
#define STATUEMAZEUI_H_

#include "UIWidget.h"
#include "PrimeTextWidget.h"

class UIMazeMiniGameCredit : public UIWidget
{
public:
	RT_CLASS_DEFINE(UIMazeMiniGameCredit, UIWidget, RtClass);
	UIMazeMiniGameCredit();
	virtual ~UIMazeMiniGameCredit();

	virtual void Draw(Graphics* i_g) override;

    void SetLeftTarget(int i_left);
    void SetCurrentSet(int i_num);
    void SetMaxSet(int i_num);
private:
	int m_leftTarget;
    SexyString m_targetLabel;
    Sexy::Rect m_targetLebelRect;
    Color m_targetColor;

    Sexy::Rect m_setLebelRect;
    SexyString m_setLabel;
    int m_currentSet;
    int m_maxSet;
};

class UIMazeMiniGameLifeCounter : public UIWidget
{
public:
	RT_CLASS_DEFINE(UIMazeMiniGameLifeCounter, UIWidget, RtClass);
	UIMazeMiniGameLifeCounter();
	virtual ~UIMazeMiniGameLifeCounter();

	virtual void Draw(Graphics* i_g) override;

    void SetLife(int i_num) { m_life = i_num; }
private:
	int m_life;
    PrimeTextWidget* m_textWidget;
};


#endif /* STATUEMAZEUI_H_ */
