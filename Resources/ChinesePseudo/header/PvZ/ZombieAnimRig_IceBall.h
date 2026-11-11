//
//  ZombieAnimRig_IceBall.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 4/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZombieAnimRig_IceBall_H__
#define __ZombieAnimRig_IceBall_H__

#include "ZombieAnimRig.h"

class ZombieAnimRig_IceBall : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_IceBall, ZombieAnimRig, RtClass);

    void PlayMove();
    
protected:
	virtual void			onNeedsToDie() override;
};

#endif //__ZombieAnimRig_IceBall_H__
