/*
 * ZombieToxicWater.h
 *
 *  Created on: 2019-8-15
 *      Author: zhousen
 */

#ifndef ZOMBIETOXICWATER_H_
#define ZOMBIETOXICWATER_H_

#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"
#include "GameSubSystem.h"
#include "Projectile.h"

class ToxicWaterPerfumeBottleProjectile;

enum PoisonMistState {
	PoisonMist_Init,
	PoisonMist_Loop,// play loop effect
	PoisonMist_Destroy,// destroy this grid item
	PoisonMist_Max,
};

namespace Message
{
	void ToxicWaterNotifyCleanPoison();
}

///
/// poison mist griditem props
///
class ToxicWaterGridItemPoisonMistProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(ToxicWaterGridItemPoisonMistProps, GridItemAnimationProps, RtClass);

	ToxicWaterGridItemPoisonMistProps();

	pvztime_t GetAliveTimeThreshold() const { return _aliveTimeThreshold; }
	float GetPercentOfMaxHealth() const { return _percentOfMaxHealth; }

private:	
	pvztime_t _aliveTimeThreshold;// poison mist alive time
	float _percentOfMaxHealth;// the loss of life percent in one second

};

///
/// poison mist griditems
///
class ToxicWaterGridItemPoisonMist : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(ToxicWaterGridItemPoisonMist, GridItemAnimation, RtClass);

	ToxicWaterGridItemPoisonMist();
	virtual ~ToxicWaterGridItemPoisonMist();

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
/// ToxicWaterPerfumeBottleProjectile
///
class ToxicWaterPerfumeBottleProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ToxicWaterPerfumeBottleProjectile, Projectile, RtClass);

	ToxicWaterPerfumeBottleProjectile();

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
/// Zombie ToxicWater Props
///
class ZombieToxicWaterProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieToxicWaterProps, ZombiePropertySheet, RtClass);

	pvztime_t GetThrowChargeTimeThreshold() const { return _throwChargeTimeThreshold; }

	ProjectilePropertySheetPtr Projectile;

private:
	pvztime_t _throwChargeTimeThreshold;// the time charging to throw

};



STATE_ENUM_CHILD_BEGIN(ZombieState_ToxicWater, ZombieState)
	ZS_ToxicWater_Throw,// throw bottle
STATE_ENUM_END(ZombieState_ToxicWater)

// this state is for not avoiding the ZombieStateMachine, and do some new logic
enum ZombieToxicWaterState {
	ToxicWaterState_Init,
	ToxicWaterState_Charge,
	ToxicWaterState_Max,
};

///
/// zombie ToxicWater
///
class ZombieToxicWater : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieToxicWater, Zombie, RtClass);

	OVERRIDE_STATE_UPDATE(ZombieState, Idle);
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	DECLARE_STATE_FUNCTIONS(ZombieState, Throw);

	void onZombieInitialize() override;
	void onUpdate() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

	void onAnimStop(const std::string& i_animCommand);
	Sexy::Point throwPoint = {0,0};
	int m_LiveWave =0;
	float m_Damage = 0;

private:
//	bool findTargetPosition(Sexy::Point& o_targetPoint, bool isDead = false);// find a target can throw bottle
	SexyVector3 CalcDetailBottleOffset(int bottleType);// calc the bottle detail offset
	void Throw(Sexy::Point point);// throw poison bottle
	Sexy::Point GetTargetPos(Sexy::Point);// calc N block from the bottle drop grid (when zombie die)
	bool CanCheckThrow();// check zombie state , if can throw

	void onStartCompleted();
	void onLoopCompleted();
	void onEndCompleted();

private:
	int _state;// ToxicWater state
	bool _startCharge;// status if have start to charge
	pvztime_t _startChargeTime;// time to start throw charge
	pvztime_t _throwChargeTimeThreshold;// throw charge time
	float attack_time = 0;
	float mm_Veloctiy = 0;
	float m_damage_temp = 0;
	int temp_facting = 0;
	int m_StartWave = 0;
};


#endif /* ZOMBIETOXICWATER_H_ */
