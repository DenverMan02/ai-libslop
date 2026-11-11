//
//  ZombieMonkBlade.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 14-1-2.
//  Copyright (c) 2014年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieMonkBlade__
#define __PlantsVersusZombies2__ZombieMonkBlade__

#include <iostream>
#include "Precompile.h"
#include "Zombie.h"


//STATE_ENUM_CHILD_BEGIN(ZombieBasicState, ZombieState)
//ZS_Basic_TakeWeapon,
//STATE_ENUM_END(ZombieBasicState)



class ZombieMonkBlade : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieMonkBlade, Zombie, RtClass);
    
    
protected:
	virtual void onZombieInitialize() override;
	
    virtual void onUpdate() override;
    

    virtual void onEnterState_Eat(ZombieState i_fromState) override;
    virtual void updateState_Eat() override;
    virtual void onExitState_Eat(ZombieState i_toState) override;

    bool EatPlant(Plant* i_targetPlant);
    virtual void eatGridItem(GridItemPtr i_targetGridItem) override;

    
    void onAnimStoppedCallback(const std::string& i_animCommand);
    void onAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string &i_animCommand, const std::string &i_animCommandParam);
    
    bool targetHasDied;
};




#endif /* defined(__PlantsVersusZombies2__ZombieMonkBlade__) */
