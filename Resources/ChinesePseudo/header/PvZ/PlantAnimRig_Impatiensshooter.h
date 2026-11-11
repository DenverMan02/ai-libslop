/*
 * PlantAnimRig_Peashooter.h
 *
 *  Created on: May 21, 2014
 *      Author: lijie
 */

#ifndef PLANTANIMRIG_IMPATIENSSHOOTER_H_
#define PLANTANIMRIG_IMPATIENSSHOOTER_H_

#include "PlantAnimRig.h"

class PlantAnimRig_Impatiensshooter : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Impatiensshooter, PlantAnimRig, RtClass);
	bool PlayPuff(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped, int i_growthLevel);
	bool PlayPlantFood(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped, int i_growthLevel);
    virtual bool PlayPlantFoodStart(int i_mainAnimPlayCount = 0) override;
    void upgrade(int level);
    void upPlantLevel(int plantLevel);
    int m_plantLevel;
    virtual pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;
protected:
    void onInitialized() override;
    std::string getIdleAnimationName() override;

    virtual std::string getAttackAnimationName() override;
    virtual std::string getPlantFoodMainAnimName() override;
    virtual void onAnimStopped() override;
    virtual void onPopAnimInitialized() override;
    std::string getPuffAnimationName(int i_growthLevel);
    std::string getPlantFoodAnimName(int i_growthLevel);
    int32_t m_growthLevel;
    bool isMaxLevel;
};

#endif /* PLANTANIMRIG_PEASHOOTER_H_ */
