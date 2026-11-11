//
//  ZombieMonkBlade.h
//  PlantsVersusZombies2
//
//  Created by Xiangyu Zhang on 14-1-2.
//  Copyright (c) 2014年 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieMonkNunchaku__
#define __PlantsVersusZombies2__ZombieMonkNunchaku__

#include <iostream>
#include "Precompile.h"
#include "Zombie.h"
#include "ZombieHammer.h"



STATE_ENUM_CHILD_BEGIN(ZombieMonkNunchakuState,ZombieHammerState)
ZS_Hammer_Block_Return,
ZS_Nunchaku_Throw,
STATE_ENUM_END(ZombieMonkNunchakuState);


class ZombieMonkNunchaku : public ZombieHammer
{
public:
	RT_CLASS_DEFINE(ZombieMonkNunchaku, ZombieHammer, RtClass);
    
    
protected:
    
    DECLARE_STATE_FUNCTIONS(ZombieState, Block_Return);
    DECLARE_STATE_FUNCTIONS(ZombieState, Throw);
    
    OVERRIDE_STATE_UPDATE(ZombieState,  Block);
    OVERRIDE_STATE_UPDATE(ZombieState,  Walk);

    virtual void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;


    void onBlockReturnEnd(Zombie* z);
    void onFinishEatAnimation(Zombie* z);

    void startPushing(class Zombie* z);
private:
    Rect CalcPushRect();
    class Plant* FindThrowTarget();
};




#endif /* defined(__PlantsVersusZombies2__ZombieMonkBlade__) */
