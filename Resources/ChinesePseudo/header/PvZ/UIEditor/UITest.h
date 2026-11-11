//
//  UITest.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 17/5/15.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef _UITest_h_
#define _UITest_h_

#include "UISingletonDialog.h"

class UITest : public UISingletonDialog<UITest>
{
public:
	UITest();
	virtual ~UITest();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "uitest"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

private:
};


#endif
