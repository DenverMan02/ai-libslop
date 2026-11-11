/*
 * ZombiePerfumer.h
 *
 *  Created on: 2019-8-15
 *      Author: zhousen
 */

#ifndef ZOMBIEPERFUMER_H_
#define ZOMBIEPERFUMER_H_

#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"
#include "GameSubSystem.h"
#include "Projectile.h"

class PerfumeBottleProjectile;

enum PoisonMistState {
	PoisonMist_Init,
	PoisonMist_Loop,// play loop effect
	PoisonMist_Destroy,// destroy this grid item
	PoisonMist_Max,
};

namespace Message
{
	void NotifyCleanPoison();
}

///
/// poison mist griditem props
///
class GridItemPoisonMistProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemPoisonMistProps, GridItemAnimationProps, RtClass);

	GridItemPoisonMistProps();

	pvztime_t GetAliveTimeThreshold() const { return _aliveTimeThreshold; }
	float GetPercentOfMaxHealth() const { return _percentOfMaxHealth; }

private:	
	pvztime_t _aliveTimeThreshold;// poison mist alive time
	float _percentOfMaxHealth;// the loss of life percent in one second
};

///
/// poison mist griditems
///
class GridItemPoisonMist : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemPoisonMist, GridItemAnimation, RtClass);

	GridItemPoisonMist();
	virtual ~GridItemPoisonMist();

	bool IsDamageable() const override { return false; }
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

	void onGridItemInitialize() override;
	void onUpdate() override;
	void KillGridItem() override;
	int CalcRenderOrder() const override;

	void TurnToLoop();// enhance the grid item live time

protected:
	virtual void CreatePoisonEffect();// create poison mist
	virtual void DoPoisonMistEffect(Sexy::Point pos);// execute the poison effect
	
	virtual void OnCleanPoison(int x, int y, bool i_fromPlant);// water mist created, post message to callback
	virtual void OnCreatePlant(Plant* plant);// plant created, post message to callback
	virtual void PoisonPlant(Plant* plant);//  poison the plant which in mist
	virtual void RecoverPlant(Plant* plant);// when poison mist disappear, plant should be recovered

protected:
	int _state;// PoisonMistState
	Sexy::Point _position;// poison grid pos
	pvztime_t _startTime;// poison start time
	pvztime_t _aliveTimeThreshold;// poison alive time
};

enum BottleThrowType {
	BottleThrow_Throw,// zombie throw
	BottleThrow_DeadDrop,// zombie dead drop
};

///
/// PerfumeBottleProjectile
///
class PerfumeBottleProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(PerfumeBottleProjectile, Projectile, RtClass);

	PerfumeBottleProjectile();

	bool OnCollideGround() override;

	void SetType(int type);// BottleThrowType
	void SetTargetPoint(Sexy::Point point);

private:
	void CreateBrokenAnimation();// bottle broken animation
	void OnBrokenBottleComplete(StandaloneEffect* i_effect);// create poison mist
	std::vector<Sexy::Point> CreatePoisonList(Sexy::Point point, int type);// create poison grid pos list according to type
	bool CheckExistPlantInPlantfoodStatus(Sexy::Point point);// check if in point has plant, and it is in plantfood status.

private:
	int _type;// BottleThrowType
	Sexy::Point _targetPos;// target grid positions
};

///
/// Zombie Perfumer Props
///
class ZombiePerfumerProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombiePerfumerProps, ZombiePropertySheet, RtClass);

	pvztime_t GetThrowChargeTimeThreshold() const { return _throwChargeTimeThreshold; }

	ProjectilePropertySheetPtr Projectile;

private:
	pvztime_t _throwChargeTimeThreshold;// the time charging to throw
};



STATE_ENUM_CHILD_BEGIN(ZombieState_Perfumer, ZombieState)
	ZS_Perfumer_Throw,// throw bottle
STATE_ENUM_END(ZombieState_Perfumer)

// this state is for not avoiding the ZombieStateMachine, and do some new logic
enum ZombiePerfumerState {
	PerfumerState_Init,
	PerfumerState_Charge,
	PerfumerState_Max,
};

///
/// zombie perfumer
///
class ZombiePerfumer : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePerfumer, Zombie, RtClass);

	OVERRIDE_STATE_UPDATE(ZombieState, Idle);
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	DECLARE_STATE_FUNCTIONS(ZombieState, Throw);

	void onZombieInitialize() override;
	void onUpdate() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

	void onAnimStop(const std::string& i_animCommand);

private:
	bool findTargetPosition(Sexy::Point& o_targetPoint, bool isDead = false);// find a target can throw bottle
	SexyVector3 CalcDetailBottleOffset(int bottleType);// calc the bottle detail offset
	void Throw(Sexy::Point point);// throw poison bottle
	Sexy::Point GetTargetPos(Sexy::Point);// calc N block from the bottle drop grid (when zombie die)
	bool CanCheckThrow();// check zombie state , if can throw

private:
	int _state;// perfumer state
	bool _startCharge;// status if have start to charge
	pvztime_t _startChargeTime;// time to start throw charge
	pvztime_t _throwChargeTimeThreshold;// throw charge time
};


#endif /* ZOMBIEPERFUMER_H_ */
