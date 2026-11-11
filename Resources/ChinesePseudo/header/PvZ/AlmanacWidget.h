//
//  AlmanacWidget.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 10/10/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__AlmanacWidget__
#define __PlantsVersusZombies2__AlmanacWidget__

#include "Widget.h"
#include "ButtonWidget.h"
#include "PVZTypes.h"
#include "PopAnimRigHelper.h"
#include "PlantPropertySheet.h"
#include "GameNotify.h"
#include "GameFeatureType.h"
#include "MagentoService.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"

class StretchableNewLawnButton;

enum AlmanacButtons
{
	ALMANACBUTTON_Close = -1,
	ALMANACBUTTON_SwitchToPlants,
	ALMANACBUTTON_SwitchToZombies,
	ALMANACBUTTON_SwitchToUpgrades,
	
	ALMANACPLANTBUTTON_BuyPlant,
	ALMANACPLANTBUTTON_ViewOnMap,
	
	ALMANACUPGRADEBUTTON_BuyUpgrade,
	ALMANACUPGRADEBUTTON_ViewOnMap,
};

class AlmanacPage : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	AlmanacPage(class AlmanacWidget* i_parent, ObjectTypeDescriptorPtr i_objectType, const Rect i_rect, bool bShowDesc = true);
	virtual ~AlmanacPage();

	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
	virtual void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) {}
	virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) {}

	ObjectTypeDescriptorPtr GetObjectType() const { return m_objectType; }

protected:
	void onItemPurchasedFromStore(MagentoProductProps* i_props);

	class AlmanacWidget* m_parent;
	
private:
	ObjectTypeDescriptorPtr m_objectType;
	MagentoProductPropsPtr m_purchaseProps;
	class PVZ2UIButton* m_purchaseButton;
    
    void onUseGemFinish(const bool& isSuccess);
};

class UpgradesAlmanacButton : public Widget, public ButtonListener
{
public:
	UpgradesAlmanacButton(ObjectTypeDescriptorPtr i_gameFeatureType, MagentoProductProps* i_purchaseProps);
	virtual ~UpgradesAlmanacButton();

	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
	
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);

	GameFeatureType* GetFeatureType() const { return m_featureType; }

protected:
	void onItemPurchasedFromStore(MagentoProductProps* i_props);

private:
	class PVZ2UIAlmanacUpgradeDisplayer* m_upgradeDisplayer;
	GameFeatureType* m_featureType;
	MagentoProductProps* m_purchaseProps;
	class PVZ2UIButton* m_purchaseButton;
};

class UpgradesAlmanacPage : public AlmanacPage
{
public:
	UpgradesAlmanacPage(class AlmanacWidget* i_parent, ObjectTypeDescriptorPtr i_objectType, const Rect i_rect);
	virtual ~UpgradesAlmanacPage();

	int GetScrollOffset() const;

private:
	void onItemPurchasedFromStore(GameEventNotification& i_notification);

	std::vector<UpgradesAlmanacButton*> m_upgradeButtons;
};

class AlmanacObjectButton : public Sexy::ButtonWidget
{
public:
	AlmanacObjectButton(int i_id, ButtonListener* i_listener, ObjectTypeDescriptorPtr i_objectType);

	virtual void Draw(Sexy::Graphics* i_g);
	
	void RefreshUnlockStatus();
	
	bool GetIsVisible();

	ObjectTypeDescriptorPtr m_objectType;
	bool m_selected;
	
private:
	void drawPlant(Graphics* i_g);
	void drawZombie(Graphics* i_g);

	bool m_visible;
	bool m_purchaseable;
	bool m_unlocked;
};

class AlmanacObjectChooser : public Sexy::Widget, public Sexy::ButtonListener
{
public:
	AlmanacObjectChooser(ObjectTypeDescriptorPtr i_objectType, class AlmanacWidget* i_almanacWidget);
	virtual ~AlmanacObjectChooser();

	virtual void Initialize(int i_x, int i_y, int i_width, int i_height);
	virtual void ButtonDepress(int i_id);
	
	int GetScrollOffset() const;

private:

	ObjectTypeDescriptorPtr m_selectedObject;
	std::vector<AlmanacObjectButton*> m_buttons;
	class AlmanacWidget* m_almanacWidget;
};

class AlmanacWidget : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
	AlmanacWidget(ObjectTypeDescriptorPtr i_objectType);
	virtual ~AlmanacWidget();

	void SetupAlmanac(ObjectTypeDescriptorPtr i_objectType);
	
	void SetNeedsRefresh(ObjectTypeDescriptorPtr i_objectType);
	
	virtual void Update();
	virtual void DrawAll(Sexy::ModalFlags* theFlags, Graphics* g);

	virtual void ButtonPress(int i_id);
	virtual void ButtonDepress(int i_id);
	virtual void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget);
	virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget);

	void SetAlmanacPage(ObjectTypeDescriptorPtr i_objectType);

private:

	void resetPages();

	AlmanacPage* m_almanacPage;
	AlmanacObjectChooser* m_objectChooser;
	class PVZ2UIScrollingWidget* m_scrollingWidget;
	
	Image* m_scrollerFades[2];

	ObjectTypeDescriptorPtr m_switchToObject;
};

#endif /* defined(__PlantsVersusZombies2__AlmanacWidget__) */
