//
//  ZombieBasic.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/9/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEBASIC_H__
#define __ZOMBIEBASIC_H__

#include "Precompile.h"
#include "Zombie.h"



class ZombieBasic : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieBasic, Zombie, RtClass);
    
    void PlaySurPrise();

protected:
	virtual void onZombieInitialize() override;
    void    onSetHelm() override;
	
	virtual void SetIsFlagZombie(bool i_hasFlag) override;
    
    virtual void onUpdate() override;
	
	virtual void onTakeHelmDamage(const DamageInfo& i_damageReceived) override;
    class ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints) override;
    
    virtual void refreshAnimRigForHelm();
	virtual void refreshHelmDamageState();    
private:
	int	m_helmDamageIndex;
    
    bool      m_HaveTanHao;
    bool      m_HavePlayTanHao;
    
    float     m_lastFrame;
};

#endif
