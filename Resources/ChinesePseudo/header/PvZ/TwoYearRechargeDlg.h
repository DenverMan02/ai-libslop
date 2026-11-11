//
//  ActiveCenter.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.9.25.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef _TwoYearRechargeDlg_h_
#define _TwoYearRechargeDlg_h_

#include "UIEditor/UISingletonDialog.h"
#include "PVZ2UIButton.h"


class TwoYearRechargeDlg : public UISingletonDialog<TwoYearRechargeDlg>
{
public:
	TwoYearRechargeDlg();
	virtual ~TwoYearRechargeDlg();
	virtual bool							OnCreate();
	virtual std::string				GetLayoutName() { return "TwoYearRecharge"; }
	virtual void							Draw(Sexy::Graphics* i_g);
    virtual void							DrawAll(Sexy::ModalFlags* theFlags, Sexy::Graphics* g);
	virtual void							Update();

	// ButtonListener
	virtual void							ButtonDepress(int i_id);


protected:
    class ActiveCenterTabRecharge*      m_pRechargeTab;
};

#endif
