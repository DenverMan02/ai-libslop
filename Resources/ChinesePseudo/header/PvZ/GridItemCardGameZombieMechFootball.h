/*
 * GridItemCardGameZombieMechFootball.h
 *
 *  Created on: 2022-7-13
 *      Author: zhousen
 */

#ifndef GRIDITEMCARDGAMEZOMBIEMECHFOOTBALL_H_
#define GRIDITEMCARDGAMEZOMBIEMECHFOOTBALL_H_

#include "GridItemCardGameZombie.h"

// GridItemCardGameZombieMechFootballProps
class GridItemCardGameZombieMechFootballProps : public GridItemCardGameZombieProps
{
public:
    RT_CLASS_DEFINE(GridItemCardGameZombieMechFootballProps, GridItemCardGameZombieProps, RtClass);

    GridItemCardGameZombieMechFootballProps();

    std::vector<Point> DiscoZombiePos;
    std::vector<Point> BattlePlaneZombiePos;
};

// GridItemCardGameZombieMechFootball
class GridItemCardGameZombieMechFootball : public GridItemCardGameZombie
{
public:
	RT_CLASS_DEFINE(GridItemCardGameZombieMechFootball, GridItemCardGameZombie, RtClass);

	GridItemCardGameZombieMechFootball();
	virtual ~GridItemCardGameZombieMechFootball();

	virtual void GenerateZombieActions() override;
	virtual void onUpdate() override;
	virtual void onPopAnimCommand(const std::string &i_animLabel, pvztime_t i_timeStamp, const std::string &i_command, const std::string &i_param) override;
	virtual void onAttackAnimDone(const std::string& name) override;
	virtual GridItemCardGameZombieAction* PickAction() override;

protected:
	void onGridItemInitialize() override;
	void GenerateDiscoZombies();
	void GenerateBattlePlaneZombies();
	void SummonBothZombies();
	void TossZombies(int block);
	void HalfBloodSpecailAction();
	bool CheckHalfBlood();
	void SetDamageState(int i_damageState);

protected:
	bool m_initHalfBloodAction;// init half blood action once
	bool m_isHalfBloodAction;// is half blood action

};


#endif /* GRIDITEMCARDGAMEZOMBIEMECHFOOTBALL_H_ */
