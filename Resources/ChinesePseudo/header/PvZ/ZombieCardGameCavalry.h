#ifndef ZombieCardGameCavalry_H
#define ZombieCardGameCavalry_H

#include "ZombieCavalry.h"


class ZombieCardGameCavalry : public ZombieCavalry
{
public:
	RT_CLASS_DEFINE(ZombieCardGameCavalry, ZombieCavalry, RtClass);

protected:
    OVERRIDE_STATE_FUNCTIONS(ZombieState, Running);

	virtual void onPopAnimCommand(const std::string& i_animName, pvztime_t i_time, const std::string& i_command, const std::string& i_params) override;
	virtual void launchImp() override;
    virtual void onPlaceOnBoard() override;

protected:
    bool m_hitZombie;
    bool m_hitGridItem;
};


#endif
