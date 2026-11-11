/*
 * ZombieFairyTaleBasic.h
 *
 *  Created on: 2022-4-6
 *      Author: admin
 */

#ifndef ZOMBIEFAIRYTALEBASIC_H_
#define ZOMBIEFAIRYTALEBASIC_H_

#include "Precompile.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_FairyTaleBasic.h"

class ZombieAnimRig_FairyTaleArmorBasic : public ZombieAnimRig_FairyTaleBasic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_FairyTaleArmorBasic, ZombieAnimRig_FairyTaleBasic, RtClass) {}

	void SetLayerVisibilityForCurrentState() override;
};


#endif /* ZOMBIEFAIRYTALEBASIC_H_ */
