//
//  Plant_Akee.h
//  PlantsVersusZombies2
//
//  Created by Janney, Michael on 3/5/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__Plant_Akee__
#define __PlantsVersusZombies2__Plant_Akee__

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "RtDb.h"
#include "RtObject.h"
#include "Zombie.h"

namespace Sexy
{
	class SexyVector3;
}

enum AKP_STYLE
{
    AKP_NONE,
    AKP_NORMAL,
    AKP_EXPLODE,
    AKP_ICE,
    AKP_END,
};

class AkeeProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(AkeeProjectile, Projectile, RtClass);
	
	bool OnCollideEntity(BoardEntity* i_entity) override;
	bool OnCollideGround() override;
	void SetInitialLaunchValues(float i_height, float i_timeToTarget, int i_row);
    void RollProjectileStyle();
    bool AddAvatarSpecialCollide(BoardEntity* i_entity);
    
protected:
	void onProjectileInitialized() override;
    void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;
	
private:
    void DoFission();
	void DoBounce();
    void DealSplashDamage(BoardEntity* i_entity, bool i_chill);
    
    void HideAllLayer();
    void ShowNormalMegaAkee();
    void ShowFireMegaAkee();
    void ShowIceMegaAkee();
    void damageEntitySpecial(BoardEntity* i_entity, bool i_fire);
    
    Projectile* FissionProjectile();
	BoardEntity* findNextTarget(int i_row = -1);
    BoardEntity* findNearestTargetType(BoardEntityTypeFlag i_flag, int i_row);
	
    AKP_STYLE m_akpStyle;
	float m_initialLobHeightThisBounce;
	float m_initialTimeOfFlightThisBounce;
	float m_reductionRatio;
	float m_targetingRadius;
	int m_rowBeingFiredAt;
	std::vector<BoardEntityPtr>	m_targetsAlreadyHit;
};

class AkeeProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(AkeeProjectileProps, ProjectilePropertySheet, RtClass);
	
	AkeeProjectileProps()
	{
		ProjectileBounceCount = 5;
		ProjectileRetargetingRadius = 200.0f;
		PropertyReductionMultiplierPerBounce = 0.75;
		DamageReductionAmountPerBounce = 5;
        AkeeSpecialFireDamage = 200.f;
        AkeeSpecialFireRadius = 2.f;
	}
	
    bool FissionAfterFirstCollide;
	int ProjectileBounceCount;
	float ProjectileRetargetingRadius;
	float PropertyReductionMultiplierPerBounce;
    float DamageReductionAmountPerBounce;
    float ProjectileTimeOfFlight;
    float ProjectileLobHeight;
    float AkeeSpecialFireDamage;
    float AkeeSpecialFireRadius;
};

class PlantAkee : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantAkee, PlantFramework, RtClass);
	
	bool CanApplyPlantfood() override;
	void DoSpecial(int i_extraParam = 0) override;
    Projectile*	Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	
protected:
	void LaunchProjectileAt(AkeeProjectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
	
private:
	void launchSpecialProjectile(SexyVector3 i_targetLoc, BoardEntityPtr i_targetZombie, const RtWeakPtr<class BoardEntity>& i_target, int i_row);
	BoardEntityPtr findBestTargetInRow(int i_row);
	BoardEntity* findLeftmostTargetType(BoardEntityTypeFlag i_flag, int i_row);
};

class AkeeProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(AkeeProps, PlantPropertySheet, RtClass);
	
	AkeeProps()
	{
        FissionProbilityPercent = 0;
		ProjectileTimeOfFlight = 1.2f;
		ProjectileLobHeight = 350.f;
	}
	
    // Projectile properties
    int FissionProbilityPercent;
	float ProjectileTimeOfFlight;
	float ProjectileLobHeight;
};

#endif /* defined(__PlantsVersusZombies2__Plant_Akee__) */
