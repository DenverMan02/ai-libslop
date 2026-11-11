//
//  PVPLab.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2016.1.12
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _PVPLab_h_
#define _PVPLab_h_

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVPDatas.h"

class PVPLabDlg : public UISingletonDialog<PVPLabDlg>, public Sexy::ScrollWidgetListener
{
public:
	PVPLabDlg();
	virtual ~PVPLabDlg();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "PVPLab"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;
	virtual void                DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
    // ScrollWidgetListener
    virtual void                ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void                ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    virtual void                ScrollTouchMotion(const Sexy::Touch& touch) override;

protected:
    class PVPLabItem*           CreateLabItem(int i_btn, const std::string& str_name, int i_type);
    
    void                        onPVPLabRefresh();
private:
    class UIPage*               m_pPage;
    class UIScrollControl*      m_pScroll;
    class PVPCurrencyBar*       m_pCurrencyBar;
    std::vector<class PVPLabItem*>  m_labList;
public:
    static PVPLabItemType       s_AutoOpenType;
};

//------------------------------------------------------
class PVPLabItem : public PVZ2UIButton
{
public:
    friend class PVPLabDlg;
    PVPLabItem(Sexy::Image* pImage);
    ~PVPLabItem();
    virtual void    Draw(Sexy::Graphics* i_g);
    //virtual void    Update();
    
protected:
    Sexy::Image*    m_pLabImage;
    float           m_fScale;
    int             m_type;
};


#endif
