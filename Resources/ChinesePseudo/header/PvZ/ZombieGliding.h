/*
 * ZombieGliding.h
 *
 *  Created on: 2019-11-18
 *      Author: zhousen
 */

#ifndef ZOMBIEGLIDING_H_
#define ZOMBIEGLIDING_H_

#include "RtObject.h"
#include "Zombie.h"
#include "ZombieAnimRig.h"
#include "ZombieAnimRig_Basic.h"

/// grid item gliding (ground)
class GridItemGliding : public GridItemGravestone
{
public:
    RT_CLASS_DEFINE(GridItemGliding, GridItemGravestone, RtClass);
    
    GridItemGliding();
    
    void PlayDropAnimation(bool destroyAfterCrash);
    
protected:
    void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason> *io_plantingReasons) const override;
    PlantingReason GetCantPlantReason() const override;
    void onTakeDamage(const DamageInfo& i_damage) override;
    
    void onUpdate() override;
    void onGridItemInitialize() override;
    
private:
    void OnAnimStoppedCallback(const std::string& animName);
    void KillGridPlant(Sexy::Point point);

    bool _destroyAfterCrash;// should not add this craft on the crash grid
    bool _checkKillPlant;// should kill plant ?
};

/// grid item gliding (gournd) props
class GridItemGlidingProps : public GridItemGravestonePropertySheet
{
public:
    RT_CLASS_DEFINE(GridItemGlidingProps, GridItemGravestonePropertySheet, RtClass);
	PlantRestrictionSet NoKillPlants;
};

/// grid item gliding (ground) anim rig
class GridItemGlidingAnimRig : public GravestoneAnimRig
{
public:
    RT_CLASS_DEFINE(GridItemGlidingAnimRig, GravestoneAnimRig, RtClass);
    
    void SetDamageState(int i_damageState, bool i_i_isAnimated) override;
};

// new zombie gliding state
STATE_ENUM_CHILD_BEGIN(ZombieGlidingState, ZombieState)
    ZS_Gliding_Flying_Up,// zombie fly over tall plant state
    ZS_Gliding_Flying_Update,
    ZS_Gliding_Flying_Down,
    ZS_Gliding_Crash,// start crash
    ZS_Gliding_Flying_Updown,// be blowed by some plants
    ZS_Gliding_ShootDown, // gliding is be shooted down
STATE_ENUM_END(ZombieGlidingState)

/// zombie gliding
class ZombieGliding : public Zombie
{
public:
    RT_CLASS_DEFINE(ZombieGliding, Zombie, RtClass);

    ~ZombieGliding();

    void onZombieInitialize() override;
    void onZombiePostLoad() override;
    bool IsFlying() const { return _isFlying; }

protected:
    void onTakeHelmDamage(const DamageInfo& i_damageReceived) override;

private:
    OVERRIDE_STATE_UPDATE(ZombieState, Walk);
    DECLARE_STATE_FUNCTIONS(ZombieState, FlyingUp);
    DECLARE_STATE_FUNCTIONS(ZombieState, FlyingUpdate);
    DECLARE_STATE_FUNCTIONS(ZombieState, FlyingDown);
    DECLARE_STATE_FUNCTIONS(ZombieState, Crash);
    DECLARE_STATE_FUNCTIONS(ZombieState, FlyingUpdown);
    DECLARE_STATE_FUNCTIONS(ZombieState, ShootDown);

    void onPlaceOnBoard() override;
    void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_command, const std::string& i_param) override;
    
    bool CheckCrash();
    Sexy::Point RandomCrashLocation(int type);// type 0 = initialize, 1 = early crash location
    void RandomEarlyCrashLocation();
    void PlantBlow(Plant* ptr);
    void OnAnimStop(const std::string& animCommand);
    void KillGridPlant(Sexy::Point point);

    Sexy::Point _crashGridLocation;// which grid will gliding crash
    bool _isEarlyCrash;// if is early crash
    bool _isInPlantBlowStatus;// if zombie is blowed
    class ZombieAnimRig_RenaiGliding* _animRig;
    bool _isFlying;// zombie is in flying
};

/// zombie gliding props
class ZombieRenaiGlidingProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombieRenaiGlidingProps, ZombiePropertySheet, RtClass);
};

/// zombie gliding anim rig
class ZombieAnimRig_RenaiGliding : public ZombieAnimRig_Basic
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_RenaiGliding, ZombieAnimRig_Basic, RtClass);
    ZombieAnimRig_RenaiGliding();
    
    void SetGlidingVisible(bool enable);
    bool GetGlidingVisible() const { return _isGlidingVisible; }
    void SetZombiePtr(ZombieGliding* ptr) { _zombie = ptr; }

protected:
    const std::string getIdleAnimationName() override;
    const std::string getWalkAnimationName() override;
    const std::vector<std::string>& getHeadLayerNames() override;
    const std::vector<std::string>& getArmLayerNames() override;
    const std::vector<std::string>& getGlidingLayerNames() override;

private:
    bool _isGlidingVisible;
    ZombieGliding* _zombie;
};


#endif /* ZOMBIEFLYMACHINE_H_ */
