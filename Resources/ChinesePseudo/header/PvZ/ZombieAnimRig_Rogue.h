/*
 * ZombieAnimRig_Rogue.h
 *
 *  Created on: 2014-9-23
 *      Author: jianglc
 */

#ifndef ZOMBIEANIMRIG_ROGUE_H_
#define ZOMBIEANIMRIG_ROGUE_H_

#include "Precompile.h"
#include "ZombieAnimRig_DarkBasic.h"

class ZombieAnimRig_Rogue : public ZombieAnimRig_DarkBasic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Rogue, ZombieAnimRig, RtClass);

	virtual bool PlayInvisible(AnimStoppedReflectionDelegate i_onAnimStopped);
protected:
	virtual const std::string getWalkAnimationName() override;
	virtual const std::string getEatAnimationName() override;
	virtual void onPopAnimInitialized() override;
private:
	bool m_isInvisible = false;
};


#endif /* ZOMBIEANIMRIG_ROGUE_H_ */
