/*
 * ZombieYearMonster.h
 *
 *  Created on: 2022-11-7
 *      Author: huangzhisheng
 */

#ifndef ZOMBIEYEARMONSTER_H_
#define ZOMBIEYEARMONSTER_H_

#include "ZombieAnimRig.h"
#include "Zombie.h"
#include "ZombieAction.h"
#include "ZombiePropertySheet.h"
#include "Projectile.h"
#include "EliteModule.h"
#include "Effect_PopAnim.h"

class ZombieYearMonsterProps : public ZombieWithActionsProps
{
public:
	 RT_CLASS_DEFINE(ZombieYearMonsterProps, ZombieWithActionsProps, RtClass);
	 ZombieYearMonsterProps(){
	 }

	 ProjectilePropertySheetPtr Projectile;
	 std::vector<std::string> whitelist;
};

class ZombieYearMonster : public Zombie, public ZombieEliteModule{
public:
	RT_CLASS_DEFINE(ZombieYearMonster, Zombie, RtClass);
	ZombieYearMonster();
	virtual ~ZombieYearMonster();

protected:
	virtual void 	onZombieInitialize();
	virtual void	onUpdate();
	virtual bool	OverrideProjectileCollision(Projectile* i_projectile);
	void	onAnimStoppedCallback(const std::string& i_animLabel);
	bool	WillTargetPlant(Plant* i_plant){return false;}
	virtual BoardEntity *findTarget(){return NULL;}
    bool CanDropArm() const override { return false; }
	bool CanDropHead() const override { return false; }

	virtual void onStartBleeding(){};

	void	setState(int i_action);
	virtual void TakeDamage(const DamageInfo& i_damage) override;
	void takeBodyDamage(const DamageInfo& i_incomingDamage) override;

	BoardEntityPtr	findNearest();

	bool	isRedPlant(BoardEntity* BoardEntity);
	bool	isOnLastColumn();

	void	attackTarget();
	void	healingItself();
	std::string	calJumpingDistance();
	void onDraw(class Sexy::Graphics* i_g) override;

	enum actionState
	{
		PreAttack,
		FindTarget,
		AttackTarget,
		FeelFrightened,
		EngulfAndDigest,
		FearExplosion,
		Departure
	};

private:
	OVERRIDE_STATE_FUNCTIONS(ZombieState, Ash);
	pvztime_t healingTime;
	pvztime_t endTime;
	pvztime_t endDigest;
	pvztime_t endStun;
	int TotalFrames;
	int m_state;
	bool fristAttack;
	bool isFearing;
	bool Dying;
	bool startEffect;
	SexyVector3 targetPosition;
	BoardEntityPtr m_target;
};

class ZombieAnimRig_YearMonster : public ZombieAnimRig
{
public:
	 RT_CLASS_DEFINE(ZombieAnimRig_YearMonster, ZombieAnimRig, RtClass);
	 bool PlayAccumulation(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	 bool PlayJumpBackOne(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	 bool PlayJumpBackFive(std::string animation ,PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	 bool PlayLook(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	 bool PlayEat(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	 bool PlayRunAway(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	 bool PlayDeparture();
};

class YearMonsterProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(YearMonsterProjectile, Projectile, RtClass);
	virtual void onProjectileInitialized();
//	virtual bool handleImpact(BoardEntity* i_impactedEntity = NULL);
};

class Effect_MistUp :	public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_MistUp, Effect_PopAnim, RtClass);
    Effect_MistUp(){}
    void startMistUp (SexyVector3 m_position);
protected:
    void playMistUp (SexyVector3 m_position);
};


class Effect_MistDown :	public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_MistDown, Effect_PopAnim, RtClass);
    Effect_MistDown(){}
    void startMistDown (SexyVector3 m_position);
protected:
    void playMistDown (SexyVector3 m_position);
};

#endif /* ZOMBIEYEARMONSTER_H_ */
