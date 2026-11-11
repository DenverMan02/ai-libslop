//
//  ShipReconstructionUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-7-13.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ShipReconstructionUI__
#define __PlantsVersusZombies2__ShipReconstructionUI__

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "PrimeTextWidget.h"
#include "LawnAppEnums.h"
#include "PlayerInfo.h"

class ShipReconstructionUI : public Sexy::Widget, Sexy::ButtonListener
{
public:
    
	ShipReconstructionUI();
	virtual ~ShipReconstructionUI();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    
    virtual void    ButtonDepress(int i_id);

private:
    
    void            RefreshView();
    
    void            onAddComponentDialogOK();
    void            onAddCoinDialogOK();
    void            onAddDialogCancel();
    
private:
    
    Widget*                             m_contentWidget;
    Sexy::Rect                          m_rectDialog;
    eReconstructionType                 m_ReconstructionType;
    std::vector<class PVZ2UIButton*>	m_tabButtons;
    
    class PVZ2UIButton*                 addComponentButton;
    class PVZ2UIButton*                 addCoinButton;
    class PVZ2UIButton*                 transformButton;
    
    float                               m_ItemWidth;
    bool                                m_IsTopLevel;
    
    std::string                         m_curWorldName;
    std::string                         m_curComponentName;
    
    int                                 m_curLevel;
    int                                 m_needComponentCount;
    int                                 m_needCoinCount;
    
    Sexy::Rect                          m_componentRect;
    Sexy::Rect                          m_coinRect;
    
    bool                                m_componentColor;
    bool                                m_coinColor;
};





class ReconstructionItemWidget : public Widget
{
public:
	ReconstructionItemWidget(eReconstructionType i_ReconstructionType,int i_nLevel);
	virtual ~ReconstructionItemWidget();
    
	virtual void Resize(int theX, int theY, int theWidth, int theHeight);
	virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    
private:
    
    eReconstructionType m_ReconstructionType;
    int                 m_nLevel;
};




#endif /* defined(__PlantsVersusZombies2__ShipReconstructionUI__) */
