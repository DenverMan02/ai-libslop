/*
 * PlantAnimRig_Spikeweed.h
 *
 *  Created on: 2014-6-26
 *      Author: jianglc
 */

#ifndef PLANTANIMRIG_SPIKEWEED_H_
#define PLANTANIMRIG_SPIKEWEED_H_

#include "PlantAnimRig.h"

class PlantAnimRig_Spikeweed : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Spikeweed, PlantAnimRig, RtClass);

	virtual bool playPlantFoodMain() override;
	virtual bool PlayIdleLooped() override;
	virtual bool PlayAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate()) override;
	void		 SetTransform(bool isTransform);

private:
	bool	m_isTransformed = false;

protected:
	virtual void onPopAnimInitialized() override;
};


#endif /* PLANTANIMRIG_SPIKEWEED_H_ */
