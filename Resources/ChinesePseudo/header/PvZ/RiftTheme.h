/*
 * RiftTheme.h
 *
 *  Created on: 2020-6-3
 *      Author: Administrator
 */

#ifndef RIFTTHEME_H_
#define RIFTTHEME_H_

#include "PropertySheetBase.h"
#include "PVZTypes.h"
#include "Wave.h"
#include "ZombieEnums.h"
#include "Utils.h"
#include "RestrictionSet.h"
#include "DamageInfo.h"
#include "RainDarkModule.h"
#include "ComponentBase.h"
#include "Projectile.h"
#include "Plant_BoomFlower.h"

typedef RtWeakPtr<class RiftThemeProperties> RiftThemePropertiesPtr;
typedef RtWeakPtr<class RiftMainThemeProperties> RiftMainThemePropertiesPtr;

enum ThemeType
{
	Theme_Projectile_Hell,
	Theme_Defence_Nuke,
	Theme_Exploder,
	Theme_KOed,
	Theme_Gravity,
	Theme_TougherZombie,
	Theme_Rift,
	Theme_ZombossRevenge,
	Theme_InvisibleMadness,
	Theme_TinyRusher,
	Theme_SunFlyingOut,
	Theme_DarknessCrazy,
	Theme_FunnyChristmas,
	Theme_ArtOfGravestone,
	Theme_PlantExploder,
	Theme_PlantArtOfAOE,
	Theme_PlantArtOfDefence,
	Theme_PlantArtOfMelee,
	Theme_AcidLemons,
	Theme_PlantsRain,
	Theme_WealthComing,
	Theme_SpawnOffset,
	Theme_FireReduce,
	Theme_LightingReduce,
	Theme_ColdReduce,
	Theme_HeavyBallon,
	Theme_MinerCheating,
	Theme_KnightCheating,
	Theme_MageCheating,
	Theme_Balloon,
	Theme_Lightning,
	Theme_PiggyBank,
	Theme_PlantSeed,
	Theme_EnergyFly,
};

class RiftMainThemeProperties : public PropertySheetBase
{
	RT_CLASS_DEFINE(RiftMainThemeProperties, PropertySheetBase, RtClass);

	std::string Description;
	std::string Name;
	ThemeType Type;
	std::vector<std::string> ThemeNames;

	virtual SexyString GetDescription();
	virtual SexyString GetName();
};

class RiftThemeProperties : public PropertySheetBase
{
	RT_CLASS_DEFINE(RiftThemeProperties, PropertySheetBase, RtClass);

	std::string TypeName;
	std::string ClassName;
};

class RiftTheme : public GameObject
{
public:
	RT_CLASS_DEFINE(RiftTheme, GameObject, RtClass);
	RiftTheme();
	virtual ~RiftTheme();
	virtual void Initialize(RiftThemePropertiesPtr i_propsPtr);
	RiftThemePropertiesPtr GetProps() { return m_props; }
	virtual void Activate();
	virtual void Update() {}

	bool IsActivated() { return m_activated; }

protected:
	RiftThemePropertiesPtr m_props;
	bool m_activated;
};

class RiftThemeJunggledProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeJunggledProperties, RiftThemeProperties, RtClass);

	RiftThemeJunggledProperties()
		: MaxProjectilesToJuggle(3)
		, JuggleLaunchDelay(2.0f)
		, MoveSpeedMultiplierWhileJuggling(0.8f)
		, CatchArcDegrees(120.0f)
	{}

	SexyVector3 LaunchVelocity;
	SexyVector3 LaunchAcceleration;
	ValueRange LaunchHeight;

	int MaxProjectilesToJuggle;
	float JuggleLaunchDelay;
	float MoveSpeedMultiplierWhileJuggling;
	float CatchArcDegrees;

	std::vector<std::string> JuggleableProjectiles;
	std::vector<std::string> UnthrowableProjectiles;
	std::vector<std::string> AngleAgnosticProjectiles;
};

class RiftThemeJunggled : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeJunggled, RiftTheme, RtClass);

	void Activate() override;
	void syncProps();
};

class RiftThemeHealthDebuffProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeHealthDebuffProperties, RiftThemeProperties, RtClass);

	RiftThemeHealthDebuffProperties()
		: HealthPercent(1.0f)
	{}

	PlantRestrictionSet TargetablePlantTypes;
	float HealthPercent;
};

class RiftThemeHealthDebuff : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeHealthDebuff, RiftTheme, RtClass);
	~RiftThemeHealthDebuff();

	void Activate() override;

private:
	void OnCreatePlant(class Plant* plant);
};

class RiftThemeExploderProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeExploderProperties, RiftThemeProperties, RtClass);

	RiftThemeExploderProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	ZombieRestrictionSet TargetableZombieTypes;
};

class RiftThemeExploder : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeExploder, RiftTheme, RtClass);
	~RiftThemeExploder();

	void Activate() override;

private:
	void onZombieDied(class Zombie* zombie, const DamageInfo* i_deathBlow);
	void TryExplode(Zombie* zombie);
	void DoExplode(int i_column, int i_row);
};

class RiftThemeNoPlantfoodProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeNoPlantfoodProperties, RiftThemeProperties, RtClass);

	RiftThemeNoPlantfoodProperties()
	{}

	PlantRestrictionSet TargetablePlantTypes;
};

class RiftThemeNoPlantfood : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeNoPlantfood, RiftTheme, RtClass);

	void Activate() override;

	bool CanApplyPlantfood(class Plant* i_plant);
};

class RiftThemeArmoredProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeArmoredProperties, RiftThemeProperties, RtClass);

	RiftThemeArmoredProperties()
	: LinePosition(0.0f)
	, KnightHelmHitpoints(0.0f)
	, KnightHelm(HELMTYPE_CONE)
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	HelmType KnightHelm;
	float KnightHelmHitpoints;
	std::vector<std::string> ValidKnightTargets;
	float LinePosition;
};

class RiftThemeArmored : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeArmored, RiftTheme, RtClass);

	void Activate() override;
	void syncProps();

	void onZombieReachLine(class Zombie* zombie);

private:
	bool isValidKnightingTarget(Zombie* i_zombie);
};

class RiftThemeReduceRangeProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeReduceRangeProperties, RiftThemeProperties, RtClass);

	RiftThemeReduceRangeProperties()
	: ReducedGrids(0)
	{}

	PlantRestrictionSet TargetablePlantTypes;
	int ReducedGrids;
};

class RiftThemeReduceRange : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeReduceRange, RiftTheme, RtClass);

	void Activate() override;
	void syncProps();
};

class RiftThemeLimitedSeedPacketProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeLimitedSeedPacketProperties, RiftThemeProperties, RtClass);

	RiftThemeLimitedSeedPacketProperties()
	: DisabledPlantNum(0)
	{}

	int DisabledPlantNum;
};

class RiftThemeLimitedSeedPacket : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeLimitedSeedPacket, RiftTheme, RtClass);

	void Activate() override;
	void GetNameBlackList(std::vector<std::string>& i_list);

private:
	void DisableSeedPackets();

	std::vector<std::string> m_plantBlacklist;
};

class RiftThemeZombieSpeedProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeZombieSpeedProperties, RiftThemeProperties, RtClass);

	RiftThemeZombieSpeedProperties()
	: SpeedScale(0.0f)
	{}

	ZombieRestrictionSet TargetableZombieTypes;
	float SpeedScale;
};

class RiftThemeZombieSpeed : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeZombieSpeed, RiftTheme, RtClass);
	~RiftThemeZombieSpeed();

	void Activate() override;

private:
	void onZombiePlaceOnBoard(class Zombie* zombie);
};

class RiftThemeZombossReviveProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeZombossReviveProperties, RiftThemeProperties, RtClass);

	RiftThemeZombossReviveProperties()
	: ReviveCount(0)
	{}

	ZombieRestrictionSet TargetableZombieTypes;
	int ReviveCount;
};

class RiftThemeZombossRevive : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeZombossRevive, RiftTheme, RtClass);
	RiftThemeZombossRevive();

	void Activate() override;
	bool TryRevive();

private:
	int m_reviveCount;
};

class RiftThemeInvisibleProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeInvisibleProperties, RiftThemeProperties, RtClass);

	RiftThemeInvisibleProperties()
	{}

	ZombieRestrictionSet TargetableZombieTypes;
};

class RiftThemeInvisible : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeInvisible, RiftTheme, RtClass);
	~RiftThemeInvisible();

	void Activate() override;

private:
	void onZombiePlaceOnBoard(class Zombie* zombie);
};

class RiftThemeShrunkenProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeShrunkenProperties, RiftThemeProperties, RtClass);

	RiftThemeShrunkenProperties()
	{}

	ZombieRestrictionSet TargetableZombieTypes;
	float ModifiedScale;
	float ModifiedSpeed;
};

class RiftThemeShrunken : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeShrunken, RiftTheme, RtClass);
	~RiftThemeShrunken();

	void Activate() override;

private:
	void onZombiePlaceOnBoard(class Zombie* zombie);
};

class RiftThemeSunDrainProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeSunDrainProperties, RiftThemeProperties, RtClass);

	RiftThemeSunDrainProperties()
	{}

	float StartDealy;
	float TriggerInterval;
	int DrainAmount;
};

class RiftThemeSunDrain : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeSunDrain, RiftTheme, RtClass);
	~RiftThemeSunDrain();

	void Activate() override;
	void Update() override;

private:
	void onGamePlayStarted();
	void drainSun(int i_amount);

	pvztime_t m_nextStartTime;
};

class RiftThemeRainDarkProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeRainDarkProperties, RiftThemeProperties, RtClass);

	RiftThemeRainDarkProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float TriggerInterval;
	float Duration;
};

class RiftThemeRainDark : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeRainDark, RiftTheme, RtClass);
	~RiftThemeRainDark();

	void Activate() override;
	void Update() override;

private:
	void onGamePlayStarted();
	void enterDarkness(float i_duration);

	pvztime_t m_nextStartTime;
	pvztime_t   m_nextRainDrop;
	RainDropper m_RainDropper;
};

class RiftThemeBlizzardProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeBlizzardProperties, RiftThemeProperties, RtClass);

	RiftThemeBlizzardProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float TriggerInterval;
	float TakeEffectDelay;
};

class RiftThemeBlizzard : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeBlizzard, RiftTheme, RtClass);
	~RiftThemeBlizzard();

	void Activate() override;
	void Update() override;

private:
	void onGamePlayStarted();
	void triggerBlizzard();
	void createBlizzardEffect();
	void AddSnowman(class Zombie* zombie);
	void effectEntities();
	bool CheckZombieCanBeSnowman(class Zombie* zombie);
	class Effect_PopAnim* CreateProjectileEffectByBoardSpace(const std::string pamName, const std::string animName, SexyVector3 pos, int renderOrder);

	pvztime_t m_nextStartTime;
	pvztime_t m_takeEffectTime;
};

class RiftThemeGravestoneProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeGravestoneProperties, RiftThemeProperties, RtClass);

	RiftThemeGravestoneProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	ZombieRestrictionSet TargetableZombieTypes;
};

class RiftThemeGravestone : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeGravestone, RiftTheme, RtClass);
	~RiftThemeGravestone();

	void Activate() override;

private:
	void onZombieDied(class Zombie* zombie, const DamageInfo* i_deathBlow);
	void TrySpawnGravestone(Zombie* zombie);
};

class RiftThemeBuffExploderProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeBuffExploderProperties, RiftThemeProperties, RtClass);

	RiftThemeBuffExploderProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	PlantRestrictionSet TargetablePlantTypes;
	float ExplodeDamage;
};

class RiftThemeBuffExploder : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeBuffExploder, RiftTheme, RtClass);
	~RiftThemeBuffExploder();

	void Activate() override;

private:
	void OnPlantDestroyed(class Plant* plant);
	void TryExplode(class Plant* plant);
	void DoExplode(int i_column, int i_row);
};

class RiftThemeBuffPlantAOEProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeBuffPlantAOEProperties, RiftThemeProperties, RtClass);

	RiftThemeBuffPlantAOEProperties()
		: DamagePercent(1.0f)
		, SunReducedRate(1.0f)
	{}

	PlantRestrictionSet TargetablePlantTypes;
	float DamagePercent;
	float SunReducedRate;
};

class RiftThemeBuffPlantAOE : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeBuffPlantAOE, RiftTheme, RtClass);
	~RiftThemeBuffPlantAOE();

	void Activate() override;
	void GetReducedSunCost(const std::string& i_typeName, int& i_cost);

private:
	void OnCreatePlant(class Plant* plant);
	bool CanReduceSunCost(const std::string& i_typeName);
};

class RiftThemeBuffPlantFastCDProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeBuffPlantFastCDProperties, RiftThemeProperties, RtClass);

	RiftThemeBuffPlantFastCDProperties()
		: ReducedCooldown(1.0f)
	{}

	PlantRestrictionSet TargetablePlantTypes;
	float ReducedCooldown;
};

class RiftThemeBuffPlantFastCD : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeBuffPlantFastCD, RiftTheme, RtClass);
	~RiftThemeBuffPlantFastCD();

	void Activate() override;
	void GetReducedCD(PlantTypePtr i_type, float& i_cd);

private:
	bool CanReduceCD(PlantTypePtr i_type);
};

class RiftThemeBuffPlantMeleeProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeBuffPlantMeleeProperties, RiftThemeProperties, RtClass);

	RiftThemeBuffPlantMeleeProperties()
		: DamagePercent(1.0f)
	{}

	PlantRestrictionSet TargetablePlantTypes;
	float DamagePercent;
};

class RiftThemeBuffPlantMelee : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeBuffPlantMelee, RiftTheme, RtClass);
	~RiftThemeBuffPlantMelee();

	void Activate() override;

private:
	void OnCreatePlant(class Plant* plant);
};

class LemonRainDropperEffectAnim : public Effect_PopAnim
{
public:

    RT_CLASS_DEFINE(LemonRainDropperEffectAnim, Effect_PopAnim, RtClass);

    void onAnimStopped(const std::string& i_animLabel) override;

    void SetEntity(BoardEntityPtr pTarget);
    void SetDamageRate(float i_damageRate) { m_damageRate = i_damageRate; }

private:
    float m_damageRate;
    BoardEntityPtr m_pTargetEntity;
};

class LemonRainDropper
{
public:
	LemonRainDropper();

	void Start(pvztime_t i_duration, int i_shotTotal);
	void Update();
	static bool TargetIsValid(BoardEntity* target);
	void SetDamageRate(float i_damageRate) { m_damageRate = i_damageRate; }

private:
	void GenerateLemonRain(int iX, int iY, BoardEntityPtr ptrTarget);

    pvztime_t m_shotsPerSecond;
	pvztime_t m_startTime;
	int       m_shotsFired;
	int       m_shotTotal;
	std::vector<BoardEntityPtr> m_targets;
	float m_damageRate;
};

class RiftThemeRainLemonProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeRainLemonProperties, RiftThemeProperties, RtClass);

	RiftThemeRainLemonProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float TriggerInterval;
	float DamageRate;
};

class RiftThemeRainLemon : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeRainLemon, RiftTheme, RtClass);
	~RiftThemeRainLemon();

	void Activate() override;
	void Update() override;

private:
	void onGamePlayStarted();

	pvztime_t m_nextStartTime;
	LemonRainDropper m_RainDropper;
};

class RiftThemeLightningProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeLightningProperties, RiftThemeProperties, RtClass);

	RiftThemeLightningProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float TriggerInterval;
	float DamageRate;
};

class RiftThemeLightning : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeLightning, RiftTheme, RtClass);
	~RiftThemeLightning();

	void Activate() override;
	void Update() override;
	void LightningTrigger();

private:

	void onGamePlayStarted();
	void DoTrigger(Point i_grid);
	void OnEffectDone1(class StandaloneEffect* i_effect);
	void OnEffectDone2(class StandaloneEffect* i_effect);
	void OnEffectDone3(class StandaloneEffect* i_effect);
	void DoDamage(int x ,int y ,float damageNum);
	void TakeLightningDamage(BoardEntity* i_entity,bool die);
	pvztime_t m_nextStartTime;
	bool m_Triggerstate = false;
	Point m_target;
	float m_temp_temp = 0;
	SexyVector3 LightingOffset1 = SexyVector3{0,0,0};
	SexyVector3 LightingOffset2 = SexyVector3{0,-20,0};
//	SexyVector3 LightingOffset2 = SexyVector3{-70,-95,0};
};


//balloon
class BalloonDropper
{
public:
	BalloonDropper();

	void Update();
	static bool TargetIsValid(BoardEntity* target);
	void SetDamageRate(float i_damageRate) { m_damageRate = i_damageRate; }

private:

    pvztime_t m_shotsPerSecond;
	pvztime_t m_startTime;
	int       m_shotsFired;
	int       m_shotTotal;
	std::vector<BoardEntityPtr> m_targets;
	float m_damageRate;
};



class RiftThemeBalloonProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeBalloonProperties, RiftThemeProperties, RtClass);

	RiftThemeBalloonProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float TriggerInterval;
	float DamageRate;
};

class RiftThemeBalloon : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeBalloon, RiftTheme, RtClass);
	~RiftThemeBalloon();

	void Activate() override;
	void Update() override;

private:
	void onGamePlayStarted();

	pvztime_t m_nextStartTime;
//	LemonRainDropper m_RainDropper;
	BalloonDropper m_RainDropper;
};


class RiftThemePiggyBankProperties : public RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemePiggyBankProperties, RiftThemeProperties, RtClass);

	RiftThemePiggyBankProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

};

class RiftThemePiggyBank : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemePiggyBank, RiftTheme, RtClass);
	RiftThemePiggyBank();
	~RiftThemePiggyBank();

	void Activate() override;
	void onZombieDied(Zombie* zombie, const DamageInfo* i_deathBlow);
	void OnGridItemGravestoneCoinOnDestructionKilled(class GridItemGravestoneCoinOnDestruction* i_coinStone);
private:
	int m_productCoin;
};


class RiftThemePlantSeedProperties : public RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemePlantSeedProperties, RiftThemeProperties, RtClass);

	RiftThemePlantSeedProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<std::string> PlantBlackList;
};

class RiftThemePlantSeed : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemePlantSeed, RiftTheme, RtClass);
	RiftThemePlantSeed();
	~RiftThemePlantSeed();

	void Activate() override;

	void onPlantLost(class Plant* i_plant);
    // void onLilyPadDied(class GridItemLilyPad* i_lilyPad);
	// void onFlowerPotDied(class GridItemFlowerPot* i_flowerPot);
	void handlePlantDied(class Plant* i_plant);

private:
	int m_productCoin;
};


class RiftThemeEnergyFlyProperties : public RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeEnergyFlyProperties, RiftThemeProperties, RtClass);

	RiftThemeEnergyFlyProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	std::vector<std::string> PlantBlackList;
	float EnergyCostOnPlantPlanted;
};

class RiftThemeEnergyFly : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeEnergyFly, RiftTheme, RtClass);
	RiftThemeEnergyFly();
	~RiftThemeEnergyFly();

	void Activate() override;

	void onPlantPlanted(class Plant* i_plant);
	void handlePlantPlanted(class Plant* i_plant);

private:
	int m_productCoin;
};


class RiftThemeSeedRainProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeSeedRainProperties, RiftThemeProperties, RtClass);

	RiftThemeSeedRainProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override {}
};

class RiftThemeSeedRain : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeSeedRain, RiftTheme, RtClass);
	~RiftThemeSeedRain(){}
};

class RiftThemeWealthGodProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeWealthGodProperties, RiftThemeProperties, RtClass);

	RiftThemeWealthGodProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override {}
};

class RiftThemeWealthGod : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeWealthGod, RiftTheme, RtClass);
	~RiftThemeWealthGod(){}
};

class RiftThemeZombieSpawnOffsetProperties : public RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeZombieSpawnOffsetProperties, RiftThemeProperties, RtClass);
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override {}
};

class RiftThemeZombieSpawnOffset : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeZombieSpawnOffset, RiftTheme, RtClass);
	void Activate() override;
};


class RiftThemeFireReduceProperties : public RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeFireReduceProperties, RiftThemeProperties, RtClass);
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override {}
};

class RiftThemeFireReduce : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeFireReduce, RiftTheme, RtClass);
	~RiftThemeFireReduce();
	void Activate() override;
private:
	void OnZombieConditionPrepare(class Zombie* i_zombie, int* i_condition, pvztime_t* i_duration);
	void onZombiePlaceOnBoard(class Zombie* zombie);
};


class RiftThemeLightingReduceProperties : public RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeLightingReduceProperties, RiftThemeProperties, RtClass);
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override {}
};

class RiftThemeLightingReduce : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeLightingReduce, RiftTheme, RtClass);
	~RiftThemeLightingReduce();
	void Activate() override;
private:
	void OnZombieConditionPrepare(class Zombie* i_zombie, int* i_condition, pvztime_t* i_duration);
	void onZombiePlaceOnBoard(class Zombie* zombie);
};


class RiftThemeColdReduceProperties : public RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeColdReduceProperties, RiftThemeProperties, RtClass);
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override {}
};

class RiftThemeColdReduce : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeColdReduce, RiftTheme, RtClass);
	~RiftThemeColdReduce();
	void Activate() override;
private:
	void OnZombieConditionPrepare(class Zombie* i_zombie, int* i_condition, pvztime_t* i_duration);
	void onZombiePlaceOnBoard(class Zombie* zombie);
};

class RiftThemeHeavyBallonProperties : public RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeHeavyBallonProperties, RiftThemeProperties, RtClass);
	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override {}
};

class RiftThemeHeavyBallon : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeHeavyBallon, RiftTheme, RtClass);
};

class RiftThemeCrossFireProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeCrossFireProperties, RiftThemeProperties, RtClass);

	RiftThemeCrossFireProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override {}
};

class RiftThemeCrossFire : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeCrossFire, RiftTheme, RtClass);
	~RiftThemeCrossFire(){}
};

class RiftThemeChargingProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeChargingProperties, RiftThemeProperties, RtClass);

	RiftThemeChargingProperties()
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override {}
};

class RiftThemeCharging : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeCharging, RiftTheme, RtClass);
	~RiftThemeCharging(){}
};

class RiftThemeFastSpellProperties : RiftThemeProperties
{
public:
	RT_CLASS_DEFINE(RiftThemeFastSpellProperties, RiftThemeProperties, RtClass);

	RiftThemeFastSpellProperties()
	: ReducedCooldownRate(0.0f)
	{}

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;

	float ReducedCooldownRate;
};

class RiftThemeFastSpell : public RiftTheme
{
public:
	RT_CLASS_DEFINE(RiftThemeFastSpell, RiftTheme, RtClass);
	~RiftThemeFastSpell(){}

	const float GetReducedCDRate();
};

#endif /* RIFTTHEME_H_ */
