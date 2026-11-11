//
//  SeedPacket_Friend.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-7-22.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SeedPacket_Friend__
#define __PlantsVersusZombies2__SeedPacket_Friend__

#include "SeedPacket.h"

class SeedPacket_Friend : public SeedPacket
{
public:
	RT_CLASS_DEFINE(SeedPacket_Friend, SeedPacket, RtClass);
    
    void FriendSetAffordable()
    {
        setAffordable(true);
    }
    
    void SetFriendSeedMotion(const Sexy::SexyVector2 &i_velocity,
                             const Sexy::SexyVector2 &i_acceleration,
                             float i_max_y);
    
private:
    // Motion_Newtonian
	SexyVector2 	m_newton_velocity;
	SexyVector2 	m_newton_acceleration;
    
    float           m_newton_max_y;
    
    pvztime_t       m_motionStartTime;
    pvztime_t       m_motionStartFlash;
    pvztime_t       m_motionEndTime;
    
protected:
    
	// Protected Interface (Inheritable)
	
    virtual void onUpdate() override;
    
    void updateMotion();
};

#endif /* defined(__PlantsVersusZombies2__SeedPacket_Friend__) */
