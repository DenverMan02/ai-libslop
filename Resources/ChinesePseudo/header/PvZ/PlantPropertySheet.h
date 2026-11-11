//
//  PlantPropertySheet.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/26/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PLANTPROPERTYSHEET_H__
#define __PLANTPROPERTYSHEET_H__

#include "Precompile.h"
#include "PlantEnums.h"
#include "ProjectileEnums.h"
#include "PropertySheetBase.h"
#include "RtObject.h"
#include "ProjectilePropertySheet.h"
#include "BoardEntity.h"
#include "SkillPropertySheet.h"
#include "PlantDisplayBoard.h"
#include "PowerSet.h"

struct PlantAction
{
	PlantAction()
	{
		Type = PLANT_ACTION_NONE;
		ExplodeType = SPLASH_DAMAGE_EXPLODE_NONE;
        ExplodeRadius = 0.0;
		TriggerType = PLANT_ACTION_TRIGGER_NONE;
		
		DieAfterExplode = true;
		
		InitialMinCooldownTime = 0.0f;
		CooldownTimeMin = 0.85f;
		CooldownTimeMax = 1.0f;
        
		Damage = 0;
		XVelocityOverride = 0;
		Burns = false;
		PushbackAmount = 0;
		ChillDuration = FreezeDuration = StunDuration = 0.0f;
		SplashDamage = 0;
		SecondaryAction = false;
	}
	
	PlantActionType 		Type;
	ProjectilePropertySheetPtr Projectile;
	SplashDamageType 		ExplodeType;
    float			    ExplodeRadius;
	PlantActionTriggerType 	TriggerType;

	bool	DieAfterExplode;	// If true, and 'Type' is EXPLODE, we Die() immediately afterwards (was m_keepAlive)
	
	float	InitialMinCooldownTime; // When spawning or post-plantfood, use this for the 'minimum' possible recharge time
	float	CooldownTimeMin;	// Reduces the launch timer by a maximum of this amount (randomly) after every shot
	float	CooldownTimeMax;	// Number of seconds to wait between projectile fires (at most)
	
	int		Damage;				// Amount of damage to apply
	float	XVelocityOverride;	// PROTOTYPE: Override the velocity of a projectile
	
	bool	Burns;				// If 'true,' then damage both shield and body and apply an ash effect if this attack kills
	int		PushbackAmount;		// If non-zero, then push affected zombies backwards that far
	float	ChillDuration;		// Amount of time to chill affected zombies for
	float	FreezeDuration;		// Amount of time to freeze affected zombies in place
	float	StunDuration;		// Amount of time to leave hit zombies stunned for (butter!)
	
	float SplashDamage;//yaomeile add
	std::string ProjectileLaunchSound;
	
	Sexy::Rect	RectTriggerRange;	// Bounding region for a RECT type trigger, offset from plant's position in board-space pixels
	
	SexyVector2	SpawnOffset;	// Offset from our position for spawned projectiles or coins

	bool	SecondaryAction;	// If true, this action must be manually fired from special code
};

struct PlantLevelStat
{
	PlantLevelStat()
	{
		AttackLevel = 1.0f;
		HitPointsLevel = 1.0f;
		MaxAffectZombieLevel = 99;
	}

	float AttackLevel;
	float HitPointsLevel;
	SkillPropertySheetPtr PropertySkillType;
	SkillPropertySheetPtr AdvancedSkillType;
	int MaxAffectZombieLevel;
	//std::vector<SkillPropertySheetPtr> SkillTypes;

};

enum PlantDamageType
{
	TYPE_NORMAL,
	TYPE_FLAME,
	TYPE_COLD,
	TYPE_LIGHTNING,
	TYPE_EXPLODE,
	TYPE_POISON,
	TYPE_MAGIC,
};

typedef RtWeakPtr<class DisplayActionsPropertySheet> DisplayActionsPropertySheetPtr;

class DisplayActionsPropertySheet : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(DisplayActionsPropertySheet, PropertySheetBase, RtClass);
    
    std::vector<DisplayActionInfo> Actions;
};

typedef RtWeakPtr<class DisplayAvatarActionsPropertySheet> DisplayAvatarActionsPropertySheetPtr;

class DisplayAvatarActionsPropertySheet : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(DisplayAvatarActionsPropertySheet, PropertySheetBase, RtClass);
    
    std::vector<DisplayActionInfo> Actions;
};

struct PlantDetailsInfo
{
	std::vector<PlantDetailsType> DetailsList;

    std::vector<int> CostOverride;
    std::vector<float> PacketCooldownOverride;
	std::vector<int> HitpointsOverride;

	std::vector<float> Damages;
	std::vector<float> AttackInterval;
	std::vector<std::string> Ranage;
	std::vector<std::string> Area;
	std::vector<float> Rest;
	std::vector<float> Duration;
	std::vector<int> SunYield;
	std::vector<float> SunYieldInterval;
};


class PlantPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(PlantPropertySheet, PropertySheetBase, RtClass);

	PlantPropertySheet()
    : IdleAnimationWeights()
	{
		Cost = 0;
		BeghouledCost = 0;
        SaveCostInHomeWorld = 0;
		Hitpoints = 0.0f;
        MinLevel = 0;
        MaxLevel = 0;
		PacketCooldown = 0.0f;
		StartingCooldown = 0.0f;
		PlantFoodDurationSeconds = 0.0f;
		PlantFoodPlayCount = 0;
		PlantGridType = PLANT_GRID_PLANTING_GROUND;
		GridWidth = GridHeight = 1;
		Height = ENTITYHEIGHT_NORMAL;
		PlantingOffsetY = 0.f;
		DangerRoomWeight = 100;
		RestrictPlantingToGridArea = Sexy::Rect(0,0,0,0); // Default value indicates free placement
		CanReceiveFirstAid = false;
		IsConsumable = false;
        CanLiveOnWaves = false;
        CanPlantAgainToUpgrade = false;
        CanLiveInSky = false;
        IsPultPlant = false;
        BoostRate = 0.0f;
        //DamageType = TYPE_NORMAL;
        AwakenLevel = 1.0f;
        ViewScale = 1.f;
        ViewOffset = { 0.f, 0.f };
        SeedChooserPreviewAdjust = { 0.f, 0.f };
		GridExtents = Sexy::Point(1, 1);
		MultiPlantLayer = MULTI_PLANT_GRID_LAYER_MAIN;
	}

	Sexy::Point GridExtents;
	int32 Cost;								// m_cost
	int32 BeghouledCost;					// Beghouled cost
    int32 SaveCostInHomeWorld;              // m_saveCostInHomeWorld;
	float Hitpoints;						// m_life
    int32 MinLevel;                         // m_minLevel;
    int32 MaxLevel;                         // m_maxLevel;
	float PacketCooldown;					// m_packetCooldown
	float StartingCooldown;					// m_startingCooldown
	float PlantFoodDurationSeconds;			// m_plantFoodDuration (was int, need to convert to ticks)
	int32 PlantFoodPlayCount;				// m_plantFoodLoopCount
	std::string PlantFoodActivationSound;	//
    std::string HelpedActivationSound;		//
	PlantGridPlantingType PlantGridType;	// m_plantGridType
    PowerSet Powers;
	std::vector<PlantAction> Actions;		// m_actions
	int32 GridWidth;						// m_gridWidth
	int32 GridHeight;						// m_gridHeight
	float PlantingOffsetY;					// Height offset into the grid cell from the normal planting position for this plant. Affects grid selection when planting.
	SexyVector2 CursorPreviewOffset; 		// Board-space offset of the plant
	SexyVector2 ArtCenter;					// m_artCenterX, m_artCenterY
	Sexy::Rect HitRectAdjust;				// m_hitRectAdj
	BoardEntityHeight Height;
    int32 DangerRoomWeight;

	MultiPlantGridLayer     MultiPlantLayer;
    
	Sexy::Rect RestrictPlantingToGridArea;	// Plant can't be planted outside of this area
	std::vector<BoardEntityStat> PlantStats;
	PlantDetailsInfo DetailProps;

	//plant star stats
	std::vector<PlantLevelStat> PlantLevelStats;
    DisplayActionsPropertySheetPtr          DisplayActions;
    DisplayAvatarActionsPropertySheetPtr    DisplayAvatarActions;
	std::vector<std::string> ValidStages;
	bool CanReceiveFirstAid;				// If true, the plant can be planted over to heal to full.
	bool IsConsumable;						// If true, the plant is considered 'consumable' for plant challenge purposes.
    bool IsPultPlant;						// If true, zombies that can only be attacked by pult plants will be attacked by this plant
    bool CanLiveOnWaves;		// if true, it can be planted on waves and won't die if waves cover the spot it was on
    bool CanPlantAgainToUpgrade;            // If true, we can plant again on the plant
    bool CanLiveInSky;
    float BoostRate; // Used for 4-star plants

    std::vector<PlantDamageType> DamageType; // Used for boost
    
    std::map<std::string, int> IdleAnimationWeights;
    
    // Awaken
    float AwakenLevel;
    
    float ViewScale;
    SexyVector2 ViewOffset;

    SexyVector2 SeedChooserPreviewAdjust;

	virtual	float	GetPacketCoolDownTime(int iStarLv = 1) const;
	virtual Sexy::Rect GetCollisionRect(class Plant* plant) const;
};

struct StarRateInfo
{
    float SecondStarRate;
    float ThirdStarRate;
    
    StarRateInfo()
    {
        SecondStarRate = 0.1f;
        ThirdStarRate = 0.1f;
    }
};

class StarRateProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(StarRateProps, PlantPropertySheet, RtClass);
    
    StarRateProps()
    {
        
    }
    
    StarRateInfo StarRate;
};

class SunflowerProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(SunflowerProps, PlantPropertySheet, RtClass);

	SunflowerProps()
	{
		PlantFoodSunCount = 6;
        AvatarCoinRate = 0.0f;
	}

	int PlantFoodSunCount;
    float AvatarCoinRate;
	std::string CollectibleTypeName;
};

class PultProjectileProps : public PropertySheetBase
{
public:
    RT_CLASS_DEFINE(PultProjectileProps, PropertySheetBase, RtClass);
    
    PultProjectileProps()
    {
        TimeOfFlight = 1.2f;
        TimeOfFlightVariance = 0.1f;
        LobHeight = 350.f;
        LobHeightVariance = 0.1f;
        FireOnlyForward = true;
    }
    
    float TimeOfFlight;
    float TimeOfFlightVariance;
    float LobHeight;
    float LobHeightVariance;
    bool  FireOnlyForward;
};

class SnowPeaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(SnowPeaProps, PlantPropertySheet, RtClass);
	
	SnowPeaProps()
	{
		PlantFoodProjectileCount = 1;
	}
	
	int PlantFoodProjectileCount;
};

class RepeaterProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(RepeaterProps, PlantPropertySheet, RtClass);
	
	RepeaterProps()
	{
		PlantFoodProjectileCount = 1;
	}
	
	int PlantFoodProjectileCount;
};

class SplitpeaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(SplitpeaProps, PlantPropertySheet, RtClass);
	
	SplitpeaProps()
	{
		PlantFoodForwardProjectileCount = 1;
		PlantFoodBackwardProjectileCount = 1;
	}
	
	int PlantFoodForwardProjectileCount;
	int PlantFoodBackwardProjectileCount;
};

class TallnutProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(TallnutProps, PlantPropertySheet, RtClass);
	
	TallnutProps()
	{
		PlantFoodShieldHitpoints = 0.0f;
	}
	
	float 	PlantFoodShieldHitpoints;
};


class GraveBusterProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(GraveBusterProps, PlantPropertySheet, RtClass);
	
	// Amount of time we should eat for
	float EatTime;
	// Amount of time it takes for the dirt to fade out after we're done eating
	float DirtFadeTime;
};

class CabbagepultProps : public StarRateProps
{
public:
	RT_CLASS_DEFINE(CabbagepultProps, StarRateProps, RtClass);
	
	CabbagepultProps()
	{
		ProjectileTimeOfFlight = 1.2f;
		ProjectileLobHeight = 350.f;
	}
	
	// Projectile properties
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
};

class CarrotLauncherProps : public StarRateProps
{
public:
	RT_CLASS_DEFINE(CarrotLauncherProps, StarRateProps, RtClass);

	CarrotLauncherProps()
	{
		ProjectileTimeOfFlight = 0.6f;
		ProjectileLobHeight = 300.f;
	}

	// Projectile properties
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
};

class DandelionProps : public StarRateProps
{
public:
	RT_CLASS_DEFINE(DandelionProps, StarRateProps, RtClass);
    
	DandelionProps()
	{
		ProjectileTimeOfFlight = 2.f;
		ProjectileLobHeight = 100.f;
        FlySpeed = 200.f;
        SpawnSpeed = 500.f;
		BigBombRatio = 0.3f;
		BigBombDamageRatio = 1.5f;
	}
    
	// Projectile properties
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
    float FlySpeed;
	float SpawnSpeed;
	float BigBombRatio;// level5 throw big bomb ratio
	float BigBombDamageRatio;// level5 big bomb damage ratio
};

class RafflesiaProps : public StarRateProps
{
public:
	RT_CLASS_DEFINE(RafflesiaProps, StarRateProps, RtClass);

	RafflesiaProps()
	{
		ProjectileTimeOfFlight = 0.5f;
		ProjectileLobHeight = 0.f;
	}

	// Projectile properties
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
};

class KernelpultProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(KernelpultProps, PlantPropertySheet, RtClass);
	
	KernelpultProps()
	{
		ButterChance = 0.5f;
		ButterStormDuration = 3.5f;
		AdditionalButterStormMissiles = 5;
		ButterStormDelay = 3.0f;
		ButterStormMissileSpeed = 700.f;
		ProjectileTimeOfFlight = 1.2f;
		ProjectileLobHeight = 350.f;
	}
	
	// Probability that a shot will be butter
	float ButterChance;
	// Total amount of time that we rain down butter for
	float ButterStormDuration;
	// Additional random pats of butter to throw down
	int AdditionalButterStormMissiles;
	float ButterStormDelay;
	float ButterStormMissileSpeed;
	// Projectile properties
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
};

class MelonpultProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(MelonpultProps, PlantPropertySheet, RtClass);
	
	MelonpultProps()
	{
		NormalProjectileTimeOfFlight = 1.2f;
		NormalProjectileLobHeight = 350.f;
		PlantfoodProjectileLobHeight = 500.f;
		PlantfoodProjectileTimeOfFlight = 2.0f;
		Level5ProjectileRate = 0.2f;
	}
	
	// Projectile properties
	float NormalProjectileTimeOfFlight;
	float NormalProjectileLobHeight;
	float PlantfoodProjectileTimeOfFlight;
	float PlantfoodProjectileLobHeight;
	float Level5ProjectileRate;
};

class CoconutCannonProps : public StarRateProps
{
public:
	RT_CLASS_DEFINE(CoconutCannonProps, StarRateProps, RtClass);
	
	CoconutCannonProps()
	{
		NumPushedZombiesForMinSpeed = 5;
		MinimumSpeedScaleWhilePushing = 0.3f;
		ExplodeAtXPosition = 750.f;
        StarPFStunTime = 5.0f;
	}

	float MinimumSpeedScaleWhilePushing;
	int32 NumPushedZombiesForMinSpeed;
	float ExplodeAtXPosition;
    float StarPFStunTime;
};

struct ConvertProjectileNameNode
{
	ConvertProjectileNameNode()
	{
		InputType = "";
		OutputType = "";
		AdvOutputType = "";
	}
	std::string		InputType;		// Name of source projectile sheet
	std::string		OutputType;		// Name of destination projectile sheet to turn into
	std::string		AdvOutputType;	// Name of the destination projectile sheet to turn into while in advanced mode.
	std::string		AudioEventName;		// Name of the audio event to play when we do the conversion.
};

class SpringbeanProps : public StarRateProps
{
    public:
    RT_CLASS_DEFINE(SpringbeanProps, StarRateProps, RtClass);
    
    SpringbeanProps()
    {
        KnockbackTime = 1.0f;
        KnockbackHeight = 50.0f;
        KnockbackOffset = 96.0f;
        AttackRecoveryTime = 1.1f;
        StunTimeAfterPF = 3.0f;
    }
    
    float KnockbackTime;
    float KnockbackHeight;
    float KnockbackOffset;
    float AttackRecoveryTime;
    float StunTimeAfterPF;
	Sexy::Rect RectZombieProximity;
};

class SpikeweedProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(SpikeweedProps, PlantPropertySheet, RtClass);
	
	SpikeweedProps()
	{
		PlantFoodDPS = 100;
		PFConveyorSpeed = 4.0f;
		PFSpikeDamage = 40;
		PFSpikeCooldown = 0.25;
		PFSpikeOffset = SexyVector2();
	}
	
	// Damage per second the plantfood saws should dish out (Base zombie is 270 HP)
	int 	PlantFoodDPS;
	// Speed in grid squares (1.0f, 1.5f, etc) per second the plantfood saws should send a zombie toward the spikeweed
	float	PFConveyorSpeed;
	// Time between hits for the spikeweed plantfood effect
	float	PFSpikeCooldown;
	// Damage that the spikeweed does once every second or so while in Plantfood state
	int		PFSpikeDamage;
	// Visual offset for the PF spike art
	SexyVector2	PFSpikeOffset;
};

struct TargetProbabilityItem
{
	TargetProbabilityItem()
	{
		Number = 1;
		Weight = 1;
	}
	int Number;
	int Weight;
};

class SquashProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(SquashProps, PlantPropertySheet, RtClass);
    
    float GetLiveRateInPVP(int i_level) const;
    float GetLiveRateNormal(int i_level) const;
	
	// Radius from center point of squash, that will hit stuff
	int		SquashRadius = 32;
	// Probabilities that we'll hit a certain number of targets
	std::vector<TargetProbabilityItem> PlantfoodZombiesToTarget;
    std::vector<float> LiveRateInPVP;
};

class ChilibeanProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ChilibeanProps, PlantPropertySheet, RtClass);
	
	ChilibeanProps()
	{
		PlantFoodSpawnCount = 3;
	}
	
	int PlantFoodSpawnCount; // Number of plants to spawn when plantfood is used.
};

class LightningReedProps : public StarRateProps
{
public:
	RT_CLASS_DEFINE(LightningReedProps, StarRateProps, RtClass);

	LightningReedProps()
	{
		NumShotBounces = 3;
		BounceDamagePercent = 0.5f;
		BounceDelay = 0.15f;
		PlantFoodCloudSpeed = 15.0f;
		PlantFoodLightningBoltDamage = 20.0f;
		PlantFoodAttackCooldown = 2.0f;
		PlantFoodCloudDuration = 10.0f;
	}

	// how many times the lightning shot bounces once it hits a zombie
	int NumShotBounces;
	// how much of a percentage is the bounce damage of the original shot (and subsequent shots)
	float BounceDamagePercent;
	// how long it takes to do the next bounce
	float BounceDelay;
	// how fast the plant food cloud moves in pixels per second
	float PlantFoodCloudSpeed;
	// how much damage the plant food cloud does to each zombie per lightning bolt
	float PlantFoodLightningBoltDamage;
	// plant food attack cooldown rate
	float PlantFoodAttackCooldown;
	// plant food cloud duration
	float PlantFoodCloudDuration;
};

class MagnifyingGrassProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(MagnifyingGrassProps, PlantPropertySheet, RtClass);
    
	MagnifyingGrassProps()
	{
		SunMoneyPerShot = 25;
		SunSuckInTime = 0.25f;
		PlantFoodBeamDPS = 200.0f;
		PlantFoodBeamMovementRate = 100;
		PlantFoodBeamMaxTargetingAngleDegrees = 85.0f;
		PlantFoodBeamMaxTargetingDistance = 500.f;
		PlantFoodPulseDamage = 1000.f;
	}
    
	int SunMoneyPerShot;
	float SunSuckInTime;
	float PlantFoodBeamDPS;
	float PlantFoodBeamMovementRate;
	Sexy::Point PlantFoodBeamStartOffset;
	Sexy::Point PlantFoodOriginArtOffset;
	Sexy::Point PlantFoodBeamStartArtOffset;
	Sexy::Point PlantFoodBeamEndArtOffset;
	Sexy::Point PlantFoodHitEffectPivotOffset;
	float PlantFoodBeamMaxTargetingAngleDegrees;
	float PlantFoodBeamMaxTargetingDistance;
	Sexy::SexyVector3 SunproducerOriginatingPlantOffset;
	Sexy::SexyVector3 SunproducerTargetMagnifyingGrassOffset;
	Sexy::Point SunproducerBeamStartOffset;
	Sexy::Point SunproducerBeamEndOffset;
	float SunproducerExtendTime;
	float SunproducerContractTime;
    
	float PlantFoodPulseDamage;
};

class BloverProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(BloverProps, PlantPropertySheet, RtClass);
	
	BloverProps()
	{
		WindAccel = 100.0f;
		UpPercent = 0.0f;
	}
	
	float WindAccel;
	float UpPercent;
};

class EMPeaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(EMPeaProps, PlantPropertySheet, RtClass);
	
	EMPeaProps()
	{
		TapToActivate = false;
		ActivateImmediately = false;
		ActivationRecoveryTime = 10.0f;
		ActivationRadius = 200.f;
		StunTime = 16.0f;
	}
	
	std::vector<std::string> AffectedZombieTypes;
	bool ActivateImmediately;
	bool TapToActivate;
	
	float ActivationRadius;
	
	float ActivationRecoveryTime;
	
	float StunTime;
};

class HolonutProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(HolonutProps, PlantPropertySheet, RtClass);
    
	HolonutProps()
	{
		RegenAfterDamage = true;
		RegenAfterDeath = true;
		DelayBeforeRegenFromDamage = 5.0f;
		DelayBeforeRecoverFromDeath = 15.f;
		OnHalfShieldHp = 7000.f;
		OnTotalShieldHp = 8000.f;
		HpImprovedAfterRecoverInLv5 = 1000.f;
		MaxHpCeilingInLv5 = 10000.f;
	}
    
	bool RegenAfterDamage;
	float DelayBeforeRegenFromDamage;
	bool RegenAfterDeath;
	float DelayBeforeRecoverFromDeath;
    
	std::string SoundOnRegen;

	float OnHalfShieldHp;
	float OnTotalShieldHp;
	float HpImprovedAfterRecoverInLv5;
	float MaxHpCeilingInLv5;
};

class StarFruitProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(StarFruitProps, PlantPropertySheet, RtClass);
	
	StarFruitProps()
	{
		PlantFoodProjectileCount = 1;
		FireHeight = 0.32;
	}
	
	int PlantFoodProjectileCount;
	float FireHeight;
};

class BloomerangProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(BloomerangProps, PlantPropertySheet, RtClass);
	
	BloomerangProps()
	{
		BoomerangHitCount = 3;
		PlantFoodProjectileCount = 5;
		BoomerangSlowdownRadius = 150.0f;
		BoomerangMinSpeedPercentage = 0.1f;
		BoomerangStunsZombies = false;
		BoomerangPauseDuration = 0.25f;
	}
	
	int PlantFoodProjectileCount;
	int BoomerangHitCount;
	bool BoomerangStunsZombies;
	float BoomerangSlowdownRadius;
	float BoomerangMinSpeedPercentage;
	float BoomerangPauseDuration;
};

class AcornProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(AcornProps, PlantPropertySheet, RtClass);

	AcornProps()
	{
		BoomerangSlowdownRadius = 150.0f;
		BoomerangMinSpeedPercentage = 0.1f;
	}

	float BoomerangSlowdownRadius;
	float BoomerangMinSpeedPercentage;
};

class ImitaterProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ImitaterProps, PlantPropertySheet, RtClass);
	
	ImitaterProps()
	{
		NewPlantFadeInTime = 0.5f;
	}
	
	float NewPlantFadeInTime;
};

class PowerLilyProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PowerLilyProps, PlantPropertySheet, RtClass);

	PowerLilyProps()
	{
	}
};

class PlantCoinDispenserProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PlantCoinDispenserProps, PlantPropertySheet, RtClass);
    
    PlantCoinDispenserProps()
	{
		PlantFoodCoinsToSpawn = 10;
	}
    
	int PlantFoodCoinsToSpawn;
};

class LotusProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(LotusProps, PlantPropertySheet, RtClass);
	
	LotusProps()
	{
		ProjectileTimeOfFlight = 1.2f;
		ProjectileLobHeight = 350.f;
        PlantFoodSpeed = 1.0f;
	}
	
	// Projectile properties
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
    float PlantFoodSpeed;
};

class PitayaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PitayaProps, PlantPropertySheet, RtClass);
	
	PitayaProps()
	{
		NormalProjectileTimeOfFlight    = 1.2f;
		NormalProjectileLobHeight       = 350.f;
		PlantfoodProjectileLobHeight    = 500.f;
		PlantfoodProjectileTimeOfFlight = 2.0f;
	}
	
	// Projectile properties
	float NormalProjectileTimeOfFlight;
	float NormalProjectileLobHeight;
	float PlantfoodProjectileTimeOfFlight;
	float PlantfoodProjectileLobHeight;
};

class PeachProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PeachProps, PlantPropertySheet, RtClass);
    
	PeachProps()
	{
		timeInvincible = 6.0f;
        cureValue      = 150;
		timeSecondLevel = 3.0f;
		timeThirdLevel = 5.0f;
		AttackUpPercent = 0.1f;
	}
    
	pvztime_t timeInvincible;
    pvztime_t timeSecondLevel;
    pvztime_t timeThirdLevel;
    int       cureValue;
    float     AttackUpPercent;
};



class FireGourdProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(FireGourdProps, PlantPropertySheet, RtClass);
	
	FireGourdProps()
	{
        dot1 = 100;
        dot2 = 100;
        dot3 = 100;
        dotPlantfood = 100;
        fireDuration = 3;
        dotArmrackCoeff = 2;
        armrackExtraFireDuration = 2;
        armrackExtraDot = 100;
	}
	
	// Projectile properties
	float dot1;
	float dot2;
	float dot3;
	float dotPlantfood;
    float fireDuration;
    
    float dotArmrackCoeff;
	float armrackExtraFireDuration;
    float armrackExtraDot;
};


class BambooProps : public StarRateProps
{
public:
	RT_CLASS_DEFINE(BambooProps, StarRateProps, RtClass);
	
	BambooProps()
	{
        PlantGridAttackRange = 4;
		PlantFoodTargetCount = 4;
        PlantFoodAvatarTargetCount = 6;
	}
	
	int PlantFoodTargetCount;
    int PlantFoodAvatarTargetCount;
    int PlantGridAttackRange;

};

class SunshroomProps : public SunflowerProps
{
public:
	struct SunshroomGrowthStates
	{
		std::string CollectibleTypeName;
		float TimeToGrowInSeconds;
	};
    
	RT_CLASS_DEFINE(SunshroomProps, SunflowerProps, RtClass);
    
	SunshroomProps() :fPercentGrowthTime2(1.0f), fPercentGrowthTime3(1.0f),fPercentDropCoinRate(1.0f)
	{
        
	}
    
	std::vector<SunshroomGrowthStates> GrowthStages;
	float	fPercentGrowthTime2;
	float	fPercentGrowthTime3;
	float	fPercentDropCoinRate;
};

class PuffshroomProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PuffshroomProps, PlantPropertySheet, RtClass);
    
	PuffshroomProps()
	{
		PlantFoodProjectileCount = 1;
		ExpirationDurationSeconds = PVZ_EOT();
		ExpirationBlinkTime = 5.f;
		PlantfoodPropagationDelayBaseSeconds = 0.0;
		PlantfoodPropagationDelayPerTileDistanceSeconds = 0.2;
		PlantfoodResetsDecayForAllPuffshrooms = false;

		fPlantCoolTimePercentLv2 = 1.0f;
		fPlantCoolTimePercentLv3 = 1.0f;
	}
    
	int PlantFoodProjectileCount;
	pvztime_t ExpirationDurationSeconds;
	pvztime_t ExpirationBlinkTime;
	float PlantfoodPropagationDelayBaseSeconds;
	float PlantfoodPropagationDelayPerTileDistanceSeconds;
	bool PlantfoodResetsDecayForAllPuffshrooms;
 	float fPlantCoolTimePercentLv2;
 	float fPlantCoolTimePercentLv3;

	virtual	float	GetPacketCoolDownTime(int iStarLv = 1) const override;
};

class FumeshroomProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(FumeshroomProps, PlantPropertySheet, RtClass);
    
	FumeshroomProps()
	{
		PlantFoodPushSpeed = 1;
	}
    
	float PlantFoodPushSpeed;
};

class ScaredyshroomProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ScaredyshroomProps, PlantPropertySheet, RtClass);
    
	ScaredyshroomProps()
	{
		PlantFoodProjectileCount = 1;
		ScaredRangeWidth = 3;
		ScaredRangeHeight = 3;
	}
    
	int PlantFoodProjectileCount;
	int ScaredRangeWidth;
	int ScaredRangeHeight;
};

class PultshroomProps : public CabbagepultProps
{
public:
	RT_CLASS_DEFINE(PultshroomProps, CabbagepultProps, RtClass);
    
	PultshroomProps()
	{
		MutationWaitSeconds = 120.f;
		MaxArmLevels = 3;
	}
    
	float MutationWaitSeconds;
	int MaxArmLevels;
};

class RotoshroomProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(RotoshroomProps, PlantPropertySheet, RtClass);
    
	RotoshroomProps()
	{
		PlantFoodProjectileCount = 1;
		SnapRotationToCardinals = false;
	}
    
	int PlantFoodProjectileCount;
	bool SnapRotationToCardinals;
};

class DartshroomProps : public CabbagepultProps
{
public:
	RT_CLASS_DEFINE(DartshroomProps, CabbagepultProps, RtClass);
    
	DartshroomProps()
	{
		PlantFoodProjectileCount = 1;
		RowTargetOffset = 4;
	}
    
	int RowTargetOffset;
	int PlantFoodProjectileCount;
};

class ZoomshroomProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ZoomshroomProps, PlantPropertySheet, RtClass);
    
	ZoomshroomProps()
	{
		ExpirationDurationSeconds = 15;
		KnockbackTime = 1.0f;
		KnockbackHeight = 50.0f;
		KnockbackTargetColumn = 9;
		AttackRecoveryTime = 0.f;
	}
    
	float KnockbackTime;
	float KnockbackHeight;
	int KnockbackTargetColumn;
	float AttackRecoveryTime;
    
	pvztime_t ExpirationDurationSeconds;
	std::string ExpirationEffectID;
	std::string KnockbackEffectID;
};

// please move these code props to the plantxxx.h (require including wallnut.h)
//class VacuumshroomProps : public WallnutProps
//{
//public:
//	RT_CLASS_DEFINE(VacuumshroomProps, WallnutProps, RtClass);
//    
//	VacuumshroomProps()
//	{
//		VacuumCooldownTime			= 3.0f;
//		VacuumRangeWidth			= 3;
//		VacuumRangeHeight			= 3;
//		VacuumTossTime				= 1.0f;
//		VacuumTossApexHeight		= 50.0f;
//	}
//    
//	pvztime_t	VacuumCooldownTime;
//	int32     	VacuumRangeWidth;
//	int32     	VacuumRangeHeight;
//	float		VacuumTossTime;
//	float		VacuumTossApexHeight;
//};

class PowerPlantProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(PowerPlantProps, PlantPropertySheet, RtClass);
    
	PowerPlantProps()
	{
		SecondTileCost = 250;
	}
    
	int	SecondTileCost;
};

class SunBeanProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(SunBeanProps, PlantPropertySheet, RtClass);
    
	SunBeanProps()
	{
		SunPerHitpoint = 0.5f;
		SunMultiplierOnPlantfoodBurst = 2.f;
		MaxSunPerZombieOnPlantfoodBurst = 600;
		MaxSunPerZombie = 400;
		OnlyLargeSun = false;
	}
    
	float SunMultiplierOnPlantfoodBurst;
	float MaxSunPerZombieOnPlantfoodBurst;
	float SunPerHitpoint;
	float MaxSunPerZombie;
	bool OnlyLargeSun;
};

class MagnetShroomProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(MagnetShroomProps, PlantPropertySheet, RtClass);
    
	MagnetShroomProps()
	{
		GridSquareRangeWidth = 7;
		GridSquareRangeHeight = 5;
		MaxPlantFoodObjects = 6;
		DestroyPulledObjectsTime = 10.0f;
		InitialPulledObjectSpeed = 0.f;
		PulledObjectAcceleration = 1000.f;
		PlantFoodCollectTime = 1.5f;
	}
    
	int GridSquareRangeWidth;
	int GridSquareRangeHeight;
    
	float InitialPulledObjectSpeed;
	float PulledObjectAcceleration;
    
	float DestroyPulledObjectsTime;
    
	int MaxPlantFoodObjects;
	float PlantFoodCollectTime;
    
	ProjectilePropertySheetPtr PlantFoodProjectileType;
    
    std::vector<std::string> PullableZombieTypes;
    std::vector<std::string> PullableZombieHeadTypes;
};

class HypnoShroomProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(HypnoShroomProps, PlantPropertySheet, RtClass);
    
	HypnoShroomProps()
	{
		HealsOnHypnosis = false;
	}
    
	bool HealsOnHypnosis;
	std::vector<std::string> CannotBeHypnotized;
};

class BroccoliProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(BroccoliProps, PlantPropertySheet, RtClass);
    
	BroccoliProps()
	{
		RestTime = 3;
        AttackCountBeforeRest = 1;
        Level2AdvancedPrimaryAttackProbility = 30;
        Level3AdvancedPrimaryAttackProbility = 60;
	}
    
	ProjectilePropertySheetPtr PlantFoodProjectileType;
	pvztime_t                  RestTime;
	int                        AttackCountBeforeRest;
    float                      Level2AdvancedPrimaryAttackProbility;
    float                      Level3AdvancedPrimaryAttackProbility;
};

class LilyPadProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(LilyPadProps, PlantPropertySheet, RtClass);
    
	LilyPadProps()
	{
	}
};

class BowlingBulbProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(BowlingBulbProps, PlantPropertySheet, RtClass);
    
	enum SuperSKillRateIndex
	{
		E_FIRE_RATE = 0,
		E_RELOAD_TWO_RATE,
		E_RELOAD_THREE_RATE,
	};

	BowlingBulbProps()
	{
		MaxAmmo = 3;
		AmmoRefreshTime = 3.0f;
	}
    
	int MaxAmmo;
	pvztime_t AmmoRefreshTime;
    std::vector<float> AdvancedRate;
    std::vector<float> SuperSkillRate;
};

class BananaProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(BananaProps, PlantPropertySheet, RtClass);
    
	BananaProps()
	{
		NumPlantfoodRockets = 3;
		FireTime = 1.0f;
		PlantfoodFireTime = 0.5f;
		TargetOffset.x = 0;
		TargetOffset.y = 0;
		FireLevel5Ratio = 1;
	}
    
	int NumPlantfoodRockets;
	pvztime_t FireTime;
	pvztime_t PlantfoodFireTime;
	SexyVector2 TargetOffset;
    std::vector<pvztime_t> RecoverTime;
	float FireLevel5Ratio;

};

class TangleKelpProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(TangleKelpProps, PlantPropertySheet, RtClass);
    
	TangleKelpProps()
	{
		MinPlantfoodWaterKills = 3;
		MaxPlantfoodWaterKills = 5;
		SlapDamage = 200.0f;
        RepulseDamage = 100.0f;
	}
    
	int MinPlantfoodWaterKills;
	int MaxPlantfoodWaterKills;
	float SlapDamage;
    float RepulseDamage;
	std::vector<std::string> ZombieDrownBlackList;
};

class ChomperProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(ChomperProps, PlantPropertySheet, RtClass);
    
	ChomperProps()
	{
		NumberOfPlantfoodTargets = 5;
		ChewDamage = 200.0f;
		PFChewDamage = 1000.0f;
		BurpingTimeSeconds = 1.0;
		SuctionSpeed = 1.0f;
		BurpingSpeed = 1.0f;
        GulpChance = 0.8f;
        GulpDamage = 1000.0f;
	}
    
	int NumberOfPlantfoodTargets;
    std::vector<pvztime_t> ChewTimeSeconds;
	pvztime_t BurpingTimeSeconds;
    
	std::vector<std::string> ZombieChewBlacklist;
	float ChewDamage;
	float PFChewDamage;
	float SuctionSpeed;
	float BurpingSpeed;
    float GulpChance;
    float GulpDamage;
};

class GuacodileProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(GuacodileProps, PlantPropertySheet, RtClass);
    
	GuacodileProps()
	{
        
	}
};

class PumpkinWitchProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PumpkinWitchProps, PlantPropertySheet, RtClass);
    
    PumpkinWitchProps()
    {
        ZombieWhiteList.clear();
        ProjectileTimeOfFlight = 1.2f;
        ProjectileLobHeight = 350.f;
        NormalCoolDownTime = 5.f;
        PlantfoodCoolDownTime = 10.f;
    }
    
    std::vector<PlantLevelStat> ZombieBuffStatus;
    std::vector<std::string> ZombieWhiteList;
    float ProjectileTimeOfFlight;
    float ProjectileLobHeight;
    float NormalCoolDownTime;
    float PlantfoodCoolDownTime;
};

class SunpodProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(SunpodProps, PlantPropertySheet, RtClass);
	
	SunpodProps()
	{
		SunBankPerTier = 1000;
	}
	
	int SunBankPerTier;
};

class SunGunProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(SunGunProps, PlantPropertySheet, RtClass);
	
	SunGunProps()
	{
		AngleVarianceInDegrees = 45.0f;
	}
	
	float AngleVarianceInDegrees;
};

class CottonYetiProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(CottonYetiProps, PlantPropertySheet, RtClass);
    
    CottonYetiProps()
    {
        ProjectileTimeOfFlight = 0.5f;
        ProjectileLobHeight = 50.f;
        PlantfoodFreezeTime = 3.f;
        NormalAttackFreezeRate = 0.1f;
    }
    
    float ProjectileTimeOfFlight;
    float ProjectileLobHeight;
    float PlantfoodFreezeTime;
    float NormalAttackFreezeRate;
};

class AgaveProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(AgaveProps, PlantPropertySheet, RtClass);
    
    AgaveProps()
    {
        ExtraDamageModifier = 1.2f;
        ChargeTime = 3.f;
        ChargeTimeHighLevel = 1.5f;
    }
    
    float ExtraDamageModifier;
    float ChargeTime;
    float ChargeTimeHighLevel;
};

class ShadowPeashooterProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(ShadowPeashooterProps, PlantPropertySheet, RtClass);
    ShadowPeashooterProps()
    {
        PlantFoodProjectileCount = 1;
        PoweredAttackSlowDuration = PoweredAttackSlowMinimumDuration = PoweredAttackDecayPerZombieHit  = PlantFoodBombTravelTime = 0.0f;
        ShadowBoostedZombieSwallows = 3;
        SpecialAttackRate = 0.5f;
        ImprovedSpecialAttackBonus = 1.0f;
		LV5Rate = 0.5;
		LV5DarkRate = 0.5;
		LV5CD = 10.0f;
    }

    int PlantFoodProjectileCount;
    float PoweredAttackSlowDuration;
    float PoweredAttackSlowMinimumDuration;
    float PoweredAttackDecayPerZombieHit;
    int ShadowBoostedZombieSwallows;
    float PlantFoodBombTravelTime;
    std::vector<std::string> ZombieSwallowBlackList;
    float SpecialAttackRate;
    float ImprovedSpecialAttackBonus;
	float LV5Rate;
	float LV5DarkRate;
	float LV5CD;
};

#endif // __PLANTPROPERTYSHEET_H__
