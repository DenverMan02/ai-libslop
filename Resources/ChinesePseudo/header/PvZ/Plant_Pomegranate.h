/*
 * Plant_Pomegranate.h
 *
 *  Created on: 2019-11-12
 *      Author: zhousen
 */

#ifndef PLANT_POMEGRANATE_H_
#define PLANT_POMEGRANATE_H_

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "GameSubSystem.h"
#include "PlantUtils.h"

// projectile type
enum PomegranateJewelerProjectileType {
    PomegranateJeweler_Proj_Invalid = -1,
    PomegranateJeweler_Proj_One,
    PomegranateJeweler_Proj_Two,
    PomegranateJeweler_Proj_Three,
    PomegranateJeweler_Proj_Big,
    PomegranateJeweler_Proj_Small,
    PomegranateJeweler_Proj_Giant,
    PomegranateJeweler_Proj_Absorb,
    PomegranateJeweler_Proj_Max,
};

///////////////////////////////////////
/// pomegranate Jeweler projectile
///////////////////////////////////////
class PomegranateJewelerOneProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PomegranateJewelerOneProjectile, Projectile, RtClass);
    
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    void InitialSetPosition(const float x, const float y, const float z) override;

protected:
    void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;

private:
    PomegranateJewelerProjectileType _type = PomegranateJeweler_Proj_One;
    ProjectilePropertySheetPtr _projectile;
};

class PomegranateJewelerTwoProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PomegranateJewelerTwoProjectile, Projectile, RtClass);
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    void InitialSetPosition(const float x, const float y, const float z) override;
    
private:
    PomegranateJewelerProjectileType _type = PomegranateJeweler_Proj_Two;
    ProjectilePropertySheetPtr _projectile;
};

class PomegranateJewelerThreeProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PomegranateJewelerThreeProjectile, Projectile, RtClass);
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    void InitialSetPosition(const float x, const float y, const float z) override;
    
private:
    PomegranateJewelerProjectileType _type = PomegranateJeweler_Proj_Three;
    ProjectilePropertySheetPtr _projectile;
};

class PomegranateJewelerBigProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PomegranateJewelerBigProjectile, Projectile, RtClass);
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    
private:
    PomegranateJewelerProjectileType _type = PomegranateJeweler_Proj_Big;
};

class PomegranateJewelerSmallProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PomegranateJewelerSmallProjectile, Projectile, RtClass);
    virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    void InitialSetPosition(const float x, const float y, const float z) override;
    void SetFirstBulletType(PomegranateJewelerProjectileType type) {
        _firstBulletType = type;
    }

protected:
    void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;

private:
    PomegranateJewelerProjectileType _type = PomegranateJeweler_Proj_Small;
    PomegranateJewelerProjectileType _firstBulletType;
    float _attackRatio;
    std::vector<float> _firstBulletDamageList;
};

class PomegranateJewelerGiantProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PomegranateJewelerGiantProjectile, Projectile, RtClass);
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    void InitialSetPosition(const float x, const float y, const float z) override;

private:
    bool CheckFatalDamage(Zombie* ptr);
    void FatalKill(Sexy::Point grid);
    
private:
    PomegranateJewelerProjectileType _type = PomegranateJeweler_Proj_Giant;
    int _stunTime;
};

class PomegranateJewelerAbsorbProjectile : public Projectile
{
public:
    RT_CLASS_DEFINE(PomegranateJewelerAbsorbProjectile, Projectile, RtClass);
	virtual bool OnCollideEntity(BoardEntity* i_entity) override;
    
protected:
    void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;

private:
    void AbsorbZombies(Sexy::Point pos);
    
private:
    PomegranateJewelerProjectileType _type = PomegranateJeweler_Proj_Absorb;
};

///////////////////////////////////////
/// pomegranate Jeweler proper
///////////////////////////////////////
class PlantPomegranateJewelerProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PlantPomegranateJewelerProps, PlantPropertySheet, RtClass);
    PlantPomegranateJewelerProps();

    float ShootTwoRatio;// the ratio for shooting proj two
    float ShootThreeRatio;// the ratio for shooting proj three
    float ShootBigRatio;// the ratio for shooting proj big
    int ShootThreeTimes;// how many times can shoot proj three after proj big
    float GiantGemStunTime;// giant projectile make zombie stun time
    int GiantGemDamage;// giant projectile damage for 3 x 3 grid hurt.
    float PlantfoodAttackRatio;// when in plantfood status, the damage ratio of projectile
    float BounceBulletAttackRatio;// the bounce bullet attack ratio (N% of the first bullet attack)
};

///////////////////////////////////////
/// pomegranate Jeweler
///////////////////////////////////////
class PlantPomegranateJeweler : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantPomegranateJeweler, PlantFramework, RtClass);
    PlantPomegranateJeweler();

    virtual  Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    
	virtual void PostInitialize() override;
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void UpdatePlantfood() override;
	virtual void CancelPlantfood() override;

	virtual bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	virtual void onAnimStoppedCallback(const std::string& i_animCommand) override;

private:
    Projectile* LaunchProjectile(PomegranateJewelerProjectileType type, BoardEntity* entity, BoardEntity* targetEntity);
    Projectile* CreateProjectile(PomegranateJewelerProjectileType type, float x, float y, float z);
    PomegranateJewelerProjectileType CheckProjectileType(int level);
    void LaunchSpecialProjectile();
    
    int _shootThreeCount;// how many proj three bullets can be use
    std::vector<BoardEntity*> _plantfoodEnemyList;// plantfood skill enemy list
    int _plantfoodEnemyListIndex;// plantfood projectile order index
};

///////////////////////////////////////
/// pomegranate Jeweler anim rig
///////////////////////////////////////
class PlantAnimRig_PomegranateJeweler : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_PomegranateJeweler, PlantAnimRig, RtClass);
    PlantAnimRig_PomegranateJeweler();
};


#endif /* PLANT_POMEGRANATE_H_ */
