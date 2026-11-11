//
//  Plant_CeleryStalker.h
//  PlantsVersusZombies2
//
//  Created by Aaron Schneider on 7/13/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//


#ifndef __PlantsVersusZombies2__Plant_CeleryStalker__
#define __PlantsVersusZombies2__Plant_CeleryStalker__

#include "PlantFramework.h"
#include "PlantPropertySheet.h"
#include "PlantAnimRig.h"

class PlantTypeCeleryStalker : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeCeleryStalker, PlantType, RtClass) {}
	
	// void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
    bool CanPlantOnPlant(Plant* i_plant) const override;
};

class PlantCeleryStalker : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantCeleryStalker, PlantFramework, RtClass);
	~PlantCeleryStalker();

	void Initialize() override;
	void UpdateActions() override;
    
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    bool CanApplyPlantfood() override;
	void ApplyPlantfood() override;
    void CancelPlantfood() override;
	DamageInfo TakeDamage(const DamageInfo& i_damage) override;
	bool CanUpgrade(void);
	void onHealed() override;
	
    BoardEntityHeight		GetEntityHeight() const override;

protected:
	void onAnimStoppedCallback(const std::string& i_animLabel) override;

private:
	enum State
	{
		STATE_START_ATTACK = STATE_FRAMEWORK_BEGIN,
		STATE_ATTACK,
        STATE_ATTACK_SPECIAL,
		STATE_FINISH_ATTACK,
        STATE_SUBMERGED,
        STATE_RISING,
		STATE_NEEDS_PLANTFOOD_ATTACK,
	};

    void setState(const uint i_state);
    std::vector<Point> findPlantableGridCells();
    void executePlantFoodEffect();
	bool targetFound();
	void updateDamageVisuals();
	void createDuplicateStalker(const Point& pt);
    
    void tossZombie(Zombie* i_zombie);
    void onEntityDamaged(BoardEntity* i_entity) override;
    bool CanFireZombie(const Zombie* i_zombie) const;
    bool trySpecialAttack();
    bool canSpecialAttack();
    void createBounceEffectAt(Zombie* zombie, std::string animationName);

    pvztime_t m_lastAttack = PVZ_EOT();
	std::vector<PlantPtr> m_PFSpawnedStalkers;
    bool m_BounceZombieEnabled = false;
};

class PlantAnimRig_CeleryStalker : public PlantAnimRig
{
public:
	RT_CLASS_DEFINE(PlantAnimRig_CeleryStalker, PlantAnimRig, RtClass);

	void onPopAnimInitialized() override;

	void StartAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
	void LoopAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void StopAttacking(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void Submerge(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void Emerge(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    void SpecialAttack(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
    bool PlayPreviewAnim(bool bHideLayer) override;
	
	void ShowDamaged0();
	void ShowDamaged1();
	void ShowDamaged2();
	
private:
	void hideAllDamage();
    std::string getIdleAnimationName() override;
    
    bool m_submerged = true;
};

class CeleryStalkerProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(CeleryStalkerProps, PlantPropertySheet, RtClass);

	CeleryStalkerProps()
	{
        PlantFoodPlantsToSpawn = 3;
		RetractionDelay = 3;
        KnockbackTime = 0.5f;
        KnockbackHeight = 130.0f;
        KnockbackOffset = 96.0f;
        RectZombieProximity.mX = 0.0;
        RectZombieProximity.mY = -50;
        RectZombieProximity.mWidth = 64;
        RectZombieProximity.mHeight = 60;
        bounceZombieChance1 = 0.6f;
        bounceZombieChance2 = 1.0f;
	}
    
    int PlantFoodPlantsToSpawn;
	float RetractionDelay;
	float HitPointRemainingForDamage1;
	float HitPointRemainingForDamage2;
    float   KnockbackTime;
    float   KnockbackHeight;
    float   KnockbackOffset;
    Sexy::Rect RectZombieProximity;
    float bounceZombieChance1;
    float bounceZombieChance2;
};

#endif /* defined(__PlantsVersusZombies2__Plant_CeleryStalker__) */
