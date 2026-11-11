/*
 * 	Plant_HatMushroom.h
 *
 * 	Created on: 2022-3-9
 * 		Author: kkdud
 */

#ifndef __PLANT_HATMUSHROOM_H__
#define __PLANT_HATMUSHROOM_H__


#include "Projectile.h"
#include "PlantFramework.h"
#include "GameSubSystem.h"


class HatMushroomProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(HatMushroomProps, PlantPropertySheet, RtClass);

	HatMushroomProps()
	{
		DamageTimesLevel12 = 0;
		DamageTimesLevel345 = 0;
		DamageTimesPlantfood = 0;
		DamageTimesAvatar = 0;
		BackInTimeAtTimesLevel1 = 0;
		BackInTimeAtTimesLevel2345 = 0;
		Level5SpecialRate = 0.0f;
		DamageFactorLevel5 = 1.0f;
		DamageFactorPlantfood = 1.0f;
		DamageFactorAvatar = 1.0f;

		SpecialRateLevel1 = 0.0f;
		SpecialRateLevel2 = 0.0f;
		SpecialRateLevel345 = 0.0f;
		SpecialRateMagicLevel5 = 0.0f;
		LinkagePlantTypeName = "";
	}

	int DamageTimesLevel12;
	int DamageTimesLevel345;
	int DamageTimesPlantfood;
	int DamageTimesAvatar;
	int BackInTimeAtTimesLevel1;
	int BackInTimeAtTimesLevel2345;
	float Level5SpecialRate;
	float DamageFactorLevel5;
	float DamageFactorPlantfood;
	float DamageFactorAvatar;

	float SpecialRateLevel1;
	float SpecialRateLevel2;
	float SpecialRateLevel345;
	float SpecialRateMagicLevel5;
	std::string LinkagePlantTypeName;
};

class PlantHatMushroom : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantHatMushroom, PlantFramework, RtClass);

	PlantHatMushroom() {}

	void Initialize() override;
	void UpdateActions() override;

	bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;

	void onDestroy() override;

	Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;

	bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;

	std::vector<BoardEntity*> findAllTargetsAndSort();

	void updateFloorEffect();

private:
	std::vector<BoardEntityPtr> m_plantfoodTargetsLocked;
	RtWeakPtr<Effect_PopAnim> m_floorEffectPtr1;
	RtWeakPtr<Effect_PopAnim> m_floorEffectPtr2;
	Point m_floorEffectPoint;
};


class PlantAnimRig_HatMushroom : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_HatMushroom, PlantAnimRig, RtClass);

	std::string getPlantFoodOnAnimName() override { return "plantfood"; }
	std::string getPlantFoodMainAnimName() override { return "plantfood_loop"; }
	std::string getPlantFoodOffAnimName() override {return "plantfood_end"; }
};


class HatMushroomProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(HatMushroomProjectileProps, ProjectilePropertySheet, RtClass);

	HatMushroomProjectileProps()
	{
		BackInTimeDuration = 5.0f;
		HealEntsEntsCd = 0.0f;
	}

	float BackInTimeDuration;
	std::string VariationGeneratorTypeName;
	float VariationGeneratorHealthPersent;
	float HealEntsEntsCd;

	std::vector<std::string> BackListOfBackInTimeZombieTypeName;
	std::vector<std::string> BackListOfTransportZombieTypeName;
};


class HatMushroomProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(HatMushroomProjectile, Projectile, RtClass);

	HatMushroomProjectile() {}
	~HatMushroomProjectile() {}

	enum Type
	{
		HatMushroomProjectile_Normal,
		HatMushroomProjectile_FirstBack,
		HatMushroomProjectile_Lv5Special,
		HatMushroomProjectile_Plantfood,
		HatMushroomProjectile_Avatar,
		HatMushroomProjectile_Thorny,
	};

	void onProjectileInitialized() override;

	void SetOverrideTarget(BoardEntity* i_overrideTarget);
	void SetRotatedVelocity(float i_magnitude);

	bool canZomibeBeTransport(Zombie* i_zombie);

//	bool isInvalidZombieTarget(BoardEntity* i_entity);

	void setValues(Type i_type, int i_maxDamageTimes, float i_damageFactor, float i_backInTimeDuration = 0);

    bool FindNextTargetAndTrack();


protected:
	void registerForEvents() override;
	void onTargetDestroyed();

	void onDeflection(class BoardEntity* i_deflector) override;
	void moveThroughTime(pvztime_t i_dt) override;
	void getCollisionEntities(std::vector<BoardEntity*> &o_entities,const Rect& i_projectileRect) const override;

	float calcDesiredRot(SexyVector3 i_toTarget, float i_currentRot);
    SexyVector2 GetTargetCenter(BoardEntity* i_target) const;
    SexyVector3 GetTargetPos(BoardEntity* i_target) const;
    bool OnCollideEntity(BoardEntity* i_entity) override;
    bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
    void damageEntity(class BoardEntity* i_entity) override;
    void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;
    void onDraw(Graphics* i_g) override;

    void doTransportZombei(Zombie* i_zombie, float i_stuckDuration = 0.0f, float i_transportDistance = 0.0f);

	void fireThrons(BoardEntity* i_impactedEntity);
	void checkCollisionWithVariationGenerator();

	RtWeakPtr<BoardEntity> m_overrideTarget;
	bool m_deflected;
	bool m_targetDisappear;

	int m_damageTimes;
	std::map<BoardEntity*, int > m_damagedTargetsMap;
	Type m_type;
	int m_maxDamageTimes;
	float m_backInTimeDuration;
	float m_damageFactor;
	PlantPtr m_variationGenerator;

private:
	void onTargetDestroyedBase(BoardEntity* i_destroyedBoardEntity);
};


class HatMushroomProjectileThronProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(HatMushroomProjectileThronProps, ProjectilePropertySheet, RtClass);

	HatMushroomProjectileThronProps()
	{
		fieldOfFire = BoardConstants::GRIDSQUARE_WIDTH();
	}

	int fieldOfFire;
};


class HatMushroomProjectileThron : public Projectile
{
public:
	RT_CLASS_DEFINE(HatMushroomProjectileThron, Projectile, RtClass);

	void setIgnoreEntityPtr(BoardEntityPtr i_ignore) { m_ignoreEntityPtr = i_ignore; }

//	virtual void onProjectileInitialized() override;
	virtual void InitialSetPosition(const float i_x, const float i_y, const float i_z) override;
	virtual void onUpdate(pvztime_t i_dt) override;
	virtual void getCollisionEntities(std::vector<BoardEntity*> &o_entities,const Rect& i_projectileRect) const  override;

private:
	BoardEntityPtr m_ignoreEntityPtr;
	SexyVector3 m_originalPosition;
};

struct TransportingZombie
{
	TransportingZombie()
	{
		zombiePtr = nullptr;
		timer = PVZ_EOT();
		hasWarpOut = false;
		hasWarpIn = false;
		hasStuck = false;
		stuckDuration = false;
		transportDistance = 0.0f;
		turningPoint1 = 0.0f;
		turningPoint2 = 0.5f;
	}

	ZombiePtr zombiePtr;
	pvztime_t timer;
	bool hasWarpOut;
	bool hasWarpIn;
	bool hasStuck;
	float stuckDuration;
	float transportDistance;
	float turningPoint1;
	float turningPoint2;
};

class HatMushroomTransportSubSystem : public GameSubSystem
{
	RT_CLASS_DEFINE(HatMushroomTransportSubSystem, GameSubSystem, RtClass);

	virtual void registerForEvents() override;

	virtual void Update() override;

	void transportZombieToRightmostGrid(ZombiePtr i_zombiePtr,  float i_stuckDuration = 0.0f, float i_transportDistance = 0.0f);

	void onZombieConditionEnded(Zombie* i_zombie, int i_condition);
	void onZombieDestroyed(Zombie* i_zombie);
	void onZombieBleedingOut(Zombie *i_zombie, const DamageInfo* i_deathBlow);

	std::vector<TransportingZombie>::iterator getIteratorOfZombie(ZombiePtr i_zombiePtr);

private:
    void warpZombieOut(RtWeakPtr<Zombie> zombie, bool special);
	void warpZombieIn(RtWeakPtr<Zombie> zombie, bool special);
	void stuckZombie(RtWeakPtr<Zombie> zombie, float duration);
	void createStuckEffect(RtWeakPtr<Zombie> zombie, float duration);
	void reapearZombie(RtWeakPtr<Zombie> zombie);
	void placeZombieInNewPosition(RtWeakPtr<Zombie> zombie);
//	void createWarpingOutEffectAt(RtWeakPtr<Zombie> zombie);
//	void createWarpingInEffectAt(RtWeakPtr<Zombie> zombie);
	void createWarpingEffectAt(RtWeakPtr<Zombie> zombie, bool isUp, bool isSpecial);
	bool shouldDoStuffTo(RtWeakPtr<Zombie> zombie);
//	std::string getWarpingEffectNameFor(RtWeakPtr<Zombie> zombie);

	std::vector<TransportingZombie> m_transportingZombies;
	std::vector<TransportingZombie> m_newTransportZombies;
	std::vector<ZombiePtr> m_deadZombie;



};

#endif /* __PLANT_HATMUSHROOM_H__ */
