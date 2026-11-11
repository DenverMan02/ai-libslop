/*
 * GridItemCardGameZombieBarrel.h
 *
 *  Created on: 2022-6-21
 *      Author: zhousen
 */

#ifndef GRIDITEMCARDGAMEZOMBIEBARREL_H_
#define GRIDITEMCARDGAMEZOMBIEBARREL_H_

#include "GridItemCardGameZombie.h"
#include "GridItemBarrel.h"

// GridItemCardGameZombieBarrelProps
class GridItemCardGameZombieBarrelProps : public GridItemCardGameZombieProps
{
public:
    RT_CLASS_DEFINE(GridItemCardGameZombieBarrelProps, GridItemCardGameZombieProps, RtClass);

    GridItemCardGameZombieBarrelProps();

    int ZombieBarrelCountMax;// zombie barrel count
	GriditemBarrelParams ZombieBarrelParam;// spawn zombie list in one barrel
    int ExplodeBarrelCountMax;// explode barrel count
    GriditemBarrelParams ExplodeBarrelParam;// explode barrel list
};

// GridItemCardGameZombieFlag
class GridItemCardGameZombieBarrel : public GridItemCardGameZombie
{
public:
	RT_CLASS_DEFINE(GridItemCardGameZombieBarrel, GridItemCardGameZombie, RtClass);

	GridItemCardGameZombieBarrel();
	virtual ~GridItemCardGameZombieBarrel();

	virtual void GenerateZombieActions() override;

protected:
	void SummonNormalBarrel();// summon normal barrel
	void SummonExplodeBarrel();// summon explode barrel
	void onAttackAnimDone(const std::string& name) override;

	void SummonBarrel(std::string barrelType, int num, GriditemBarrelParams param);

protected:
};


#endif /* GRIDITEMCARDGAMEZOMBIEBARREL_H_ */
