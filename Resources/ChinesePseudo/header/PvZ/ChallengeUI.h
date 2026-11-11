//
//  ChallengeUI.h
//  PlantsVersusZombies2
//
//  Created by Andrew Khosravian on 5/3/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef _CHALLENGE_UI_H_
#define _CHALLENGE_UI_H_

#include "core.h"
#include "UIWidget.h"
#include "Tribool.h"

class ChallengeUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(ChallengeUI, UIWidget, RtClass);
	
	ChallengeUI();
	virtual ~ChallengeUI();
	
	virtual void Draw(Graphics* i_g) override;
	
	void SetFailTime(pvztime_t i_t);
	void FadeWithoutFailing();
	void SetDrawBox(bool i_drawBox) { m_drawBox = i_drawBox; }
	
	void SetSuccess(const Tribool i_succeeded);
	void SetIconOffset(const Sexy::Point& pt) { m_iconOffset = pt; }
	void SetIconImage(ImagePtr i_image) { m_icon = i_image; }
	
protected:

	virtual void initLoadingResourcesGroupList() override;
	
	virtual SexyString getCountText();
	virtual void postDraw(Graphics* i_g);
	
	Sexy::Point m_iconOffset;
	
	int m_textPaddingLeft;
	Sexy::PrimeTypeface* m_font;
	
	ImagePtr m_icon;
	
private:
	
	Tribool m_succeeded;
	Sexy::Color m_textColor;
	ImagePtr m_stateIcon;
	pvztime_t m_failTime;
	bool m_drawBox;
};

#endif
