//
//  UIEditorMenu.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/6/11.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UIEditorMenu_h_
#define _UIEditorMenu_h_

#include "Widget.h"
#include "PVZ2UIButton.h"
#include "RtDelegate.h"

enum
{
	UIEditorMenu_ID_RESERVE = 100,
	UIEditorMenu_ID_CUSTOM,
};

class UIEditorMenu : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	typedef Sexy::Delegate1<int> MenuClickEvent;
public:
	UIEditorMenu();
	~UIEditorMenu();

	virtual void						Draw(Sexy::Graphics* i_g);
	virtual void						Resize(int i_x, int i_y, int i_w, int i_h);
	virtual void						SetDisabled(bool isDisabled);

	// implement of Sexy::ScrollWidgetListener
	virtual void						ScrollTargetReached(ScrollWidget* scrollWidget) {}
	virtual void						ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}
	virtual void						ButtonDepress(int i_id);		// menu clicked

	virtual void						OnCreate(int i_id, const SexyString& text, MenuClickEvent callback);
	virtual void						ShowMenu();
	virtual void						HideMenu();
	PVZ2UIButton*				AddSubMenu(int i_id, const SexyString& text);
    PVZ2UIButton*               GetSubMenu(int i_id);
	Sexy::Widget*				GetPanel() { return m_pPanel; }
	int									GetMenuID() { return m_pMenu ? m_pMenu->mId : -1; }
protected:
	
protected:
	PVZ2UIButton*					m_pMenu;
	PVZ2UIScrollingWidget*	m_pScrollingWidget;
	Sexy::Widget*					m_pPanel;
	MenuClickEvent				m_menuClickedCallback;
};


#endif
