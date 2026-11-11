/*
 * ZombieIceageBasic.h
 *
 *  Created on: 2023-11-14
 *      Author: zhousen
 */

#ifndef ZOMBIEICEAGEBASIC_H_
#define ZOMBIEICEAGEBASIC_H_

#include "ZombieBasic.h"
#include "ZombieIceAgeHunter.h"
#include "ZombieChickenFarmer.h"
#include "ZombieIceAgeTroglobite.h"

class ZombieIceAgeArmor3Elite : public ZombieBasic
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeArmor3Elite, ZombieBasic, RtClass);
};

class ZombieIceAgeArmor3ElitePropertySheet : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieIceAgeArmor3ElitePropertySheet, ZombiePropertySheet, RtClass);

	ZombieIceAgeArmor3ElitePropertySheet() {
	}
};

#endif /* ZOMBIEICEAGEBASIC_H_ */
