/*
 * MomotaroRider.h
 *
 *  Created on: 2021-3-23
 *      Author: admin
 */

#ifndef MOMOTARORIDER_H_
#define MOMOTARORIDER_H_

#include "RiverCrossingDodoRider.h"

class MomotaroRider : public RiverCrossingDodoRider
{
public:
    RT_CLASS_DEFINE(MomotaroRider, RiverCrossingDodoRider, RtClass);

    MomotaroRider();
    virtual ~MomotaroRider();

    bool IsDying();

protected:
    /// GameObject interface
    void initializePAM(PopAnim* i_popAnim) override;
    void onAnimStopped(const std::string& i_animName) override;
    void GetIdleWeights(ProbabilitySet<std::string>& i_idleWeights) override;
    Rect calcCollisionRect() override;
    void onInitialized() override;
};

#endif /* MOMOTARORIDER_H_ */
