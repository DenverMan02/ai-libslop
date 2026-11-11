//
//  ZombiePropertySheet.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIEPROPERTYSHEET_H__
#define __ZOMBIEPROPERTYSHEET_H__

#include "Precompile.h"
#include "PropertySheetBase.h"
#include "ZombieEnums.h"
#include "RestrictionSet.h"
#include "ZombieSkillUtils.h"
#include "ProjectilePropertySheet.h"
#include "BoardEntity.h"
#include "ArmorPropertySheet.hpp"

struct ZombieAction
{
	ZombieAction()
	{
        Type = ZOMBIE_ACTION_NONE;
        
        ExplodeType = ZOMBIE_EXPLODE_NONE;
        
		DieAfterExplode = true;
        
		Damage          = 0;
        
        SummonNumMin = 0;
        SummonNumMax = 0;
        
        SummonName = "";
	}
    
    ZombieActionType Type;
    
    ZombieExplodeType ExplodeType;
    
	bool	DieAfterExplode;
	
	int		Damage;
    
    int     SummonNumMin;
    int     SummonNumMax;
    std::string SummonName;
};

struct ZombieLevelStat
{
	ZombieLevelStat()
	{
		AttackLevel = 1.0f;
		HitPointsLevel = 1.0f;
	}

	float AttackLevel;
	float HitPointsLevel;
};

struct ZombieSkillInfo
{
    ZombieSkillInfo()
    : lawnStrLevelContent("[PVP_ZOMBIE_LEVEL_UP_NEXT_CONTENT]")
    , iLevelUpNeedCoin(30000)
    , iLevelUpNeedTime(600)
    {
        
    }
    
    std::string lawnStrLevelContent;
    int iLevelUpNeedCoin;
    int iLevelUpNeedTime;
};

enum ZombieResistenceType
{
	ZombieResistenceType_None = -1,
	ZombieResistenceType_InstantKill,
	ZombieResistenceType_Physical,
	ZombieResistenceType_Poison,
	ZombieResistenceType_Lightning,
	ZombieResistenceType_Magic,
	ZombieResistenceType_Frost,
	ZombieResistenceType_Flame,
	ZombieResistenceType_Count
};

class ZombieResilience : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(ZombieResilience, PropertySheetBase, RtClass);

	ZombieResilience()
	: Amount(0.0f)
	, WeakType(ZombieResistenceType_None)
	, RecoverSpeed(0.0f)
	, DamageThresholdPerSecond(0.0f)
	, RecoverInterval(1.0f)
	, ResilienceBaseDamageThreshold(0.0f)
	, ResilienceExtraDamageThreshold(0.0f)
	{

	}

	float Amount;
	ZombieResistenceType WeakType;
	float RecoverSpeed;
	std::vector<std::string> AnimLabels;
	float DamageThresholdPerSecond;
	float RecoverInterval;
	float ResilienceBaseDamageThreshold;
	float ResilienceExtraDamageThreshold;
};

class ZombiePropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(ZombiePropertySheet, PropertySheetBase, RtClass);
	
	ZombiePropertySheet()
	: HitRect(0, 0, 42, 125), AttackRect(10, 10, 50, 125)
	, ArtCenter(135.0f, 160.0f), ShadowOffset(0.f, 0.f, 1.2f), ShadowScaling(1.0f, 1.0f)
	, StreetSize(2.0f, 2.0f), StreetCriticalSize(1.0f, 1.0f), StreetOffset(0.0f, -1.0f)
    ,FireDamageMultiplier(1.0f)
	{
		Speed = 0.16f;
		Hitpoints = 270.0f;
		MinLevel = 1;
		MaxLevel = 1;
		EatDPS = 100.0f;
		EatDPSRatio = -1.0f;
		Ammo = 0;
        PowerUpDamageModifier = 1.0;
		
        FireDamageMultiplier = 1.0f;
		CanSpawnPlantFood = false;
		CanTriggerZombieWin = true;
        CanSurrender = false;
		ExplodesWhenMowed = false;
		NormalDeathWhenMowed = false;
		IsValidPinchTarget = true;
        CanBeLaunchedByPlants = true;
        AffectedBySliders = true;
        ChillInsteadOfFreeze = false;
        CanBePlantTossedStrong = true;
        CanBePlantTossedWeak = true;
        
        HypnoshroomEffectOffset.x = 0;
		HypnoshroomEffectOffset.y = 63;

		DoAttack = false;
        DoSmashAttack = false;
		AttackDPS = 500.0f;
		AttackDistance = 1;
        
        // By default, arms drop at 66% health and heads drop at 33% health
		// If either value is set to -1, the body part will not fall off
		ArmDropFraction = 2.f / 3.f;
		HeadDropFraction = 1.f / 3.f;
		
		Helm = HELMTYPE_NONE;
        SizeType = ZOMBIE_SIZE_SMALL;
		HelmHitpoints = 0.0f;
		HelmDamageLayerIndices = 3;
		HelmAbsorbsOverflowDamage = false;
        
        MetallicBodyParts = false;
        
		SpeedVariance = 0.1f;
		
		GridHeight = 1;
		
		Cost = 150;
        CostBrain = 5;
		FirstWave = 1;
		WavePointCost = 100;
		Weight = 4000;
        AlmanacScale = 0;
        CanTakeWeapon = false;
        
        PacketCooldown = 5.0f;
        StartingCooldown = 0.0f;
        
        SkillInterval = 5.0f;
        
        CriticalPos = 0.2f;
        
        AwakenLevel = 1.0f;
        
        CanBeFlicked = true;
        CanBeFlickedOff = true;
        IgnoreWaterLine = false;
        MaxTideLoweredPercent = 0.f;
        GridExtents = Sexy::Point(1,1);
        DieFadeout = true;
        CanInvokeInvisible = true;
        //AwakenLevel = 1.0f;
        
        ShrunkenScale = 0.5f;
        
        ShrunkenScaleEx = 0.3f;
        
        PlantifyDuration = 0.5f;
        
        EnableAutoTest = true;

        ScoreOverride = 0;

		EliteScale = 2.0f;
		EliteScaleEx = 3.0f;
		EliteZombieType = EliteZombie_Invalid;
    	HurtDamageLimit = 0; 
    	DrawHealthBarTime = 4.0f;// for elite zombie , draw healthbar for how much time before it dissappear.
    	EnableShowHealthBarByDamage = false;
    	EnableEliteScale = false;
    	EnableEliteImmunities = false;
    	EnableNoInvincibleTakeDamage = false;
    	NoInvincibleTakeDamagePlantsList.clear();
	}
	
	float Speed;
	float SpeedVariance;
	float Hitpoints;
	int32 MinLevel;
	int32 MaxLevel;
	float EatDPS;
	float EatDPSRatio;
    float PowerUpDamageModifier;
	int32 Ammo;
    float FireDamageMultiplier;
	
	bool CanSpawnPlantFood;
	bool CanTriggerZombieWin;
    bool CanSurrender;
	bool ExplodesWhenMowed;
	bool NormalDeathWhenMowed;
	bool IsValidPinchTarget;
    bool CanBeLaunchedByPlants;
    bool AffectedBySliders;
    bool ChillInsteadOfFreeze;
    bool CanBePlantTossedStrong;
    bool CanBePlantTossedWeak;

	bool 	DoAttack;
    bool    DoSmashAttack;
	float 	AttackDPS;
	int 	AttackDistance;
    
    float HeadDropFraction;
	float ArmDropFraction;

    ZombieSizeType SizeType;
	HelmType Helm;
	float HelmHitpoints;
    int32 HelmDamageLayerIndices;
	bool HelmAbsorbsOverflowDamage;
    
    bool MetallicBodyParts;

	int32 GridHeight;
	Sexy::Rect HitRect;
	Sexy::Rect AttackRect;
	
	int32 Cost;
    int32 CostBrain;
	int32 FirstWave;
	int32 WavePointCost;
	int32 Weight;
	
	float ScoreOverride;

    bool PlaceOnStreet = true;
    SexyVector2 StreetSize;
    SexyVector2 StreetCriticalSize;
    SexyVector2 StreetOffset;
	
	SexyVector2 ArtCenter;
    SexyVector2 AlmanacOffset;
    float       AlmanacScale;
	SexyVector3 ShadowOffset;
    SexyVector2 ShadowScaling;
	std::string GroundTrackName;
    
    Sexy::Point GridExtents;
    
    SexyVector2 HypnoshroomEffectOffset;

    std::vector<ZombieAction>    EffectActions;
	std::vector<BoardEntityStat> ZombieStats;
	std::vector<ArmorPropertySheetPtr> ZombieArmorProps;
    std::vector<ZombieSkillInfo> ZombieSkillDisplay;
    
    bool IgnoreWaterLine;
    float MaxTideLoweredPercent;

    std::string SoundOnTakeDamage;
	//zombie star stats
	std::vector<ZombieLevelStat> ZombieLevelStats;
    
    bool CanTakeWeapon;

    float PacketCooldown;
    float StartingCooldown;
    
    pvztime_t   SkillInterval;
    std::vector<ZombieSkillData> ZombieSkillDataPool;
    
    float CriticalPos;
    
    float AwakenLevel;
    
    // Flicking
    bool CanBeFlicked;
    bool CanBeFlickedOff;
    bool DieFadeout;
    
    bool CanInvokeInvisible;
    
    float ShrunkenScale;
    
    float ShrunkenScaleEx;
    
    float PlantifyDuration;
    
    // Awaken
    //float AwakenLevel;
    
    bool EnableAutoTest;

	float EliteScale;
	float EliteScaleEx;
	EliteZombie_Type EliteZombieType;
    int HurtDamageLimit;
    float DrawHealthBarTime;// how many seconds duaring show health bar.
    bool EnableShowHealthBarByDamage;// enable show health bar by takedamage
    bool EnableEliteScale;// enable elite scale for normal zombie.
    bool EnableEliteImmunities;// enable elite immunities for normal zombie.
    bool EnableNoInvincibleTakeDamage;// enable take damage by no check invincible.
    std::vector<std::string> NoInvincibleTakeDamagePlantsList;// only check in list plants for enable no invincible take damage

    RtWeakPtr<const class ZombieResilience> Resilience;
};

class ZombieWithActionsProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieWithActionsProps, ZombiePropertySheet, RtClass);
    
	/// Actions
	std::vector<RtWeakPtr<class ZombieActionDefinition> > Actions;

	void GatherResourceRequirements(std::set<std::string>& io_resourceGroupNames) const override;
};

class ZombiePrototypeProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombiePrototypeProps, ZombiePropertySheet, RtClass);
	
	std::string StaticArtImageAsset;
	float ArtScale;
};

class ZombieMechProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieMechProps, ZombiePropertySheet, RtClass);
	
	ZombieMechProps()
		: NumDamageStates(0)
	{}
	
	std::string SoundOnDeactivate;
	std::string SoundOnActivate;
	
	int			NumDamageStates;
};

class ZombieMechFootballProps : public ZombieMechProps
{
public:
	RT_CLASS_DEFINE(ZombieMechFootballProps, ZombieMechProps, RtClass);
    ZombieMechFootballProps();
    ProjectilePropertySheetPtr Football;
	std::string SoundOnPush;
    std::string SoundOnThrow;
    float PushDamageToZombies;
    float FootballHeight;
    float FootballTimeOfFlight;
};

class ZombieMechDiscoProps : public ZombieMechProps
{
public:
	RT_CLASS_DEFINE(ZombieMechDiscoProps, ZombieMechProps, RtClass);
	
	float DanceCountdown;
	float DanceDuration;
	float SummonDuration;
	
	std::string SoundOnSummon;
};

struct ZombieGargantuarProjectilePair
{
    float HealthPercentThrowImp;
    std::vector<std::string> ProjectileLayersToHide;
};

class ZombieGargantuarProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieGargantuarProps, ZombiePropertySheet, RtClass);
    
    ZombieGargantuarProps()
	{
        MinPosXThrowImp = 0.0f;
        ThrowImpDuration = 0.0f;
        ImpTargetColumn = 0;
        ImpApex = 0.0f;
        ImpFlightTime = 0.0f;
        SmashDuration = 0.0f;
        SmashDamage = 1000.0f;
	}
    
    std::vector<ZombieGargantuarProjectilePair> HealthThresholdToImpAmmoLayers;
	
	float MinPosXThrowImp;
	float ThrowImpDuration;
	int ImpTargetColumn;
	float ImpApex;
	SexyVector3 ImpSpawnOffset;
	float ImpFlightTime;
	float SmashDuration;
    float SmashDamage;
	
	std::string ImpType;

	std::string SoundOnSmash;
	std::string SoundOnCannon;
};

class ZombieGargantuarMechProps : public ZombieGargantuarProps
{
public:
	RT_CLASS_DEFINE(ZombieGargantuarMechProps, ZombieGargantuarProps, RtClass);
	
	float EyeLaserDelayBetweenShots;
	float EyeLaserWarmUpTime;
	float EyeLaserSweepTime;
	float EyeLaserTotalDamage;
	
	float EyeLaserMinDistance;
	float EyeLaserMaxDistance;
	float EyeLaserSweepLength;
	
	std::string SoundOnDeactivate;
	std::string SoundOnActivate;
};

class ZombieCamelProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieCamelProps, ZombiePropertySheet, RtClass);
	
	ZombieCamelProps()
	{
		CamelSegmentOffset = 60;
		CamelSegmentTooCloseBuffer = 2;
		CamelSegmentTooFarBuffer = 6;
		
		WalkCycleOffset = -10;
		
		SpawnManyCamelSegmentAtPosition = 780;
		
		InitialFrontSignHealth = 250.0f;
		InitialBodySignHealth = 250.0f;
		SignHealthStates = 3;
		
		PropagateSignDamage = false;
		PropagateSignDestruction = false;
		DamagePropagationDelay = 25;
		
		OnlyHeadZombieEats = false;
		
		SurprisedTime = 300;
		
		DropArmOnSignDrop = true;
		SwitchToHeadCamelSign = true;
	}
	
	// Initial distance between segments for placement
	int32 CamelSegmentOffset;
	int32 CamelSegmentTooCloseBuffer;
	int32 CamelSegmentTooFarBuffer;
	
	// Amount of the walk cycle to offset each adjacent segment by (in frames)
	int32 WalkCycleOffset;

	// Many-camel spawn threshold
	// If the last zombie in our sequence is beyond this X value, spawn a new zombie
	int32 SpawnManyCamelSegmentAtPosition;
	
	// Sign health
	float InitialFrontSignHealth;
	float InitialBodySignHealth;
	int32 SignHealthStates; // norm, damage1, damage2. Must equal the number of art layers!

	// If set to 'true,' we propagate all damage down the length of the camel
	bool PropagateSignDamage;
	// If set to 'true,' when our sign is destroyed the rest of the camels' signs will also be destroyed
	bool PropagateSignDestruction;
	// Delay between propagating sign damage down the row of camels
	int32 DamagePropagationDelay;

	// If set to 'true,' only the head zombie will stop and eat,
	// and all other camel segments will walk through plants
	bool OnlyHeadZombieEats;

	// Number of seconds to remain 'surprised' after our sign is dropped
	float SurprisedTime;

	// Drop our arm as well as our sign
	bool DropArmOnSignDrop;

	// Switch to head camel sign when our leading Zombie dies
	bool SwitchToHeadCamelSign;
};

class ZombieCamelTouchProps : public ZombieCamelProps
{
public:
	RT_CLASS_DEFINE(ZombieCamelTouchProps, ZombieCamelProps, RtClass);
	
	ZombieCamelTouchProps()
	{
		PostMatchStunChance = 0.f;
		PostMatchStunDuration = 1.f;
	}
	
	float PostMatchStunChance;
	float PostMatchStunDuration;
};

class ZombieRaProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieRaProps, ZombiePropertySheet, RtClass);
	
	ZombieRaProps()
	{
		MaxClaimedSunCurrency = 250;
	}
	
	int MaxClaimedSunCurrency;
};


class ZombieTombRaiserProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieTombRaiserProps, ZombiePropertySheet, RtClass);
	
	ZombieTombRaiserProps()
	{
		TimeBetweenCasts = 0.f;
		TimeBetweenRaisings = 6.0f;
		NumberOfTombsToSpawn = 2;
	}
	
	float TimeBetweenCasts;
	float TimeBetweenRaisings;
	int32 NumberOfTombsToSpawn;
	ProjectilePropertySheetPtr Projectile;
};

class ZombieSarcophagusProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieSarcophagusProps, ZombiePropertySheet, RtClass);

	ZombieSarcophagusProps()
	{
		RunSpeed = 0.75f;
	}

	float RunSpeed;
};

class ZombiePirateCannonProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombiePirateCannonProps, ZombiePropertySheet, RtClass);
	
	ZombiePirateCannonProps()
	{
		InitialShotCooldown = 3.0f;
		ShotCooldown = 8.0f;
		ChanceImpFallsInWater = 0.1f;
        TimeToWalkInToPosition = 4.0f;
		ImpShotHeight = 80.f;
		ImpShotTime = 1.f;
		
		ExplosionImpSpawnCount = 10;
		ExplosionImpTargetColumnMin = 2;
		ExplosionImpTargetColumnMax = 9;
		ExplosionImpLaunchHeight = 180.f;
		ExplosionImpLaunchTime = 1.5f;
		ExplosionImpLaunchTimeVariance = 0.25f;
	}
	
	float InitialShotCooldown;
	float ShotCooldown;
	float ChanceImpFallsInWater;
    float TimeToWalkInToPosition;
	float ImpShotHeight;
	float ImpShotTime;
	
	int		ExplosionImpSpawnCount;
	int		ExplosionImpTargetColumnMin;
	int		ExplosionImpTargetColumnMax;
	float	ExplosionImpLaunchHeight;
	float	ExplosionImpLaunchTime;
	float	ExplosionImpLaunchTimeVariance;
};

class ZombiePirateCaptainProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombiePirateCaptainProps, ZombiePropertySheet, RtClass);
	
	ZombiePirateCaptainProps()
	{
		ParrotCooldown = 8.0f;
		ParrotRetryCooldown = 2.0f;
	}
	
	float ParrotCooldown;
	float ParrotRetryCooldown;
};

class ZombiePirateCaptainParrotProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombiePirateCaptainParrotProps, ZombiePropertySheet, RtClass);
	
	ZombiePirateCaptainParrotProps()
	{
		LiftSpeed = 100.0f;
		PlantLiftingWaitTime = 3.0f;
		ReturningToCaptainWaitTime = 3.0f;
	}
	
	float LiftSpeed;
	float PlantLiftingWaitTime;
	float ReturningToCaptainWaitTime;
};

class ZombieProspectorProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieProspectorProps, ZombiePropertySheet, RtClass);
	
	ZombieProspectorProps()
	{
		LaunchCountdown = 10.0f;
		TimeToTravel = 2.5f;
		Apex = 150.f;
		StunTime = 1.5f;
        restTime = 3;
	}
	
	float LaunchCountdown;
    float restTime;
	float TimeToTravel;
	float Apex;
	float StunTime;
};

class ZombieBullProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieBullProps, ZombiePropertySheet, RtClass);

	ZombieBullProps()
	{
		BullRunSpeed = 0.5;
		BullPawLocation = 800.0f;
		BullEnterSpeed = 0.3f;
	}

    Sexy::Rect BuckRect;
	float BullRunSpeed;
	float BullPawLocation;
	float BullEnterSpeed;
};

class ZombieBullRiderProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieBullRiderProps, ZombiePropertySheet, RtClass);

	ZombieBullRiderProps()
	{
		LaunchDistance = 200.0f;
		LaunchHeight = 200.0f;
		LaunchAirTime = 1.5f;
	}

	float LaunchDistance;
	float LaunchHeight;
	float LaunchAirTime;
};

class ZombiePonchoProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombiePonchoProps, ZombiePropertySheet, RtClass);

	ZombiePonchoProps()
	{
		PonchoHealth = 20.0f;
		PlateProbability = 0.5f;
		PlateHealth = 1100.0f;
	}

	float PonchoHealth;
	float PlateProbability;
	float PlateHealth;
};


class ZombieBarrelProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieBarrelProps, ZombiePropertySheet, RtClass);

	ZombieBarrelProps()
	{
		BurstDelay = 10.0f;
	}

	float BurstDelay;
    PlantRestrictionSet	TargetByWhitelist;
    PlantRestrictionSet PlantsWhichBreakBarrelOnCollision;
};

class ZombiePianoProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombiePianoProps, ZombiePropertySheet, RtClass);
	
	ZombiePianoProps()
	{
		FastMoveSpeed = 0.4f;
	}
	
	float FastMoveSpeed;
};

class ZombieExplorerProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieExplorerProps, ZombiePropertySheet, RtClass);
	
	ZombieExplorerProps()
	{
		MaxTorchReach = 80.f;
	}
	
	float MaxTorchReach;
};

class ZombieFutureJetpackProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieFutureJetpackProps, ZombiePropertySheet, RtClass);
	
	ZombieFutureJetpackProps()
	{
		DiscoMode = false;
	}
	
	bool DiscoMode;
};

class ZombieFutureProtectorProps : public ZombieMechProps
{
public:
	RT_CLASS_DEFINE(ZombieFutureProtectorProps, ZombieMechProps, RtClass);
	
	ZombieFutureProtectorProps()
	{
		ShieldActivationColumn = 15.f;
		ShieldSizeX = 3.0f;
		ShieldSizeY = 3.0f;
		ShieldHP = 1200.0f;
		ShieldCount = 1;
		ShieldReactivationDelay = -1.0f;
		ShieldDiesUponLossOfControl = true;
	}
	
	float	ShieldActivationColumn;
	float	ShieldSizeX;
	float	ShieldSizeY;
	float	ShieldHP;
	int32	ShieldCount;
	float	ShieldReactivationDelay;
	bool	ShieldDiesUponLossOfControl;
	
	std::string SoundOnShieldActivate;
	std::string SoundOnShieldDeactivate;
};

class ZombieSelfExplodeProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieSelfExplodeProps, ZombiePropertySheet, RtClass);
	
	ZombieSelfExplodeProps()
	{
		MaxTorchReach = 80.f;
	}
	
	float MaxTorchReach;
};

class ZombieGongProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieGongProps, ZombiePropertySheet, RtClass);
	
	ZombieGongProps()
	{
		ActionIntervalMin = 0.0f;
        ActionIntervalMax = 0.0f;
	}
    
    float	ActionIntervalMin;
	float	ActionIntervalMax;
};

class ZombieRocketProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieRocketProps, ZombiePropertySheet, RtClass);
	
	ZombieRocketProps()
	{
        FlyIntervalMin = 0.0f;
        FlyIntervalMax = 0.0f;
	}
    
    float	FlyIntervalMin;
	float	FlyIntervalMax;
};

class ZombieDrinkProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieDrinkProps, ZombiePropertySheet, RtClass);
	
	ZombieDrinkProps()
	{
		CrazySpeed = 0.75f;
        CrazyDamagePercent = 0.75f;
        CrazyHitPoints = 200.0f;
	}
    
    float CrazySpeed;
    float CrazyDamagePercent;
    float CrazyHitPoints;
};

class ZombieMonkDrinkProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieMonkDrinkProps, ZombiePropertySheet, RtClass);
	
	ZombieMonkDrinkProps()
	{
		CrazySpeed = 0.75f;
        CrazyDamagePercent = 0.75f;
        CrazyHitPoints = 200.0f;
        ChargeDamage = 0;
        CrazyChargeDamage = 0;
	}
    
    float CrazySpeed;
    float CrazyDamagePercent;
    float CrazyHitPoints;
    float ChargeDamage;
    float CrazyChargeDamage;
    Sexy::Rect ChargeAttackRect;
};

class ZombieStrongBronzeProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieStrongBronzeProps, ZombiePropertySheet, RtClass);
	
	ZombieStrongBronzeProps()
	{
		CrazySpeed = 0.75f;
        CrazyDamagePercent = 0.75f;
        CrazyHitPoints = 200.0f;
	}
    
    float CrazySpeed;
    float CrazyDamagePercent;
    float CrazyHitPoints;
};

class ZombieAgileBronzeProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieAgileBronzeProps, ZombiePropertySheet, RtClass);

	ZombieAgileBronzeProps()
	{
		GridWidthToJump = 1;
	}

    int  	GridWidthToJump;
};

class ZombieMonkImpProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieMonkImpProps, ZombiePropertySheet, RtClass);

	ZombieMonkImpProps()
	{
		StartGridColumn = 6;
		JumpGridColumnStride = 3;
		FlySpeedByGrid = 0.5f;
	}

	int StartGridColumn;
	int JumpGridColumnStride;
	float FlySpeedByGrid;
};

class ZombieMonkBladeProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieMonkBladeProps, ZombiePropertySheet, RtClass);
    
	ZombieMonkBladeProps()
	{
		StartGridColumn = 2;
		JumpGridColumnStride = 3;
	}
    
	int StartGridColumn;
	int JumpGridColumnStride;
};




class ZombieHammerProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieHammerProps, ZombiePropertySheet, RtClass);
	
	ZombieHammerProps()
	{
		LaunchCountdown = 10.0f;
		TimeToTravel = 2.5f;
        restTime = 3;
        ChargeDamage = 0;
        AdvanceSpin = false;
        SpinSpeed = 0;
        SpinDPS = 0;
	}
	
	float LaunchCountdown;
    float restTime;
	float TimeToTravel;
    float ChargeDamage;
    Sexy::Rect ChargeAttackRect;
    bool  AdvanceSpin;
    float SpinSpeed;
    float SpinDPS;
    Sexy::Rect SpinAttackRect;
};


class ZombieMonkNunchakuProps : public ZombieHammerProps
{
public:
	RT_CLASS_DEFINE(ZombieMonkNunchakuProps, ZombieHammerProps, RtClass);
    
	ZombieMonkNunchakuProps()
	{
	}
    
};


class ZombieQigongProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieQigongProps, ZombiePropertySheet, RtClass);
	
	ZombieQigongProps()
	{
		LaunchCountdown = 10.0f;
		TimeToTravel = 2.5f;
		Apex = 150.f;
		StunTime = 1.5f;
        restTime = 3;
	}
	
	float LaunchCountdown;
    float restTime;
	float TimeToTravel;
	float Apex;
	float StunTime;
};

class ZombieMagicBronzeProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieMagicBronzeProps, ZombiePropertySheet, RtClass);
	
	ZombieMagicBronzeProps()
	{
        
	}

	CZombieSummonDataPool		ZombieSummonDataPool;
};


class ZombieKongfuTorchProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieKongfuTorchProps, ZombiePropertySheet, RtClass);
	
	ZombieKongfuTorchProps()
	{
		MaxTorchReach = 80.f;
	}
	
	float MaxTorchReach;
};

class ZombieTreasureYetiProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieTreasureYetiProps, ZombiePropertySheet, RtClass);

	ZombieTreasureYetiProps()
	{
		WalkTime = 0.f;
	}

	float WalkTime;
};

class ZombossIceBallProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombossIceBallProps, ZombiePropertySheet, RtClass);
    
public:
    float ReduceHitPointPercent;
};

class ZombieTargetProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieTargetProps, ZombiePropertySheet, RtClass);
    
	ZombieTargetProps()
	{
        ProjectilePopAnim = "";
        SoundOnSpellActivate = "";
	}
    
    ValueRange FirstAttackColdDownTime;
    ValueRange AttackColdDownTime;
    
    std::string                         ProjectilePopAnim;
    std::string                         SoundOnSpellActivate;
    ProjectilePropertySheetPtr          Projectile;
};

class ZombieTargetGargantuarProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieTargetGargantuarProps, ZombiePropertySheet, RtClass);
    
	ZombieTargetGargantuarProps()
	{
        ImpTargetColumn = 0;
        
        ImpApex                     = 0.0f;
        ImpFlightTime               = 0.0f;
        SpecialAttackColdDownTime   = 0.0f;
        SpecialAttackRandomPercent  = 0.0f;
        WeakPrecent                 = 0.0f;
        SpecialAttackImpCount       = 0.0f;
        StrongPrecent               = 0.0f;
        
        ImpType = "";
        ProjectileLayersToHide.clear();
	}
    
    int ImpTargetColumn;
    
    float ImpApex;
    float ImpFlightTime;
    float SpecialAttackColdDownTime;
    float SpecialAttackRandomPercent;
    float WeakPrecent;
    float StrongPrecent;
    
    ValueRange AttackColdDownTime;
    ValueRange FirstAttackColdDownTime;
    
    int   SpecialAttackImpCount;
    
    std::string ImpType;
    std::vector<std::string> ProjectileLayersToHide;
    
    SexyVector3 ImpSpawnOffset;
};

class ZombieCavalryProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieCavalryProps, ZombiePropertySheet, RtClass);
    
	ZombieCavalryProps()
	{
		BullRunSpeed = 0.5;
		BullPawLocation = 800.0f;
		BullEnterSpeed = 0.3f;
        GunHitpoints = 500.0f;
        HorseHitpoints = 500.0f;
        RiderType = "dark_cavalry_rider";
	}
    
    Sexy::Rect BuckRect;
    Sexy::Rect GunRect;
    
    Sexy::Rect RiderAttackRect;
    
	float BullRunSpeed;
	float BullPawLocation;
	float BullEnterSpeed;
    float GunHitpoints;
    float HorseHitpoints;
    std::string RiderType;
};

class ZombieWolfBossProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieWolfBossProps, ZombiePropertySheet, RtClass);
    
	ZombieWolfBossProps()
	{
		
	}
    
    ValueRange FirstTakeSkill;
	ValueRange TakeSkillInterval;
};

class ZombieBeachFastSwimmerProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieBeachFastSwimmerProps, ZombiePropertySheet, RtClass);
    
	ZombieBeachFastSwimmerProps()
	{
		SwimSpeedMultiplier = 2.f;
	}
    
	float SwimSpeedMultiplier;
};

class ZombieBeachSurferProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieBeachSurferProps, ZombiePropertySheet, RtClass);
	float SurfSpeedMultiplier = 4.0f;
	float SurfboardAttackRectOffsetX = 0;
	PlantRestrictionSet BlocksSurfboard;
};

class ZombieBeachOctopusProps : public ZombieWithActionsProps
{
public:
	RT_CLASS_DEFINE(ZombieBeachOctopusProps, ZombieWithActionsProps, RtClass);
};

class ZombieBeachSnorkelProps : public ZombiePropertySheet
{
public:
	RT_CLASS_DEFINE(ZombieBeachSnorkelProps, ZombiePropertySheet, RtClass);
	std::vector<std::string> TargetByWhitelist;
	std::vector<std::string> DamageWhileSubmerged;
	std::vector<std::string> DamageWhileSubmergedPlantfoodOnly;
};

class ZombiePVPCannonProps : public ZombiePropertySheet
{
public:
    RT_CLASS_DEFINE(ZombiePVPCannonProps, ZombiePropertySheet, RtClass);
    
    ZombiePVPCannonProps()
    {
        InitialShotCooldown = 3.0f;
        ShotCooldown = 8.0f;
        ChanceImpFallsInWater = 0.1f;
        TimeToWalkInToPosition = 4.0f;
        ImpShotHeight = 80.f;
        ImpShotTime = 1.f;
        ChanceBigFire = 0.3f;
        
        ExplosionImpSpawnCount = 10;
        ExplosionImpTargetColumnMin = 2;
        ExplosionImpTargetColumnMax = 9;
        ExplosionImpLaunchHeight = 180.f;
        ExplosionImpLaunchTime = 1.5f;
        ExplosionImpLaunchTimeVariance = 0.25f;
    }
    
    float InitialShotCooldown;
    float ShotCooldown;
    float ChanceImpFallsInWater;
    float TimeToWalkInToPosition;
    float ImpShotHeight;
    float ImpShotTime;
    float ChanceBigFire;
    
    int		ExplosionImpSpawnCount;
    int		ExplosionImpTargetColumnMin;
    int		ExplosionImpTargetColumnMax;
    float	ExplosionImpLaunchHeight;
    float	ExplosionImpLaunchTime;
    float	ExplosionImpLaunchTimeVariance;
};

#endif // __ZOMBIEPROPERTYSHEET_H__
