/*
 * ZombieMoneyTree.h
 *
 *  Created on: 2022-11-9
 *      Author: huangzhisheng
 */

#ifndef ZOMBIEMONEYTREE_H_
#define ZOMBIEMONEYTREE_H_

#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "Projectile.h"
#include "ZombiePropertySheet.h"
#include "GridItemAnimation.h"
#include "PopAnimRig.h"
#include "Board.h"

class ZombieMoneyTreeProps : public ZombieWithActionsProps
{
public:
	 RT_CLASS_DEFINE(ZombieMoneyTreeProps, ZombieWithActionsProps, RtClass);
	 ZombieMoneyTreeProps(){
		 attackTargetInterval = 15;
	 }

	 ProjectilePropertySheetPtr Projectile;
	 pvztime_t attackTargetInterval;
};


class ZombieMoneyTree : public Zombie{
public:
	RT_CLASS_DEFINE(ZombieMoneyTree, Zombie, RtClass);
	ZombieMoneyTree();
	virtual ~ZombieMoneyTree();
	virtual void onInitialized();
	virtual void onUpdate() override;

	void throwOutYuanbao();
	void getYuanbaoPositon();
	bool isGridCenter();
	virtual bool hasHeadParticle() const {return false;}

//	void setState(uint m_zombiestate);

protected:
	virtual void onPopAnimCommand(const std::string &i_animLabel, pvztime_t i_timeStamp, const std::string &i_command, const std::string &i_param);
	void onAttackAnimStopped(const std::string& i_animLabel);

private:
	pvztime_t attackTime;
	int attackLock;
	std::vector<Sexy::Point> targetGrid;
};

enum ZombieAnimRigState_MoneyTree
{
	ZOMBIEANIM_MONEYTREE_THROWYUANBAO = ZOMBIEANIM_USERDEFINED,
};

class ZombieAnimRig_MoneyTree : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_MoneyTree, ZombieAnimRig, RtClass);

protected:

};


class YuanbaoProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(YuanbaoProjectile, Projectile, RtClass);
	virtual void onProjectileInitialized() {
		JoinTeam(TEAM_ZOMBIES);
	}
	virtual bool handleImpact(BoardEntity* i_impactedEntity = NULL);
};


class GridItemYuanbao : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemYuanbao, GridItemAnimation, RtClass);

	void onUpdate() override;
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return true; }
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return true; }
	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
	bool OverrideProjectileCollision(Projectile* i_projectile);
	void onGridItemInitialize() override;
	void DropCoin();
	void onAnimStoppedCallback(const std::string& i_animLabel);

private:
	pvztime_t disappear;
};

class GridItemYuanbaoRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemYuanbaoRig, PopAnimRig, RtClass);

	bool playBirthAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	void playIdle1Anim();

	void playIdle2Anim();

	void playIdle3Anim();
};


#endif /* ZOMBIEMONEYTREE_H_ */
