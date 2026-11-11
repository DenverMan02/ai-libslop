//
//  WorldMap_SummerCenterButton.hpp
//  PlantsVersusZombies2
//
//  Created by popcap on 7/26/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef WorldMap_SummerCenterButton_hpp
#define WorldMap_SummerCenterButton_hpp

#include "UIEasyButtonWidget.h"
#include "ActivityManager.h"

class WorldMap_ActivityHomeButton : public UIEasyButtonWidget
{
    
public:
    RT_CLASS_DEFINE(WorldMap_ActivityHomeButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_ActivityHomeButton();
    virtual ~WorldMap_ActivityHomeButton();
    
    void WaitForTutorialClick()
    {
        m_clicked = false;
    }
    bool WasClickedForTutorial()
    {
        return m_clicked;
    }
    void                    RequestData(ActivityTypeID i_typeId);
public:
    static bool CheckVisibility(bool i_init = false);
    static bool CheckDrawDollActivityTips();
    static bool CheckFirstRechargeActivityTips();
    
protected:
    bool CheckActivityTips();
    
    void Draw(Sexy::Graphics* i_g) override;
    void SetNotice(bool notice);
    
protected:
    void                onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void                onMsgErrorRequest(int erroId, const std::string& i_reqID);
    void                onNotifyStaticConfig(int result, const class S2C_StaticConfig* data);
    
private:
    void                OnKillChooseDialog(UIWidget* pButton);
    void                KillChooseDialog();
    void             CheckTutorialAndCancel();
    
    bool	m_clicked;
    bool			m_bRequested = false;
};

#endif /* WorldMap_SummerCenterButton_hpp */
