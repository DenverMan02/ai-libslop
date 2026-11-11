/*
 * PlantAnimRig_Iceburg.h
 *
 *  Created on: Apr 23, 2014
 *      Author: lijie
 */

#ifndef PlantsVersusZombies2_PLANTANIMRIG_ICEBURG_H_
#define PlantsVersusZombies2_PLANTANIMRIG_ICEBURG_H_

#include "PlantAnimRig.h"

enum PlantAnimRigState_Iceburg
{
	PLANTANIM_ICEBURG_SHOOT = PLANTANIM_USERDEFINED,
};

class PlantAnimRig_Iceburg : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Iceburg, PlantAnimRig, RtClass);

	bool PlayShootAnimation();
};



#endif /* PLANTANIMRIG_ICEBURG_H_ */
