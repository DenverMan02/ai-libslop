//
//  Plant_PumpkinWitch.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/10/19.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_PumpkinWitch__
#define __PlantsVersusZombies2__Plant_PumpkinWitch__

#include <stdio.h>
#include "PlantFramework.h"
#include "PopAnimRig.h"

class PlantPumpkinWitch : public PlantFramework
{
public:
    enum PumpkinWitch_State
    {
        PUMPKINSTATE_PREPARING = STATE_FRAMEWORK_BEGIN,
        PUMPKINSTATE_IDLE,  
        PUMPKINSTATE_ATTACK,                      // pumpking is attacking.
        PUMPKINSTATE_SLEEPING,                     // pumpking is resting.
        PUMPKINSTATE_RECOVER,                      // pumpking is ready,
        PUMPKINSTATE_PLANTFOOD,                    // in plantfood state.
        PUMPKINSTATE_PLANTFOOD_SLEEPING,
        PUMPKINSTATE_PLANTFOOD_RECOVER,
    };
    
    
    RT_CLASS_DEFINE(PlantPumpkinWitch, PlantFramework, RtClass);
    
    virtual void    Initialize() override;
    virtual void	UpdateActions() override;
    virtual bool	CanApplyPlantfood() override;
    virtual void	ApplyPlantfood() override;
    virtual void    UpdatePlantfood() override;
    virtual void    CancelPlantfood() override;
    virtual bool    FindTargetAndFire(PlantWeapon i_plantWeapon) override;
    virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    virtual bool	OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    virtual void    PlayAttackAnimation() override;
    virtual void    DoSpecial(int i_extraParam) override;
    
    void            onAnimStoppedCallback(const std::string &i_animLabel) override;
    
protected:
    virtual bool    CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    void            LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
    ZombiePtr       FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;
    ZombiePtr       FindPlantFoodTargetZombie();
private:
    void            setState(uint i_plantState);
    
//    Zombie*         FindTarget(int i_row, PlantWeapon i_plantWeapon);
    Projectile*     normalFire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon);
    
    
    bool			isAnimDone();
    
    pvztime_t       m_prepareTime;
    std::vector<ZombiePtr> m_hitZombies;
    int             m_plantFoodNum;
};

#endif /* defined(__PlantsVersusZombies2__Plant_PumpkinWitch__) */
