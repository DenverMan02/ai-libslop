/*
 * ZombieAnimRig_FairyTaleBasic.h
 *
 *  Created on: 2022-3-11
 *      Author: admin
 */

#ifndef ZOMBIEANIMRIG_FAIRYTALEBASIC_H_
#define ZOMBIEANIMRIG_FAIRYTALEBASIC_H_

#include "Precompile.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_FairyTaleBasic : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_FairyTaleBasic, ZombieAnimRig_Basic, RtClass) {}

private:
    virtual const std::vector<std::string>& getHeadLayerNames() override;
    virtual const std::vector<std::string>& getArmLayerNames() override;
    virtual const std::vector<std::string>& getArmReplacementPairNames() override;
    virtual const std::vector<std::string>& getFlagHandLayerNames() override;
    virtual const std::vector<std::string>& getNoFlagHandLayerNames() override;
    virtual const std::vector<std::string>& getConeLayerNames() override;
    virtual const std::vector<std::string>& getBucketLayerNames() override;
};


#endif /* ZOMBIEANIMRIG_FAIRYTALEBASIC_H_ */
