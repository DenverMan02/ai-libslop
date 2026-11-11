/*
 * ZombieZoybeanPodGatlingPea.h
 *
 *  Created on: 2022-10-17
 *      Author: huangzhisheng
 */

#ifndef ZOMBIEZOYBEANPODGATLINGPEA_H_
#define ZOMBIEZOYBEANPODGATLINGPEA_H_

#include "ZombieShooter.h"
#include "Plant.h"

class ZombieZoybeanPodGatlingPea : public ZombieShooter{
public:
	RT_CLASS_DEFINE(ZombieZoybeanPodGatlingPea, ZombieShooter, RtClass);
	ZombieZoybeanPodGatlingPea(){
		spawnFromPodAnimationName = "born";
		additionalDamage = 0.0f;
	}
	virtual ~ZombieZoybeanPodGatlingPea();
	float additionalDamage;

	void SetInstigator(Plant* plant);
	float GetInstigatorBoost() const;

private:
	void onUpdate() override;
protected:
	virtual BoardEntity *findTarget() override;
    virtual void onZombieInitialize() override;

    RtWeakPtr<Plant> m_instigator;
    DamageInfo calcEatDamage() override;
};

#endif /* ZOMBIEZOYBEANPODGATLINGPEA_H_ */
