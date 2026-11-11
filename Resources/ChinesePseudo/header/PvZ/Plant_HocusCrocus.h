/*
 * 	Plant_HocusCrocus.cpp
 *
 * 		Created on:	2022-5-4
 * 			Author:	kkdud
 */

#ifndef PLANTSVERSUSZOMBIES2_PVZ2_PLANT_HOCUSCROCUS_H_
#define PLANTSVERSUSZOMBIES2_PVZ2_PLANT_HOCUSCROCUS_H_

#include "Effect_PopAnim.h"
#include "GameSubSystem.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RtObject.h"
#include "TimeLine.h"
#include "Zombie.h"
#include "EffectObject.h"

class HocusCrocusProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(HocusCrocusProps, PlantPropertySheet, RtClass);
	
	HocusCrocusProps()
	: TeleportInitialDelay(0.5f)
	, TeleportRechargeTime(5.0f)
	, TimeZombieGone(1.0f)
	, TeleportDamage(10.0f)
	, TeleportBeamDecayDelay(0.5f)
	, PFZombiesTeleported(3)
	, ChildRayDamageDiscountPlus(0.5f)
	, ChildRayDamageDiscount(0.25f)
	, ChildRayShrinkProbabilityPlus(0.5f)
	, ChildRayShrinkProbability(0.2f)
	, RayRefractionProbabilityPlus(1.0f)
	, RayRefractionProbability(1.0f)
	, RayPlusHappenedOnTimes(3)
	, FogSurviveDurationPlus(6.0f)
	, FogSurviveDuration(4.0f)
	{}
	
	float TeleportInitialDelay;
	float TeleportRechargeTime;
	float TeleportBeamDecayDelay;
	float TimeZombieGone;
	float TeleportDamage;
	int   PFZombiesTeleported;
	float ChildRayDamageDiscountPlus;
	float ChildRayDamageDiscount;
	float ChildRayShrinkProbabilityPlus;
	float ChildRayShrinkProbability;
	float RayRefractionProbabilityPlus;
	float RayRefractionProbability;
	int RayPlusHappenedOnTimes;
	float FogSurviveDurationPlus;
	float FogSurviveDuration;

	
	ZombieRestrictionSet CannotBeShrunk;
};

class PlantHocusCrocus : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantHocusCrocus, PlantFramework, RtClass);
	
	void Initialize() override;
	void UpdateActions() override;
	
	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
	void CancelPlantfood() override;
	bool OnAnimCommand(const std::string& i_animCommand, const std::string& i_animCommandParam) override;
	
	static bool canBeShrunkByHocusCrocus(RtWeakPtr<Zombie> i_zombie);
	static bool canBeAttackedByHocusCrocus(RtWeakPtr<BoardEntity> i_ent);

protected:
	void onPlantfoodLooped() override;
	
private:
	enum HocusState
	{
		HOCUS_STATE_IDLE = STATE_FRAMEWORK_BEGIN,
		HOCUS_STATE_CASTING,
	};
	
	bool shouldBeginCasting();
	void beginCasting();
	void fireProjectileAtTarget(RtWeakPtr<BoardEntity> i_ent);
	void fireChildProjectileBetweenTargets(RtWeakPtr<BoardEntity> i_target, RtWeakPtr<BoardEntity> i_originTarget);
	void findChildTargets(std::vector<RtWeakPtr<BoardEntity>>& o_twoTargets, RtWeakPtr<BoardEntity> i_mainTarget);
	void checkRayRefraction(RtWeakPtr<BoardEntity> i_ent);
	void downZombieLevel(RtWeakPtr<Zombie> i_zombie);
	void createDownLevelFogEffect(RtWeakPtr<Zombie> i_zombie);
	
	bool hasTargetToAttack();
	std::vector<RtWeakPtr<BoardEntity>> findTargetsForAttack(int i_numTargets);

	
	std::vector<RtWeakPtr<Zombie>>		m_warpingZombies;
	float								m_nextTeleportTime;
	int									m_fireTimes;
	bool 								m_isRayPlus;
};

class PlantAnimRig_HocusCrocus : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_HocusCrocus, PlantAnimRig, RtClass);
	
private:
	std::string getPlantFoodOnAnimName() override { return "plantfood_start"; }
	std::string getPlantFoodMainAnimName() override { return "plantfood_loop"; }
	std::string getPlantFoodOffAnimName() override { return "plantfood_end"; }
};

enum ZombieWarpState
{
	PVZ_BEGIN_ENUM(ZWARP_),
	ZWARP_Hit,
	ZWARP_Gone,
	ZWARP_Reappearing,
	ZWARP_Done,
	PVZ_END_ENUM(ZWARP_)
};

class ZombieWarpRecord
{
public:
	ZombieWarpRecord()
	: StartTime(0.0f)
	, TeleportDuration(0.0f)
	, State(ZWARP_Invalid)
	{}
	
	RtWeakPtr<class Plant> Plant;
	ZombiePtr Zombie;
	pvztime_t StartTime;
	pvztime_t TeleportDuration;
	ZombieWarpState State;
};

class PlantHocusCrocusSubSystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(PlantHocusCrocusSubSystem, GameSubSystem, RtClass);
	
	void Update() override;
	
	void AddWarpingZombie(Plant* i_plant, Zombie* i_zombie, pvztime_t i_teleportDuration);
	void RemoveWarpingZombie(Zombie* i_zombie);
	
protected:
	void warpZombieOut(ZombieWarpRecord* i_zombie);
	void warpZombieIn(ZombieWarpRecord* i_zombie);
	void createTeleportEffectAtReappearance(ZombieWarpRecord* i_zombie);
	
	void reappearZombie(RtWeakPtr<Zombie> i_zombie);
	SexyVector3 getZombiePostTeleportPosition(RtWeakPtr<Zombie> i_zombie);
	
private:
	std::vector<ZombieWarpRecord> m_zombieRecords;
};

class EffectObject_HocusCrocusFog : public EffectObject
{
public:
	RT_CLASS_DEFINE(EffectObject_HocusCrocusFog, EffectObject, RtClass);

	void onEffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY) override;
	void onUpdate() override;
	void setDuration(float i_duration) { m_duration = i_duration; }
	void setShrinkRect(Rect i_rect);
//	void onDraw(class Graphics* i_g) override;

private:
	pvztime_t m_timer = PVZ_T();
	float m_duration = PVZ_EOT();
	Rect m_effectRect = Rect();
};

#endif // PLANTSVERSUSZOMBIES2_PVZ2_PLANT_HOCUSCROCUS_H_
