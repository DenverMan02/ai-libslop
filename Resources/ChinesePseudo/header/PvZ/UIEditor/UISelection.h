//
//  UITest.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/5/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//
#ifndef __UISelection_h_
#define __UISelection_h_
#pragma once
#include "UIWndBox.h"

namespace UI
{

class Selection
{
public:
	enum AlignType{
		AlignLeft,
		AlignRight,
		AlignTop,
		AlignBottom,
		AlignHCenter,
		AlignVCenter,
		SameWidth,
		SameHeight,
		ArrangeHorz,
		ArrangeVert,
	};
public:
	Selection(void);
	~Selection(void);
	bool										selectWindow(Sexy::Widget* wnd);		// true 窗体被选中，false未被选中
	bool										unselectWindow(Sexy::Widget* wnd);	// true 已取消选中，
	Sexy::Widget*					getSelectWindow() const;
	WndBox								getSelectBox() const;
	void										clear();
	void										reset();
	size_t									count() const { return m_boxes.size(); }

	void										draw(Sexy::Graphics* i_g, const Sexy::Color& clrSel, const Sexy::Color& clrOther);
	void										drawParent(Sexy::Graphics* i_g, const Sexy::Color& clrParent);

	bool										beginDrag(int x, int y, int mouseType);
	void										dragMove(int x, int y);
	void										endDrag();
	bool										isDraging() const;

	void										offsetArea(const Rectf& rcOffset);
	void										alignArea(AlignType type, float step = 0.0f);
protected:
	void										offsetArea(const Rectf& rcOffset, Sexy::Widget* wnd);

protected:
	typedef std::vector<WndBox> VecBox;
	VecBox								m_boxes;
	Vector2f						m_mousePosition;
	int										m_mouseType;
};

class CopySelection
{
public:
protected:
private:
};

}

#endif
