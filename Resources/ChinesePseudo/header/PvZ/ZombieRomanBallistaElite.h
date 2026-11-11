/*
 * ZombieRomanBallistaElite.h
 *
 *  Created on: 2021-6-4
 *      Author: zhousen
 */

#ifndef ZOMBIEROMANBALLISTAELITE_H_
#define ZOMBIEROMANBALLISTAELITE_H_

#include <string>
#include <vector>

#include "DamageInfo.h"
#include "Projectile.h"
#include "ProjectilePropertySheet.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieEnums.h"
#include "ZombieAnimRig.h"
#include "ProbabilityTypeContainer.h"
#include "EliteModule.h"


class ZombieEliteRomanBallista : public ZombieRomanBallista, public ZombieEliteModule
{
public:
	RT_CLASS_DEFINE(ZombieEliteRomanBallista, ZombieRomanBallista, RtClass);

	void onZombieInitialize() override;
	void onDraw(class Sexy::Graphics* i_g) override;
	void onPlaceOnBoard() override;
	void onUpdate() override;
    bool CanDropArm() const override { return false; }
	bool CanDropHead() const override { return false; }
    void takeBodyDamage(const DamageInfo& i_incomingDamage) override;

protected:
    void launchVase() override;
    SexyVector3 FindRandomTarget();
};

class ZombieEliteRomanBallistaProps : public ZombieRomanBallistaProps
{
public:
    RT_CLASS_DEFINE(ZombieEliteRomanBallistaProps, ZombieRomanBallistaProps, RtClass);

    ZombieEliteRomanBallistaProps();

    int VaseShotTimesInSameTime;
};


#endif /* ZOMBIEROMANBALLISTAELITE_H_ */
