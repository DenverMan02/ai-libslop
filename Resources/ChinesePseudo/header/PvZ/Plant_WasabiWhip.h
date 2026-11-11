#ifndef __PLANT_WASABIWHIP_H__
#define __PLANT_WASABIWHIP_H__

#include "ComponentWarmingRadius.h"
#include "MeleePlantTargeter.h"
#include "Plant.h"
#include "PlantFramework.h"
#include "Rect.h"
#include "RtObject.h"
#include "TimeMgr.h"
#include <string>
#include "PlantIdleAwareAnimRig.h"
#include "PopAnimRig.h"
#include "Projectile.h"

class GridItem;
class IdleAnimationSelector;

enum WasabiWhipState {
	WASABISTATE_IDLE = STATE_FRAMEWORK_BEGIN,
	WASABISTATE_ATTACKING,
	WASABISTATE_PLANTFOOD,
	WASABISTATE_SUPERSKILL,
};

#pragma mark
class WasabiWhipProps: public PlantPropertySheet {
public:
	RT_CLASS_DEFINE(WasabiWhipProps, PlantPropertySheet, RtClass);

	ComponentWarmingRadiusProps NormalWarmingRadius;
	ComponentWarmingRadiusProps PlantfoodWarmingRadius;

	float TargetCount;
	float burnDuration;
	float burnDps;
	float level5Rare;
};

class PlantAnimRig_WasabiWhip: public PlantIdleAwareAnimRig {
public:
	RT_CLASS_DEFINE(PlantAnimRig_WasabiWhip, PlantIdleAwareAnimRig, RtClass);
	virtual ~PlantAnimRig_WasabiWhip() {
	}

	bool PlayIdleLooped()
override	;
	bool PlayPunchAttack(MeleePlantTargeter::TargetDirection i_attackType, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});

protected:
	void onPopAnimInitialized() override;

private:
	std::string getAttackAnimLabel(MeleePlantTargeter::TargetDirection i_attackType);
};

class WasabiWhipProjectile: public Projectile {
public:
	RT_CLASS_DEFINE(WasabiWhipProjectile, Projectile, RtClass);
private:
	void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity) override;
	bool zombieIsBlacklisted(const Zombie* i_zombie) const;
};

class PlantWasabiWhip: public PlantFramework {
public:
	RT_CLASS_DEFINE(PlantWasabiWhip, PlantFramework, RtClass);

	void Initialize()
override	;
	void UpdateActions() override;
	virtual void DoSpecial(int i_extraParam) override;
	bool CanApplyPlantfood() override {return true;};
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	void UpdatePlantfood() override;

	DamageTypeFlags GetDamageFlags(PlantWeapon i_plantWeapon) override;
	void burnZombie(Zombie* i_zombie);

	void OnCoinEffectFinished(const std::string& i_animLabelName);
	Projectile* Fireball();

	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

	bool isCanFireBall();
private:
	bool findTargetsAndPlayAttackAnim();

	void activatePfWarmingRadius();
	void activateNormalWarmingRadius();
	void activateWarmingRadius(ComponentWarmingRadiusProps props);
	DamageInfo getDamage(PlantWeapon i_plantWeapon);
	void updatePfEndTime();

	void attack();
	bool tryToDamageAdjacentTargets();
	bool tryDoAvatarDamageAdjacentTargets();

	// Serialized
	pvztime_t m_plantfoodDamageEndTime;
	pvztime_t m_level5DamageEndTime;
	RtWeakPtr<ComponentWarmingRadius> m_warmingRadius;
	MeleePlantTargeter::TargetDirection m_attackDirection;

};

#endif
