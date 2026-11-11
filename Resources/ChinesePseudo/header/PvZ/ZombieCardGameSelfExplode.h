#ifndef ZombieCardGameSelfExplode_h
#define ZombieCardGameSelfExplode_h

#include "ZombieSelfExplode.h"



class ZombieCardGameSelfExplode : public ZombieSelfExplode
{
public:
	RT_CLASS_DEFINE(ZombieCardGameSelfExplode, ZombieSelfExplode, RtClass);


	OVERRIDE_STATE_UPDATE(ZombieState, Walk);

    virtual void DoSpecial() override;

protected:
    void ExplodeDirectly();
};

#endif