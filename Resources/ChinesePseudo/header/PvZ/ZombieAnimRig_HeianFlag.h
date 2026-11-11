/*
 * ZombieAnimRig_HeianFlag.h
 *
 *  Created on: 2019-8-23
 *      Author: zhousen
 */

#ifndef ZOMBIEANIMRIG_HEIANFLAG_H_
#define ZOMBIEANIMRIG_HEIANFLAG_H_

#include "Precompile.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_HeianFlag : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_HeianFlag, ZombieAnimRig_Basic, RtClass) {}

private:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	virtual const std::vector<std::string>& getFlagHandLayerNames() override;
	virtual const std::vector<std::string>& getNoFlagHandLayerNames() override;
	virtual const std::vector<std::string>& getConeLayerNames() override;
	virtual const std::vector<std::string>& getBucketLayerNames() override;
};


#endif /* ZOMBIEANIMRIG_HEIANFLAG_H_ */
