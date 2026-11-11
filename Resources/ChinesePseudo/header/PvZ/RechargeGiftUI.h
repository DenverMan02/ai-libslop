//
//  RechargeGiftUI.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/5/14.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__RechargeGiftUI__
#define __PlantsVersusZombies2__RechargeGiftUI__

#include "Widget.h"
#include "RtObject.h"
#include "GameButton.h"
#include "Core.h"
#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "MagentoService.h"

#define RECHARGEGIFT_MAXTIMES 1

class RechargePlantItem : public PVZ2UIButton
{
public:
	enum PlantState
	{
		PlantState_Invalid,
		PlantState_Unlock,
		PlantState_Level1,
		PlantState_Level2,
		PlantState_Avatar,
		PlantState_Max,
	};
public:
	RechargePlantItem(MagentoProductPropsPtr i_props, int i_id, Sexy::ButtonListener* i_listener);
	virtual ~RechargePlantItem();

	//virtual void				Draw(Graphics* i_g);
	void							DrawPreview(Graphics* i_g, int iX, int iY, bool isGemsGet);
	void							DrawIcon(Graphics* i_g, int iX, int iY);
	int							GetWidth();
	int							GetHeight();
	void							Refresh();
	void							SetSelect(bool bSelect);
	bool							LevelUp();
	PlantState				GetPlantState();
    std::string		GetItemName();

	static bool				LevelUp(MagentoProductPropsPtr pProp);
	static PlantState	GetPlantState(const std::string& plantname);
public:
	MagentoProductPropsPtr	m_pProp;
	bool											m_bSelected;
	bool											m_bUnLock;
	float											m_fProgress;
	Sexy::Image*							m_pImagePlant;
	Sexy::Image*							m_pImagePlantAvatar;
	Sexy::Image*							m_pImagePlantTag;
};

class RechargeGiftUI : public Sexy::Widget, public ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	enum ViewType
	{
		View_Recharge,
		View_Get,
	};
public:
	RechargeGiftUI(const std::string& name = "");
	virtual ~RechargeGiftUI();

	virtual void							Update();
	virtual void							DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	virtual void							Draw(Graphics* i_g);
	virtual void							ButtonDepress(int i_id);

	// implement of Sexy::ScrollWidgetListener
	virtual void							ScrollTargetReached(ScrollWidget* scrollWidget) {}
	virtual void							ScrollTargetInterrupted(ScrollWidget* scrollWidget) {}

	RechargePlantItem*			GetSelectedPlantItem();
	void										RechargeSuccessed();
	void										OnPurchaseDialogClosed();
	void										SetPurchaseSuccess(bool bSuccess = true);

	static bool							IsCanRecharge();
private:
	void										InitView();
	void										ShowPlantItems(Sexy::Widget* pPanel);
	void										SelectPlant(int iPlant);

private:
	class RechargeGiftConfig*		m_pConfigData;
	Sexy::Rect									m_rectDialog;
	Sexy::Rect									m_rectScoll;
	Sexy::Image*								m_pImageTitle;
	Sexy::Image*								m_pImageDesc;
	SexyString									m_strDesc;
	SexyString									m_strTime;
	typedef std::map<int, RechargePlantItem*>	MapPlantItems;
	MapPlantItems							m_mapPlantItems;
	int												m_iSelectedPlantItem;
	PVZ2UIButton*							m_pBtnBuy;
	ViewType									m_viewType;
	bool												m_bPurchaseSuccess;
};



#endif /* defined(__PlantsVersusZombies2__RechargeGiftUI__) */
