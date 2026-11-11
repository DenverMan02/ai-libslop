//
//  ShovelUI.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 5/23/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//
//  UI for the shovel tool.

#ifndef __SHOVELUI_H__
#define __SHOVELUI_H__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "GameEventMgr.h"
#include "PVZTypes.h"

class ShovelUI : public UIWidget
{
public:
	RT_CLASS_DEFINE(ShovelUI, UIWidget, RtClass);	
	
	ShovelUI();
	virtual ~ShovelUI();
	
	// Public Interface (Inheritable)
	
	virtual void	Draw(Graphics* i_g) override;
	virtual bool	OnTouch(const Sexy::Touch& i_touch) override;

	inline void		SetIsFlashing(bool i_isFlashing);
	inline bool		IsFlashing();

protected:
	
	// Protected Interface (Inheritable)

	OVERRIDE_STATE_ONEXIT(WidgetState, Loading);
	OVERRIDE_STATE_ONENTER(WidgetState, Pressed);
	OVERRIDE_STATE_ONEXIT(WidgetState, Pressed);
	
	virtual void	onCursorDestroyed(class BaseCursor* i_cursor);
	void 			onGameplayEnded();
	virtual void	onUpdate() override;

	virtual void	initLoadingResourcesGroupList() override;
	virtual void	registerForEvents() override;
	
private:	
	
	// Private Interface
	
	// Private Members (serialized)
	bool					m_isFlashing;
	bool 					m_levelEnded;
	
	// Private Members (not serialized)
};

inline void ShovelUI::SetIsFlashing(bool i_isFlashing)
{
	m_isFlashing = i_isFlashing;
}

inline bool ShovelUI::IsFlashing()
{
	return m_isFlashing;
}

#endif //__SHOVELUI_H__
