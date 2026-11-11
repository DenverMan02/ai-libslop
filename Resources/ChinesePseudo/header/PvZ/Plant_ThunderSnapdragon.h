/*
 * Plant_ThunderSnapdragon.h
 *
 *  Created on: 2019-7-9
 *      Author: Administrator
 */

#ifndef PLANT_THUNDERSNAPDRAGON_H_
#define PLANT_THUNDERSNAPDRAGON_H_

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "GridItemAnimation.h"

class Zombie;

class ThunderSnapdragonProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ThunderSnapdragonProps, PlantPropertySheet, RtClass);

	ThunderSnapdragonProps()
	{
		PurpleBallRate = 1.0f;
		ImprovedPurpleBallBonus = 1.0f;
		FieldItemName = "field";
        PlantfoodRate = 0.2f;
	}

	float PurpleBallRate;
	float ImprovedPurpleBallBonus;
	std::string FieldItemName;
    float PlantfoodRate;// level5 special attack ratio
};

class BlueBallProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(BlueBallProjectileProps, ProjectilePropertySheet, RtClass);

	BlueBallProjectileProps()
	{
		StuckRate = 1.0f;
		StuckDuration = 1.0f;
		ImpactDamage = 0.0f;
	}

	float StuckRate;
	float StuckDuration;
	float ImpactDamage;
};

class BlueBallProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(BlueBallProjectile, Projectile, RtClass);

private:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	void MarkCenterTarget(BoardEntity* i_entity);
	void DoSplashDamage(int i_sourceCol, int i_sourceRow);
};

class PlantAnimRig_ThunderSnapdragon : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_ThunderSnapdragon, PlantAnimRig, RtClass);

protected:
    std::string getPlantFoodMainAnimName() override;

public:
    bool PlayLevel5Attack();

public:
    float m_plantfoodRate = 0.2f;// the ratio if level 5 can do special attack
    bool  m_isNewPlantfood = false;// flag that if has start the special attack
};

class PlantThunderSnapdragon : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantThunderSnapdragon, PlantFramework, RtClass);

	bool			CanApplyPlantfood() override;
	Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	virtual bool	OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	virtual void	onStandaloneEffectFinishedCallback(class StandaloneEffect* i_effect) override;
    bool	FindTargetAndFire(PlantWeapon i_plantWeapon) override;
private:
    bool CanFindTarget(PlantWeapon i_plantWeapon);
};

enum GridItemElectricFieldState
{
    PVZ_BEGIN_ENUM(ELECTRICFIELDSTATE_),
    ELECTRICFIELDSTATE_UNKNOWN,
    ELECTRICFIELDSTATE_RESETTING,
    ELECTRICFIELDSTATE_IDLE,
    ELECTRICFIELDSTATE_DEAD,
    PVZ_END_ENUM(ELECTRICFIELDSTATE_)
};

class GridItemElectricField : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemElectricField, GridItemAnimation, RtClass);

    GridItemElectricField();
    int	CalcRenderOrder() const override;

    void ResetTimer();
    void SetIdle() { setState(ELECTRICFIELDSTATE_IDLE); }
    void SetIsAvatar(bool i_avatar) { m_avatar = i_avatar; }
    void SetDamageRate(float i_damageRate) { m_damageRate = i_damageRate; }
    void SetStuckedExtend(float i_stuckedExtend) { m_stuckedExtend = i_stuckedExtend; }
protected:
    void onGridItemInitialize() override;
    void onUpdate() override;

    void setState(GridItemElectricFieldState i_state);
    void tryAffectZombies();

    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    void onResetFinished(const std::string &i_animName);
    void onDeadFinished(const std::string &i_animName);

private:
    bool isZombieTypeBlacklisted(const std::string& zombieTypeName);
    pvztime_t m_creationTime;
    GridItemElectricFieldState m_state;
    pvztime_t m_affectTime;
    bool m_avatar;
    float m_damageRate;
    float m_stuckedExtend;
};

class GridItemElectricFieldProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemElectricFieldProps, GridItemAnimationProps, RtClass);
    GridItemElectricFieldProps()
    : Lifetime(1.0)
    , EffectRectRight(1)
    , EffectRectLeft(1)
    , EffectRectTop(1)
    , EffectRectBottom(1)
    , ElectricDamage(0.0f)
    , AffectInterval(1.0f)
    , AvatarElectricDamage(0.0f)
    {}

    int EffectRectRight;
    int EffectRectLeft;
    int EffectRectTop;
    int EffectRectBottom;

    pvztime_t Lifetime;
    std::vector<std::string> ZombieBlacklist;
    float ElectricDamage;
    float AvatarElectricDamage;
    float AffectInterval;
};

//////////////////////
/// level 5 effect
//////////////////////
class ThunderSnapdragonFlyDragon : public FlyingObject
{
public:
    RT_CLASS_DEFINE(ThunderSnapdragonFlyDragon, FlyingObject, RtClass);

    ThunderSnapdragonFlyDragon();
    virtual ~ThunderSnapdragonFlyDragon();

    void onUpdate() override;
    void InitParam(Plant* parent, const std::string& effectPam, RenderLayer layer) override;

    void SetDamage(float damage) { _damage = damage; }
    void SetStuckedExtend(float i_stuckedExtend) { m_stuckedExtend = i_stuckedExtend; }
    void SetReturn(bool i_flag) { m_dragonReturn = i_flag; }

protected:
    void DoAttack(Sexy::Point point);
    SexyVector3 GetAttachPosition() override;

private:
    float _damage;// thunder damage.
    float m_stuckedExtend;
    float m_dragonReturn;
};


#endif /* PLANT_THUNDERSNAPDRAGON_H_ */
