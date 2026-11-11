//
//  ArenaAwakenWidget.h
//  PlantsVersusZombies2
//
//  Created by Jiang, Lichun on 15-11-27.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ArenaAwakenWidget__
#define __PlantsVersusZombies2__ArenaAwakenWidget__

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

enum AwakenButtons
{
    AWAKENBUTTON_Close = -1,
    AWAKENBUTTON_SwitchToPlants,
    AWAKENBUTTON_SwitchToZombies,
};

class AwakenPage : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    AwakenPage(class ArenaAwakenWidget* i_parent, ObjectTypeDescriptorPtr i_objectType, const Rect i_rect, bool bShowDesc = true);
    virtual ~AwakenPage();
    
    virtual void ButtonPress(int i_id);
    virtual void ButtonDepress(int i_id);
    virtual void ScrollTargetReached(Sexy::ScrollWidget* i_scrollWidget) {}
    virtual void ScrollTargetInterrupted(Sexy::ScrollWidget* i_scrollWidget) {}
    
    ObjectTypeDescriptorPtr GetObjectType() const { return m_objectType; }
    
protected:
    void onItemPurchasedFromStore(MagentoProductProps* i_props);
    
    class ArenaAwakenWidget* m_parent;
    
private:
    ObjectTypeDescriptorPtr m_objectType;
    MagentoProductPropsPtr m_purchaseProps;
    class PVZ2UIButton* m_purchaseButton;
    
    void onUseGemFinish(const bool& isSuccess);
};

class AwakenObjectButton : public Sexy::ButtonWidget
{
public:
    AwakenObjectButton(int i_id, ButtonListener* i_listener, ObjectTypeDescriptorPtr i_objectType);
    
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

class AwakenObjectChooser : public Sexy::Widget, public Sexy::ButtonListener
{
public:
    AwakenObjectChooser(ObjectTypeDescriptorPtr i_objectType, class ArenaAwakenWidget* i_awakenWidget);
    virtual ~AwakenObjectChooser();
    
    virtual void Initialize(int i_x, int i_y, int i_width, int i_height);
    virtual void ButtonDepress(int i_id);
    
    int GetScrollOffset() const;
    
private:
    
    ObjectTypeDescriptorPtr m_selectedObject;
    std::vector<AwakenObjectButton*> m_buttons;
    class ArenaAwakenWidget* m_awakenWidget;
};

class ArenaAwakenWidget : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::ScrollWidgetListener
{
public:
    ArenaAwakenWidget(ObjectTypeDescriptorPtr i_objectType);
    virtual ~ArenaAwakenWidget();
    
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
    
    class PVZ2UIScrollingWidget* m_scrollingWidget;
    AwakenObjectChooser* m_objectChooser;
    
    Image* m_scrollerFades[2];
    
    ObjectTypeDescriptorPtr m_switchToObject;
};

#endif /* defined(__PlantsVersusZombies2__ArenaAwakenWidget__) */
