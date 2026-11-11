//
//  Plant_Zoomshroom.h
//  PlantsVersusZombies2
//
//  Created by Albert Lai on 10/29/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Zoomshroom_h
#define PlantsVersusZombies2_Plant_Zoomshroom_h

#include <string>

#include "Plant.h"
#include "PlantFramework.h"
#include "PlatformAutodetect.h"
#include "RtObject.h"
#include "TimeMgr.h"
#include "ZombieEnums.h"

class Zombie;

enum Zoomshroom_State
{
	ZOOMSHROOMSTATE_IDLE = STATE_FRAMEWORK_BEGIN, // bobbing around, ready to spew the goods
    ZOOMSHROOMSTATE_RECOVER,                      // recovering from teleport
};

class PlantZoomshroom : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantZoomshroom, PlantFramework, RtClass);
	
    virtual void    Initialize() override;
    virtual void	UpdateActions() override;
    virtual CollisionTypeFlags GetCollisionFlags(PlantWeapon i_plantWeapon) override;
    virtual bool	CanApplyPlantfood() override;
    virtual void	ApplyPlantfood() override;
    
    virtual bool    IsInvincible() override;
	virtual bool    HasShadow() override;
	
private:
	void			calculateRemainingLifeAndUpdateLayers();
	void			playEffectCenteredOnPlant(std::string i_animationID);
	void			playKnockbackEffect();
	void			playExpirationEffect();
    void            tossZombie(Zombie* i_zombie);
	
	void            setState(uint i_plantState);
    
	pvztime_t m_startTime;
};
#endif
