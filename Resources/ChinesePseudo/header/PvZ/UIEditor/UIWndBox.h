//
//  UITest.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/5/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//
#ifndef __UIWndBox_h_
#define __UIWndBox_h_
#pragma once
#include <map>
#include "Color.h"
#include "UIRect.h"

namespace Sexy
{
	class Widget;
	class Graphics;
}

namespace UI
{
class WndBox
{
public:
	enum{
		Unknow = 0,
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		WndArea,
		DrawBegin = TopLeft,
		DrawEnd = WndArea + 1,

		TopCenter,
		LeftCenter,
		RightCenter,
		BottomCenter,

		InnerArea,
		OutterArea,

		Max,
	};
public:
	WndBox(Sexy::Widget * wnd);
	~WndBox(void);
	void									draw(Sexy::Graphics* i_g, const Sexy::Color& clr, bool bSelect);
	void									setWindow(Sexy::Widget* wnd);
	Sexy::Widget*				getWindow() const { return m_pWnd; }
	void									reset();
	int									getMouseType(const UI::Vector2f& pt);

protected:
	Sexy::Widget*				m_pWnd;
	typedef std::map<int, UI::Rectf>	MapArea;
	MapArea							m_areas;
};

}

#endif
