#ifndef ZombieCardGameElectric_H
#define ZombieCardGameElectric_H

#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombiePropertySheet.h"

class ZombieCardGameElectricProperty : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieCardGameElectricProperty, ZombiePropertySheet, RtClass);

    ZombieCardGameElectricProperty()
    :ProjectileTypeName("CardGameElectricProjectile")
    {
        
    }

    std::string ProjectileTypeName;
};

class ZombieCardGameElectric : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieCardGameElectric, Zombie, RtClass);

    ZombieCardGameElectric();

    virtual void onZombieInitialize() override;
    virtual std::string getAshPAMName() const override;
    virtual BoardEntity *findTarget() override;
    virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    
};


class ZombieAnimRig_CardGameElectric : public ZombieAnimRig  //need obs follow ZombieSkyCity
{
public:
    
	RT_CLASS_DEFINE(ZombieAnimRig_CardGameElectric, ZombieAnimRig, RtClass);
    
    ZombieAnimRig_CardGameElectric() {}


};

#endif