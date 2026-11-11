/*
 * PlantAnimRig_Peashooter.h
 *
 *  Created on: May 21, 2014
 *      Author: lijie
 */

#ifndef PLANTANIMRIG_PEASHOOTER_H_
#define PLANTANIMRIG_PEASHOOTER_H_

#include "PlantAnimRig.h"

class PlantAnimRig_Peashooter : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Peashooter, PlantAnimRig, RtClass);

    virtual bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;

protected:
    virtual std::string getAttackAnimationName() override;
    virtual void onAnimStopped() override;
    virtual void onPopAnimInitialized() override;
};

#endif /* PLANTANIMRIG_PEASHOOTER_H_ */
