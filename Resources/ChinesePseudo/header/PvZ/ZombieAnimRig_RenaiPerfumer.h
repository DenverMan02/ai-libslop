/*
 * ZombieAnimRig_RenaiPerfumer.h
 *
 *  Created on: 2019-9-18
 *      Author: zhousen
 */

#ifndef ZOMBIEANIMRIG_RENAIPERFUMER_H_
#define ZOMBIEANIMRIG_RENAIPERFUMER_H_

#include "ZombieAnimRig_RenaiBasic.h"

class ZombieAnimRig_RenaiPerfumer : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_RenaiPerfumer, ZombieAnimRig_Basic, RtClass) {}

private:
    virtual const std::vector<std::string>& getHeadLayerNames() override;
    virtual const std::vector<std::string>& getArmLayerNames() override;
};


#endif /* ZOMBIEANIMRIG_RENAIPERFUMER_H_ */
