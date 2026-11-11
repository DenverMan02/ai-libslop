/*
 * GridItemCardGameZombieFlag.h
 *
 *  Created on: 2022-6-20
 *      Author: zhousen
 */

#ifndef GRIDITEMCARDGAMEZOMBIEFLAG_H_
#define GRIDITEMCARDGAMEZOMBIEFLAG_H_

#include "GridItemCardGameZombie.h"

// GridItemCardGameZombieFlagProps
class GridItemCardGameZombieFlagProps : public GridItemCardGameZombieProps
{
public:
    RT_CLASS_DEFINE(GridItemCardGameZombieFlagProps, GridItemCardGameZombieProps, RtClass);

    GridItemCardGameZombieFlagProps();

    std::vector<std::string> SummonZombies;// summon zombies name
    int SummonCountMaxHardMode;// summon zombies count for hard mode
    int SummonCountMaxEasyMode;// for easy mode
    int LevelBuff;// buff zombie level those on board
    float AttackBuff;// buff zombie attack those on board
    float SpeedBuff;// buff zombie speed those on board
};

// GridItemCardGameZombieFlag
class GridItemCardGameZombieFlag : public GridItemCardGameZombie
{
public:
	RT_CLASS_DEFINE(GridItemCardGameZombieFlag, GridItemCardGameZombie, RtClass);

	GridItemCardGameZombieFlag();
	virtual ~GridItemCardGameZombieFlag();

	virtual void GenerateZombieActions() override;

protected:
	virtual void PlayAttackAnim() override;
	virtual void SummonZombie();// summon zombie
	virtual void BuffZombies();// buff zombies on board

	std::vector<BoardEntity*> findTargets();

protected:
	int m_summonCount;// current summon count
	int m_summonCountMax;// summon count max
	std::vector<BoardEntity*> m_buffZombies;// buff zombies
};

#endif /* GRIDITEMCARDGAMEZOMBIEFLAG_H_ */
