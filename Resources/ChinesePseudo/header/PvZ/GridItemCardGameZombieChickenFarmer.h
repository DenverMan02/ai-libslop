/*
 * GridItemCardGameZombieChickenFarmer.h
 *
 *  Created on: 2022-7-12
 *      Author: zhousen
 */

#ifndef GRIDITEMCARDGAMEZOMBIECHICKENFARMER_H_
#define GRIDITEMCARDGAMEZOMBIECHICKENFARMER_H_

#include "GridItemCardGameZombie.h"


// GridItemCardGameZombieChickenFarmerProps
class GridItemCardGameZombieChickenFarmerProps : public GridItemCardGameZombieProps
{
public:
    RT_CLASS_DEFINE(GridItemCardGameZombieChickenFarmerProps, GridItemCardGameZombieProps, RtClass);

    GridItemCardGameZombieChickenFarmerProps();

    Sexy::Rect SpawnGraveyardRect;// random spawn graveyard field
    int LineCount;// nearby lines spawn chickens.
    int SingleLineSummonCount;// one line summon chickens count
};


// GridItemCardGameZombieChickenFarmer
class GridItemCardGameZombieChickenFarmer : public GridItemCardGameZombie
{
public:
	RT_CLASS_DEFINE(GridItemCardGameZombieChickenFarmer, GridItemCardGameZombie, RtClass);

	GridItemCardGameZombieChickenFarmer();
	virtual ~GridItemCardGameZombieChickenFarmer();

	virtual void GenerateZombieActions() override;
	virtual void onUpdate() override;
	virtual void onPopAnimCommand(const std::string &i_animLabel, pvztime_t i_timeStamp, const std::string &i_command, const std::string &i_param) override;
	virtual void onAttackAnimDone(const std::string& name) override;
	virtual GridItemCardGameZombieAction* PickAction() override;

protected:
	void SummonChickenGraveyard();
	void SummonChickens();
	Sexy::Point PickRandomGraveyardPos(Sexy::Rect rect);
	int PickRandomLine(int togetherLines);

protected:
};

#endif /* GRIDITEMCARDGAMEZOMBIECHICKENFARMER_H_ */
