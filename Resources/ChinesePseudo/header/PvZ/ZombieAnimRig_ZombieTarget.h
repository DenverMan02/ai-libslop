/*
 * ZombieAnimRig_ZombieTarget.h
 *
 *  Created on: 2014-9-18
 *      Author: jianglc
 */

#ifndef ZOMBIEANIMRIG_ZOMBIETARGET_H_
#define ZOMBIEANIMRIG_ZOMBIETARGET_H_

#include "Precompile.h"
#include "ZombieAnimRig.h"

class ZombieAnimRig_ZombieTarget : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_ZombieTarget, ZombieAnimRig, RtClass);

	virtual bool PlayAppearing(AnimStoppedReflectionDelegate i_onAnimStopped);
protected:
	virtual const std::string getIdleAnimationName() override;
	virtual const std::string getDieAnimationName() override;
};



#endif /* ZOMBIEANIMRIG_ZOMBIETARGET_H_ */
