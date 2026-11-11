/*
 * Plant_ShadowVanilla.h
 *
 *  Created on: 2020-8-31
 *      Author: zhousen
 */

#ifndef PLANT_SHADOWVANILLA_H_
#define PLANT_SHADOWVANILLA_H_

#include "PlantFramework.h"
#include "RtDb.h"
#include "BoardEntity.h"
#include "Projectile.h"
#include "Plant.h"
#include "RtObject.h"
#include "Zombie.h"
#include <string>
#include "GameSubSystem.h"
#include "FlyingObject.h"

/// 
/// enum
///
enum {
    SHADOWVANILLA_PROJECTILE_NORMAL = 0,// normal bullet
    SHADOWVANILLA_PROJECTILE_SHADOW = 1,// shadow status bullet
    SHADOWVANILLA_PROJECTILE_HURRICANE = 2,// hurricane bullet (die impact)
    SHADOWVANILLA_PROJECTILE_SHADOW_HURRICANE = 3,// shadow hurricane bullet (die impact)
    SHADOWVANILLA_PROJECTILE_SPECIAL_HURRICANE = 4,// special hurricane after shadow avatar plantfood hit (not die impact)
    SHADOWVANILLA_PROJECTILE_SHADOWMIST = 5,// shadow status 4 count hit special shadow mist attack
    SHADOWVANILLA_PROJECTILE_SHADOW_THREELINES = 6,// shadow plantfood first attack 3 lines (not die impact)
};

/// 
/// ShadowVanilla Anim Rig
///
class PlantAnimRig_ShadowVanilla : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_ShadowVanilla, PlantAnimRig, RtClass);
    PlantAnimRig_ShadowVanilla();

    virtual std::string getIdleAnimationName() override;
    virtual std::string getAttackAnimationName() override;
	virtual std::string getPlantFoodMainAnimName() override;

    // void SetPlantFramework(class PlantShadowvanilla* ptr) { _plantFramework = ptr; }
    void SetPlantPtr(PlantPtr ptr) { _plantPtr = ptr; }
	bool PlayPreviewAnim(bool bHideLayer = false) override;

protected:
    bool IsInShadowStatus();
    int GetShadowChargeCount();

protected:
    // class PlantShadowvanilla* _plantFramework;
    PlantPtr _plantPtr;
};

///
/// PlantShadowVanillaProps
///
class PlantShadowVanillaProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PlantShadowVanillaProps, PlantPropertySheet, RtClass);
    PlantShadowVanillaProps();

    int ShadowAvatarHurricaneDamage;// cross hurricane damage
    std::vector<float> WhirlPoolRatios;// create whirlpool ratios
    int PlantfoodHurricaneDamage;// 3x3 hurricane damage
    float PlantfoodHurricaneDuration;// 3x3 hurricane duration
    int ShadowMistDamage;// shadowmist damage
    float ShadowMistDamageRatio;// shadowmist damage ratio
    float ShadowMistDuration;// shadowmist duration
    int Level5HurricanDamage;// shadow mist double attack hurricane damage
    float Level5HurricaneDuration;//shadow mist double attack hurricane duration
    float Level5AttachShadowMistDamageRatio;// attach shadow mist damageratio
    float Level5AttachShadowMistDuration;// attach shadow mist duration
    // shadow plantfood attack object
    int ShadowHurricaneDamage;// once attack damage
    int ShadowHurricaneShadowMistDamage;// shadowmist once atack damage
    float ShadowHurricaneShadowMistDuration;// shadowmist duration
    float ShadowHurricaneShadowMistDamageRatio;// shadowmist damage ratio
};

///
/// PlantShadowvanilla
///
class PlantShadowvanilla : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantShadowvanilla, PlantFramework, RtClass);
    PlantShadowvanilla();
    ~PlantShadowvanilla();

    void Initialize() override;
    void UpdateActions() override;
    bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
    bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	void onAnimStoppedCallback(const std::string& i_animCommand) override;
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

    bool IsBoosted();// check is in shadow status
    int GetShadowChargeCount() { return _shadowChargeCount; }
    void UpdateBoostLayer(bool enable);

protected:
    void LaunchSpecialAttack(bool isInShadowStatus, bool isAvatar);// launch plantfood attack
    void LaunchShadowHurricane();// launch three lines shadowhurricane object
    void LaunchShadowSecondPlantfood();

protected:
    int _shadowChargeCount;// shadow charget count
    bool _isShadowStatus;// cache shadow status
};

///
/// ShadowVanilla Projectile
///

// normal projectile
class ShadowVanillaNormalProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ShadowVanillaNormalProjectile, Projectile, RtClass);
    ShadowVanillaNormalProjectile();

    virtual void onSetInstigator(BoardEntity* i_instigator) override;
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;

protected:
    int _level;
    float _level5AttachShadowMistDamageRatio;
    float _level5AttachShadowMistDuration;
};

// hurricane projectile
class ShadowVanillaHurricaneProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ShadowVanillaHurricaneProjectile, Projectile, RtClass);
    ShadowVanillaHurricaneProjectile();

    virtual void onSetInstigator(BoardEntity* i_instigator) override;
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;

    void AttachShadowMist(bool shouldAttach) { _attachShadowMist = shouldAttach; }

protected:
    void CrossFireHurricane(BoardEntity* i_entity);

protected:
    int _level;// plant level
    bool _isAvatar;// plant avatar

    bool _attachShadowMist;// should touch shadowmist
    float _shadowMistDamageRatio;// shadowmist damage ratio
    float _shadowMistDuration;// shadowmist duration

    bool _isInShadowStatus;// is in shadow status
    int _hurricaneDamage;// 3x3 hurricane damage
    float _hurricaneDuration;// 3x3 hurricane duration
    int _shadowAvatarHurricaneDamage;// shadow avatar hurricane damage
    ProjectilePropertySheetPtr _projectile;// cross fire projectile property
	std::vector<BoardEntityPtr> _targetsAlreadyHit;// hit list
};

// special hurricane projectile (not die impact)
class ShadowVanillaSpecialHurricaneProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ShadowVanillaSpecialHurricaneProjectile, Projectile, RtClass);
    ShadowVanillaSpecialHurricaneProjectile();

    virtual void onSetInstigator(BoardEntity* i_instigator) override;
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;

    void SetShadowMistParam(float damageRatio, float duration);

protected:
    int _level;
	std::vector<BoardEntityPtr> _targetsAlreadyHit;// hit list
    float _shadowMistRatio;
    float _shadowMistDuration;
};

// shadow mist projectile
class ShadowVanillaShadowMistProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(ShadowVanillaShadowMistProjectile, Projectile, RtClass);
    ShadowVanillaShadowMistProjectile();

    virtual void onSetInstigator(BoardEntity* i_instigator) override;
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;

protected:
    int _level;
    int _shadowMistDamage;
    float _shadowMistDamageRatio;
    float _shadowMistDuration;
    int _hurricaneDamage;
    float _hurricaneDuration;
	std::vector<BoardEntityPtr> _targetsAlreadyHit;// hit list
};


/// 
/// effect griditem
///

// zombie death whirlpool griditem
class GridItemShadowVanillaWhirlpool : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemShadowVanillaWhirlpool, GridItemAnimation, RtClass);
    GridItemShadowVanillaWhirlpool();

    void InitParams(int level);
    float GetDamageRatio();

protected:
    void onUpdate() override;
    void DamageEntity();
    void OnAnimStoppedCallback(const std::string& i_animCommand);

protected:
    int _level;
    pvztime_t _startTime;
    float _damageRatio;
    float _duration;
    bool _playEndAnim;
};

class GridItemShadowVanillaWhirlpoolProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemShadowVanillaWhirlpoolProps, GridItemAnimationProps, RtClass);
    GridItemShadowVanillaWhirlpoolProps();

    std::vector<SexyVector2> WhirlPoolParams;// x = DamageRatio, y = Duration
};

// level5 zombie hurricane griditem
class GridItemShadowVanillaHurricane : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemShadowVanillaHurricane, GridItemAnimation, RtClass);
    GridItemShadowVanillaHurricane();

	int CalcRenderOrder() const override;

    void InitParams(int damage, float duration, bool hasShadowEnergy = false);

protected:
    void onUpdate() override;
    void DamageEntity();

protected:
    pvztime_t _startTime;
    int _damage;
    float _duration;
    bool _shouldCreateShadowEnergy;// after this griditem die, craete a shadowenergy griditem
};

// avatar normal status shadow energy griditem
class GridItemShadowVanillaShadowEnergy : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GridItemShadowVanillaShadowEnergy, GridItemAnimation, RtClass);
    GridItemShadowVanillaShadowEnergy();
    
    virtual void KillGridItem() override;

protected:
	void onGridItemInitialize() override;
    void onUpdate() override;
    void DamageEntity();

protected:
    pvztime_t _startTime;
    int _damage;
    float _duration;
    
};

class GridItemShadowVanillaShadowEnergyProps : public GridItemAnimationProps
{
public:
    RT_CLASS_DEFINE(GridItemShadowVanillaShadowEnergyProps, GridItemAnimationProps, RtClass);
    GridItemShadowVanillaShadowEnergyProps();

    int Damage;
    float Duration;
};


/// 
/// Flying Hurricane Object
/// plantfood in shadow status fire projectile
///
class ShadowVanillaHurricaneObject : public FlyingObject
{
public:
    RT_CLASS_DEFINE(ShadowVanillaHurricaneObject, FlyingObject, RtClass);

    ShadowVanillaHurricaneObject();
    virtual ~ShadowVanillaHurricaneObject();

    void onUpdate() override;
    void InitParam(Plant* parent, const std::string& effectPam, RenderLayer layer) override;

    void SetDamage(float damage) { _damage = damage; }
    void SetDamages(int onceDamage, int mistOnceDamage, float mistDuration, float mistDamageRatio);

protected:
    void DoAttack(Sexy::Point point);
    SexyVector3 GetAttachPosition() override;

private:
    float _damage;// hurricane damage.
    int _onceDamage;// once attack damage
    int _mistOnceDamage;// shadowmist once atack damage
    float _mistDuration;// shadowmist duration
    float _mistDamageRatio;// shadowmist damage ratio
};

///
/// whirlpool statistics system
///
class ShadowVanillaWhirlPoolSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(ShadowVanillaWhirlPoolSubSystem, GameSubSystem, RtClass);

	ShadowVanillaWhirlPoolSubSystem();
	virtual ~ShadowVanillaWhirlPoolSubSystem();

    void SetPlantLevel(int level) { _plantLevel = level; }
    void InitWhirlPoolRatio(std::vector<float> ratios);

protected:
    void CreateWhirlPool(int x, int y);
    void ZombieDied(Zombie* i_zombie, const DamageInfo* i_deathBlow);
    bool CheckCreateWhirlPool(float ratio);

	std::vector<GridItemShadowVanillaWhirlpool*> _container;// maybe no use
    int _plantLevel;// shadowvanilla level
    std::vector<float> _whirlPoolRatios;// create whirlpool ratio
};

#endif /* PLANT_SHADOWVANILLA_H_ */
