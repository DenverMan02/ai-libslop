/*
 * 	ZombiePumpkinKnightGhost.cpp
 *
 * 	Created On: 2022-8-20
 * 		Author:	kkdud
 */

#ifndef _ZOMBIEPUMPKINKNIGHTGHOST_H__
#define _ZOMBIEPUMPKINKNIGHTGHOST_H__

#include "Zombie.h"

STATE_ENUM_CHILD_BEGIN(ZombiePumpkinKnightGhostState, ZombieState)
	ZS_PUMPKIN_KNIGHT_GHOST_Float,
	ZS_PUMPKIN_KNIGHT_GHOST_Explode,
STATE_ENUM_END(ZombiePumpkinKnightGhostState);

class ZombiePumpkinKnightGhost : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombiePumpkinKnightGhost, Zombie, RtClass);

public:
	void setGhostGridSpeed(float i_speed) { m_gridSpeed = i_speed; }
	void setGhostStunDuration(float i_dur) { m_stunDuration = i_dur; }
	void setGhostExplodeDamageAmount(float i_damageAmount) { m_explodeDamageAmount = i_damageAmount; }
	void setGhostManifestRect(Rect i_manifestRect);

protected:
	void onZombieInitialize() override;
	void onPlaceOnBoard() override;
	void onApplyCondition(ZombieConditions i_condition) override;
	void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
	bool willDieToShrinking() override { return true; }
	bool ShouldDrawShadow() const override { return false; };
	void onDestroy() override;
	void onUpdate() override;
	void onDraw(class Sexy::Graphics* i_g) override;
	bool hasHeadParticle() const override { return false; }
	bool hasArmParticle() const override { return false; }

    std::string getElectrocutePAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_IMP_SHOCK"; }
    std::string getAshPAMName() const override { return "POPANIM_EFFECTS_ZOMBIE_IMP_ASH"; }

	void updateTargetLoc();
	void updateGhostFacing();
	void tryChangeState();

	void updateGhostPosition();
	void updateGhostInvisibleState();

	void playFloatingAnimation();
	void playExplodeAnimation();

	void blowUpNearby();
	void onExplodeAnimationDone(class StandaloneEffect* i_effect);

	DECLARE_STATE_FUNCTIONS(ZombieState, Float);
	DECLARE_STATE_FUNCTIONS(ZombieState, Explode);

private:
	bool moveToDestination(const float i_destX, const float i_destY);

	RtWeakPtr<BoardEntity> m_owner = nullptr;

	SexyVector3 m_targetLoc;
	float m_gridSpeed = 1.f;
	float m_stunDuration = 1.f;
	float m_explodeDamageAmount = 100.f;
	// The offset of the rect's bottom center relative to the zombie's position
	Rect m_manifestRect = Rect(0, 100, 256, 304);
	pvztime_t m_birdCryTimer = PVZ_EOT();
};

class ZombieAnimRig_PumpkinKnightGhost : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_PumpkinKnightGhost, ZombieAnimRig, RtClass) {}

	bool playSingleAnimation(std::string i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool playLoopAnimation(std::string i_animLabel);

	std::string getFloatAnimLabelName() { return "fly"; }

};

#endif /* _ZOMBIEPUMPKINKNIGHTGHOST_H__ */
