#ifndef PlantsVersusZombies2_Plant_Cypripedium_h
#define PlantsVersusZombies2_Plant_Cypripedium_h

#include "DamageInfo.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "GridItemBreakableTarget.h"

#pragma mark - CypripediumProps

class CypripediumProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(CypripediumProps, PlantPropertySheet, RtClass);

	CypripediumProps()
	{
		ProjectileTimeOfFlight = 1.2;
		ProjectileLobHeight = 350;
		SkillRate2 = 0.5;
	};

	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
	float SkillRate2;
};

#pragma mark - CypripediumProjectileProps

class CypripediumProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(CypripediumProjectileProps, ProjectilePropertySheet, RtClass);

	CypripediumProjectileProps()
	{
		PoisonDPS = 100;
	};

	float PoisonDPS;
};

#pragma mark - CypripediumProjectile

class CypripediumProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(CypripediumProjectile, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};


#pragma mark - CypripediumThickProjectile

class CypripediumThickProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(CypripediumThickProjectile, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};


#pragma mark - CypripediumPlantfood

class CypripediumPlantfood : public Projectile
{
public:
	RT_CLASS_DEFINE(CypripediumPlantfood, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};


#pragma mark - CypripediumPlantfoodAvatar

class CypripediumPlantfoodAvatar : public Projectile
{
public:
	RT_CLASS_DEFINE(CypripediumPlantfoodAvatar, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};


#pragma mark - CypripediumLv5

class CypripediumLv5 : public Projectile
{
public:
	RT_CLASS_DEFINE(CypripediumLv5, Projectile, RtClass);

	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
};


#pragma mark - PlantCypripedium

class PlantCypripedium : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantCypripedium, PlantFramework, RtClass);
	
	virtual void Initialize() override;
    virtual void UpdateActions() override;

	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void CancelPlantfood() override;
    virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
	virtual Projectile*	Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
protected:
	void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);

	int m_actionIdx;
};


#pragma mark - PlantAnimRig_Cypripedium

class PlantAnimRig_Cypripedium : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Cypripedium, PlantAnimRig, RtClass);

	PlantAnimRig_Cypripedium();
	~PlantAnimRig_Cypripedium();

	void SetAttackMode(int i_mode);
	void SetIsLevel5(bool i_flag);
private:
	std::string getIdleAnimationName() override;
    std::string getAttackAnimationName() override;
	std::string getPlantFoodMainAnimName() override;
	int m_mode;
	bool m_isLv5;
};

#endif