/*
 * GridItemCardGameZombieCannon.h
 *
 *  Created on: 2022-6-23
 *      Author: zhousen
 */

#ifndef GRIDITEMCARDGAMEZOMBIECANNON_H_
#define GRIDITEMCARDGAMEZOMBIECANNON_H_

#include "GridItemCardGameZombie.h"
#include "ProjectilePropertySheet.h"
#include "SexyAppFramework/SexyVector.h"
#include "Projectile.h"

// GridItemCardGameZombieCannonProps
class GridItemCardGameZombieCannonProps : public GridItemCardGameZombieProps
{
public:
    RT_CLASS_DEFINE(GridItemCardGameZombieCannonProps, GridItemCardGameZombieProps, RtClass);

    GridItemCardGameZombieCannonProps();

    std::string PopAnimFireProjectileName;
    int SpawnImpMax;
    int SpawnImpMaxHardMode;
    ProjectilePropertySheetPtr          Projectile;
};

// GridItemCardGameZombieCannon
class GridItemCardGameZombieCannon : public GridItemCardGameZombie
{
public:
	RT_CLASS_DEFINE(GridItemCardGameZombieCannon, GridItemCardGameZombie, RtClass);

	GridItemCardGameZombieCannon();
	virtual ~GridItemCardGameZombieCannon();

	virtual void GenerateZombieActions() override;
	virtual void PlayAttackAnim() override;

protected:
	virtual void SpawnImp();// fire a imp to player's board.
	virtual void FireProjectile();// fire projectile
	virtual void onPopAnimCommand(const std::string &i_animLabel, pvztime_t i_timeStamp, const std::string &i_command, const std::string &i_param) override;

	std::vector<SexyVector3> FindSpawnImpPosition();// find spawn imp position
	void FireImp(SexyVector3 position);// fire imp in position
	std::vector<BoardEntity*> FindFireProjectileTarget();// find fire projectile target
	void FireTarget(BoardEntity* target);// fire projectile to target

protected:
	int m_spawnImpCount;
	int m_spawnImpCountMax;
};

// CardGameZombieCannonBallProjectile
class CardGameZombieCannonBallProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(CardGameZombieCannonBallProjectile, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};

#endif /* GRIDITEMCARDGAMEZOMBIECANNON_H_ */
