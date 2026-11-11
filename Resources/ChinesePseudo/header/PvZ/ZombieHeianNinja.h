/*
 * ZombieHeianNinja.h
 *
 *  Created on: 2020-12-3
 *      Author: admin
 */

#ifndef ZOMBIEHEIANNINJA_H_
#define ZOMBIEHEIANNINJA_H_

#include "DamageInfo.h"
#include "RtObject.h"
#include "StateMachine.h"
#include "TimeMgr.h"
#include "Zombie.h"
#include "ZombieAction.h"
#include "ZombieImp.h"
#include "ZombieAnimRig_Imp.h"
//#include "ZombieWithActions.h"

STATE_ENUM_CHILD_BEGIN(ZombieState_HeianNinja, ZombieStateImp)
	ZS_HN_HangStart,
	ZS_HN_HangIdle,
	ZS_HN_HangEat,
	ZS_HN_HangCut,
	ZS_HN_HangBleed,
	ZS_HN_ThrowSushi,
STATE_ENUM_END(ZombieState_HeianNinja)

class ZombieHeianNinjaProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieHeianNinjaProps, ZombiePropertySheet, RtClass);

	ZombieHeianNinjaProps()
	{
		HangingAttackRectOffsetY = 0;
		HangingNoEatTimeUntilDrop = 0;
		TargetLeftmostGridXOffset = 0;
		TargetRightmostGridXOffset = 0;
		AttackInterval = 0;
	}

	int	HangingAttackRectOffsetY;
	pvztime_t HangingNoEatTimeUntilDrop;
	SexyVector3	SpawnOffset;
	ProjectilePropertySheetPtr Projectile;
	int TargetLeftmostGridXOffset;
	int TargetRightmostGridXOffset;
	pvztime_t AttackInterval;
};

class ZombieHeianNinja : public ZombieImp
{
public:
    RT_CLASS_DEFINE(ZombieHeianNinja, ZombieImp, RtClass);

	void doFallFromSky();
	Sexy::Rect CalcZombieAttackRect() override;

	bool allowElectrocuteState() const override;
	bool allowAshState() const override;

	void OnBeforeBlown(BoardEntity* i_blowSource) override;
	void onMowedDown() override;
	bool CollidesWithType(CollisionTypeFlags i_collisionFlags) const override;

protected:
	//void onExternalControlEvent() override;
	//std::string getElectrocutePAMName() const override;

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Eat);

	DECLARE_STATE_FUNCTIONS(ZombieState, HangStart);
	DECLARE_STATE_FUNCTIONS(ZombieState, HangIdle);
	DECLARE_STATE_FUNCTIONS(ZombieState, HangEat);
	DECLARE_STATE_FUNCTIONS(ZombieState, HangCut);
	DECLARE_STATE_FUNCTIONS(ZombieState, HangBleed);
	DECLARE_STATE_FUNCTIONS(ZombieState, ThrowSushi);

	//void onStartBleeding() override;
	void immediatelyCutDown();
	bool canTargetEntityHeight(BoardEntityHeight i_entityHeight) override;
	Rect calcRangedTargetGridRect() override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;

protected:
    void onZombieInitialize() override;

	void onHangStartCompleted(const std::string& i_animName);
	void onHangCutCompleted(const std::string& i_animName);
	void onThrowSushi(const std::string& i_animName);

	virtual void throwSushi();

	pvztime_t m_TimeToFallFromHang = PVZ_EOT();
	pvztime_t m_nextAttackTime = PVZ_EOT();
};

class CardGameZombieHeianNinja : public ZombieHeianNinja
{
public:
    RT_CLASS_DEFINE(CardGameZombieHeianNinja, ZombieHeianNinja, RtClass);

	virtual void throwSushi() override;

protected:
	void updateState_Walk() override;
	Rect calcRangedTargetGridRect() override;

	std::vector<BoardEntity*> FindRangedTargets();
	void throwSushi(BoardEntity*);
};

class ZombieAnimRig_HeianNinja : public ZombieAnimRig_Imp
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_HeianNinja, ZombieAnimRig_Imp, RtClass);

	const std::string getRangedAttackAnimationName() override;
	const std::vector<std::string>& getHeadLayerNames() override;
//	const std::vector<std::string>& getArmLayerNames() override;
//	const std::vector<std::string>& getArmReplacementPairNames() override;

	bool PlayHangStart(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayHangIdle();
	bool PlayHangEat();
	bool PlayHangCut(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	bool PlayThrowSushi(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);

	AnimHandle PlayDie() override;

	void SetIsHanging(bool i_hanging) { m_isHanging = i_hanging; }
	bool GetIsHanging() { return m_isHanging; }

private:
	bool m_isHanging = false;
};


#endif /* ZOMBIEHEIANNINJA_H_ */
