//
//  TimeCDWorldMapEvent.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-11-6.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_TimeCDWorldMapEvent_h
#define PlantsVersusZombies2_TimeCDWorldMapEvent_h

#include "WorldMapEventAlert.h"

class TimeCDWorldMapEvent : public WorldMapEventAlert
{
public:
    
    enum TimeCDWorldMapEventTipType
    {
        TipType_NONE,
        TipType_CDTIME,
        TipType_BT_CDTIME,
        TipType_UNLOCKED,
    };
    
    TimeCDWorldMapEvent() : m_TipType(TipType_NONE){ }
    
    ~TimeCDWorldMapEvent() { }

    void DrawFromMap(Graphics* i_g, WorldMapCamera* i_camera = NULL,int index=-1) override;
    
    bool IsMouseOver(const int i_mouseX, const int i_mouseY) override;
    
    void UpdataDesc(const std::string& strDesc) { m_strDesc = strDesc; }
    
    void SetTipType(TimeCDWorldMapEventTipType ty) { m_TipType = ty; }
    
    TimeCDWorldMapEventTipType GetTipType() { return m_TipType; }
    
private:
    
    std::string m_strDesc;
    
    TimeCDWorldMapEventTipType m_TipType;
};

#endif
