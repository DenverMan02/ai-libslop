//
//  ZombiePoncho.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 6/25/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEPONCHO_H__
#define __ZOMBIEPONCHO_H__

#include "Zombie.h"

class ZombiePoncho : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePoncho, Zombie, RtClass);

	virtual int CalcProgressMeterHitpoints() const override;
	virtual int CalcHelmDamageIndex() const override;

protected:
	virtual void onZombieInitialize() override;
    class ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints) override;
	virtual void onTakeHelmDamage(const DamageInfo& i_damageReceived) override;
    virtual DamageInfo modifyBodyDamage(const DamageInfo& i_receivedDamage) override;

private:
	int m_helmDamageIndex;
	bool m_hasPlate;
    bool m_ponchoDroped;
};


#endif
