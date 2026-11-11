
#ifndef ZombieCardGameProtector_H
#define ZombieCardGameProtector_H


#include "ZombieFutureProtector.h"
#include "GridItemProtectorShieldSegment.h"


class ZombieCardGameProtector : public ZombieFutureProtector
{
public:
	RT_CLASS_DEFINE(ZombieCardGameProtector, ZombieFutureProtector, RtClass);

    OVERRIDE_STATE_UPDATE(ZombieState, Walk);


protected:
	virtual void spawnShield() override;

};

class GridItemProtectorShieldSegment_CardGame : public GridItemProtectorShieldSegment
{
public:
    RT_CLASS_DEFINE(GridItemProtectorShieldSegment_CardGame, GridItemProtectorShieldSegment, RtClass);

protected:
	virtual void onGridItemInitialize() override;
};


#endif