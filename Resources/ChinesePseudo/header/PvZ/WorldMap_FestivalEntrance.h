//
//  WorldMap_FestivalEntrance.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 14-1-8.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__WorldMap_FestivalEntrance__
#define __PlantsVersusZombies2__WorldMap_FestivalEntrance__

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "PVZTypes.h"
#include "GameEventMgr.h"
#include "Effect_BouncingArrow.h"
#include "LawnAppEnums.h"

class WorldMap_FestivalEntrance : public UIWidget
{
	
public:
	RT_CLASS_DEFINE(WorldMap_FestivalEntrance, UIWidget, RtClass);
    
	WorldMap_FestivalEntrance();
	virtual ~WorldMap_FestivalEntrance();
    
    void SetGameMode(FestivalGameMode i_mode);
    void SetRemainTime(int i_time);
    uint64 GetLocalSeconds();
    void RefreshState();
    
	// Public Interface (Inheritable)
	
	virtual void			Draw(Graphics* i_g) override;
    
	virtual void			onUpdate() override;
    virtual void			OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	virtual void			OnMouseMove(const int i_mouseX, const int i_mouseY) override;
    
    virtual bool			IsMouseOver(const int i_mouseX, const int i_mouseY) override;

	void 					DisplayBouncingArrow(float i_duration);
    
protected:
    
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing)
	OVERRIDE_STATE_UPDATE(WidgetState,  Ready)
    
	// Protected Interface (Inheritable)
    
	virtual void			initLoadingResourcesGroupList() override;
    
	// Protected Members (not serialized)
	
private:
    
	// Private Interface
    
    void                    updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed);
    
private:    
    int    							m_nButtonIndex;
    RtWeakPtr<Effect_BouncingArrow> m_bouncingArrow;
    float 							m_bouncingArrowEndTime;
    FestivalGameMode m_mode;
    
    Image* m_imgBtn;
    Image* m_imgBtnDown;
    Image* m_imgTips;
};

#endif /* defined(__PlantsVersusZombies2__WorldMap_FestivalEntrance__) */
