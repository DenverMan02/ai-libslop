/*
 * Plant_CthulhuActinia.h
 *
 *  Created on: 2023-5-31
 *      Author: zhousen
 */

#ifndef PLANT_CTHULHUACTINIA_H_
#define PLANT_CTHULHUACTINIA_H_

#include "ComponentWarmingRadius.h"
#include "DamageInfo.h"
#include "GridItemAnimation.h"
#include "GridItemAnimController.h"
#include "GameSubSystem.h"
#include "TimeMgr.h"
#include "PlantFramework.h"
#include "RtObject.h"
#include "Zombie.h"
#include "GameSubSystem.h"
#include "CthulhuSubSystem.h"

namespace Message
{
	// for tentacle drag
	void CthulhuActiniaTentacleDragStart(Plant* parent);
	void CthulhuActiniaTentacleDragOver(Plant* parent);
	void CthulhuActiniaTentacleAttackOver(Plant* parent);
	void CthulhuActiniaPlantfood(Plant* parent);
}

////////////////////////////////////////
/// CthulhuActiniaProps
////////////////////////////////////////
class CthulhuActiniaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(CthulhuActiniaProps, PlantPropertySheet, RtClass);

	CthulhuActiniaProps() {
		EyeballOpenDuration = 40.0f;
		TentacleAbsorbDuration = { 20.0f, 18.0f, 15.0f, 15.0f, 15.0f };
		TentacleAbsorbEyeballOpenTimeExchange = { 0.5f, 0.75f, 1.0f, 1.5f, 2.0f };
		FishLevelCondition = { 3, 5, 6, 8, 10 };
		FishLevelDecline = 2;
		FishStatusDuration = { 5.0f, 5.0f, 5.0f, 5.0f, 5.0f };
		TentacleDamage = 100;
		PlantfoodTentacleDamage = 100;
		PlantfoodAvatarTentacleDamage = 100;
		PlantfoodTentacleDragCountMax = 4;
		PlantfoodAvatarTentacleDragCountMax = 5;
		PlantfoodAvatarTossGridNum = 1;
		ZombieBlacklist = {};
	}

public:
	pvztime_t EyeballOpenDuration;
	std::vector<pvztime_t> TentacleAbsorbDuration;
	std::vector<float> TentacleAbsorbEyeballOpenTimeExchange;// for eyeball open time exchange
	std::vector<int> FishLevelCondition;// under level zombie turn fish
	int FishLevelDecline;
	std::vector<pvztime_t> FishStatusDuration;
	int TentacleDamage;
	int PlantfoodTentacleDamage;
	int PlantfoodAvatarTentacleDamage;
	int PlantfoodTentacleDragCountMax;
	int PlantfoodAvatarTentacleDragCountMax;
	int PlantfoodAvatarTossGridNum;
	std::vector<std::string> ZombieBlacklist;
};

////////////////////////////////////////
/// PlantCthulhuActiniaType
////////////////////////////////////////
class PlantTypeCthulhuActinia : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeCthulhuActinia, PlantType, RtClass) {}

    virtual int GetCost(PlantAvatarType i_avatarType=E_AVATAR_ILLEGAL) const override;
    int GetRefundSunCount() const override;
};


////////////////////////////////////////
/// PlantCthulhuActinia
////////////////////////////////////////
class PlantCthulhuActinia : public PlantFramework
{
public:
	enum CthulhuActiniaState
	{
		STATE_CTHULHUACTINIA_IDLE = STATE_FRAMEWORK_BEGIN,
		STATE_TENTACLE_ATTACK_START,
		STATE_TENTACLE_ATTACK_HIT_LOOP,// for tentacle hit
		STATE_TENTACLE_ATTACK_ABSORB_LOOP,// for tentacle absorb
		STATE_TENTACLE_ATTACK_END,
		// maybe lv5 another.
		STATE_EYEBALL_OPEN,
		STATE_EYEBALL_FIRE_LASER,
	};

	RT_CLASS_DEFINE(PlantCthulhuActinia, PlantFramework, RtClass);

	void Initialize() override;
	void registerForEvents() override;
	void unregisterForEvents() override;
	void onKilled(bool i_instantKill) override;
	int CalcRenderOrder() override;
	void ApplyPlantfood() override;
	bool CanApplyPlantfood() override;
	void CancelPlantfood() override;
	void UpdateActions() override;
	float GetRefundSunAmount() override;
	BoardEntityTypeFlag GetTargetEntityTypesForWeapon(PlantWeapon i_plantWeapon) override;
	ZombiePtr FindTargetZombie(Rect& i_region, PlantWeapon i_plantWeapon, PlantTargetParams& i_targetParams) override;

	std::vector<Zombie*> FindAttackTargets(Rect searchRect, bool onlyAbsorb = false);
	bool GetEyeballStatus();
	bool IsTentacleAvailable();
	float GetTentacleDamage();

protected:
	void SetState(int i_plantState);
	bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

	void CthulhuActiniaTentacleDragStart(Plant* parent);
	void CthulhuActiniaTentacleDragOver(Plant* parent);
	void CthulhuActiniaTentacleAttackOver(Plant* parent);
	void OnPlantMoving(Plant* i_plant, Point& i_targetGridLocation);

	void UpdateEyeballTime();
	pvztime_t GetTentacleAbsorbTimeExchange();

	bool IsAbsorbTarget(const ZombiePtr& i_potentialZombie);
	bool IsZombieBlacklisted(const ZombiePtr i_zombie, const std::vector<std::string>& i_blacklist);
	bool IsZombieFishable(const ZombiePtr i_zombie);
	void UpdateEyeballLaser();
	ZombiePtr SpawnZombie(Zombie* i_ancestorZombie);
	std::string getTransformType(Zombie* i_zombie);
	void GenerateTentacle(int x, int y, ZombiePtr zombie = ZombiePtr());
	void PlayDarkEffect(const SexyVector2& start);
	void DarkEffectFlyEnd(float value);
	std::string GetFireLaserAnimationName();

protected:
	pvztime_t m_eyeballTime;// for eyeball open anim
	pvztime_t m_eyeballTimeEnd;
	pvztime_t m_absorbTime;// for tentacle loop anim
	pvztime_t m_absorbTimeEnd;
	pvztime_t m_absorbTimeDuration;
	pvztime_t m_absorbTimeExchange;
	bool m_eyeballStatus;// eyeball open.
	int m_tentacleArmsMax;
	int m_plantfoodTentacleArmCount;
	std::vector<BoardEntityPtr> m_tentacleEntityList;// the generate tentacle entity.
	std::vector<RtWeakPtr<BoardEntity> > m_hitEntities;
	RtWeakPtr<BoardEntity> m_turnZombie;
	RtWeakPtr<class AddCthulhuEnergyEffect> m_darkEffect;
};



////////////////////////////////////////
/// PlantAnimRig_CthulhuActinia
////////////////////////////////////////
class PlantAnimRig_CthulhuActinia : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_CthulhuActinia, PlantAnimRig, RtClass);

	void SetPlantPtr(PlantPtr ptr) { m_plantPtr = ptr; }
	bool playSingleAnimation(std::string i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	bool playLoopAnimation(std::string i_animLabel);

protected:
	void onPopAnimInitialized() override;
    std::string getIdleAnimationName() override;
    std::string getWaterAnimName() override;

protected:
    PlantPtr m_plantPtr;
};


////////////////////////////////////////
///  GridItemCthulhuActiniaTentacleProps
////////////////////////////////////////
class GridItemCthulhuActiniaTentacleProps : public GridItemAnimControllerProps
{
public:
	RT_CLASS_DEFINE(GridItemCthulhuActiniaTentacleProps, GridItemAnimControllerProps, RtClass);

	GridItemCthulhuActiniaTentacleProps();
};

////////////////////////////////////////
///  GridItemCthulhuActiniaTentacle
////////////////////////////////////////
class GridItemCthulhuActiniaTentacle : public GridItemAnimController
{
public:
	RT_CLASS_DEFINE(GridItemCthulhuActiniaTentacle, GridItemAnimController, RtClass);

	enum {
		STATE_TENTACLE_IDLE = GRID_ITEM_STATE_CUSTOM_BEGIN,
		STATE_TENTACLE_DRAG_START,
		STATE_TENTACLE_DRAGGING,
		STATE_TENTACLE_DRAG_OVER,
		STATE_TENTACLE_ATTACK,
		STATE_TENTACLE_DESTROY,
	};

	GridItemCthulhuActiniaTentacle();
	virtual ~GridItemCthulhuActiniaTentacle();

	void onGridItemInitialize() override;
	void onUpdate() override;
	int CalcRenderOrder() const override;
    void KillGridItem() override;

    void SetProps(const CthulhuActiniaProps* props);
    void SetOwnerPlant(PlantPtr parent);
    void SetTargetZombie(ZombiePtr zombie);
	bool PlaySingleAnimation(std::string i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

protected:
	virtual void UpdateIdle();
	void UpdateSwallowZombies();
	std::vector<BoardEntity*> FindTargets(bool IsOnlyAbsorb);
	std::vector<BoardEntity*> FindParentTargets(bool IsOnlyAbsorb);
	virtual void SwallowZombies(std::vector<BoardEntity*> i_zombies);
	void KillZombie(Zombie* zombie);
	void SetupZombieToBeSwallowed(Zombie* i_zombie);
	virtual void SetState(int state);

	virtual void OnAttackAnimDone(const std::string& name);
	virtual void OnPopAnimCommand(const std::string& i_animName, pvztime_t i_atTime, const std::string& i_command, const std::string& i_params);

	const std::string GetAttackAnimName();
	const std::string GetDragAnimName();
	void DamageZombie(Zombie* zombie, int damage, bool isToss);
	void CthulhuActiniaPlantfood(Plant* parent);
	void PlantDied(Plant* parent);
	void OnPlantMoving(Plant* i_plant, Point& i_targetGridLocation);

protected:
	PlantPtr m_plant;
	RtWeakPtr<const CthulhuActiniaProps> m_props;
	std::vector<ZombiePtr> m_zombieSwallowList;
	std::vector<CurveSequence_SexyVector3> m_zombieSwallowCurves;
	bool m_firstPlay;
	ZombiePtr m_targetZombie;
};

////////////////////////////////////////
/// CthulhuActiniaSubSystem
////////////////////////////////////////
class CthulhuActiniaSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(CthulhuActiniaSubSystem, GameSubSystem, RtClass);

	CthulhuActiniaSubSystem();

	void AddTransformEntry(ZombiePtr i_zombie);
	void hideShowOriginal(ZombiePtr i_zombie, bool i_hide);
	ZombiePtr tryTransform(class Zombie* i_zombie, int i_level, pvztime_t i_duration);
	ZombiePtr transform(class Zombie* i_zombie, int i_level, pvztime_t duration);
	std::string getTransformType(Zombie* i_zombie);
	void ApplyConditionToOriginalZombie(ZombiePtr transformed, ZombiePtr original);
	void CopyCondition(ZombiePtr transformedZombie, ZombiePtr originalZombie, ZombieConditions condition);

protected:
	void registerForEvents() override;

private:
	void onZombieConditionEnded(Zombie* i_zombie, int i_condition);
	std::vector<ZombiePtr> m_transformedEntries;
};




#endif /* PLANT_CTHULHUACTINIA_H_ */
