//
//  Plant_Agave.h
//  PlantsVersusZombies2
//
//  Created by Zhao, Bokun on 15/12/2.
//  Copyright © 2015年 PopCap Games. All rights reserved.
//

#ifndef Plant_Agave_h
#define Plant_Agave_h

#include "PlantFramework.h"
#include "Zombie.h"

enum AgaveState
{
    AGAVESTATE_PLANTING = STATE_FRAMEWORK_BEGIN,
    AGAVESTATE_IDLE,
    AGAVESTATE_ATTACK,
    AGAVESTATE_COOLDOWN,
    AGAVESTATE_CHARGING,
    AGAVESTATE_CHARGE_ATTACK,
    AGAVESTATE_PLANTFOOD,
};

class PlantAgave : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantAgave, PlantFramework, RtClass);
    
    virtual void Initialize() override;
    virtual void UpdateActions() override;
    virtual void DoSpecial(int i_extraParam = 0) override;
    virtual bool CanApplyPlantfood() override;
    virtual void ApplyPlantfood() override;
    virtual void CancelPlantfood() override;
    virtual void UpdatePlantfood() override;
    
    virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
//    virtual int CalcRenderOrder();
    
protected:
//    virtual bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon);
    
//    //PVZ2_CHINESE_BEGIN
//    virtual void DoSpecialForAvatarNormal();  // for avatar
//    //PVZ2_CHINESE_END
    
private:
    void            setState(uint i_plantState);
    void            dealDamage(float i_chargeRate, float& o_damageAmount);
    virtual void    onAnimStoppedCallback(const std::string& name) override;
    void            updateChargingRate();
    bool            isZombieArmorType(const ZombiePtr i_zombie);
    RtWeakPtr<BoardEntity> FindTarget(PlantWeapon i_plantWeapon);

    pvztime_t m_plantCoolDownTime;
    pvztime_t m_chargeEndTime;
    pvztime_t m_chargeTime;
    float m_chargeDamageRate;
};

#endif /* Plant_Agave_h */
