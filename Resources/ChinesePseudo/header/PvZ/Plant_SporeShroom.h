#ifndef Plant_SporeShroom
#define Plant_SporeShroom

#include "Plant.h"
#include "PlantFramework.h"
#include "PlantUtils.h"
#include "Projectile.h"
#include "RtObject.h"
#include "GameSubSystem.h"
#include <vector>

class Zombie;

 struct SpawnItemRecord
 {
     SpawnItemRecord()
     :Probability(0){}
     
     std::string ItemName;
     int Probability;
 };

class SporeshroomProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(SporeshroomProps, PlantPropertySheet, RtClass);
	
	SporeshroomProps()
	{
	}
    std::vector<SpawnItemRecord> SpawnPlantList1;
    std::vector<SpawnItemRecord> SpawnPlantList2;
	ZombieRestrictionSet DuplicatableZombies;
	PultProjectileProps NormalLaunchProps;
	PultProjectileProps PlantfoodLaunchProps;
};

class SporeshroomSubsystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(SporeshroomSubsystem, GameSubSystem, RtClass);
	
	SporeshroomSubsystem();
	~SporeshroomSubsystem() override;
	
	void ReplaceZombieWithShroom(Zombie* zombie);
    void RecordSporeshroomLevel(int level);
	
private:
	void onZombieDeath(Zombie* zombie);
	bool shouldReplaceZombieWithShroom(Zombie* zombie);
    void trySpawnAnotherSporeshroom(Zombie* zombie);
    PlantTypePtr GetSpawnPlantType();
    
    int m_sporeshroomLevel;
	RtWeakPtr<SporeshroomProps> m_sporeshroomProps;
	std::set<RtWeakPtr<Zombie>> m_zombiesToSpoorshroom;
};

class SporeshroomProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(SporeshroomProjectile, Projectile, RtClass);
	
protected:
	bool OnCollideEntity(BoardEntity* i_entity) override;
	
private:
	bool isZombieValidToKill(BoardEntity* i_entity);
	bool hasZombieBeenKilled(Zombie* zombie);
	void removeMarkedForDeathFromTargetedZombie();
};

class PlantSporeshroom : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantSporeshroom, PlantFramework, RtClass);
	PlantSporeshroom();
    
    void Initialize() override;
	Projectile*		Fire(ZombiePtr i_targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
	bool			CanApplyPlantfood() override;
	void			UpdatePlantfood() override;
	void			ApplyPlantfood()override;
	
	void			PlayGrowAnimation();
	void			onAnimStoppedCallback(const std::string& i_anim) override;
	
private:
	bool			isValidTargetGridItem(BoardEntityPtr target);
	bool			isValidTargetZombie(BoardEntityPtr target);
    void            trySpawnPlantForZombie(Zombie *zombie);
	
	Projectile*		launchNormalProjectile();
	Projectile*		launchSpecialProjectile();

	Projectile*		launchProjectile(PlantWeapon i_plantWeapon, const PultProjectileProps& pultProps,
									 Zombie* targetZombie, GridItem* targetGridItem);

	SexyVector3		calculateTargetLocationForZombie(const PultProjectileProps& pultProps, PlantWeapon i_plantWeapon, Zombie* zombie);
	SexyVector3		calculateTargetLocationForGridItem(const PultProjectileProps& pultProps, PlantWeapon i_plantWeapon, GridItem* gridItem);

	BoardEntityPtr  findNextPlantfoodTarget();
	void			makeSureWeStillHaveAPlantFoodTarget();
	void			markTargetZombieForDeath();

	std::vector<RtWeakPtr<BoardEntity>> m_entitiesHitDuringPlantfood;
	RtWeakPtr<BoardEntity> m_nextPlantFoodTarget;

};

#endif //__PLANT_PEASHOOTER_H__
