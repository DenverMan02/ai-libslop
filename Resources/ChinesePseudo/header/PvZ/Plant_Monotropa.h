/*
 * Plant_Monotropa.h
 *
 *  Created on: 2019-3-11
 *      Author: zhousen
 */

#ifndef PLANT_MONOTROPA_H_
#define PLANT_MONOTROPA_H_

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "GameSubSystem.h"
#include "PlantUtils.h"


//////////////////////////////////////////
//
//	monotropa plant food counter
//
//////////////////////////////////////////
class MonotropaFoodCounter : public PlantFoodCounter
{
public:
	RT_CLASS_DEFINE(MonotropaFoodCounter, PlantFoodCounter, RtClass);

	enum EffectType {
		Effect_Blizzard = 0,
		Effect_Ice,
	};

	void Start(pvztime_t duration, int shootTotal, BoardEntityPtr plant, bool isAvatar);
	void SetTargets(std::vector<BoardEntityPtr> targets);
	void SetIceTarget(BoardEntityPtr target);
	void Update();

private:
	void GenerateEffect(int x, int y, BoardEntityPtr source, BoardEntityPtr target, EffectType type);

private:
	std::vector<BoardEntityPtr> _targets;
	BoardEntityPtr _iceTarget;
	BoardEntityPtr _plant;
	bool _isAvatar;// if is avatar
	bool _isFireAvatarEffect;// if is shoot when avatar effect
};

// grid item props
class GridItemMonotropaProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemMonotropaProps, GridItemAnimationProps, RtClass);

	enum DamageType{
		Damage_Undefine,
		Damage_Flame,// flame damage
	};

	GridItemMonotropaProps();

	pvztime_t GetTimeThreshold() const;
	float GetDamageRatio(DamageType type) const;

private:
	float _fireDamageRatio;// damage ratio when flame hit grid item
	pvztime_t _timeThreshold;// grid itme lasted time
};

// grid item monotropa animation , like a snow man
class GridItemMonotropa : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemMonotropa, GridItemAnimation, RtClass);

	// snow man state
	enum SnowmanState {
		Snowman_Idle = 0,
		Snowman_Freezing,
		Snowman_Frozen,
		Snowman_Fadeout,// maybe not use
		Snowman_TurnZombie,
		Snowman_Dead,
	};

	GridItemMonotropa();

	void onUpdate() override;
	virtual void TakeDamage(const DamageInfo& i_damage) override;
	virtual void KillGridItem() override;
	int	CalcRenderOrder() const override;

	void SetLevel5();
	void SetZombie(ZombiePtr zombie);
	void UpdateSnowmanFade();

	void SetThresholdRatio(float ratio);
	void SetSpecialType(int type){ _snowmanType = type; }

protected:
	void onGridItemInitialize() override;
	void onDestroy() override;
	bool CollidesWithType(const CollisionTypeFlags i_collisionTypes) const override { return true; }

protected:
	void PlayFreezeAnimation();
	std::string GetFreezeAnimationName(ZombiePtr ptr);
	void OnStopAnimation(const std::string& label);

private:
	bool _IsLevel5;
	SnowmanState _state;// snowman state
	ZombiePtr _zombie;// which zombie turn in griditem
	pvztime_t _startTime;// the time that become a snowman
	pvztime_t _timeThreshold;// the time that keep in snowman status
	int _zombieVisibleState;// zombie original visible state
	ZombieState _zombieState;// zombie original state
	float _timeThresholdRatio;// level 3 ratio
	int _snowmanType;// special snowman type.
};

// monotropa props
class PlantMonotropaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PlantMonotropaProps, PlantPropertySheet, RtClass);
	PlantMonotropaProps();

	pvztime_t _chargeTime;// plant to charge time
	pvztime_t _chargeTimeShorten;// decline charge time lv2 use
	float _chargeTimeShortenRatio;// decline charge time ratio lv3 use
	pvztime_t _cooldownTime;// cool down time to idle

	pvztime_t _specialAttackTime;// food plant attack blizzard time
	int _specialAttackTargetsNumberMin;// the number of targets which can be attacked by blizzard 
	int _specialAttackTargetsNumberMax;
	int _attackRange;// plant attack range in front of it's position
};

// plant monotropa state
enum MonotropaState {
	Monotropa_Idle = STATE_FRAMEWORK_BEGIN,
	Monotropa_Charge,// charge to shoot
	Monotropa_Attack,
	Monotropa_Cooldown,
	Monotropa_SpecialAttack,// apply food plant
	Monotropa_Blizzard,
	Monotropa_BlizzardHurtZombie,
};

class PlantMonotropa : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantMonotropa, PlantFramework, RtClass);

	virtual void Initialize() override;
	virtual void UpdateActions() override;
	virtual bool CanApplyPlantfood() override;
	virtual void ApplyPlantfood() override;
	virtual void UpdatePlantfood() override;
	virtual void CancelPlantfood() override;

	virtual bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
	virtual void onAnimStoppedCallback(const std::string& i_animCommand) override;
	virtual bool FindTargetAndFire(PlantWeapon i_plantWeapon) override;
private:
	void UpdateIdle();
	void UpdateCharge();
	void UpdateAttack();
	void UpdateCooldown();
	void UpdateSpecialAttack();
	void UpdateBlizzard();
	void UpdateBlizzardHurtZombie();

	bool CheckZombieIsSnowman(ZombiePtr zombie);
	bool CheckZombieCanBeSnowman(ZombiePtr zombie);
	void InitParamByCurrentLevel(const PlantMonotropaProps* props);
//	void FindTargetAndAttack(PlantWeapon weapon);

	// zhousen do attack
	void DoAttack(PlantWeapon weapon);
	void FireProjectile();
	void RemoveUndamageableEntitiesFromList(std::vector<BoardEntity*> &o_boardEntities);
	std::vector<BoardEntity*> FindEnemies(PlantWeapon weapon);

	void AddSnowman(ZombiePtr zombie);
	Rect GetPlantAttackRect(PlantWeapon weapon);
	void ExecuteDamage(BoardEntity* entity, PlantWeapon weapon);

	void OnAttackEndAnim(const std::string& label);

	void LaunchSpecialAttack();// just only change state
	void LaunchSpecialAttackReal();// real launch attack

	Effect_PopAnim* CreateProjectileEffectByScreenSpace(const std::string pamName, const std::string animName, SexyVector2 pos, int renderOrder);
	Effect_PopAnim* CreateProjectileEffectByBoardSpace(const std::string pamName, const std::string animName, SexyVector3 pos, int renderOrder);

private:
	class MonotropaFoodCounter _foodCounter;

	pvztime_t _triggerChargeTime;// charge time start
	pvztime_t _triggerCooldownTime;// cool down time start

	pvztime_t _deltaChargeTime;//charge time delta
	pvztime_t _deltaCooldownTime;// cool down time delta

	pvztime_t _specialAttackTime;// special attack duration
	int _specialAttackTargetsNumberMin;// special attack targets number
	int _specialAttackTargetsNumberMax;
	int _attackRange;// plant attack range
	int _randSpecialTotalNumber;// special attack zombies random number
	std::vector<BoardEntityPtr> _randSpecialTargets;// special attack zombies vector
	BoardEntityPtr _randIceDropZombie;// random ice drop zombie hit
	static ZombiePtr _snowmanZombie;// the zombie what is be a snowman
	static std::vector<ZombiePtr> _snowmanZombieList;// this should be a list

	static bool _isInFoodPlantStatus;// is in food plant status, other monotropa cant apply food
};

// monotropa anim rig
class PlantAnimRig_Monotropa : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_Monotropa, PlantAnimRig, RtClass);
	PlantAnimRig_Monotropa();

	void SetPlant(PlantPtr ptr);

private:
	std::string getPlantFoodOnAnimName() override;
	std::string getPlantFoodMainAnimName() override;
	std::string getPlantFoodOffAnimName() override;
	std::string getWaterAnimName() override;

	PlantPtr m_plant;
};


#endif /* PLANT_SNOWMACHINE_H_ */
