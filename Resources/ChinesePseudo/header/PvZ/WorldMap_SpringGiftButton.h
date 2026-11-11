//
//  WorldMap_ActivityLevelsButton.h
//  PlantsVersusZombies2
//
//  Created by Tak Zhang on 14-8-29.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_SpringGiftButton_h
#define PlantsVersusZombies2_WorldMap_SpringGiftButton_h

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"

class WorldMap_SpringGiftButton : public UIWidget
{
    
public:
	RT_CLASS_DEFINE(WorldMap_SpringGiftButton, UIWidget, RtClass);
    
	WorldMap_SpringGiftButton();
	virtual ~WorldMap_SpringGiftButton();
    
    virtual void onUpdate() override;
    virtual void SetVisible(bool i_visible);
    
    static bool s_bCanGet;
    static bool s_bActivated;
    static bool s_bAllGet;
    static bool s_bHasOpened;
    static void UpdateValid();

    
	// Public Interface (Inheritable)
    
	virtual void			Draw(Graphics* i_g) override;
	virtual void			OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseDown(const int i_mouseX, const int i_mouseY) override;
    virtual void			OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    virtual void            OnOK();
    
    void OnVerify2015NewYearCharge(bool i_result);
    
protected:
    
	// Protected Interface (Inheritable)   

    
private:
    
	// Private Interface (Core)
    
    virtual void SpringGiftInit();
    virtual bool isSpringGiftButtonVisible();
    virtual bool HasPlantLowerThanLevel3();
	virtual void updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
   
};

#endif
