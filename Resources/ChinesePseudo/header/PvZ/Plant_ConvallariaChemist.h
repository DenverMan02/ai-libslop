/*
 * Plant_ConvallariaChemist.h
 *
 *  Created on: 2017-12-5
 *      Author: Administrator
 */

#ifndef PLANT_CONVALLARIACHEMIST_H_
#define PLANT_CONVALLARIACHEMIST_H_

#include "PlantFramework.h"
#include "Projectile.h"
#include "GridItemAnimation.h"
#include "GameSubSystem.h"

struct PoisonInfo
{
	PoisonInfo()
	{
		PoisonDuration = 1.0f;
		PoisonDamage = 1.0f;
	}
	float PoisonDuration;
	float PoisonDamage;
};

class ConvallariaChemistProps : public CabbagepultProps
{
public:
    RT_CLASS_DEFINE(ConvallariaChemistProps, CabbagepultProps, RtClass);

    ConvallariaChemistProps()
    {
    	AmountToAimLeftOfZombie = 0.33;
    	Level5Rate = 1.0f;
    }

    float AmountToAimLeftOfZombie;
    float Level5Rate;
};

class PlantConvallariaChemist : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantConvallariaChemist, PlantFramework, RtClass);

    void Initialize() override;
    bool CanApplyPlantfood() override;
    void ApplyPlantfood()override;
    void UpdatePlantfood() override;
    void CancelPlantfood() override;
    bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    virtual void PlayAttackAnimation() override;

protected:
    void LaunchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance
                            , bool i_avatar, bool i_plantfood);
private:
    Projectile* launchSpecialProjectile();
	Projectile* launchProjectile(Zombie* targetZombie, GridItem* targetGridItem);
	bool		isValidTargetGridItem(BoardEntityPtr target);
	bool		isValidTargetZombie(BoardEntityPtr target);
	BoardEntityPtr  findNextPlantfoodTarget();
	void		makeSureWeStillHaveAPlantFoodTarget();

    std::vector<RtWeakPtr<BoardEntity>> m_entitiesHitDuringPlantfood;
    RtWeakPtr<BoardEntity> m_nextPlantFoodTarget;
};

class PlantAnimRig_ConvallariaChemist : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_ConvallariaChemist, PlantAnimRig, RtClass);

	void SetIsSuperAttack(bool i_super) { m_isSuperAttack = i_super; }
	bool GetIsSuperAttack() { return m_isSuperAttack; }

protected:
	void onPopAnimInitialized() override;
    std::string getAttackAnimationName() override;
    std::string getPlantFoodMainAnimName() override;
    //std::string getIdleAnimationName() override;
private:
    bool m_isSuperAttack;
};

class ConvallariaChemistProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(ConvallariaChemistProjectileProps, ProjectilePropertySheet, RtClass);

	ConvallariaChemistProjectileProps()
	{
		MaximumStackLevel = 3.0f;
		MaximumStacksPerLevel = 3.0f;
		StacksToAdd = 1.f;
		VenomItemName = "venom";
		BasicVenomRate = 1.0f;
		AdvancedVenomRate = 1.0f;
	};

	float MaximumStackLevel;
	float MaximumStacksPerLevel;
	float StacksToAdd;
	std::vector<PoisonInfo> PoisonInfos;
	std::string VenomItemName;
	float BasicVenomRate;
	float AdvancedVenomRate;
};

class ConvallariaChemistProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ConvallariaChemistProjectile, Projectile, RtClass);
    ConvallariaChemistProjectile()
    : m_avatar(false)
    {}
    SexyVector3 m_TargetPosition;

    void SetIsAvatar(bool i_avatar) { m_avatar = i_avatar; }
    void SetIsPlantfood(bool i_plantfood) { m_plantfood = i_plantfood; }
protected:
    virtual void damageEntity(class BoardEntity* i_entity) override;
    virtual bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;

    bool m_avatar;
    bool m_plantfood;
};

class ConvallariaChemistPlantfoodProjectileProps : public ConvallariaChemistProjectileProps
{
public:
	RT_CLASS_DEFINE(ConvallariaChemistPlantfoodProjectileProps, ConvallariaChemistProjectileProps, RtClass);

	ConvallariaChemistPlantfoodProjectileProps()
	{
		ExplodeDamage = 300.0f;
	};

	float ExplodeDamage;
};

class ConvallariaChemistPlantfoodProjectile : public ConvallariaChemistProjectile
{
public:
    RT_CLASS_DEFINE(ConvallariaChemistPlantfoodProjectile, ConvallariaChemistProjectile, RtClass);

    void damageEntity(class BoardEntity* i_entity) override;
};

class ConvallariaChemistAvatarProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ConvallariaChemistAvatarProjectile, Projectile, RtClass);

    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
};

class ConvallariaChemistSuperProjectile : public ConvallariaChemistProjectile
{
public:
    RT_CLASS_DEFINE(ConvallariaChemistSuperProjectile, ConvallariaChemistProjectile, RtClass);

    void damageEntity(class BoardEntity* i_entity) override;
    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
};

enum GridItemVenomState
{
    PVZ_BEGIN_ENUM(VENOMSTATE_),
    VENOMSTATE_UNKNOWN,
    VENOMSTATE_RESETTING,
    VENOMSTATE_IDLE,
    VENOMSTATE_DEAD,
    PVZ_END_ENUM(VENOMSTATE_)
};

class GridItemVenom : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemVenom, GridItemAnimation, RtClass);

    GridItemVenom();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(VENOMSTATE_IDLE); }
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(GridItemVenomState i_state);
    void applyVenom();

    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }

private:
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    pvztime_t m_creationTime;
    GridItemVenomState m_state;
};

class GridItemVenomProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemVenomProps, GridItemAnimationProps, RtClass);
    GridItemVenomProps()
    : Lifetime(1.0)
    , VenomTime(2.0)
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
    pvztime_t VenomTime;
    std::vector<std::string> ZombieBlacklist;
    std::vector<float> VenomInfos;
};

#endif /* PLANT_CONVALLARIACHEMIST_H_ */
