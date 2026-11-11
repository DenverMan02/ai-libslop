//
//  SkatingGuacodile.h
//  PlantsVersusZombies2
//
//  Created by Wan, Qi on 15/3/26.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__SkatingGuacodile__
#define __PlantsVersusZombies2__SkatingGuacodile__

#include <stdio.h>
#include "RiverEntity.h"

class SkatingGuacodile : public RiverEntity
{
public:
    RT_CLASS_DEFINE(SkatingGuacodile, RiverEntity, RtClass);
    
    SkatingGuacodile();
    virtual ~SkatingGuacodile();
    
    virtual Rect GetAttackRect();
    void SkatingGuacodileInitialize();
    
    virtual int CalcRenderOrder() const override;
    
protected:
    virtual std::string GetPam();

private:
    void initializePAM(PopAnim* i_popAnim);
    void onZombieDropHead(class Zombie *i_zombie);    
};

#endif /* defined(__PlantsVersusZombies2__SkatingGuacodile__) */
