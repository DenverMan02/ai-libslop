//
//  Plant_EggplantNinja.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-12-23.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_EggplantNinja_h
#define PlantsVersusZombies2_Plant_EggplantNinja_h

#include "PlantFramework.h"
#include "PlantUtils.h"
#include "ActionSubSystem.h"
#include "Projectile.h"

class EggplantShuriken : public Projectile
{
public:
	enum ShurikenTrajectory
	{
		E_TOP_HIGH,
		E_HIGH,
		E_NORMAL,
		E_LOW,
		E_BOTTOM_LOW
	};

	RT_CLASS_DEFINE(EggplantShuriken, Projectile, RtClass);

	EggplantShuriken(): slot(0), flightTime(0.f){}
	void SetTrajectory(ShurikenTrajectory trajectory, bool plantfood);

	uint32 slot;
	float flightTime;

protected:
	virtual void onFlyToTargetDone(BoardEntity * target);
	virtual void onFlyBackDone(BoardEntity * target);
	void onPlantDie(Plant* plant);

	void SetTrajectoryTopHigh();
	void SetTrajectoryHigh();
	void SetTrajectoryNormal();
	void SetTrajectoryLow();
	void SetTrajectoryBottomLow();

protected:
	SexyVector3 initPos;
	ccBezierConfig go;
	ccBezierConfig back;
	bool bPlantFoodShuriken;
};

class EggplantSuperShuriken : public EggplantShuriken
{
public:
	RT_CLASS_DEFINE(EggplantSuperShuriken, EggplantShuriken, RtClass);
};

class EggplantStormShuriken : public EggplantShuriken
{
public:
	RT_CLASS_DEFINE(EggplantStormShuriken, EggplantShuriken, RtClass);

	bool OnCollideEntity(BoardEntity* i_entity) override;

protected:
	void onFlyBackDone(BoardEntity * target) override;
};

class EggplantLightningShuriken : public EggplantShuriken
{
public:
	RT_CLASS_DEFINE(EggplantLightningShuriken, EggplantShuriken, RtClass);
};

class EggplantBombShuriken : public EggplantShuriken
{
public:
	RT_CLASS_DEFINE(EggplantBombShuriken, EggplantShuriken, RtClass);

	bool OnCollideEntity(BoardEntity* i_entity) override;
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;

protected:
	bool hasExplode = false;
};

class EggplantSepcialShurikenProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(EggplantSepcialShurikenProps, ProjectilePropertySheet, RtClass);

	float ExDamage;
};

class EggplantNinjaPropertySheet : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(EggplantNinjaPropertySheet, PlantPropertySheet, RtClass);
    
    EggplantNinjaPropertySheet() : Level2SkillRate(0.2f), Level3SkillRate(0.4f), Level4SkillRate(0.1f) {}
    
    float ProjectileTimeOfFlight;

    float Level2SkillRate;
    float Level3SkillRate;
    float Level4SkillRate;
    float Level5SkillRate;
};



class PlantEggplantNinja : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantEggplantNinja, PlantFramework, RtClass);
    
	virtual void Initialize() override;

	virtual bool CanApplyPlantfood() override;

	void PlayAttackAnimation() override;
	void PlayShurikenBack(bool level5Shuriken);

	virtual bool		FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile* Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

	virtual void DoSpecial(int i_extraParam = 0) override;

	void ResetShurikenSlot(uint32 slotIndex);

protected:
	enum ShurikenState
	{
		E_SHURIKEN_READY,
		E_SHURIKEN_LAUNCH,
		E_SHURIKEN_FIRED,
	};

	std::vector<ShurikenState> m_shuriken;

	void onAnimStoppedCallback(const std::string& i_animLabel) override;

private:
	int m_attackCount;
	float m_boostSkill;
};

class PlantAnimRig_EggplantNinja : public PlantAnimRig
{
public:
    
	RT_CLASS_DEFINE(PlantAnimRig_EggplantNinja, PlantAnimRig, RtClass);
    
	void SetIdleAnimation(const std::string& idle) { m_idle = idle; }

private:
    std::string getIdleAnimationName() { return m_idle; }
    std::string getPlantFoodOnAnimName() override;
    std::string getPlantFoodMainAnimName() override;
    std::string getPlantFoodOffAnimName() override;

private:
    std::string m_idle = "idle";
};

#endif
