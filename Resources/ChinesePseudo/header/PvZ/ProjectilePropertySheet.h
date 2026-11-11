//
//  ProjectilePropertySheet.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 2/24/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PROJECTILEPROPERTYSHEET_H__
#define __PROJECTILEPROPERTYSHEET_H__

#include "Precompile.h"
#include "ProjectileEnums.h"
#include "ZombieEnums.h"
#include "PlantEnums.h"
#include "RtDb.h"
#include "PropertySheetBase.h"
#include "Utils.h"
#include "DamageInfo.h"
#include "DamageInfoProps.h"

enum ProjectileDamageType
{
	P_TYPE_NORMAL,
	P_TYPE_FLAME,
	P_TYPE_COLD,
	P_TYPE_LIGHTNING,
	P_TYPE_EXPLODE,
	P_TYPE_POISON,
	P_TYPE_MAGIC,
};

typedef RtWeakPtr<class ProjectilePropertySheet> ProjectilePropertySheetPtr;

class ProjectilePropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(ProjectilePropertySheet, PropertySheetBase, RtClass);

	ProjectilePropertySheet()
	{
		ClassName = "Projectile";
        ProjectileType = "";

		BaseDamage = 0.0f;
        HealAmount = 0.0f;

        ExtraResilienceDamage = 0.0f;

		CollisionFlags = COLLIDE_None;
		DamageFlags = DAMAGE_NONE;

		SplashDamage = 0.0f;
		DisableSplashDamageRate = false;
		StunDuration = 0.0f;
        SplashRadius = 0.0f;
		ShakeBoardOnSplash = false;

		DiesOnImpact = true;
        PieceCount = 0;
        CheckHeadShot = false;

        SkipAdditionalAngularVelocity = false;

		for (int i = 0; i < 3; ++i)
		{
			InitialVelocity.push_back(ValueRange());
			InitialAcceleration.push_back(ValueRange());

			InitialVelocityScale.push_back(ValueRange());
			InitialVelocityScale[i].SetRange(1.f, 1.f);
		}
		InitialScale.SetRange(1.f, 1.f);

		for (int i = 0; i < 2; ++i)
		{
			ImpactOffset.push_back(ValueRange());
		}
		
		ImpactSoundThrottleTimer = 0.f;

		RenderColor = Color::White;
		HasShadow = true;
        FollowsGround = false;
        
        ImpactShowsAtZombieFeet = false;
		RotateToMatchVelocity = false;
        //DamageType = P_TYPE_NORMAL;
        ImpactPAM = "";
	}

	// The projectile class to instantiate.
	std::string ClassName;
	
	// Baseline amount of damage to do on collision or activation
	float BaseDamage;
    // Baseline amount of healing to do on collision or activation (only used for iceblocks so far)
    float HealAmount;
    std::string ProjectileType;
    float ExtraResilienceDamage;
    
    

	// How we do damage
	CollisionTypeFlags CollisionFlags;
	// What type of damage we do
	DamageTypeFlags DamageFlags;

	// When we hit, how much extra damage do we want to do around us
	//float SplashDamage;
	float SplashDamage;
	bool DisableSplashDamageRate;
	float StunDuration;
    std::vector<float> GradedSplashDamage;
	float SplashRadius;
	bool ShakeBoardOnSplash;

	bool DiesOnImpact;
    int PieceCount;
	bool HasShadow;
    bool ImpactShowsAtZombieFeet;
    bool RotateToMatchVelocity;
    bool CheckHeadShot;
    bool FollowsGround;

	// Initial motion values
	std::vector<ValueRange> InitialVelocity; // originally InitialVelocity[3]
	std::vector<ValueRange> InitialAcceleration; // originally InitialAcceleration[3]
	std::vector<ValueRange> InitialVelocityScale; // originally InitialVelocityScale[3]

	ValueRange InitialHeight;
	ValueRange InitialRotation;
	ValueRange InitialAngularVelocity;
	ValueRange InitialScale;

	bool	   SkipAdditionalAngularVelocity;

	// Attached PAM to use on or for projectile (will generate a pop anim rig from it)
	std::string AttachedPAM;
	// Name of the class of an AnimRig we should spin up and attach to this
	// Will use the PAM specified in attachedPAM
	std::string AttachedPAMAnimRigClass;
	// Attached PAM offset
	SexyVector2 AttachedPAMOffset;
	// Animation to play on the attached PAM when created
    std::string AttachedPAMAnimationToPlay;

	// If we want to use a static image to draw the projectile
	std::string RenderImage;
	
	// Apply this color to attached pams and render images
	Color RenderColor;

	// Bounding box to use for collision, based on offset from our position
	FRect CollisionRect;

	// Event to send to WWise when we hit an object
	std::string ImpactSoundEvent;
	// Amount of time to wait before allowing this impact sound to play again
	float		ImpactSoundThrottleTimer;
	
	// PAM animation to spawn on impact, if any
	std::string ImpactPAM;
	// Animation label to play on spawned PAM animation from impact
	std::string ImpactPAMAnimationToPlay;
	// Amount of offset (from impact location) for splat popanim or image to play
	std::vector<ValueRange> ImpactOffset; // initially ImpactOffset[2]
	
	std::vector<ZombieConditionEntry> Conditions;
    std::vector<StarLevelConditionEntry> starLevelConditions;
    
    std::vector<ProjectileDamageType> DamageType;

    // this is only called once after the JSON file have been loaded into the tables
    bool Serialize(const RtSerializeContext& inContext) override;
    
private:    
    // this is only called once after the JSON file have been loaded into the tables
    void postLoadFixup();
    
	std::vector<CollisionTypeFlags> JSONCollisionFlags;
	std::vector<DamageTypeFlags> JSONDamageFlags;
};

#endif // __PROJECTILEPROPERTYSHEET_H__
