/*
 * Plant_Icelotus.h
 *
 *  Created on: 2020-12-7
 *      Author: zhousen
 */

#ifndef PLANT_ICELOTUS_H_
#define PLANT_ICELOTUS_H_

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "GameSubSystem.h"
#include "PlantUtils.h"
#include "AnimRigLayerSet.h"
#include "Zombie.h"
#include "BoardEntity.h"
#include <string>

///
/// global enums and parameters
///
enum {
    DROPWATER_STATE_INVALID = -1,
    DROPWATER_STATE_START,
    DROPWATER_STATE_LOOP,
    DROPWATER_STATE_END,
    DROPWATER_STATE_MAX,
};

enum {
    ICELOTUS_PROJECTILE_INVALID = -1,
    ICELOTUS_PROJECTILE_1,
    ICELOTUS_PROJECTILE_2,
    ICELOTUS_PROJECTILE_3,
    ICELOTUS_PROJECTILE_MAX,
};

enum {
    ICELOTUS_STATE_IDLE = STATE_FRAMEWORK_BEGIN,
    ICELOTUS_STATE_FIRE,
    ICELOTUS_STATE_PLANTFOOD,
    ICELOTUS_STATE_RECOVERY,
    ICELOTUS_STATE_DEAD,
    ICELOTUS_STATE_MAX,
};

enum {
    ICELOTUS_FIRE_INVALID = -1,
    ICELOTUS_FIRE_LEFT,
    ICELOTUS_FIRE_RIGHT,
    ICELOTUS_FIRE_ALL,
};

enum {
    ICELOTUS_ANIMRIG_RELOAD = PLANTANIM_USERDEFINED,
};

/// 
/// GridIcelotusDropWaterProps
///
class GridIcelotusDropwaterProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridIcelotusDropwaterProps, GridItemAnimationProps, RtClass);
	GridIcelotusDropwaterProps();

    pvztime_t Duration;// gird item duration time
    pvztime_t FreezeDuration;// freeze duration time 
};

/// 
/// GridIcelotusDropwater
/// 
class GridIcelotusDropwater : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridIcelotusDropwater, GridItemAnimation, RtClass);
	GridIcelotusDropwater();

    bool IsDamageable() const override { return false; }
    bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
    void onGridItemInitialize() override;
    void onUpdate() override;
    void KillGridItem() override;
	int CalcRenderOrder() const override;
	// int  CalcRenderOrder() const override;

    void InitParam(bool avatar);
    void Resume(bool avatar);// resume icelotus status, reset start time.then should affect all zombielist
    void ExtensionDuration(float i_rate);

protected:
    void OnAnimStoppedCallback(const std::string& i_animCommand);
    void ExtinguishFire();
    void DebuffZombie();

protected:
    pvztime_t _startTime;// this effect start time
    pvztime_t _durationTime;// this effect duration time
    int _state;// item state
    bool _avatar;// check is avatar
    std::vector<RtWeakPtr<BoardEntity> > _slowDownZombieList;// effected zombie list, check each zombie out of the list in onUpdate，then put thme into this list,
    std::vector<RtWeakPtr<BoardEntity> > _frozenZombieList;// use in avatar
};

/// 
/// IcelotusWaterProjectile
///
class IcelotusWaterProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(IcelotusWaterProjectile, Projectile, RtClass);
    IcelotusWaterProjectile();

    void onSetInstigator(BoardEntity* i_instigator) override;
    bool OnCollideGround() override;

    void CreateIcelotusDropwater(Sexy::Point pos);
    void SetTargetPos(Sexy::Point pos) { _target = pos; }

protected:
    bool _isAvatar;// if plant is avatar
    int _projectileType;// projectile style
    Sexy::Point _target;// target block
};

///
/// PlantIcelotusProps
/// 
class PlantIcelotusProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PlantIcelotusProps, PlantPropertySheet, RtClass);
	PlantIcelotusProps();

    int NormalLifeTimes;// normal spray water times
    int AdvancedLifeTimes;// advanced spray water times
    float FreezeRatio;// freeze zombie ratio
    pvztime_t FreezeDuration;// lv3 skill, freeze zombie duration
    int NormalLayerLimit1;// below the limit, we change layer2
    int NormalLayerLimit2;// below the limit, we change layer3
    int AdvancedLayerLimit1;// below the limit, we change layer2
    int AdvancedLayerLimit2;// below the limit, we change layer3
    pvztime_t RecoveryTime;// recovery time between fire and fire
};

///
/// PlantIcelotus
///
class PlantIcelotus : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantIcelotus, PlantFramework, RtClass);
    PlantIcelotus();

    void PostInitialize() override;
	void UpdateActions() override;
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	void onAnimStoppedCallback(const std::string& i_animCommand) override;
    DamageInfo TakeDamage(const DamageInfo& i_damage) override;
    
    bool CanFreezeZombieWhenBite(DamageInfo info);// check if can freeze zombie.
    bool FindTarget();// find target
    bool FindHanabi();// find hanabi
    void FireDropwater(int type);// fire dropwater
    void CreateDropwaterProjectile(std::vector<Sexy::Point> range);// fire dropwater projectile
    void UpdateLife(bool fillMax = false);// update life times
    std::vector<Sexy::Point> CreateFireField(Sexy::Point pos, int range, int type = ICELOTUS_FIRE_ALL);// craete a fire rect
    int CalcProjectileType();// which prijectile should we use
    void CreateIcelotusDropwater(Sexy::Point pos);
    bool CheckFireField(int x, int y, int type);// chekc is ICELOTUS_FIRE_LEFT or ICELOTUS_FIRE_RIGHT
    void CreateFireEffect(bool plantfood);// craete attack effect

protected:
    int _lifeLeftTime;// the life times before died
    int _lifeTimeMax;// the max life time
    int _layerLimit1;// below this limit, we change layer2
    int _layerLimit2;// below this limit, we change layer3
    pvztime_t _recoveryTime;// recovery time between fire and fire
};

///
/// Icelotus Animrig
///
class PlantAnimRig_Icelotus : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Icelotus, PlantAnimRig, RtClass);
	PlantAnimRig_Icelotus();

    bool PlayIdleLooped() override;
    void onPopAnimInitialized() override;
	bool PlayPreviewAnim(bool bHideLayer = false) override;
    bool PlayWatering() override;

    void AddBoostedLayerSet(std::string setName, std::vector<std::string> layerNames);
	void ShowBoostedLayerSet(std::string setName);
    void ShowIceLayer(bool enable);
    void onAnimStoppedCallback(const std::string& i_animCommand);
    void SetReload(bool reload) { _shouldReload = reload; }

protected:
	AnimRigLayerSet _layer;// change layer
    bool _shouldReload;// check if need reload
};

#endif /* PLANT_ICELOTUS_H_ */
