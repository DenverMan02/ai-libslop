/*
 * GridItemCardGameZombieWind.h
 *
 *  Created on: 2022-6-10
 *      Author: zhousen
 */

#ifndef GRIDITEMCARDGAMEZOMBIEWIND_H_
#define GRIDITEMCARDGAMEZOMBIEWIND_H_

#include "GridItemCardGameZombie.h"
#include "HeianWindSystem.h"

// GridItemCardGameZombieWindProps
class GridItemCardGameZombieWindProps : public GridItemCardGameZombieProps
{
public:
    RT_CLASS_DEFINE(GridItemCardGameZombieWindProps, GridItemCardGameZombieProps, RtClass);

    GridItemCardGameZombieWindProps();

    int NinjaZombieCount;// throw the count of ninja zombie.
    int GargantuarZombieCount;// throw the count of gargantuar zombie.
    int WindPushZombieBlocks;// can push all zombies the count of blocks
    int WindTornadoCount;// generate the count of tornados.
    int NinjaTentHitpoints;
    pvztime_t NinjaTentProductInterval;
    int GargantuarTentHitpoints;
    pvztime_t GargantuarTentProductInterval;

};

// GridItemCardGameZombieWind
class GridItemCardGameZombieWind : public GridItemCardGameZombie
{
public:
	RT_CLASS_DEFINE(GridItemCardGameZombieWind, GridItemCardGameZombie, RtClass);

	GridItemCardGameZombieWind();
	virtual ~GridItemCardGameZombieWind();

	virtual void GenerateZombieActions() override;
	virtual void onUpdate() override;
	virtual void onPopAnimCommand(const std::string &i_animLabel, pvztime_t i_timeStamp, const std::string &i_command, const std::string &i_param) override;
	virtual void onAttackAnimDone(const std::string& name) override;
	virtual GridItemCardGameZombieAction* PickAction() override;

protected:
	void ThrowNinjaZombies();
	void SummonGargantuarZombies();
	void SummonBothZombies();
	void TossZombies(int block);
	void HalfBloodSpecailAction();
	void GenerateWind();
	void GenerateTornado();
	void GenerateTornadoInRow(int i_row);

	void GenerateNinjaTent();
	void GenerateGargantuarTent();
	void SummonTent(std::string tentName, Sexy::Point pos);
	void GenerateCurseCard();
	bool CheckTentsDestroyed();
	bool CheckHalfBlood();

protected:
	bool m_initHalfBloodAction;// init half blood action once
	bool m_isHalfBloodAction;// is half blood action
	std::vector<Sexy::Point> m_ninjaTentGeneratorPositions;// ninja tent pos
	std::vector<Sexy::Point> m_gargantuarTentGeneratorPositions;// gargantuar tent pos
};

// Card Game Zombie Wind Tornado
class CardGameZombieWindTornado : public Projectile
{
public:
	RT_CLASS_DEFINE(CardGameZombieWindTornado, Projectile, RtClass);
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;

protected:
	virtual void onInitialized() override;
	virtual void moveThroughTime(pvztime_t i_dt) override;

	void TryFlickZombie(Zombie* i_zombie);

protected:
	std::vector<RtWeakPtr<class Zombie>> m_completedZombies;// touches zombie.
};

#endif /* GRIDITEMCARDGAMEZOMBIEWIND_H_ */
