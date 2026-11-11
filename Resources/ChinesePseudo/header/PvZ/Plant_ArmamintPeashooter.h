#ifndef Plant_ArmamintPeashooter_h
#define Plant_ArmamintPeashooter_h

#include "Plant.h"
#include "PlantFramework.h"
#include "Projectile.h"
#include "PlantPropertySheet.h"

enum AttackType
{
	Type_Normal,
	Type_Advanced,
	Type_Super,
	Type_Pf_Fire,
	Type_Pf_Blue_Fire
};

class ArmamintPeashooterProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(ArmamintPeashooterProps, PlantPropertySheet, RtClass);

    ArmamintPeashooterProps()
    {
        ProjectileTimeOfFlight = 1.2f;
        ProjectileLobHeight = 350.f;
        NumberOfShots = 5;
        NumberOfPlantFoodShots = 5;
        AdvancedRate = 1.0f;
        ImprovedAdvancedBonus = 1.0f;
        Lvl5Rate = 1.0f;
        PlantfoodFireRate = 1.0f;
    }

    // Projectile properties
    float ProjectileTimeOfFlight;
    float ProjectileLobHeight;
    int NumberOfShots;
    int NumberOfPlantFoodShots;
    float AdvancedRate;
    float ImprovedAdvancedBonus;
    float Lvl5Rate;
    float PlantfoodFireRate;
};

class ArmamintProjectile : public Projectile
{
public:
	RT_CLASS_DEFINE(ArmamintProjectile, Projectile, RtClass);

	bool OnCollideEntity(BoardEntity* i_entity) override;
	bool OnCollideGround() override;
	void SetInitialLaunchValues(float i_height, float i_timeToTarget, int i_row);

protected:
	void onProjectileInitialized() override;
    void fillDamageInfo(DamageInfo& o_info, BoardEntity* pImpactedEntity = NULL) override;

private:
	void DoBounce();
	BoardEntity* findNextTarget(int i_row = -1);
    BoardEntity* findNearestTargetType(BoardEntityTypeFlag i_flag, int i_row);

	float m_initialLobHeightThisBounce;
	float m_initialTimeOfFlightThisBounce;
	float m_reductionRatio;
	float m_targetingRadius;
	int m_rowBeingFiredAt;
	std::vector<BoardEntityPtr>	m_targetsAlreadyHit;
};

class ArmamintProjectileProjectileProps : public ProjectilePropertySheet
{
public:
	RT_CLASS_DEFINE(ArmamintProjectileProjectileProps, ProjectilePropertySheet, RtClass);

	ArmamintProjectileProjectileProps()
	{
		ProjectileBounceCount = 5;
		ProjectileRetargetingRadius = 200.0f;
		PropertyReductionMultiplierPerBounce = 0.75;
		DamageReductionAmountPerBounce = 5;
	}

	int ProjectileBounceCount;
	float ProjectileRetargetingRadius;
	float PropertyReductionMultiplierPerBounce;
    float DamageReductionAmountPerBounce;
    float ProjectileTimeOfFlight;
    float ProjectileLobHeight;
};

class PlantAnimRig_ArmamintPeashooter : public PlantAnimRig
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_ArmamintPeashooter, PlantAnimRig, RtClass);
    PlantAnimRig_ArmamintPeashooter();
    void SetAttackType(AttackType i_type) { m_type = i_type; }
    AttackType GetAttackType() { return m_type; }

protected:
	virtual void onAnimStopped() override;
    std::string getAttackAnimationName() override;
private:
    AttackType m_type;
};

class PlantArmamintPeashooter : public PlantFramework
{
public:
    RT_CLASS_DEFINE(PlantArmamintPeashooter, PlantFramework, RtClass);
    
    void Initialize() override;
    void PlayAttackAnimation() override;
    Projectile* Fire(ZombiePtr targetZombie, int i_row, PlantWeapon i_plantWeapon) override;
    bool CanApplyPlantfood() override;
    bool TriggerAdvancedAttack();
    bool TriggerFireAttack();

protected:
	/// BRAD NOTE: This is some starting work to separate out the concept of finding targets
	//             uniquely by row, given your column and row. The follow up work to this would
	//             be to take the underlying dependency functions (FindZombieTarget,
	//             FindTargetableGridItem) and make it such that those are just calling utility
	//             functions that take in all necessary parameters. We also have the call for searching
	//             for targets spread across rows more genericized, though it is currently dependent
	//             on not only the underlying functions, but also the rectandle and search parameters
	//             for plants. Ideally it would just take the starting rectangle in and do what minor
	//             modifications are necessary for the search.
	void findTargetsSpreadAcrossRows(std::vector<RtWeakPtr<class BoardEntity>>& io_zombieTargets, std::vector<RtWeakPtr<class BoardEntity>>& io_gridObjTargets, int i_startCol, int i_startRow, int i_spreadDistance, PlantWeapon i_plantWeapon);
	void findAndInsertTargetForRow(std::vector<RtWeakPtr<class BoardEntity>>& io_zombieTargets, std::vector<RtWeakPtr<class BoardEntity>>& io_gridObjTargets, int i_col, int i_row, PlantWeapon i_plantWeapon);
	
	// BRAD NOTE: This is also some starting work for breaking out the concept of launching into
	//            something slightly more manageable. Some things to note about dependencies:
	//            - this requires the plant's fire function, when ideally it should take a
	//              created and set projectile as a variable and then perform operations as necessary
	//            - this version is specifically for number of shots iterating over an already sorted
	//              target list, which prioritizes landing multiple shots against the highest priority
	//              targets as it iterates
	Projectile* launchAtTargetsForNumShots(const std::vector<RtWeakPtr<class BoardEntity>>& i_zombieTargets, const std::vector<RtWeakPtr<class BoardEntity>>& i_gridObjTargets, int i_numShots, PlantWeapon i_plantWeapon, AttackType i_type);
	Projectile* launchAtEntity(RtWeakPtr<class BoardEntity> i_target, PlantWeapon i_plantWeapon, AttackType i_type);
	SexyVector3 getTargetLocationForEntity(RtWeakPtr<class BoardEntity> i_target);
    void launchProjectileAt(Projectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);
    void launchProjectileAt(ArmamintProjectile* i_projectile, const SexyVector3& i_targetLoc, float i_heightVariance, float i_timeOfFlightVariance);

private:
	float m_superProjectRate;
};

#endif /* Plant_ArmamintPeashooter_h */
