/*
 * ZombieHanabi.h
 *
 *  Created on: 2020-12-10
 *      Author: zhousen
 */

#ifndef ZOMBIEHANABI_H_
#define ZOMBIEHANABI_H_


#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"
#include "GameSubSystem.h"
#include "Projectile.h"
#include "ZombiePerfumer.h"

/// 
/// GridItemHanabi
/// 
class GridItemHanabi : public GridItemPoisonMist
{
public:
	RT_CLASS_DEFINE(GridItemHanabi, GridItemPoisonMist, RtClass);

	GridItemHanabi();
	virtual ~GridItemHanabi();

    void onGridItemInitialize() override;
    void KillGridItem() override;

protected:
	void PoisonPlant(Plant* plant) override;
	void RecoverPlant(Plant* plant) override;

    void CreatePoisonEffect() override;
    void OnCleanPoison(int x, int y, bool i_fromPlant) override;
};

/// 
/// HanabiProjectile
///
class HanabiProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(HanabiProjectile, Projectile, RtClass);
    
    HanabiProjectile();

    void SetTargetPosition(Sexy::Point target) { _target = target; }

protected:
    bool OnCollideGround() override;

    Sexy::Point _target;// fire target
};

///
/// ZombieHanabiProps
///
class ZombieHanabiProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieHanabiProps, ZombiePropertySheet, RtClass);

    ZombieHanabiProps();

    pvztime_t HanabiRecoveryTime;// how much time should recovery after a time of hanabi shoot
    pvztime_t HanabiLifeDuration;// how much time should hanabi exists
    float MaxTorchReach;// max hanabi touch
    float ExplodeRatio;// hanabi explode ratio
    int ExplodeDamage;// hanabi explode damage
	ProjectilePropertySheetPtr Projectile;// hanabi projectile
};

///
/// Zombie State
///
STATE_ENUM_CHILD_BEGIN(ZombieState_Hanabi, ZombieState)
    ZS_Hanabi_Fire,// fire hanabi
	ZS_Hanabi_Explode,// Explode
STATE_ENUM_END(ZombieState_Hanabi)

/// 
/// ZombieHanabi
///
class ZombieHanabi : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieHanabi, Zombie, RtClass);

    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    OVERRIDE_STATE_ONENTER(ZombieState, Die);
    DECLARE_STATE_FUNCTIONS(ZombieState, Fire);
    OVERRIDE_STATE_UPDATE(ZombieState, Eat);
    DECLARE_STATE_FUNCTIONS(ZombieState, Explode);

    void onZombieInitialize() override;
	Sexy::Rect CalcZombieAttackRect() override;
	// void onTakeFatalDamage(const DamageInfo& i_lastDamageReceived) override;
	// void onUpdate() override;
    void TakeDamage(const DamageInfo& i_damage) override;
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    ZombieParticle* DropArm() override;

protected:    
    void onAnimStop(const std::string& i_animCommand);
	void burnPlantGroup(class PlantGroup* i_plantGroup);
    void burnZombie(class Zombie* targetZombie);
    bool CheckExplode(float ratio);
    void Explode();
    void DamagePlant();
    std::vector<Sexy::Point> CalcAroundField(Sexy::Point pos);
    std::vector<Sexy::Point> CalcHanabiFireField();
    Sexy::Point RandomFirePosition();
    void FireHanabi();
    void HanabiEndCompleted(StandaloneEffect* i_effect);

protected:
    bool _hasHanabi;// if zombie has hanabi on fire
    pvztime_t _hanabiShootStartTime;// when to shoot hanabi
    pvztime_t _hanabiEndTime;// the end time of hanabi
    Sexy::Point _hanabiTarget;// hanabi target
};

/// 
/// ZombieAnimRig_Hanabi
///
class ZombieAnimRig_Hanabi : public ZombieAnimRig_Basic
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Hanabi, ZombieAnimRig_Basic, RtClass);

    ZombieAnimRig_Hanabi();

    void SetHanabiLayer(bool visible);

protected:
    virtual const std::vector<std::string>& getHeadLayerNames() override;
    virtual const std::vector<std::string>& getArmLayerNames() override;
    virtual const std::vector<std::string>& getArmReplacementPairNames() override;
};

#endif /* ZOMBIEHANABI_H_ */
