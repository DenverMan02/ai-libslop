//
//  UIPropertySheet.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.7.3
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _UIPropertySheet_h_
#define _UIPropertySheet_h_

#include "Widget.h"
#include "PVZ2UIButton.h"
#include "EditListener.h"

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
class UIProperty : public Sexy::Widget
{
	friend class UIPropertySheet;
public:
	UIProperty();
	virtual ~UIProperty();
	virtual void			OnCreate(int theId, const std::string& name, const std::string& value, Sexy::EditListener* pListener);
	virtual void			Draw(Sexy::Graphics* i_g);
	virtual void			Resize(int i_x, int i_y, int i_w, int i_h);

public:
	std::string			GetName();
	int						GetID();
	void						SetValue(const std::string& value);
	std::string			GetValue();
	void						SetReadOnly(bool setting);
	bool						IsReadOnly() { return m_bReadOnly; }
protected:
	class EditWidget*					m_pEditWidget;
	class UIWidgetText*				m_pTextWidget;
	class UIWidgetText*				m_pReadOnlyWidget;
	bool											m_bReadOnly;
};

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
class UIPropertySheet : public Sexy::Widget, public Sexy::ScrollWidgetListener, public Sexy::ButtonListener, public Sexy::EditListener
{
public:
	typedef Sexy::Delegate1<UIProperty*> PropertyChangedEvent;
public:
	UIPropertySheet(PropertyChangedEvent callback);
	~UIPropertySheet();

	virtual void						Draw(Sexy::Graphics* i_g);
	virtual void						Resize(int i_x, int i_y, int i_w, int i_h);

	// ButtonListener
	virtual void						ButtonDepress(int i_id);

	// implement of Sexy::ScrollWidgetListener
	virtual void						ScrollTargetReached(ScrollWidget* scrollWidget) {}
	virtual void						ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}

	// EditListener
	virtual void						EditWidgetText(int theId, const SexyString& theString);
	virtual bool						AllowKey(int theId, Sexy::KeyCode theKey) { return true; }
	virtual bool						AllowChar(int theId, SexyChar theChar) { return true; }
	virtual bool						AllowText(int theId, const SexyString& theText) { return true; }

public:
	void									Layout();
	UIProperty*						AddProperty(int i_id, const std::string& name, const std::string& value);
	UIProperty*						GetProperty(const std::string& name);
	UIProperty*						GetProperty(int i_id);
	std::string						GetPropertyValue(const std::string& name);
	void									SetPropertyValue(const std::string& name, const std::string& value);

	void									ClearAllProperties();
	std::vector<UIProperty*>& GetProperties() { return m_Properties; }

protected:
	std::vector<UIProperty*> m_Properties;
	PVZ2UIScrollingWidget*	m_pScrollingWidget;
	Sexy::Widget*					m_pPanel;
	PVZ2UIButton*					m_pBtnClose;
	PVZ2UIButton*					m_pBtnOK;
	PropertyChangedEvent	m_propertyChangedCallback;
};




#endif
