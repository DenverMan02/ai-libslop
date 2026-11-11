			//
//  ZombieEightiesGlitter.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 7/13/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieEightiesGlitter__
#define __PlantsVersusZombies2__ZombieEightiesGlitter__

#include "DamageInfo.h"
#include "PlatformAutodetect.h"
#include "ZombieEnums.h"
#include "Zombie.h"

class ZombieEightiesGlitter : public Zombie
{
public:
	RT_CLASS_DEFINE(ZombieEightiesGlitter, Zombie, RtClass);
	ZombieEightiesGlitter();

protected:
	Rect calcRainbowRect();

	void StartJamming() override;
	void StopJamming() override;
	std::string GetJamStyle()override;

	void updateState_Eat() override;
	void updateState_Idle() override;

	void onPlaceOnStreet() override;

private:
	static const float kExpireSoonAfterOutOfRange;
	static const float kGlitterApplicationCooldown;

	OVERRIDE_STATE_ONEXIT(ZombieState, RiseFromGround);
	
	void addRainbowEffect(std::string effectName, std::string animName, bool isFront, bool playOnce);
	bool shouldHaveRainbowTrail();
	bool shouldKillRainbowTrail();
	void onUpdate() override;
	void makeZombiesInTrailInvincible();
	bool shouldZombieBeInvincible(Zombie* zombie);
	void setupRainbowEffects();
	void skateOverThis(BoardEntity* target);
	void createHitEffectAt(BoardEntity* target);
	void startRainbowTrail();
	void endRainbowTrail();
	bool areRainbowIntroEffectsDone();

	pvztime_t m_lastApplicationTime;
	bool m_isMyJamOn;
	bool m_isStreetZombie;
	bool m_isRainbowEffectShowing;
};

class ZombieEightiesGlitterProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieEightiesGlitterProps, ZombiePropertySheet, RtClass);

	ZombieEightiesGlitterProps()
		: JamStyle("jam_pop")
		, RainbowTrailLength(200)
	{}

	std::string JamStyle;
	int RainbowTrailLength;

};

//
//  AnimRig!
//

#include "RtObject.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_EightiesGlitter : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_EightiesGlitter, ZombieAnimRig, RtClass);

private:
	const std::vector<std::string>& getHeadLayerNames() override;
	const std::vector<std::string>& getArmLayerNames() override;
	const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif /* defined(__PlantsVersusZombies2__ZombieEightiesGlitter__) */
