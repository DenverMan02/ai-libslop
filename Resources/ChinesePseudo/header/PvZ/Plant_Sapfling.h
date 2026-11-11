#ifndef __PLANT_SAPFLING_H__
#define __PLANT_SAPFLING_H__

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RestrictionSet.h"
#include "RtDb.h"
#include "RtObject.h"
#include "Zombie.h"
#include "GridItemAnimation.h"
#include "PlantPropertySheet.h"

namespace Sexy {
class SexyVector3;
}  // namespace Sexy

class PlantSapfling : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSapfling, PlantFramework, RtClass);

    bool CanApplyPlantfood() override;
    bool	 CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
	void DoSpecial(int i_extraParam = 0) override;
	Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	
	//don't target grid items
	GridItemPtr FindTargetDamageableGridItem(Rect& i_gridRect, PlantWeapon i_plantWeapon) override { return GridItemPtr(); }
protected:
	void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);

private:
    void launchSpecialProjectile(SexyVector3 i_targetesLoc, ZombiePtr i_targetZombie, const RtWeakPtr<class BoardEntity>& i_target);
    const bool isValidSapLocation(const int i_gridX, const int i_gridY);
};

class SapflingProps : public CabbagepultProps
{
public:
	RT_CLASS_DEFINE(SapflingProps, CabbagepultProps, RtClass);
	
	SapflingProps()
	{
		PlantfoodPineconeCount = 4;
        AmountToAimLeftOfZombie = 0.33;
	}

	int PlantfoodPineconeCount;
    float AmountToAimLeftOfZombie;
	ZombieRestrictionSet TargetableZombieTypes;
    std::vector<float> AmberRate;
};

class PlantAnimRig_Sapfling : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Sapfling, PlantAnimRig, RtClass);
	
	std::string getPlantFoodOnAnimName() override { return "plantfood_start"; }
	std::string getPlantFoodMainAnimName() override { return "plantfood_loop"; }
	std::string getPlantFoodOffAnimName() override { return "plantfood_end"; }
};

class SapflingProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(SapflingProjectileProps, ProjectilePropertySheet, RtClass);

	SapflingProjectileProps()
	{
		SapItemName = "sap";
	}
	
	std::string SapItemName;
};

class SapflingProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(SapflingProjectile, Projectile, RtClass);
    SapflingProjectile() { m_amberRate = 0; }
	bool OnCollideGround() override;
    void SetAmberRate(float rate) { m_amberRate = rate; }
	SexyVector3 m_TargetPosition;
private:
    float m_amberRate;
};


enum GridItemSapState
{
	PVZ_BEGIN_ENUM(SAPSTATE_),
	SAPSTATE_UNKNOWN,
	SAPSTATE_SPAWNING,
    SAPSTATE_RESETTING,
	SAPSTATE_IDLE,
	SAPSTATE_FADING,
	SAPSTATE_DEAD,
    PVZ_END_ENUM(SAPSTATE_)
};

class GridItemSap : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemSap, GridItemAnimation, RtClass);

	GridItemSap();
	int	CalcRenderOrder() const override;

    void ResetTimer();
    void OnWashedOut();
    void SetAmberRate(float rate) { m_amberRate = rate; }
protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	
    void setState(GridItemSapState i_state);
	void applySap();
    void ApplyAmber();

	void onSplatFinished(const std::string &i_animName);
	void onSplatFaded(const std::string &i_animName);
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

private:
	bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    void UpdateAmberZombie();
	pvztime_t m_creationTime;
	GridItemSapState m_state;
    float m_amberRate;
    std::vector<ZombiePtr> m_amberZombie;
	float m_slowRate;
};

class GridItemSapProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemSapProps, GridItemAnimationProps, RtClass);
	GridItemSapProps()
	: Lifetime(1.0)
	, SapTime(2.0)
    , AmberTime(3.0)
    , EffectRectRight(0)
    , EffectRectLeft(0)
    , EffectRectTop(0)
    , EffectRectBottom(0)
	{}

    int EffectRectRight;
    int EffectRectLeft;
    int EffectRectTop;
    int EffectRectBottom;
    
	pvztime_t Lifetime;
	pvztime_t SapTime;
    pvztime_t AmberTime;
	std::vector<std::string> ZombieBlacklist;
};

#endif // __PLANT_CABBAGEPULT_H__
