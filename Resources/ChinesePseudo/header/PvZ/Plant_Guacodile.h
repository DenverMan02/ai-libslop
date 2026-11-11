//
//  Plant_Guacodile.h
//  PlantsVersusZombies2
//
//  Created by David Siems on 7/11/14
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Guacodile_h
#define PlantsVersusZombies2_Plant_Guacodile_h

#include "PlantFramework.h"
#include "PlantAnimRig.h"
#include "Projectile.h"

class PlantGuacodile : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantGuacodile, PlantFramework, RtClass);

    void Initialize() override;
	void UpdateUnconditionally() override;
	bool CanApplyPlantfood() override;
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	void ApplyPlantfood() override;
	DamageInfo TakeDamage(const DamageInfo& i_damage) override;
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
	bool TryBlockPush() override;
	GroundEffectType	GetTideEffect() override { return GROUND_EFFECT_Tide_With_Tail; }

	void Trigger();

	bool ShouldClipWithWater() const override;

private:
	bool canAutoTrigger() const;
	Projectile* shootGuacodile(float i_xOffset);
};

class PlantAnimRig_Guacodile : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Guacodile, PlantAnimRig, RtClass);

    bool PlayPreviewAnim(bool bHideLayer = false) override;
    std::vector<std::string> GetHideLayers();
    
protected:
    void onPopAnimInitialized() override;
    void onLevelUpdate() override;
};

class GuacodileProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(GuacodileProjectile, Projectile, RtClass);

	bool OnCollideEntity(BoardEntity* i_entity) override;
	void SetJumpState();
	bool ShouldClipWithWater() const override { return true; }

    void SetIsAvatar(bool i_avatar) { m_IsAvatar = i_avatar; }
    
protected:

private:
	void onProjectileInitialized() override;
	void onUpdate(pvztime_t i_dt) override;
	void onPostLoad() override;

	void onAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);
	void chomp(void);

	pvztime_t m_nextChompTime;

	enum State
	{
		JUMPING,
		MOVING
	};
	State m_state;
	AnimHandle m_animHandle;
    bool       m_turnedAround;
    bool       m_IsAvatar;
};

class GuacodileProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(GuacodileProjectileProps, ProjectilePropertySheet, RtClass);

	GuacodileProjectileProps()
	: ChompsPerSecond(1.0f)
	, DamagePerChomp(100.0f)
	{
		// Do nothing.
	}

	float ChompsPerSecond;
	float DamagePerChomp;
};

#endif
