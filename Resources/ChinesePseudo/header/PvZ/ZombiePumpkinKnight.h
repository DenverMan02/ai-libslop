/*
 * 	ZombiePumpkinKnight.h
 *
 * 	Created On: 2022-8-20
 * 		Author:	kkdud
 */

#ifndef __ZOMBIEPUMPKINKNIGHT_H__
#define __ZOMBIEPUMPKINKNIGHT_H__

#include "Zombie.h"

class ZombiePumpkinKnightProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombiePumpkinKnightProps, ZombiePropertySheet, RtClass);

	float SummonPumpkinGhostInterval = 5.f;
	float GhostHitpoints = 500.f;
	float GhostSpeed = 1.f;
	float GhostExplodeStunDuration = 1.f;
	float GhostExplodeDamageAmount = 1.f;

	float PumpkinRollSpeed = 1.f;

	float HitpointsInPhase2 = 3000.f;
	float SlashDamageAmountInPhase2 = 500.f;
	Rect AttackRectInPhase2 = {-30, 15, 95, 45};
	float BullWalkSpeed = 0.3f;
	float BullRunSpeed = 1.25f;

	float BullFireGroundAliveDuration = 5.f;
};

STATE_ENUM_CHILD_BEGIN(PumpkinKnightState, ZombieState)
	ZS_PUMPKIN_KNIGHT_Summon,
	ZS_PUMPKIN_KNIGHT_Retreat,
	ZS_PUMPKIN_KNIGHT_Rebirth,
	ZS_PUMPKIN_KNIGHT_Bull_Summon,
	ZS_PUMPKIN_KNIGHT_Bull_Entering,
	ZS_PUMPKIN_KNIGHT_Bull_Pawing,
	ZS_PUMPKIN_KNIGHT_Bull_Running,
	ZS_PUMPKIN_KNIGHT_Bull_Translate,
STATE_ENUM_END(PumpkinKnightState);


class ZombiePumpkinKnight : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePumpkinKnight, Zombie, RtClass);

protected:
	void onZombieInitialize() override;
	void onPlaceOnBoard() override;
	void chooseDeathState(const DamageInfo& i_deathBlow) override;
	bool CanDropHead() const override { return false; };
	bool canAttack() override { return m_currentPhase; };
	Sexy::Rect CalcZombieAttackRect() override;

	OVERRIDE_STATE_UPDATE(ZombieState, Walk);

	DECLARE_STATE_FUNCTIONS(ZombieState, Summon);
	DECLARE_STATE_FUNCTIONS(ZombieState, Retreat);
	DECLARE_STATE_FUNCTIONS(ZombieState, Rebirth);
	DECLARE_STATE_FUNCTIONS(ZombieState, Bull_Summon);
	DECLARE_STATE_FUNCTIONS(ZombieState, Bull_Entering);
	DECLARE_STATE_FUNCTIONS(ZombieState, Bull_Pawing);
	DECLARE_STATE_FUNCTIONS(ZombieState, Bull_Running);
	DECLARE_STATE_FUNCTIONS(ZombieState, Bull_Translate);

private:
	void checkForPumpkinGhostSummon();

	void playSummonAnim();
	void onSummonAnimDone();
	void summonPumpkinGhosts();
	void summonPumpkinGhostAtPosition(SexyVector3 i_position);

	void playRetreatStartAnimation();
	void onRetreatStartAnimationDone();
	void playRetreatLoopAnimation();

	void switchPopAnimRigToPhase2();

	void playRebirthAnimation();
	void onRebirthAnimationDone();

	void playBullSummonAnim();
	void onBullSummonAnimDone();

	void playBullEnteringAnimation();

	void playBullPawingAnimation();
	void onBullPawingAnimationDone();

	void onBullWalkAnimContinued(const std::string&, const std::string&, int);

	void playRunningAnimation();
	Rect getRunningAttackRect();
	void checkAndFireGround();
	void addFireGroundEffect();

	void playTranslateStartAnimation();
	void onTranslateStartAnimationDone();
	void addTranslateEffect();
	void onTranslateEffectDone(class StandaloneEffect* i_effect);

	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
	void onAttackAnimStopped(const std::string& i_animLabel) override;

	pvztime_t m_pumpkinGhostSummonTimer = PVZ_EOT();

	int m_currentPhase = 0;

	bool m_walkCycled = false;
	std::vector<Point> m_firedGrids;

	int m_attackedTimes = 0;
};

class ZombieAnimRig_PumpkinKnight : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_PumpkinKnight, ZombieAnimRig, RtClass);

	const std::string getWalkAnimationName() override;
	const std::string getDieAnimationName() override { return "bull die"; };

	bool playSingleAnimation(std::string i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool playLoopAnimation(std::string i_animLabel);

	std::string getSummonAnimLabelName() { return "attack"; }
	std::string getSummonCommand() { return "summon"; }
	std::string getRetreatStartAnimLabelName() { return "die"; }
	std::string getRetreatLoopAnimLabelName() { return "roll"; }
	std::string getBullSummonAnimLabelName() { return "attack2"; }
	std::string getBullSummonCommand() { return "bull summon"; }
	std::string getBullEnteringAnimLabelName() { return "bull walk"; }

	std::string getBullPawingAnimLabelName() { return "bull stamp"; }

	std::string getRebirthAnimLabelName() { return "appear"; }
	std::string getTranslateStartAnimLabelName() { return "bull stop"; }

	void setCurrentPhase(int i_phase) { m_currentAnimPhase = i_phase; }
	void setRunning(bool i_flg) { m_isRunning = i_flg; }

	int m_currentAnimPhase = 0;
	bool m_isRunning = false;
};

class EffectPumpkinKnightBullRunning : public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(EffectPumpkinKnightBullRunning, Effect_PopAnim, RtClass);

	void registerForEvents() override;
    void OnGatherPlantingRestrictions(const Sexy::Point& i_gridPosition, const PlantType* i_plantType, std::vector<PlantingReason>* io_plantingReasons);

	void onInitialized() override;
	void onUpdate() override;
	void setGridPoint(Point i_gridPoint);
	void setAliveDruation(float i_aliveDuration);

	Point m_gridPoint = Point();
	pvztime_t m_timeToDie = PVZ_EOT();
};

#endif /* __ZOMBIEPUMPKINKNIGHT_H__ */
