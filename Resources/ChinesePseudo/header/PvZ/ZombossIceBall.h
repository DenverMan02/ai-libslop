//
//  ZombossIceBall.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/11/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZombossIceBall_H__
#define __ZombossIceBall_H__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombieStateIceBall, ZombieState)
	ZS_B_IceBallMove,
STATE_ENUM_END(ZombieStateIceBall);

class ZombossIceBall : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombossIceBall, Zombie, RtClass);

protected:
	virtual void onInitialized() override;
	virtual void onPlaceOnBoard() override;
	
    bool CanBeTargetedByPlant(const RtWeakPtr<PlantType> i_plantType, bool i_ignoreInvisible = false) const override;
    virtual bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
    
    virtual bool CanBeMowed() const override
	{
		return false;
	}
    
    virtual bool CanBeFlickedOff() const override
    {
        return false;
    }
    
    virtual bool CanBeStabbed() const override
    {
        return false;
    }
    
    bool allowElectrocuteState() const override
	{
		return false;
	}
	bool allowAshState() const override
	{
		return false;
	}

	DECLARE_STATE_FUNCTIONS(ZombieState, IceBallMove);
};

#endif
