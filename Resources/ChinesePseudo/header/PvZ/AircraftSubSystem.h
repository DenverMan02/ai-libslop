//
//  AircraftSubSystem.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 15-9-8.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__AircraftSubSystem__
#define __PlantsVersusZombies2__AircraftSubSystem__

#include "GameSubSystem.h"
#include "RtReflectionDelegate.h"
#include "BossAircraft.h"

class AircraftSubSystem : public GameSubSystem
{
public:
    RT_CLASS_DEFINE(AircraftSubSystem, GameSubSystem, RtClass);
    
    virtual void Update() override;
    
    void LaunchAircraft(const SexyVector3& i_pos,
                        int i_index,
                        int i_up_row,
                        int i_down_row,
                        float craftHitpoint,
                        float craftDamage,
                        float lineDamage);
    
protected:
	virtual void registerForEvents() override;
    
    void onAircraftDownMoveDone(BoardEntity * target);
    void onAircraftUpMoveDone(BoardEntity * target);
    
private:
    
    
};

#endif /* defined(__PlantsVersusZombies2__AircraftSubSystem__) */
