//
//  PurchaseConfirmUI.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/5/28.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PurchaseConfirmUI__
#define __PlantsVersusZombies2__PurchaseConfirmUI__

#include "Widget.h"
#include "RtObject.h"
#include "RtDelegate.h"
#include "GameButton.h"
#include "Core.h"
#include "MagentoService.h"

class PurchaseConfirmUI : public Sexy::Widget, public ButtonListener
{
public:
	typedef Sexy::Delegate1<MagentoProductProps*> ConfirmCallback;
public:
	static PurchaseConfirmUI*		ShowUI(MagentoProductPropsPtr pProductProps, ConfirmCallback fun);
public:
	PurchaseConfirmUI(MagentoProductPropsPtr pProductProps);
	virtual ~PurchaseConfirmUI();

	//virtual void Update();
	virtual void				Draw(Graphics* i_g);
	virtual void				ButtonDepress(int i_id);

	void							SetConfirmCallback(ConfirmCallback fun);
	void							Close();
protected:
	void							InitView();
protected:
	MagentoProductPropsPtr				m_pProductProps;
	Sexy::Rect				m_rectDialog;
	SexyString				m_strPrice;
	SexyString				m_strItem;
	ConfirmCallback	m_confirmCallback;
};

#endif /* defined(__PlantsVersusZombies2__PurchaseConfirmUI__) */
