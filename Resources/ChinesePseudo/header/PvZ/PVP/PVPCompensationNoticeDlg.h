//
//  PVPCompensationNoticeDlg.h
//  PlantsVersusZombies2
//
//  Created by ling, zhaojun on 16/1/13.
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef _PVPCompensationNoticeDlg_h_
#define _PVPCompensationNoticeDlg_h_

#include "UISingletonDialog.h"

class PVPCompensationNoticeDlgCaller
{
public:
    static PVPCompensationNoticeDlgCaller* getInstance();
    static void destroy();
    void   onPVPCompensationReward(int i_resourceNum,int i_coinNum,int i_medalNum);
    
    void   requestService(int type);
    
protected:
    static PVPCompensationNoticeDlgCaller* s_pInstance;
};

class PVPCompensationNoticeDlg : public UISingletonDialog<PVPCompensationNoticeDlg>
{
public:
	PVPCompensationNoticeDlg();
	virtual ~PVPCompensationNoticeDlg();
	virtual bool					OnCreate() override ;
	virtual std::string				GetLayoutName() override { return "PvpResNoticeDlg"; }
    virtual void                    Draw(Sexy::Graphics* i_g) override;
    virtual void                    DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g) override;
	// ButtonListener
	virtual void                    ButtonDepress(int i_id) override;
    
    void setInfos(int i_resourceNum,int i_coinNum,int i_medalNum);
    

private:
};


#endif
