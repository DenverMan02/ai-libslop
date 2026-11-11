/*
 * ZombieShooter.h
 *
 *  Created on: 2020-10-21
 *      Author: admin
 */

#ifndef ZOMBIESHOOTER_H_
#define ZOMBIESHOOTER_H_

#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombiePropertySheet.h"
#include "RestrictionSet.h"
#include "ZombieAnimRig_Basic.h"

namespace Message
{
    void NotifyHitPlant();
}

class ZombieAnimRig_ShooterBasic : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ShooterBasic, ZombieAnimRig_Basic, RtClass);

private:
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

class ZombieShooterProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieShooterProps, ZombiePropertySheet, RtClass);

    ZombieShooterProps()
    {

    }

    SexyVector3	SpawnOffset;
    ProjectilePropertySheetPtr Projectile;
};

class ZombieShooter : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieShooter, Zombie, RtClass);

protected:
    virtual void onZombieInitialize() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	virtual void tryShoot();

	bool hasHeadParticle() const override { return false; }
};


#endif /* ZOMBIESHOOTER_H_ */
