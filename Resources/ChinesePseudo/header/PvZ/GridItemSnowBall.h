/*
 * GridItemSnowBall.h
 *
 *  Created on: 2022-11-15
 *      Author: huangzhisheng
 */

#ifndef GRIDITEMSNOWBALL_H_
#define GRIDITEMSNOWBALL_H_

#include "Plant.h"
#include "RtDb.h"
#include "RtObject.h"
#include "GridItemBoardEntityConditionTarget.h"
#include "GameSubSystem.h"
#include "Zombie.h"

class GridItemSnowBall : public GridItemBoardEntityConditionTarget{
public:
	RT_CLASS_DEFINE(GridItemSnowBall, GridItemBoardEntityConditionTarget, RtClass);
	GridItemSnowBall();
	virtual ~GridItemSnowBall();

	void	setMyType(int m_type);
	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;

	enum SnowBall
	{
		big,
		mid,
		small
	};

protected:
	void onUpdate() override;
	virtual void executeAttack(Plant* plant);
	virtual bool CollidesWithType(CollisionTypeFlags i_collisionTypes) const override { return true; }
	virtual void onGridItemInitialize() override;
	virtual bool CanBeTargetedBy(const BoardEntity* i_entity) const { return true; }
	virtual bool OverrideProjectileCollision(Projectile* i_projectile);
	void TakeDamage(const DamageInfo& i_damage);

	float	calZombieSpeed(Zombie* zombie);
	void	attackTarget();
	void	onHit();
	void	toCrash();
	void	meltSnowBall();
	void	changeRowPosition(Zombie* zombie);
	void	onAnimAttackStoppedCallback(const std::string& i_animLabel);
	void	onAnimHitStoppedCallback(const std::string& i_animLabel);
	void	onAnimMeltStoppedCallback(const std::string& i_animLabel);
	void	onAnimCrashStoppedCallback(const std::string& i_animLabel);

	int hitNumber;
	int myType;
	Point targetPoint;
	bool canChangePos;
	bool canPush;
	bool isRolling;

private:

};

class GridItemSnowRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemSnowRig, PopAnimRig, RtClass);

	bool playPreAttack(std::string m_type ,PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool playHit(std::string m_type, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool playMelt(std::string m_type, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool playCrash(std::string m_type, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
};

class GridItemMidSnowBall : public GridItemSnowBall
{
	public:
	RT_CLASS_DEFINE(GridItemMidSnowBall, GridItemSnowBall, RtClass){}

	virtual void executeAttack(Plant* plant) override;
	virtual void onGridItemInitialize() override;
};

class GridItemSmallSnowBall : public GridItemSnowBall
{
public:
	RT_CLASS_DEFINE(GridItemSmallSnowBall, GridItemSnowBall, RtClass){}

	virtual void executeAttack(Plant* plant) override;
	virtual void onGridItemInitialize() override;
};

class Effect_BigCrash : public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_BigCrash, Effect_PopAnim, RtClass);
    void startBigCrash(SexyVector3 m_position);
protected:
    void playBigCrash(SexyVector3 m_position);
    int m_renderDifferenceFromPlant = RENDER_LAYER_ZOMBIE - 1;
};

#endif /* GRIDITEMSNOWBALL_H_ */
