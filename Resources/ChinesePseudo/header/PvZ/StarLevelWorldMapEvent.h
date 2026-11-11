//
//  StarLevelWorldMapEvent.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 14-5-16.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StarLevelWorldMapEvent__
#define __PlantsVersusZombies2__StarLevelWorldMapEvent__

#include "WorldMapEventAlert.h"

class StarLevelWorldMapEvent : public WorldMapEventAlert
{
public:
    virtual void				OnMouseUp(const int i_mouseX, const int i_mouseY);
    
    StarLevelWorldMapEvent();
    
    ~StarLevelWorldMapEvent();

    void drawYetiLevelDialog(Sexy::Graphics *i_g);
    virtual void DrawFromMap(Graphics* i_g, WorldMapCamera* i_camera,int challengeIndex);
    
    
protected:
    int m_challengeIndex;
};


#endif /* defined(__PlantsVersusZombies2__StarLevelWorldMapEvent__) */
