//
//  UIAuthenticationDialog.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 17/5/15.
//  Copyright (c) 2017 PopCap Games. All rights reserved.
//

#ifndef _UIAuthenticationDialog_h_
#define _UIAuthenticationDialog_h_

#include "UISingletonDialog.h"

class UIAuthenticationDialog : public UISingletonDialog<UIAuthenticationDialog>
{
public:
	

	UIAuthenticationDialog();
	virtual ~UIAuthenticationDialog();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "AuthenticationDialog"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;
	void setDialogTxt(const SexyString& str);
private:
	UIWidgetText* m_pText;
};


#endif
