//
//  WorldMap_BackButton.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 10/1/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WorldMap_BackButton_h
#define PlantsVersusZombies2_WorldMap_BackButton_h

#include "RtObject.h"
#include "TimeMgr.h"
#include "UIButtonWidget.h"
#include "core.h"

namespace Sexy {
    class Graphics;
}  // namespace Sexy

namespace Message
{
    void NotifyBackFromRift();
}

enum WMBackBtnState
{
    PVZ_BEGIN_ENUM(WMBackBtnState_),
    WMBBS_Idle,
    WMBBS_FadingIn,
    WMBBS_FadingOut,
    WMBBS_Transitioning,
    PVZ_END_ENUM(WMBackBtnState_),
};

enum WMBackBtnTypeState
{
    PVZ_BEGIN_ENUM(WMBackBtnTypeState_),
    WMBTS_Init,
    WMBTS_WorldMap,
    WMBTS_UniverseMap,
    WMBTS_ZenGarden,
    PVZ_END_ENUM(WMBackBtnTypeState_),
};

class WorldMap_BackButton : public UIButtonWidget
{
    
public:
    RT_CLASS_DEFINE(WorldMap_BackButton, UIButtonWidget, RtClass);
    
    WorldMap_BackButton();
    virtual ~WorldMap_BackButton();
    
    // Public Interface (Inheritable)
    
    virtual bool		OnBackButtonPressed();
    
    void				SetMetricsUILocation(std::string& i_location) { m_metricsUILocation = i_location; }
    void				FadeIn();
    void				FadeOut();
    
protected:
    
    // Protected Interface (Inheritable)
    
    void				initLoadingResourcesGroupList() override;
    void				onUpdate() override;
    
private:
    
    // Private Interface (Core)
    
    void				performButtonAction() override;
    void				goToMainMenu();
    void				goToUniverseMap();
    
    WMBackBtnState		m_state;
    WMBackBtnTypeState	m_typeState;
    pvztime_t			m_fadeStartTime;
    std::string			m_metricsUILocation;
};

#endif
