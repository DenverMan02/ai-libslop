//
//  ActiveCenter.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.9.13.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _ActiveCenterTabBase_h_
#define _ActiveCenterTabBase_h_

#include "UIEditor/UIDialog.h"

class ActiveCenterTabBase
{
public:
	ActiveCenterTabBase(int tab_id, class UI::Dialog* pCenterDlg);
	virtual ~ActiveCenterTabBase();
    
	virtual void		OnButtonClicked(int i_id);
	virtual void		SetSelect(bool setting);
    virtual void        DrawBackground(class Sexy::Graphics* i_g);
    virtual void        DrawForeground(class Sexy::Graphics* i_g);
    
    virtual std::string GetTabContainerImageName() const { return ""; }
    virtual SexyString  GetGoToButtonTitle();
    
	virtual void		Update() {}

	class PVZ2UIButton*	GetTabBtn() const;
	int					GetTabID()  const { return m_tabID; }
    Sexy::Widget*		GetTabContent();

protected:
	int						m_tabID;
	class UI::Dialog*		m_pCenterDlg;
	class PVZ2UIButton*     m_pTabBtn;
	class UIWidgetImage*	m_pTabContainer;
};



#endif
