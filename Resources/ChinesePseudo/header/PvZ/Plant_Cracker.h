//
//  Plant_Cracker.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-1-5.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_Plant_Cracker_h
#define PlantsVersusZombies2_Plant_Cracker_h

#include "PlantFramework.h"
#include "Projectile.h"
#include "GridItemAnimation.h"

enum CrackerDamgeType
{
    Cracker_Normal_Damge,
    Cracker_Piece_Damge,
    Cracker_PlandFood_Damge
};

class PlantCracker : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantCracker, PlantFramework, RtClass);
    
	void Initialize() override;
	
    bool CanApplyPlantfood() override { return true; }
    
	void ApplyPlantfood() override;
    
	void CancelPlantfood() override;
    
	bool CanEndPlantfood() override;
    
    void UpdateActions() override;
    
    bool CanBeTargeted() override;
    
	bool CanBeTargetedBy(const BoardEntity* i_entity) override;
    
    void onAnimStoppedCallback(const std::string &i_animLabel) override;
    
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    int CalcRenderOrder() override;
    
    bool IsInvincible() const override;
    
    void DoCrackerPieceExplode(Point& stPoint);
    
    void CheckAndKill();

	virtual bool CanBeWatered() override;

	virtual bool CanBeShoveled() override;
    
private:
    
    bool AnyValidZombieAtLocation();
    
    void FindSameLocationValidZombie(std::vector<BoardEntity*>& vEntities);
    
    void FindLocationValidZombie(std::vector<BoardEntity*>& vEntities, int iColumn, int iRow);
    
    void FindLocationValidGridItemAndDamage(int iColumn, int iRow);
    
    bool ZombieCanBeFlick(Zombie* pZombie);
    
    void DoFlickZombie(Zombie* pZombie);
    
    void DoNormalExplode();
    
    void DoPlantFoodExplode(Point stPoint);
    
    void DropCrackerPiece();
    
    void DropCrackerPiece(float iX, float iY);
    
    void DoDamage(std::vector<BoardEntity*>& veEntities, CrackerDamgeType eType);
    
    void DoNormalDamage(Zombie* pZombie);
    
    void DoPieceDamage(Zombie* pZombie);
    
    void DoPlantFoodDamage(Zombie* pZombie);
    
    void PlaySmallCrackerEffect();
    
private:
    
    bool m_bCancelPlantFood = false;
    
    int  m_iDropCracker = 0;

	bool m_IsAlive;
};


class CrackerPropertySheet : public PlantPropertySheet
{
    
public:
    
    RT_CLASS_DEFINE(CrackerPropertySheet, PlantPropertySheet, RtClass);
    
    int iNormalDamage;
    int iPieceDamage;
    int iPlantFoodDamage;
};

class PlantAnimRig_Cracker : public PlantAnimRig
{
public:
    
	RT_CLASS_DEFINE(PlantAnimRig_Cracker, PlantAnimRig, RtClass);
    
};

class EffectCrackerDrop : public Effect_PopAnim
{
public:
    
    RT_CLASS_DEFINE(EffectCrackerDrop, Effect_PopAnim, RtClass);
    
    void OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    void SetDate(BoardEntityPtr ptrCracker, Point targetPoint);
    
private:
    
    Point m_TargetPoint;
    BoardEntityPtr m_ptrCracker;
};


enum GridItemPlantCrackerFlowerState
{
	PVZ_BEGIN_ENUM(CRACKERFLOWERSTATE_),
	CRACKERFLOWERSTATE_UNKNOWN,
	CRACKERFLOWERSTATE_DORMANT,
	CRACKERFLOWERSTATE_PROJECTILE_ASCENDING,
	CRACKERFLOWERSTATE_PROJECTILE_DESCENDING,
	CRACKERFLOWERSTATE_GROW,
	CRACKERFLOWERSTATE_EXPLODE,
	CRACKERFLOWERSTATE_SHRAPNEL,
	CRACKERFLOWERSTATE_DEAD,
	PVZ_END_ENUM(CRACKERFLOWERSTATE_)
};

class GridItemPlantCrackerFlower : public GridItemAnimation
{
public:
	RT_CLASS_DEFINE(GridItemPlantCrackerFlower, GridItemAnimation, RtClass);
	
	GridItemPlantCrackerFlower()
	: m_state(CRACKERFLOWERSTATE_UNKNOWN)
	{ JoinTeam(TEAM_PLANTS); }
	
	void onPopAnimCommand(const std::string& i_animLabel, pvztime_t i_timeStamp, const std::string& i_animCommand, const std::string& i_animCommandParam);
	
	int	CalcRenderOrder() const override;
	void StartGrowing();
	void SetSplashDamageProps(float i_splashDamage, float i_splashRadius);
	void SetShrapnelProps(float i_shrapnelRadius, float i_shrapnelDamage);
	void SetPauseBeforeStartFlower(pvztime_t i_pause);
	
	void setPlantWeapon(PlantWeapon i_plantWeapon);
	PlantWeapon getPlantWeapon() const;

	void setIsAvatarEnable(bool isEnable);
	bool getIsAvatarEnable() const;
	void setState(GridItemPlantCrackerFlowerState i_state);
protected:
	void onGridItemInitialize() override;
	void onUpdate() override;
	
	GridItemPlantCrackerFlowerState getState() { return m_state; }
	void launchDescendingProjectile();
	void launchDescendingAvatarProjectile();
	
	void doDamage(int i_damage, float i_radius);
	void radiateSplashDamage();
	void doShrapnelDamage();
	void onDropFinished(const std::string &i_animName);
	void onGrowFinished(const std::string &i_animName);
	void onBoomFinished(const std::string &i_animName);
	bool CanBeTargetedBy(const BoardEntity* i_entity) const override { return false; }
	
	void launchProjectileAt(Projectile *i_projectile, const Sexy::SexyVector3 &i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
	
private:
	GridItemPlantCrackerFlowerState m_state;
	pvztime_t m_pauseBeforeStartFlower;

	bool shouldStun(BoardEntity* i_impactedEntity);
	void stunZombie(BoardEntity* i_impactedEntity);
	
	// props gotten from pfProjectile and CrackerProps
	// note that we could just put these in flower props instead
	float m_splashDamage;
	float m_splashRadius;
	
	float m_shrapnelDamage;
	float m_shrapnelRadius;
	bool m_bIsAvatarEnable;
	pvztime_t k_damageInterval;
	pvztime_t m_damageTime; //For dealing damage with interval
	PlantWeapon m_plantWeapon;
};

class GridItemPlantCrackerFlowerProps : public GridItemAnimationProps
{
public:
	RT_CLASS_DEFINE(GridItemPlantCrackerFlowerProps, GridItemAnimationProps, RtClass);
	GridItemPlantCrackerFlowerProps()
	: Lifetime(5.0)
	, BombProjectile("PlantCrackerPlantfoodAvatarBomb"),
	  AvatarBombProjectile("PlantCrackerPlantfoodAvatarBomb"),
      ShrapnelDamage(1.07),
      ShrapnelRadius(300),

      SplashRadius(1.0),
      SplashDamage(50)
	{}
	
	pvztime_t Lifetime;
	std::string BombProjectile;
	std::string AvatarBombProjectile;

    float ShrapnelDamage;
	float ShrapnelRadius;
	
	float SplashRadius;
	float SplashDamage;
    
};


class PlantCrackerPlantfoodProjectileAvatar : public Projectile
{
public:
	RT_CLASS_DEFINE(PlantCrackerPlantfoodProjectileAvatar, Projectile, RtClass);

	GridItemPlantCrackerFlower *GetFlower();
	void SetFlower(GridItemPlantCrackerFlower *flower);
protected:
	void onProjectileInitialized() override;
private:
	bool handleImpact(BoardEntity* i_impactedEntity = NULL) override;
	RtWeakPtr<GridItemPlantCrackerFlower> m_flower;
};

#endif
