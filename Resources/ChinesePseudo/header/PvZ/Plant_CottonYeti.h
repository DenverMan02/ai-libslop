//
//  Plant_CottonYeti.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/11/9.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef Plant_CottonYeti_h
#define Plant_CottonYeti_h

#include <stdio.h>
#include "PlantFramework.h"
#include "PopAnimRig.h"

class PlantCottonYeti : public PlantFramework
{
public:
    enum CottonYeti_State
    {
        COTTONSTATE_PREPARING = STATE_FRAMEWORK_BEGIN,
        COTTONSTATE_IDLE,
        COTTONSTATE_ATTACK,                       // cotton is attacking.
        COTTONSTATE_SLEEPING,                     // cotton is resting.
        COTTONSTATE_RECOVER,                      // cotton is ready,
        COTTONSTATE_PLANTFOOD,                    // in plantfood state.
        COTTONSTATE_PLANTFOOD_SLEEPING,
        COTTONSTATE_PLANTFOOD_RECOVER,
    };
    
    
    RT_CLASS_DEFINE(PlantCottonYeti, PlantFramework, RtClass);
    
    virtual void    Initialize() override;
    virtual void	UpdateActions() override;
    virtual bool	CanApplyPlantfood() override;
    virtual void	ApplyPlantfood() override;
    virtual void    UpdatePlantfood() override;
    virtual void    CancelPlantfood() override;
    virtual bool    FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    virtual void    DoSpecial(int i_extraParam) override;
    
    
protected:
    virtual bool    CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    void            LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
private:
    void            setState(uint i_plantState);
    
    Projectile*     normalFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
    
    
    bool			isAnimDone();
    
    pvztime_t       m_prepareTime = PVZ_EOT();
};

#endif /* Plant_CottonYeti_hpp */
