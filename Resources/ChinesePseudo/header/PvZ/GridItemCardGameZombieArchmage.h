/*
 * GridItemCardGameZombieArchmage.h
 *
 *  Created on: 2022-6-21
 *      Author: zhousen
 */

#ifndef GRIDITEMCARDGAMEZOMBIEARCHMAGE_H_
#define GRIDITEMCARDGAMEZOMBIEARCHMAGE_H_

#include "GridItemCardGameZombie.h"

// GridItemCardGameZombieArchmageProps
class GridItemCardGameZombieArchmageProps : public GridItemCardGameZombieProps
{
public:
    RT_CLASS_DEFINE(GridItemCardGameZombieArchmageProps, GridItemCardGameZombieProps, RtClass);

    GridItemCardGameZombieArchmageProps();

    int HypnotizeZombieMax;// hypnotize zombie number
    int HypnotizeZombieMaxHardMode;
    int WizardZombieMax;// summon wizard zombie number
    int WizardZombieMaxHardMode;
    std::string SummonZombieType;// summon zombie name
};


// GridItemCardGameZombieArchmage
class GridItemCardGameZombieArchmage : public GridItemCardGameZombie
{
public:
	RT_CLASS_DEFINE(GridItemCardGameZombieArchmage, GridItemCardGameZombie, RtClass);

	GridItemCardGameZombieArchmage();
	virtual ~GridItemCardGameZombieArchmage();

	virtual void GenerateZombieActions() override;

protected:
	virtual void onPopAnimCommand(const std::string &i_animLabel, pvztime_t i_timeStamp, const std::string &i_command, const std::string &i_param) override;

	void Hypnotize();// hypontize zombie
	void Summon();// summon wizard zombie

	std::vector<BoardEntity*> FindTargets();

protected:
	int m_hypnotizeCount;
	int m_summonWizardZombieCount;
};

#endif /* GRIDITEMCARDGAMEZOMBIEARCHMAGE_H_ */
