//
//  PumpkinWitchProjectile.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/10/20.
//  Copyright (c) 2015年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PumpkinWitchProjectile__
#define __PlantsVersusZombies2__PumpkinWitchProjectile__

#include "Projectile.h"

class PumpkinWitchProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PumpkinWitchProjectile, Projectile, RtClass);
    
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    virtual void onUpdate(pvztime_t i_dt) override;
    virtual void onProjectileInitialized() override;
    
    void setPlantFoodAttack(bool i_isPlantfoodAttack);
    void setAvatarAttack(bool i_isAvatarAttack);
protected:
    
private:
    void updateAnimLayerVisibility(const std::string& i_layerName);
    
    void SpawnPumpkinZombie(class Zombie* i_ancestorZombie);
    
    bool m_isPlantfoodAttack;
    bool m_isAvatarAttack;
    pvztime_t m_attackStartTime;
    pvztime_t m_attackEndTime;
    
};


#endif /* defined(__PlantsVersusZombies2__PumpkinWitchProjectile__) */
