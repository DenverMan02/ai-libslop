/*
 * ZombieAnimRig_ToxicWater.h
 *
 *  Created on: 2019-9-18
 *      Author: zhousen
 */

#ifndef ZOMBIEANIMRIG_TOXICWATER_H_
#define ZOMBIEANIMRIG_TOXICWATER_H_

#include "ZombieAnimRig_RenaiBasic.h"
//#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_ToxicWater : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ToxicWater, ZombieAnimRig_Basic, RtClass) {}

	void PlayToxicStartAnimation(AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayToxicLoopAnimation(AnimStoppedReflectionDelegate i_onAnimStopped);
	void PlayToxicEndAnimation(AnimStoppedReflectionDelegate i_onAnimStopped);

private:
    virtual const std::vector<std::string>& getHeadLayerNames() override;
    virtual const std::vector<std::string>& getArmLayerNames() override;
};


#endif /* ZOMBIEANIMRIG_RENAIPERFUMER_H_ */
